#!/usr/bin/env python3
"""
export_fronts.py - Wordclock 16x16, exports the front of every language as STL with OpenSCAD, v1.0

Front        = front of the own case (Wordclock_Model.scad, PART = "Front")      -> Frame_<LANG>_<font>.stl
PictureFrame = front plate for a deep picture frame, one file per frame of PF_FRAMES (size = glass size, inner depth;
               all other values = defaults of Wordclock_Model_PictureFrame.scad) -> Pictureframe_<FRAME>_<LANG>_<font>.stl
               RIBBA = IKEA RIBBA 25x25 (231 / 38 mm, default of the model), SANNAHED = IKEA SANNAHED 25x25 (249 / 44 mm);
               --frame RIBBA = only this frame (default: all frames)
Parts        = the language independent parts: Rear.stl, Holder_<name>.stl and the break-away supports
               Holder_<name>_Support.stl (same print coordinates as the holder)
All files in print orientation as binary STL (much smaller than OpenSCAD's default ASCII STL; --ascii = old format).
Fonts: a language with its own script (CN, JP, KR, runes) brings its font in lang_XX.scad; the file name gets the
tag of the font really used (Frame_KR_NotoSansKRBold.stl). Before the export every needed font is searched in the
fonts OpenSCAD sees (Windows: the system font folder = "Install for all users", the fonts of OpenSCAD); if one is
missing, nothing is exported and the font is named (else OpenSCAD would cut empty boxes).
Only LANG, FONT, QUALITY and PRINT_ORIENT (PictureFrame: also size and depth of the frame) are set, all other
parameters are the defaults of the model.
Output: _private/makerworld/export/ (private, not in the repository). FreeCAD: LANG = "ALL" in the macro.
Special case other picture frame: --size/--depth/--tol/--thickness/--glass/--mount set the PictureFrame values
(e.g. another IKEA frame) -> _private/makerworld/export/custom/Pictureframe_<size>x<depth>_<LANG>_<font>.stl
(wordclock_tools.bat item P asks for the values).
Unchanged files are skipped: export_info.json in the output folder holds the base data of every STL (content of the
model, Wordclock_Common.scad, lang_all.scad and the language file, the -D values, OpenSCAD version and the font file,
see tools/wc_stamp.py). Only when one of them changed OpenSCAD runs again (--force = all).

Call:  python tools/export_fronts.py [Front|PictureFrame|Both|Parts] [--lang DE GB ...] [--font Liberation|Arial|DejaVu]
                                     [--quality Preview|Normal|Fine] [--openscad PATH] [--manifold] [--ascii]
                                     [--frame RIBBA SANNAHED] [--size MM] [--depth MM] [--tol MM] [--thickness MM] [--glass MM]
                                     [--mount SCREW|THIMBLES|NONE] [--force]
       (or tools/wordclock_tools.bat)
"""
import argparse
import glob
import os
import re
import shutil
import struct
import subprocess
import sys
import time

import wc_stamp

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MODELS = os.path.join(ROOT, "models")
OUT = os.path.join(ROOT, "_private", "makerworld", "export")
# FONT setting of the model -> OpenSCAD font name
BASE_FONTS = {"liberation": "Liberation Sans:style=Bold", "arial": "Arial:style=Bold", "dejavu": "DejaVu Sans:style=Bold"}
FONT_TAGS = {"liberation": "LiberationSansBold", "arial": "ArialBold", "dejavu": "DejaVuSansBold"}
# language independent parts (PART in Wordclock_Model.scad = file name)
HOLDERS = ["Holder_Foot", "Holder_Skadis", "Holder_Wall", "Holder_BasePlate"]
PARTS = ["Rear"] + HOLDERS + [h + "_Support" for h in HOLDERS]


def find_openscad(given):
    for c in [given, os.environ.get("OPENSCAD"), r"C:\Program Files\OpenSCAD\openscad.exe",
              r"C:\Program Files\OpenSCAD (Nightly)\openscad.exe",
              "/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD"]:
        if c and os.path.isfile(c):
            return c
    return shutil.which("openscad")


def num(v):
    return ("%d" % v) if v == int(v) else ("%g" % v)       # as str() in OpenSCAD: 231.0 -> 231


def pf_default(name, fallback):
    with open(os.path.join(MODELS, "Wordclock_Model_PictureFrame.scad"), encoding="utf-8") as f:
        m = re.search(r"(?m)^%s\s*=\s*([\d.]+)" % name, f.read())
    return float(m.group(1)) if m else fallback


