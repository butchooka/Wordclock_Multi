// lang_scifi_QYA.scad - Wordclock 16x16, model language file scifi_QYA (Quenya), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_scifi_QYA.h (check: python3 tools/check_lang.py scifi_QYA).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
// Fictional language (code scifi_ + short code), Latin capitals with Ë Á É Í Ó Ú (Latin-1, metrics present).
LANG_scifi_QYA = ["scifi_QYA", "Quenya", [
    "*xSÍxNÁxCANASTA*",
    "*YUCAINENxLEMPË*",
    "*PERTAxxAPAxNÓx*",
    "*xMINËxxxATTAxx*",
    "*NELDËxxxxCANTA*",
    "*xLEMPËxxENQUËx*",
    "*OTSOxxxxxTOLTO*",
    "*xNERTËxxCAINEN*",
    "*MINQUËxYUNQUËx*",
    "*xxxxxxxxxxxxxx*",
    "*xPEDOxMELLONxx*",
    "*xxxAxMINNOxxxx*",
    "*xxxxxxxxxxxxxx*",
    "xxxxx+x1234xxxxx",
    "xSÚRËxxxxxxROMBA",
    "xTUOxx||||||||||"
], "", ""];
