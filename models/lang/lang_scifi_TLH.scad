// lang_scifi_TLH.scad - Wordclock 16x16, model language file scifi_TLH (tlhIngan Hol), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_scifi_TLH.h (check: python3 tools/check_lang.py scifi_TLH).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file, filler]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
//   filler: default of FILLER for this language, used with FILLER = "auto" in the models ("" = X); here "dot"
//   (a capital X looks heavy between the many lower case letters)
// Mixed case: q and Q, h and H ... are different letters and are printed as they are (lower case smaller, as in
// the font); the apostrophe ' is a letter of its own (one cell). Lower case "x" is always a filler (no letter here).
// OpenSCAD places the lower case letters exactly with the metrics for a-z (core package core-metrics_EO-GR-x).
LANG_scifi_TLH = ["scifi_TLH", "tlhIngan Hol", [
    "*xDaHxxxxxxpagh*",
    "*wa'maHxcha'maH*",
    "*xwa'xcha'xwejx*",
    "*xloSxvaghxjavx*",
    "*xSochxchorghxx*",
    "*xxHutxxvatlhxx*",
    "*wa'maHxcha'maH*",
    "*xwejmaHxloSmaH*",
    "*xvaghmaHxvaghx*",
    "*xxxxxxrepxxxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xxHeghlu'meHxx*",
    "*xxQaQxjajvamxx*",
    "x+x1234xxxtupxxx",
    "xSuSxxxxghuHmoHx",
    "xHoSxx||||||||||"
], "", "", "dot"];