# picture frames with their own export (file name Pictureframe_<FRAME>_<LANG>_<font>.stl, type first = grouped):
# size = glass size (PICTUREFRAME_SIZE), depth = inner depth of the frame (PICTUREFRAME_FRAME_DEPTH), in mm
PF_FRAMES = {"RIBBA": {"size": 231.0, "depth": 38.0},          # IKEA RIBBA 25x25 (default of the model)
             "SANNAHED": {"size": 249.0, "depth": 44.0}}       # IKEA SANNAHED 25x25, measured 2026-11-11


def frame_defs(frame):
    f = PF_FRAMES[frame]
    return ["-D", "PICTUREFRAME_SIZE=%s" % num(f["size"]), "-D", "PICTUREFRAME_FRAME_DEPTH=%s" % num(f["depth"])]


def pf_name(lang, font, frame):
    """File name (without .stl) of the PictureFrame plate of a frame: Pictureframe_RIBBA_DE_LiberationSansBold."""
    return "Pictureframe_%s_%s_%s" % (frame, lang, font_for(lang, font)[1])


# special case other picture frame: option -> (SCAD parameter, min, max) - limits as in the Customizer
PF_CUSTOM = {"size": ("PICTUREFRAME_SIZE", 220, 300), "depth": ("PICTUREFRAME_FRAME_DEPTH", 22, 80),
             "tol": ("PICTUREFRAME_TOL", 0, 2), "thickness": ("PICTUREFRAME_THICKNESS", 1, 4),
             "glass": ("PICTUREFRAME_GLASS_THICKNESS", 0, 3)}


def pf_custom(a):
    """-D definitions and errors for the special case; [] when no PictureFrame value is given."""
    defs, errors = [], []
    for opt, (par, lo, hi) in PF_CUSTOM.items():
        v = getattr(a, opt)
        if v is None:
            continue
        if not lo <= v <= hi:
            errors.append("--%s %s outside %s ... %s mm" % (opt, num(v), num(lo), num(hi)))
        defs += ["-D", "%s=%s" % (par, num(v))]
    if a.mount:
        defs += ["-D", 'PICTUREFRAME_OWN_MOUNT="%s"' % a.mount]
    return defs, errors


def all_langs():
    return sorted(os.path.basename(p)[5:-5] for p in glob.glob(os.path.join(MODELS, "lang", "lang_*.scad"))
                  if not p.endswith("lang_all.scad"))


# ------------------------------------------------------------------ fonts
def lang_font(lang):
    """OpenSCAD font of the language (field 4 of lang_XX.scad: [code, name, [rows], font, file, ...]), "" = FONT."""
    with open(os.path.join(MODELS, "lang", "lang_%s.scad" % lang), encoding="utf-8") as f:
        text = f.read()
    m = re.search(r'\]\s*,((?:\s*"[^"]*"\s*,?)+)\]\s*;\s*$', text)
    fields = re.findall(r'"([^"]*)"', m.group(1)) if m else []
    return (fields[0] if fields else ""), (fields[1] if len(fields) > 1 else "")


def font_tag_of(spec):
    """Short font name as font_tag_of() in Wordclock_Common.scad: "Noto Sans KR:style=Bold" -> NotoSansKRBold."""
    name, _, rest = spec.partition(":")
    style = rest.split("=", 1)[1] if "=" in rest else ""
    t = re.sub(r"[^A-Za-z0-9]", "", name + style)
    return t[:-7] if len(t) > 7 and t.endswith("Regular") else t


def font_for(lang, font):
    """(OpenSCAD font name, tag for the file name) that the model really uses for this language."""
    own = lang_font(lang)[0]
    if own:
        return own, font_tag_of(own)
    return BASE_FONTS.get(font.lower(), font), FONT_TAGS.get(font.lower(), font_tag_of(font))


def front_name(lang, font):
    return "Frame_%s_%s" % (lang, font_for(lang, font)[1])


