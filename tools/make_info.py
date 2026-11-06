#!/usr/bin/env python3
"""
make_info.py - Wordclock 16x16, writes docs/languages, docs/setup and the setup READMEs, v1.0

Generates (never edit these files by hand, they are overwritten):
  docs/languages/LANG_XX.txt  per language (German + English): data, grid, time grammar, all 5-minute steps,
                              special times and example times as lit grid
  arduino/README.md, arduino/README_DE.md    setup guide Arduino (English / German, Markdown)
  esphome/README.md, esphome/README_DE.md    setup guide ESPHome
  docs/setup/SETUP_<part>_EN.md / _DE.md     setup guides FreeCAD and OpenSCAD (models/ is private)
  docs/languages/LANGUAGES.txt  overview of all languages (available and planned)
and updates the language list in the comments of arduino/Wordclock/config.h and esphome/wordclock_multi.yaml
and the language table in README.md / README_DE.md (between the lines "LANGUAGES BEGIN" and "LANGUAGES END").
Order everywhere: languages of countries (DE and GB first), then dialects, then other languages.
Sources: arduino/Wordclock/src/wc_lang_XX.h (grid, defaults, INFO_DE/INFO_EN block in the header),
esphome/wordclock_multi/lang/lang_XX.yaml, models/lang/lang_XX.scad. Every language found there is listed
automatically, a new language needs no change in this script (only the PLANNED list below for the overview).

Usage (from the repository root):  python3 tools/make_info.py
The language files (time phrases, example grids) need g++ or clang++ (compiles tools/preview.cpp). Without a
compiler only the setup guides and LANGUAGES.txt are written, the existing LANG_XX.txt stay unchanged.
"""
import os
import re
import shutil
import subprocess
import sys
import tempfile
import textwrap

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "arduino", "Wordclock", "src")
DOCS = os.path.join(ROOT, "docs")


def info_rel(name):
    """Target of a generated file (relative to the repository root): a path with "/" stays as it is
    (arduino/README.md ...), SETUP_* -> docs/setup, LANG_* / LANGUAGES.txt -> docs/languages."""
    if "/" in name:
        return name
    return "docs/" + ("setup/" if name.startswith("SETUP_") else "languages/") + name
VERSION = "v1.0"

# times for the info files
STEPS_HOUR = 9                                    # all 5-minute steps of this hour
SPECIAL = ["00:00", "00:30", "00:35", "01:00", "01:05", "12:00", "12:30", "13:00", "09:01", "09:02"]
EXAMPLES = ["09:00", "10:25", "13:47", "23:58"]   # shown as lit grid

# planned languages (code: German name, English name) - shown in the overview until their files exist
PLANNED = [
    ("scifi_QYA", "Elbisch", "Elvish"), ("scifi_HVA", "Valyrisch", "Valyrian"),
]

# groups: languages of countries, dialects (code dialect_...), other languages (constructed, classical, fictional
# scifi_...). Codes without prefix and not in OTHER = country.
OTHER = ("VA", "EO")                              # plus every code starting with scifi_
GROUP_NAMES = {0: ("Länder", "countries"), 1: ("Dialekte", "dialects"), 2: ("andere Sprachen", "other languages")}
KIND = {0: "Land/country", 1: "Dialekt/dialect", 2: "andere/other"}


def group(code):
    if code.startswith("dialect_"):
        return 1
    if code in OTHER or code.startswith("scifi_"):
        return 2
    return 0


def order_key(code):
    return (group(code), {"DE": 0, "GB": 1}.get(code, 2), code)


def read(p):
    with open(p, encoding="utf-8") as f:
        return f.read()


def write(name, text):
    rel = info_rel(name)
    p = os.path.join(ROOT, *rel.split("/"))
    os.makedirs(os.path.dirname(p), exist_ok=True)
    text = text.rstrip("\n") + "\n"
    old = read(p) if os.path.isfile(p) else None
    if old != text:
        with open(p, "w", encoding="utf-8", newline="\n") as f:
            f.write(text)
        print("written   %s" % rel)
    else:
        print("unchanged %s" % rel)


# ------------------------------------------------------------------ language data
def lang_data(code):
    h = read(os.path.join(SRC, "wc_lang_%s.h" % code))
    y = read(os.path.join(ROOT, "esphome", "wordclock_multi", "lang", "lang_%s.yaml" % code))
    d = {"code": code}
    m = re.search(r"wc_lang_\w+\.h - .*?, (v[\d.]+)", h)
    d["version"] = m.group(1) if m else "?"
    m = re.search(r"static const WcLangDef WC_LANG = \{\s*\"([^\"]+)\",\s*\"([^\"]+)\"", h)
    d["name"] = m.group(2) if m else code
    m = re.search(r"time_words,\s*\"([^\"]+)\",\s*\"([^\"]+)\",\s*(-?[\d.]+)f,\s*(-?[\d.]+)f,\s*//\s*([^\n]+)\n"
                  r"\s*\"([^\"]+)\",\s*//\s*([^\n]+)\n\s*\"([^\"]+)\"", h)
    if m:
        d.update(host=m.group(1), ap=m.group(2), lat=float(m.group(3)), lon=float(m.group(4)),
                 capital=m.group(5).strip(), posix=m.group(6), tzname=m.group(7).split(" (")[0].strip(),
                 datefmt=m.group(8))
    g = re.search(r"GRID\[16\]\s*=\s*\{(.*?)\};", h, re.S)
    d["grid"] = re.findall(r'"((?:[^"\\]|\\.)*)"', g.group(1)) if g else []
    m = re.search(r"^\s*INFO_DE\b[^\n]*\n(.*?)^\s*INFO_EN\s*\n(.*?)^\s*INFO_END", h, re.S | re.M)
    strip = lambda t: "\n".join(l[2:] if l.startswith("  ") else l for l in t.rstrip().split("\n"))
    d["info_de"], d["info_en"] = (strip(m.group(1)), strip(m.group(2))) if m else ("(INFO_DE fehlt)", "(INFO_EN missing)")
    for k in ("name", "friendly_name", "ap_ssid"):
        m = re.search(r"^  %s:\s*(.+?)\s*$" % k, y, re.M)
        d["y_" + k] = m.group(1) if m else ""
    d["tested"] = d["version"] not in ("v0.9", "?") and not d["version"].startswith("v0.")
    return d


def languages():
    codes = sorted((f[8:-2] for f in os.listdir(SRC) if f.startswith("wc_lang_") and f.endswith(".h")), key=order_key)
    return [lang_data(c) for c in codes]


# ------------------------------------------------------------------ script variants (front only)
VAR = []                                          # filled in main(): script variants, see tools/make_variants.py


def scad_strings(text):
    text = "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("//"))
    m = re.search(r"LANG_\w+\s*=\s*\[(.*)\]\s*;", text, re.S)
    return re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1)) if m else []


