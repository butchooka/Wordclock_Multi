#!/usr/bin/env python3
"""
check_models.py - Wordclock 16x16, checks the 3D models (OpenSCAD, optionally FreeCAD), v1.0

Renders every part of models/Wordclock_Model.scad and models/Wordclock_Model_PictureFrame.scad with OpenSCAD and
checks the result (pure Python, no extra packages):
  - render errors and "WARNING Wordclock" messages of the model
  - loose bodies: every part must be ONE connected body (catches floating pieces like the old foot)
  - open / non-manifold mesh (edges not shared by exactly two triangles)
  - print orientation: with PRINT_ORIENT = true the part lies on z = 0
  - fit (option --fit): no overlap between the holders and the back / front and between back and front
  - changes against the last saved state (tools/check_models_baseline.json): bounding box and volume
  - FreeCAD (option --freecad): runs Wordclock_Model.FCMacro headless (without front) and compares back and holders
    with the OpenSCAD parts (same size and volume = both files build the same part)

Usage (or tools/wordclock_tools.bat):
    python3 tools/check_models.py                  all parts, compare with the saved state
    python3 tools/check_models.py --quick          without front and PictureFrame (fast)
    python3 tools/check_models.py --fit            additionally the fit check (needs a few more renders)
    python3 tools/check_models.py --freecad        additionally compare with the FreeCAD macro
    python3 tools/check_models.py --update         save the current state as the new reference
    options: --lang GB, --openscad PATH, --freecad-cmd PATH, --keep (keep the STL files in tools/logs/check_models_stl)
Exit code 1 if an error was found.
"""
import argparse
import json
import math
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile
import time

TOOLS = os.path.dirname(os.path.abspath(__file__))      # this script lies in tools/
ROOT = os.path.dirname(TOOLS)
MODELS = os.path.join(ROOT, "models")                    # the models themselves are private, not on GitHub
MAIN = os.path.join(MODELS, "Wordclock_Model.scad")
PFRAME = os.path.join(MODELS, "Wordclock_Model_PictureFrame.scad")
MACRO = os.path.join(MODELS, "Wordclock_Model.FCMacro")
BASELINE = os.path.join(TOOLS, "check_models_baseline.json")   # reference for "changed since the last check"

# part name -> (scad file, -D settings); "front" parts are skipped with --quick
PARTS = [
    ("Front",            MAIN,   {"PART": "Front"}),
    ("Rear",             MAIN,   {"PART": "Rear"}),
    ("Holder_Foot",      MAIN,   {"PART": "Holder_Foot"}),
    ("Holder_Skadis",    MAIN,   {"PART": "Holder_Skadis"}),
    ("Holder_Wall",      MAIN,   {"PART": "Holder_Wall"}),
    ("Holder_BasePlate", MAIN,   {"PART": "Holder_BasePlate"}),
    ("Holder_Foot_Support",      MAIN, {"PART": "Holder_Foot_Support"}),
    ("Holder_Skadis_Support",    MAIN, {"PART": "Holder_Skadis_Support"}),
    ("Holder_Wall_Support",      MAIN, {"PART": "Holder_Wall_Support"}),
    ("Holder_BasePlate_Support", MAIN, {"PART": "Holder_BasePlate_Support"}),
    ("PictureFrame",     PFRAME, {}),
]
SLOW = ("Front", "PictureFrame")
HOLDERS = ("Holder_Foot", "Holder_Skadis", "Holder_Wall", "Holder_BasePlate")
SUPPORTS = tuple(h + "_Support" for h in HOLDERS)   # break-away supports: 2 tubes each, foot support above the base plate
# FreeCAD export label part -> OpenSCAD part
FREECAD_NAMES = {"Rear": "Rear", "Holder_Foot": "Holder_Foot", "Holder_Skadis": "Holder_Skadis",
                 "Holder_Wall": "Holder_Wall", "Holder_BasePlate": "Holder_BasePlate"}
FREECAD_NAMES.update({s_: s_ for s_ in SUPPORTS})

TOL_BBOX = 0.05      # mm, change of the bounding box against the reference
TOL_VOL = 0.005      # 0.5 % change of the volume against the reference
TOL_FC_BBOX = 0.1    # mm, OpenSCAD <-> FreeCAD
TOL_FC_VOL = 0.01    # 1 %, OpenSCAD <-> FreeCAD (different tessellation of round faces)
TOL_FIT = 1.0        # mm^3, overlap that still counts as "touching"
TOL_BED = 0.05       # mm, lowest point in print orientation may be this far from z = 0


