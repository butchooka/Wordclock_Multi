# Changelog – Wordclock_Multi

## 2026-11-04 – ESPHome check of all languages, YAML fixes
- Fix: `c_off: Off` (GB, scifi_*) and `No` (ES) were read as bool by YAML ("Must be string, got <class 'bool'>"),
  now quoted. Also fixed: `lang_code: NO` (Norway, bool too) and `t_sw_extra` in KR (text after the closing quote,
  invalid YAML).
- New `tools/check_esphome.bat` -> `tools/check_esphome.py`, result `output/check_esphome_log.txt`: step 1 (Python
  only) checks every `lang_XX.yaml` (valid YAML with line number, all values strings, select options unique);
  step 2 runs `esphome config` for every language with a generated copy of `wordclock_multi.yaml` (dummy secrets)
  in `output/esphome_check/`, if ESPHome is installed (`pip install esphome`).

## 2026-11-04 – ESPHome: device name in the main file, firmware single files for MakerWorld
- `wordclock_multi.yaml`: `name` / `friendly_name` are now substitutions of the main file and `esphome: name: ${name}`
  is set there too. Renaming in the ESPHome dashboard works (it only accepts a name defined in the main file).
  Several clocks: one copy of `wordclock_multi.yaml` per clock with its own `name`. The name no longer follows the
  language package (default `wortuhr` / `Wortuhr`; `name` in `lang_XX.yaml` is no longer used).
- New `tools/bundle_firmware.bat` -> `tools/bundle_firmware.py`: per language ESPHome `wordclock_multi_XX.yaml`
  (main file + core + language as inline packages) + `wordclock_multi_XX.h` (all C++), Arduino
  `Wordclock_XX/Wordclock_XX.ino` (config.h inserted, language fixed) + `wordclock_bundle.h`, README.txt and two zips
  in `output/makerworld/`. The C++ stays in one .h each (ESPHome needs a file for `includes:`, the Arduino IDE
  would generate wrong prototypes for header code inside the .ino).
- Setup texts (`make_info.py`), README adjusted.

## 2026-11-04 – Additional displays: colour "off" instead of switches
- ESPHome `core.yaml`: the colour selects of VENT, ALARM, BATTERY, temperature outside and inside have the new first
  option `${c_off}` (display off); the switches `sw_temp`, `sw_vent`, `sw_alarm`, `sw_battery` are removed.
  Temperature outside / inside can now be switched off separately. Single minutes and extra words stay switches.
- Entity names of these selects renamed to "Show ..." (DE "Anzeige LÜFTEN", "Anzeige Temperatur Außen", ...), so
  "Colour time" / "Farbe Uhrzeit" is the only colour entity of the clock and is listed before them in Home Assistant
  (alphabetical order). New substitution `c_off` in all `lang_XX.yaml`, `t_sw_temp/vent/alarm/battery` removed.
  After the update: the renamed selects start with their default colours, the old switch entities can be deleted
  in Home Assistant, automations on the old entity IDs must be adjusted.
- `wc_core.h`: `show_temp` -> `show_tout` / `show_tin`.
- Arduino: colour selection 11 = off (first entry for groups 1-5 in the web interface, label `off_`), checkboxes
  "Temperature dots", "Show VENTILATE / ALARM / BATT" removed (also from `ui_json`). HTTP: `col_vent=off` etc.;
  `show_temp/vent/alarm/battery` still work (0 = off, 1 = default colour if off). Saved switches are migrated
  once (switch off -> colour off), default for a new clock: additional displays off as before.

## 2026-11-04 – ESPHome: time zone from Home Assistant, fallbacks
- `core.yaml`: time from `platform: homeassistant` (id `ha_time`, without `timezone`): time AND time zone come from
  Home Assistant. The time zone of the last sync is saved (`globals` `tz_saved`, `ParsedTimezone`, needs a current
  ESPHome) and set again at boot. SNTP stays as fallback for the time (only UTC, the saved time zone stays).
- `timezone:` removed from all `lang_XX.yaml` and from the override comment in `wordclock_multi.yaml`.
- New `ha_timeout_min` (default 5) in `wordclock_multi.yaml`: after that many minutes without API connection
  ALARM, VENT, BATTERY and temperature dots are off until Home Assistant is connected again.
