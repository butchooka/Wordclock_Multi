// lang_scifi_HVA.scad - Wordclock 16x16, model language file scifi_HVA (Valyrio), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_scifi_HVA.h (check: python3 tools/check_lang.py scifi_HVA).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
// Fictional language (code scifi_ + short code), Latin capitals with macron Ā Ē Ī Ō Ȳ (metrics present).
// Ȳ (BȲRE) is missing in some Arial versions: for FreeCAD choose Liberation Sans Bold or DejaVu Sans Bold
// (FONT_AUTO otherwise takes another installed font that contains all characters).
LANG_scifi_HVA = ["scifi_HVA", "Valyrio", [
    "*SĪRxMĒRExLANTA*",
    "*HĀRExTŌMAxBȲRE*",
    "*IZULAxSĪKUDAxx*",
    "*xJĒNQAxxxVŌREx*",
    "*AMPAxAMPĀxTŌMA*",
    "*AMPAxLANTĒPSAx*",
    "*AMPĀxLANTEPSĀx*",
    "*HĀRĒPSAxRYTSAS*",
    "*xxxxxxxHĀREPSĀ*",
    "*IZULĒPSAxxxxxx*",
    "*xxxxxxIZULEPSĀ*",
    "*xTŌMĒPSAxxxxxx*",
    "*xxxxxxxTŌMEPSĀ*",
    "xxxxx+x1234xxxxx",
    "xJELMĀZMAxPERZYS",
    "xĀEKSx||||||||||"
], "", ""];
