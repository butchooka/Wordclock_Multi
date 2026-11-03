#!/usr/bin/env python3
"""
render_fronts.py - Wordclock 16x16, preview images of the front for every language, v2.0

Renders the front of each language as PNG with the same time and the same colour (lit letters exactly as the
clock shows them: the language file is compiled with the shared core, see tools/render_mask.cpp).
One image per language plus an overview with all languages, e.g. for MakerWorld or the README.

Needs: Python 3 with Pillow (pip install pillow). With g++ or clang++ the language files are compiled directly;
without a compiler the mask cache tools/render_masks.json.xz is used (built by tools/make_masks.py, contains every
minute of every language; a warning is printed if a language changed since). Windows: double-click
tools/render_fronts.bat.

Usage (from the repository root):
    python3 tools/render_fronts.py                         all languages, 10:22, warm white
    python3 tools/render_fronts.py DE GB --time 13:47 --color green
    python3 tools/render_fronts.py --color 00A0FF --features --style dark

Options:
    --time hh:mm      time shown (default 10:22, shows hour, minute words and the single minutes)
    --color C         palette name (warmwhite, white, red, orange, yellow, green, blue, violet) or hex RRGGBB
    --features        also light VENT, ALARM, battery bars and the temperature dots
    --style S         light = white front skin (FRONT_SKIN, default) | dark = dark front, letters open
    --size N          edge length of the single images in pixels (default 1600)
    --bg RRGGBB       background colour (default 1E1F22)
    --filler F        how the filler cells ("x" in the grid) are printed: auto (default, as FILLER = auto in the
                      models: default of the language from lang_XX.scad, else X), X, dot, or any other character
    --font FILE       TTF file (default: Liberation Sans Bold, else Arial Bold, else DejaVu Sans Bold). Languages
                      whose characters are not all in this font (JP, CN, KR, ...) automatically get a matching
                      font: own font of the language (lang_XX.scad), LANG_FONTS, FALLBACKS, then any installed font
                      (same idea as FONT_AUTO in the FreeCAD macro). The font used is printed per language.
    --out DIR         output folder (default docs/render)
Output: Wordclock_Render_v2.0_<LANG>_<hhmm>.png and Wordclock_Render_v2.0_ALL_<hhmm>.png
"""
import argparse
import bisect
import glob
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile

try:
    from PIL import Image, ImageDraw, ImageFilter, ImageFont, ImageChops
except ImportError:
    sys.exit("Pillow is missing: pip install pillow")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "arduino", "Wordclock", "src")
VERSION = "v2.0"

# geometry of the front in mm (Wordclock_Model.scad defaults)
PITCH = 10.0
CAP = 7.0
DOT_D = 3.0
STROKE_W, STROKE_H = 1.6, 6.0
FRONT = 160.0 + 2 * 0.3 + 2 * 2.0     # matrix + clearance + frame wall
CORNER_R = 4.0
FIT = PITCH - 1.2 - 0.4                # chamber (PITCH - GRID_WALL) minus LETTER_CLEARANCE

PALETTE = {"warmwhite": "FF8C28", "white": "FFFFFF", "red": "FF0000", "orange": "FF4600",
           "yellow": "FFBE00", "green": "00FF00", "blue": "0000FF", "violet": "9600FF"}

