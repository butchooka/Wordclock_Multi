#!/usr/bin/env python3
"""
wc_stamp.py - Wordclock 16x16, skip outputs whose inputs did not change, v1.0

Every tool that builds slow outputs (export_fronts.py, make_3mf.py, render_fronts.py) writes an info
file next to its outputs with the base data of every output: the input files (SHA-256 of the content + date of the
file), the parameters and the program versions (OpenSCAD, Pillow, fonts ...). In the next run an output is
only built again when one of these changed or the output file is missing / has another size.
The content and not the date decides (git checkout, OneDrive and tools that rewrite a file with the same content
change the date only); the date is in the info file for information.

Info files: _private/makerworld/export/export_info.json (custom/ has its own),
            _private/makerworld/export_3mf/3mf_info.json, docs/render*/render_info.json
Build everything again: option --force of the tools, or the environment variable WC_FORCE=1
(wordclock_tools.bat: second argument F, e.g. "wordclock_tools.bat A F").
"""
import hashlib
import json
import os
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_HASH = {}


def file_hash(path):
    """SHA-256 (first 16 hex digits) of the content; cached per run by path, size and date."""
    st = os.stat(path)
    k = (os.path.normcase(os.path.abspath(path)), st.st_size, st.st_mtime_ns)
    if k not in _HASH:
        h = hashlib.sha256()
        with open(path, "rb") as f:
            for b in iter(lambda: f.read(1 << 20), b""):
                h.update(b)
        _HASH[k] = h.hexdigest()[:16]
    return _HASH[k]


def text_hash(text):
    return hashlib.sha256(text.encode("utf-8")).hexdigest()[:16]


def rel(path):
    p = os.path.abspath(path)
    try:
        r = os.path.relpath(p, ROOT)
    except ValueError:                                # other drive (Windows)
        return p.replace("\\", "/")
    return p.replace("\\", "/") if r.startswith("..") else r.replace("\\", "/")


def inputs(files, **params):
    """Base data of one output: {"files": {path: {"sha256", "date"}}, "params": {...}}. Missing files count as such."""
    fl = {}
    for p in sorted(set(files), key=lambda x: rel(x)):
        if os.path.isfile(p):
            fl[rel(p)] = {"sha256": file_hash(p),
                          "date": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(os.path.getmtime(p)))}
        else:
            fl[rel(p)] = {"sha256": "missing", "date": ""}
    return {"files": fl, "params": params}


def key(inp):
    """Fingerprint of the base data - without the file dates (they do not change the result)."""
    data = {"files": {k: v["sha256"] for k, v in inp["files"].items()}, "params": inp["params"]}
    return hashlib.sha256(json.dumps(data, sort_keys=True, ensure_ascii=False).encode("utf-8")).hexdigest()[:16]


class Info:
    """Info file of one output folder. fresh() = output can be kept, store() after a successful build."""

    def __init__(self, path, force=False):
        self.path = path
        self.force = force or os.environ.get("WC_FORCE", "") not in ("", "0")
        try:
            with open(path, encoding="utf-8") as f:
                self.data = json.load(f)
        except (OSError, ValueError):
            self.data = {}
        self.data.setdefault("outputs", {})

    def fresh(self, out, inp, extra_outputs=(), virtual=False):
        """virtual: out is only a name (e.g. one render run), the files to check are extra_outputs"""
        if self.force:
            return False
        e = self.data["outputs"].get(os.path.basename(out))
        if not e or e.get("key") != key(inp):
            return False
        for o, size in ([] if virtual else [(out, e.get("size"))]) + [(p, None) for p in extra_outputs]:
            if not os.path.isfile(o) or (size is not None and os.path.getsize(o) != size):
                return False
        return True

    def store(self, out, inp, **more):
        e = {"key": key(inp), "built": time.strftime("%Y-%m-%d %H:%M:%S"),
             "size": os.path.getsize(out) if os.path.isfile(out) else None}
        e.update(more)
        e.update(inp)
        self.data["outputs"][os.path.basename(out)] = e
        self.save()

    def drop_missing(self, folder):
        """Removes entries whose output file no longer exists (e.g. after a version change)."""
        for n in [n for n in self.data["outputs"] if not os.path.isfile(os.path.join(folder, n))]:
            del self.data["outputs"][n]

    def save(self):
        self.data["note"] = ("written by the Wordclock tools (tools/wc_stamp.py): base data of every output, "
                             "an output is only built again when they change")
        os.makedirs(os.path.dirname(self.path), exist_ok=True)
        tmp = self.path + ".tmp"
        with open(tmp, "w", encoding="utf-8", newline="\n") as f:
            json.dump(self.data, f, indent=1, sort_keys=True, ensure_ascii=False)
            f.write("\n")
        os.replace(tmp, self.path)
