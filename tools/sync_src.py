#!/usr/bin/env python3
"""
sync_src.py - Wordclock 16x16, copies the shared C++ files to the ESPHome folder, v2.0

The single source is arduino/Wordclock/src/*.h (Arduino needs the files inside the sketch folder).
ESPHome uses a copy in esphome/wordclock_multi/src/, so the folder esphome/ can be copied 1:1 to /config/esphome/.
Run after every change of a .h file (check_lang.py reports a copy that is out of date):
    python3 tools/sync_src.py
"""
import filecmp
import os
import shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "arduino", "Wordclock", "src")
DST = os.path.join(ROOT, "esphome", "wordclock_multi", "src")


def main():
    os.makedirs(DST, exist_ok=True)
    names = sorted(f for f in os.listdir(SRC) if f.endswith(".h"))
    for f in names:
        a, b = os.path.join(SRC, f), os.path.join(DST, f)
        if not os.path.isfile(b) or not filecmp.cmp(a, b, shallow=False):
            shutil.copy2(a, b)
            print("copied  %s" % f)
        else:
            print("same    %s" % f)
    for f in sorted(os.listdir(DST)):
        if f.endswith(".h") and f not in names:
            os.remove(os.path.join(DST, f))
            print("removed %s (no longer in arduino/Wordclock/src)" % f)


if __name__ == "__main__":
    main()
