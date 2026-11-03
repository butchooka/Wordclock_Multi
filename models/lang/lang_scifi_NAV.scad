// lang_scifi_NAV.scad - Wordclock 16x16, model language file scifi_NAV (Na'vi), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_scifi_NAV.h (check: python3 tools/check_lang.py scifi_NAV).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
// Note: the apostrophe ' ('AWVE) is a letter of its own (one cell, printed high like in the font) and Ì
// (Latin-1) is one cell; both have metrics in METRIK_LIBERATION_BOLD / METRIK_DEJAVU_BOLD of Wordclock_Model.scad.
LANG_scifi_NAV = ["scifi_NAV", "Na'vi", [
    "*xxKRRLIKxLUxxx*",
    "*x'AWVExxMUVExx*",
    "*xPXEYVExTSÌVEx*",
    "*xMRRVExxxPUVEx*",
    "*xKIVExxVOLVExx*",
    "*VOLAWVExVOMUVE*",
    "*VOPEYVExVOSÌVE*",
    "*xSÌxMExPXExTSÌ*",
    "*xMRRxPUxVOLAWx*",
    "*xMUNxPEYxSÌNGx*",
    "*xxMRRxFUxHINxx*",
    "*xxOELxxNGATIxx*",
    "*xxxxKAMEIExxxx*",
    "x+x1234xTRRPXÌVI",
    "xHUFWExxxxHRRAPx",
    "TSWALx||||||||||"
], "", ""];