def _font_names(path):
    """[(family, style)] of a .ttf/.otf/.ttc (name table, ids 1/2 and 16/17), pure Python."""
    res = []
    try:
        with open(path, "rb") as f:
            head = f.read(12)
            offsets = [0]
            if head[:4] == b"ttcf":
                n = struct.unpack(">I", head[8:12])[0]
                offsets = list(struct.unpack(">%dI" % n, f.read(4 * n)))
            for off in offsets:
                f.seek(off)
                ntab = struct.unpack(">4sH", f.read(6))[1]
                f.seek(off + 12)
                tables = {}
                for _ in range(ntab):
                    tag, _c, toff, tlen = struct.unpack(">4sIII", f.read(16))
                    tables[tag] = (toff, tlen)
                if b"name" not in tables:
                    continue
                f.seek(tables[b"name"][0])
                data = f.read(tables[b"name"][1])
                _fmt, count, soff = struct.unpack(">HHH", data[:6])
                names = {}
                for i in range(count):
                    pid, eid, _lid, nid, ln, o = struct.unpack(">HHHHHH", data[6 + 12 * i:18 + 12 * i])
                    if nid not in (1, 2, 16, 17):
                        continue
                    raw = data[soff + o:soff + o + ln]
                    s_ = raw.decode("utf-16-be", "replace") if pid in (0, 3) else raw.decode("latin-1")
                    names.setdefault(nid, set()).add(s_)
                fams = names.get(16, set()) | names.get(1, set())
                styles = names.get(17, set()) | names.get(2, set())
                res += [(fa, st) for fa in fams for st in (styles or {""})]
    except (OSError, struct.error, IndexError):
        pass
    return res


def font_dirs(scad):
    """Font folders OpenSCAD reads (its own fonts, system fonts) and - for a hint only - the per-user fonts."""
    seen = [os.path.join(os.path.dirname(scad), "fonts")] if scad else []
    win = os.environ.get("WINDIR")
    if win:
        seen.append(os.path.join(win, "Fonts"))
    if os.environ.get("LOCALAPPDATA"):
        seen.append(os.path.join(os.environ["LOCALAPPDATA"], "fonts"))
    home = os.path.expanduser("~")
    seen += [os.path.join(home, ".fonts"), os.path.join(home, ".local", "share", "fonts"), "/usr/share/fonts",
             "/usr/local/share/fonts", "/Library/Fonts", "/System/Library/Fonts", os.path.join(home, "Library", "Fonts")]
    user = [os.path.join(os.environ["LOCALAPPDATA"], "Microsoft", "Windows", "Fonts")] if os.environ.get("LOCALAPPDATA") else []
    return [d for d in seen if os.path.isdir(d)], [d for d in user if os.path.isdir(d)]


def _scan(dirs):
    found = {}
    for d in dirs:
        for root, _dirs, files in os.walk(d):
            for fn in files:
                if fn.lower().endswith((".ttf", ".otf", ".ttc")):
                    p = os.path.join(root, fn)
                    for fam, st in _font_names(p):
                        found.setdefault(fam.lower(), []).append((st.lower(), p))
    return found


def check_fonts(langs, font, scad):
    """Returns a list of error lines for fonts that OpenSCAD would not find (then the letters would be empty boxes)."""
    need = {}
    for L in langs:
        need.setdefault(font_for(L, font)[0], []).append(L)
    if all(spec.startswith("Liberation Sans") for spec in need):
        return []                                     # comes with OpenSCAD
    ok_dirs, user_dirs = font_dirs(scad)
    found, user = _scan(ok_dirs), None
    errors = []
    for spec, ls in sorted(need.items()):
        fam, _, rest = spec.partition(":")
        style = rest.split("=", 1)[1].lower() if "=" in rest else ""
        faces = found.get(fam.strip().lower(), [])
        if faces and (not style or any(st == style for st, _ in faces)):
            continue
        if faces:
            print("WARNING: font \"%s\" found without style %s (%s) - OpenSCAD uses another style"
                  % (fam, style, ", ".join(sorted({st for st, _ in faces}))))
            continue
        if user is None:
            user = _scan(user_dirs)
        where = user.get(fam.strip().lower())
        hint = ("installed for your user only (%s) - OpenSCAD does not see it: right click on the font file > "
                "\"Install for all users\"" % os.path.basename(where[0][1])) if where else \
            "not installed - e.g. https://fonts.google.com/?query=%s (static Bold file, \"Install for all users\")" \
            % fam.strip().replace(" ", "+")
        errors.append("font \"%s\" for %s: %s" % (spec, " ".join(ls), hint))
    return errors


# ------------------------------------------------------------------ base data (skip unchanged files)
_VER = {}
_FOUND = {}


def scad_version(scad):
    if scad not in _VER:
        try:
            r = subprocess.run([scad, "--version"], capture_output=True, text=True, timeout=60)
            _VER[scad] = ((r.stdout or "") + (r.stderr or "")).strip().splitlines()[-1:] or [""]
        except (OSError, subprocess.SubprocessError):
            _VER[scad] = [""]
    return _VER[scad][0]


