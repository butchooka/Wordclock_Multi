#!/usr/bin/env python3
"""tools/check_params.py - Wordclock_Multi: parameter comparison OpenSCAD <-> FreeCAD macro.

Compares the settings of
    models/Wordclock_Model.scad              <-> models/Wordclock_Model.FCMacro
    models/Wordclock_Model_PictureFrame.scad <-> models/Wordclock_Model_PictureFrame.FCMacro
each including the shared part (models/Wordclock_Common.scad <-> models/Wordclock_Common.py),
without starting OpenSCAD or FreeCAD (text/AST analysis only).

Checked per parameter (top-level assignments with UPPERCASE names and a fixed value):
  ERROR  same name, different value
  ERROR  FCMacro value not in the option list of the SCAD Customizer (// [a, b, c])
  WARN   parameter only in one of the two files (known one-sided names: see ONLY_SCAD / ONLY_FC)
  WARN   customizable in one file, fine tuning / [Hidden] in the other
  WARN   customizable SCAD text or number without option list (// [a, b]) or slider (// [min:step:max])
Calculated values (expressions) are not compared.

Call: python tools/check_params.py [--log output/check_params_log.txt] [--verbose]
Exit code 1 if errors were found.
"""
import argparse
import ast
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
MODELS = ROOT / "models"
PAIRS = [("Wordclock_Model.scad", "Wordclock_Model.FCMacro"),
         ("Wordclock_Model_PictureFrame.scad", "Wordclock_Model_PictureFrame.FCMacro")]
# shared part, included by both files of a pair (parameters there count for every pair, all [Hidden] / fine tuning)
COMMON = ("Wordclock_Common.scad", "Wordclock_Common.py")

# Names that exist on one side only by design (reported as INFO instead of WARN); a trailing "*" = prefix
ONLY_SCAD = {
    "C_*": "preview colours",
    "METRICS_*": "font metrics (FreeCAD reads the font file)",
    "FONT": "font choice (FCMacro: FONT_FILE / FONT_CANDIDATES)",
    "FONT_CUSTOM*": "free font (FCMacro: FONT_FILE)",
    "PART": "part selection of the Customizer",
    "PRINT_ORIENT": "print orientation (FCMacro: EXPORT_PRINT_POSE)",
    "QUALITY": "rounding quality of OpenSCAD",
    "LAYOUT_GAP": "OpenSCAD view only",
}
ONLY_FC = {
    "EXPORT*": "export (FreeCAD only)",
    "FONT_*": "font search (FreeCAD only)",
    "WATERMARK_FONT_FILE": "font file (FreeCAD only)",
    "LANG_DIR": "path of the language files",
    "LANG_FONTS": "font files per language",
    "SKIPPED_LANGS": "runtime list, no setting",
    "SCREW_BORE_DIAMETERS": "table for SCREW_TYPE (SCAD: calculated)",
}
# Intended different values (reported as INFO instead of ERROR)
DIFF_OK = {
    "LANG": "FCMacro None = selection dialog",
}
# Additional option values allowed in the FCMacro only
ENUM_EXTRA_FC = {
    "LANG": ["ALL"],
}


def listed(name, table):
    for k, why in table.items():
        if name == k or (k.endswith("*") and name.startswith(k[:-1])):
            return why
    return None

NAME_RE = re.compile(r"^\s*([A-Z][A-Z0-9_]*)\s*=\s*(.+?)\s*$", re.S)
SECTION_RE = re.compile(r"/\*\s*\[(.+?)\]\s*\*/")
ENUM_RE = re.compile(r"^\s*//\s*\[(.*)\]\s*$")


# ------------------------------ OpenSCAD ------------------------------
def scad_to_py(expr):
    """OpenSCAD literal -> Python value, None if it is an expression."""
    parts = re.split(r'("(?:\\.|[^"\\])*")', expr)
    out = []
    for i, p in enumerate(parts):
        if i % 2 == 0:
            p = re.sub(r"\btrue\b", "True", p)
            p = re.sub(r"\bfalse\b", "False", p)
            p = re.sub(r"\bundef\b", "None", p)
        out.append(p)
    try:
        return ("lit", ast.literal_eval("".join(out)))
    except Exception:
        return ("expr", expr)