FONT_CANDIDATES = [
    "LiberationSans-Bold.ttf", "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf",
    "/usr/share/fonts/truetype/liberation2/LiberationSans-Bold.ttf",
    "C:/Windows/Fonts/arialbd.ttf", "/Library/Fonts/Arial Bold.ttf",
    "/System/Library/Fonts/Supplemental/Arial Bold.ttf",
    "DejaVuSans-Bold.ttf", "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
]
# preferred fonts of languages with their own script: "file" or "file#face index" (.ttc collections).
# Noto (Google Fonts, OFL), Yu Gothic / Microsoft YaHei / Malgun Gothic (Windows), Hiragino / PingFang (macOS).
LANG_FONTS = {
    "JP": ["NotoSansJP-Bold.ttf", "NotoSansCJKjp-Bold.otf", "NotoSansCJK-Bold.ttc#0", "YuGothB.ttc#0",
           "meiryob.ttc#0", "msgothic.ttc#0"],
    "CN": ["NotoSansSC-Bold.ttf", "NotoSansCJKsc-Bold.otf", "NotoSansCJK-Bold.ttc#2", "msyhbd.ttc#0",
           "simhei.ttf", "PingFang.ttc#0"],
    "KR": ["NotoSansKR-Bold.ttf", "NotoSansCJKkr-Bold.otf", "NotoSansCJK-Bold.ttc#1", "malgunbd.ttf",
           "AppleSDGothicNeo.ttc#0"],
    # runes (script variants scifi_RUNE_..): Segoe UI Historic (Windows 10/11), Noto Sans Runic, GNU FreeFont
    "SCIFI_RUNE_GB": ["seguihis.ttf", "NotoSansRunic-Regular.ttf", "FreeSerif.ttf", "FreeSans.ttf", "FreeMono.ttf", "seguisym.ttf"],
    "SCIFI_RUNE_DE": ["seguihis.ttf", "NotoSansRunic-Regular.ttf", "FreeSerif.ttf", "FreeSans.ttf", "FreeMono.ttf", "seguisym.ttf"],
}
FALLBACKS = ["LiberationSans-Bold.ttf", "arialbd.ttf", "DejaVuSans-Bold.ttf", "Arial Bold.ttf", "segoeuib.ttf",
             "NotoSans-Bold.ttf", "NotoSansCJK-Bold.ttc#0", "YuGothB.ttc#0", "msyhbd.ttc#0", "malgunbd.ttf"]


def hex_rgb(s):
    s = s.strip().lstrip("#")
    return tuple(int(s[i:i + 2], 16) for i in (0, 2, 4))


def find_font(path):
    for p in ([path] if path else []) + FONT_CANDIDATES:
        try:
            ImageFont.truetype(p, 20)
            return p
        except OSError:
            continue
    sys.exit("no font found, use --font path/to/font.ttf")


def font_dirs():
    home = os.path.expanduser("~")
    if os.name == "nt":
        return [os.path.join(os.environ.get("WINDIR", "C:\\Windows"), "Fonts"),
                os.path.join(os.environ.get("LOCALAPPDATA", ""), "Microsoft", "Windows", "Fonts")]
    if sys.platform == "darwin":
        return ["/Library/Fonts", "/System/Library/Fonts", os.path.join(home, "Library", "Fonts")]
    return ["/usr/share/fonts", "/usr/local/share/fonts", os.path.join(home, ".fonts"),
            os.path.join(home, ".local", "share", "fonts")]


_INDEX = {}


def font_index():
    if not _INDEX:
        for base in font_dirs():
            for root, _d, files in os.walk(base):
                for f in files:
                    if f.lower().endswith((".ttf", ".otf", ".ttc")):
                        _INDEX.setdefault(f.lower(), os.path.join(root, f))
        _INDEX.setdefault("", "")
    return _INDEX


def locate(spec):
    """'file' or 'file#index' -> (path, index) or None."""
    name, _h, idx = spec.partition("#")
    path = name if os.path.isfile(name) else font_index().get(os.path.basename(name).lower())
    return (path, int(idx or 0)) if path else None


def cmap_ranges(path, index=0):
    """Mapped code points of a font face as sorted ranges (cmap format 4/12, pure Python)."""
    with open(path, "rb") as f:
        head = f.read(16)
        off = 0
        if head[:4] == b"ttcf":
            f.seek(12 + 4 * index)
            off = struct.unpack(">I", f.read(4))[0]
        f.seek(off)
        num = struct.unpack(">H", f.read(12)[4:6])[0]
        tables = f.read(16 * num)
        d = None
        for i in range(num):
            tag, _c, toff, tlen = struct.unpack(">4sIII", tables[16 * i:16 * i + 16])
            if tag == b"cmap":
                f.seek(toff)
                d = f.read(tlen)
    subs = {}
    for i in range(struct.unpack(">H", d[2:4])[0]):
        pid, eid, o = struct.unpack(">HHI", d[4 + 8 * i:12 + 8 * i])
        subs.setdefault((struct.unpack(">H", d[o:o + 2])[0], pid, eid), o)
    for key in ((12, 3, 10), (12, 0, 6), (12, 0, 4), (4, 3, 1), (4, 0, 3), (4, 0, 4), (4, 0, 1), (4, 0, 0)):
        if key not in subs:
            continue
        o = subs[key]
        if key[0] == 12:
            n = struct.unpack(">I", d[o + 12:o + 16])[0]
            return sorted((a + (g == 0), b) for a, b, g in
                          (struct.unpack(">III", d[o + 16 + 12 * i:o + 28 + 12 * i]) for i in range(n)))
        seg2 = struct.unpack(">H", d[o + 6:o + 8])[0]
        n = seg2 // 2
        end = struct.unpack(">%dH" % n, d[o + 14:o + 14 + seg2])
        start = struct.unpack(">%dH" % n, d[o + 16 + seg2:o + 16 + 2 * seg2])
        delta = struct.unpack(">%dh" % n, d[o + 16 + 2 * seg2:o + 16 + 3 * seg2])
        rp = o + 16 + 3 * seg2
        ro = struct.unpack(">%dH" % n, d[rp:rp + seg2])
        out = []
        for i in range(n):
            for c in range(start[i], end[i] + 1):
                if c == 0xFFFF:
                    continue
                if ro[i]:
                    q = rp + 2 * i + ro[i] + 2 * (c - start[i])
                    g = struct.unpack(">H", d[q:q + 2])[0] if q + 2 <= len(d) else 0
                    g = (g + delta[i]) & 0xFFFF if g else 0
                else:
                    g = (c + delta[i]) & 0xFFFF
                if g:
                    if out and out[-1][1] == c - 1:
                        out[-1] = (out[-1][0], c)
                    else:
                        out.append((c, c))
        return out
    return []


