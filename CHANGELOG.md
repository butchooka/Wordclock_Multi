# Changelog – Wordclock_Multi

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
