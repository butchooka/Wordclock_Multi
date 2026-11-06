#!/usr/bin/env python3
"""
install_fonts.py - Wordclock 16x16, checks the fonts the fronts need and installs missing ones, v1.0

Languages with their own script bring their font in models/lang/lang_XX.scad (CN, JP, KR: Noto Sans SC/JP/KR Bold,
runes: Segoe UI Historic, part of Windows 10/11). OpenSCAD only sees fonts installed for all users (Windows:
the system font folder), without them the letters become empty boxes.
Missing Noto fonts are downloaded (static Bold OTF from github.com/notofonts/noto-cjk, SIL Open Font License)
to tools/logs/fonts/ and installed for all users - Windows asks once for administrator rights (UAC).
Other systems: copied to ~/.fonts (+ fc-cache). The FreeCAD macro finds the same files (LANG_FONTS).

Call:  python tools/install_fonts.py [--check] [--font Liberation|Arial|DejaVu]
       (or tools/wordclock_tools.bat, item 15)
"""
import argparse
import ctypes
import os
import shutil
import subprocess
import sys
import urllib.request

TOOLS = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(TOOLS)
sys.path.insert(0, TOOLS)
import export_fronts as ef  # noqa: E402

DL_DIR = os.path.join(TOOLS, "logs", "fonts")
CJK = "https://github.com/notofonts/noto-cjk/raw/main/Sans/SubsetOTF/%s/NotoSans%s-Bold.otf"
# font family -> (download URL, file name); fonts not listed here have to be installed by hand
SOURCES = {
    "noto sans kr": (CJK % ("KR", "KR"), "NotoSansKR-Bold.otf"),
    "noto sans jp": (CJK % ("JP", "JP"), "NotoSansJP-Bold.otf"),
    "noto sans sc": (CJK % ("SC", "SC"), "NotoSansSC-Bold.otf"),
}


def needed(font):
    """{OpenSCAD font name: [languages]} for all languages."""
    res = {}
    for L in ef.all_langs():
        res.setdefault(ef.font_for(L, font)[0], []).append(L)
    return res


def missing(font):
    """[(family, style, languages)] that OpenSCAD would not find."""
    scad = ef.find_openscad(None)
    found = ef._scan(ef.font_dirs(scad)[0])
    res = []
    for spec, langs in sorted(needed(font).items()):
        if spec.startswith("Liberation Sans"):
            continue                                  # comes with OpenSCAD
        fam, _, rest = spec.partition(":")
        style = rest.split("=", 1)[1].lower() if "=" in rest else ""
        faces = found.get(fam.strip().lower(), [])
        if not faces or (style and not any(st == style for st, _ in faces)):
            res.append((fam.strip(), style, langs))
    return res


def is_admin():
    try:
        return bool(ctypes.windll.shell32.IsUserAnAdmin())
    except Exception:
        return False


def install_windows(files):
    """Copies the files into the system font folder and registers them (HKLM), elevated via UAC if needed."""
    ps = os.path.join(DL_DIR, "install_fonts.ps1")
    lines = ['$ErrorActionPreference = "Stop"',
             '$key = "HKLM:\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts"']
    for path, family in files:
        fn = os.path.basename(path)
        kind = "OpenType" if fn.lower().endswith(".otf") else "TrueType"
        lines += ['Copy-Item -LiteralPath "%s" -Destination "$env:WINDIR\\Fonts\\%s" -Force' % (path, fn),
                  'New-ItemProperty -Path $key -Name "%s Bold (%s)" -Value "%s" -PropertyType String -Force | Out-Null'
                  % (family, kind, fn)]
    lines.append('"installed: %d font(s)" | Out-File -Encoding utf8 "%s"' % (len(files), ps + ".done"))
    with open(ps, "w", encoding="utf-8-sig") as f:
        f.write("\r\n".join(lines) + "\r\n")
    if os.path.isfile(ps + ".done"):
        os.remove(ps + ".done")
    if is_admin():
        cmd = ["powershell", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", ps]
    else:
        print("Windows asks for administrator rights (fonts for all users) ...")
        cmd = ["powershell", "-NoProfile", "-Command",
               "Start-Process powershell -Verb RunAs -Wait -ArgumentList '-NoProfile','-ExecutionPolicy','Bypass',"
               "'-File','\"%s\"'" % ps]
    subprocess.run(cmd)
    return os.path.isfile(ps + ".done")


def install_other(files):
    dst = os.path.join(os.path.expanduser("~"), ".fonts")
    os.makedirs(dst, exist_ok=True)
    for path, _fam in files:
        shutil.copy(path, dst)
    if shutil.which("fc-cache"):
        subprocess.run(["fc-cache", "-f", dst])
    return True


def main():
    ap = argparse.ArgumentParser(description="Checks and installs the fonts of the Wordclock fronts")
    ap.add_argument("--check", action="store_true", help="only check, install nothing")
    ap.add_argument("--font", default="Liberation", help="font setting of the model (FONT)")
    a = ap.parse_args()
    if not os.path.isdir(os.path.join(ef.MODELS, "lang")):
        print("models/lang not found.")
        return 1
    print("Fonts of the fronts (FONT = %s):" % a.font)
    for spec, langs in sorted(needed(a.font).items()):
        print("  %-28s %s" % (spec, " ".join(langs)))
    miss = missing(a.font)
    if not miss:
        print("\nResult: all fonts found - nothing to do.")
        return 0
    print("\nMissing for OpenSCAD:")
    for fam, style, langs in miss:
        print("  %s%s  (%s)" % (fam, " " + style if style else "", " ".join(langs)))
    if a.check:
        print("\nResult: %d font(s) missing - run without --check to install them." % len(miss))
        return 1

    os.makedirs(DL_DIR, exist_ok=True)
    files, manual = [], []
    for fam, _style, _langs in miss:
        src = SOURCES.get(fam.lower())
        if not src:
            manual.append(fam)
            continue
        url, fn = src
        path = os.path.join(DL_DIR, fn)
        print("Download %s ... " % fn, end="", flush=True)
        try:
            with urllib.request.urlopen(url, timeout=120) as r, open(path + ".part", "wb") as f:
                shutil.copyfileobj(r, f)
            os.replace(path + ".part", path)
        except Exception as e:                        # noqa: BLE001
            print("FAILED (%s)" % e)
            manual.append(fam)
            continue
        if not any(f_.lower() == fam.lower() for f_, _ in ef._font_names(path)):
            print("FAILED (not the font %s)" % fam)
            manual.append(fam)
            continue
        print("ok (%.1f MB)" % (os.path.getsize(path) / 1e6))
        files.append((path, fam))
    if files:
        ok = install_windows(files) if os.name == "nt" else install_other(files)
        print("Install: %s" % ("ok" if ok else "NOT done (administrator rights refused?)"))
    rest = missing(a.font)
    print()
    if rest:
        for fam, style, langs in rest:
            print("ERROR still missing: %s%s (%s) - install it by hand for all users" %
                  (fam, " " + style if style else "", " ".join(langs)))
        print("Result: %d font(s) missing" % len(rest))
        return 1
    print("Result: all fonts installed and found.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
