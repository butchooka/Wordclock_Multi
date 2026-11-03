#!/usr/bin/env python3
"""
check_lang.py - Wordclock 16x16, checks language files, v2.0

Usage (from the repository root):
    python3 tools/check_lang.py            all languages
    python3 tools/check_lang.py DE GB      only these
    python3 tools/check_lang.py DE --words also print the text of every word definition

Checks per language XX:
  - arduino/Wordclock/src/wc_lang_XX.h: 16 rows of 16 characters, layout contract (temperature dots, 10 bars)
  - the grid is identical in wc_lang_XX.h and models/lang/lang_XX.scad
  - every grid character has metrics in Wordclock_Model.scad (else OpenSCAD only centres it roughly),
    not checked for a language with its own font
  - every word {row, col, len} lies inside the grid (with --words: its text)
  - fillers: every cell that is never lit is "x" and every "x" is never lit (needs g++)
  - the INFO_DE / INFO_EN block (time grammar for docs/languages/LANG_XX.txt) is in the header of wc_lang_XX.h
  - ui_json is valid JSON and has exactly the keys of the reference (GB) and all keys used by webpage.html
  - esphome/wordclock_multi/lang/lang_XX.yaml has exactly the substitutions of the reference (GB)
  - models/lang/lang_all.scad and the LANG option of Wordclock_Model.scad list the language
  - the copy in esphome/wordclock_multi/src is identical (tools/sync_src.py)
  - arduino/Wordclock/webpage.h is the packed form of webpage.html (tools/make_webpage.py)
  - with g++ installed: compiles tools/preview.cpp for the language and checks that it runs
Script variants (front only, models/lang/lang_XX.scad with a base language in field 7, no firmware files,
see tools/make_variants.py): same layout as the base (fillers, dots, bars, +, digits at the same place), every
letter of the base always replaced by the same character, listed in lang_all.scad and in the LANG option.
Exit code 0 = everything OK.
"""
import json
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "arduino", "Wordclock", "src")
REF = "GB"


def read(p):
    with open(p, encoding="utf-8") as f:
        return f.read()


def h_grid(text):
    m = re.search(r"GRID\[16\]\s*=\s*\{(.*?)\};", text, re.S)
    return re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1)) if m else []


def strip_comments(text):
    """Removes // comments outside of strings."""
    out, i, n, ins = [], 0, len(text), False
    while i < n:
        ch = text[i]
        if ins:
            out.append(ch)
            if ch == "\\" and i + 1 < n:
                out.append(text[i + 1])
                i += 1
            elif ch == '"':
                ins = False
        elif ch == '"':
            ins = True
            out.append(ch)
        elif text.startswith("//", i):
            while i < n and text[i] != "\n":
                i += 1
            continue
        else:
            out.append(ch)
        i += 1
    return "".join(out)


def scad_grid(text):
    text = strip_comments(text)
    m = re.search(r"LANG_\w+\s*=\s*\[(.*)\]\s*;", text, re.S)
    text = m.group(1) if m else ""
    s = re.findall(r'"((?:[^"\\]|\\.)*)"', text)
    return s[2:18] if len(s) >= 18 else []


def scad_font(text):
    """OpenSCAD font of the language entry ("" = setting SCHRIFT)."""
    text = strip_comments(text)
    m = re.search(r"LANG_\w+\s*=\s*\[(.*)\]\s*;", text, re.S)
    s = re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1)) if m else []
    return s[18] if len(s) > 18 else ""


def scad_strings(text):
    text = strip_comments(text)
    m = re.search(r"LANG_\w+\s*=\s*\[(.*)\]\s*;", text, re.S)
    return re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1)) if m else []


def variants():
    """Codes of the script variants: lang_XX.scad with a base language (string 22) and no wc_lang_XX.h."""
    d = os.path.join(ROOT, "models", "lang")
    out = []
    if not os.path.isdir(d):
        return out
    for f in sorted(os.listdir(d)):
        if f.startswith("lang_") and f.endswith(".scad") and f != "lang_all.scad":
            code = f[5:-5]
            if not os.path.isfile(os.path.join(SRC, "wc_lang_%s.h" % code)):
                s = scad_strings(read(os.path.join(d, f)))
                if len(s) > 21 and s[21]:
                    out.append(code)
    return out


KEEP = set("x*|+.0123456789 ")


