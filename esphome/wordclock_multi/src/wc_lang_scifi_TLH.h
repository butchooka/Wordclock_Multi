/*
  wc_lang_scifi_TLH.h - Wordclock 16x16, language file scifi_TLH (tlhIngan Hol), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_scifi_TLH.scad (check: python3 tools/check_lang.py scifi_TLH).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_scifi_TLH.txt)
  Kürzel scifi_TLH (Kunstsprache, scifi_ + ISO-639-Code tlh). Kein Land: Standort Berlin (bestehender Eintrag, MEZ).
  Standard-Umschrift mit Groß-/Kleinschreibung: q und Q sind verschiedene Buchstaben, D I S H immer groß,
  der Apostroph ' ist ein eigener Buchstabe und belegt eine Zelle. Kleines x kommt nicht vor und bleibt Füllfeld.
  Füllfelder druckt das 3D-Modell als Punkt (Vorgabe der Sprache bei FILLER = "auto"), ein großes X wirkt zwischen
  den vielen Kleinbuchstaben zu wuchtig.
  Satzbau (24-Stunden-Form): DaH <Stunde> vatlh <Minuten> rep, um 0 Uhr DaH pagh <Minuten> rep
  (DaH = „jetzt“, vatlh = „hundert“, rep = „Stunde“, pagh = „null“; die Uhrzeit wird wie eine vierstellige
  Zahl gelesen, 14:30 = „vierzehnhundertdreißig Stunden“). Kein Bezug auf die nächste Stunde, keine Viertel/halb.
  :00 DaH <Stunde> vatlh rep, :05 … vagh, :10 … wa'maH, :15 … wa'maH vagh, :20 … cha'maH, :25 … cha'maH vagh,
  :30 … wejmaH, :35 … wejmaH vagh, :40 … loSmaH, :45 … loSmaH vagh, :50 … vaghmaH, :55 … vaghmaH vagh (jeweils + rep);
  z. B. 6:05 DaH jav vatlh vagh rep, 14:30 DaH wa'maH loS vatlh wejmaH rep, 0:25 DaH pagh cha'maH vagh rep.
  Zahlen: wa' cha' wej loS vagh jav Soch chorgh Hut (1-9), Zehner = Ziffer + maH (wa'maH 10, cha'maH 20,
  wejmaH 30, loSmaH 40, vaghmaH 50). Stunden 0-23: pagh (ohne vatlh), 1-9 Ziffer, 10 wa'maH, 11-19 wa'maH + Ziffer,
  20 cha'maH, 21-23 cha'maH + Ziffer, danach vatlh. 12:00 = DaH wa'maH cha' vatlh rep, 0:00 = DaH pagh rep.
  Stunden- und Minuten-Zehner (wa'maH, cha'maH) stehen je einmal für die Stunde und einmal für die Minuten im Raster.
  Ohne gültige Uhrzeit leuchtet nur DaH.
  Minutenzeile: + 1..4 tup („Minute“; nach Zahlwörtern keine Mehrzahl, daher immer tup).
  Ersatzwörter: LÜFTEN = SuS („Wind, Brise“), ALARM = ghuHmoH („alarmieren, warnen“), AKKU = HoS („Energie, Kraft“).
  Zusatzwörter (Schalter „Show Heghlu'meH QaQ jajvam“, aus = Standard): Heghlu'meH QaQ jajvam
  („Heute ist ein guter Tag zum Sterben“, bekanntester Spruch der Sprache).
  Gerätename mutlhaq / Hotspot Mutlhaq (mu' tlhaq = „Wort-Chronometer“, ohne Apostroph wegen Hostname).
  Webinterface und Home-Assistant-Entitäten auf Englisch, nur die Uhrwörter auf tlhIngan Hol. Auch Farben und
  Effekte bleiben englisch: Die belegten Farbwörter sind zu grob (Doq = rot/orange, SuD = gelb/grün/blau), die
  Farbauswahl wäre damit nicht unterscheidbar.
  INFO_EN
  Code scifi_TLH (constructed language, scifi_ + ISO 639 code tlh). No country: location Berlin (existing entry, CET).
  Standard romanisation with upper/lower case: q and Q are different letters, D I S H always upper case,
  the apostrophe ' is a letter of its own and takes one cell. Lower case x does not occur and stays the filler.
  The 3D model prints the fillers as dots (language default with FILLER = "auto"), a capital X looks too heavy
  between the many lower case letters.
  Sentence (24-hour form): DaH <hour> vatlh <minutes> rep, at 0 o'clock DaH pagh <minutes> rep
  (DaH = "now", vatlh = "hundred", rep = "hour", pagh = "zero"; the time is read like a four-digit number,
  14:30 = "fourteen hundred thirty hours"). No reference to the next hour, no quarter/half.
  :00 DaH <hour> vatlh rep, :05 … vagh, :10 … wa'maH, :15 … wa'maH vagh, :20 … cha'maH, :25 … cha'maH vagh,
  :30 … wejmaH, :35 … wejmaH vagh, :40 … loSmaH, :45 … loSmaH vagh, :50 … vaghmaH, :55 … vaghmaH vagh (each + rep);
  e.g. 6:05 DaH jav vatlh vagh rep, 14:30 DaH wa'maH loS vatlh wejmaH rep, 0:25 DaH pagh cha'maH vagh rep.
  Numbers: wa' cha' wej loS vagh jav Soch chorgh Hut (1-9), tens = digit + maH (wa'maH 10, cha'maH 20,
  wejmaH 30, loSmaH 40, vaghmaH 50). Hours 0-23: pagh (without vatlh), 1-9 digit, 10 wa'maH, 11-19 wa'maH + digit,
  20 cha'maH, 21-23 cha'maH + digit, then vatlh. 12:00 = DaH wa'maH cha' vatlh rep, 0:00 = DaH pagh rep.
  The tens wa'maH and cha'maH are in the grid once for the hour and once for the minutes.
  Without a valid time only DaH is lit.
  Minute row: + 1..4 tup ("minute"; no plural after numbers, so always tup).
  Substitute words: VENTILATE = SuS ("wind, breeze"), ALARM = ghuHmoH ("to alert, warn"), BATTERY = HoS ("energy, power").
  Extra words (switch "Show Heghlu'meH QaQ jajvam", off by default): Heghlu'meH QaQ jajvam
  ("today is a good day to die", the best-known saying of the language).
  Device name mutlhaq / hotspot Mutlhaq (mu' tlhaq = "word chronometer", no apostrophe in a host name).
  Web interface and Home Assistant entities in English, only the clock words in tlhIngan Hol. Colours and effects
  stay English too: the attested colour words are too coarse (Doq = red/orange, SuD = yellow/green/blue), the
  colour choice could not be told apart.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_scifi_tlh {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models).
// Mixed case: q/Q, h/H etc. are different letters, "'" is a letter (one cell). "x" is never a letter here.
static const char *const GRID[16] = {
    "*xDaHxxxxxxpagh*",
    "*wa'maHxcha'maH*",
    "*xwa'xcha'xwejx*",
    "*xloSxvaghxjavx*",
    "*xSochxchorghxx*",
    "*xxHutxxvatlhxx*",
    "*wa'maHxcha'maH*",
    "*xwejmaHxloSmaH*",
    "*xvaghmaHxvaghx*",
    "*xxxxxxrepxxxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xxHeghlu'meHxx*",
    "*xxQaQxjajvamxx*",
    "x+x1234xxxtupxxx",
    "xSuSxxxxghuHmoHx",
    "xHoSxx||||||||||",
};
// {row, column, length}, row/column counted from 0 (the apostrophe is one cell)
static const WcWord DAH = {0, 2, 3}, PAGH = {0, 11, 4}, VATLH = {5, 8, 5}, REP = {9, 7, 3};
// hour tens: wa'maH (10-19), cha'maH (20-23)
static const WcWord H_10 = {1, 1, 6}, H_20 = {1, 8, 7};
// hour digits 1..9 (index = digit - 1): wa' cha' wej loS vagh jav Soch chorgh Hut
static const WcWord H_DIGIT[9] = {{2, 2, 3}, {2, 6, 4}, {2, 11, 3}, {3, 2, 3}, {3, 6, 4},
                                  {3, 11, 3}, {4, 2, 4}, {4, 7, 6}, {5, 3, 3}};
// minute tens 10..50 (index = tens - 1): wa'maH cha'maH wejmaH loSmaH vaghmaH, and the unit vagh (5)
static const WcWord M_TENS[5] = {{6, 1, 6}, {6, 8, 7}, {7, 2, 6}, {7, 9, 6}, {8, 2, 7}};
static const WcWord M_VAGH = {8, 10, 4};
// extra words (easter egg): Heghlu'meH QaQ jajvam ("today is a good day to die")
static const WcWord EXTRA[3] = {{11, 3, 10}, {12, 3, 3}, {12, 7, 6}};
// row 14: "+ 1 2 3 4  tup" (digits in columns 3..6, no plural)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 10, 3};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void hour_words(int h, WcMark &m) {  // h = 0..23
  if (h == 0) { m.word(PAGH); return; }             // pagh: zero, without vatlh
  if (h >= 20) m.word(H_20);
  else if (h >= 10) m.word(H_10);
  if (h % 10) m.word(H_DIGIT[h % 10 - 1]);
  m.word(VATLH);
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(DAH);
  if (!valid) return;  // no time: only the prefix
  hour_words(hour % 24, m);
  const int m5 = minute / 5;  // 0..11: tens m5 / 2 (wa'maH ... vaghmaH), odd steps + vagh
  if (m5 >= 2) m.word(M_TENS[m5 / 2 - 1]);
  if (m5 & 1) m.word(M_VAGH);
  m.word(REP);
  const int mm = minute % 5;  // "+ 1..4 tup"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_WORD);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"tlh","dec":".",
"notime_msg":"The clock has no time yet (no internet or NTP).",
"btn_settime":"Take time from phone/PC",
"ap_info":"Hotspot “{ap}” active. Please enter your network below under <b>Wi-Fi</b>.",
"sec_show":"Display","on":"Clock switched on","swMin":"Single minutes (+ 1–4 tup)",
"brD":"Brightness day","brN":"Brightness night","cur":"Current limit (mA)",
"hint_show":"Night 0 % = display off at night. Choose the current limit to suit the power supply (256 LEDs already need approx. 256 mA idle current).",
"sec_col":"Colours",
"hint_col":"“Random” changes every full hour. “Temperature”: cold dark blue, yellow, comfort green, orange, hot red (according to the scale under additional displays).",
"g_time":"Time","g_vent":"SuS","g_alarm":"ghuHmoH","g_batt":"HoS","g_tout":"Temperature outside","g_tin":"Temperature inside",
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
"swExtra":"Show Heghlu'meH QaQ jajvam",
"apiTo":"Values valid for (min, 0 = always)",
"v_out":"Outside","v_in":"Inside","v_batt":"Battery (HoS)","v_la":"Ventilate (SuS) / alarm (ghuHmoH)","on_":"on","off_":"off",
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
}  // namespace wc_scifi_tlh
static const WcLangDef WC_LANG = {
    "scifi_TLH", "tlhIngan Hol", wc_scifi_tlh::GRID,
    {14, 1, 3},   // SuS
    {14, 8, 7},   // ghuHmoH
    {15, 1, 3},   // HoS
    {15, 6, 10},  // battery bars
    wc_scifi_tlh::EXTRA, 3,  // Heghlu'meH QaQ jajvam
    wc_scifi_tlh::time_words,
    "mutlhaq", "Mutlhaq",
    52.5200f, 13.4050f,            // Berlin
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Berlin
    "%Y-%m-%d",
    wc_scifi_tlh::UI_JSON,
};
