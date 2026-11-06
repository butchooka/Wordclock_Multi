# Changelog – Wordclock_Multi

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