# ------------------------------------------------------------------ helpers
def find_openscad(given):
    cands = [given, os.environ.get("OPENSCAD"), shutil.which("openscad"), shutil.which("openscad.com"),
             r"C:\Program Files\OpenSCAD (Nightly)\openscad.com", r"C:\Program Files\OpenSCAD\openscad.com",
             r"C:\Program Files\OpenSCAD\openscad.exe", "/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD"]
    for c in cands:
        if c and os.path.isfile(c):
            return c
    return None


def find_freecadcmd(given):
    cands = [given, os.environ.get("FREECADCMD"), shutil.which("freecadcmd"), shutil.which("FreeCADCmd")]
    for base in (os.environ.get("LOCALAPPDATA", ""), r"C:\Program Files"):
        if base and os.path.isdir(os.path.join(base, "Programs")):
            base = os.path.join(base, "Programs")
        if base and os.path.isdir(base):
            for d in sorted(os.listdir(base), reverse=True):
                if d.lower().startswith("freecad"):
                    cands.append(os.path.join(base, d, "bin", "freecadcmd.exe"))
    for c in cands:
        if c and os.path.isfile(c):
            return c
    return None


def manifold_option(openscad):
    """--backend=Manifold if this OpenSCAD knows it (2024+): renders in seconds instead of minutes."""
    try:
        out = subprocess.run([openscad, "--help"], capture_output=True, text=True, timeout=30)
        if "--backend" in (out.stdout + out.stderr):
            return ["--backend=Manifold"]
    except Exception:
        pass
    return []


def scad_value(v):
    if isinstance(v, bool):
        return "true" if v else "false"
    if isinstance(v, (int, float)):
        return repr(v)
    return '"%s"' % v


def render(openscad, extra, scad, defs, out_stl):
    cmd = [openscad] + extra + ["-o", out_stl]
    for k, v in defs.items():
        cmd += ["-D", "%s=%s" % (k, scad_value(v))]
    cmd.append(scad)
    t0 = time.time()
    p = subprocess.run(cmd, capture_output=True, text=True, encoding="utf-8", errors="replace")
    text = p.stdout + p.stderr
    ok = p.returncode == 0 and os.path.isfile(out_stl) and os.path.getsize(out_stl) > 0
    return ok, text, time.time() - t0


def model_messages(text):
    """WARNING lines of the model (echo) and OpenSCAD errors."""
    warn, err = [], []
    for line in text.splitlines():
        s = line.strip()
        if "WARNING Wordclock" in s:
            warn.append(re.sub(r'^ECHO:\s*"?|"$', "", s))
        elif s.startswith("ERROR") or "Current top level object is empty" in s:
            err.append(s)
    return warn, err


# ------------------------------------------------------------------ STL analysis (pure Python)
def load_stl(path):
    """List of triangles ((x,y,z),(x,y,z),(x,y,z)), ASCII or binary STL."""
    with open(path, "rb") as f:
        data = f.read()
    tris = []
    if data[:5] == b"solid" and b"facet" in data[:400]:
        nums = re.findall(rb"vertex\s+(\S+)\s+(\S+)\s+(\S+)", data)
        v = [(float(a), float(b), float(c)) for a, b, c in nums]
        tris = [(v[i], v[i + 1], v[i + 2]) for i in range(0, len(v) - 2, 3)]
    else:
        n = struct.unpack("<I", data[80:84])[0]
        for i in range(n):
            f = struct.unpack("<12f", data[84 + 50 * i: 84 + 50 * i + 48])
            tris.append((f[3:6], f[6:9], f[9:12]))
    return tris


