// lang_ID.scad - Wordclock 16x16, model language file ID (Bahasa Indonesia), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_ID.h (check: python3 tools/check_lang.py ID).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
LANG_ID = ["ID", "Bahasa Indonesia", [
    "*SEKARANGxxxJAM*",
    "*SETENGAHxxSATU*",
    "*DUAxTIGAxEMPAT*",
    "*xLIMAxxxxENAMx*",
    "*TUJUHxxDELAPAN*",
    "*xxxSEMBILANxxx*",
    "*SEPULUHSEBELAS*",
    "*LEWATxxxKURANG*",
    "*SEPEREMPATxDUA*",
    "*SEPULUHxxxLIMA*",
    "*PAGIxxxxxSIANG*",
    "*SORExxxxxMALAM*",
    "*SELAMATxDATANG*",
    "x+x1234xxMENITxx",
    "xVENTILASIxALARM",
    "DAYAxx||||||||||"
], "", ""];