def variants(langs):
    """Script variants: models/lang/lang_XX.scad with a base language (field 7) and no wc_lang_XX.h."""
    d = os.path.join(ROOT, "models", "lang")
    by = {x["code"]: x for x in langs}
    out = []
    if not os.path.isdir(d):
        return out
    for f in sorted(os.listdir(d)):
        code = f[5:-5]
        if not (f.startswith("lang_") and f.endswith(".scad")) or f == "lang_all.scad" or code in by:
            continue
        s = scad_strings(read(os.path.join(d, f)))
        if len(s) > 21 and s[21] in by:
            b = by[s[21]]
            pairs = []
            for r in range(16):
                for c in range(16):
                    a, v = b["grid"][r][c], s[2 + r][c]
                    if a != v and (a, v) not in pairs:
                        pairs.append((a, v))
            out.append({"code": code, "name": s[1], "grid": s[2:18], "font": s[18], "fontfile": s[19],
                        "filler": s[20], "base": b, "pairs": sorted(pairs)})
    return out


def variant_file(v):
    b = v["base"]
    L = []
    L.append("Wordclock_Multi %s - %s (%s)" % (VERSION, v["name"], v["code"]))
    L.append("=" * len(L[0]))
    L.append("Automatisch erzeugt von tools/make_info.py - nicht von Hand ändern. / Generated, do not edit.")
    L.append("")
    L.append("Schrift-Variante der Sprache %s (%s): nur die Front ist anders. Raster, Wörter, Grammatik und Firmware sind"
             % (b["code"], b["name"]))
    L.append("die von %s, die Buchstaben stehen in einer anderen Schrift. Für die Uhr die Sprache %s wählen" % (b["code"], b["code"]))
    L.append("(Arduino config.h, ESPHome wordclock_multi.yaml), nur im 3D-Modell LANG = \"%s\"." % v["code"])
    L.append("Script variant of the language %s (%s): only the front differs. Grid, words, grammar and firmware are"
             % (b["code"], b["name"]))
    L.append("those of %s, the letters are printed in another script. Choose the language %s for the clock" % (b["code"], b["code"]))
    L.append("(Arduino config.h, ESPHome wordclock_multi.yaml), LANG = \"%s\" only in the 3D model." % v["code"])
    L.append("")
    L.append("Datei / file:                 models/lang/lang_%s.scad (erzeugt von / generated by tools/make_variants.py)" % v["code"])
    L.append("Schrift / font:               OpenSCAD \"%s\", FreeCAD %s" % (v["font"] or "FONT", v["fontfile"] or "(Dialog / dialog)"))
    L.append("Grammatik, Uhrzeiten / grammar, times: docs/languages/LANG_%s.txt" % b["code"])
    L.append("")
    L.append("BUCHSTABEN / LETTERS")
    L.append("-" * 20)
    for i in range(0, len(v["pairs"]), 8):
        L.append("  " + "   ".join("%s = %s" % p for p in v["pairs"][i:i + 8]))
    L.append("")
    L.append("RASTER / GRID (Zeile 1 = oben / row 1 = top)")
    L.append("-" * 44)
    L.append(framed(v["grid"]))
    L.append("")
    L.append("Basis / base %s:" % b["code"])
    L.append(framed(b["grid"]))
    return "\n".join(L)


def model_rows(langs):
    return langs + [{"code": v["code"], "name": v["name"]} for v in VAR]


# ------------------------------------------------------------------ preview (g++)
class Preview:
    def __init__(self, code, cxx, tmp):
        self.exe = os.path.join(tmp, "preview_%s%s" % (code, ".exe" if os.name == "nt" else ""))
        r = subprocess.run([cxx, "-std=c++11", "-DLANG=%s" % code, os.path.join(ROOT, "tools", "preview.cpp"),
                            "-o", self.exe], capture_output=True, text=True)
        if r.returncode:
            raise RuntimeError(r.stderr[-1500:])
        self.texts = {}
        for l in self.run("all").splitlines():
            m = re.match(r"^(\d\d:\d\d|no time)  (.*)$", l)
            if m:
                self.texts[m.group(1)] = m.group(2)

    def run(self, *args):
        return subprocess.run([self.exe] + list(args), capture_output=True, text=True, encoding="utf-8").stdout

    def grid(self, hhmm):
        rows = [l[2:] for l in self.run("grid", hhmm, "time").splitlines() if l.startswith("  ")]
        return rows[-16:]


def framed(rows, numbers=True):
    out = ["     " + "".join(str((c + 1) % 10) for c in range(16))] if numbers else []
    for i, r in enumerate(rows):
        out.append(("  %2d " % (i + 1) if numbers else "") + r)
    return "\n".join(out)


def lang_file(d, pv):
    c = d["code"]
    status_de = "bestätigt" if d["tested"] else "Grammatik unbestätigt"
    status_en = "confirmed" if d["tested"] else "grammar unconfirmed"
    L = []
    L.append("Wordclock_Multi %s - %s (%s)" % (VERSION, d["name"], c))
    L.append("=" * len(L[0]))
    L.append("Automatisch erzeugt von tools/make_info.py - nicht von Hand ändern. / Generated, do not edit.")
    L.append("")
    L.append("Status:                       %s (%s / %s)" % (d["version"], status_de, status_en))
    L.append("Hauptstadt / capital:         %s  (%.4f, %.4f)" % (d.get("capital", "?"), d.get("lat", 0), d.get("lon", 0)))
    L.append("Zeitzone / time zone:         %s  (POSIX %s)" % (d.get("tzname", "?"), d.get("posix", "?")))
    L.append("Arduino: Hotspot / hotspot:   %s  ->  http://192.168.4.1" % d.get("ap", "?"))
    L.append("Arduino: Adresse / address:   http://%s.local" % d.get("host", "?"))
    L.append("ESPHome: Gerät / device:      %s (%s), Fallback-Hotspot \"%s\"" % (d["y_name"], d["y_friendly_name"], d["y_ap_ssid"]))
    L.append("Dateien / files:              arduino/Wordclock/src/wc_lang_%s.h" % c)
    L.append("                              esphome/wordclock_multi/lang/lang_%s.yaml (+ src/wc_lang_%s.h)" % (c, c))
    L.append("                              models/lang/lang_%s.scad" % c)
    L.append("Auswahl / selection:          config.h: #define WC_LANG_FILE \"src/wc_lang_%s.h\"" % c)
    L.append("                              wordclock_multi.yaml: lang: !include wordclock_multi/lang/lang_%s.yaml" % c)
    L.append("                              OpenSCAD/FreeCAD: LANG = \"%s\"" % c)
    L.append("")
    L.append("RASTER / GRID (Zeile 1 = oben / row 1 = top)")
    L.append("-" * 44)
    L.append(framed(d["grid"]))
    L.append("")
    L.append("  *  Temperaturpunkt (links außen, rechts innen) / temperature dot (left outside, right inside)")
    L.append("  |  Akkubalken / battery bar")
    L.append("  x  Füllfeld, leuchtet nie; im 3D-Modell als FILLER gedruckt (auto = Vorgabe der Sprache, sonst X)")
    L.append("     filler, never lit; printed as FILLER in the 3D models (auto = language default, else X)")
    L.append("")
    L.append("GRAMMATIK (Deutsch)")
    L.append("-" * 19)
    L.append(d["info_de"])
    L.append("")
    L.append("GRAMMAR (English)")
    L.append("-" * 17)
    L.append(d["info_en"])
    if pv:
        L.append("")
        L.append("ALLE 5-MINUTEN-SCHRITTE / ALL 5-MINUTE STEPS (%d:00 - %d:55)" % (STEPS_HOUR, STEPS_HOUR))
        L.append("-" * 60)
        for m in range(0, 60, 5):
            k = "%02d:%02d" % (STEPS_HOUR, m)
            L.append("%s  %s" % (k, pv.texts.get(k, "?")))
        L.append("")
        L.append("SONDERFÄLLE / SPECIAL TIMES")
        L.append("-" * 27)
        L.append("ohne Uhrzeit / no time  %s" % pv.texts.get("no time", "?"))
        for k in SPECIAL:
            L.append("%s  %s" % (k, pv.texts.get(k, "?")))
        L.append("")
        L.append("BEISPIELE / EXAMPLES (nur Uhrzeit, · = aus / time only, · = off)")
        L.append("-" * 64)
        grids = [pv.grid(t) for t in EXAMPLES]
        L.append("   ".join("%-16s" % t for t in EXAMPLES).rstrip())
        for r in range(16):
            L.append("   ".join(g[r] if r < len(g) else " " * 16 for g in grids))
        L.append("")
        for t in EXAMPLES:
            L.append("%s  %s" % (t, pv.texts.get(t, "?")))
    else:
        L.append("")
        L.append("(Uhrzeiten und Beispiele fehlen: kein g++ gefunden / times and examples missing: no g++ found)")
    return "\n".join(L)


