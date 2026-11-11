#!/usr/bin/env python3
"""
make_3mf.py - Wordclock 16x16, Bambu Studio project (3MF) per language from a template, v1.0

The template (tools/template_P2S.3mf) is a normal Bambu Studio project, saved with Ctrl+S. It holds everything that is
not geometry: printer, process profile, bed type, filaments, the filament change after the front skin, per object
settings (infill, shells, supports ...), plates and the position of every part on its plate. This script only swaps
the meshes and keeps all the rest, so a change in the template (e.g. supports off for one holder) shows up in every
new 3MF after the next run.

Objects of the template are found by their name (".stl" and "_freecad" are ignored):
  Frame...  / Front        -> the front of the language (Frame_<LANG>_<font of the language>.stl)
  Rear (or Holder_Rear)    -> Rear.stl
  Holder_<name>            -> Holder_<name>.stl, plus Holder_<name>_Support.stl as a second part of the same object
                              (break-away supports; in Bambu Studio: right click on the part > Delete, if not wanted)
Supports are only added to holders that stand on the plate as exported (template object not tilted).
The plate with the front gets the name of the front (Frame_<LANG>_<font>).

All STL files are brought up to date first with tools/export_fronts.py (OpenSCAD; unchanged STL files are skipped,
see export_info.json), so the 3MF always shows the current model (--reuse = take existing files, only for tests).
A 3MF is only written again when its STL files, the template or make_3mf.py changed (3mf_info.json in the output
folder, see tools/wc_stamp.py; --force = all). Languages with their own script (CN, JP, KR, runes) get their
own font, its tag is in the file names; a missing font stops the run before anything is exported.
Input:  _private/makerworld/export/           Output: _private/makerworld/export_3mf/
  Wordclock_<LANG>_<font>.3mf   one project per language (default)
  Wordclock_ALL_<font>.3mf      --all: one project with one plate per front plus the plates of the other parts
  Wordclock_Pictureframe_<FRAME>_<LANG>_<font>.3mf   --pictureframe: one project per language and picture frame
                                (export_fronts.PF_FRAMES: RIBBA, SANNAHED; --frame RIBBA = only this one) with one
                                plate: the PictureFrame plate takes the place and all settings (filament change, per
                                object settings) of the front of the template - no template of its own needed

Call:  python tools/make_3mf.py [--lang DE GB ...] [--all | --all-only | --pictureframe [--frame RIBBA]]
                         [--font Liberation] [--template FILE]
                                [--reuse] [--no-supports] [--quality Fine] [--manifold] [--log FILE] [--force]
       (or tools/wordclock_tools.bat, items 12, 13 and 16)
Pure Python 3 (no extra packages).
"""
import argparse
import json
import math
import os
import re
import struct
import sys
import time
import uuid
import zipfile
import xml.etree.ElementTree as ET

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOLS = os.path.join(ROOT, "tools")
MODELS = os.path.join(ROOT, "models")
STL_DIR = os.path.join(ROOT, "_private", "makerworld", "export")
OUT_DIR = os.path.join(ROOT, "_private", "makerworld", "export_3mf")
TEMPLATE = os.path.join(TOOLS, "template_P2S.3mf")
sys.path.insert(0, TOOLS)
import export_fronts  # noqa: E402  (same folder; OpenSCAD export and font tags)
import wc_stamp  # noqa: E402

NS = {"m": "http://schemas.microsoft.com/3dmanufacturing/core/2015/02",
      "p": "http://schemas.microsoft.com/3dmanufacturing/production/2015/06"}
P_UUID = "{%s}UUID" % NS["p"]
P_PATH = "{%s}path" % NS["p"]
MAX_PLATES = 36            # Bambu Studio limit of plates per project
PLATE_GAP = 1.2            # plates are placed in a grid, distance = bed size * 1.2 (Bambu Studio)


