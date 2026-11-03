# Changelog – Wordclock_Multi

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