# ------------------------------------------------------------------ overview + setup guides
def table(langs, cols, rowfn, indent="   "):
    rows = [cols] + [rowfn(d) for d in langs]
    w = [max(len(r[i]) for r in rows) for i in range(len(cols))]
    out = []
    for n, r in enumerate(rows):
        out.append(indent + "  ".join(r[i].ljust(w[i]) for i in range(len(cols))).rstrip())
        if n == 0:
            out.append(indent + "  ".join("-" * w[i] for i in range(len(cols))))
    return "\n".join(out)


def st(d, de):
    return ("bestätigt" if d["tested"] else "Grammatik unbestätigt") if de else ("confirmed" if d["tested"] else "grammar unconfirmed")


def planned_line(langs, de):
    have = {d["code"] for d in langs}
    p = [(c, n_de if de else n_en) for c, n_de, n_en in PLANNED if c not in have]
    return ", ".join("%s (%s)" % (n, c) for c, n in p) if p else "-"


def overview(langs):
    T = []
    T.append("Wordclock_Multi %s - Sprachen / languages" % VERSION)
    T.append("=" * len(T[0]))
    T.append("Automatisch erzeugt von tools/make_info.py - nicht von Hand ändern. / Generated, do not edit.")
    T.append("")
    T.append(table(langs, ["Code", "Sprache/language", "Art/kind", "Version", "Status", "Hauptstadt/capital",
                           "Zeitzone/time zone"],
                   lambda d: [d["code"], d["name"], KIND[group(d["code"])], d["version"],
                              st(d, True) + " / " + st(d, False), d.get("capital", "?"), d.get("tzname", "?")]))
    T.append("")
    if VAR:
        T.append("Schrift-Varianten (nur Front, Firmware der Basissprache) / script variants (front only, firmware of the base):")
        T.append(table(VAR, ["Code", "Name", "Basis/base", "Schrift/font (OpenSCAD, FreeCAD)"],
                       lambda v: [v["code"], v["name"], v["base"]["code"], "%s, %s" % (v["font"], v["fontfile"])]))
        T.append("")
    if planned_line(langs, True) != "-":
        T.append("Geplant / planned:")
        for k, de in (("DE", True), ("EN", False)):
            T.append(textwrap.fill(planned_line(langs, de), 110, initial_indent="  %s: " % k, subsequent_indent="      "))
        T.append("")
    T.append("Details je Sprache / per language: docs/languages/LANG_<Code>.txt")
    T.append("Neue Sprache / new language: docs/LANG_SPEC.md")
    return "\n".join(T)


def md_tab(langs, cols, rowfn):
    """Markdown table: header cols, one row per entry (rowfn returns the cells, already formatted)."""
    out = ["| " + " | ".join(cols) + " |", "|" + "---|" * len(cols)]
    for d in langs:
        out.append("| " + " | ".join(rowfn(d)) + " |")
    return "\n".join(out)


def variant_note(de):
    if not VAR:
        return ""
    names = ", ".join("`%s` = `%s`" % (v["code"], v["base"]["code"]) for v in VAR)
    if de:
        return "\n\nSchrift-Varianten (nur Front, gleiche Firmware wie die Basissprache - diese hier wählen): " + names
    return "\n\nScript variants (front only, same firmware as the base language - choose that one here): " + names


def head(title, de, other):
    """Title, generated note and link to the other language version (other = file name of it)."""
    t = "# Wordclock_Multi %s - %s\n\n" % (VERSION, title)
    gen = ("> Automatisch erzeugt von `tools/make_info.py` - nicht von Hand ändern.\n\n"
           "[English](%s) | **Deutsch**\n" % other if de else
           "> Generated by `tools/make_info.py` - do not edit by hand.\n\n"
           "**English** | [Deutsch](%s)\n" % other)
    return t + gen


