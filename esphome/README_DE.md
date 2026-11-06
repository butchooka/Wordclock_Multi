# Wordclock_Multi v1.0 - Einrichtung ESPHome

> Automatisch erzeugt von `tools/make_info.py` - nicht von Hand ändern.

[English](README.md) | **Deutsch**

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

| Code | Sprache | wordclock_multi.yaml (packages:) | Gerät/name | Fallback-Hotspot |
|---|---|---|---|---|
| `DE` | Deutsch | `lang: !include wordclock_multi/lang/lang_DE.yaml` | `wortuhr` | `Wortuhr Fallback` |
| `GB` | English | `lang: !include wordclock_multi/lang/lang_GB.yaml` | `wordclock` | `Wordclock Fallback` |
| `CN` | 中文 | `lang: !include wordclock_multi/lang/lang_CN.yaml` | `wenzizhong` | `WenziZhong Fallback` |
| `CZ` | Čeština | `lang: !include wordclock_multi/lang/lang_CZ.yaml` | `slovnihodiny` | `SlovniHodiny Fallback` |
| `DK` | Dansk | `lang: !include wordclock_multi/lang/lang_DK.yaml` | `ordur` | `Ordur Fallback` |
| `ES` | Español | `lang: !include wordclock_multi/lang/lang_ES.yaml` | `reloj` | `Reloj Fallback` |
| `FR` | Français | `lang: !include wordclock_multi/lang/lang_FR.yaml` | `horloge` | `Horloge Fallback` |
| `GR` | Ελληνικά | `lang: !include wordclock_multi/lang/lang_GR.yaml` | `roloilexeon` | `RoloiLexeon Fallback` |
| `HU` | Magyar | `lang: !include wordclock_multi/lang/lang_HU.yaml` | `szoora` | `SzoOra Fallback` |
| `ID` | Bahasa Indonesia | `lang: !include wordclock_multi/lang/lang_ID.yaml` | `jamkata` | `JamKata Fallback` |
| `IT` | Italiano | `lang: !include wordclock_multi/lang/lang_IT.yaml` | `orologio` | `Orologio Fallback` |
| `JP` | 日本語 | `lang: !include wordclock_multi/lang/lang_JP.yaml` | `mojidokei` | `MojiDokei Fallback` |
| `KR` | 한국어 | `lang: !include wordclock_multi/lang/lang_KR.yaml` | `geuljasigye` | `GeuljaSigye Fallback` |
| `NL` | Nederlands | `lang: !include wordclock_multi/lang/lang_NL.yaml` | `woordklok` | `Woordklok Fallback` |
| `NO` | Norsk | `lang: !include wordclock_multi/lang/lang_NO.yaml` | `ordklokke` | `Ordklokke Fallback` |
| `PL` | Polski | `lang: !include wordclock_multi/lang/lang_PL.yaml` | `zegarslowny` | `ZegarSlowny Fallback` |
| `PT` | Português | `lang: !include wordclock_multi/lang/lang_PT.yaml` | `relogio` | `Relogio Fallback` |
| `RO` | Română | `lang: !include wordclock_multi/lang/lang_RO.yaml` | `ceascucuvinte` | `CeasCuCuvinte Fallback` |
| `SE` | Svenska | `lang: !include wordclock_multi/lang/lang_SE.yaml` | `ordklocka` | `Ordklocka Fallback` |
| `TR` | Türkçe | `lang: !include wordclock_multi/lang/lang_TR.yaml` | `kelimesaati` | `KelimeSaati Fallback` |
| `TZ` | Kiswahili | `lang: !include wordclock_multi/lang/lang_TZ.yaml` | `saamaneno` | `SaaManeno Fallback` |
| `UA` | Українська | `lang: !include wordclock_multi/lang/lang_UA.yaml` | `slovohodynnyk` | `SlovoHodynnyk Fallback` |
| `dialect_BAD` | Badisch | `lang: !include wordclock_multi/lang/lang_dialect_BAD.yaml` | `wortuhrle` | `Wortuhrle Fallback` |
| `dialect_CH` | Schwizerdütsch | `lang: !include wordclock_multi/lang/lang_dialect_CH.yaml` | `wortuehrli` | `Wortuehrli Fallback` |
| `dialect_SWG` | Schwäbisch | `lang: !include wordclock_multi/lang/lang_dialect_SWG.yaml` | `wortuehrle` | `Wortuehrle Fallback` |
| `EO` | Esperanto | `lang: !include wordclock_multi/lang/lang_EO.yaml` | `vorthorlogo` | `VortHorlogo Fallback` |
| `VA` | Latina | `lang: !include wordclock_multi/lang/lang_VA.yaml` | `horologium` | `Horologium Fallback` |
| `scifi_HVA` | Valyrio | `lang: !include wordclock_multi/lang/lang_scifi_HVA.yaml` | `valyrio` | `Valyrio Fallback` |
| `scifi_NAV` | Na'vi | `lang: !include wordclock_multi/lang/lang_scifi_NAV.yaml` | `liukrr` | `LiuKrr Fallback` |
| `scifi_QYA` | Quenya | `lang: !include wordclock_multi/lang/lang_scifi_QYA.yaml` | `quettalume` | `QuettaLume Fallback` |
| `scifi_TLH` | tlhIngan Hol | `lang: !include wordclock_multi/lang/lang_scifi_TLH.yaml` | `mutlhaq` | `Mutlhaq Fallback` |

Schrift-Varianten (nur Front, gleiche Firmware wie die Basissprache - diese hier wählen): `scifi_RUNE_DE` = `DE`, `scifi_RUNE_GB` = `GB`

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