- VENT / ALARM only light up with a valid value (`has_state()`), unavailable entities no longer keep the old state.
- Setup texts (`make_info.py`, `SETUP_ESPHome_*.txt`), README, LANG_SPEC adjusted. Arduino variant unchanged.

## 2026-11-04 – Models: shared part in Wordclock_Common, single files for MakerWorld
- New `models/Wordclock_Common.scad`: everything both SCAD models had twice (font config, language include, font
  metrics, watermark settings, resolution, font selection, grid dimensions, common checks, helper functions, letters
  `glyph2d` / `glyph_solids`, watermark `wm_cut`, ESP slot `esp_rails_local`). Both models `include` it after their
  Customizer parameters; all moved values were [Hidden] already, the Customizer is unchanged. Geometry unchanged
  (code lines identical, PictureFrame now also checks the row length of the grid).
- New `models/Wordclock_Common.py`: shared code of both FCMacros (font config, log/warn, geometry helpers, font search,
  letters, watermark, languages, grid check / letter cuts, ESP slot, export folder), loaded by the macros at the marked
  place (`# >>> include` ... `# <<< include`). Must lie next to the macros (or in the FreeCAD macro folder).
- New `tools/bundle_models.bat` -> `tools/bundle_models.py`: writes both SCAD files (with common part and all language
  files inserted) and both FCMacros (with `Wordclock_Common.py` inserted) as single files to `models/export/bundle/`.
- `tools/check_params.py` reads the common files too (and ignores `include` lines); `tools/check_lang.py` reads the
  font metrics from `Wordclock_Common.scad`; `tools/make_info.py`: setup texts name the common files.

## 2026-11-04 – SCAD: English option values
- Both SCAD files: `FONT = "Frei"` -> `"Custom"`, `QUALITY` `Vorschau / Normal / Fein` -> `Preview / Normal / Fine`;
  `Wordclock_Model.scad`: `PART` `Alle_Nebeneinander / Alle_Montage` -> `All_SideBySide / All_Assembled`;
  PictureFrame: Customizer labels of `PICTUREFRAME_OWN_MOUNT` in English (before "OWN MOUNT REISSZWECKE").
- Font metric tables `METRIK_*` -> `METRICS_*` (SCAD, lang files, check_lang.py, check_params.py, LANG_SPEC.md).
- `tools/export_fronts.bat`: `QUALITY=Fine`. Old values in saved Customizer presets / own calls must be changed.

## 2026-11-04 – Parameter comparison SCAD <-> FCMacro
- New `tools/check_params.bat` -> `tools/check_params.py` (Python only, result `output/check_params_log.txt`): compares
  the settings of both model pairs. ERROR on different values or an FCMacro value outside the Customizer options,
  WARN for one-sided parameters or different customizable / fine tuning status. Known one-sided names (colours, font
  metrics, export, font search) and conventions (SCAD -1 / -999 = None in the macro) are listed in the script.
- Both FCMacros: `BUILD_LETTERS` and `FONT_IN_NAME` moved to the fine tuning (as [Hidden] in SCAD). check_params: ALL OK.
- `Wordclock_Model.scad`: `WALL_SCREW_DIAMETER` as option list in the Customizer (hole 3.5 ... 6.5 mm for 3 ... 6 mm
  screws, default unchanged 4.5). check_params now also warns about customizable text/number fields without option
  list or slider.

## 2026-11-04 – Models: fixed numbers in modules named
- All 4 model files (SCAD + FCMacro, same names): strain relief `STRAIN_RELIEF_LENGTH` (12), `STRAIN_RELIEF_SIDE_WALL` (2.5),
  `STRAIN_RELIEF_TUNNEL_SKIN` (1.6), `CABLE_TIE_CLEARANCE` (0.2), `CABLE_GROOVE_CLEARANCE` (0.1).
- `Wordclock_Model.scad` / `.FCMacro`: semicircle support `ESP_SUPPORT_RADIUS_EXTRA` (10), `ESP_SUPPORT_DISTANCE` (3),
  `ESP_SUPPORT_WALL` (1.6), `ESP_SUPPORT_CLEARANCE` (0.8); holder plates `HOLDER_PLATE_EXTRA_WIDTH` (26 = 16 + 10);
  SCAD only: `LAYOUT_GAP` (20) for the "Alle_Nebeneinander" view. All hidden, values unchanged.