def font_file(spec, scad):
    """Font file OpenSCAD uses for a font name (name and size, for the base data); "" if not found."""
    if scad not in _FOUND:
        _FOUND[scad] = _scan(font_dirs(scad)[0])
    fam, _, rest = spec.partition(":")
    style = rest.split("=", 1)[1].lower() if "=" in rest else ""
    faces = _FOUND[scad].get(fam.strip().lower(), [])
    for st, p in faces:
        if not style or st == style:
            return "%s (%d bytes)" % (os.path.basename(p), os.path.getsize(p))
    return ""


def base_data(scad, extra, defs, model, lang=None, spec=None):
    files = [os.path.join(MODELS, model), os.path.join(MODELS, "Wordclock_Common.scad"),
             os.path.join(MODELS, "lang", "lang_all.scad")]
    if lang:
        files.append(os.path.join(MODELS, "lang", "lang_%s.scad" % lang))
    return wc_stamp.inputs(files, defines=[d for d in defs if d != "-D"], options=extra,
                           openscad=scad_version(scad), font=(font_file(spec, scad) if spec else ""))


# ------------------------------------------------------------------ main
def export(scad, extra, out, defs, model, info, inp):
    """OpenSCAD export, skipped when the base data did not change. Returns True when the file is fine."""
    if info.fresh(out, inp):
        print("unchanged, skipped")
        return True
    ok = run_scad(scad, extra, out, defs, model)
    if ok:
        info.store(out, inp)
    return ok


def run_scad(scad, extra, out, defs, model):
    if os.path.isfile(out):
        os.remove(out)                                # never keep an old file when the export fails
    t = time.time()
    r = subprocess.run([scad] + extra + ["-o", out] + defs + [model], cwd=MODELS, capture_output=True, text=True,
                       encoding="utf-8", errors="replace")
    ok = r.returncode == 0 and os.path.isfile(out)
    if ok:
        print("ok (%.0f s, %.1f MB)" % (time.time() - t, os.path.getsize(out) / 1e6))
    else:
        print("FAILED")
        print("\n".join((r.stderr or "").splitlines()[-8:]))
    return ok


