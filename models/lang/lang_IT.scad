// lang_IT.scad - Wordclock 16x16, model language file IT (Italiano), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_IT.h (check: python3 tools/check_lang.py IT).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
LANG_IT = ["IT", "Italiano", [
    "*SONOxLExÈxCIAO*",
    "*L'UNAxDUExxxxx*",
    "*xTRExQUATTROxx*",
    "*CINQUExxSEIxxx*",
    "*xSETTExxxOTTOx*",
    "*NOVExxDIECIxxx*",
    "*xxxUNDICIxxxxx*",
    "*xMEZZOGIORNOxx*",
    "*xxMEZZANOTTExx*",
    "*xxExxxxMENOxxx*",
    "*xVENTICINQUExx*",
    "*xUNxxQUARTOxxx*",
    "*DIECIxxxMEZZAx*",
    "x+x1234xMINUTIOx",
    "xAERARExALLARMEx",
    "xBATTx||||||||||"
], "", ""];