def setup_arduino(langs, de):
    tab = md_tab(langs, ["Code", "Sprache" if de else "Language", "config.h", "Hotspot", "Adresse" if de else "Address"],
                 lambda d: ["`%s`" % d["code"], d["name"], '`#define WC_LANG_FILE "src/wc_lang_%s.h"`' % d["code"],
                            "`%s`" % d.get("ap", "?"), "http://%s.local" % d.get("host", "?")]) + variant_note(de)
    if de:
        return head("Einrichtung Arduino", True, "README.md") + """
Einzeldatei-Sketch je Sprache: [`single_Language/`](single_Language/).

## 1. Voraussetzungen

- Arduino IDE 2.x mit dem ESP32-Boardpaket von Espressif (Version 2.0.x oder 3.x).
  Boardverwalter-URL: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
- Nur bei Boardpaket 2.0.x: Bibliothek „Adafruit NeoPixel“ (Bibliotheksverwalter).
  Mit 3.x wird keine zusätzliche Bibliothek gebraucht.

## 2. Was wohin kopieren

Den kompletten Ordner `arduino/Wordclock` in den Sketchbook-Ordner der Arduino IDE kopieren
(z. B. `Dokumente/Arduino/Wordclock`). Der Ordner muss `Wordclock` heißen und enthält:

- `Wordclock.ino`, `config.h`, `webpage.h` (`webpage.html` = Quelle der Weboberfläche)
- `src/wc_core.h`, `src/wc_effects.h`, `src/wc_text.h`, `src/wc_font16.h`
- `src/wc_lang_XX.h` (alle Sprachen, nur die gewählte wird kompiliert)

## 3. Sprache wählen

Nur in `config.h`, eine Zeile (die Liste steht auch als Kommentar in `config.h`):

%s

Die Sprache bestimmt Raster, Uhrzeitwörter, Texte der Weboberfläche, Gerätename, Hotspot-Name sowie
Standard-Standort und Zeitzone (Hauptstadt). Standort und Zeitzone sind später in der Weboberfläche änderbar.

## 4. Hardware in config.h

`LED_PIN` (Standard 32 beim Wemos D1 mini ESP32, 2 beim ESP32-C6), `MA_PER_CHANNEL`, `IDLE_MA_PER_LED`,
`AP_PASS` (leer = offener Hotspot), optional `AP_SSID` (eigener Hotspot-Name). Alles andere wird in der
Weboberfläche eingestellt.

## 5. Hochladen

Board „WEMOS D1 MINI ESP32“, Partition Scheme „Default 4MB with spiffs“, Port wählen, Hochladen.
Updates nur per USB, kein Update über WLAN.

ESP32-C6 (SuperMini / XIAO): nur mit Boardpaket 3.x, Board „ESP32C6 Dev Module“ (bzw. „XIAO_ESP32C6“),
„USB CDC On Boot: Enabled“ (serieller Monitor über USB), gleiches Partition Scheme. `LED_PIN` ist dann
automatisch GPIO2.

## 6. Erster Start

Die Uhr öffnet den Hotspot aus der Tabelle oben → verbinden → http://192.168.4.1 → unter WLAN das eigene
Netz eintragen. Danach erreichbar unter der Adresse aus der Tabelle oder der IP aus dem Router.
Steuerung per HTTP: siehe Kommentar oben in `Wordclock.ino` (Parameternamen in allen Sprachen gleich).

## 7. Sprache wechseln

Zeile in `config.h` ändern und per USB neu hochladen.

## 8. Lauftext

Weboberfläche, Bereich Effekte: Text eingeben, „Lauftext starten“. Jeder Buchstabe füllt die ganze Matrix,
der Text läuft für die Effekt Dauer (mindestens einmal komplett, Dauer 0 = bis Stopp) in der Farbe der Uhrzeit
(„Zufall“ = Regenbogen). Per HTTP: `/api/set?text=Hallo%%20Welt` (optional `&textcolor=red|rrggbb|rainbow`),
`/api/set?textstart=1` zeigt den gespeicherten Text erneut, `fx=stop` beendet ihn. Schrift: lateinische,
griechische und kyrillische Buchstaben, Ziffern, Satzzeichen, € und ♥ (chinesische, japanische und
koreanische Zeichen werden übersprungen).

---

Alle Sprachen im Detail: [`docs/languages/LANG_<Code>.txt`](../docs/languages/),
Übersicht: [`docs/languages/LANGUAGES.txt`](../docs/languages/LANGUAGES.txt)
""" % tab
    return head("Setup Arduino", False, "README_DE.md") + """
Single-file sketch per language: [`single_Language/`](single_Language/).

## 1. Requirements

- Arduino IDE 2.x with the ESP32 board package by Espressif (version 2.0.x or 3.x).
  Board manager URL: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
- Only with board package 2.0.x: library "Adafruit NeoPixel" (library manager).
  With 3.x no additional library is needed.

## 2. What goes where

Copy the complete folder `arduino/Wordclock` into the sketchbook folder of the Arduino IDE
(e.g. `Documents/Arduino/Wordclock`). The folder must be called `Wordclock` and contains:

- `Wordclock.ino`, `config.h`, `webpage.h` (`webpage.html` = source of the web interface)
- `src/wc_core.h`, `src/wc_effects.h`, `src/wc_text.h`, `src/wc_font16.h`
- `src/wc_lang_XX.h` (all languages, only the chosen one is compiled)

## 3. Choose the language

Only in `config.h`, one line (the list is also a comment in `config.h`):

%s

The language sets grid, time words, texts of the web interface, device name, hotspot name and the default
location and time zone (capital). Location and time zone can be changed later in the web interface.

## 4. Hardware in config.h

`LED_PIN` (default 32 on the Wemos D1 mini ESP32, 2 on the ESP32-C6), `MA_PER_CHANNEL`, `IDLE_MA_PER_LED`,
`AP_PASS` (empty = open hotspot), optional `AP_SSID` (own hotspot name). Everything else is set in the
web interface.

## 5. Upload

Board "WEMOS D1 MINI ESP32", partition scheme "Default 4MB with spiffs", choose the port, upload.
Updates via USB only, no update over Wi-Fi.

ESP32-C6 (SuperMini / XIAO): board package 3.x only, board "ESP32C6 Dev Module" (or "XIAO_ESP32C6"),
"USB CDC On Boot: Enabled" (serial monitor via USB), same partition scheme. `LED_PIN` is then GPIO2
automatically.

## 6. First start

The clock opens the hotspot from the table above → connect → http://192.168.4.1 → enter your network
under Wi-Fi. Afterwards reachable at the address from the table or the IP from the router.
Control via HTTP: see the comment at the top of `Wordclock.ino` (parameter names are the same in all languages).

## 7. Change the language

Change the line in `config.h` and upload again via USB.

## 8. Text ticker

Web interface, section effects: enter a text, "Start text". Every letter fills the whole matrix, the text runs
for the effect duration (at least once completely, duration 0 = until stop) in the colour of the time
("random" = rainbow). Via HTTP: `/api/set?text=Hello%%20World` (optional `&textcolor=red|rrggbb|rainbow`),
`/api/set?textstart=1` shows the saved text again, `fx=stop` ends it. Font: Latin, Greek and Cyrillic letters,
digits, punctuation, € and ♥ (Chinese, Japanese and Korean characters are skipped).

---

All languages in detail: [`docs/languages/LANG_<code>.txt`](../docs/languages/),
overview: [`docs/languages/LANGUAGES.txt`](../docs/languages/LANGUAGES.txt)
""" % tab