def main(argv=None):
    ap = argparse.ArgumentParser(description="Exports the Wordclock fronts of all languages as STL (OpenSCAD)")
    ap.add_argument("part", nargs="?", default="Front", choices=["Front", "PictureFrame", "Both", "Parts"])
    ap.add_argument("--lang", nargs="*", help="only these languages (default: all of models/lang)")
    ap.add_argument("--font", default="Liberation")
    ap.add_argument("--quality", default="Fine")
    ap.add_argument("--openscad")
    ap.add_argument("--manifold", action="store_true", help="--backend=Manifold (OpenSCAD 2024/2025, much faster)")
    ap.add_argument("--ascii", action="store_true", help="ASCII STL as before (OpenSCAD older than 2021)")
    ap.add_argument("--only", nargs="*", help="Parts: only these part names")
    ap.add_argument("--frame", nargs="*", type=str.upper, choices=sorted(PF_FRAMES),
                    help="PictureFrame: only these frames (default: all of PF_FRAMES)")
    g = ap.add_argument_group("special case other picture frame (PictureFrame only)")
    g.add_argument("--size", type=float, help="picture size = glass size in mm (220 ... 300)")
    g.add_argument("--depth", type=float, help="inner depth of the frame in mm (22 ... 80)")
    g.add_argument("--tol", type=float, help="plate smaller per side in mm (0 ... 2)")
    g.add_argument("--thickness", type=float, help="thickness of the front plate in mm (1 ... 4)")
    g.add_argument("--glass", type=float, help="keep the glass in front of the plate: its thickness, 0 = no glass")
    g.add_argument("--mount", type=str.upper, choices=["SCREW", "THIMBLES", "NONE"], help="fastening")
    ap.add_argument("--force", action="store_true", help="export everything, also unchanged files")
    a = ap.parse_args(argv)

    if not os.path.isfile(os.path.join(MODELS, "Wordclock_Model.scad")):
        print("models/ not found - the 3D models are not part of this repository.")
        return 1
    scad = find_openscad(a.openscad)
    if not scad:
        print("OpenSCAD not found - install it or pass --openscad PATH (or set OPENSCAD).")
        return 1
    langs = a.lang or all_langs()
    parts = ["Front", "PictureFrame"] if a.part == "Both" else [a.part]
    pf_defs, errors = pf_custom(a)
    out_dir = OUT
    if pf_defs:
        if a.part != "PictureFrame":
            errors.append("--size/--depth/--tol/--thickness/--glass/--mount only with PictureFrame")
        if errors:
            for e in errors:
                print("ERROR " + e)
            return 2
        out_dir = os.path.join(OUT, "custom")
        print("Special case picture frame: " + " ".join(d for d in pf_defs if d != "-D"))
    extra = (["--backend=Manifold"] if a.manifold else []) + ([] if a.ascii else ["--export-format", "binstl"])
    os.makedirs(out_dir, exist_ok=True)
    info = wc_stamp.Info(os.path.join(out_dir, "export_info.json"), a.force)
    print("OpenSCAD: %s\n%s, quality %s -> %s" % (scad, " + ".join(parts), a.quality, os.path.relpath(out_dir, ROOT)))
    failed = []
    t0 = time.time()
    if a.part == "Parts":
        names = a.only or PARTS
        print()
        for i, name in enumerate(names):
            fn = name + ".stl"
            print("[%d/%d] %-24s -> %s ... " % (i + 1, len(names), name, fn), end="", flush=True)
            d = ["-D", 'PART="%s"' % name, "-D", 'QUALITY="%s"' % a.quality, "-D", "PRINT_ORIENT=true"]
            if not export(scad, extra, os.path.join(OUT, fn), d, "Wordclock_Model.scad", info,
                          base_data(scad, extra, d, "Wordclock_Model.scad")):
                failed.append(name)
        print("\nResult: %d files, %d failed %s  (%.0f s)" % (len(names) - len(failed), len(failed), " ".join(failed),
                                                           time.time() - t0))
        return 1 if failed else 0

    print("Font %s; languages with their own script use their own font (in the file name)" % a.font)
    print("Checking the fonts ... ", end="", flush=True)
    errors = check_fonts(langs, a.font, scad)
    if errors:
        print("MISSING")
        for e in errors:
            print("ERROR " + e)
        print("\nNothing exported. Install the fonts with tools/install_fonts.py (wordclock_tools.bat item 15) or leave\n"
              "the languages out with --lang ..., then run again.")
        return 2
    print("ok\n")
    # jobs: (part, frame); frame = PF_FRAMES key, "custom" for the special case, None for the front
    jobs = []
    for part in parts:
        if part != "PictureFrame":
            jobs.append((part, None))
        elif pf_defs:
            jobs.append((part, "custom"))
        else:
            jobs += [(part, f) for f in (a.frame or list(PF_FRAMES))]
    if pf_defs and a.frame:
        print("NOTE: --frame is ignored with --size/--depth/... (special case)")
    custom = "%sx%s" % (num(a.size if a.size is not None else pf_default("PICTUREFRAME_SIZE", 231.0)),
                        num(a.depth if a.depth is not None else pf_default("PICTUREFRAME_FRAME_DEPTH", 38.0)))
    total = len(jobs) * len(langs)
    k = 0
    for part, frame in jobs:
        if frame and frame != "custom":
            print("PictureFrame %s: glass %s mm, depth %s mm" % (frame, num(PF_FRAMES[frame]["size"]),
                                                                 num(PF_FRAMES[frame]["depth"])))
        for L in langs:
            k += 1
            spec, tag = font_for(L, a.font)
            d = ["-D", 'LANG="%s"' % L, "-D", 'FONT="%s"' % a.font, "-D", 'QUALITY="%s"' % a.quality,
                 "-D", "PRINT_ORIENT=true"]
            if frame == "custom":
                fn, model = "Pictureframe_%s_%s_%s.stl" % (custom, L, tag), "Wordclock_Model_PictureFrame.scad"
                d += pf_defs
            elif frame:
                fn, model = pf_name(L, a.font, frame) + ".stl", "Wordclock_Model_PictureFrame.scad"
                d += frame_defs(frame)
            else:
                fn, model = "Frame_%s_%s.stl" % (L, tag), "Wordclock_Model.scad"
                d += ["-D", 'PART="Front"']
            print("[%d/%d] %-14s -> %s ... " % (k, total, L, fn), end="", flush=True)
            if not export(scad, extra, os.path.join(out_dir, fn), d, model, info,
                          base_data(scad, extra, d, model, L, spec)):
                failed.append("%s_%s" % (part, L))
    print("\nResult: %d files, %d failed %s  (%.0f s)" % (total - len(failed), len(failed), " ".join(failed),
                                                       time.time() - t0))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