## 2026-11-04 – FreeCAD macros: user settings structured like the SCAD Customizer, descriptive names
- `Wordclock_Model.FCMacro` / `Wordclock_Model_PictureFrame.FCMacro`: settings block split as in the SCAD files – on top
  the user settings (same groups as the Customizer: basis, export, front, back and fastening, ESP slot, cable, holders /
  PictureFrame), below the fine tuning per module (front, ESP slot, back, keyhole, holders, foot, hooks, watermark, font).
  Comments completed and aligned. Values unchanged.
- `Wordclock_Model.FCMacro`: new options as in SCAD: `BACK_MOUNT` ("both" / "keyhole" / "holders", replaces `BACK_KEYHOLE`),
  `SCREW_TYPE` (sets `SCREW_BORE_DIAMETER`), `SCREW_HEAD` ("countersunk" / "flat"), `CABLE_SLOT_REAR` / `CABLE_SLOT_FRAME`.
  Both FCMacros: `ESP_BOARD = "custom"` with `CUSTOM_BOARD`.
- Parameters renamed in SCAD and FCMacro (names stay identical): `MATRIX` → `MATRIX_SIZE`, `PITCH` → `LED_PITCH`,
  `THICKNESS` → `FRONT_THICKNESS`, `MATRIX_CLEAR` / `BOARD_CLEAR` / `HOOK_CLEAR` → `..._CLEARANCE`, `STANDOFF` → `BOARD_STANDOFF`,
  `STRAIN_BELOW` → `STRAIN_RELIEF_GAP`, `BP_SLOT_H` → `CABLE_SLOT_REAR_HEIGHT`, `FRAME_SLOT_H` → `CABLE_SLOT_FRAME_DEPTH`,
  `CONE_8MM` / `CONE_MAT` → `CONE_CLEARANCE` / `CONE_MATERIAL`, `CABLE_SINK` → `CABLE_GROOVE_SINK`, `SLOT_FROM_EDGE` →
  `ESP_SLOT_FROM_EDGE`, `BACK_KH_FROM_TOP` / `BACK_KH_EDGE` → `KEYHOLE_FROM_TOP` / `KEYHOLE_TOP_EDGE`, `KEYHOLE_HEAD_D` /
  `KEYHOLE_SLOT_W` → `KEYHOLE_HEAD_DIAMETER` / `KEYHOLE_SLOT_WIDTH`, `MOUNT_GAP` → `SKADIS_SKIP_HOLE`, `SK_HOOK_WIDTH` →
  `HOOK_WIDTH`, `SK_HOOK_HEIGHT` → `SKADIS_HOOK_HEIGHT`, `SKADIS_LIP` → `SKADIS_LIP_LENGTH`, `HEAD_DIAMETER` →
  `SCREW_HEAD_DIAMETER`, `BASE_HEIGHT` → `BASEPLATE_HEIGHT`, `FONT_FREI` / `FREI_GROESSE` → `FONT_CUSTOM` / `FONT_CUSTOM_SCALE`,
  `WM_*` → `WATERMARK_TEXT_1/2`, `WATERMARK_HEIGHT_1/2`, `WATERMARK_LINE_GAP`, `WATERMARK_DEPTH`, `WATERMARK_BACK_FROM_TOP`,
  `WATERMARK_FONT_FILE`. `Wordclock_Model_PictureFrame.scad`: unused `THICKNESS` and `MATRIX_SLACK` removed.

## 2026-11-04 – PictureFrame: ESP slot on the watermark side
- `Wordclock_Model_PictureFrame.scad` / `.FCMacro`: automatic `PICTUREFRAME_ESP_X` puts the slot below the clip lip on the
  watermark side (−X), outer face of the stop flush with the rim (stop at −OUT / 2 + 2 = −80.5 mm); before, the stop sat at
  X = 0. Strain relief moves along, the USB cable now runs towards the middle (centre of gravity closer to the middle).
- Holder hooks (`HOOK_FIT_WIDTH/HEIGHT`, `HOOK_TIP_RADIUS`): test print fits.