def setup_esphome(langs, de):
    tab = md_tab(langs, ["Code", "Sprache" if de else "Language", "wordclock_multi.yaml (packages:)",
                         "Gerät/name" if de else "Device/name", "Fallback-Hotspot"],
                 lambda d: ["`%s`" % d["code"], d["name"], "`lang: !include wordclock_multi/lang/lang_%s.yaml`" % d["code"],
                            "`%s`" % d["y_name"], "`%s`" % d["y_ap_ssid"]]) + variant_note(de)
    if de:
        return head("Einrichtung ESPHome", True, "README.md") + """
Einfacher: Einzeldatei-Version je Sprache in [`single_Language/`](single_Language/) (2 Dateien, siehe
[`README.md`](single_Language/README.md) dort).

## 1. Was wohin kopieren

Den **Inhalt** des Ordners `esphome/` 1:1 nach `/config/esphome/` (Home-Assistant-Add-on ESPHome):

| Datei | Inhalt |
|---|---|
| `/config/esphome/wordclock_multi.yaml` | die einzige Datei, die normalerweise geändert wird |
| `/config/esphome/wordclock_multi/core.yaml` | Logik und Entitäten (für alle Sprachen gleich) |
| `/config/esphome/wordclock_multi/lang/lang_XX.yaml` | Namen, Optionen, Standort je Sprache |
| `/config/esphome/wordclock_multi/src/*.h` | C++ (Anzeige, Effekte, Raster + Uhrzeitwörter) |

Der Unterordner sorgt dafür, dass das ESPHome-Dashboard die Pakete nicht als eigene Geräte anzeigt.

## 2. Secrets

`secrets.yaml` neben `wordclock_multi.yaml`: `wifi_ssid`, `wifi_password`, `ap_password`, `api_key`, `ota_password`

## 3. Sprache wählen

In `wordclock_multi.yaml` unter `packages:`, eine Zeile (Liste auch als Kommentar in der Datei):

%s

Hotspot und Standort kommen aus der Sprache, Uhrzeit und Zeitzone aus Home Assistant
(Zeitzone wird gespeichert, ohne Home Assistant läuft die Uhr über NTP weiter).
Der Gerätename steht fest in `wordclock_multi.yaml` (`name`, `friendly_name`), ein Sprachwechsel ändert ihn nicht.

**Mehrere Uhren:** je Uhr eine Kopie von `wordclock_multi.yaml` (z. B. `wortuhr-kueche.yaml`) mit eigenem `name:`,
alle nutzen den Ordner `wordclock_multi/`. Umbenennen geht auch im ESPHome-Dashboard (… > Rename).

## 4. Anpassen in wordclock_multi.yaml (substitutions:)

- `led_pin` (Standard GPIO32; ESP32-C6: GPIO2), `serpentine` (Zickzack-Verdrahtung, Standard `"true"`),
  `mirror_x` (Standard `"true"`), `ma_per_channel`, `idle_ma_per_led`
- Entitäten aus Home Assistant: `alarm_entity`, `vent_entity`, `battery_entity`, `temp_out_entity`, `temp_in_entity`
- `ha_timeout_min` (Standard 5: so viele Minuten ohne Verbindung zu Home Assistant → ALARM, LÜFTEN, AKKU und
  Temperatur aus)
- `name`, `friendly_name` (Gerätename, je Uhr eindeutig)
- optional `latitude`, `longitude` (überschreiben die Werte der Sprache)
- Board: `wemos_d1_mini32`; ESP32-C6 (SuperMini/XIAO) siehe Kommentar am Ende der Datei.

## 5. Installieren

ESPHome-Dashboard: `wordclock_multi` → Install. Kommandozeile: `esphome run wordclock_multi.yaml`

**Lauftext:** Textfeld „Lauftext“ und Taste „Lauftext starten“ (Namen je Sprache). Jeder Buchstabe füllt die
ganze Matrix, Dauer = Effekt Dauer (mindestens einmal komplett), Farbe = Farbe Uhrzeit (Zufall = Regenbogen).
In Automationen: Aktion `esphome.<name>_show_text` mit `text: "Hallo"` (setzt den Text und startet ihn).

## 6. Nur für Entwickler

Die `.h`-Dateien werden nur in `arduino/Wordclock/src/` geändert; danach `python3 tools/sync_src.py` ausführen
(kopiert sie nach `esphome/wordclock_multi/src/`).

---

Alle Sprachen im Detail: [`docs/languages/LANG_<Code>.txt`](../docs/languages/),
Übersicht: [`docs/languages/LANGUAGES.txt`](../docs/languages/LANGUAGES.txt)
""" % tab
    return head("Setup ESPHome", False, "README_DE.md") + """
Simpler: single-file version per language in [`single_Language/`](single_Language/) (2 files, see the
[`README.md`](single_Language/README.md) there).

## 1. What goes where

Copy the **content** of the folder `esphome/` 1:1 to `/config/esphome/` (Home Assistant add-on ESPHome):

| File | Content |
|---|---|
| `/config/esphome/wordclock_multi.yaml` | the only file you normally edit |
| `/config/esphome/wordclock_multi/core.yaml` | logic and entities (the same for all languages) |
| `/config/esphome/wordclock_multi/lang/lang_XX.yaml` | names, options, location per language |
| `/config/esphome/wordclock_multi/src/*.h` | C++ (display, effects, grid + time words) |

The subfolder keeps the packages out of the ESPHome dashboard (it would list them as devices).

## 2. Secrets

`secrets.yaml` next to `wordclock_multi.yaml`: `wifi_ssid`, `wifi_password`, `ap_password`, `api_key`, `ota_password`

## 3. Choose the language

In `wordclock_multi.yaml` under `packages:`, one line (list also as a comment in the file):

%s

Hotspot and location come from the language, time and time zone from Home Assistant
(time zone is saved, without Home Assistant the clock keeps running via NTP).
The device name is fixed in `wordclock_multi.yaml` (`name`, `friendly_name`), changing the language keeps it.

**Several clocks:** one copy of `wordclock_multi.yaml` per clock (e.g. `wordclock-kitchen.yaml`) with its own `name:`,
all use the folder `wordclock_multi/`. Renaming also works in the ESPHome dashboard (… > Rename).

## 4. Adjust in wordclock_multi.yaml (substitutions:)

- `led_pin` (default GPIO32; ESP32-C6: GPIO2), `serpentine` (zigzag wiring, default `"true"`),
  `mirror_x` (default `"true"`), `ma_per_channel`, `idle_ma_per_led`
- entities from Home Assistant: `alarm_entity`, `vent_entity`, `battery_entity`, `temp_out_entity`, `temp_in_entity`
- `ha_timeout_min` (default 5: minutes without connection to Home Assistant → ALARM, VENT, BATTERY and
  temperature off)
- `name`, `friendly_name` (device name, unique per clock)
- optional `latitude`, `longitude` (overwrite the values of the language)
- Board: `wemos_d1_mini32`; ESP32-C6 (SuperMini/XIAO) see the comment at the end of the file.

## 5. Install

ESPHome dashboard: `wordclock_multi` → Install. Command line: `esphome run wordclock_multi.yaml`

**Text ticker:** text field "Text ticker" and button "Start text" (names per language). Every letter fills the
whole matrix, duration = effect duration (at least once completely), colour = colour of the time
(random = rainbow). In automations: action `esphome.<name>_show_text` with `text: "Hello"` (sets and starts it).

## 6. Developers only

The `.h` files are only edited in `arduino/Wordclock/src/`; afterwards run `python3 tools/sync_src.py`
(copies them to `esphome/wordclock_multi/src/`).

---

All languages in detail: [`docs/languages/LANG_<code>.txt`](../docs/languages/),
overview: [`docs/languages/LANGUAGES.txt`](../docs/languages/LANGUAGES.txt)
""" % tab


