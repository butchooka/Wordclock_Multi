/*
  wc_lang_scifi_HVA.h - Wordclock 16x16, language file scifi_HVA (Valyrio), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_scifi_HVA.scad (check: python3 tools/check_lang.py scifi_HVA).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_scifi_HVA.txt)
  Kürzel scifi_HVA (Fantasiesprache Hochvalyrisch, eigener Name Valyrio). Standort Roma (vorhandener Eintrag, Europe/Rome).
  Satzbau wie eine Digitaluhr: SĪR <Stunde> <Minuten> (SĪR = „jetzt“), 12-Stunden-Zählung, keine Wörter für
  „nach“, „vor“, „Viertel“ oder „halb“. Zusammengesetzte Zahlen: Einer vor Zehner, der Zehner bekommt einen langen
  Endvokal (AMPA -> AMPĀ, LANTĒPSA -> LANTEPSĀ).
  :00 SĪR <Stunde>, :05 TŌMA, :10 AMPA, :15 TŌMA AMPĀ, :20 LANTĒPSA, :25 TŌMA LANTEPSĀ, :30 HĀRĒPSA,
  :35 TŌMA HĀREPSĀ, :40 IZULĒPSA, :45 TŌMA IZULEPSĀ, :50 TŌMĒPSA, :55 TŌMA TŌMEPSĀ;
  z. B. 3:25 SĪR HĀRE TŌMA LANTEPSĀ, 11:45 SĪR MĒRE AMPĀ TŌMA IZULEPSĀ.
  Stunden: MĒRE, LANTA, HĀRE, IZULA, TŌMA, BȲRE, SĪKUDA, JĒNQA, VŌRE, AMPA, MĒRE AMPĀ (11),
  LANTA AMPĀ (12 und 0 Uhr). Ohne gültige Uhrzeit leuchtet nur SĪR.
  Minutenzeile: nur + 1..4 ohne Wort, daher keine Einzahl/Mehrzahl.
  Ersatzwörter: LÜFTEN = JELMĀZMA („Wind“), ALARM = PERZYS („Feuer“), AKKU = ĀEKS (Neo-Valyrio, gekürzt
  von āeksior „Macht, Einfluss“). Zusatzwort (Schalter „Show RYTSAS“, aus = Standard): RYTSAS („Hallo“).
  Sonderzeichen: Ā Ē Ī Ō Ȳ sind je eine Zelle (Metriken vorhanden; Ȳ fehlt in manchen Arial-Versionen).
  Die zusammengesetzten Zehnerformen (LANTEPSĀ usw.) folgen der Regel oben und sind noch zu bestätigen.
  Webinterface auf Englisch, Uhrwörter auf Valyrio.
  INFO_EN
  Code scifi_HVA (fictional language High Valyrian, own name Valyrio). Location Roma (existing entry, Europe/Rome).
  Sentence like a digital clock: SĪR <hour> <minutes> (SĪR = "now"), 12-hour count, no words for "past",
  "to", "quarter" or "half". Compound numbers: unit before ten, the ten gets a long final vowel
  (AMPA -> AMPĀ, LANTĒPSA -> LANTEPSĀ).
  :00 SĪR <hour>, :05 TŌMA, :10 AMPA, :15 TŌMA AMPĀ, :20 LANTĒPSA, :25 TŌMA LANTEPSĀ, :30 HĀRĒPSA,
  :35 TŌMA HĀREPSĀ, :40 IZULĒPSA, :45 TŌMA IZULEPSĀ, :50 TŌMĒPSA, :55 TŌMA TŌMEPSĀ;
  e.g. 3:25 SĪR HĀRE TŌMA LANTEPSĀ, 11:45 SĪR MĒRE AMPĀ TŌMA IZULEPSĀ.
  Hours: MĒRE, LANTA, HĀRE, IZULA, TŌMA, BȲRE, SĪKUDA, JĒNQA, VŌRE, AMPA, MĒRE AMPĀ (11),
  LANTA AMPĀ (12:00 and 0:00). Without a valid time only SĪR is lit.
  Minute row: only + 1..4 without a word, so no singular/plural.
  Substitute words: VENTILATE = JELMĀZMA ("wind"), ALARM = PERZYS ("fire"), BATTERY = ĀEKS (Neo-Valyrio,
  shortened from āeksior "power, influence"). Extra word (switch "Show RYTSAS", off by default): RYTSAS ("hello").
  Special characters: Ā Ē Ī Ō Ȳ are one cell each (metrics present; Ȳ is missing in some Arial versions).
  The compound tens (LANTEPSĀ etc.) follow the rule above and still need confirmation.
  Web interface in English, clock words in Valyrio.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_scifi_hva {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*SĪRxMĒRExLANTA*",
    "*HĀRExTŌMAxBȲRE*",
    "*IZULAxSĪKUDAxx*",
    "*xJĒNQAxxxVŌREx*",
    "*AMPAxAMPĀxTŌMA*",
    "*AMPAxLANTĒPSAx*",
    "*AMPĀxLANTEPSĀx*",
    "*HĀRĒPSAxRYTSAS*",
    "*xxxxxxxHĀREPSĀ*",
    "*IZULĒPSAxxxxxx*",
    "*xxxxxxIZULEPSĀ*",
    "*xTŌMĒPSAxxxxxx*",
    "*xxxxxxxTŌMEPSĀ*",
    "xxxxx+x1234xxxxx",
    "xJELMĀZMAxPERZYS",
    "xĀEKSx||||||||||",
};
// {row, column, length}, row/column counted from 0 (Ā Ē Ī Ō Ȳ are one cell)
static const WcWord SIR = {0, 1, 3};
// hours: 1..10 and AMPĀ for 11 (MĒRE AMPĀ) and 12 (LANTA AMPĀ)
static const WcWord H_MERE = {0, 5, 4}, H_LANTA = {0, 10, 5}, H_HARE = {1, 1, 4}, H_IZULA = {2, 1, 5}, H_TOMA = {1, 6, 4}, H_BYRE = {1, 11, 4},
                    H_SIKUDA = {2, 7, 6}, H_JENQA = {3, 2, 5}, H_VORE = {3, 10, 4}, H_AMPA = {4, 1, 4}, H_AMPAA = {4, 6, 4};
// minutes: unit TŌMA, then the ten (plain form alone, long final vowel after TŌMA)
static const WcWord M_TOMA = {4, 11, 4}, M_AMPA = {5, 1, 4}, M_AMPAA = {6, 1, 4};
static const WcWord TENS[2][5] = {
    {{0, 0, 0}, {5, 6, 8}, {7, 1, 7}, {9, 1, 8}, {11, 2, 7}},   // index 1..4 = 20 30 40 50 alone (index 0 unused)
    {{0, 0, 0}, {6, 6, 8}, {8, 8, 7}, {10, 7, 8}, {12, 8, 7}},   // index 1..4 = 25 35 45 55 after TŌMA
};
// extra word (easter egg): RYTSAS ("hello")
static const WcWord EXTRA[1] = {{7, 9, 6}};
// row 14: "+ 1 2 3 4" without a word (digits in columns 7..10)
static const WcWord MIN_PLUS = {13, 5, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 7;
static inline void hour_words(int h, WcMark &m) {  // h = 0..11 (0 = 12)
  static const WcWord *const H[10] = {&H_MERE, &H_LANTA, &H_HARE, &H_IZULA, &H_TOMA,
                                      &H_BYRE, &H_SIKUDA, &H_JENQA, &H_VORE, &H_AMPA};
  if (h == 0) { m.word(H_LANTA); m.word(H_AMPAA); }        // 12 = LANTA AMPĀ
  else if (h == 11) { m.word(H_MERE); m.word(H_AMPAA); }   // 11 = MĒRE AMPĀ
  else m.word(*H[h - 1]);
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(SIR);
  if (!valid) return;  // no time: only the prefix
  hour_words(hour % 12, m);
  const int m5 = minute / 5;          // 0..11
  const int tens = m5 / 2, five = m5 % 2;
  if (five) m.word(M_TOMA);           // unit 5 in front of the ten
  if (tens == 1) m.word(five ? M_AMPAA : M_AMPA);
  else if (tens >= 2) m.word(TENS[five][tens - 1]);
  const int mm = minute % 5;          // "+ 1..4" (no minute word)
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
"g_time":"Time","g_vent":"JELMĀZMA","g_alarm":"PERZYS","g_batt":"ĀEKS","g_tout":"Temperature outside","g_tin":"Temperature inside",
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
"swExtra":"Show RYTSAS",
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
}  // namespace wc_scifi_hva
static const WcLangDef WC_LANG = {
    "scifi_HVA", "Valyrio", wc_scifi_hva::GRID,
    {14, 1, 8},   // JELMĀZMA
    {14, 10, 6},  // PERZYS
    {15, 1, 4},   // ĀEKS
    {15, 6, 10},  // battery bars
    wc_scifi_hva::EXTRA, 1,  // RYTSAS
    wc_scifi_hva::time_words,
    "valyrio", "Valyrio",
    41.9028f, 12.4964f,            // Roma
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Rome
    "%d/%m/%Y",
    wc_scifi_hva::UI_JSON,
};
