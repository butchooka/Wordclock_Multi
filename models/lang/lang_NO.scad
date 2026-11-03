// lang_NO.scad - Wordclock 16x16, model language file NO (Norsk), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_NO.h (check: python3 tools/check_lang.py NO).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
LANG_NO = ["NO", "Norsk", [
    "*xKLOKKAxxxERxx*",
    "*xxFEMxxxxxTIxx*",
    "*xxxxKVARTxxxxx*",
    "*xOVERxxHEIxxxx*",
    "*xxxxxxxxxxPÅxx*",
    "*xxxxxHALVxxxxx*",
    "*xETTxxxxxxTOxx*",
    "*xTRExxxxFIRExx*",
    "*xxFEMxxxSEKSxx*",
    "*xSJUxxxxÅTTExx*",
    "*xxxNIxxxxxTIxx*",
    "*xxxxELLEVExxxx*",
    "*xxxxxTOLVxxxxx*",
    "x+x1234xMINUTTER",
    "xLUFTExxxxxALARM",
    "xBATTx||||||||||"
], "", ""];
