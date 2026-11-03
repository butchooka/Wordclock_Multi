// lang_PT.scad - Wordclock 16x16, model language file PT (Português), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_PT.h (check: python3 tools/check_lang.py PT).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
LANG_PT = ["PT", "Português", [
    "*xÉxxSÃOxxxUMAx*",
    "*xDUASxxxTRÊSxx*",
    "*QUATROxxxCINCO*",
    "*xSEISxxSETExxx*",
    "*xxOITOxxNOVExx*",
    "*xDEZxxxxONZExx*",
    "*xxxMEIO-DIAxxx*",
    "*xxMEIA-NOITExx*",
    "*xHORASxxOLÁxxx*",
    "*xxExxxxxMENOSx*",
    "*xVINTExExCINCO*",
    "*DEZxUMxQUARTOx*",
    "*xxxxxxMEIAxxxx*",
    "x+x1234xMINUTOSx",
    "xAREJARxxALARMEx",
    "xCARGA||||||||||"
], "", ""];
