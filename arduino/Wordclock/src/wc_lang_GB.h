/*
  wc_lang_GB.h - Wordclock 16x16, language file GB (English), v2.0
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_GB.scad (check: python3 tools/check_lang.py GB).
  This file is also the reference for the ui_json keys of all other languages.
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_GB.txt)
  Satzbau: IT IS [<Minuten> PAST|TO] <Stunde> [OCLOCK]
  Ab :35 („twenty five to“) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 <Stunde> OCLOCK, :05 FIVE PAST, :10 TEN PAST, :15 QUARTER PAST, :20 TWENTY PAST,
  :25 TWENTY FIVE PAST, :30 HALF PAST, :35 TWENTY FIVE TO, :40 TWENTY TO, :45 QUARTER TO,
  :50 TEN TO, :55 FIVE TO
  TWENTY FIVE wird aus TWENTY + FIVE zusammengesetzt (FIVE der Minuten).
  12-Stunden-Anzeige: 0 und 12 Uhr = TWELVE. OCLOCK nur zur vollen Stunde.
  Minutenzeile: + 1 MINUTE (Einzahl), + 2..4 MINUTES.
  Zusatzwörter (Schalter „Show HELLO“): HELLO („Hallo“, Gruß).
  INFO_EN
  Sentence: IT IS [<minutes> PAST|TO] <hour> [OCLOCK]
  From :35 ("twenty five to") on the time refers to the next hour.
  :00 <hour> OCLOCK, :05 FIVE PAST, :10 TEN PAST, :15 QUARTER PAST, :20 TWENTY PAST,
  :25 TWENTY FIVE PAST, :30 HALF PAST, :35 TWENTY FIVE TO, :40 TWENTY TO, :45 QUARTER TO,
  :50 TEN TO, :55 FIVE TO
  TWENTY FIVE is made of TWENTY + FIVE (FIVE of the minutes).
  12-hour display: 0 and 12 o'clock = TWELVE. OCLOCK only at the full hour.
  Minute row: + 1 MINUTE (singular), + 2..4 MINUTES.
  Extra words (switch "Show HELLO"): HELLO ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_gb {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xxxxITxISxxxxx*",
    "*xxxQUARTERxxxx*",
    "*xxxTWENTYHELLO*",
    "*xxFIVExxTENxxx*",
    "*xxxxxHALFxxxxx*",
    "*xxPASTxxxTOxxx*",
    "*xxONExxxTWOxxx*",
    "*xTHREExxFOURxx*",
    "*xxFIVExxxSIXxx*",
    "*xSEVENxxEIGHTx*",
    "*xxNINExxxTENxx*",
    "*ELEVENxxTWELVE*",
    "*xxxxOCLOCKxxxx*",
    "x+x1234xMINUTESx",
    "xVENTILATExALARM",
    "xBATTx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord IT = {0, 5, 2}, IS = {0, 8, 2};
static const WcWord M_QUARTER = {1, 4, 7}, M_TWENTY = {2, 4, 6}, M_FIVE = {3, 3, 4}, M_TEN = {3, 9, 3};
static const WcWord HALF = {4, 6, 4}, PAST = {5, 3, 4}, TO = {5, 10, 2}, OCLOCK = {12, 5, 6};
// hour 0..11 (0 = twelve)
static const WcWord HOURS[12] = {{11, 9, 6}, {6, 3, 3}, {6, 9, 3},  {7, 2, 5},  {7, 9, 4},  {8, 3, 4},
                                 {8, 10, 3}, {9, 2, 5}, {9, 9, 5},  {10, 3, 4}, {10, 10, 3}, {11, 1, 6}};
// extra words (easter egg): HELLO ("hello", greeting)
static const WcWord EXTRA[1] = {{2, 10, 5}};
// row 14: "+ 1 2 3 4  MINUTES" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 7}, MIN_ONE = {13, 8, 6};  // MINUTES / MINUTE
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(IT);
  m.word(IS);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 7) h = (h + 1) % 12;  // from "twenty five to" on the next hour counts
  switch (m5) {
    case 0: break;
    case 1: m.word(M_FIVE); m.word(PAST); break;
    case 2: m.word(M_TEN); m.word(PAST); break;
    case 3: m.word(M_QUARTER); m.word(PAST); break;
    case 4: m.word(M_TWENTY); m.word(PAST); break;
    case 5: m.word(M_TWENTY); m.word(M_FIVE); m.word(PAST); break;
    case 6: m.word(HALF); m.word(PAST); break;
    case 7: m.word(M_TWENTY); m.word(M_FIVE); m.word(TO); break;
    case 8: m.word(M_TWENTY); m.word(TO); break;
    case 9: m.word(M_QUARTER); m.word(TO); break;
    case 10: m.word(M_TEN); m.word(TO); break;
    default: m.word(M_FIVE); m.word(TO); break;
  }
  m.word(HOURS[h]);
  if (m5 == 0) m.word(OCLOCK);
  const int mm = minute % 5;  // "+ 1 MINUTE" or "+ 2..4 MINUTES"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(mm == 1 ? MIN_ONE : MIN_WORD);  // singular: without the final S
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"en","dec":".",
"notime_msg":"The clock has no time yet (no internet or NTP).",
"btn_settime":"Take time from phone/PC",
"ap_info":"Hotspot “{ap}” active. Please enter your network below under <b>Wi-Fi</b>.",
"sec_show":"Display","on":"Clock switched on","swMin":"Single minutes (+ 1–4 MINUTES)",
"brD":"Brightness day","brN":"Brightness night","cur":"Current limit (mA)",
"hint_show":"Night 0 % = display off at night. Choose the current limit to suit the power supply (256 LEDs already need approx. 256 mA idle current).",
"sec_col":"Colours",
"hint_col":"“Random” changes every full hour. “Temperature”: cold dark blue, yellow, comfort green, orange, hot red (according to the scale under additional displays).",
"g_time":"Time","g_vent":"VENTILATE","g_alarm":"ALARM","g_batt":"BATT","g_tout":"Temperature outside","g_tin":"Temperature inside",
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
"swExtra":"Show HELLO",
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
}  // namespace wc_gb
static const WcLangDef WC_LANG = {
    "GB", "English", wc_gb::GRID,
    {14, 1, 9},   // VENTILATE
    {14, 11, 5},  // ALARM
    {15, 1, 4},   // BATT
    {15, 6, 10},  // battery bars
    wc_gb::EXTRA, 1,  // HELLO
    wc_gb::time_words,
    "wordclock", "Wordclock",
    51.5074f, -0.1278f,           // London
    "GMT0BST,M3.5.0/1,M10.5.0",   // Europe/London
    "%d/%m/%Y",
    wc_gb::UI_JSON,
};
