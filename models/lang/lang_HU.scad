// lang_HU.scad - Wordclock 16x16, model language file HU (Magyar), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_HU.h (check: python3 tools/check_lang.py HU).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
// Note: Ő (O with double acute, U+0150) is not Latin-1; its metrics are in METRICS_LIBERATION_BOLD /
// METRICS_DEJAVU_BOLD of Wordclock_Model.scad (Latin Extended-A block).
LANG_HU = ["HU", "Magyar", [
    "*MOSTxxxÖTxxTÍZ*",
    "*PERCCELxxxMÚLT*",
    "*xxMÚLVAxxxFÉLx*",
    "*xxHÁROMNEGYEDx*",
    "*xxTIZENKETTŐxx*",
    "*xxxTIZENEGYxxx*",
    "*HÁROMxxxxxNÉGY*",
    "*xÖTxxHATxxHÉTx*",
    "*NYOLCxxxKILENC*",
    "*xxxxxxTÍZxxxxx*",
    "*xxÓRAxxxxxVANx*",
    "*xxxxxxxxxxxxxx*",
    "*xAZxIDŐxPÉNZxx*",
    "x+x1234xxPERCxxx",
    "SZELLŐZÉSxxRIADÓ",
    "xAKKUx||||||||||"
], "", ""];
