#!/usr/bin/env python3
"""
clean.py - Wordclock 16x16, removes caches and temporary files of the tools, v1.0

Removes (only generated files, never sources or results):
  - __pycache__ folders and *.pyc / *.pyo everywhere in the repository (also models/, tools/logs/, _private/)
  - leftovers of interrupted checks: tools/preview_*(.exe), tools/render_mask_*(.exe), *.o
  - FreeCAD / editor backups: *.FCBak, *.bak, *~ (models/, tools/)
  - ESPHome build cache tools/logs/esphome_check/.esphome (the logs <code>.txt stay)
  - temporary folders in %TEMP%: wc_firmware_build (sketch copy + build cache of build_firmware), wc_check_*
With --backup additionally the large generated outputs (slim folder for a manual backup, all can be rebuilt
with tools/wordclock_tools.bat), only files NOT tracked by git:
  - _private/makerworld/export/ (STL incl. custom/, menu 9, 10, 14, P), export_3mf/ (menu 12, 13),
    models/ (menu 8), *.zip (menu 6)
  - downloaded fonts tools/logs/fonts/*.otf (menu 15), tools/logs/claude/*.stl *.otf *.png
  - models/export/, output/, arduino/Wordclock/firmware/
  Kept: sources, logs *.txt, _private/ notes (todo.md, MakerWorld_Text.txt, README.txt), templates, everything in git.
Usage:  python3 tools/clean.py [--quiet] [--dry] [--backup]
Called automatically by tools/wordclock_tools.bat after every action (without --backup).
"""
import argparse
import glob
import os
import shutil
import stat
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SKIP = {".git"}


def targets():
    out = []
    for dp, dns, fns in os.walk(ROOT):
        dns[:] = [d for d in dns if d not in SKIP]
        for d in dns:
            if d == "__pycache__":
                out.append(os.path.join(dp, d))
        for f in fns:
            if f.endswith((".pyc", ".pyo")) and "__pycache__" not in dp:
                out.append(os.path.join(dp, f))
    for pat in ("tools/preview_*", "tools/render_mask_*", "tools/*.o", "models/*.FCBak", "models/*.bak",
                "models/lang/*.bak", "tools/*.bak", "tools/*~", "models/*~"):
        out += [p for p in glob.glob(os.path.join(ROOT, pat)) if not p.endswith((".cpp", ".py"))]
    out.append(os.path.join(ROOT, "tools", "logs", "esphome_check", ".esphome"))
    tmp = tempfile.gettempdir()
    out.append(os.path.join(tmp, "wc_firmware_build"))
    out += glob.glob(os.path.join(tmp, "wc_check_*"))
    return [p for p in out if os.path.exists(p)]


BACKUP_DIRS = ("_private/makerworld/export", "_private/makerworld/export_3mf", "_private/makerworld/models",
               "models/export", "output", "arduino/Wordclock/firmware")
BACKUP_GLOBS = ("_private/makerworld/*.zip", "tools/logs/fonts/*.otf", "tools/logs/fonts/*.ttf",
                "tools/logs/claude/*.stl", "tools/logs/claude/*.otf", "tools/logs/claude/*.ttf",
                "tools/logs/claude/*.png", "tools/logs/claude/*.3mf")


def git_tracked():
    """files tracked by git (normalised absolute paths); None if git is not available"""
    try:
        r = subprocess.run(["git", "-C", ROOT, "ls-files", "-z"], capture_output=True, timeout=60)
    except (OSError, subprocess.SubprocessError):
        return None
    if r.returncode != 0:
        return None
    return {os.path.normcase(os.path.normpath(os.path.join(ROOT, f)))
            for f in r.stdout.decode("utf-8", "replace").split("\0") if f}


def backup_targets():
    """large generated outputs; a folder that contains a git-tracked file is only cleaned file by file"""
    tracked = git_tracked()
    if tracked is None:
        print("note: git not found - only the fixed output folders are cleaned (they are all git-ignored)")
        tracked = set()
    out = []
    for d in BACKUP_DIRS:
        d = os.path.join(ROOT, d)
        if not os.path.isdir(d):
            continue
        key = os.path.normcase(os.path.normpath(d)) + os.sep
        if not any(t.startswith(key) for t in tracked):
            out.append(d)
            continue
        for dp, _, fns in os.walk(d):
            out += [os.path.join(dp, f) for f in fns
                    if os.path.normcase(os.path.normpath(os.path.join(dp, f))) not in tracked]
    for pat in BACKUP_GLOBS:
        out += [p for p in glob.glob(os.path.join(ROOT, pat))
                if os.path.isfile(p) and os.path.normcase(os.path.normpath(p)) not in tracked]
    return out


def _force(func, path, _exc):
    """rmtree helper: read-only files / folders (e.g. copied from OneDrive or git) are made writable and retried."""
    try:
        os.chmod(path, stat.S_IWRITE | stat.S_IREAD | stat.S_IEXEC)
        parent = os.path.dirname(path)
        os.chmod(parent, stat.S_IWRITE | stat.S_IREAD | stat.S_IEXEC)
    except OSError:
        pass
    func(path)


def remove(p):
    if os.path.isdir(p) and not os.path.islink(p):
        shutil.rmtree(p, onerror=_force)
    else:
        try:
            os.remove(p)
        except PermissionError:
            os.chmod(p, stat.S_IWRITE)
            os.remove(p)


def size(p):
    if os.path.isfile(p):
        return os.path.getsize(p)
    return sum(os.path.getsize(os.path.join(dp, f)) for dp, _, fns in os.walk(p) for f in fns
               if os.path.isfile(os.path.join(dp, f)))


def main():
    ap = argparse.ArgumentParser(description="Removes caches and temporary files of the Wordclock tools")
    ap.add_argument("--quiet", action="store_true", help="only a summary line")
    ap.add_argument("--dry", action="store_true", help="only list, delete nothing")
    ap.add_argument("--backup", action="store_true",
                    help="also remove large generated outputs (STL, 3MF, zips, fonts) for a slim backup")
    a = ap.parse_args()
    total, n = 0, 0
    items = targets() + (backup_targets() if a.backup else [])
    for p in items:
        s = size(p)
        if not a.quiet:
            print("%s %-70s %8.1f kB" % ("would remove" if a.dry else "removed", os.path.relpath(p, ROOT)
                                          if p.startswith(ROOT) else p, s / 1024))
        if not a.dry:
            try:
                remove(p)
            except OSError as e:
                print("  could not remove %s: %s" % (p, e))
                continue
        total += s
        n += 1
    print("clean: %d item(s), %.1f MB %s" % (n, total / 1048576, "to remove" if a.dry else "removed"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