def check_variant(code):
    err = []
    sp = os.path.join(ROOT, "models", "lang", "lang_%s.scad" % code)
    if not os.path.isfile(sp):
        return ["missing file models/lang/lang_%s.scad" % code]
    s = scad_strings(read(sp))
    base = s[21] if len(s) > 21 else ""
    bp = os.path.join(ROOT, "models", "lang", "lang_%s.scad" % base)
    if not base or not os.path.isfile(bp) or not os.path.isfile(os.path.join(SRC, "wc_lang_%s.h" % base)):
        return ["base language '%s' (field 7) missing or without language files" % base]
    print("    script variant of %s, font %s / %s" % (base, s[18] or "(SCHRIFT)", s[19] or "(dialog)"))
    g, bg = s[2:18], scad_grid(read(bp))
    if len(g) != 16 or any(len(r) != 16 for r in g):
        return ["grid must have 16 rows of 16 characters"]
    table = {}
    for r in range(16):
        for c in range(16):
            a, b = bg[r][c], g[r][c]
            if a in KEEP or b in KEEP:
                if a != b:
                    err.append("row %d col %d: %s in the base must stay %s (is %s)" % (r + 1, c + 1, a, a, b))
            elif table.setdefault(a, b) != b:
                err.append("row %d col %d: %s is %s here but %s elsewhere" % (r + 1, c + 1, a, b, table[a]))
    if err:
        err.append("grid differs from the base %s: run python3 tools/make_variants.py" % base)
    la = read(os.path.join(ROOT, "models", "lang", "lang_all.scad"))
    if "lang_%s.scad" % code not in la or "LANG_%s" % code not in la.split("LANGS")[-1]:
        err.append("models/lang/lang_all.scad: include and LANGS entry for %s missing" % code)
    mp = os.path.join(ROOT, "models", "Wordclock_Model.scad")
    if os.path.isfile(mp):
        m = re.search(r'^LANG = "\w+"; // \[(.*)\]', read(mp), re.M)
        if not m or not re.search(r"(^|, )%s:" % re.escape(code), m.group(1)):
            err.append("Wordclock_Model.scad: option %s missing in LANG" % code)
    return err


def metric_chars():
    """Characters with metrics in both tables of Wordclock_Model.scad."""
    mp = os.path.join(ROOT, "models", "Wordclock_Model.scad")
    if not os.path.isfile(mp):          # software-only checkout (GitHub): no model, no metric check
        return None
    t = read(mp)
    out = None
    for name in ("METRIK_LIBERATION_BOLD", "METRIK_DEJAVU_BOLD"):
        m = re.search(name + r"\s*=\s*\[(.*?)\n\];", t, re.S)
        chars = set(re.findall(r'\["((?:[^"\\]|\\.))",\s*\[', m.group(1))) if m else set()
        out = chars if out is None else out & chars
    return out or set()


def h_ui(text):
    m = re.search(r'R"JSON\((.*?)\)JSON"', text, re.S)
    return json.loads(m.group(1)) if m else None


def h_words(text):
    """All {r, c, n} triples with a name: NAME = {r, c, n}, arrays and the WC_LANG status words."""
    out = []
    body = re.sub(r'R"JSON\(.*?\)JSON"', "", text, flags=re.S)
    for m in re.finditer(r"(\w+)(\[\d*\])?\s*=\s*\{((?:\s*\{\s*\d+\s*,\s*\d+\s*,\s*\d+\s*\}\s*,?)+)\s*\}", body):
        for i, t in enumerate(re.findall(r"\{\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\}", m.group(3))):
            out.append(("%s[%d]" % (m.group(1), i), tuple(map(int, t))))
    for m in re.finditer(r"(\w+)\s*=\s*\{\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\}", body):
        out.append((m.group(1), tuple(map(int, m.group(2, 3, 4)))))
    for m in re.finditer(r"^\s*\{\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\},\s*//\s*(.+)$", body, re.M):
        out.append(("WC_LANG " + m.group(4).strip(), tuple(map(int, m.group(1, 2, 3)))))
    return out


def yaml_keys(text):
    keys, on = [], False
    for l in text.splitlines():
        if l.startswith("substitutions:"):
            on = True
            continue
        if on and l and not l.startswith(" ") and not l.startswith("#"):
            break
        m = re.match(r"^  (\w+):", l)
        if on and m:
            keys.append(m.group(1))
    return keys