## 2026-11-04 – FreeCAD macros with the OpenSCAD parameter names, model check complete
- `Wordclock_Model.FCMacro` and `Wordclock_Model_PictureFrame.FCMacro`: parameters renamed as in the SCAD files, e.g.
  `CORNER_R` → `CORNER_RADIUS`, `STROKE_W/H` → `STROKE_WIDTH/HEIGHT`, `GRID_HEIGHT/WALL` → `CHAMBER_HEIGHT` /
  `CHAMBER_WALL_THICKNESS`, `MATRIX_T` → `MATRIX_THICKNESS`, `RAIL_W` / `LIP` → `RAIL_WIDTH` / `RAIL_LIP`,
  `CABLE_D`, `TIE_W/T` → `CABLE_DIAMETER`, `CABLE_TIE_WIDTH/THICKNESS`, `SCREW_D`, `SCREW_BORE_D`, `WALL_SCREW_D`,
  `HEAD_D` → `..._DIAMETER`, `HOOK_*`, `SK_*`, `SLOT_PLAY_*`, `BP_TOL` → `BACKPLATE_TOLERANCE`, `CAV` → `BACK_CAVITY`,
  `BP_T` → `BACK_THICKNESS`, `BUILD_BACK/FOOT/SKADIS/WALL/BASE` → `BUILD_REAR` / `BUILD_HOLDER_*`. Values unchanged.
  Unused `USB_PLUG_LEN` and the unused `QMessageBox` imports removed.
- FreeCAD macros headless (`freecadcmd`): no dialogs any more without GUI (`App.GuiUp`); before, `FONT_FILE = None`
  ended with "QWidget: Must construct a QApplication".
- Model check: FreeCAD comparison works again; SCAD ↔ FCMacro equal (main model and PictureFrame SCREW / THIMBLES /
  NONE, volume ≤ 0.2 % = tessellation). Fit check incl. front OK. New reference `models/check_models_baseline.json`
  (back +0.7 %, wall holder with one centred hole +0.9 %, PictureFrame hollow keyhole hanger −7.3 %).

## 2026-11-03 – New export names (OpenSCAD = FreeCAD, FreeCAD with "_freecad")
- Front `Frame_<LANG>_<FONT>`, letters `Frame_<LANG>_<FONT>_Letters`, back `Holder_Rear`, holders `Holder_Foot`,
  `Holder_Skadis`, `Holder_Wall`, `Holder_BasePlate`; PictureFrame `<LANG>_Pictureframe_<PICTUREFRAME_SIZE>_<FONT>`
  (letters `..._Letters`). The FreeCAD macros use the same names plus `_freecad`, no `Wordclock_` prefix any more.
- FreeCAD macros: English part names (before `Rueckwand`, `Fuss`, `Wandhalter`, `Basisplatte`, `Buchstaben`),
  `EXPORT = "stl"`, back through holes `SCREW_D = 3.6` (as in OpenSCAD).
- `tools/export_fronts.bat`: new names, `PF_SIZE` for the PictureFrame; `models/check_models.py` reads the `_freecad`
  files; OpenSCAD prints the export name in the console again; setup texts (`tools/make_info.py`) updated.

## 2026-11-03 – PictureFrame as FreeCAD macro
- New `models/Wordclock_Model_PictureFrame.FCMacro` (counterpart of `Wordclock_Model_PictureFrame.scad`, same
  parameter names `PICTUREFRAME_*`): plate, light grid, clips, ESP slot, strain relief, watermark, keyhole hanger
  (hollow with ribs) and the fastening choice `PICTUREFRAME_OWN_MOUNT` = `"SCREW"` (screw blocks), `"THIMBLES"`
  (tabs for office thumbtacks / Reißzwecken) or `"NONE"` (plate only).

## 2026-11-03 – PictureFrame: clips connected to the rim
- `Wordclock_Model_PictureFrame.scad`: the matrix clips now start 0.5 mm inside the rim wall. Before, they only
  touched the rim and 4 of them were exported as loose bodies (check: "5 separate bodies").

## 2026-11-03 – Strain relief distance follows the board length
- All models (OpenSCAD frame, FreeCAD macro, PictureFrame): the gap between the open end of the ESP slot and the strain
  relief pedestal is now board length + `STRAIN_BELOW` (2.5 mm). Before: exactly the board length (frame model, the
  macro parameter was not used) or a fixed 28 mm (PictureFrame, too short for the Wemos D1 mini).
  `USB_PLUG_LENGTH` (SCAD) and `STRAIN_PED_UP` (macro) removed (no longer used).