def setup_freecad(langs, de):
    tab = md_tab(model_rows(langs), ["Code", "Sprache" if de else "Language", "Makro / macro", "Datei / file"],
                 lambda d: ["`%s`" % d["code"], d["name"], '`LANG = "%s"`' % d["code"], "`models/lang/lang_%s.scad`" % d["code"]])
    if de:
        return head("Einrichtung FreeCAD", True, "SETUP_FreeCAD_EN.md") + """
## 1. Was wohin kopieren

`Wordclock_Model.FCMacro`, `Wordclock_Common.py` (gemeinsamer Teil beider Makros) und den Ordner `lang/`
(mit allen `lang_XX.scad`) zusammen in einen Ordner kopieren, z. B. in den FreeCAD-Makroordner
(Makro > Makros... zeigt den Pfad) oder einfach den Ordner `models/` benutzen.
Das Makro liest die Raster aus `lang/lang_XX.scad` neben sich (anderer Ort: `LANG_DIR` oben im Makro).

## 2. Sprache wählen

Oben im Makro:

- `LANG = None` → Auswahldialog beim Start (zeigt alle gefundenen Sprachen)
- `LANG = "ALL"` → Fronten aller Sprachen in einem Durchlauf

%s

## 3. Wichtige Einstellungen

Oben im Makro, Kommentare dort:

- `MODEL` / `BUILD_*` (welche Teile), `CAP_HEIGHT`, `FRONT_SKIN`, `ESP_BOARD`
- `FONT_FILE` (`None` = Schriftdialog; Sprachen mit eigener Schrift wie JP/CN/KR bekommen automatisch eine
  passende installierte Schrift, `FONT_AUTO` / `LANG_FONTS`)
- `FILLER` = Darstellung der Füllfelder (`x` im Raster): `"auto"` (Standard: Vorgabe der Sprache aus
  `lang_XX.scad`, z. B. Punkt bei CN/JP/KR, sonst X), `"X"`, `"dot"` (Punkt wie die Temperaturpunkte,
  Größe `FILLER_DOT`) oder ein beliebiges Zeichen wie `"-"`, `"+"`, `"O"`.
  Die Füllfelder bleiben offen (Lichtkammer), damit Effekte über die ganze Fläche laufen.

## 4. Ausführen und exportieren

Makro > Makros... > `Wordclock_Model.FCMacro` > Ausführen. Mit `EXPORT = "stl"` (Standard, `"step"` geht auch)
landen alle Teile in Drucklage im Ordner `export/` neben dem Makro. Dateinamen wie in OpenSCAD, mit Zusatz `_freecad`:
`Frame_<LANG>_<Schrift>_freecad` (Buchstaben: `..._Letters_freecad`), `Rear_freecad`, `Holder_<Name>_freecad`
(Stützen: `Holder_<Name>_Support_freecad`).

## 5. Sondermodell PictureFrame

Der PictureFrame (Frontplatte für einen tiefen Bilderrahmen) hat ein eigenes Makro:
`Wordclock_Model_PictureFrame.FCMacro` (gleiche Parameter `PICTUREFRAME_*` wie in OpenSCAD, Befestigung
`PICTUREFRAME_OWN_MOUNT = "SCREW"` / `"THIMBLES"` / `"NONE"`, siehe [SETUP_OpenSCAD](SETUP_OpenSCAD_DE.md)).
Dateiname: `Pictureframe_<PICTUREFRAME_SIZE>_<LANG>_<Schrift>_freecad`.

---

Raster und Grammatik je Sprache: [`docs/languages/LANG_<Code>.txt`](../languages/)
""" % tab
    return head("Setup FreeCAD", False, "SETUP_FreeCAD_DE.md") + """
## 1. What goes where

Copy `Wordclock_Model.FCMacro`, `Wordclock_Common.py` (shared part of both macros) and the folder `lang/`
(all `lang_XX.scad`) into one folder, e.g. the FreeCAD macro folder (Macro > Macros... shows the path)
or simply use the folder `models/`.
The macro reads the grids from `lang/lang_XX.scad` next to it (other place: `LANG_DIR` at the top of the macro).

## 2. Choose the language

At the top of the macro:

- `LANG = None` → selection dialog at the start (lists all languages found)
- `LANG = "ALL"` → fronts of all languages in one run

%s

## 3. Important settings

Top of the macro, comments there:

- `MODEL` / `BUILD_*` (which parts), `CAP_HEIGHT`, `FRONT_SKIN`, `ESP_BOARD`
- `FONT_FILE` (`None` = font dialog; languages with their own script like JP/CN/KR automatically get a matching
  installed font, `FONT_AUTO` / `LANG_FONTS`)
- `FILLER` = how the filler cells (`x` in the grid) are printed: `"auto"` (default: the language's choice
  from `lang_XX.scad`, e.g. dot for CN/JP/KR, else X), `"X"`, `"dot"` (dot like the temperature dots,
  size `FILLER_DOT`) or any character such as `"-"`, `"+"`, `"O"`.
  Filler cells stay open (light chamber), so effects run over the whole face.

## 4. Run and export

Macro > Macros... > `Wordclock_Model.FCMacro` > Execute. With `EXPORT = "stl"` (default, `"step"` also works)
every part is written in print orientation into the folder `export/` next to the macro. File names as in
OpenSCAD plus `_freecad`: `Frame_<LANG>_<font>_freecad` (letters: `..._Letters_freecad`), `Rear_freecad`,
`Holder_<name>_freecad` (supports: `Holder_<name>_Support_freecad`).

## 5. Special model PictureFrame

The PictureFrame (front plate for a deep picture frame) has a macro of its own:
`Wordclock_Model_PictureFrame.FCMacro` (same parameters `PICTUREFRAME_*` as in OpenSCAD, fastening
`PICTUREFRAME_OWN_MOUNT = "SCREW"` / `"THIMBLES"` / `"NONE"`, see [SETUP_OpenSCAD](SETUP_OpenSCAD_EN.md)).
File name: `Pictureframe_<PICTUREFRAME_SIZE>_<LANG>_<font>_freecad`.

---

Grid and grammar per language: [`docs/languages/LANG_<code>.txt`](../languages/)
""" % tab


