#!/usr/bin/env python3
"""
check_esphome.py - Wordclock 16x16, checks the ESPHome configuration of all languages, v1.0

Step 1 (always, Python only): every esphome/wordclock_multi/lang/lang_XX.yaml
  - is valid YAML (with line number on an error)
  - every substitution is a string: YAML 1.1 reads Off / No / Yes / On / NO (Norway) / true / null ... unquoted
    as bool or null, ESPHome then stops with "Must be string, got <class 'bool'>" without a line number
  - the options of a select are unique (colours incl. c_off, night modes)
  Uses PyYAML if installed (comes with ESPHome), otherwise a simple line check.
Step 2 (if ESPHome is installed, or with --esphome): "esphome config" for every language with a generated copy of
  esphome/wordclock_multi.yaml (language set, dummy secrets) in tools/logs/esphome_check/. Only validates, no compile.
  Full output per language: tools/logs/esphome_check/<code>.txt

    python3 tools/check_esphome.py [--log FILE] [--no-esphome] [--esphome] [CODE ...]
"""
import argparse
import glob
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ESP = os.path.join(ROOT, "esphome")
LANG_DIR = os.path.join(ESP, "wordclock_multi", "lang")
WORK = os.path.join(ROOT, "tools", "logs", "esphome_check")

# values YAML 1.1 does not read as a string when unquoted
YAML11_SPECIAL = re.compile(r"^(y|Y|yes|Yes|YES|n|N|no|No|NO|true|True|TRUE|false|False|FALSE|on|On|ON|off|Off|OFF"
                            r"|null|Null|NULL|~|)$")
# options of one select must be unique
UNIQUE = [["c_off", "c_0", "c_1", "c_2", "c_3", "c_4", "c_5", "c_6", "c_7", "c_random", "c_temp", "c_pride"],
          ["nm_mix", "nm_sun", "nm_fixed"]]
DUMMY_SECRETS = {"api_key": "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=", "ota_password": "check1234",
                 "wifi_ssid": "check", "wifi_password": "check1234", "ap_password": "check1234"}

out_lines = []


def say(s=""):
    print(s)
    out_lines.append(s)


def codes_all():
    return sorted(os.path.basename(p)[5:-5] for p in glob.glob(os.path.join(LANG_DIR, "lang_*.yaml")))


def subst_raw(text):
    """substitutions as (line number, key, raw value) - line based, without YAML library"""
    res, on = [], False
    for i, l in enumerate(text.splitlines(), 1):
        if l.startswith("substitutions:"):
            on = True
            continue
        if on and l and not l.startswith(" ") and not l.startswith("#"):
            break
        m = re.match(r"^  (\w+):\s?(.*)$", l)
        if on and m:
            res.append((i, m.group(1), m.group(2)))
    return res


def strip_comment(v):
    if v[:1] in "\"'":
        m = re.match(r"^(%s.*?%s)(\s+#.*)?\s*$" % (v[0], v[0]), v)
        return m.group(1) if m else v + "\x00"   # \x00: text after the closing quote
    return re.sub(r"\s+#.*$", "", v).strip()


def check_lang(code):
    p = os.path.join(LANG_DIR, "lang_%s.yaml" % code)
    text = open(p, encoding="utf-8").read()
    err = []
    raw = subst_raw(text)
    lines = {k: n for n, k, _ in raw}
    values = {}
    try:
        import yaml

        class Loader(yaml.SafeLoader):
            pass
        Loader.add_constructor("!include", lambda l, n: None)
        Loader.add_constructor("!secret", lambda l, n: None)
        try:
            data = yaml.load(text, Loader=Loader) or {}
        except yaml.YAMLError as e:
            mk = getattr(e, "problem_mark", None)
            err.append("YAML error%s: %s" % (" line %d" % (mk.line + 1) if mk else "", getattr(e, "problem", e)))
            return err
        for k, v in (data.get("substitutions") or {}).items():
            values[k] = v
            if not isinstance(v, str):
                err.append("line %s: %s is %s (%r), not a string - put the value in quotes"
                           % (lines.get(k, "?"), k, type(v).__name__, v))
    except ImportError:
        for n, k, v in raw:
            v = strip_comment(v)
            if v[:1] in "\"'":
                q = v[0]
                if v.endswith("\x00") or len(v) < 2:
                    err.append("line %d: %s starts with %s but has text after the closing quote" % (n, k, q))
                values[k] = v[1:-1]
            elif YAML11_SPECIAL.match(v):
                err.append("line %d: %s = %s is read as bool/null by YAML - put the value in quotes" % (n, k, v))
            else:
                values[k] = v
    for group in UNIQUE:
        seen = {}
        for k in group:
            if k in values:
                v = str(values[k]).strip().lower()
                if v in seen:
                    err.append("%s and %s have the same text '%s' (options of a select must be unique)"
                               % (seen[v], k, values[k]))
                seen[v] = k
    return err