## 2026-11-03 – New defaults, battery bars, export names
- Firmware (Arduino + ESPHome): default brightness day 40 % (before 60 %), night 1 % (before 8 %); fixed night times
  default 22:00 – 07:00 (before 06:30). Saved settings are kept, only new devices / a reset use the new values.
- Battery bars now have the same colour as the BATTERY word (no more red / blue / green by level).
- FreeCAD macro: default `EXPORT = "stl"` (before "step"); export names without version (`Wordclock_Rueckwand`
  instead of `Wordclock_Rueckwand_v2.0`, front `Wordclock_Front_<LANG>_<font>`).
- Back: through holes for the 4 screws 3.6 mm (before 3.4 mm), OpenSCAD + FreeCAD macro.

## 2026-11-03 – Strain relief: cable tie through the pedestal
- Back of the frame model (OpenSCAD + FreeCAD macro): the cable tie tunnel now runs across the cable through the base
  of the strain relief pedestal (as in the PictureFrame model). Before, it ran along the cable inside the cable groove
  and did not hold the tie. The cable groove now lies half sunk in the top of the pedestal (pedestal 7.6 mm high,
  1.6 mm wall between tunnel and groove). No cut in the back.
- Cable tie width is 3.8 mm in all models (narrow ties approx. 2.5 ... 3.6 mm; before 6.0 mm in the frame model).

## 2026-11-03 – Animated GIF of all fronts
- `tools/render_fronts.py` (and `render_fronts.bat`) now also writes `Wordclock_Render_v2.0_ALL_<hhmm>.gif` to
  `docs/render/` and `docs/render/dark/`: all fronts one after another, 1 second each, endless loop, language name
  below (options `--gif-size`, default 480 px, 0 = off, and `--gif-ms`). Both GIFs are shown in the README overview.

## 2026-11-03 – Wall mount with one screw
- The wall mount (`Holder_Wall`) of the OpenSCAD model now has one centred countersunk screw hole instead of two
  (x = ±15 mm), the same as the FreeCAD macro. The clock hangs on the hooks; the plate is held by one wall screw.

## 2026-11-03 – Holder hooks fit better
- The hooks of the holders (foot, Skadis, wall, base plate) are 0.2 mm narrower and 0.2 mm lower (`HOOK_FIT_WIDTH`,
  `HOOK_FIT_HEIGHT`; hanging point unchanged), the end piece is 1 mm deeper (`HOOK_LIP_DEPTH` 5 mm) and its upper
  corners are rounded (`HOOK_TIP_RADIUS`), so the hooks pass through the slots of the back more easily. The back is
  unchanged (slot play now as parameters `SLOT_PLAY_WIDTH` / `SLOT_PLAY_HEIGHT`). Foot v2 test print OK.

## 2026-11-03 – Language codes with prefix
- Dialects now use the prefix `dialect_` (`dialect_BAD`, `dialect_CH`, `dialect_SWG`), fictional languages and script
  variants `scifi_` instead of `_x_` (`scifi_HVA`, `scifi_NAV`, `scifi_QYA`, `scifi_TLH`, `scifi_RUNE_DE`, `scifi_RUNE_GB`).
  The code is the same everywhere: file names, `LANG = "..."`, `WC_LANG_FILE`, ESPHome `lang_code`, C++ namespaces.
  Existing configurations: change `config.h` / `wordclock_multi.yaml` to the new file name.

## 2026-11-03 – Repository structure
- The project folder is now the repository root (no extra `Wordclock_Multi/` level).
- All Windows double-click files moved to `tools/` (`build_firmware.bat`, `check_languages.bat`, `render_fronts.bat`,
  `check_models.bat`, `export_fronts.bat`).
- `info/` split into `docs/languages/` (LANG_XX.txt, LANGUAGES.txt) and `docs/setup/` (SETUP_*.txt);
  `LANG_SPEC.md` moved to `docs/`.
- Front previews are written to `docs/render/` (before: `models/export/render/`).
- Logs and firmware builds go to `output/` (not in the repository).

## 2026-11-02 – v2.0
- Merge of the user model variant into `Wordclock_Multi`, new foot v2, PictureFrame model (OpenSCAD).