_COV = {}


def missing(font, chars):
    """Characters of chars not contained in font (path, index). Unreadable font: everything missing."""
    if font not in _COV:
        try:
            r = cmap_ranges(*font)
        except Exception:
            r = []
        _COV[font] = (r, [a for a, _b in r])
    r, st = _COV[font]

    def has(cp):
        i = bisect.bisect_right(st, cp) - 1
        return i >= 0 and r[i][0] <= cp <= r[i][1]
    return "".join(c for c in chars if not has(ord(c)))


def grid_chars(grid, filler):
    out = []
    for row in grid:
        for ch in row:
            if ch == "x":
                ch = filler
            if len(ch) == 1 and ch not in " .*|·" and ch not in out:
                out.append(ch)
    return "".join(out)


def lang_font(lang, grid, filler, name, default):
    """Font (path, index) that contains every character of the grid and the language name; see --font."""
    chars = grid_chars(grid, filler) + "".join(c for c in name if not c.isspace())
    own = lang_field(lang, 19)
    specs = ([own] if own else []) + LANG_FONTS.get(lang.upper(), [])
    cands = [locate(sp) for sp in specs if not default[2]] + [default[:2]] + \
            ([locate(sp) for sp in specs] if default[2] else []) + [locate(sp) for sp in FALLBACKS]
    seen = []
    for c in cands:
        if c and c not in seen:
            seen.append(c)
            if not missing(c, chars):
                return c
    for p in sorted(set(v for v in font_index().values() if v)):
        if not missing((p, 0), chars):
            return (p, 0)
    print("  warning: no installed font contains all characters of %s (%s), using %s"
          % (lang, missing(default[:2], chars), os.path.basename(default[0])))
    return default[:2]


def languages():
    out = []
    for p in sorted(glob.glob(os.path.join(SRC, "wc_lang_*.h"))):
        out.append(re.match(r"wc_lang_(\w+)\.h", os.path.basename(p)).group(1))
    return out


def variants():
    """Script variants (front only, tools/make_variants.py): code -> base language (field 7 of lang_XX.scad)."""
    out = {}
    for p in sorted(glob.glob(os.path.join(ROOT, "models", "lang", "lang_*.scad"))):
        code = os.path.basename(p)[5:-5]
        if code != "all" and not os.path.isfile(os.path.join(SRC, "wc_lang_%s.h" % code)):
            base = lang_field(code, 21)
            if base:
                out[code] = base
    return out


def variant_grid(code):
    return [lang_field(code, 2 + r) for r in range(16)]


def lang_mask(lang, hhmm, color, features, cxx, tmp):
    exe = os.path.join(tmp, "render_mask_" + lang + (".exe" if os.name == "nt" else ""))
    r = subprocess.run([cxx, "-std=c++11", "-O1", "-DLANG=" + lang, os.path.join(ROOT, "tools", "render_mask.cpp"),
                        "-o", exe], capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stderr)
        sys.exit("compile error for " + lang)
    r = subprocess.run([exe, hhmm, color, "1" if features else "0"], capture_output=True)
    lines = r.stdout.decode("utf-8").splitlines()
    code, name, text = lines[0].split("\t")
    grid = lines[1:17]
    cols = [[hex_rgb(v) for v in l.split()] for l in lines[17:33]]
    return code, name, text, grid, cols