# ------------------------------------------------------------------ STL
def load_stl(path):
    """Returns (vertices as list of 'x y z' strings, triangles as index tuples). Binary and ASCII STL."""
    with open(path, "rb") as f:
        data = f.read()
    verts, index, tris = [], {}, []

    def vid(key):
        i = index.get(key)
        if i is None:
            i = index[key] = len(verts)
            verts.append(key)
        return i

    n = struct.unpack_from("<I", data, 80)[0] if len(data) >= 84 else 0
    if len(data) == 84 + 50 * n and n:
        for rec in struct.iter_unpack("<12fH", data[84:84 + 50 * n]):
            a = vid((rec[3], rec[4], rec[5]))
            b = vid((rec[6], rec[7], rec[8]))
            c = vid((rec[9], rec[10], rec[11]))
            if a != b and b != c and a != c:
                tris.append((a, b, c))
    else:
        vals = re.findall(rb"vertex\s+(\S+)\s+(\S+)\s+(\S+)", data)
        for k in range(0, len(vals) - 2, 3):
            a = vid(tuple(float(x) for x in vals[k]))
            b = vid(tuple(float(x) for x in vals[k + 1]))
            c = vid(tuple(float(x) for x in vals[k + 2]))
            if a != b and b != c and a != c:
                tris.append((a, b, c))
    return verts, tris


def bbox(verts):
    xs, ys, zs = zip(*verts)
    return (min(xs), min(ys), min(zs)), (max(xs), max(ys), max(zs))


# ------------------------------------------------------------------ transforms (3MF: row vector p' = p * M + t)
def parse_tf(s):
    v = [float(x) for x in s.split()]
    return [v[0:3], v[3:6], v[6:9]], v[9:12]


def fmt_tf(m, t):
    return " ".join("%.9g" % x for x in m[0] + m[1] + m[2] + list(t))


def rot_z(m, p):
    return p[0] * m[0][2] + p[1] * m[1][2] + p[2] * m[2][2]


def tilted(m):
    return abs(m[2][2] - 1.0) > 1e-6


def plate_cols(n):
    v = math.sqrt(n)
    r = round(v)
    return int(r + 1 if v > r else r)


