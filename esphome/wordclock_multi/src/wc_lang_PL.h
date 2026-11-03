/*
  wc_lang_PL.h - Wordclock 16x16, language file PL (Polski), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_PL.scad (check: python3 tools/check_lang.py PL).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_PL.txt)
  Satzbau (gängige Umgangsform, 12-Stunden-Zählung, Stunden als weibliche Ordnungszahlen):
  <Minuten> PO <Stunde>[Lokativ] | WPÓŁ DO <nächste Stunde>[Genitiv] | ZA <Minuten> <nächste Stunde> |
  <Stunde>. Ohne vorangestelltes „JEST“ („es ist“) – im Polnischen ganz natürlich („Za pięć druga.“).
  Ab :30 (WPÓŁ DO = „halb zur …“) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 <Stunde>, :05 PIĘĆ PO <Stunde-Lok.>, :10 DZIESIĘĆ PO, :15 KWADRANS PO, :20 DWADZIEŚCIA PO,
  :25 DWADZIEŚCIA PIĘĆ PO, :30 WPÓŁ DO <nächste Stunde-Gen.>, :35 ZA DWADZIEŚCIA PIĘĆ <nächste Stunde>,
  :40 ZA DWADZIEŚCIA, :45 ZA KWADRANS, :50 ZA DZIESIĘĆ, :55 ZA PIĘĆ
  Beispiele: 3:05 PIĘĆ PO TRZECIEJ, 3:30 WPÓŁ DO CZWARTEJ, 3:45 ZA KWADRANS CZWARTA.
  Stunden (Nominativ / Lokativ = Genitiv): PIERWSZA/PIERWSZEJ, DRUGA/DRUGIEJ, TRZECIA/TRZECIEJ,
  CZWARTA/CZWARTEJ, PIĄTA/PIĄTEJ, SZÓSTA/SZÓSTEJ, SIÓDMA/SIÓDMEJ, ÓSMA/ÓSMEJ, DZIEWIĄTA/DZIEWIĄTEJ,
  DZIESIĄTA/DZIESIĄTEJ, JEDENASTA/JEDENASTEJ, DWUNASTA/DWUNASTEJ.
  Im Raster folgen beide Endungen dem Wortstamm (z. B. „PIERWSZAEJ“): Nominativ = Stamm + A
  (zusammenhängend), Lokativ = Stamm + EJ (eine Lücke, das A bleibt dunkel; DRUG + IEJ).
  DZIEWIĄTA und DZIESIĄTA teilen sich ein Wort „DZIEWSIĄTAEJ“: DZIEW·IĄTA bzw. DZIE·SIĄTA
  (je ein Buchstabe Lücke).
  0 und 12 Uhr = DWUNASTA. Keine Wörter für Mitternacht/Mittag.
  Ohne gültige Uhrzeit bleibt das Raster dunkel (kein Vorsatzwort).
  Minutenzeile: + 1 MINUTA, + 2..4 MINUTY (MINUT + Y, eine Lücke).
  Statuswörter: LÜFTEN = WIETRZ („lüfte!“), ALARM = ALARM, AKKU = AKU (Kurzform von „akumulator“;
  BATERIA ist mit 7 Buchstaben zu lang für die Zeile mit den 10 Balken).
  Zusatzwörter (Schalter „Pokaż CZAS LECI“): CZAS LECI („die Zeit vergeht/fliegt“).
  Sonderzeichen: Ą, Ę, Ć, Ś, Ł, Ó (Metriken für OpenSCAD in Wordclock_Model.scad vorhanden).
  INFO_EN
  Sentence (common spoken form, 12-hour counting, hours as feminine ordinal numbers):
  <minutes> PO <hour>[locative] | WPÓŁ DO <next hour>[genitive] | ZA <minutes> <next hour> |
  <hour>. Without a leading "JEST" ("it is") - quite natural in Polish ("Za pięć druga.").
  From :30 on (WPÓŁ DO = "half to ...") the time refers to the next hour.
  :00 <hour>, :05 PIĘĆ PO <hour-loc.>, :10 DZIESIĘĆ PO, :15 KWADRANS PO, :20 DWADZIEŚCIA PO,
  :25 DWADZIEŚCIA PIĘĆ PO, :30 WPÓŁ DO <next hour-gen.>, :35 ZA DWADZIEŚCIA PIĘĆ <next hour>,
  :40 ZA DWADZIEŚCIA, :45 ZA KWADRANS, :50 ZA DZIESIĘĆ, :55 ZA PIĘĆ
  Examples: 3:05 PIĘĆ PO TRZECIEJ, 3:30 WPÓŁ DO CZWARTEJ, 3:45 ZA KWADRANS CZWARTA.
  Hours (nominative / locative = genitive): PIERWSZA/PIERWSZEJ, DRUGA/DRUGIEJ, TRZECIA/TRZECIEJ,
  CZWARTA/CZWARTEJ, PIĄTA/PIĄTEJ, SZÓSTA/SZÓSTEJ, SIÓDMA/SIÓDMEJ, ÓSMA/ÓSMEJ, DZIEWIĄTA/DZIEWIĄTEJ,
  DZIESIĄTA/DZIESIĄTEJ, JEDENASTA/JEDENASTEJ, DWUNASTA/DWUNASTEJ.
  In the grid both endings follow the stem (e.g. "PIERWSZAEJ"): nominative = stem + A (contiguous),
  locative = stem + EJ (one gap, the A stays dark; DRUG + IEJ).
  DZIEWIĄTA and DZIESIĄTA share one word "DZIEWSIĄTAEJ": DZIEW·IĄTA and DZIE·SIĄTA (one letter gap each).
  0 and 12 o'clock = DWUNASTA. No words for midnight/noon.
  Without a valid time the grid stays dark (no prefix word).
  Minute row: + 1 MINUTA, + 2..4 MINUTY (MINUT + Y, one gap).
  Status words: VENTILATE = WIETRZ ("ventilate!"), ALARM = ALARM, BATTERY = AKU (short for "akumulator";
  BATERIA with 7 letters is too long for the row with the 10 bars).
  Extra words (switch "Pokaż CZAS LECI"): CZAS LECI ("time flies").
  Special letters: Ą, Ę, Ć, Ś, Ł, Ó (metrics for OpenSCAD available in Wordclock_Model.scad).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_pl {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*ZAxDWADZIEŚCIA*",
    "*PIĘĆxDZIESIĘĆx*",
    "*KWADRANSxxWPÓŁ*",
    "*POxDOxDRUGAIEJ*",
    "*xxPIERWSZAEJxx*",
    "*TRZECIAEJxCZAS*",
    "*CZWARTAEJxLECI*",
    "*PIĄTAEJxÓSMAEJ*",
    "*xxxSZÓSTAEJxxx*",
    "*xxxSIÓDMAEJxxx*",
    "*xDZIEWSIĄTAEJx*",
    "*xxJEDENASTAEJx*",
    "*xxDWUNASTAEJxx*",
    "x+x1234xMINUTAYx",
    "WIETRZxxxxxALARM",
    "xAKUxx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord ZA = {0, 1, 2}, PO = {3, 1, 2}, WPOL = {2, 11, 4}, DO = {3, 4, 2};
static const WcWord M_PIEC = {1, 1, 4}, M_DZIESIEC = {1, 6, 8}, M_KWADRANS = {2, 1, 8}, M_DWADZIESCIA = {0, 4, 11};
// hour 0..11 (0 = DWUNASTA). Stem, then ending A (nominative) and EJ (locative/genitive, DRUG + IEJ).
// 9 and 10 share "DZIEWSIĄTAEJ": DZIEW + IĄT / DZIE + SIĄT (H_MID9 / H_MID10)
static const WcWord H_STEM[12] = {{12, 3, 7}, {4, 3, 7}, {3, 7, 4}, {5, 1, 6},  {6, 1, 6},  {7, 1, 4},
                                  {8, 4, 5},  {9, 4, 5}, {7, 9, 3}, {10, 2, 5}, {10, 2, 4}, {11, 3, 8}};
static const WcWord H_A[12] = {{12, 10, 1}, {4, 10, 1}, {3, 11, 1}, {5, 7, 1},   {6, 7, 1},   {7, 5, 1},
                               {8, 9, 1},   {9, 9, 1},  {7, 12, 1}, {10, 11, 1}, {10, 11, 1}, {11, 11, 1}};
static const WcWord H_EJ[12] = {{12, 11, 2}, {4, 11, 2}, {3, 12, 3}, {5, 8, 2},   {6, 8, 2},   {7, 6, 2},
                                {8, 10, 2},  {9, 10, 2}, {7, 13, 2}, {10, 12, 2}, {10, 12, 2}, {11, 12, 2}};
static const WcWord H_MID9 = {10, 8, 3}, H_MID10 = {10, 7, 4};  // IĄT / SIĄT
// extra words (easter egg): CZAS LECI ("time flies")
static const WcWord EXTRA[2] = {{5, 11, 4}, {6, 11, 4}};
// row 14: "+ 1 2 3 4  MINUTA / MINUT+Y" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_ONE = {13, 8, 6}, MIN_STEM = {13, 8, 5}, MIN_Y = {13, 14, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
// loc = false: nominative (stem + A), true: locative/genitive (stem + EJ)
static inline void hour_word(int h, bool loc, WcMark &m) {
  m.word(H_STEM[h]);
  if (h == 9) m.glue(H_MID9);
  else if (h == 10) m.glue(H_MID10);
  m.glue(loc ? H_EJ[h] : H_A[h]);
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  if (!valid) return;  // no prefix word in Polish: grid stays dark without time
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 6) h = (h + 1) % 12;  // from "wpół do" on the next hour counts
  switch (m5) {
    case 0: hour_word(h, false, m); break;
    case 1: m.word(M_PIEC); m.word(PO); hour_word(h, true, m); break;
    case 2: m.word(M_DZIESIEC); m.word(PO); hour_word(h, true, m); break;
    case 3: m.word(M_KWADRANS); m.word(PO); hour_word(h, true, m); break;
    case 4: m.word(M_DWADZIESCIA); m.word(PO); hour_word(h, true, m); break;
    case 5: m.word(M_DWADZIESCIA); m.word(M_PIEC); m.word(PO); hour_word(h, true, m); break;
    case 6: m.word(WPOL); m.word(DO); hour_word(h, true, m); break;
    case 7: m.word(ZA); m.word(M_DWADZIESCIA); m.word(M_PIEC); hour_word(h, false, m); break;
    case 8: m.word(ZA); m.word(M_DWADZIESCIA); hour_word(h, false, m); break;
    case 9: m.word(ZA); m.word(M_KWADRANS); hour_word(h, false, m); break;
    case 10: m.word(ZA); m.word(M_DZIESIEC); hour_word(h, false, m); break;
    default: m.word(ZA); m.word(M_PIEC); hour_word(h, false, m); break;
  }
  const int mm = minute % 5;  // "+ 1 MINUTA", "+ 2..4 MINUTY"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    if (mm == 1) m.word(MIN_ONE);
    else { m.word(MIN_STEM); m.glue(MIN_Y); }
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"pl","dec":",",
"notime_msg":"Zegar nie zna jeszcze czasu (brak internetu lub NTP).",
"btn_settime":"Pobierz czas z telefonu/komputera",
"ap_info":"Punkt dostępowy „{ap}” jest aktywny. Wprowadź swoją sieć poniżej w sekcji <b>Wi-Fi</b>.",
"sec_show":"Wyświetlanie","on":"Zegar włączony","swMin":"Pojedyncze minuty (+ 1–4 MINUTY)",
"brD":"Jasność w dzień","brN":"Jasność w nocy","cur":"Limit prądu (mA)",
"hint_show":"Noc 0 % = wyświetlacz wyłączony w nocy. Dobierz limit prądu do zasilacza (256 diod LED pobiera już ok. 256 mA w spoczynku).",
"sec_col":"Kolory",
"hint_col":"„Losowy” zmienia się co pełną godzinę. „Temperatura”: zimno ciemnoniebieski, żółty, komfort zielony, pomarańczowy, gorąco czerwony (według skali w dodatkowych wskazaniach).",
"g_time":"Godzina","g_vent":"WIETRZ","g_alarm":"ALARM","g_batt":"AKU","g_tout":"Temperatura na zewnątrz","g_tin":"Temperatura wewnątrz",
"pal_0":"Ciepła biel","pal_1":"Biały","pal_2":"Czerwony","pal_3":"Pomarańczowy","pal_4":"Żółty","pal_5":"Zielony","pal_6":"Niebieski","pal_7":"Fioletowy",
"c_random":"Losowy","c_temp":"Temperatura","c_pride":"Pride","c_custom":"własny kolor",
"sec_fx":"Efekty",
"fx_rainbow":"Tęcza","fx_aurora":"Zorza polarna","fx_matrix":"Matrix","fx_fire":"Ogień","fx_confetti":"Konfetti","fx_stars":"Gwiaździste niebo",
"fx_blink":"Miganie","fx_blink_own":"Miganie (własny kolor)","stop":"Stop",
"fxd":"Czas trwania efektu","blk":"Cykl migania",
"hint_fx":"Czas 0 s = działa do „Stop”. Efekty działają zawsze z jasnością co najmniej 10 %, także w nocy przy 0 % lub przy wyłączonym zegarze.",
"fx_started":"{fx} uruchomiony","fx_stopped":"Efekt zatrzymany",
"txt":"Tekst","txt_ph":"Wpisz tekst","txt_start":"Pokaż tekst","txt_started":"Tekst uruchomiony",
"hint_txt":"Każda litera wypełnia całą matrycę. Trwa tyle, ile czas efektu (co najmniej raz), w kolorze godziny (losowy = tęcza). Litery łacińskie, greckie i cyrylickie, cyfry, znaki interpunkcyjne, € i ♥. HTTP: /api/set?text=…",
"sec_sun":"Dzień / noc","nmode":"Tryb nocny","nm_mix":"Mieszany","nm_sun":"Położenie słońca","nm_fixed":"Stałe godziny",
"lat":"Szerokość geogr.","lon":"Długość geogr.","nso":"Przesunięcie początku nocy (min)","neo":"Przesunięcie końca nocy (min)",
"nme":"Noc najwcześniej","nml":"Noc najpóźniej","nfs":"Noc od","nfe":"Noc do",
"sunrise":"Wschód słońca","sunset":"Zachód słońca","night_today":"Noc dzisiaj","now":"Teraz",
"nmh_0":"Przesunięcie: + po, − przed zachodem lub wschodem słońca. Współrzędne np. z aplikacji z mapą (prawy klik na miejsce).",
"nmh_1":"Stałe godziny obowiązują codziennie.",
"nmh_2":"Noc zaczyna się o zachodzie słońca (plus przesunięcie), ale nie przed ustawioną godziną, i kończy o wschodzie słońca (plus przesunięcie), ale nie po ustawionej godzinie.",
"day":"Dzień","night":"Noc",
"sec_extra":"Dodatkowe wskazania","swTemp":"Punkty temperatury (lewa zewnątrz, prawa wewnątrz)","tOnl":"Temperatura zewnętrzna z Open-Meteo (lokalizacja)",
"scale_out":"Skala zewnątrz (°C)","scale_in":"Skala wewnątrz (°C)",
"swLuft":"Pokaż WIETRZ","swAlarm":"Pokaż ALARM","swAkku":"Pokaż AKU","swExtra":"Pokaż CZAS LECI",
"apiTo":"Ważność wartości (min, 0 = zawsze)",
"v_out":"Zewnątrz","v_in":"Wewnątrz","v_batt":"Akumulator","v_la":"Wietrzenie / alarm","on_":"wł.","off_":"wył.",
"hint_extra":"Wewnątrz, akumulator, wietrzenie i alarm (oraz zewnątrz bez Open-Meteo) przychodzą z zewnątrz, np. przez przeglądarkę, skrypt lub inteligentny dom:",
"sec_api":"Sterowanie HTTP",
"hint_api1":"Z innych systemów przez przeglądarkę, skrypt lub inteligentny dom (GET lub POST na <code>/api/set</code>, można łączyć kilka parametrów). Jasność, kolory i przełączniki są zapisywane, efekty działają przez ustawiony czas.",
"hint_api2":"Kolory: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatura: temp) lub rrggbb · Przełączniki: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Efekty: {fx}, stop · fxcolor: nazwa koloru lub rrggbb. Limit prądu, Wi-Fi i system tylko tutaj w interfejsie WWW.",
"sec_time":"Czas","ntpD":"Serwer NTP","ntp_auto":"automatycznie (DHCP)","ntp_manual":"ręcznie","ntp_server":"Serwer",
"ntp_fallback":"Serwer zapasowy (gdy router go nie podaje, obowiązuje po ponownym uruchomieniu)",
"loc":"Lokalizacja","loc_custom":"własna lokalizacja (współrzędne)","tz_from_loc":"z lokalizacji {city}",
"tz":"Strefa czasowa","tz_cet":"Europa Środkowa (PL, DE, AT, CH …)","tz_wet":"Londyn, Lizbona (WET)","tz_eet":"Europa Wschodnia (Kijów, Ateny, Bukareszt)",
"tz_trt":"Turcja","tz_eat":"Afryka Wschodnia (Tanzania, Kenia)","tz_utc":"UTC",
"tz_use":"USA Wschód","tz_usc":"USA Centrum","tz_usm":"USA Góry","tz_usw":"USA Zachód",
"tz_wib":"Indonezja (Dżakarta)","tz_cst":"Chiny","tz_kst":"Korea","tz_jst":"Japonia","tz_aus":"Australia Wschód",
"tz_custom":"własna (POSIX TZ) …","tz_posix":"Strefa czasowa POSIX","ntp_active":"Aktywny serwer",
"ntp_hint":"Automatycznie: serwer z routera (DHCP), w przeciwnym razie wpisany jako zapasowy. Przełączenie między automatycznym a ręcznym uruchamia zegar ponownie.",
"ntp_nodhcp":"NTP przez DHCP nie jest dostępne w tym pakiecie płytki – używany jest wpisany serwer.",
"sec_wifi":"Wi-Fi","ssid":"Sieć (SSID)","scan":"Szukaj sieci","pass":"Hasło","pass_ph":"puste = zachowaj obecne",
"host":"Nazwa urządzenia (http://nazwa.local)","save_wifi":"Zapisz i połącz ponownie",
"status":"Stan","ip":"IP","last_err":"Ostatni błąd",
"hint_wifi":"Jeśli przy starcie sieć Wi-Fi nie zostanie znaleziona, zegar otwiera punkt dostępowy „{ap}” (bez hasła, http://192.168.4.1).",
"w_conn":"połączono z {ssid}","w_ap":"Punkt dostępowy aktywny ({ip})","w_none":"brak połączenia",
"scanning":"Szukam …","scan_none":"Nie znaleziono sieci","scan_err":"Wyszukiwanie nie powiodło się",
"wr_2":"uwierzytelnianie wygasło","wr_15":"błędne hasło?","wr_201":"nie znaleziono sieci","wr_202":"uwierzytelnianie odrzucone (hasło?)",
"wr_203":"skojarzenie nie powiodło się","wr_204":"błędne hasło?","wr_205":"połączenie nie powiodło się","wr_8":"rozłączono",
"net_hotspot":"Punkt dostępowy {ap}","net_off":"Wi-Fi rozłączone","net_lost":"brak połączenia z zegarem",
"sec_sys":"System","mir":"LED 0 z przodu w prawym górnym rogu (lustro)","srp":"Matryca połączona zygzakiem",
"restart":"Uruchom ponownie","reset":"Ustawienia fabryczne",
"q_restart":"Uruchomić zegar ponownie?","q_reset":"Usunąć wszystkie ustawienia łącznie z Wi-Fi?",
"language":"Język","firmware":"Oprogramowanie","uptime":"Czas pracy","heap":"Wolna pamięć",
"footer":"{ap} – instrukcja budowy, kod i pliki do druku:",
"saved":"Zapisano","saved_restart":"Zapisano – zegar uruchamia się ponownie …","save_err":"Błąd zapisu",
"time_set":"Czas przejęty","restarting":"Zegar uruchamia się ponownie …",
"srv_no_network":"Nie podano sieci","srv_back":"Wstecz","srv_saved":"Wi-Fi zapisane",
"srv_connecting":"Zegar łączy się teraz z siecią","srv_restart":"i w tym celu uruchamia się ponownie. Punkt dostępowy znika.",
"srv_reach":"Następnie dostępny pod adresem","srv_reach2":"lub przez adres IP z routera albo monitora portu szeregowego.",
"srv_retry":"Jeśli połączenie się nie powiedzie, punkt dostępowy pojawi się ponownie po ok. 30 sekundach.",
"srv_not_found":"Nie znaleziono"
})JSON";
}  // namespace wc_pl
static const WcLangDef WC_LANG = {
    "PL", "Polski", wc_pl::GRID,
    {14, 0, 6},   // WIETRZ
    {14, 11, 5},  // ALARM
    {15, 1, 3},   // AKU
    {15, 6, 10},  // battery bars
    wc_pl::EXTRA, 2,  // CZAS LECI
    wc_pl::time_words,
    "zegarslowny", "ZegarSlowny",
    52.2297f, 21.0122f,  // Warszawa
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Warsaw
    "%d.%m.%Y",
    wc_pl::UI_JSON,
};
