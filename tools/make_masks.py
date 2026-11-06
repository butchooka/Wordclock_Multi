#!/usr/bin/env python3
"""
make_masks.py - Wordclock 16x16, mask cache for render_fronts.py, v1.0

Compiles every language once (tools/render_mask.cpp, needs g++ or clang++) and stores the lit cells of all
1440 minutes, the time texts and the additional displays in tools/render_masks.json.xz (approx. 40 KB).
With this file tools/render_fronts.py runs WITHOUT a compiler (only Python 3 + Pillow), e.g. on Windows.
Every entry carries a checksum of wc_core.h + wc_lang_XX.h; render_fronts.py warns if a language changed since.
Run after a change of a language or of wc_core.h (tools/make_info.py does it automatically when g++ is there):
    python3 tools/make_masks.py
"""
import hashlib
import json
import lzma
import os
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "arduino", "Wordclock", "src")
OUT = os.path.join(ROOT, "tools", "render_masks.json.xz")


def lang_hash(code):
    h = hashlib.sha1()
    for f in ("wc_core.h", "wc_lang_%s.h" % code):
        with open(os.path.join(SRC, f), "rb") as fh:
            h.update(fh.read().replace(b"\r\n", b"\n"))   # same checksum with Windows line ends
    return h.hexdigest()[:16]


def languages():
    return sorted(f[8:-2] for f in os.listdir(SRC) if f.startswith("wc_lang_") and f.endswith(".h"))


def dump(code, cxx, tmp):
    exe = os.path.join(tmp, "rm_" + code + (".exe" if os.name == "nt" else ""))
    r = subprocess.run([cxx, "-std=c++11", "-O1", "-DLANG=" + code, os.path.join(ROOT, "tools", "render_mask.cpp"),
                        "-o", exe], capture_output=True, text=True)
    if r.returncode:
        raise RuntimeError(r.stderr[-1500:])
    lines = subprocess.run([exe, "all"], capture_output=True).stdout.decode("utf-8").split("\n")
    c, name = lines[0].split("\t")
    grid = lines[1:17]
    masks, texts = [], []
    for l in lines[17:17 + 1440]:
        m, t = l.split("\t")
        masks.append(m)
        texts.append(t)
    extra = {}
    for item in lines[17 + 1440].split():
        k, v = item.split("=")
        extra[k] = v
    return {"code": c, "name": name, "hash": lang_hash(code), "grid": grid, "masks": masks, "texts": texts,
            "extra": extra}


def load():
    """Mask cache as dict code -> entry, {} if missing."""
    if not os.path.isfile(OUT):
        return {}
    with lzma.open(OUT, "rt", encoding="utf-8") as f:
        return json.load(f)


def main():
    cxx = shutil.which("g++") or shutil.which("clang++")
    if not cxx:
        sys.exit("no g++/clang++ found: the mask cache can only be built with a compiler")
    data = {}
    with tempfile.TemporaryDirectory() as tmp:
        for code in languages():
            data[code] = dump(code, cxx, tmp)
    text = json.dumps(data, ensure_ascii=False, separators=(",", ":"), sort_keys=True)
    old = None
    if os.path.isfile(OUT):
        with lzma.open(OUT, "rt", encoding="utf-8") as f:
            old = f.read()
    if old == text:
        print("unchanged tools/render_masks.json.xz")
        return
    with lzma.open(OUT, "wt", encoding="utf-8", preset=9) as f:
        f.write(text)
    print("written   tools/render_masks.json.xz (%d languages, %d bytes)" % (len(data), os.path.getsize(OUT)))


if __name__ == "__main__":
    main()
