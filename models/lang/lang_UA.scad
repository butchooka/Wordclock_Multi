// lang_UA.scad - Wordclock 16x16, model language file UA (Українська), v0.9
// Used by Wordclock_Model.scad (via lang_all.scad) and Wordclock_Model.FCMacro (reads this file).
// The grid must be identical to arduino/Wordclock/src/wc_lang_UA.h (check: python3 tools/check_lang.py UA).
// 16 rows of 16 characters, row 1 = top. "*" temperature dot, "|" battery bar, "+" plus, "x" filler (printed as FILLER), space/"." = nothing.
// Format (keep it, FreeCAD parses it): [code, own name, [16 rows], OpenSCAD font, FreeCAD font file]
//   OpenSCAD font: "" = setting SCHRIFT, otherwise e.g. "Noto Sans KR:style=Bold"
//   FreeCAD font file: "" = font dialog, otherwise e.g. "NotoSansKR-Bold.otf" (searched in the system fonts)
// Cyrillic: the metrics are in METRIK_LIBERATION_BOLD / METRIK_DEJAVU_BOLD of Wordclock_Model.scad (block Cyrillic),
// so the font stays "" (setting SCHRIFT: Liberation Sans Bold, Arial Bold and DejaVu Sans Bold contain Cyrillic).
// Д and Ц (short descender) are reduced and pushed up like Ç. FreeCAD: choose a font with Cyrillic (e.g. Arial Bold).
// The filler is the Latin "x"; the Cyrillic "Х" of ХВИЛИНА is a letter. Filler default "dot" (FILLER = "auto"),
// as a printed X is easily confused with the Cyrillic Х.
LANG_UA = ["UA", "Українська", [
    "*ЗАРАЗxЗАxxПІВx*",
    "*ЧВЕРТЬxxДЕСЯТЬ*",
    "*ДВАДЦЯТЬxП'ЯТЬ*",
    "*НАxОДИНАДЦЯТАУ*",
    "*xПЕРШАУxДРУГАУ*",
    "*ТРЕТЯЮxxП'ЯТАУ*",
    "*xxЧЕТВЕРТАУxxx*",
    "*ШОСТАУxВОСЬМАУ*",
    "*СЬОМАУxДЕСЯТАУ*",
    "*ДЕВ'ЯТАУxСЛАВА*",
    "*xДВАНАДЦЯТАУxx*",
    "*ГОДИНАxУКРАЇНІ*",
    "*xГЕРОЯМxСЛАВАx*",
    "+x1234xxХВИЛИНАИ",
    "ПРОВІТРИxТРИВОГА",
    "ЗАРЯДx||||||||||"
], "", "", "dot"];
