/*
  wc_lang_scifi_QYA.h - Wordclock 16x16, language file scifi_QYA (Quenya), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_scifi_QYA.scad (check: python3 tools/check_lang.py scifi_QYA).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_scifi_QYA.txt)
  Kürzel scifi_QYA (Fantasiesprache: scifi_ + QYA, ISO-639-3-Code). Standort London (vorhandener Eintrag, Europe/London).
  Satzbau: SÍ NÁ [<Minuten> APA | <Minuten> NÓ] <Stunde>
  (SÍ NÁ = „jetzt ist“, APA = „nach“, NÓ = „vor“, CANASTA = „Viertel“, PERTA = „Hälfte“).
  Ab :35 bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 SÍ NÁ <Stunde>, :05 LEMPË APA, :10 CAINEN APA, :15 CANASTA APA, :20 YUCAINEN APA,
  :25 YUCAINEN LEMPË APA, :30 PERTA APA, :35 YUCAINEN LEMPË NÓ, :40 YUCAINEN NÓ, :45 CANASTA NÓ,
  :50 CAINEN NÓ, :55 LEMPË NÓ; z. B. 3:05 SÍ NÁ LEMPË APA NELDË, 3:30 SÍ NÁ PERTA APA NELDË,
  3:45 SÍ NÁ CANASTA NÓ CANTA.
  Stunden mit den belegten Zahlwörtern (12-Stunden-Zählung): MINË, ATTA, NELDË, CANTA, LEMPË, ENQUË, OTSO,
  TOLTO, NERTË, CAINEN, MINQUË, YUNQUË. 12 und 0 Uhr = YUNQUË. Ohne gültige Uhrzeit leuchtet nur SÍ NÁ.
  YUCAINEN („zwanzig“, yu- „zwei“ + cainen „zehn“) ist Neo-Quenya, bei Tolkien ist kein Wort für 20 belegt;
  im Raster YU vor dem CAINEN der Minuten, im Text zusammengeschrieben. 25 = YUCAINEN LEMPË.
  Minutenzeile: nur + 1..4 ohne Wort (Quenya hat kein Wort für Minute), daher keine Einzahl/Mehrzahl.
  Ersatzwörter: LÜFTEN = SÚRË („Wind“), ALARM = ROMBA („Horn, Trompete“), AKKU = TUO („Kraft, Stärke“).
  Zusatzwörter (Schalter „Show PEDO MELLON“, aus = Standard): PEDO MELLON A MINNO
  („Sprich, Freund, und tritt ein“, Torinschrift; das Original ist Sindarin, nicht Quenya, Schreibweise ohne Akzente).
  Sonderzeichen: Ë Á Í Ó Ú sind je eine Zelle (Latin-1, Metriken vorhanden).
  Webinterface auf Englisch (Quenya hat keine Begriffe für Technik), Uhrwörter auf Quenya.
  INFO_EN
  Code scifi_QYA (fictional language: scifi_ + QYA, ISO 639-3 code). Location London (existing entry, Europe/London).
  Sentence: SÍ NÁ [<minutes> APA | <minutes> NÓ] <hour>
  (SÍ NÁ = "now is", APA = "after", NÓ = "before", CANASTA = "quarter", PERTA = "half").
  From :35 on the time refers to the next hour.
  :00 SÍ NÁ <hour>, :05 LEMPË APA, :10 CAINEN APA, :15 CANASTA APA, :20 YUCAINEN APA,
  :25 YUCAINEN LEMPË APA, :30 PERTA APA, :35 YUCAINEN LEMPË NÓ, :40 YUCAINEN NÓ, :45 CANASTA NÓ,
  :50 CAINEN NÓ, :55 LEMPË NÓ; e.g. 3:05 SÍ NÁ LEMPË APA NELDË, 3:30 SÍ NÁ PERTA APA NELDË,
  3:45 SÍ NÁ CANASTA NÓ CANTA.
  Hours with the attested numerals (12-hour count): MINË, ATTA, NELDË, CANTA, LEMPË, ENQUË, OTSO,
  TOLTO, NERTË, CAINEN, MINQUË, YUNQUË. 12:00 and 0:00 = YUNQUË. Without a valid time only SÍ NÁ is lit.
  YUCAINEN ("twenty", yu- "two" + cainen "ten") is Neo-Quenya, Tolkien left no word for 20;
  in the grid YU in front of the minute CAINEN, written as one word in the text. 25 = YUCAINEN LEMPË.
  Minute row: only + 1..4 without a word (Quenya has no word for minute), so no singular/plural.
  Substitute words: VENTILATE = SÚRË ("wind"), ALARM = ROMBA ("horn, trumpet"), BATTERY = TUO ("strength").
  Extra words (switch "Show PEDO MELLON", off by default): PEDO MELLON A MINNO
  ("speak, friend, and enter", door inscription; the original is Sindarin, not Quenya, written without accents).
  Special characters: Ë Á Í Ó Ú are one cell each (Latin-1, metrics present).
  Web interface in English (Quenya has no technical vocabulary), clock words in Quenya.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_scifi_qya {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xSÍxNÁxCANASTA*",
    "*YUCAINENxLEMPË*",
    "*PERTAxxAPAxNÓx*",
    "*xMINËxxxATTAxx*",
    "*NELDËxxxxCANTA*",
    "*xLEMPËxxENQUËx*",
    "*OTSOxxxxxTOLTO*",
    "*xNERTËxxCAINEN*",
    "*MINQUËxYUNQUËx*",
    "*xxxxxxxxxxxxxx*",
    "*xPEDOxMELLONxx*",
    "*xxxAxMINNOxxxx*",
    "*xxxxxxxxxxxxxx*",
    "xxxxx+x1234xxxxx",
    "xSÚRËxxxxxxROMBA",
    "xTUOxx||||||||||",
};
// {row, column, length}, row/column counted from 0 (Ë Á É Í Ó Ú are one cell)
static const WcWord SI = {0, 2, 2}, NA = {0, 5, 2}, CANASTA = {0, 8, 7};
static const WcWord M_YU = {1, 1, 2}, M_CAINEN = {1, 3, 6}, M_LEMPE = {1, 10, 5};
static const WcWord PERTA = {2, 1, 5}, APA = {2, 8, 3}, NO = {2, 12, 2};
// hours 0..11 (0 = YUNQUË)
static const WcWord HOURS[12] = {{8, 8, 6}, {3, 2, 4}, {3, 9, 4},  {4, 1, 5}, {4, 10, 5}, {5, 2, 5},
                                 {5, 9, 5}, {6, 1, 4}, {6, 10, 5}, {7, 2, 5}, {7, 9, 6},  {8, 1, 6}};
// extra words (easter egg): PEDO MELLON A MINNO ("speak, friend, and enter", door inscription, Sindarin)
static const WcWord EXTRA[4] = {{10, 2, 4}, {10, 7, 6}, {11, 4, 1}, {11, 6, 5}};
// row 14: "+ 1 2 3 4" without a word (digits in columns 7..10)
static const WcWord MIN_PLUS = {13, 5, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 7;
static inline void minutes_word(int n5, WcMark &m) {  // n5 = 1..5 (5..25 minutes)
  switch (n5) {
    case 1: m.word(M_LEMPE); break;
    case 2: m.word(M_CAINEN); break;
    case 3: m.word(CANASTA); break;
    case 4: m.word(M_YU); m.glue(M_CAINEN); break;                    // YUCAINEN
    default: m.word(M_YU); m.glue(M_CAINEN); m.word(M_LEMPE); break;  // YUCAINEN LEMPË
  }
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(SI);
  m.word(NA);
  if (!valid) return;  // no time: only the prefix
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 7) h = (h + 1) % 12;  // from "yucainen lempë nó" on the next hour counts
  if (m5 >= 1 && m5 <= 5) { minutes_word(m5, m); m.word(APA); }
  else if (m5 == 6) { m.word(PERTA); m.word(APA); }
  else if (m5 >= 7) { minutes_word(12 - m5, m); m.word(NO); }
  m.word(HOURS[h]);
  const int mm = minute % 5;  // "+ 1..4" (no minute word)
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"en","dec":".",
"notime_msg":"The clock has no time yet (no internet or NTP).",
"btn_settime":"Take time from phone/PC",
"ap_info":"Hotspot “{ap}” active. Please enter your network below under <b>Wi-Fi</b>.",
"sec_show":"Display","on":"Clock switched on","swMin":"Single minutes (+ 1–4)",
"brD":"Brightness day","brN":"Brightness night","cur":"Current limit (mA)",
"hint_show":"Night 0 % = display off at night. Choose the current limit to suit the power supply (256 LEDs already need approx. 256 mA idle current).",
"sec_col":"Colours",
"hint_col":"“Random” changes every full hour. “Temperature”: cold dark blue, yellow, comfort green, orange, hot red (according to the scale under additional displays).",
"g_time":"Time","g_vent":"SÚRË","g_alarm":"ROMBA","g_batt":"TUO","g_tout":"Temperature outside","g_tin":"Temperature inside",
"pal_0":"Warm white","pal_1":"White","pal_2":"Red","pal_3":"Orange","pal_4":"Yellow","pal_5":"Green","pal_6":"Blue","pal_7":"Violet",
"c_random":"Random","c_temp":"Temperature","c_pride":"Pride","c_custom":"custom colour",
"sec_fx":"Effects",
"fx_rainbow":"Rainbow","fx_aurora":"Aurora","fx_matrix":"Matrix","fx_fire":"Fire","fx_confetti":"Confetti","fx_stars":"Starry sky",
"fx_blink":"Blink","fx_blink_own":"Blink (custom colour)","stop":"Stop",
"fxd":"Effect duration","blk":"Blink cycle",
"hint_fx":"Duration 0 s = runs until “Stop”. Effects always run with at least 10 % brightness, even at night with 0 % or with the clock switched off.",
"fx_started":"{fx} started","fx_stopped":"Effect stopped",
"txt":"Text ticker","txt_ph":"Enter text","txt_start":"Start text","txt_started":"Text started",
"hint_txt":"Every letter fills the whole matrix. Runs for the effect duration (at least once), in the colour of the time (random = rainbow). Latin, Greek and Cyrillic letters, digits, punctuation, € and ♥. HTTP: /api/set?text=…",
"sec_sun":"Day / night","nmode":"Night mode","nm_mix":"Mixed","nm_sun":"Sun position","nm_fixed":"Fixed times",
"lat":"Latitude","lon":"Longitude","nso":"Night start offset (min)","neo":"Night end offset (min)",
"nme":"Night not before","nml":"Night not after","nfs":"Night from","nfe":"Night until",
"sunrise":"Sunrise","sunset":"Sunset","night_today":"Night today","now":"Now",
"nmh_0":"Offset: + after, − before sunset or sunrise. Coordinates e.g. from a map app (right-click on the place).",
"nmh_1":"Fixed times apply every day.",
"nmh_2":"Night starts at sunset (plus offset), but not before the set time, and ends at sunrise (plus offset), but not after the set time.",
"day":"Day","night":"Night",
"sec_extra":"Additional displays","tOnl":"Outdoor temperature from Open-Meteo (location)",
"scale_out":"Scale outside (°C)","scale_in":"Scale inside (°C)",
"swExtra":"Show PEDO MELLON",
"apiTo":"Values valid for (min, 0 = always)",
"v_out":"Outside","v_in":"Inside","v_batt":"Battery","v_la":"Ventilate / alarm","on_":"on","off_":"off",
"hint_extra":"Inside, battery, ventilate and alarm (and outside, if without Open-Meteo) come from outside, e.g. via browser, script or smart home:",
"sec_api":"HTTP control",
"hint_api1":"From other systems via browser, script or smart home (GET or POST to <code>/api/set</code>, several parameters can be combined). Brightness, colours and switches are saved, effects run for the set duration.",
"hint_api2":"Colours: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperature: temp) or rrggbb · Switches: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effects: {fx}, stop · fxcolor: colour name or rrggbb. Current limit, Wi-Fi and system only here in the web interface.",
"sec_time":"Time","ntpD":"NTP server","ntp_auto":"automatic (DHCP)","ntp_manual":"manual","ntp_server":"Server",
"ntp_fallback":"Fallback server (if the router does not provide one, applies after restart)",
"loc":"Location","loc_custom":"custom location (coordinates)","tz_from_loc":"from location {city}",
"tz":"Time zone","tz_cet":"Central Europe (DE, AT, CH …)","tz_wet":"London, Lisbon (WET)","tz_eet":"Eastern Europe (Kyiv, Athens, Bucharest)",
"tz_trt":"Turkey","tz_eat":"East Africa (Tanzania, Kenya)","tz_utc":"UTC",
"tz_use":"USA East","tz_usc":"USA Central","tz_usm":"USA Mountain","tz_usw":"USA West",
"tz_wib":"Indonesia (Jakarta)","tz_cst":"China","tz_kst":"Korea","tz_jst":"Japan","tz_aus":"Australia East",
"tz_custom":"custom (POSIX TZ) …","tz_posix":"POSIX time zone","ntp_active":"Active server",
"ntp_hint":"Automatic: server from the router (DHCP), otherwise the entered one as fallback. Switching between automatic and manual restarts the clock.",
"ntp_nodhcp":"DHCP NTP is not available in this board package – the entered server is used.",
"sec_wifi":"Wi-Fi","ssid":"Network (SSID)","scan":"Search networks","pass":"Password","pass_ph":"leave empty = keep current",
"host":"Device name (http://name.local)","save_wifi":"Save & reconnect",
"status":"Status","ip":"IP","last_err":"Last error",
"hint_wifi":"If the Wi-Fi is not found at start-up, the clock opens the hotspot “{ap}” (without password, http://192.168.4.1).",
"w_conn":"connected to {ssid}","w_ap":"Hotspot active ({ip})","w_none":"not connected",
"scanning":"Searching …","scan_none":"No networks found","scan_err":"Search failed",
"wr_2":"authentication expired","wr_15":"wrong password?","wr_201":"network not found","wr_202":"authentication rejected (password?)",
"wr_203":"association failed","wr_204":"wrong password?","wr_205":"connection failed","wr_8":"disconnected",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi disconnected","net_lost":"no connection to the clock",
"sec_sys":"System","mir":"LED 0 front top right (mirror)","srp":"Matrix wired in zigzag",
"restart":"Restart","reset":"Factory reset",
"q_restart":"Restart the clock?","q_reset":"Delete all settings including Wi-Fi?",
"language":"Language","firmware":"Firmware","uptime":"Uptime","heap":"Free memory",
"footer":"{ap} – build guide, code and print files:",
"saved":"Saved","saved_restart":"Saved – clock restarts …","save_err":"Error while saving",
"time_set":"Time taken over","restarting":"Clock restarts …",
"srv_no_network":"No network entered","srv_back":"Back","srv_saved":"Wi-Fi saved",
"srv_connecting":"The clock now connects to","srv_restart":"and restarts for this. The hotspot disappears.",
"srv_reach":"Afterwards reachable at","srv_reach2":"or via the IP address from the router or the serial monitor.",
"srv_retry":"If the connection fails, the hotspot reappears after about 30 seconds.",
"srv_not_found":"Not found"
})JSON";
}  // namespace wc_scifi_qya
static const WcLangDef WC_LANG = {
    "scifi_QYA", "Quenya", wc_scifi_qya::GRID,
    {14, 1, 4},   // SÚRË
    {14, 11, 5},  // ROMBA
    {15, 1, 3},   // TUO
    {15, 6, 10},  // battery bars
    wc_scifi_qya::EXTRA, 4,  // PEDO MELLON A MINNO
    wc_scifi_qya::time_words,
    "quettalume", "QuettaLume",
    51.5074f, -0.1278f,           // London
    "GMT0BST,M3.5.0/1,M10.5.0",   // Europe/London
    "%d/%m/%Y",
    wc_scifi_qya::UI_JSON,
};