def setup_openscad(langs, de):
    tab = md_tab(model_rows(langs), ["Code", "Sprache" if de else "Language", "Customizer / -D", "Datei / file"],
                 lambda d: ["`%s`" % d["code"], d["name"], '`LANG = "%s"`' % d["code"], "`models/lang/lang_%s.scad`" % d["code"]])
    if de:
        return head("Einrichtung OpenSCAD", True, "SETUP_OpenSCAD_EN.md") + """
## 1. Was wohin kopieren

`Wordclock_Model.scad` (Gehäuse + Halter), `Wordclock_Model_PictureFrame.scad` (Sondermodell Bilderrahmen),
`Wordclock_Common.scad` (gemeinsamer Teil beider Modelle) und den Ordner `lang/` (`lang_all.scad` + alle
`lang_XX.scad`) zusammen lassen (am einfachsten den Ordner `models/` benutzen).
Optional `tools\\wordclock_tools.bat` (Windows, Punkt 9/10: alle Fronten auf einmal).

## 2. Sprache wählen

Customizer (Fenster > Customizer), Gruppe „Basis Settings“, Auswahl `LANG`:

%s

Kommandozeile:

```
openscad -o front.stl -D 'LANG="DE"' -D 'PART="Front"' -D 'PRINT_ORIENT=true' Wordclock_Model.scad
```

(`PART` = `Front`, `Rear`, `Holder_Foot`, `Holder_Skadis`, `Holder_Wall`, `Holder_BasePlate`, `Letters`)
Alle Fronten: `tools\\wordclock_tools.bat`, Punkt 9 (oder `python tools/export_fronts.py`, OpenSCAD wird gesucht).

## 3. Wichtige Einstellungen (Customizer)

`LANG`, `FONT` (Schrift), `PART` (Anzeige: alle nebeneinander / montiert), `BUILD_*` (welche Teile gebaut werden),
`FRAME_WALL`, `DOT_DIAMETER`, `STROKE_VERTICAL`, `FRONT_SKIN`, `BACK_MOUNT`, `SCREW_TYPE`, `SCREW_HEAD`,
`STRAIN_RELIEF`, `CABLE_SLOT_REAR`, `CABLE_SLOT_FRAME`, `ESP_BOARD` (`CUSTOM_BOARD`), `WALL_SCREW_DIAMETER`.

Alles andere (Matrix, Buchstabenhöhe, Raster, Füllfelder, Rückwand/Befestigung, Halter, `QUALITY`,
`PRINT_ORIENT`) steht in den versteckten Config-Blöcken der Datei - nur ändern, wenn man weiß, was man tut.

`FONT` = Schriftart für Front und Buchstaben: Liberation Sans Bold (Standard, liegt OpenSCAD bei),
Arial Bold oder DejaVu Sans Bold. Sprachen mit eigenem Zeichensatz (CN 中文, JP 日本語, KR 한국어,
Runen-Varianten) nutzen immer ihre eigene Schrift - die Auswahl `FONT` wird dann ignoriert.

### 3a. Schriften für andere Zeichensätze installieren (nur CN, JP, KR)

Für diese Sprachen muss zusätzlich eine Schrift installiert sein (OpenSCAD findet sie im System):

| Sprache | Schrift | Download |
|---|---|---|
| CN 中文 | Noto Sans SC Bold | https://fonts.google.com/noto/specimen/Noto+Sans+SC |
| JP 日本語 | Noto Sans JP Bold | https://fonts.google.com/noto/specimen/Noto+Sans+JP |
| KR 한국어 | Noto Sans KR Bold | https://fonts.google.com/noto/specimen/Noto+Sans+KR |

Download: Seite öffnen, oben rechts „Download“ → ZIP entpacken und die TTF-Dateien installieren
(Windows: Rechtsklick auf die TTF-Datei → „Für alle Benutzer installieren“).
Die Runen-Varianten brauchen nichts zusätzliches: Windows 10/11 hat Segoe UI Historic dabei.
Ohne installierte Schrift meldet OpenSCAD einen Fehler, wenn die entsprechende Sprache gewählt wird.

## 4. Exportieren

F6 (Rendern), F7 (STL). Der Exportname steht in der Konsole: Front `Frame_<LANG>_<Schrift>`
(Buchstaben `..._Letters`), Rückwand `Rear`, Halter `Holder_<Name>` (Stützen `Holder_<Name>_Support`),
PictureFrame `Pictureframe_<Größe>_<LANG>_<Schrift>`.
Tipp: OpenSCAD 2024/2025 mit Backend „Manifold“ rendert in Sekunden.

## 5. Neue Sprache im Modell

`models/lang/lang_XX.scad` anlegen, in `lang/lang_all.scad` die include-Zeile und den Eintrag in `LANGS`
ergänzen und in `Wordclock_Model.scad` die Option `XX:Name` in der `LANG`-Zeile (siehe [`docs/LANG_SPEC.md`](../LANG_SPEC.md)).

## 6. Sondermodell PictureFrame (eigene Datei Wordclock_Model_PictureFrame.scad)

Frontplatte für einen tiefen Bilderrahmen (Standard: 231 mm Bildmaß, 38 mm Innentiefe). `PICTUREFRAME_SIZE`
und `PICTUREFRAME_FRAME_DEPTH` nachmessen, `PICTUREFRAME_GLASS_THICKNESS` = Dicke der Originalscheibe, wenn sie
vorn bleiben soll (0 = ohne). ESP waagerecht unter dem Buchstabenteil (USB rechts, Zugentlastung daneben).
Befestigung umschalten mit `PICTUREFRAME_OWN_MOUNT`:

- `SCREW` = 4 Schraubblöcke in den Ecken (Spax-Senkkopf in die Rahmenwand) + Schlüsselloch-Aufhänger oben
- `THIMBLES` = 4 Blöcke für je eine Reißzwecke in die Rahmenwand (z. B. Spanplattenrahmen) + Schlüsselloch-Aufhänger
- `NONE` = nur die Platte, gehalten von Rückwand / Abstandsrahmen und Aufhänger des Bilderrahmens

Kommandozeile:

```
openscad -o pf.stl -D 'LANG="DE"' -D 'PRINT_ORIENT=true' Wordclock_Model_PictureFrame.scad
```

(alle Sprachen: `tools\\wordclock_tools.bat`, Punkt 10). FreeCAD: `Wordclock_Model_PictureFrame.FCMacro`.

---

Raster und Grammatik je Sprache: [`docs/languages/LANG_<Code>.txt`](../languages/)
""" % tab
    return head("Setup OpenSCAD", False, "SETUP_OpenSCAD_DE.md") + """
## 1. What goes where

Keep `Wordclock_Model.scad` (case + holders), `Wordclock_Model_PictureFrame.scad` (special model picture frame),
`Wordclock_Common.scad` (shared part of both models) and the folder `lang/` (`lang_all.scad` + all `lang_XX.scad`)
together (easiest: use the folder `models/`).
Optional `tools\\wordclock_tools.bat` (Windows, items 9/10: all fronts at once).

## 2. Choose the language

Customizer (Window > Customizer), group "Basis Settings", option `LANG`:

%s

Command line:

```
openscad -o front.stl -D 'LANG="GB"' -D 'PART="Front"' -D 'PRINT_ORIENT=true' Wordclock_Model.scad
```

(`PART` = `Front`, `Rear`, `Holder_Foot`, `Holder_Skadis`, `Holder_Wall`, `Holder_BasePlate`, `Letters`)
All fronts: `tools\\wordclock_tools.bat`, item 9 (or `python tools/export_fronts.py`, OpenSCAD is searched).

## 3. Important settings (Customizer)

`LANG`, `FONT`, `PART` (view: all side by side / assembled), `BUILD_*` (which parts are built),
`FRAME_WALL`, `DOT_DIAMETER`, `STROKE_VERTICAL`, `FRONT_SKIN`, `BACK_MOUNT`, `SCREW_TYPE`, `SCREW_HEAD`,
`STRAIN_RELIEF`, `CABLE_SLOT_REAR`, `CABLE_SLOT_FRAME`, `ESP_BOARD` (`CUSTOM_BOARD`), `WALL_SCREW_DIAMETER`.

Everything else (matrix, cap height, grid, filler cells, back/fastening, holders, `QUALITY`, `PRINT_ORIENT`)
is in the hidden config blocks of the file - change only if you know what you are doing.

`FONT` = font for the front and letters: Liberation Sans Bold (default, included with OpenSCAD),
Arial Bold or DejaVu Sans Bold. Languages with their own script (CN 中文, JP 日本語, KR 한국어,
rune variants) always use their own font - the `FONT` selection is then ignored.

### 3a. Installing fonts for other scripts (only CN, JP, KR)

For these languages an additional font must be installed (OpenSCAD finds it in the system):

| Language | Font | Download |
|---|---|---|
| CN 中文 | Noto Sans SC Bold | https://fonts.google.com/noto/specimen/Noto+Sans+SC |
| JP 日本語 | Noto Sans JP Bold | https://fonts.google.com/noto/specimen/Noto+Sans+JP |
| KR 한국어 | Noto Sans KR Bold | https://fonts.google.com/noto/specimen/Noto+Sans+KR |

Download: open the page, "Download" at the top right → unzip and install the TTF files
(Windows: right-click the TTF file → "Install for all users").
The rune variants need nothing extra: Windows 10/11 ships with Segoe UI Historic.
Without the installed font, OpenSCAD reports an error when the corresponding language is selected.

## 4. Export

F6 (render), F7 (STL). The export name is shown in the console: front `Frame_<LANG>_<font>`
(letters `..._Letters`), back `Rear`, holders `Holder_<name>` (supports `Holder_<name>_Support`),
PictureFrame `Pictureframe_<size>_<LANG>_<font>`.
Tip: OpenSCAD 2024/2025 with the backend "Manifold" renders in seconds.

## 5. New language in the model

Create `models/lang/lang_XX.scad`, add the include line and the entry in `LANGS` to `lang/lang_all.scad` and the
option `XX:Name` to the `LANG` line of `Wordclock_Model.scad` (see [`docs/LANG_SPEC.md`](../LANG_SPEC.md)).

## 6. Special model PictureFrame (own file Wordclock_Model_PictureFrame.scad)

Front plate for a deep picture frame (default: 231 mm picture size, 38 mm inner depth). Measure
`PICTUREFRAME_SIZE` and `PICTUREFRAME_FRAME_DEPTH`, `PICTUREFRAME_GLASS_THICKNESS` = thickness of the original
sheet if it stays in front (0 = without). ESP horizontal below the letter part (USB right, strain relief next to it).
Choose the fastening with `PICTUREFRAME_OWN_MOUNT`:

- `SCREW` = 4 screw blocks in the corners (countersunk wood screw into the frame wall) + keyhole hanger at the top
- `THIMBLES` = 4 blocks for one thumbtack each into the frame wall (e.g. chipboard frames) + keyhole hanger
- `NONE` = plate only, held by the back board / spacer frame and hanger of the picture frame

Command line:

```
openscad -o pf.stl -D 'LANG="GB"' -D 'PRINT_ORIENT=true' Wordclock_Model_PictureFrame.scad
```

(all languages: `tools\\wordclock_tools.bat`, item 10). FreeCAD: `Wordclock_Model_PictureFrame.FCMacro`.

---

Grid and grammar per language: [`docs/languages/LANG_<code>.txt`](../languages/)
""" % tab


