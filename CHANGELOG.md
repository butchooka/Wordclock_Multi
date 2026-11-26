# Changelog – Wordclock_Multi

## 2026-11-26 - SCAD side-by-side view in print orientation
- `Wordclock_Model.scad`: `PART = "All_SideBySide"` now places every part in its print orientation on z = 0 (front
  face down, rear flat, holders standing, supports included); one export, then "Split to objects" in Bambu Studio.
  `PRINT_ORIENT = false` keeps the old unrotated layout. MakerWorld text: hint added (EN/DE).

## 2026-11-26 - MakerWorld export: Wemos rear again
- `export_fronts.py`: new `REAR_BOARDS` (ESP32C6, WemosD1); parts export (menu item 14) writes `Rear_ESP32C6.stl` and
  `Rear_WemosD1.stl` again. `make_3mf.py`: one rear plate per board ("Rear ESP32-C6 SuperMini", "Rear Wemos D1 mini
  ESP32"). PictureFrame stays ESP32-C6 only (`EXPORT_BOARDS`, other boards via `--board`).

## 2026-11-26 - MakerWorld folder moved to the top level
- MakerWorld outputs (texts, zips, `export/`, `export_3mf/`, `models/`) now in `makerworld/` (was `_private/makerworld/`,
  still ignored). Paths updated in `bundle_firmware.py`, `bundle_models.py`, `export_fronts.py`, `make_3mf.py`,
  `clean.py`, `wc_stamp.py`, `wordclock_tools.bat`, `Wordclock_Common.py` (FreeCAD export folder) and model comments.

## 2026-11-26 - Corner screws: direct screwing as default
- `Wordclock_Model.scad` / `.FCMacro`: default `SCREW_TYPE` is now `m3_coarse` (standard M3x0.5 screws, the ones used
  with inserts, 2.5 mm core hole, hand-tight); `insert` stays selectable in the Customizer.
- MakerWorld text (EN/DE): screw note with Customizer hint for heat set inserts.

## 2026-11-26 - Letters: oversize reduced per axis
- `Wordclock_Common.scad` (`glyph2d()`) / `Wordclock_Common.py` (`base_glyph()`): too wide characters (W, Ш, Ю) are
  only narrowed (full cap height, was reduced uniformly to 88 %), too high characters (Ä Ö Ü, accents) are only
  lowered (full width). Same cap height and baseline for W in DE, GB, NL, PL, ID, TZ, dialects, NAV.
- `tools/render_fronts.py`: same per-axis fitting in the renders (scaled glyphs drawn as tile and resized).

## 2026-11-23 - Light bleed: wall choice, support wall on the back, test print 3 x 3
- `CHAMBER_WALL_THICKNESS` (default 1.2 mm) customizable (section Front) in `Wordclock_Model` and
  `Wordclock_Model_PictureFrame` (`.scad` / `.FCMacro`): 0.8 / 1.2 / 1.65 mm = 2 / 3 / 4 lines of a 0.4 nozzle.
  1.2 mm needs the Arachne wall generator (classic: 2 lines + zigzag gap fill = light leak).
- `LETTER_THICKNESS` slider from 1.0 mm (was 1.6) in both models.
- Back (`Wordclock_Model.scad` / `.FCMacro`): new support wall (`MATRIX_SUPPORT`, on by default) along the edges
  (centre line 70 mm from the centre = under a chamber wall), arc around each corner block, rests on the rear of the
  matrix without pressure (`MATRIX_SUPPORT_GAP` 0). Before: 0.5 mm air and only the support ring; the old V4 clock had
  ribs. Open at the cable, keyhole, hook slots and at the free strips `MATRIX_FREE_STRIPS` (default top, left, right
  30 ... 60 mm from the frame wall: connectors / solder pads). The support ring above the ESP slot now has the same
  height (was 0.2 mm below the back of the matrix pocket).
- Support wall: `MATRIX_SUPPORT_JOIN` (on): the left / right free strips no longer cut the top and bottom wall, so
  the short pieces next to the keyhole and the cable (approx. 10 mm) are joined to the corner arcs (stiffer, easier
  to print).
- Support ring above the ESP slot: inner cut now through the full ring height (the higher ring had a 0.5 mm lid).
- `MATRIX_SUPPORT_GAP` 0 -> 0.3 mm (print test): support wall and ESP support ring 0.3 mm lower, the back sits closer to the matrix.
- `MATRIX_THICKNESS` 0.3 -> 0.15 mm (measured) in `Wordclock_Model` and `Wordclock_Model_PictureFrame` (`.scad` /
  `.FCMacro`): support wall and ring end exactly at the rear of the matrix, case 0.15 mm shallower.
- `Wordclock_TestPrint.scad`: default 3 x 3 cells (`ÄIW|MJx*Ö`), letter layer per cell row by row from
  `TEST_LETTER_MIN` 1.0 mm in `TEST_THICKNESS_STEP` 0.2 mm (1.0 ... 2.6 mm), `CHAMBER_WALL_THICKNESS` and
  `CHAMBER_HEIGHT` customizable, rim = chamber wall, small tab marks the top.
- Comparison with the old V4 clock (no light bleed): black PETG from layer 4 (3 white layers), chamber walls only
  0.8 mm, 14 mm chambers, ribs on the back -> the filament colour is the main factor.

## 2026-11-23 - Filler dots by default, letter thickness customizable, test print, C6-only exports
- Filler cells: default `FILLER = "dot"` (was `"auto"` = X for most languages) and `FILLER_DOT` 3.0 -> 4.0 mm in
  `Wordclock_Model` and `Wordclock_Model_PictureFrame` (`.scad` / `.FCMacro`). Both are now in the Customizer below
  the font (`dot`, `X`, `auto` = language default, dot 2 ... 7 mm). `render_fronts.py --filler` default `dot`.
- `LETTER_THICKNESS` customizable again (1.6 ... 3.0 mm, 0.2 mm steps; main model: section Front, PictureFrame: Basis
  Settings) - raise it if light shines through into the neighbouring cells.
- New `models/Wordclock_TestPrint.scad`: small test print (default 4 x 2 cells, approx. 40 x 20 mm) with the same light
  chambers and letter pockets as the front, characters freely selectable (`TEST_CHARS`, default `IJÍÄWMx|`).
  `Wordclock_Common.scad`: new module `glyph_solid()` (one cell), used by `glyph_solids()` and the test print.
  `export_fronts.py Parts` (item 14) also exports `TestPrint.stl`.
- `bundle_models.py` (item 8) bundles `Wordclock_Model.scad` again, plus `Wordclock_TestPrint.scad` (MakerWorld Customizer).
- Exports only for the ESP32-C6 SuperMini: new `EXPORT_BOARDS = ["ESP32C6"]` in `export_fronts.py` (rear and PictureFrame
  STL, 3MF); other boards via the Customizer or `--board WemosD1`.
- `make_3mf.py`: 3MF of the fully printed clock renamed `Wordclock_<LANG|all|...>.3mf` -> `frame_Wordclock_...3mf`.
- MakerWorld text: photo hint removed, printing without colour change or change between layer 2 and 3, dark filament for
  the rear part, test print, ready-made files C6 only (rest via Customizer).

## 2026-11-23 - Letter layer fixed 1.6 mm
- New `LETTER_THICKNESS = 1.6` (fixed) in all models: the dark layer with the cut-out letters must not shine
  through. Front plate = `LETTER_THICKNESS + FRONT_SKIN` (`FRONT_THICKNESS` in `Wordclock_Model`,
  `PICTUREFRAME_THICKNESS` in PictureFrame, 2.0 mm with the default skin 0.4 mm). `PICTUREFRAME_THICKNESS` is no
  longer adjustable: Customizer slider, preset in `Wordclock_Model_PictureFrame.json`, `export_fronts.py --thickness`
  and the question in `wordclock_tools.bat` item P removed.

## 2026-11-21 - Arduino: "Forget Wi-Fi" instead of factory reset
- Web interface, section System: the button "Factory reset" is replaced by "Forget Wi-Fi". It deletes only SSID and
  password, the clock restarts as hotspot, all other settings (colours, location, night mode, wiring ...) are kept.
- `Wordclock.ino`: `handleReset()` -> `handleWifiForget()`, endpoint `/api/reset` -> `/api/wifi_forget` (POST).
- `UI_JSON` of all languages: keys `reset` / `q_reset` -> `wifi_forget` / `q_wifi_forget`; `webpage.h` rebuilt.

## 2026-11-21 - Front plate 2 mm
- `FRONT_THICKNESS` default 1.6 -> 2.0 mm in `Wordclock_Model` (`.scad` / `.FCMacro`). PictureFrame already uses
  `PICTUREFRAME_THICKNESS = 2.0`, unchanged.
- Keyhole: `KEYHOLE_HEAD_DIAMETER` / `PICTUREFRAME_KEYHOLE_HEAD_DIAMETER` 9.0 -> 11.0 mm (screw heads up to approx. 10.5 mm).

## 2026-11-21 - Strain relief anchored to the lower edge
- Back (`Wordclock_Model.scad` / `.FCMacro`): the strain relief pedestal now starts at a fixed `STRAIN_RELIEF_FROM_EDGE = 16` mm
  above the lower edge (just above the rear U-slot, height unchanged) instead of board length + `STRAIN_RELIEF_GAP` below
  the ESP slot. Reason: with short boards (C6 SuperMini, XIAO) the USB plug almost touched the pedestal. The
  watermark stays centred between ESP slot and pedestal. Parameter `STRAIN_RELIEF_GAP` removed (PictureFrame unchanged).

## 2026-11-19 - Clearer skip messages of the export tools
- `wc_stamp.py`: new `Info.check()` gives the reason with the state. `export_fronts.py` / `make_3mf.py` print
  `up to date (built 2026-11-19 09:20), skipped` instead of `unchanged, skipped`, and on a rebuild the reason, e.g.
  `changed: Wordclock_Model.scad, rebuilding`, `new, building`, `Frame_DE.stl missing, rebuilding`, `forced, rebuilding`.
  Reason: in item 13 the STL step said "unchanged" although the model had changed - the STL were already rebuilt by an
  earlier item (14 / 9 / 10), "unchanged" meant "already up to date".

## 2026-11-19 - Watermark on the back moved
- Back (`Wordclock_Model.scad` / `.FCMacro`): the watermark now sits automatically centred between the open end of
  the ESP slot and the strain relief (gap = board length + `STRAIN_RELIEF_GAP`) instead of 30 mm below the upper edge.
  Reason: with the Wemos D1 mini ESP32 the wider semicircle support covered part of the text. Parameter
  `WATERMARK_BACK_FROM_TOP` removed.

## 2026-11-18 - Light chambers 10 mm
- `CHAMBER_HEIGHT` default 15 -> 10 mm in `Wordclock_Model.scad` / `.FCMacro` and `Wordclock_Model_PictureFrame.scad` /
  `.FCMacro` (front 5 mm shallower, shorter print). Reason: with 120° LEDs (10 mm pitch) only ~11 % of the light hit the
  letter directly at 15 mm, ~89 % hit the walls and shone through light filament into the neighbour cells. At 10 mm
  ~26 % reach the letter directly, the wall-to-front ratio drops from ~8:1 to ~3:1, the letter stays evenly lit.

## 2026-11-17 - Frame wall 3.7 mm
- `FRAME_WALL` default 2.7 -> 3.7 mm (frame 1 mm wider all around, outer size +2 mm) in `Wordclock_Model.scad` and `Wordclock_Model.FCMacro`, picture frame (`Wordclock_Model_PictureFrame.scad` / `.FCMacro`) and the customizer parameter sets (`Wordclock_Model.json`). Reason: thin wall + rounded outer corners vs. square inner corners gave uneven wall thickness and a rough outer surface.

## 2026-11-16 - MakerWorld exports: all_ files per group, no wall holder
- `make_3mf.py`: the all_ files are split into groups (`ALL_GROUPS`): `Wordclock_all.3mf` (languages and dialects),
  `Wordclock_scifi_all.3mf` (Klingon, Na'vi, Quenya, Valyrian), `Wordclock_runes_all.3mf` (runes DE / GB), the same for
  the picture frame (`Pictureframe_<FRAME>_scifi_all_<BOARD>.3mf` ...) - room for more languages below 36 plates.
- `Holder_Wall` is no longer exported (STL / 3MF): the keyhole hanger in the rear does the same. The part stays in the model.
- `wordclock_tools.bat`: `A` no longer builds the single 3MF per language (items 12 / 16); 12 and 16 ask for the
  languages (Enter = all).

## 2026-11-16 - MakerWorld exports: board variants, single holder plates, short names
- Rear and PictureFrame plate per board: `ESP32C6` (ESP32-C6 SuperMini) and `WemosD1` (Wemos D1 mini ESP32), the ESP
  slot differs. `export_fronts.py`: `Rear_ESP32C6.stl` / `Rear_WemosD1.stl` (was `Rear.stl`),
  `Pictureframe_<FRAME>_<LANG>_<BOARD>.stl`, new option `--board`.
- File names without the font (shorter): `Frame_<LANG>.stl`, `Wordclock_<LANG>.3mf`, `Wordclock_all.3mf`,
  `Pictureframe_<FRAME>_<LANG>_<BOARD>.3mf`, `Pictureframe_<FRAME>_all_<BOARD>.3mf` (one all_ file per frame and board,
  62 plates would exceed the Bambu Studio limit of 36). The font stays part of the base data (rebuild on change).
- `make_3mf.py`, Wordclock 3MF: one plate per rear (160 x 160 mm, two do not fit on the P2S bed), every holder on its
  own plate (centred). In `Wordclock_all.3mf` the holders stay on one plate when there would be more than 36 plates.
- PictureFrame 3MF: prime tower off (no room next to the large plate; a little white after the filament change is fine).
- STEP instead of STL dropped: OpenSCAD has no STEP export, a STEP of the mesh brings no quality and is much larger,
  the 3MF always holds a mesh.

## 2026-11-16 - PictureFrame: compact keyhole hanger without bridges
- Hanger of the own mount (SCREW / THIMBLES) is now a real keyhole: put the head of the wall screw through the round
  hole, slide the clock down. It is attached directly to the rim of the matrix (more stable) instead of reaching up to
  the upper plate edge, and still reaches the rear edge of the frame. Hanger 14.3 x 16 mm instead of 20 mm x whole top
  margin. New `PICTUREFRAME_KEYHOLE_DEPTH` (default 0 = up to the rear edge of the frame; smaller = shorter hanger,
  the wall screw then stands out correspondingly further).
- The webs are only as far apart as the screw head needs (`PICTUREFRAME_KEYHOLE_HEAD_DIAMETER` + 0.5 mm),
  `PICTUREFRAME_KEYHOLE_WIDTH` removed. Underside of the flange chamfered 45 degrees from the webs to the slot edge:
  prints without bridges / overhangs, countersunk heads fit the chamfer.
- The wall screw head (outer edge) has to stand out approx. 5.5 ... 6.2 mm (was 3.3 ... 4.0 mm), see log / echo.

## 2026-11-16 - No version numbers, language status confirmed / unconfirmed
- Version numbers removed everywhere (file headers, README titles, LANG_SPEC, tools, ESPHome comment, firmware: `fwVersion()` is now `Wordclock_<LANG>`, `WC_VERSION` removed).
- Language status in the header of `wc_lang_XX.h` / `lang_XX.yaml` / `lang_XX.scad` is now `confirmed` or `unconfirmed` (was v1.0 / v0.9);
  `tools/make_info.py` reads it from there. README tables: column Status (confirmed / unconfirmed, DE: bestätigt / unbestätigt).
- `lang_PL.scad` was still marked v0.9, now confirmed like the firmware files.

## 2026-11-13 - PictureFrame: slim hanger, support pillars, Customizer cleaned up
- Fix: with a bigger board (e.g. Wemos D1 mini ESP32) the keyhole hanger of the own mount (SCREW / THIMBLES) reached
  out of the plate at the top (231 mm frame). The big hanger block is replaced by a slim hanger at the top centre: two
  thin webs and a flange flush with the rear edge of the frame with a slot open downwards (put the clock onto the shank
  of a wall screw). It only uses the rim and the top margin and never reaches out of the plate, whatever the board.
  `PICTUREFRAME_KEYHOLE_TRAVEL`, `_HEAD_HEIGHT`, `_HOLLOW` and `_RIBS` removed, `PICTUREFRAME_KEYHOLE_WIDTH` 40 -> 20 mm.
- Original fastening (NONE): new `PICTUREFRAME_PILLARS` (Customizer, default on) = 4 hollow support pillars beside the
  matrix, exactly as long as `PICTUREFRAME_FRAME_DEPTH` (rear panel of the frame rests on them), diameter
  `PICTUREFRAME_PILLAR_DIAMETER` (8 mm), wall `PICTUREFRAME_PILLAR_WALL` (1.2 mm, hidden).
- Default fastening is now `PICTUREFRAME_OWN_MOUNT = "NONE"` (original fastening with pillars).
- Customizer: section Front (`FRAME_WALL`, `DOT_DIAMETER`, `STROKE_VERTICAL`, `FRONT_SKIN`) and `PICTUREFRAME_TOL`
  moved to [Hidden]. FreeCAD macro identical (same parameters and geometry). SETUP_OpenSCAD DE/EN updated.

## 2026-11-13 - MakerWorld outputs: all_ 3MF, flat firmware zips, only PictureFrame SCAD
- `make_3mf.py`: all_ variant per clock with all languages, one plate each: `Wordclock_all_<font>.3mf` (normal clock,
  before `Wordclock_ALL_<font>.3mf`, plus the rear/holder plates) and new `--pictureframe --all[-only]` ->
  `Pictureframe_RIBBA_all_<font>.3mf` / `Pictureframe_SANNAHED_all_<font>.3mf`; the PictureFrame 3MF per language
  are named like their STL, without `Wordclock_`: `Pictureframe_<FRAME>_<LANG>_<font>.3mf`. Plates are named after the language
  ("DE - Deutsch", PictureFrame "RIBBA DE - Deutsch"), also in the 3MF per language.
- `wordclock_tools.bat`: item 13 writes all three all_ files, now also part of `A`.
- `bundle_firmware.py`: `Wordclock_ESPHome.zip` / `Wordclock_Arduino.zip` without the folder `esphome/` / `arduino/`
  (files resp. `Wordclock_XX/` folders at the top level of the zip).
- `bundle_models.py`: only `Wordclock_Model_PictureFrame.scad` is bundled for MakerWorld (no combined `.FCMacro`, no
  normal case SCAD); old bundles in `_private/makerworld/models/` are removed on the next run.

## 2026-11-13 - Desktop word clock (easter egg)
- New `docs/wordclock_desktop.html`: the time in words like the header of the Arduino web interface, as one static
  HTML file (all languages, approx. 110 KB, no server, no internet). System time, language from the browser /
  system (`?lang=XX` overrides, also dialects and sci-fi). One line per row of the clock grid, centred, size fits
  the window. Gear at the top right (shown on mouse move): single minutes, letter colour, size (saved per
  browser); shows the link with parameters for an iframe (`min`, `color`, `size`, also `bg`, `gear=0`).
  Easter egg: arrow keys ← → switch through all languages.
- New `tools/make_desktop_clock.py`: compiles the time grammar of every `wc_lang_XX.h` with g++ (same code as the
  firmware) and writes the HTML; part of menu item 1 in `wordclock_tools.bat`. README / README_DE: hint.

## 2026-11-11 - Language PL: grammar confirmed (v1.0)
- Polski (PL) grammar and spelling confirmed by BaroszD (native speaker): status v0.9 -> v1.0 in `wc_lang_PL.h`
  (Arduino and ESPHome copy), `lang_PL.yaml`, `LANG_PL.txt`, README / README_DE (intro and language table).

## 2026-11-11 - PictureFrame: named frames RIBBA / SANNAHED, Bambu 3MF
- `export_fronts.py`: PictureFrame plates are exported per frame of `PF_FRAMES` and named type first, so the
  files of one kind are grouped: `Pictureframe_RIBBA_<LANG>_<font>.stl` (231 / 38 mm, default of the model, before
  `<LANG>_Pictureframe_231_<font>.stl`) and new `Pictureframe_SANNAHED_<LANG>_<font>.stl` (IKEA SANNAHED 25x25:
  glass 249 mm, depth 44 mm). New option `--frame RIBBA|SANNAHED` (default: all). Special case `--size/--depth/...`:
  `custom/Pictureframe_<size>x<depth>_<LANG>_<font>.stl`.
- `make_3mf.py --pictureframe [--frame ...]`: one Bambu Studio project per language and frame
  (`Wordclock_Pictureframe_<FRAME>_<LANG>_<font>.3mf`); the plate takes the place and settings of the front of
  `template_P2S.3mf` (no template of its own).
- `wordclock_tools.bat`: new item 16 (Bambu 3MF PictureFrame), part of `A`; item 10 exports both frames.

## 2026-11-10 - Models: wider frame, thicker letter layer (less light bleed)
- `FRAME_WALL` default 2.2 -> 2.7 mm (+0.5 mm per side) in `Wordclock_Model` and `Wordclock_Model_PictureFrame`
  (`.scad` / `.FCMacro`), so the LEDs no longer shine through the outer frame wall. Front grows by 1 mm in width/height.
- `FRONT_THICKNESS` default 1.4 -> 1.6 mm in `Wordclock_Model` (`.scad` / `.FCMacro`): the dark letter layer is one
  0.2 mm layer higher (1.0 -> 1.2 mm at `FRONT_SKIN` 0.4). Dark filament for the front is still required.

## 2026-11-10 - Arduino: web interface switchable to English
- New switch "Web interface in English" (System, setting `uiEn`, saved in Preferences) in every language; the label
  is fixed English so it can be found in any language, hidden when the clock language is GB. After switching the
  page reloads. Also applies to the server pages of the captive portal (`tr()`).
- New `arduino/Wordclock/wc_ui_en.h`: includes `src/wc_lang_GB.h` with its `WC_LANG` renamed and only uses its
  `UI_JSON` (approx. 7 KB flash, nothing extra for GB). Grid and time words of the clock are unchanged, ESPHome unchanged.
- `/api/config` and `/api/save`: key `uiEn` (0/1). `webpage.h` regenerated.

## 2026-11-10 - Frame model: watermark only on the back
- `Wordclock_Model.scad` / `.FCMacro`: watermark engraving on the inner upper frame wall of the front removed,
  watermark remains only on the front side of the back (rear). Header/config comments adjusted.

## 2026-11-10 - Watermark depth 0.2 mm
- `WATERMARK_DEPTH` default 0.4 -> 0.2 mm (1 layer) in `Wordclock_Common.scad`, `Wordclock_Model.FCMacro` and
  `Wordclock_Model_PictureFrame.FCMacro`; header comments adjusted.

## 2026-11-09 – Renders: full display set, file names without version
- `render_fronts.py` renders a second set `*_full` per front: time plus VENT (orange), ALARM (red), battery half full
  (5 bars, white) and both temperature dots on the default scale (outside 8 °C = yellow, inside 24 °C = orange),
  i.e. the default colours of the firmware (`COL_DEF`), without the extra words. Overview PNG and GIF also as `_full`.
  Option `--set both|normal|full` (default both) replaces `--features`. `render_mask.cpp`: shared `set_features()`.
- File names without version: `Wordclock_Render_<LANG>_<hhmm>[_full].png`, `Wordclock_Render_ALL_<hhmm>[_full].png/.gif`,
  `Wordclock_Ticker.gif`. Old `*_v1.0_*` files are removed by the next complete run (menu 5).
- README / README_DE: links adjusted, GIF row shows all fronts light (normal) and dark (`_full`).
- Mask cache `render_masks.json.xz` is rebuilt by menu 1 (with g++) or 11; it is only used without a compiler.

## 2026-11-09 – Grids: no touching words that are lit together
- Checked all languages for words that are lit at the same time and touch in a row without a free cell
  (time words, extra words, status words, battery bars; script `tools/logs/claude/adjacency.cpp`).
  Found and fixed (only grid positions, no grammar change):
  - GB: TWENTY|HELLO (row 3) – TWENTY one cell to the left: `*xxTWENTYxHELLO*`.
  - VA: VIGINTI|QUINQUE (row 9, :25/:35) – rows 9/10 now `*VIGINTIxDECEMx*` / `*QUINQUEDIMIDIA*`
    (QUINQUE and DIMIDIA touch but are never lit together).
  - PT: CARGA|battery bars (row 16) – CARGA moved to column 1: `CARGAx||||||||||`.
- `lang_scifi_RUNE_GB.scad` regenerated (`make_variants.py`), ESPHome copies synced (`sync_src.py`).
  Docs, renders, single files and model exports of GB, VA, PT, RUNE_GB still have to be regenerated.

## 2026-11-06 – Ready-made Arduino firmware removed
- The precompiled `.bin` files (`arduino/compiled/`, incl. `build_info.json`) are no longer part of the project:
  the build was very slow. Arduino: compile in the Arduino IDE (`arduino/Wordclock` or `arduino/single_Language/`).
- `tools/build_firmware.py` and menu item 7 of `wordclock_tools.bat` removed (numbers 8-15 unchanged, `A` without 7).
  README, setup guides (`make_info.py`), single-file READMEs (`bundle_firmware.py`) and `wc_stamp.py` adjusted.
  The `wc_build.h` hook in `config.h` stays (harmless without the tool).

## 2026-11-06 – Arduino web page: copy HTTP examples
- HTTP examples (card "HTTP control" and the `/api/set` example in "Additional displays") each have a copy button 📋
  (Clipboard API, fallback `execCommand('copy')` because the clock runs on plain http). Click on the command selects it
  completely.
- Fix: `status()` rewrote the example texts every 2 s and cleared a running selection, now only written when changed.
- `webpage.h` regenerated (`tools/make_webpage.py`).

## 2026-11-06 – Start: easter egg instead of the prefix
- As long as the time is unknown (start, no Wi-Fi / no Home Assistant yet) the grid shows the extra words (easter egg)
  of the language instead of the prefix (ES IST, IT IS ...), also when the switch is off (`wc_render_clock` in
  `wc_core.h`). CZ and PL (no prefix) no longer stay dark. No language file changed.
- Hotspot open (Arduino: no Wi-Fi saved or Wi-Fi not reachable; ESPHome: Wi-Fi not connected for 60 s = default
  `ap_timeout` of the fallback hotspot): the extra words pulse blue, otherwise static in the time colour.
  ESPHome: new globals `wifi_lost_since`, `wifi_ap_on`.

## 2026-11-06 – Docs: setup guides as Markdown
- `make_info.py` writes the setup guides as Markdown: Arduino -> `arduino/README.md` (EN) and `README_DE.md` (DE),
  ESPHome -> `esphome/README.md` / `README_DE.md`, FreeCAD and OpenSCAD -> `docs/setup/SETUP_*_EN/DE.md`.
  Language tables as Markdown tables, links to the other language version and to `docs/languages/`.
- The old `docs/setup/SETUP_*.txt` were moved to `_private/Archiv/`. README, LANG_SPEC and the tools menu adjusted.

## 2026-11-06 – Tools: skip unchanged outputs
- New `tools/wc_stamp.py`: every slow tool writes the base data of each output into an info file next to it
  (SHA-256 and date of the input files, parameters, program versions). In the next run only outputs whose base data
  changed are built again - the content decides, not the file date.
  - `build_firmware.py` (menu 7) -> `arduino/compiled/build_info.json`: sketch files without the other languages,
    language file, FQBN, pin, arduino-cli and ESP32 core version.
  - `export_fronts.py` (menu 9, 10, 14, P) -> `export_info.json` in the output folder: model, `Wordclock_Common.scad`,
    `lang_all.scad`, language file, -D values, OpenSCAD version, font file.
  - `make_3mf.py` (menu 12, 13) -> `export_3mf/3mf_info.json`: STL files used, template, `make_3mf.py`. The STL
    files are no longer exported again in every run, only the changed ones.
  - `render_fronts.py` (menu 5) -> `docs/render*/render_info.json`: whole run skipped when `src/*.h`,
    `models/lang/*.scad`, the render scripts, options and the installed fonts did not change.
- All again: option `--force` of the tools, `WC_FORCE=1`, or `wordclock_tools.bat A F` / `wordclock_tools.bat 7 F`.

## 2026-11-06 – Tools: backup clean
- `wordclock_tools.bat` item `B` (Backup clean): lists and, after a confirmation, removes the large generated
  outputs so the folder is slim for a manual backup: `_private/makerworld/export/` (incl. `custom/`), `export_3mf/`,
  `models/`, `*.zip`, downloaded fonts in `tools/logs/fonts/`, STL/fonts/PNG in `tools/logs/claude/`,
  `models/export/`, `output/`. Files tracked by git are never removed. All can be rebuilt with menu 6, 8-10, 12-15, P.
- `clean.py` has the new option `--backup` for this.

## 2026-11-06 – Tools: other picture frame, write only on a change
- `wordclock_tools.bat` item `P`: asks size, inner depth, tolerance, plate thickness, glass, fastening, languages and
  quality of another picture frame and exports the plates to `_private/makerworld/export/custom/`
  (`<LANG>_Pictureframe_<size>x<depth>_<font>.stl`). `export_fronts.py PictureFrame` has the new options `--size`,
  `--depth`, `--tol`, `--thickness`, `--glass`, `--mount` (checked against the Customizer limits).
- Generated files are only written when their content changes (fewer changes in git): `bundle_firmware.py`,
  `bundle_models.py`, `render_fronts.py` (PNG/GIF), `make_font.py`, `build_firmware.py` (.bin). Already so before:
  `make_info.py`, `make_variants.py`, `make_webpage.py`, `make_masks.py`, `sync_src.py`.

## 2026-11-06 – 3D print: foot, supports, Bambu 3MF
- Back: export name `Rear` (before `Holder_Rear`, FreeCAD `Rear_freecad`) - it can be used on its own.
- Foot (`Holder_Foot`) new: base plate and two struts (max. 45 degrees, approx. 34) up to one pad per hook, no arm,
  no cross bar, no cable groove / plug passage (the cable runs freely between the struts). Prints without supports
  apart from the hook undersides. Parameters `FOOT_STRUT_DEPTH`, `FOOT_PAD_WIDTH`, `FOOT_STRUT_INSET` replace
  `FOOT_ARM_*`, `FOOT_PLUG_*`, `FOOT_GUSSET_*`, `FOOT_BAR_THICKNESS`.
- New `PRINT_SUPPORTS` (+ `SUPPORT_GAP_Z` 0.2 = one layer, `SUPPORT_GAP_XY`, `SUPPORT_WALL`): break-away support tubes
  under the hooks of every holder as own parts `Holder_<name>_Support` (same print coordinates as the holder; foot:
  standing on its base plate). `check_models.py` checks them (2 tubes, no contact with the holder).
- `export_fronts.py`: binary STL (`--export-format binstl`, approx. 5x smaller; `--ascii` = old format), new part
  `Parts` = Rear, holders and supports (menu item 14).
- New `tools/make_3mf.py` (menu 12 / 13): Bambu Studio 3MF per language from `tools/template_P2S.3mf`, or one file
  with all fronts (one plate each, named after the front). Output `_private/makerworld/export_3mf/`.
- `make_3mf.py` exports all STL files again before every run (current model; `--reuse` only for tests), output also
  in `tools/logs/make_3mf_log.txt`, steps 1-4 with progress.
- Fonts: fronts of languages with their own script (CN, JP, KR, runes) are named after the font really used
  (`Frame_KR_NotoSansKRBold`, before always `..._LiberationSansBold`). Before the export `export_fronts.py` /
  `make_3mf.py` check that OpenSCAD finds every needed font (system fonts, "Install for all users"); a missing font
  is named in the log and nothing is exported (no fronts with empty boxes any more).
- New `tools/install_fonts.py` (menu 15, first step of `A`): checks the fonts of all fronts, downloads missing
  Noto Sans SC/JP/KR Bold (static OTF, github.com/notofonts/noto-cjk) to `tools/logs/fonts/` and installs them for
  all users (one UAC prompt); `--check` = only check.
- Fix: `check_models.py` stopped with `NameError: FREECAD_NAMES`.
- `wordclock_tools.bat`: every action shows its name, start and end time, `A` counts [n/12]; item 1 shows its steps.

## 2026-11-06 – Version 1.0, cleanup before the release
