// lang_KR.scad - Wordclock 16x16, model language file KR (한국어 / Korean), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_KR.h (check: python3 tools/check_lang.py KR).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file, filler]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
//   filler: default of FILLER for this language, used with FILLER = "auto" in the models ("" = X); here "dot"
// Note: Hangul needs its own font. Noto Sans KR (Google Fonts, SIL Open Font License) must be installed:
//   https://fonts.google.com/noto/specimen/Noto+Sans+KR - the static file static/NotoSansKR-Bold.ttf.
// Without metrics the syllables are only roughly centred (adjust FREI_GROESSE if needed). Fillers: dot (field 6).
LANG_KR = ["KR", "한국어", [
    "*xx지금은xxx오전x오후x*",
    "*xx자정xxxxxx정오xx*",
    "*xx한xx두xx세xx네xx*",
    "*xx다섯xxxxxx여섯xx*",
    "*xx일곱xxxxxx여덟xx*",
    "*xx아홉xxxxxx열xxx*",
    "*xx열한xxxxxx열두xx*",
    "*xxxxx시xxx반xxxx*",
    "*xx이xx삼xx사xx오xx*",
    "*xxxx십xxxx오xxxx*",
    "*xxxxxxx분xxxxxx*",
    "*xxxxx입니다xxxxxx*",
    "*xxx시간은xx금이다xxx*",
    "x+x1234xx분xxxxxx",
    "xxx환기xxxxxx알람xxx",
    "x배터리xx||||||||||"
], "Noto Sans KR:style=Bold", "NotoSansKR-Bold.ttf", "dot"];