def lang_mask_cached(lang, hhmm, color, features, cache):
    """Same result as lang_mask(), but from tools/render_masks.json.xz (no compiler needed)."""
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import make_masks
    e = cache.get(lang)
    if not e:
        sys.exit("%s is not in tools/render_masks.json.xz - run tools/make_masks.py (needs g++) or install g++" % lang)
    if e["hash"] != make_masks.lang_hash(lang):
        print("WARNING %s: language file changed since the mask cache was built, lit words may be outdated "
              "(tools/make_masks.py)" % lang)
    h, m = (int(v) for v in hhmm.split(":"))
    t = (h % 24) * 60 + m % 60
    bits = int(e["masks"][t], 16)
    col = hex_rgb(color)
    off = (0, 0, 0)
    cols = [[col if bits >> (255 - (r * 16 + c)) & 1 else off for c in range(16)] for r in range(16)]
    if features:
        for k, v in e["extra"].items():
            i = int(k)
            cols[i // 16][i % 16] = col if v == "T" else hex_rgb(v)
    return e["code"], e["name"], e["texts"][t], e["grid"], cols


def lang_field(lang, i):
    """String number i of the entry in models/lang/lang_XX.scad (19 = FreeCAD font file, 20 = filler)."""
    try:
        with open(os.path.join(ROOT, "models", "lang", "lang_%s.scad" % lang), encoding="utf-8") as f:
            text = "\n".join(l for l in f.read().splitlines() if not l.lstrip().startswith("//"))
    except OSError:
        return ""
    m = re.search(r"LANG_\w+\s*=\s*\[(.*)\]\s*;", text, re.S)
    s = re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1)) if m else []
    return s[i] if len(s) > i else ""


def lang_filler(lang, filler):
    """FILLER = auto: field 6 of models/lang/lang_XX.scad (e.g. "dot"), otherwise "X"."""
    if filler != "auto":
        return filler
    return lang_field(lang, 20) or "X"


def rounded(draw, box, r, fill):
    draw.rounded_rectangle(box, radius=r, fill=fill)