def analyse(tris):
    """Bounding box, volume, number of connected bodies, number of open/non-manifold edges."""
    key = {}
    parent = []

    def vid(p):
        k = (round(p[0], 3), round(p[1], 3), round(p[2], 3))
        i = key.get(k)
        if i is None:
            i = key[k] = len(parent)
            parent.append(i)
        return i

    def find(i):
        while parent[i] != i:
            parent[i] = parent[parent[i]]
            i = parent[i]
        return i

    vol = 0.0
    lo = [math.inf] * 3
    hi = [-math.inf] * 3
    edges = {}
    ids = []
    for a, b, c in tris:
        vol += (a[0] * (b[1] * c[2] - b[2] * c[1]) - a[1] * (b[0] * c[2] - b[2] * c[0])
                + a[2] * (b[0] * c[1] - b[1] * c[0])) / 6.0
        for p in (a, b, c):
            for k in range(3):
                lo[k] = min(lo[k], p[k])
                hi[k] = max(hi[k], p[k])
        t = (vid(a), vid(b), vid(c))
        if len(set(t)) < 3:
            continue                                   # degenerate triangle
        ids.append(t)
        for e in ((t[0], t[1]), (t[1], t[2]), (t[2], t[0])):
            e = (min(e), max(e))
            edges[e] = edges.get(e, 0) + 1
    for a, b, c in ids:
        ra = find(a)
        parent[find(b)] = ra
        parent[find(c)] = ra
    bodies = len({find(t[0]) for t in ids})
    bad_edges = sum(1 for n in edges.values() if n != 2)
    return {"bbox": [round(x, 3) for x in lo + hi], "volume": round(vol, 1), "bodies": bodies,
            "bad_edges": bad_edges, "triangles": len(tris)}


def fmt_bbox(b):
    return "%.1f x %.1f x %.1f mm" % (b[3] - b[0], b[4] - b[1], b[5] - b[2])


# ------------------------------------------------------------------ checks
class Report:
    def __init__(self):
        self.errors = 0
        self.warnings = 0

    def ok(self, msg):
        print("  OK      " + msg)

    def warn(self, msg):
        self.warnings += 1
        print("  WARNING " + msg)

    def error(self, msg):
        self.errors += 1
        print("  ERROR   " + msg)


def compare(rep, name, cur, ref, tol_bbox, tol_vol, what):
    db = max(abs(a - b) for a, b in zip(cur["bbox"], ref["bbox"]))
    dv = abs(cur["volume"] - ref["volume"]) / max(abs(ref["volume"]), 1e-9)
    if db <= tol_bbox and dv <= tol_vol:
        rep.ok("%s: same as %s" % (name, what))
        return True
    rep.warn("%s: differs from %s - size %s (was %s), volume %.0f mm3 (was %.0f, %+.1f %%)"
             % (name, what, fmt_bbox(cur["bbox"]), fmt_bbox(ref["bbox"]), cur["volume"], ref["volume"],
                100.0 * (cur["volume"] - ref["volume"]) / max(abs(ref["volume"]), 1e-9)))
    return False


def overlap(openscad, extra, a, b, tmp):
    """Volume of the intersection of two STL files (OpenSCAD import), None if OpenSCAD cannot do it."""
    scad = os.path.join(tmp, "fit.scad")
    out = os.path.join(tmp, "fit.stl")
    if os.path.exists(out):
        os.remove(out)
    with open(scad, "w", encoding="utf-8") as f:
        f.write('intersection() { import("%s"); import("%s"); }\n' % (a.replace("\\", "/"), b.replace("\\", "/")))
    p = subprocess.run([openscad] + extra + ["-o", out, scad], capture_output=True, text=True, errors="replace")
    text = p.stdout + p.stderr
    if "top level object is empty" in text:
        return 0.0
    if p.returncode != 0 or not os.path.isfile(out):
        return None
    tris = load_stl(out)
    return abs(analyse(tris)["volume"]) if tris else 0.0


