// lang_CN.scad - Wordclock 16x16, model language file CN (中文 / Mandarin Chinese, simplified characters), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_CN.h (check: python3 tools/check_lang.py CN).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file, filler]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans SC:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansSC-Bold.ttf" (searched in the system fonts)
//   filler: default of FILLER for this language, used with FILLER = "auto" in the models ("" = X); here "dot"
// Note: Chinese characters need their own font. Noto Sans SC (Google Fonts, SIL Open Font License) must be installed:
//   https://fonts.google.com/noto/specimen/Noto+Sans+SC - the static file static/NotoSansSC-Bold.ttf.
// Without metrics the characters are only roughly centred (adjust FREI_GROESSE if needed). Fillers: dot (field 6).
// Closed counters (e.g. in 晨, 阴, 电, 四) need the same front construction as KR/JP (characters with inner islands).
LANG_CN = ["CN", "中文", [
    "*xx现在是x凌晨xxxxxx*",
    "*xx晚上午x中午x下午xxx*",
    "*xxxxxxxxxxxxxx*",
    "*xx一x两x三x四x五x六x*",
    "*xx七x八x九x十一x十二x*",
    "*xxxxx点半x整xxxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xxx二x三x四x五xxxx*",
    "*xxxxxxx十五分xxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xxxx一寸光阴一寸金xxx*",
    "*xxxxxxxxxxxxxx*",
    "*xxxx寸金难买寸光阴xxx*",
    "x+x1234xx分xxxxxx",
    "xxx通风xxxx警报xxxxx",
    "x电池xxx||||||||||"
], "Noto Sans SC:style=Bold", "NotoSansSC-Bold.ttf", "dot"];