def render(grid, cols, size, style, bg, font_spec, filler="X"):
    font_path, font_idx = font_spec
    s = size * 0.86 / FRONT                 # px per mm
    W = H = size
    x0 = (W - FRONT * s) / 2
    y0 = (H - FRONT * s) / 2
    gx = x0 + (FRONT - 16 * PITCH) / 2 * s  # top left of the grid
    gy = y0 + (FRONT - 16 * PITCH) / 2 * s

    if style == "dark":
        face, unlit = (38, 38, 41), (58, 58, 62)
    else:
        face, unlit = (232, 230, 226), (214, 211, 205)

    img = Image.new("RGB", (W, H), bg)
    # soft shadow
    sh = Image.new("L", (W, H), 0)
    ImageDraw.Draw(sh).rounded_rectangle([x0 + 0.8 * s, y0 + 2.0 * s, x0 + FRONT * s + 0.8 * s, y0 + FRONT * s + 2.0 * s],
                                         radius=CORNER_R * s, fill=150)
    sh = sh.filter(ImageFilter.GaussianBlur(4 * s))
    img.paste(Image.new("RGB", (W, H), (0, 0, 0)), (0, 0), sh)
    d = ImageDraw.Draw(img)
    rounded(d, [x0, y0, x0 + FRONT * s, y0 + FRONT * s], CORNER_R * s, face)

    # font size so that "H" has cap height CAP
    probe = ImageFont.truetype(font_path, 200, index=font_idx)
    hb = probe.getbbox("H", anchor="ls")
    fsize = 200 * CAP / ((hb[3] - hb[1]) / 1.0) * s / 1.0
    fsize = max(4, int(round(fsize)))
    font = ImageFont.truetype(font_path, fsize, index=font_idx)
    cap_px = CAP * s

    lit_layer = Image.new("RGB", (W, H), (0, 0, 0))
    ld = ImageDraw.Draw(lit_layer)
    core_layer = Image.new("RGB", (W, H), (0, 0, 0))
    cd = ImageDraw.Draw(core_layer)
    lit_mask = Image.new("L", (W, H), 0)
    md = ImageDraw.Draw(lit_mask)
    field = Image.new("RGB", (W, H), face)
    fd = ImageDraw.Draw(field)

    def shape(dr, ch, cx, cy, fill):
        if ch == "x":                       # filler cell, printed as FILLER (Wordclock_Model.scad)
            ch = filler
        if ch in ("", " ", ".", "·"):
            return
        if ch in ("*", "dot"):
            r = DOT_D / 2 * s
            dr.ellipse([cx - r, cy - r, cx + r, cy + r], fill=fill)
            return
        if ch == "|":
            dr.rectangle([cx - STROKE_W / 2 * s, cy - STROKE_H / 2 * s, cx + STROKE_W / 2 * s, cy + STROKE_H / 2 * s],
                         fill=fill)
            return
        # same fitting as glyph2d() in Wordclock_Model.scad: baseline at -CAP/2, too wide/high glyphs reduced
        # into the chamber (FIT), long descender: Q/J cut at the chamber edge, others reduced and pushed up
        fit = FIT * s
        bb = font.getbbox(ch, anchor="ls")          # relative to the baseline, y down
        w, top, bot = bb[2] - bb[0], -bb[1], bb[3]  # ink width, ascent, descent (px)
        h = top + bot
        k0 = min(1.0, fit / max(w, 1), (fit / 2 + cap_px / 2) / top if top > 0 else 1.0)
        centre = ch in "+"
        low = not centre and bot * k0 > (fit - cap_px) / 2
        cut = low and ch in "QJ"
        if low and not cut:
            k = min(k0, fit / max(h, 1))
        elif centre:
            k = min(1.0, fit / max(w, 1), fit / max(h, 1))
        else:
            k = k0
        f = font if abs(k - 1.0) < 1e-3 else ImageFont.truetype(font_path, max(4, int(round(fsize * k))), index=font_idx)
        bb = f.getbbox(ch, anchor="ls")
        ox = cx - (bb[0] + bb[2]) / 2
        if centre:
            oy = cy - (bb[1] + bb[3]) / 2
        elif low and not cut:
            oy = cy + fit / 2 - bb[3]               # bottom of the ink on the chamber edge
        else:
            oy = cy + cap_px / 2                    # common baseline
        if not cut:
            dr.text((ox, oy), ch, font=f, fill=fill, anchor="ls")
            return
        target = dr._image
        tmp = Image.new("L", target.size, 0)
        ImageDraw.Draw(tmp).text((ox, oy), ch, font=f, fill=255, anchor="ls")
        clip = Image.new("L", target.size, 0)
        ImageDraw.Draw(clip).rectangle([cx - fit / 2, cy - fit / 2, cx + fit / 2, cy + fit / 2], fill=255)
        target.paste(fill, (0, 0), ImageChops.multiply(tmp, clip))

    for r in range(16):
        row = list(grid[r])
        for c in range(16):
            ch = row[c] if c < len(row) else " "
            cx = gx + (c + 0.5) * PITCH * s
            cy = gy + (r + 0.5) * PITCH * s
            col = cols[r][c]
            if col == (0, 0, 0):
                shape(d, ch, cx, cy, unlit)
            else:
                shape(ld, ch, cx, cy, col)
                core = tuple(int(v + (255 - v) * 0.55) for v in col)
                shape(cd, ch, cx, cy, core)
                shape(md, ch, cx, cy, 255)
                e = 0.9 * PITCH * s
                fd.rectangle([cx - e, cy - e, cx + e, cy + e], fill=col)

    # glow: wide soft halo + tight bloom of the lit shapes, coloured by the cell colour
    halo = lit_mask.filter(ImageFilter.GaussianBlur(3.0 * s)).point(lambda v: min(255, int(v * 1.9)))
    bloom = lit_mask.filter(ImageFilter.GaussianBlur(0.8 * s)).point(lambda v: min(255, int(v * 0.9)))
    alpha = ImageChops.lighter(halo, bloom)
    face_mask = Image.new("L", (W, H), 0)
    ImageDraw.Draw(face_mask).rounded_rectangle([x0, y0, x0 + FRONT * s, y0 + FRONT * s], radius=CORNER_R * s, fill=255)
    alpha = ImageChops.multiply(alpha, face_mask)
    if style == "light":
        tint = Image.blend(img, field, 0.8)
    else:
        tint = field.point(lambda v: int(v * 0.8))
    img = Image.composite(tint, img, alpha)
    # letters: colour with a bright core
    img.paste(lit_layer, (0, 0), lit_mask)
    core_mask = lit_mask.filter(ImageFilter.MinFilter(3)).filter(ImageFilter.GaussianBlur(0.35 * s))
    img = Image.composite(core_layer, img, core_mask.point(lambda v: int(v * 0.8)))
    return img