def run_freecad(freecadcmd, tmp):
    """Runs a copy of the macro without front, STL export in assembly coordinates; returns {part: stl}."""
    with open(MACRO, encoding="utf-8") as f:
        src = f.read()
    outdir = os.path.join(tmp, "freecad")
    os.makedirs(outdir, exist_ok=True)
    rep = [(r"^BUILD_FRONT\s*=.*$", "BUILD_FRONT = False"), (r"^BUILD_LETTERS\s*=.*$", "BUILD_LETTERS = False"),
           (r"^EXPORT\s*=.*$", 'EXPORT = "stl"'), (r"^EXPORT_DIR\s*=.*$", "EXPORT_DIR = %r" % outdir),
           (r"^EXPORT_PRINT_POSE\s*=.*$", "EXPORT_PRINT_POSE = False"),
           (r"^LANG_DIR\s*=.*$", "LANG_DIR = %r" % os.path.join(MODELS, "lang"))]
    for pat, new in rep:
        # lambda: the replacement is inserted literally (Windows paths contain backslashes like \U)
        src, n = re.subn(pat, lambda m, new=new: new, src, count=1, flags=re.M)
        if n != 1:
            raise RuntimeError("setting not found in the macro: " + pat)
    macro = os.path.join(tmp, "check_run.FCMacro")
    with open(macro, "w", encoding="utf-8") as f:
        f.write(src)
    p = subprocess.run([freecadcmd, macro], capture_output=True, text=True, errors="replace", cwd=tmp)
    text = p.stdout + p.stderr
    res = {}
    for fn in os.listdir(outdir):
        m = re.match(r"(\w+?)_freecad\.stl$", fn)   # macro export names: <SCAD name>_freecad
        if m and m.group(1) in FREECAD_NAMES:
            res[FREECAD_NAMES[m.group(1)]] = os.path.join(outdir, fn)
    warns = [l.strip() for l in text.splitlines() if "WARNING" in l]
    return res, warns, text


class Tee:
    """Output to the console and a log file at the same time (progress stays visible)."""
    def __init__(self, *streams):
        self.streams = streams

    def write(self, text):
        for s in self.streams:
            s.write(text)
            s.flush()

    def flush(self):
        for s in self.streams:
            s.flush()