def find_esphome():
    exe = shutil.which("esphome")
    if exe:
        return [exe]
    try:
        r = subprocess.run([sys.executable, "-m", "esphome", "version"], capture_output=True, text=True, timeout=60)
        if r.returncode == 0:
            return [sys.executable, "-m", "esphome"]
    except Exception:
        pass
    return None


def make_config(code):
    """copy of wordclock_multi.yaml with absolute paths, the language and dummy secrets"""
    main = open(os.path.join(ESP, "wordclock_multi.yaml"), encoding="utf-8").read()
    fw = lambda *p: os.path.join(ESP, *p).replace("\\", "/")
    main, n1 = re.subn(r"^(\s*lang:\s*)!include\s+\S+.*$", lambda m: m.group(1) + '!include "%s"'
                       % fw("wordclock_multi", "lang", "lang_%s.yaml" % code), main, count=1, flags=re.M)
    main, n2 = re.subn(r"^(\s*core:\s*)!include\s+\S+.*$", lambda m: m.group(1) + '!include "%s"'
                       % fw("wordclock_multi", "core.yaml"), main, count=1, flags=re.M)
    main, n3 = re.subn(r"^(\s*src_dir:\s*)\S+.*$", lambda m: m.group(1) + '"%s"' % fw("wordclock_multi", "src"),
                       main, count=1, flags=re.M)
    if not (n1 and n2 and n3):
        raise RuntimeError("wordclock_multi.yaml: lines lang/core/src_dir not found")
    main = re.sub(r"!secret\s+(\w+)", lambda m: '"%s"' % DUMMY_SECRETS.get(m.group(1), "check1234"), main)
    os.makedirs(WORK, exist_ok=True)
    p = os.path.join(WORK, "wc_%s.yaml" % code.lower().replace("_", "-"))
    with open(p, "w", encoding="utf-8", newline="\n") as f:
        f.write(main)
    return p


def esphome_config(cmd, code):
    p = make_config(code)
    env = dict(os.environ, PYTHONIOENCODING="utf-8")
    try:
        r = subprocess.run(cmd + ["config", p], capture_output=True, text=True, encoding="utf-8", errors="replace",
                           timeout=300, env=env, cwd=WORK)
    except subprocess.TimeoutExpired:
        return False, ["timeout"]
    full = (r.stdout or "") + (r.stderr or "")
    with open(os.path.join(WORK, "%s.txt" % code), "w", encoding="utf-8") as f:
        f.write(full)
    if r.returncode == 0:
        return True, []
    keys = ("ERROR", "Error", "Invalid", "Must be", "expected", "not a valid", "is not", "Failed", "Unable")
    msg = [l.rstrip() for l in full.splitlines() if any(k in l for k in keys)]
    return False, (msg or full.strip().splitlines()[-5:])[:12]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("codes", nargs="*")
    ap.add_argument("--log")
    ap.add_argument("--esphome", action="store_true", help="step 2 required (error if ESPHome is missing)")
    ap.add_argument("--no-esphome", action="store_true", help="only step 1")
    a = ap.parse_args()
    codes = a.codes or codes_all()
    bad = []

    say("Step 1: language packages (YAML, string values, unique options)")
    for c in codes:
        if not os.path.isfile(os.path.join(LANG_DIR, "lang_%s.yaml" % c)):
            say("  %-14s MISSING lang_%s.yaml" % (c, c))
            bad.append(c)
            continue
        err = check_lang(c)
        say("  %-14s %s" % (c, "ok" if not err else "ERROR"))
        for e in err:
            say("      " + e)
        if err:
            bad.append(c)

    if not a.no_esphome:
        say()
        cmd = find_esphome()
        if not cmd:
            say("Step 2: skipped - ESPHome not found (pip install esphome, then run again)")
            if a.esphome:
                bad.append("esphome")
        else:
            say("Step 2: esphome config (%s), output in tools/logs/esphome_check/" % " ".join(cmd))
            for c in codes:
                if c in bad:
                    say("  %-14s skipped (step 1)" % c)
                    continue
                ok, msg = esphome_config(cmd, c)
                say("  %-14s %s" % (c, "ok" if ok else "FAILED  (tools/logs/esphome_check/%s.txt)" % c))
                for m in msg:
                    say("      " + m)
                if not ok:
                    bad.append(c)
    say()
    say("ALL OK" if not bad else "ERRORS: %s" % " ".join(dict.fromkeys(bad)))
    if a.log:
        os.makedirs(os.path.dirname(os.path.abspath(a.log)), exist_ok=True)
        with open(a.log, "w", encoding="utf-8") as f:
            f.write("\n".join(out_lines) + "\n")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