def parse_enum(body):
    items = [x.strip() for x in body.split(",")]
    if not items or any(re.fullmatch(r"-?[\d.]+(:-?[\d.]+){1,2}", x) for x in items):
        return "range"  # slider [min:step:max]
    vals = []
    for x in items:
        key = x.split(":", 1)[0].strip()
        try:
            vals.append(float(key))
        except ValueError:
            vals.append(key)
    return vals


def scad_params(path):
    text = path.read_text(encoding="utf-8")
    # include/use lines have no ";" - blank them (same line count), else the next assignment is not recognised
    text = re.sub(r"^[ \t]*(include|use)[ \t]*<[^>\n]*>.*$", "", text, flags=re.M)
    sections = [(m.start(), m.group(1).strip()) for m in SECTION_RE.finditer(text)]
    res = {}
    buf, start = [], None
    depth = {"{": 0, "(": 0, "[": 0}
    close = {"}": "{", ")": "(", "]": "["}
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
            continue
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            i = n if j < 0 else j + 2
            continue
        if c == '"':
            j = i + 1
            while j < n and text[j] != '"':
                j += 2 if text[j] == "\\" else 1
            if start is None:
                start = i
            buf.append(text[i:j + 1])
            i = j + 1
            continue
        if c in depth:
            depth[c] += 1
        elif c in close:
            depth[close[c]] -= 1
            if c == "}" and depth["{"] == 0:
                buf, start = [], None
                i += 1
                continue
        if c == ";" and not any(depth.values()):
            stmt = "".join(buf)
            m = NAME_RE.match(stmt)
            if m and start is not None:
                line = text.count("\n", 0, start) + 1
                eol = text.find("\n", i)
                tail = text[i + 1: n if eol < 0 else eol]
                em = ENUM_RE.match(tail)
                sec = ""
                for pos, name in sections:
                    if pos < start:
                        sec = name
                kind, val = scad_to_py(m.group(2))
                res[m.group(1)] = {"kind": kind, "val": val, "line": line,
                                   "custom": sec.lower() != "hidden" and sec != "",
                                   "enum": parse_enum(em.group(1)) if em else None}
            buf, start = [], None
            i += 1
            continue
        if not any(depth.values()) or depth["{"] == 0:
            if start is None and not c.isspace():
                start = i
            buf.append(c)
        i += 1
    return res


# ------------------------------ FreeCAD macro ------------------------------
def fc_params(path):
    text = path.read_text(encoding="utf-8")
    lines = text.splitlines()
    fine = next((k + 1 for k, l in enumerate(lines) if l.startswith("# FINE TUNING")), None)
    user = next((k + 1 for k, l in enumerate(lines) if l.startswith("# =====")), 0)
    tree = ast.parse(text)
    res = {}
    for node in tree.body:
        if not (isinstance(node, ast.Assign) and len(node.targets) == 1 and isinstance(node.targets[0], ast.Name)):
            continue
        name = node.targets[0].id
        if not re.fullmatch(r"[A-Z][A-Z0-9_]*", name):
            continue
        try:
            kind, val = "lit", ast.literal_eval(node.value)
        except Exception:
            kind, val = "expr", ast.get_source_segment(text, node.value)
        res[name] = {"kind": kind, "val": val, "line": node.lineno,
                     "custom": fine is not None and user < node.lineno < fine}
    return res


# ------------------------------ Compare ------------------------------
def norm(v):
    if isinstance(v, dict):
        return [[norm(k), norm(x)] for k, x in v.items()]
    if isinstance(v, (list, tuple)):
        return [norm(x) for x in v]
    return v


def equal(a, b):
    if isinstance(a, bool) or isinstance(b, bool):
        return isinstance(a, bool) and isinstance(b, bool) and a == b
    if isinstance(a, (int, float)) and isinstance(b, (int, float)):
        return abs(a - b) <= 1e-9 * max(1.0, abs(a), abs(b))
    if isinstance(a, list) and isinstance(b, list):
        return len(a) == len(b) and all(equal(x, y) for x, y in zip(a, b))
    return type(a) is type(b) and a == b


def fmt(v):
    s = repr(v)
    return s if len(s) <= 60 else s[:57] + "..."