def web_keys():
    w = read(os.path.join(ROOT, "arduino", "Wordclock", "webpage.html"))
    keys = set(re.findall(r'data-t[hp]?="(\w+)"', w))
    keys |= set(re.findall(r"\bt\('(\w+)'", w))
    keys.discard("key")
    return keys


def check(code, words, ref_ui, ref_yaml):
    err = []
    hp = os.path.join(SRC, "wc_lang_%s.h" % code)
    sp = os.path.join(ROOT, "models", "lang", "lang_%s.scad" % code)
    yp = os.path.join(ROOT, "esphome", "wordclock_multi", "lang", "lang_%s.yaml" % code)
    for p in (hp, sp, yp):
        if not os.path.isfile(p):
            err.append("missing file %s" % os.path.relpath(p, ROOT))
    if err:
        return err
    h = read(hp)
    g = h_grid(h)
    if len(g) != 16:
        err.append("wc_lang_%s.h: %d grid rows instead of 16" % (code, len(g)))
        return err
    for i, r in enumerate(g):
        if len(r) != 16:
            err.append("grid row %d has %d characters: %s" % (i + 1, len(r), r))
    if err:
        return err
    for r in range(13):
        if g[r][0] != "*" or g[r][15] != "*":
            err.append("row %d: column 1 and 16 must be '*' (temperature dots)" % (r + 1))
    if g[15].count("|") != 10:
        err.append("row 16 needs 10 battery bars '|'")
    sg = scad_grid(read(sp))
    if sg != g:
        for i in range(16):
            a = g[i] if i < len(g) else "-"
            b = sg[i] if i < len(sg) else "-"
            if a != b:
                err.append("grid row %d differs: .h %s / .scad %s" % (i + 1, a, b))
    if not scad_font(read(sp)) and metric_chars() is not None:
        known = metric_chars() | set("*| .x")
        miss = sorted({ch for row in g for ch in row} - known)
        if miss:
            err.append("characters without metrics in Wordclock_Model.scad (OpenSCAD places them only roughly): %s"
                       % " ".join(miss))
    if not re.search(r"^\s*INFO_DE\b.*?^\s*INFO_EN\s*$.*?^\s*INFO_END\s*$", h, re.S | re.M):
        err.append("wc_lang_%s.h: INFO_DE / INFO_EN / INFO_END block missing in the header (see docs/LANG_SPEC.md)" % code)
    for name, (r, c, n) in h_words(h):
        if r > 15 or c + n > 16 or n == 0:
            err.append("word %s {%d, %d, %d} outside the grid" % (name, r, c, n))
        elif words:
            print("    %-26s {%2d,%2d,%2d}  %s" % (name, r, c, n, g[r][c:c + n]))
    try:
        ui = h_ui(h)
    except ValueError as e:
        ui = None
        err.append("ui_json is not valid JSON: %s" % e)
    if ui is not None:
        if ref_ui is not None:
            miss, extra = set(ref_ui) - set(ui), set(ui) - set(ref_ui)
            if miss:
                err.append("ui_json: missing keys %s" % ", ".join(sorted(miss)))
            if extra:
                err.append("ui_json: unknown keys %s" % ", ".join(sorted(extra)))
        need = {k for k in web_keys() if not k.startswith(("pal_", "nmh_", "wr_", "fx_", "g_"))}
        miss = need - set(ui)
        if miss:
            err.append("ui_json: keys used by webpage.html missing: %s" % ", ".join(sorted(miss)))
        for k in ("pal_%d" % i for i in range(8)):
            if k not in ui:
                err.append("ui_json: %s missing" % k)
    yk = yaml_keys(read(yp))
    if ref_yaml is not None:
        miss, extra = set(ref_yaml) - set(yk), set(yk) - set(ref_yaml)
        if miss:
            err.append("lang_%s.yaml: missing substitutions %s" % (code, ", ".join(sorted(miss))))
        if extra:
            err.append("lang_%s.yaml: unknown substitutions %s" % (code, ", ".join(sorted(extra))))
    if "wc_lang_%s.h" % code not in read(yp):
        err.append("lang_%s.yaml does not include wc_lang_%s.h" % (code, code))
    la = read(os.path.join(ROOT, "models", "lang", "lang_all.scad"))
    if "lang_%s.scad" % code not in la or "LANG_%s" % code not in la.split("LANGS")[-1]:
        err.append("models/lang/lang_all.scad: include and LANGS entry for %s missing" % code)
    mp = os.path.join(ROOT, "models", "Wordclock_Model.scad")
    if os.path.isfile(mp):
        m = re.search(r'^LANG = "\w+"; // \[(.*)\]', read(mp), re.M)
        if not m or not re.search(r"\b%s:" % code, m.group(1)):
            err.append("Wordclock_Model.scad: option %s missing in LANG" % code)
    # the default location must be in the location list of the web interface (else "custom location")
    w = read(os.path.join(ROOT, "arduino", "Wordclock", "webpage.html"))
    tzs = dict(re.findall(r"(\w+):'([^']+)'", re.search(r"const TZ=\{(.*?)\};", w, re.S).group(1)))
    locs = re.findall(r"\['([^']+)','(\w+)',(-?[\d.]+),(-?[\d.]+),'(\w+)'\]", w)
    m = re.search(r"(-?[\d.]+)f,\s*(-?[\d.]+)f,.*?\n\s*\"([^\"]+)\"", h)
    if not m:
        err.append("WC_LANG: lat/lon/posix_tz not found")
    else:
        la, lo, tz = float(m.group(1)), float(m.group(2)), m.group(3)
        if not any(abs(float(l[2]) - la) < 0.0011 and abs(float(l[3]) - lo) < 0.0011 and tzs.get(l[4]) == tz for l in locs):
            err.append("default location %.4f, %.4f / %s is not in LOC/TZ of webpage.html" % (la, lo, tz))
    # ESPHome copy of the C++ files must be up to date (tools/sync_src.py)
    for f in ("wc_core.h", "wc_effects.h", "wc_lang_%s.h" % code):
        b = os.path.join(ROOT, "esphome", "wordclock_multi", "src", f)
        if not os.path.isfile(b) or read(b) != read(os.path.join(SRC, f)):
            err.append("esphome/wordclock_multi/src/%s missing or out of date: run python3 tools/sync_src.py" % f)
    cxx = shutil.which("g++") or shutil.which("clang++")
    if cxx:
        exe = os.path.join(ROOT, "tools", "preview_%s%s" % (code, ".exe" if os.name == "nt" else ""))
        r = subprocess.run([cxx, "-std=c++11", "-Wall", "-DLANG=%s" % code, os.path.join(ROOT, "tools", "preview.cpp"),
                            "-o", exe], capture_output=True, text=True,
                           encoding="utf-8", errors="replace")
        if r.returncode:
            err.append("preview.cpp does not compile:\n" + r.stderr[-2000:])
        else:
            r = subprocess.run([exe], capture_output=True, text=True, encoding="utf-8", errors="replace")
            if r.returncode:
                err.append("preview reports errors:\n" + (r.stdout or "")[-1500:])
            r = subprocess.run([exe, "used"], capture_output=True, text=True, encoding="utf-8", errors="replace")
            used = (r.stdout or "").splitlines()[-16:]
            if len(used) == 16 and used != g:
                for i in range(16):
                    if used[i] != g[i]:
                        err.append("row %d: never lit cells must be 'x' (and 'x' never lit): is %s, should be %s"
                                   % (i + 1, g[i], used[i]))
            os.remove(exe)
    else:
        print("    (no g++ found, preview not compiled - Windows: winget install BrechtSanders.WinLibs.POSIX.UCRT)")
    return err


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    words = "--words" in sys.argv
    var = variants()
    codes = args or sorted(f[8:-2] for f in os.listdir(SRC) if f.startswith("wc_lang_") and f.endswith(".h")) + var
    ref_ui = h_ui(read(os.path.join(SRC, "wc_lang_%s.h" % REF)))
    ref_yaml = yaml_keys(read(os.path.join(ROOT, "esphome", "wordclock_multi", "lang", "lang_%s.yaml" % REF)))
    total = 0
    for code in codes:
        print("%s:" % code)
        errs = check_variant(code) if code in var else check(code, words, ref_ui, ref_yaml)
        for e in errs:
            print("  ERROR " + e)
        if not errs:
            print("  OK")
        total += len(errs)
    # webpage.h must be the packed form of webpage.html (tools/make_webpage.py)
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import make_webpage
    if not os.path.isfile(make_webpage.OUT) or read(make_webpage.OUT) != make_webpage.build()[0]:
        print("ERROR arduino/Wordclock/webpage.h is out of date: run python3 tools/make_webpage.py")
        total += 1
    sys.exit(1 if total else 0)


if __name__ == "__main__":
    main()
