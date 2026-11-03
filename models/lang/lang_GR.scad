// lang_GR.scad - Wordclock 16x16, model language file GR (Ελληνικά), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_GR.h (check: python3 tools/check_lang.py GR).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
// Note: all letters are Greek capitals (U+0391..U+03A9, also the ones that look Latin: Α Ε Η Ι Κ Μ Ν Ο Ρ Τ Υ).
// Liberation Sans Bold, Arial Bold and DejaVu Sans Bold contain them, so the font stays "" (setting SCHRIFT).
// Their metrics are in METRIK_LIBERATION_BOLD / METRIK_DEJAVU_BOLD of Wordclock_Model.scad, FreeCAD measures the glyphs itself.
LANG_GR = ["GR", "Ελληνικά", [
    "*ΗxΩΡΑxΕΙΝΑΙxxx*",
    "*ΜΙΑxΔΥΟxΤΡΕΙΣx*",
    "*ΤΕΣΣΕΡΙΣxΠΕΝΤΕ*",
    "*ΕΞΙxΕΠΤΑxΟΚΤΩx*",
    "*xΕΝΝΙΑxxΔΕΚΑxx*",
    "*ΕΝΤΕΚΑxxΔΩΔΕΚΑ*",
    "*xxΚΑΙxxxΠΑΡΑxx*",
    "*ΕΙΚΟΣΙxxΠΕΝΤΕx*",
    "*ΔΕΚΑxxΤΕΤΑΡΤΟx*",
    "*xxxxxΜΙΣΗxxxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xΤΑxΠΑΝΤΑxΡΕΙx*",
    "*xxxxxxxxxxxxxx*",
    "x+x1234xxΛΕΠΤΟΑx",
    "ΑΕΡΑΣxΣΥΝΑΓΕΡΜΟΣ",
    "xΜΠΑΤx||||||||||"
], "", ""];
