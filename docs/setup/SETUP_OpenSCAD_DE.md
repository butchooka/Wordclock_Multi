# Wordclock_Multi v1.0 - Einrichtung OpenSCAD

> Automatisch erzeugt von `tools/make_info.py` - nicht von Hand ändern.

[English](SETUP_OpenSCAD_EN.md) | **Deutsch**

## 1. Was wohin kopieren

`Wordclock_Model.scad` (Gehäuse + Halter), `Wordclock_Model_PictureFrame.scad` (Sondermodell Bilderrahmen),
`Wordclock_Common.scad` (gemeinsamer Teil beider Modelle) und den Ordner `lang/` (`lang_all.scad` + alle
`lang_XX.scad`) zusammen lassen (am einfachsten den Ordner `models/` benutzen).
Optional `tools\wordclock_tools.bat` (Windows, Punkt 9/10: alle Fronten auf einmal).

## 2. Sprache wählen

Customizer (Fenster > Customizer), Gruppe „Basis Settings“, Auswahl `LANG`:

| Code | Sprache | Customizer / -D | Datei / file |
|---|---|---|---|
| `DE` | Deutsch | `LANG = "DE"` | `models/lang/lang_DE.scad` |
| `GB` | English | `LANG = "GB"` | `models/lang/lang_GB.scad` |
| `CN` | 中文 | `LANG = "CN"` | `models/lang/lang_CN.scad` |
| `CZ` | Čeština | `LANG = "CZ"` | `models/lang/lang_CZ.scad` |
| `DK` | Dansk | `LANG = "DK"` | `models/lang/lang_DK.scad` |
| `ES` | Español | `LANG = "ES"` | `models/lang/lang_ES.scad` |
| `FR` | Français | `LANG = "FR"` | `models/lang/lang_FR.scad` |
| `GR` | Ελληνικά | `LANG = "GR"` | `models/lang/lang_GR.scad` |
| `HU` | Magyar | `LANG = "HU"` | `models/lang/lang_HU.scad` |
| `ID` | Bahasa Indonesia | `LANG = "ID"` | `models/lang/lang_ID.scad` |
| `IT` | Italiano | `LANG = "IT"` | `models/lang/lang_IT.scad` |
| `JP` | 日本語 | `LANG = "JP"` | `models/lang/lang_JP.scad` |
| `KR` | 한국어 | `LANG = "KR"` | `models/lang/lang_KR.scad` |
| `NL` | Nederlands | `LANG = "NL"` | `models/lang/lang_NL.scad` |
| `NO` | Norsk | `LANG = "NO"` | `models/lang/lang_NO.scad` |
| `PL` | Polski | `LANG = "PL"` | `models/lang/lang_PL.scad` |
| `PT` | Português | `LANG = "PT"` | `models/lang/lang_PT.scad` |
| `RO` | Română | `LANG = "RO"` | `models/lang/lang_RO.scad` |
| `SE` | Svenska | `LANG = "SE"` | `models/lang/lang_SE.scad` |
| `TR` | Türkçe | `LANG = "TR"` | `models/lang/lang_TR.scad` |
| `TZ` | Kiswahili | `LANG = "TZ"` | `models/lang/lang_TZ.scad` |
| `UA` | Українська | `LANG = "UA"` | `models/lang/lang_UA.scad` |
| `dialect_BAD` | Badisch | `LANG = "dialect_BAD"` | `models/lang/lang_dialect_BAD.scad` |
| `dialect_CH` | Schwizerdütsch | `LANG = "dialect_CH"` | `models/lang/lang_dialect_CH.scad` |
| `dialect_SWG` | Schwäbisch | `LANG = "dialect_SWG"` | `models/lang/lang_dialect_SWG.scad` |
| `EO` | Esperanto | `LANG = "EO"` | `models/lang/lang_EO.scad` |
| `VA` | Latina | `LANG = "VA"` | `models/lang/lang_VA.scad` |
| `scifi_HVA` | Valyrio | `LANG = "scifi_HVA"` | `models/lang/lang_scifi_HVA.scad` |
| `scifi_NAV` | Na'vi | `LANG = "scifi_NAV"` | `models/lang/lang_scifi_NAV.scad` |
| `scifi_QYA` | Quenya | `LANG = "scifi_QYA"` | `models/lang/lang_scifi_QYA.scad` |
| `scifi_TLH` | tlhIngan Hol | `LANG = "scifi_TLH"` | `models/lang/lang_scifi_TLH.scad` |
| `scifi_RUNE_DE` | Runen (Deutsch) | `LANG = "scifi_RUNE_DE"` | `models/lang/lang_scifi_RUNE_DE.scad` |
| `scifi_RUNE_GB` | Runes (English) | `LANG = "scifi_RUNE_GB"` | `models/lang/lang_scifi_RUNE_GB.scad` |

Kommandozeile:

```
openscad -o front.stl -D 'LANG="DE"' -D 'PART="Front"' -D 'PRINT_ORIENT=true' Wordclock_Model.scad
```

(`PART` = `Front`, `Rear`, `Holder_Foot`, `Holder_Skadis`, `Holder_Wall`, `Holder_BasePlate`, `Letters`)
Alle Fronten: `tools\wordclock_tools.bat`, Punkt 9 (oder `python tools/export_fronts.py`, OpenSCAD wird gesucht).

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

Frontplatte für einen tiefen Bilderrahmen (Standard: 231 mm Bildmaß, 38 mm Innentiefe = IKEA RIBBA 25x25;
IKEA SANNAHED 25x25: 249 mm / 44 mm). `PICTUREFRAME_SIZE`
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

(alle Sprachen und beide Rahmen RIBBA / SANNAHED: `tools\wordclock_tools.bat`, Punkt 10, Bambu-3MF Punkt 16). FreeCAD: `Wordclock_Model_PictureFrame.FCMacro`.

---

Raster und Grammatik je Sprache: [`docs/languages/LANG_<Code>.txt`](../languages/)