def compare(scad_file, fc_file, out, verbose):
    sp = MODELS / scad_file
    fp = MODELS / fc_file
    if not sp.exists() or not fp.exists():
        out(f"  ERROR file missing: {scad_file if not sp.exists() else fc_file}")
        return 1, 0
    S, F = scad_params(sp), fc_params(fp)
    for common, parse, D in ((COMMON[0], scad_params, S), (COMMON[1], fc_params, F)):
        cp = MODELS / common
        if cp.exists():
            for name, v in parse(cp).items():
                v["custom"] = False                     # shared part = [Hidden] / fine tuning only
                v["line"] = f"{common}:{v['line']}"
                D.setdefault(name, v)
        else:
            out(f"  ERROR file missing: {common}")
            return 1, 0
    err = warn = same = expr = auto = 0
    for name in sorted(set(S) | set(F)):
        s, f = S.get(name), F.get(name)
        if (s and s["custom"] and s["kind"] == "lit" and s["enum"] is None
                and isinstance(s["val"], (str, int, float)) and not isinstance(s["val"], bool)):
            warn += 1
            out(f"  WARN   {name}: customizable without option list or slider (SCAD line {s['line']})")
        if s and f:
            if s["kind"] == "lit" and f["kind"] == "lit":
                if (f["val"] is None and isinstance(s["val"], (int, float)) and not isinstance(s["val"], bool)
                        and s["val"] < 0):
                    auto += 1  # convention: SCAD -1 / -999 = automatic = None in the macro
                    if verbose:
                        out(f"  ok     {name}: automatic (SCAD {s['val']}, FCMacro None)")
                elif equal(norm(s["val"]), norm(f["val"])):
                    same += 1
                    if verbose:
                        out(f"  ok     {name} = {fmt(s['val'])}")
                elif name in DIFF_OK:
                    if verbose:
                        out(f"  info   {name}: different on purpose ({DIFF_OK[name]})")
                else:
                    err += 1
                    out(f"  ERROR  {name}: SCAD {fmt(s['val'])} (line {s['line']})  <>  FCMacro {fmt(f['val'])} (line {f['line']})")
            else:
                expr += 1
            if isinstance(s["enum"], list) and f["kind"] == "lit" and f["val"] is not None and not isinstance(f["val"], bool):
                fv = float(f["val"]) if isinstance(f["val"], (int, float)) else f["val"]
                if fv not in s["enum"] + ENUM_EXTRA_FC.get(name, []):
                    err += 1
                    out(f"  ERROR  {name}: FCMacro value {fmt(f['val'])} not in the SCAD options {s['enum']}")
            if s["custom"] != f["custom"]:
                warn += 1
                where = lambda d: "customizable" if d["custom"] else "fine tuning"
                out(f"  WARN   {name}: SCAD {where(s)} (line {s['line']}), FCMacro {where(f)} (line {f['line']})")
        elif s and s["kind"] == "lit":
            if listed(name, ONLY_SCAD):
                if verbose:
                    out(f"  info   {name} only in SCAD ({listed(name, ONLY_SCAD)})")
            else:
                warn += 1
                out(f"  WARN   {name} only in SCAD (line {s['line']}) = {fmt(s['val'])}")
        elif f and f["kind"] == "lit":
            if listed(name, ONLY_FC):
                if verbose:
                    out(f"  info   {name} only in FCMacro ({listed(name, ONLY_FC)})")
            else:
                warn += 1
                out(f"  WARN   {name} only in FCMacro (line {f['line']}) = {fmt(f['val'])}")
    out(f"  -> {same} equal, {auto} automatic, {expr} calculated (not compared), {err} errors, {warn} warnings")
    return err, warn


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--log", help="also write the result to this file")
    ap.add_argument("--verbose", action="store_true", help="list equal parameters too")
    a = ap.parse_args()
    lines = []

    def out(s=""):
        print(s)
        lines.append(s)

    out("Wordclock_Multi - parameter comparison OpenSCAD <-> FreeCAD macro")
    errs = warns = 0
    for scad_file, fc_file in PAIRS:
        out("")
        out(f"{scad_file}  <->  {fc_file}")
        e, w = compare(scad_file, fc_file, out, a.verbose)
        errs += e
        warns += w
    out("")
    out("ALL OK" if errs == 0 and warns == 0 else f"RESULT: {errs} errors, {warns} warnings")
    if a.log:
        p = pathlib.Path(a.log)
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return 1 if errs else 0


if __name__ == "__main__":
    sys.exit(main())