def overview(images, cols_n, bg, tile, labels, fonts):
    rows_n = (len(images) + cols_n - 1) // cols_n
    pad = tile // 20
    lab = tile // 10
    W = cols_n * tile + (cols_n + 1) * pad
    H = rows_n * (tile + lab) + (rows_n + 1) * pad
    out = Image.new("RGB", (W, H), bg)
    d = ImageDraw.Draw(out)
    for i, im in enumerate(images):
        r, c = divmod(i, cols_n)
        x = pad + c * (tile + pad)
        y = pad + r * (tile + lab + pad)
        m = int(im.size[0] * 0.055)                    # crop most of the background around the front
        im = im.crop((m, m, im.size[0] - m, im.size[1] - m))
        out.paste(im.resize((tile, tile), Image.LANCZOS), (x, y))
        f = ImageFont.truetype(fonts[i][0], max(10, lab // 2), index=fonts[i][1])   # label in the font of the language
        d.text((x + tile / 2, y + tile + lab * 0.35), labels[i], font=f, fill=(200, 200, 205), anchor="mm")
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("langs", nargs="*")
    ap.add_argument("--time", default="10:22")
    ap.add_argument("--color", default="warmwhite")
    ap.add_argument("--features", action="store_true")
    ap.add_argument("--style", default="light", choices=["light", "dark"])
    ap.add_argument("--size", type=int, default=1600)
    ap.add_argument("--bg", default="1E1F22")
    ap.add_argument("--filler", default="auto")
    ap.add_argument("--font", default="")
    ap.add_argument("--out", default=os.path.join(ROOT, "docs", "render"))
    a = ap.parse_args()

    cxx = shutil.which("g++") or shutil.which("clang++")
    cache = None
    if not cxx:
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import make_masks
        cache = make_masks.load()
        if not cache:
            sys.exit("no g++/clang++ found and no mask cache tools/render_masks.json.xz")
        print("no g++/clang++: using the mask cache tools/render_masks.json.xz")
    color = PALETTE.get(a.color.lower(), a.color.lstrip("#"))
    hex_rgb(color)
    h, m = (int(v) for v in a.time.split(":"))
    hhmm = "%02d:%02d" % (h, m)
    default = (find_font(a.font), 0, bool(a.font))    # (path, face, given with --font)
    var = variants()
    known = {l.upper(): l for l in languages() + sorted(var)}   # case-insensitive, keeps the spelling (e.g. scifi_TLH)
    langs = [known.get(l.upper(), l) for l in a.langs] or languages() + sorted(var)
    os.makedirs(a.out, exist_ok=True)

    imgs, labels, fonts = [], [], []
    with tempfile.TemporaryDirectory() as tmp:
        for L in langs:
            B = var.get(L, L)                   # script variant: lit cells of the base language, own letters
            if cxx:
                code, name, text, grid, cols = lang_mask(B, hhmm, color, a.features, cxx, tmp)
            else:
                code, name, text, grid, cols = lang_mask_cached(B, hhmm, color, a.features, cache)
            if L in var:
                code, name, grid = L, lang_field(L, 1), variant_grid(L)
            filler = lang_filler(L, a.filler)
            font = lang_font(L, grid, filler, name, default)
            im = render(grid, cols, a.size, a.style, hex_rgb(a.bg), font, filler)
            fn = os.path.join(a.out, "Wordclock_Render_%s_%s_%02d%02d.png" % (VERSION, code, h, m))
            im.save(fn, optimize=True)
            print("%-6s %-13s %s  ->  %s  [%s%s]" % (code, name, text, os.path.relpath(fn, ROOT),
                                                   os.path.basename(font[0]), "#%d" % font[1] if font[1] else ""))
            imgs.append(im)
            labels.append(name)
            fonts.append(font)
    if len(imgs) > 1:
        n = len(imgs)
        cols_n = 4 if n > 6 else 3 if n > 4 else n
        ov = overview(imgs, cols_n, hex_rgb(a.bg), 800, labels, fonts)
        fn = os.path.join(a.out, "Wordclock_Render_%s_ALL_%02d%02d.png" % (VERSION, h, m))
        ov.save(fn, optimize=True)
        print("overview  ->  " + os.path.relpath(fn, ROOT))


if __name__ == "__main__":
    main()
