#!/usr/bin/env python3
"""tools/bundle_models.py - Wordclock_Multi: single-file versions of the models (e.g. for MakerWorld), v2.0

The models share code: Wordclock_Common.scad (OpenSCAD) and Wordclock_Common.py (FreeCAD macros), plus the
language grids in models/lang/. For an upload that needs ONE file this script inserts everything:

  OpenSCAD:  every line  include <file>  is replaced by the content of the file (recursive, relative to the
             including file, every file only once) -> Wordclock_Model.scad / Wordclock_Model_PictureFrame.scad
             without any include (all languages inside, Customizer parameters unchanged at the top).
  FreeCAD:   the block "# >>> include Wordclock_Common.py" ... "# <<< include" is replaced by the content of
             Wordclock_Common.py. Note: the macro still reads the language grids from a folder "lang" next to it.

Output: models/export/bundle/ (same file names). No OpenSCAD / FreeCAD needed, takes about a second.
Call:  python tools/bundle_models.py [--out DIR]     (or double-click tools/bundle_models.bat)
Exit code 1 on an error (missing include file, "use <...>", include left in the result).
"""
import argparse
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
MODELS = ROOT / "models"
SCAD_FILES = ["Wordclock_Model.scad", "Wordclock_Model_PictureFrame.scad"]
MACRO_FILES = ["Wordclock_Model.FCMacro", "Wordclock_Model_PictureFrame.FCMacro"]

INCLUDE_RE = re.compile(r"^\s*include\s*<([^>]+)>\s*;?\s*(//.*)?$")
USE_RE = re.compile(r"^\s*use\s*<([^>]+)>")
FC_BEGIN_RE = re.compile(r"^# >>> include (\S+)")
FC_END_RE = re.compile(r"^# <<< include")


def read(p):
    return p.read_text(encoding="utf-8")


def bundle_scad(path, seen=None, depth=0):
    """Text of path with all include <...> inserted (each file once)."""
    if seen is None:
        seen = set()
    seen.add(path.resolve())
    out = []
    for no, line in enumerate(read(path).splitlines(), 1):
        if USE_RE.match(line):
            raise ValueError("%s line %d: 'use <...>' is not supported (use include)" % (path.name, no))
        m = INCLUDE_RE.match(line)
        if not m:
            out.append(line)
            continue
        inc = (path.parent / m.group(1).strip()).resolve()
        rel = inc.relative_to(MODELS) if MODELS in inc.parents else inc.name
        if inc in seen:
            out.append("// (already included above: %s)" % rel)
            continue
        if not inc.is_file():
            raise FileNotFoundError("%s line %d: include file %s not found" % (path.name, no, inc))
        out.append("// ===== begin include <%s> =====" % str(rel).replace("\\", "/"))
        out.extend(bundle_scad(inc, seen, depth + 1).splitlines())
        out.append("// ===== end include <%s> =====" % str(rel).replace("\\", "/"))
    return "\n".join(out) + "\n"


def bundle_macro(path):
    """Macro text with the marked include block replaced by the shared file."""
    out, skip, n = [], False, 0
    for no, line in enumerate(read(path).splitlines(), 1):
        if skip:
            if FC_END_RE.match(line):
                skip = False
            continue
        m = FC_BEGIN_RE.match(line)
        if m:
            inc = path.parent / m.group(1)
            if not inc.is_file():
                raise FileNotFoundError("%s line %d: %s not found" % (path.name, no, inc))
            out.append("# ===== begin %s (inserted by tools/bundle_models.py) =====" % m.group(1))
            out.extend(read(inc).splitlines())
            out.append("# ===== end %s =====" % m.group(1))
            skip, n = True, n + 1
            continue
        out.append(line)
    if skip:
        raise ValueError("%s: '# <<< include' missing" % path.name)
    if n == 0:
        raise ValueError("%s: no '# >>> include' block found" % path.name)
    return "\n".join(out) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", default=str(MODELS / "export" / "bundle"), help="target folder")
    a = ap.parse_args()
    out_dir = pathlib.Path(a.out)
    out_dir.mkdir(parents=True, exist_ok=True)
    errors = 0
    for name in SCAD_FILES + MACRO_FILES:
        src = MODELS / name
        if not src.is_file():
            print("ERROR  %s missing" % name)
            errors += 1
            continue
        try:
            if name.endswith(".scad"):
                text = bundle_scad(src)
                left = [l for l in text.splitlines() if INCLUDE_RE.match(l) or USE_RE.match(l)]
            else:
                text = bundle_macro(src)
                compile(text, name, "exec")                  # syntax check of the joined macro
                left = [l for l in text.splitlines() if FC_BEGIN_RE.match(l) or "_common_file(" in l]
            if left:
                raise ValueError("include left in the result: %s" % left[0].strip())
        except (ValueError, FileNotFoundError, SyntaxError) as e:
            print("ERROR  %s: %s" % (name, e))
            errors += 1
            continue
        dst = out_dir / name
        dst.write_text(text, encoding="utf-8", newline="\n")
        print("ok     %-40s %6d lines, %4d kB" % (name, text.count("\n"), (len(text.encode("utf-8")) + 512) // 1024))
    print("")
    print("Output: %s" % out_dir)
    print("ALL OK" if not errors else "RESULT: %d errors" % errors)
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