# ------------------------------------------------------------------ main
def main():
    ap = argparse.ArgumentParser(description="Checks the Wordclock 3D models")
    ap.add_argument("--quick", action="store_true", help="without front and PictureFrame")
    ap.add_argument("--fit", action="store_true", help="check that holders, back and front do not overlap")
    ap.add_argument("--freecad", action="store_true", help="compare with the FreeCAD macro")
    ap.add_argument("--update", action="store_true", help="save the current state as reference")
    ap.add_argument("--lang", default="DE")
    ap.add_argument("--openscad")
    ap.add_argument("--freecad-cmd")
    ap.add_argument("--keep", action="store_true", help="keep the STL files in tools/logs/check_models_stl")
    ap.add_argument("--log", help="also write the output to this file")
    a = ap.parse_args()
    if a.log:
        sys.stdout = Tee(sys.stdout, open(a.log, "w", encoding="utf-8"))

    openscad = find_openscad(a.openscad)
    if not openscad:
        print("OpenSCAD not found - install it or pass --openscad PATH (or set OPENSCAD).")
        return 1
    extra = manifold_option(openscad)
    print("Wordclock_Multi - model check %s" % time.strftime("%Y-%m-%d %H:%M"))
    print("OpenSCAD: %s%s" % (openscad, " (Manifold)" if extra else " (CGAL, slow - OpenSCAD 2024+ is much faster)"))

    tmp = tempfile.mkdtemp(prefix="wc_check_")
    rep = Report()
    results = {}
    stl = {}
    ref = {}
    if os.path.isfile(BASELINE):
        with open(BASELINE, encoding="utf-8") as f:
            ref = json.load(f).get("parts", {})
    try:
        for name, scad, defs in PARTS:
            if a.quick and name in SLOW:
                continue
            if not os.path.isfile(scad):
                rep.warn("%s: %s missing" % (name, os.path.basename(scad)))
                continue
            print("\n%s (%s)" % (name, os.path.basename(scad)))
            d = dict(defs, LANG=a.lang, PRINT_ORIENT=False)
            out = os.path.join(tmp, name + ".stl")
            ok, text, dt = render(openscad, extra, scad, d, out)
            warn, err = model_messages(text)
            for w in warn:
                rep.warn(w)
            if not ok:
                for e in err or ["render failed"]:
                    rep.error(e)
                continue
            res = analyse(load_stl(out))
            res["seconds"] = round(dt, 1)
            results[name] = res
            stl[name] = out
            rep.ok("rendered in %.0f s: %s, %.0f mm3, %d triangles"
                   % (dt, fmt_bbox(res["bbox"]), res["volume"], res["triangles"]))
            if name in SUPPORTS:
                (rep.ok if res["bodies"] == 2 else rep.error)("%d support tubes (expected 2)" % res["bodies"])
            elif res["bodies"] == 1:
                rep.ok("one connected body")
            else:
                rep.error("%d separate bodies (loose / floating pieces)" % res["bodies"])
            if res["bad_edges"]:
                rep.warn("%d open or non-manifold edges (slicer may need to repair)" % res["bad_edges"])
            if res["volume"] <= 0:
                rep.error("volume <= 0 (inverted mesh)")
            # print orientation
            out_p = os.path.join(tmp, name + "_print.stl")
            okp, textp, _ = render(openscad, extra, scad, dict(d, PRINT_ORIENT=True), out_p)
            if okp:
                zmin = analyse(load_stl(out_p))["bbox"][2]
                if name == "Holder_Foot_Support":
                    rep.ok("print orientation: starts at z = %.2f mm (on the base plate of the foot)" % zmin)
                elif abs(zmin) <= TOL_BED:
                    rep.ok("print orientation on z = 0")
                else:
                    rep.error("print orientation: lowest point at z = %.2f mm instead of 0" % zmin)
            if name in ref:
                compare(rep, name, res, ref[name], TOL_BBOX, TOL_VOL, "the saved state")
            elif ref and not a.update:
                rep.warn("not in the saved state yet (new part?) - run with --update after checking it")

        if a.fit:
            print("\nFit (overlap of assembled parts, touching is allowed)")
            pairs = [(h, "Rear") for h in HOLDERS] + [(h, "Front") for h in HOLDERS] + [("Rear", "Front")] \
                + [(h, h + "_Support") for h in HOLDERS]      # supports must keep their air gap to the holder
            for x, y in pairs:
                if x not in stl or y not in stl:
                    continue
                v = overlap(openscad, extra, stl[x], stl[y], tmp)
                if v is not None and v > 0.9 * min(abs(results[x]["volume"]), abs(results[y]["volume"])):
                    v = None                       # OpenSCAD returned (almost) a whole part: import failed
                if v is None:
                    rep.warn("%s / %s: OpenSCAD could not intersect the parts - not checked" % (x, y))
                elif v <= TOL_FIT:
                    rep.ok("%s / %s: no overlap" % (x, y))
                else:
                    rep.error("%s / %s: overlap %.1f mm3" % (x, y, v))

        if a.freecad:
            print("\nFreeCAD macro (without front) vs. OpenSCAD")
            fc = find_freecadcmd(a.freecad_cmd)
            if not fc:
                rep.warn("freecadcmd not found - pass --freecad-cmd PATH (or set FREECADCMD)")
            else:
                fstl, fwarn, ftext = run_freecad(fc, tmp)
                for w in fwarn:
                    rep.warn("FreeCAD: " + w)
                if not fstl:
                    rep.error("FreeCAD produced no parts:\n" + ftext[-1500:])
                for name, path in sorted(fstl.items()):
                    r = analyse(load_stl(path))
                    if r["bodies"] != (2 if name in SUPPORTS else 1):
                        rep.error("FreeCAD %s: %d separate bodies" % (name, r["bodies"]))
                    if name in results:
                        compare(rep, name, r, results[name], TOL_FC_BBOX, TOL_FC_VOL, "OpenSCAD")

        first = not ref and results and not a.update
        if first:
            print("\nNo saved state yet: this run is saved as the reference for the next checks.")
        if (a.update or first) and results:
            data = {"date": time.strftime("%Y-%m-%d %H:%M"), "lang": a.lang, "parts": dict(ref)}
            data["parts"].update(results)
            with open(BASELINE, "w", encoding="utf-8") as f:
                json.dump(data, f, indent=1)
            print("\nReference saved: %s" % os.path.relpath(BASELINE, ROOT))
        if a.keep:
            dst = os.path.join(ROOT, "tools", "logs", "check_models_stl")
            os.makedirs(dst, exist_ok=True)
            for p in stl.values():
                shutil.copy(p, dst)
            print("STL files: %s" % os.path.relpath(dst, ROOT))
    finally:
        shutil.rmtree(tmp, ignore_errors=True)

    print("\nResult: %s (%d errors, %d warnings)"
          % ("ERRORS FOUND" if rep.errors else "ALL OK", rep.errors, rep.warnings))
    return 1 if rep.errors else 0


if __name__ == "__main__":
    sys.exit(main())
