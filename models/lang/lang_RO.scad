// lang_RO.scad - Wordclock 16x16, model language file RO (Română), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_RO.h (check: python3 tools/check_lang.py RO).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
// Note: Ă and Ș (S with comma below, U+0218) have metrics in METRIK_LIBERATION_BOLD / METRIK_DEJAVU_BOLD of
// Wordclock_Model.scad (exact placement).
LANG_RO = ["RO", "Română", [
    "*ESTExORAxxxUNU*",
    "*DOUĂxTREIxxOPT*",
    "*PATRUxxxxCINCI*",
    "*ȘASExxxxxȘAPTE*",
    "*NOUĂxxxxxxZECE*",
    "*xxUNSPREZECExx*",
    "*xDOUĂSPREZECEx*",
    "*ȘIxxxxxxxxFĂRĂ*",
    "*DOUĂZECIxxxxȘI*",
    "*CINCIxxxxxZECE*",
    "*xxxUNxSFERTxxx*",
    "*xxxJUMĂTATExxx*",
    "*xTIMPULxZBOARĂ*",
    "x+x1234xMINUTExx",
    "AERISIRExxALARMĂ",
    "xBATxx||||||||||"
], "", ""];
