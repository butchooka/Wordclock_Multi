// lang_JP.scad - Wordclock 16x16, model language file JP (日本語 / Japanese), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_JP.h (check: python3 tools/check_lang.py JP).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file, filler]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans JP:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansJP-Bold.ttf" (searched in the system fonts)
//   filler: default of FILLER for this language, used with FILLER = "auto" in the models ("" = X); here "dot"
// Note: kanji/kana need their own font. Noto Sans JP (Google Fonts, SIL Open Font License) must be installed:
//   https://fonts.google.com/noto/specimen/Noto+Sans+JP - the static file static/NotoSansJP-Bold.ttf.
// Without metrics the characters are only roughly centred (adjust FONT_CUSTOM_SCALE if needed). Fillers: dot (field 6).
// Closed counters (e.g. in 時, 電, 金) need the same front construction as KR (characters with inner islands).
LANG_JP = ["JP", "日本語", [
    "*xx今はxx正午前x午後xx*",
    "*xx零xxx一xxx二xxx*",
    "*xx三xxx四xxx五xxx*",
    "*xx六xxx七xxx八xxx*",
    "*xx九xxx十一xxxxxx*",
    "*xxxxx時xxx半xxxx*",
    "*xx二xx三xx四xx五xx*",
    "*xxxx十xxxx五xxxx*",
    "*xxxxxxx分xxxxxx*",
    "*xxxxxちょうどxxxxx*",
    "*xxxxxxですxxxxxx*",
    "*xxxxx時はxxxxxxx*",
    "*xxxxxxx金なりxxxx*",
    "x+x1234xx分xxxxxx",
    "xxx換気xxxxアラームxxx",
    "x電池xxx||||||||||"
], "Noto Sans JP:style=Bold", "NotoSansJP-Bold.ttf", "dot"];