def plate_offset(i, n, stride):
    """World offset of plate i (0-based) of n plates (grid as in Bambu Studio)."""
    cols = plate_cols(n)
    return ((i % cols) * stride[0], -(i // cols) * stride[1])


# ------------------------------------------------------------------ template
class Template:
    def __init__(self, path):
        with zipfile.ZipFile(path) as z:
            self.files = {n: z.read(n) for n in z.namelist()}
        self.model = ET.fromstring(self.files["3D/3dmodel.model"])
        self.settings = ET.fromstring(self.files["Metadata/model_settings.config"])
        self.project = json.loads(self.files["Metadata/project_settings.config"].decode("utf-8"))
        area = self.project.get("printable_area", ["0x0", "256x0", "256x256", "0x256"])
        xs = [float(p.split("x")[0]) for p in area]
        ys = [float(p.split("x")[1]) for p in area]
        self.stride = ((max(xs) - min(xs)) * PLATE_GAP, (max(ys) - min(ys)) * PLATE_GAP)
        # build items (position on the bed)
        self.items = {}
        for it in self.model.find("m:build", NS).findall("m:item", NS):
            self.items[it.get("objectid")] = parse_tf(it.get("transform", "1 0 0 0 1 0 0 0 1 0 0 0"))
        # objects and plates from model_settings.config
        self.objects = {}
        for ob in self.settings.findall("object"):
            meta = [(m.get("key"), m.get("value")) for m in ob.findall("metadata") if m.get("key")]
            parts = ob.findall("part")
            pmeta = [(m.get("key"), m.get("value")) for m in parts[0].findall("metadata")] if parts else []
            name = dict(meta).get("name", "")
            self.objects[ob.get("id")] = {"name": name, "role": role_of(name), "meta": meta, "part_meta": pmeta}
        self.plates = []
        for pl in self.settings.findall("plate"):
            meta = [(m.get("key"), m.get("value")) for m in pl.findall("metadata")]
            inst = [inst.find("metadata[@key='object_id']").get("value") for inst in pl.findall("model_instance")]
            self.plates.append({"meta": meta, "objects": inst})
        # filament changes per plate
        self.gcodes = {}
        if "Metadata/custom_gcode_per_layer.xml" in self.files:
            root = ET.fromstring(self.files["Metadata/custom_gcode_per_layer.xml"])
            for pl in root.findall("plate"):
                pid = pl.find("plate_info").get("id")
                self.gcodes[pid] = [ET.tostring(e, encoding="unicode").strip() for e in pl if e.tag != "plate_info"]
        # local position of every object on its plate
        n = len(self.plates)
        for i, pl in enumerate(self.plates):
            ox, oy = plate_offset(i, n, self.stride)
            for oid in pl["objects"]:
                m, t = self.items[oid]
                self.objects[oid]["rot"] = m
                self.objects[oid]["local"] = (t[0] - ox, t[1] - oy)

    def plate_meta(self, i, key):
        return dict(self.plates[i]["meta"]).get(key)


def role_of(name):
    n = re.sub(r"\.(stl|step|stp|3mf|obj)$", "", name, flags=re.I)
    n = re.sub(r"_freecad$", "", n)
    if n.lower().startswith("frame") or n.lower() == "front":
        return "FRONT"
    if n == "Holder_Rear":
        return "Rear"
    return n


# ------------------------------------------------------------------ writer
class Builder:
    """Collects plates and objects and writes a Bambu Studio 3MF based on the template."""

    def __init__(self, tpl, title):
        self.tpl, self.title = tpl, title
        self.plates = []          # (template plate index, name, [object entries])
        self.next_id = 1

    def add_plate(self, tpl_index, name):
        self.plates.append((tpl_index, name, []))

    def add_object(self, tpl_oid, name, meshes):
        """meshes: list of (part name, source file, verts, tris) or of functions that return it (loaded only while
        the object is written - keeps the memory low for the file with all fronts), all in print coordinates."""
        self.plates[-1][2].append((tpl_oid, name, meshes))

    def write(self, path):
        tpl = self.tpl
        n = len(self.plates)
        if n > MAX_PLATES:
            print("WARNING: %d plates - Bambu Studio allows at most %d" % (n, MAX_PLATES))
        tmp = path + ".tmp"
        z = zipfile.ZipFile(tmp, "w", zipfile.ZIP_DEFLATED, compresslevel=6)
        for k in ("[Content_Types].xml", "_rels/.rels"):
            z.writestr(k, tpl.files[k])
        files = {k: v for k, v in tpl.files.items()
                 if not (k.startswith("3D/") or re.match(r"Metadata/(plate_\d+\.json|model_settings\.config|"
                                                          r"custom_gcode_per_layer\.xml|filament_sequence\.json|"
                                                          r"cut_information\.xml)$", k))}
        res, build, rels, cfg_objects, cfg_plates, gcode_plates = [], [], [], [], [], []
        obj_no = 0
        identify = 1000
        for pi, (ti, pname, objs) in enumerate(self.plates):
            ox, oy = plate_offset(pi, n, tpl.stride)
            inst = []
            for tpl_oid, name, meshes in objs:
                meshes = [mm() if callable(mm) else mm for mm in meshes]
                obj_no += 1
                t_ob = tpl.objects[tpl_oid]
                m = t_ob["rot"]
                allv = [v for (_, _, verts, _) in meshes for v in verts]
                lo, hi = bbox(allv)
                c = [(lo[k] + hi[k]) / 2.0 for k in range(3)]
                zmin = min(rot_z(m, (v[0] - c[0], v[1] - c[1], v[2] - c[2])) for v in allv)
                t = (t_ob["local"][0] + ox, t_ob["local"][1] + oy, -zmin)
                # sub objects (one per part) in their own file
                sub_xml, comps, parts_cfg = [], [], []
                for vi, (pn, src, verts, tris) in enumerate(meshes):
                    sid = self.next_id
                    self.next_id += 1
                    vx = "".join('<vertex x="%.7g" y="%.7g" z="%.7g"/>' % (v[0] - c[0], v[1] - c[1], v[2] - c[2])
                                 for v in verts)
                    tx = "".join('<triangle v1="%d" v2="%d" v3="%d"/>' % tr for tr in tris)
                    sub_xml.append('<object id="%d" p:UUID="%s" type="model"><mesh><vertices>%s</vertices>'
                                   '<triangles>%s</triangles></mesh></object>' % (sid, uuid.uuid4(), vx, tx))
                    comps.append('<component p:path="/3D/Objects/object_%d.model" objectid="%d" p:UUID="%s" '
                                 'transform="1 0 0 0 1 0 0 0 1 0 0 0"/>' % (obj_no, sid, uuid.uuid4()))
                    pm = [(k, v) for k, v in t_ob["part_meta"] if k not in
                          ("name", "matrix", "source_file", "source_object_id", "source_volume_id",
                           "source_offset_x", "source_offset_y", "source_offset_z")] if vi == 0 else []
                    meta = [("name", pn), ("matrix", "1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1"),
                            ("source_file", src), ("source_object_id", "0"), ("source_volume_id", str(vi)),
                            ("source_offset_x", "%.9g" % c[0]), ("source_offset_y", "%.9g" % c[1]),
                            ("source_offset_z", "%.9g" % c[2])] + pm
                    parts_cfg.append('    <part id="%d" subtype="normal_part" uuid="%s">\n%s\n'
                                     '      <mesh_stat face_count="%d" edges_fixed="0" degenerate_facets="0" '
                                     'facets_removed="0" facets_reversed="0" backwards_edges="0"/>\n    </part>'
                                     % (sid, uuid.uuid4(), "\n".join('      <metadata key="%s" value="%s"/>' % (k, esc(v))
                                                       for k, v in meta), len(tris)))
                z.writestr("3D/Objects/object_%d.model" % obj_no, (
                    '<?xml version="1.0" encoding="UTF-8"?>\n<model unit="millimeter" xml:lang="en-US" '
                    'xmlns="%s" xmlns:BambuStudio="http://schemas.bambulab.com/package/2021" xmlns:p="%s" '
                    'requiredextensions="p">\n <metadata name="BambuStudio:3mfVersion">1</metadata>\n <resources>\n'
                    '%s\n </resources>\n <build/>\n</model>\n' % (NS["m"], NS["p"], "\n".join(sub_xml))).encode("utf-8"))
                faces = sum(len(x[3]) for x in meshes)
                del sub_xml, meshes, allv
                rels.append('<Relationship Target="/3D/Objects/object_%d.model" Id="rel-%d" '
                            'Type="http://schemas.microsoft.com/3dmanufacturing/2013/01/3dmodel"/>' % (obj_no, obj_no))
                oid = self.next_id
                self.next_id += 1
                res.append('  <object id="%d" p:UUID="%s" type="model">\n   <components>\n    %s\n   </components>\n'
                           '  </object>' % (oid, uuid.uuid4(), "\n    ".join(comps)))
                build.append('  <item objectid="%d" p:UUID="%s" transform="%s" printable="1"/>'
                             % (oid, uuid.uuid4(), fmt_tf(m, t)))
                ometa = [(k, v) for k, v in t_ob["meta"] if k != "name"]
                cfg_objects.append('  <object id="%d">\n    <metadata key="name" value="%s"/>\n%s\n'
                                   '    <metadata face_count="%d"/>\n%s\n  </object>'
                                   % (oid, esc(name), "\n".join('    <metadata key="%s" value="%s"/>' % (k, esc(v))
                                                                 for k, v in ometa),
                                      faces, "\n".join(parts_cfg)))
                identify += 1
                inst.append('    <model_instance>\n      <metadata key="object_id" value="%d"/>\n'
                            '      <metadata key="instance_id" value="0"/>\n'
                            '      <metadata key="identify_id" value="%d"/>\n    </model_instance>' % (oid, identify))
            # plate: metadata of the template plate, new id/name, thumbnails copied
            pmeta = []
            for k, v in tpl.plates[ti]["meta"]:
                if k == "plater_id":
                    v = str(pi + 1)
                elif k == "plater_name":
                    v = pname
                elif k in ("thumbnail_file", "thumbnail_no_light_file", "top_file", "pick_file"):
                    new = re.sub(r"_\d+\.png$", "_%d.png" % (pi + 1), v)
                    if v in tpl.files:
                        files[new] = tpl.files[v]
                    small = v.replace(".png", "_small.png")
                    if small in tpl.files:
                        files[new.replace(".png", "_small.png")] = tpl.files[small]
                    v = new
                pmeta.append('    <metadata key="%s" value="%s"/>' % (k, esc(v)))
            cfg_plates.append('  <plate>\n%s\n%s\n  </plate>' % ("\n".join(pmeta), "\n".join(inst)))
            gc = tpl.gcodes.get(str(ti + 1))
            if gc:
                gcode_plates.append('<plate>\n<plate_info id="%d"/>\n%s\n</plate>' % (pi + 1, "\n".join(gc)))
        # main model: template header (metadata), new resources and build
        head = []
        for md in tpl.model.findall("m:metadata", NS):
            v = md.text or ""
            if md.get("name") == "Title":
                v = self.title
            elif md.get("name") in ("CreationDate", "ModificationDate"):
                v = time.strftime("%Y-%m-%d")
            head.append(' <metadata name="%s">%s</metadata>' % (md.get("name"), esc(v)))
        files["3D/3dmodel.model"] = (
            '<?xml version="1.0" encoding="UTF-8"?>\n<model unit="millimeter" xml:lang="en-US" xmlns="%s" '
            'xmlns:BambuStudio="http://schemas.bambulab.com/package/2021" xmlns:p="%s" requiredextensions="p">\n%s\n'
            ' <resources>\n%s\n </resources>\n <build p:UUID="%s">\n%s\n </build>\n</model>\n'
            % (NS["m"], NS["p"], "\n".join(head), "\n".join(res), uuid.uuid4(), "\n".join(build))).encode("utf-8")
        files["3D/_rels/3dmodel.model.rels"] = (
            '<?xml version="1.0" encoding="UTF-8"?>\n<Relationships '
            'xmlns="http://schemas.openxmlformats.org/package/2006/relationships">\n %s\n</Relationships>\n'
            % "\n ".join(rels)).encode("utf-8")
        files["Metadata/model_settings.config"] = ('<?xml version="1.0" encoding="UTF-8"?>\n<config>\n%s\n%s\n'
                                                   '</config>\n' % ("\n".join(cfg_objects), "\n".join(cfg_plates))
                                                   ).encode("utf-8")
        if gcode_plates:      # <mode> is part of every <plate> in the template, copied with it
            files["Metadata/custom_gcode_per_layer.xml"] = (
                '<?xml version="1.0" encoding="utf-8"?>\n<custom_gcodes_per_layer>\n%s\n</custom_gcodes_per_layer>\n'
                % "\n".join(gcode_plates)).encode("utf-8")
        files["Metadata/filament_sequence.json"] = json.dumps(
            {"plate_%d" % (i + 1): {"nozzle_sequence": [], "optimal_assignment": [], "sequence": []}
             for i in range(n)}).encode("utf-8")
        files["Metadata/cut_information.xml"] = ('<?xml version="1.0" encoding="utf-8"?>\n<objects>\n%s\n</objects>\n'
                                                 % "\n".join(' <object id="%d">\n  <cut_id id="0" check_sum="1" '
                                                             'connectors_cnt="0"/>\n </object>' % (i + 1)
                                                             for i in range(obj_no))).encode("utf-8")
        for k in sorted(files):
            if k not in ("[Content_Types].xml", "_rels/.rels"):
                z.writestr(k, files[k])
        z.close()
        os.replace(tmp, path)


def esc(s):
    return (str(s).replace("&", "&amp;").replace('"', "&quot;").replace("<", "&lt;").replace(">", "&gt;"))


# ------------------------------------------------------------------ PictureFrame
def pictureframe(a, tpl, front_plate, langs):
    """--pictureframe: one 3MF per language and frame, the plate replaces the front of the template."""
    frames = a.frame or list(export_fronts.PF_FRAMES)
    names = [(L, f, export_fronts.pf_name(L, a.font, f)) for f in frames for L in langs]
    print("\n=== Step 3/4: export the PictureFrame STL files (%d frames x %d languages) - takes a while"
          % (len(frames), len(langs)))
    args = ["--font", a.font, "--quality", a.quality] + (["--manifold"] if a.manifold else []) + \
        (["--force"] if a.force else [])
    todo = langs
    if a.reuse:
        print("--reuse: existing STL files are used, only missing ones are exported")
        todo = sorted({L for L, f, n in names if not os.path.isfile(os.path.join(STL_DIR, n + ".stl"))})
    if todo:
        if export_fronts.main(["PictureFrame", "--lang"] + todo + ["--frame"] + frames + args) == 2:
            return 2                                  # font missing
        print()
    failed = [n for L, f, n in names if not os.path.isfile(os.path.join(STL_DIR, n + ".stl"))]
    if failed:
        print("ERROR: missing STL files: %s\n       the 3MF of these are left out" % " ".join(failed))
    front = [o for o in tpl.plates[front_plate]["objects"] if tpl.objects[o]["role"] == "FRONT"][0]
    gc = " ".join(re.findall(r'top_z="([\d.]+)', " ".join(tpl.gcodes.get(str(front_plate + 1), []))))
    if gc:
        print("Filament change of the template front at z = %s mm is taken over - check it fits the plate"
              % ", ".join("%.2f" % float(x) for x in gc.split()))
    os.makedirs(OUT_DIR, exist_ok=True)
    info = wc_stamp.Info(os.path.join(OUT_DIR, "3mf_info.json"), a.force)
    bed = (tpl.stride[0] / PLATE_GAP, tpl.stride[1] / PLATE_GAP)
    made = skipped = 0
    print("\n=== Step 4/4: write the 3MF files -> %s" % os.path.relpath(OUT_DIR, ROOT))
    todo = [x for x in names if x[2] not in failed]
    for i, (L, f, name) in enumerate(todo):
        fn = "Wordclock_%s.3mf" % name
        out = os.path.join(OUT_DIR, fn)
        print("[%d/%d] %-14s %-9s -> %s ... " % (i + 1, len(todo), L, f, fn), end="", flush=True)
        title = "Wordclock %s PictureFrame %s" % (L, f)
        inp = wc_stamp.inputs([a.template, os.path.abspath(__file__), os.path.join(STL_DIR, name + ".stl")],
                              title=title)
        if info.fresh(out, inp):
            print("unchanged, skipped")
            skipped += 1
            continue
        v, t = load_stl(os.path.join(STL_DIR, name + ".stl"))
        lo, hi = bbox(v)
        if hi[0] - lo[0] > bed[0] or hi[1] - lo[1] > bed[1]:
            print("WARNING plate %.0f x %.0f mm larger than the bed %.0f x %.0f mm ... "
                  % (hi[0] - lo[0], hi[1] - lo[1], bed[0], bed[1]), end="")
        b = Builder(tpl, title)
        b.add_plate(front_plate, name)
        b.add_object(front, name, [(name, name + ".stl", v, t)])
        del v, t
        b.write(out)
        info.store(out, inp)
        made += 1
        print("ok (%.1f MB)" % (os.path.getsize(out) / 1e6))
    print("\nResult: %d 3MF files written, %d unchanged in %s%s" % (made, skipped, os.path.relpath(OUT_DIR, ROOT),
                                                                  "  - with errors, see above" if failed else ""))
    return 1 if failed else 0


# ------------------------------------------------------------------ main
class Tee:
    """Output to the console and a log file at the same time (progress stays visible)."""
    def __init__(self, *streams):
        self.streams = streams

    def write(self, text):
        for st in self.streams:
            st.write(text)
            st.flush()

    def flush(self):
        for st in self.streams:
            st.flush()


def export_stl(a, langs, parts):
    """Exports the parts and fronts with export_fronts.py; returns the list of missing files (names)."""
    args = ["--font", a.font, "--quality", a.quality] + (["--manifold"] if a.manifold else []) + \
        (["--force"] if a.force else [])
    fronts = [export_fronts.front_name(L, a.font) for L in langs]
    if a.reuse:
        print("--reuse: existing STL files are used, only missing ones are exported")
        parts = [n for n in parts if not os.path.isfile(os.path.join(STL_DIR, n + ".stl"))]
        langs = [L for L, f in zip(langs, fronts) if not os.path.isfile(os.path.join(STL_DIR, f + ".stl"))]
    if parts:
        export_fronts.main(["Parts", "--only"] + parts + args)
        print()
    if langs:
        if export_fronts.main(["Front", "--lang"] + langs + args) == 2:
            return None                               # font missing
        print()
    return [n for n in parts + fronts if not os.path.isfile(os.path.join(STL_DIR, n + ".stl"))]


def main():
    ap = argparse.ArgumentParser(description="Bambu Studio 3MF per language from tools/template_P2S.3mf")
    ap.add_argument("--lang", nargs="*", help="only these languages (default: all of models/lang)")
    ap.add_argument("--all", action="store_true", help="also one 3MF with all fronts (one plate each)")
    ap.add_argument("--all-only", action="store_true", help="only the 3MF with all fronts")
    ap.add_argument("--pictureframe", action="store_true",
                    help="only the PictureFrame plates: one 3MF per language and picture frame")
    ap.add_argument("--frame", nargs="*", type=str.upper, choices=sorted(export_fronts.PF_FRAMES),
                    help="--pictureframe: only these frames (default: all)")
    ap.add_argument("--font", default="Liberation")
    ap.add_argument("--quality", default="Fine")
    ap.add_argument("--manifold", action="store_true")
    ap.add_argument("--template", default=TEMPLATE)
    ap.add_argument("--reuse", action="store_true", help="use existing STL files (default: export everything again)")
    ap.add_argument("--log", help="also write the output to this file")
    ap.add_argument("--no-supports", action="store_true", help="do not add the break-away supports")
    ap.add_argument("--force", action="store_true", help="export and write everything, also unchanged files")
    a = ap.parse_args()
    if a.log:
        os.makedirs(os.path.dirname(os.path.abspath(a.log)), exist_ok=True)
        sys.stdout = Tee(sys.__stdout__, open(a.log, "w", encoding="utf-8"))
    print("make_3mf %s" % time.strftime("%Y-%m-%d %H:%M"))
    a.tag = export_fronts.FONT_TAGS.get(a.font.lower(), a.font)
    if not os.path.isfile(a.template):
        print("Template not found: %s\nSave a Bambu Studio project there (see README, 3MF for Bambu Studio)."
              % a.template)
        return 1
    if not os.path.isfile(os.path.join(MODELS, "Wordclock_Model.scad")):
        print("models/ not found - the 3D models are not part of this repository.")
        return 1
    tpl = Template(a.template)
    t0 = time.time()

    # --- template check
    print("\n=== Step 1/4: read the template")
    print("Template %s (%s, %s)" % (os.path.relpath(a.template, ROOT), tpl.project.get("printer_settings_id"),
                                    tpl.project.get("print_settings_id")))
    print("  bed %s, wall generator %s, infill %s %s, filaments %s"
          % (tpl.project.get("curr_bed_type"), tpl.project.get("wall_generator"),
             tpl.project.get("sparse_infill_pattern"), tpl.project.get("sparse_infill_density"),
             ", ".join(tpl.project.get("filament_settings_id", []))))
    front_plate = None
    for i, pl in enumerate(tpl.plates):
        roles = [tpl.objects[o]["role"] for o in pl["objects"]]
        print("  plate %d \"%s\": %s%s" % (i + 1, tpl.plate_meta(i, "plater_name") or "", ", ".join(roles),
                                          "  (filament change: %d)" % len(tpl.gcodes[str(i + 1)])
                                          if tpl.gcodes.get(str(i + 1)) else ""))
        for o in pl["objects"]:
            ov = [("%s=%s" % (k, v)) for k, v in tpl.objects[o]["meta"] if k not in ("name", "extruder")]
            if ov:
                print("      %-18s %s" % (tpl.objects[o]["role"], ", ".join(ov)))
        if "FRONT" in roles:
            if front_plate is not None or roles.count("FRONT") > 1:
                print("ERROR: the template must contain exactly one front (object name Frame...)")
                return 1
            front_plate = i
    if front_plate is None:
        print("ERROR: no front in the template (object name Frame... or Front)")
        return 1
    if "cool" not in str(tpl.project.get("curr_bed_type", "")).lower():
        print("  NOTE: bed type is \"%s\" (not Cool Plate) - change it in the template if needed"
              % tpl.project.get("curr_bed_type"))
    print()

    # --- STL files
    langs = a.lang or export_fronts.all_langs()
    roles = sorted({o["role"] for o in tpl.objects.values() if o["role"] != "FRONT"})
    sup = [] if a.no_supports else [r + "_Support" for r in roles if r.startswith("Holder_")]
    os.makedirs(STL_DIR, exist_ok=True)
    print("=== Step 2/4: check the fonts (%d languages)" % len(langs))
    errors = export_fronts.check_fonts(langs, a.font, export_fronts.find_openscad(None))
    if errors:
        for e in errors:
            print("ERROR " + e)
        print("\nStopped, nothing exported. Install the fonts with tools/install_fonts.py (wordclock_tools.bat item 15)\n"
              "or leave the languages out with --lang ...")
        return 2
    print("ok: " + ", ".join(sorted({export_fronts.font_for(L, a.font)[0] for L in langs})))
    if a.pictureframe:
        r = pictureframe(a, tpl, front_plate, langs)
        print("(%.0f s)" % (time.time() - t0))
        return r
    print("\n=== Step 3/4: export the STL files (%d parts, %d fronts) - takes a while" % (len(roles + sup), len(langs)))
    failed = export_stl(a, langs, roles + sup)
    if failed is None:
        return 2
    if failed:
        print("ERROR: missing STL files: %s" % " ".join(failed))
        if all(f.startswith("Frame_") or f.endswith("_Support") for f in failed):
            langs = [L for L in langs if export_fronts.front_name(L, a.font) not in failed]
            print("       the 3MF of these languages are left out")
        else:
            return 1
    cache = {}

    def mesh(name):
        if name not in cache:
            p = os.path.join(STL_DIR, name + ".stl")
            if not os.path.isfile(p):
                return None
            v, t = load_stl(p)
            cache[name] = (name, name + ".stl", v, t)
        return cache[name]

    def front_loader(fname):
        def load():
            p = os.path.join(STL_DIR, fname + ".stl")
            v, t = load_stl(p)
            return (fname, fname + ".stl", v, t)
        return load

    def fill(b, front_langs):
        for i, pl in enumerate(tpl.plates):
            if i == front_plate:
                for L in front_langs:
                    fname = export_fronts.front_name(L, a.font)
                    b.add_plate(i, fname)
                    for o in pl["objects"]:
                        if tpl.objects[o]["role"] == "FRONT":
                            b.add_object(o, fname, [front_loader(fname)])
                        else:
                            b.add_object(o, tpl.objects[o]["role"], part_meshes(o))
            else:
                b.add_plate(i, tpl.plate_meta(i, "plater_name") or "Plate %d" % (i + 1))
                for o in pl["objects"]:
                    b.add_object(o, tpl.objects[o]["role"], part_meshes(o))

    skipped = set()

    def part_meshes(o):
        r = tpl.objects[o]["role"]
        m = [mesh(r)]
        if r.startswith("Holder_") and not a.no_supports:
            s = mesh(r + "_Support")
            if s and tilted(tpl.objects[o]["rot"]):
                skipped.add(r)
            elif s:
                m.append(s)
        return m

    os.makedirs(OUT_DIR, exist_ok=True)
    info = wc_stamp.Info(os.path.join(OUT_DIR, "3mf_info.json"), a.force)
    stl_parts = [r + ".stl" for r in roles] + ([] if a.no_supports else [r + ".stl" for r in sup])

    def base(front_langs, title):
        files = [a.template, os.path.abspath(__file__)] + \
            [os.path.join(STL_DIR, f) for f in stl_parts] + \
            [os.path.join(STL_DIR, export_fronts.front_name(L, a.font) + ".stl") for L in front_langs]
        return wc_stamp.inputs(files, title=title, no_supports=a.no_supports)

    made = skipped_3mf = 0
    print("\n=== Step 4/4: write the 3MF files -> %s" % os.path.relpath(OUT_DIR, ROOT))
    if not a.all_only:
        for i, L in enumerate(langs):
            fn = "Wordclock_%s.3mf" % export_fronts.front_name(L, a.font)[len("Frame_"):]
            print("[%d/%d] %-14s -> %s ... " % (i + 1, len(langs), L, fn), end="", flush=True)
            inp = base([L], "Wordclock %s" % L)
            if info.fresh(os.path.join(OUT_DIR, fn), inp):
                print("unchanged, skipped")
                skipped_3mf += 1
                continue
            b = Builder(tpl, "Wordclock %s" % L)
            fill(b, [L])
            b.write(os.path.join(OUT_DIR, fn))
            info.store(os.path.join(OUT_DIR, fn), inp)
            made += 1
            print("ok (%.1f MB)" % (os.path.getsize(os.path.join(OUT_DIR, fn)) / 1e6))
    if a.all or a.all_only:
        fn = "Wordclock_ALL_%s.3mf" % a.tag
        print("all %d fronts -> %s ... " % (len(langs), fn), end="", flush=True)
        inp = base(langs, "Wordclock all languages")
        if info.fresh(os.path.join(OUT_DIR, fn), inp):
            print("unchanged, skipped")
            skipped_3mf += 1
        else:
            b = Builder(tpl, "Wordclock all languages")
            fill(b, langs)
            b.write(os.path.join(OUT_DIR, fn))
            info.store(os.path.join(OUT_DIR, fn), inp)
            made += 1
            print("ok (%d plates, %.1f MB)" % (len(b.plates), os.path.getsize(os.path.join(OUT_DIR, fn)) / 1e6))
    if skipped:
        print("\nNOTE: no supports added to %s - tilted on the plate in the template (supports fit the export "
              "orientation standing on the lower edge only)." % ", ".join(sorted(skipped)))
    print("\nResult: %d 3MF files written, %d unchanged in %s  (%.0f s)%s" % (made, skipped_3mf,
                                                                          os.path.relpath(OUT_DIR, ROOT), time.time() - t0,
                                                     "  - with errors, see above" if failed else ""))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