# ------------------------------------------------------------------ language list in the base files
def base_list(langs, fmt, prefix):
    out = []
    for g in (0, 1, 2):
        ls = [d for d in langs if group(d["code"]) == g]
        if not ls:
            continue
        out.append("%s%s / %s:" % (prefix, GROUP_NAMES[g][1].capitalize(), GROUP_NAMES[g][0]))
        w = max(len(fmt % d["code"]) for d in ls)
        for d in ls:
            out.append("%s  %s  %s (%s)" % (prefix, (fmt % d["code"]).ljust(w), d["name"], d["version"]))
    return out


def update_block(rel, prefix, lines):
    p = os.path.join(ROOT, rel)
    if not os.path.isfile(p):
        return
    t = read(p)
    m = re.search(r"^([ \t]*%s[^\n]*LANGUAGES BEGIN[^\n]*\n)(.*?)(^[ \t]*%s[^\n]*LANGUAGES END)" % (re.escape(prefix.strip()),
                  re.escape(prefix.strip())), t, re.S | re.M)
    if not m:
        print("no LANGUAGES BEGIN/END block in %s" % rel)
        return
    new = t[:m.start(2)] + "\n".join(lines) + "\n" + t[m.end(2):]
    if new != t:
        with open(p, "w", encoding="utf-8", newline="\n") as f:
            f.write(new)
        print("written   %s (language list)" % rel)
    else:
        print("unchanged %s (language list)" % rel)


def md_table(langs, de):
    """Language table for README.md / README_DE.md (between <!-- LANGUAGES BEGIN --> and <!-- LANGUAGES END -->)."""
    head = ("| Code | Sprache | Art | Version | Standard-Standort |" if de else
            "| Code | Language | Kind | Version | Default location |")
    out = [head, "|---|---|---|---|---|"]
    for d in langs:
        g = group(d["code"])
        kind = {0: "Land" if de else "country", 1: "Dialekt" if de else "dialect", 2: "andere" if de else "other"}[g]
        ver = d["version"] + ((" bestätigt" if de else " confirmed") if d["tested"] else (" Grammatik unbestätigt" if de else " grammar unconfirmed"))
        out.append("| `%s` | %s | %s | %s | %s |" % (d["code"], d["name"], kind, ver, d.get("capital", "?")))
    for v in VAR:
        b = v["base"]
        out.append("| `%s` | %s | %s | %s | %s |" % (
            v["code"], v["name"], ("Schrift-Variante von `%s` (nur Front)" if de else "script variant of `%s` (front only)")
            % b["code"], ("Firmware von `%s`" if de else "firmware of `%s`") % b["code"], b.get("capital", "?")))
    return out


def update_md(rel, lines):
    p = os.path.join(ROOT, rel)
    if not os.path.isfile(p):
        return
    t = read(p)
    m = re.search(r"(<!-- LANGUAGES BEGIN[^\n]*-->\n)(.*?)(<!-- LANGUAGES END -->)", t, re.S)
    if not m:
        print("no LANGUAGES BEGIN/END block in %s" % rel)
        return
    new = t[:m.start(2)] + "\n".join(lines) + "\n" + t[m.end(2):]
    if new != t:
        with open(p, "w", encoding="utf-8", newline="\n") as f:
            f.write(new)
        print("written   %s (language table)" % rel)
    else:
        print("unchanged %s (language table)" % rel)


def main():
    langs = languages()
    VAR[:] = variants(langs)
    update_md("README.md", md_table(langs, False))
    update_md("README_DE.md", md_table(langs, True))
    update_block(os.path.join("arduino", "Wordclock", "config.h"), "//",
                 base_list(langs, '#define WC_LANG_FILE "src/wc_lang_%s.h"', "//   "))
    update_block(os.path.join("esphome", "wordclock_multi.yaml"), "#",
                 base_list(langs, "lang: !include wordclock_multi/lang/lang_%s.yaml", "#   "))
    cxx = shutil.which("g++") or shutil.which("clang++")
    if cxx:
        with tempfile.TemporaryDirectory() as tmp:
            for d in langs:
                try:
                    pv = Preview(d["code"], cxx, tmp)
                except RuntimeError as e:
                    print("ERROR %s: preview.cpp does not compile, docs/languages/LANG_%s.txt unchanged\n%s" % (d["code"], d["code"], e))
                    continue
                write("LANG_%s.txt" % d["code"], lang_file(d, pv))
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import make_masks                       # mask cache for render_fronts.py without compiler
        make_masks.main()
    else:
        print("no g++/clang++ found: docs/languages/LANG_XX.txt unchanged (only setup guides and LANGUAGES.txt are written)")
    for v in VAR:
        write("LANG_%s.txt" % v["code"], variant_file(v))
    write("LANGUAGES.txt", overview(langs))
    for folder, fn in (("arduino", setup_arduino), ("esphome", setup_esphome)):
        write(folder + "/README.md", fn(langs, False))
        write(folder + "/README_DE.md", fn(langs, True))
    for part, fn in (("FreeCAD", setup_freecad), ("OpenSCAD", setup_openscad)):
        write("SETUP_%s_EN.md" % part, fn(langs, False))
        write("SETUP_%s_DE.md" % part, fn(langs, True))


if __name__ == "__main__":
    main()
