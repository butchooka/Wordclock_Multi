/*
  wc_lang_scifi_NAV.h - Wordclock 16x16, language file scifi_NAV (Na'vi), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_scifi_NAV.scad (check: python3 tools/check_lang.py scifi_NAV).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_scifi_NAV.txt)
  Kürzel scifi_NAV (Kunstsprache, kein Land). Standort Berlin (bestehender Eintrag, Zeitzone Mitteleuropa).
  Satzbau: KRRLIK LU <Stunde> [SÌ <Minuten>] („Zeitpunkt ist <n-te Stunde> [und <Minuten>]“, Umgangsform
  nach „lu mrrve sì vomun“). Immer Bezug auf die volle Stunde (keine nächste Stunde, kein „vor“).
  Zahlen im Oktalsystem (Basis 8): Minuten = Achter + VO(L) + Einer, im Raster aus Bausteinen zusammengesetzt,
  im Text zusammengeschrieben. Achter: ME 2, PXE 3, TSÌ 4, MRR 5, PU 6; VOL = 8; Einer nach VO: (L)AW 1,
  MUN 2, PEY 3, SÌNG 4, MRR 5, FU 6, HIN 7.
  :00 KRRLIK LU <Stunde>, :05 SÌ MRR (5), :10 SÌ VOMUN (12 okt.), :15 SÌ VOHIN (17), :20 SÌ MEVOSÌNG (24),
  :25 SÌ PXEVOLAW (31), :30 SÌ PXEVOFU (36), :35 SÌ TSÌVOPEY (43), :40 SÌ MRRVOL (50),
  :45 SÌ MRRVOMRR (55), :50 SÌ PUVOMUN (62), :55 SÌ PUVOHIN (67); z. B. 3:25 KRRLIK LU PXEYVE SÌ PXEVOLAW.
  Stunden als Ordnungszahlen (12-Stunden-Zählung): 'AWVE 1, MUVE 2, PXEYVE 3, TSÌVE 4, MRRVE 5, PUVE 6,
  KIVE 7, VOLVE 8, VOLAWVE 9, VOMUVE 10, VOPEYVE 11, VOSÌVE 12. 12 und 0 Uhr = VOSÌVE.
  Ordnungszahlen nach der Grammatik „Horen leNa'vi“ (-ve; 9.-12. aus VOL + -awve/-muve/-peyve/-sìve).
  Ohne gültige Uhrzeit leuchtet nur KRRLIK LU.
  Minutenzeile: + 1..4 TRRPXÌVI (Minute; nach einer Zahl keine Mehrzahlform). Die Ziffern 1-4 sind oktal gleich.
  Ersatzwörter: LÜFTEN = HUFWE („Wind“), ALARM = HRRAP („Gefahr“), AKKU = TSWAL („Kraft, Stärke“;
  abgeleitet aus dem belegten LETSWAL „mächtig“ = le- + tswal).
  Zusatzwörter (Schalter „Show OEL NGATI KAMEIE“, aus = Standard): OEL NGATI KAMEIE („Ich sehe dich“, Gruß).
  Sonderzeichen: Ì (TSÌVE, VOSÌVE, SÌ, TSÌ, SÌNG, TRRPXÌVI) und der Apostroph ' ('AWVE) sind je eine Zelle
  (Metriken vorhanden). Weboberfläche und ESPHome-Entitäten auf Englisch (Na'vi hat kaum Technikwortschatz),
  Uhrwörter auf Na'vi. Gerätename liukrr (lì'u = Wort, krr = Zeit), Hotspot LiuKrr.
  INFO_EN
  Code scifi_NAV (constructed language, no country). Location Berlin (existing entry, Central European time).
  Sentence: KRRLIK LU <hour> [SÌ <minutes>] ("the point in time is <nth hour> [and <minutes>]", colloquial form
  as in "lu mrrve sì vomun"). Always counted from the full hour (no next hour, no "before").
  Numbers are octal (base 8): minutes = eights + VO(L) + ones, built from parts in the grid and written as one
  word in the text. Eights: ME 2, PXE 3, TSÌ 4, MRR 5, PU 6; VOL = 8; ones after VO: (L)AW 1, MUN 2, PEY 3,
  SÌNG 4, MRR 5, FU 6, HIN 7.
  :00 KRRLIK LU <hour>, :05 SÌ MRR (5), :10 SÌ VOMUN (12 octal), :15 SÌ VOHIN (17), :20 SÌ MEVOSÌNG (24),
  :25 SÌ PXEVOLAW (31), :30 SÌ PXEVOFU (36), :35 SÌ TSÌVOPEY (43), :40 SÌ MRRVOL (50),
  :45 SÌ MRRVOMRR (55), :50 SÌ PUVOMUN (62), :55 SÌ PUVOHIN (67); e.g. 3:25 KRRLIK LU PXEYVE SÌ PXEVOLAW.
  Hours as ordinal numbers (12-hour count): 'AWVE 1, MUVE 2, PXEYVE 3, TSÌVE 4, MRRVE 5, PUVE 6,
  KIVE 7, VOLVE 8, VOLAWVE 9, VOMUVE 10, VOPEYVE 11, VOSÌVE 12. 12:00 and 0:00 = VOSÌVE.
  Ordinals after the grammar "Horen leNa'vi" (-ve; 9th-12th from VOL + -awve/-muve/-peyve/-sìve).
  Without a valid time only KRRLIK LU is lit.
  Minute row: + 1..4 TRRPXÌVI (minute; no plural form after a number). The digits 1-4 are the same in octal.
  Substitute words: VENTILATE = HUFWE ("wind"), ALARM = HRRAP ("danger"), BATTERY = TSWAL ("strength, power";
  derived from the attested LETSWAL "powerful" = le- + tswal).
  Extra words (switch "Show OEL NGATI KAMEIE", off by default): OEL NGATI KAMEIE ("I see you", greeting).
  Special characters: Ì (TSÌVE, VOSÌVE, SÌ, TSÌ, SÌNG, TRRPXÌVI) and the apostrophe ' ('AWVE) are one cell
  each (metrics available). Web interface and ESPHome entities in English (Na'vi has hardly any technical
  vocabulary), clock words in Na'vi. Device name liukrr (lì'u = word, krr = time), hotspot LiuKrr.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_scifi_nav {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
// The apostrophe ' ('AWVE) and Ì are letters and take one cell each.
static const char *const GRID[16] = {
    "*xxKRRLIKxLUxxx*",
    "*x'AWVExxMUVExx*",
    "*xPXEYVExTSÌVEx*",
    "*xMRRVExxxPUVEx*",
    "*xKIVExxVOLVExx*",
    "*VOLAWVExVOMUVE*",
    "*VOPEYVExVOSÌVE*",
    "*xSÌxMExPXExTSÌ*",
    "*xMRRxPUxVOLAWx*",
    "*xMUNxPEYxSÌNGx*",
    "*xxMRRxFUxHINxx*",
    "*xxOELxxNGATIxx*",
    "*xxxxKAMEIExxxx*",
    "x+x1234xTRRPXÌVI",
    "xHUFWExxxxHRRAPx",
    "TSWALx||||||||||",
};
// {row, column, length}, row/column counted from 0 (Ì is one cell)
static const WcWord KRRLIK = {0, 3, 6}, LU = {0, 10, 2}, SI = {7, 2, 2};
// hours 0..11 as ordinal numbers (0 = VOSÌVE, twelfth)
static const WcWord HOURS[12] = {{6, 9, 6}, {1, 2, 5}, {1, 9, 4},  {2, 2, 6}, {2, 9, 5}, {3, 2, 5},
                                 {3, 10, 4}, {4, 2, 4}, {4, 8, 5}, {5, 1, 7}, {5, 9, 6}, {6, 1, 7}};
// minutes as octal numbers, built from parts: <eights> + VO(L) + <ones>, e.g. PU + VO + HIN = PUVOHIN (67 octal = 55)
// eights: ME (2), PXE (3), TSÌ (4), MRR (5), PU (6); MRR alone = 5 minutes
static const WcWord E_ME = {7, 5, 2}, E_PXE = {7, 8, 3}, E_TSI = {7, 12, 3}, E_MRR = {8, 2, 3}, E_PU = {8, 6, 2};
// VO (eight in a compound), L (VOL = eight with ones = 0), AW (one after VOL: VOLAW)
static const WcWord VO = {8, 9, 2}, VO_L = {8, 11, 1}, U_AW = {8, 12, 2};
// ones after VO: MUN (2), PEY (3), SÌNG (4), MRR (5), FU (6), HIN (7)
static const WcWord U_MUN = {9, 2, 3}, U_PEY = {9, 6, 3}, U_SING = {9, 10, 4}, U_MRR = {10, 3, 3}, U_FU = {10, 7, 2},
                    U_HIN = {10, 10, 3};
// extra words (easter egg): OEL NGATI KAMEIE ("I see you", greeting)
static const WcWord EXTRA[3] = {{11, 3, 3}, {11, 8, 5}, {12, 5, 6}};
// row 14: "+ 1 2 3 4  TRRPXÌVI" (digits in columns 3..6; no plural form after a number)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 8};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
// minutes 5..55 (m5 = 1..11) as one octal number word, the parts glued without a space
static inline void minutes_word(int m5, WcMark &m) {
  switch (m5) {
    case 1: m.word(E_MRR); break;                                          // MRR       5  =  5 octal
    case 2: m.word(VO); m.glue(U_MUN); break;                              // VOMUN     10 = 12 octal
    case 3: m.word(VO); m.glue(U_HIN); break;                              // VOHIN     15 = 17 octal
    case 4: m.word(E_ME); m.glue(VO); m.glue(U_SING); break;               // MEVOSÌNG  20 = 24 octal
    case 5: m.word(E_PXE); m.glue(VO); m.glue(VO_L); m.glue(U_AW); break;  // PXEVOLAW  25 = 31 octal
    case 6: m.word(E_PXE); m.glue(VO); m.glue(U_FU); break;                // PXEVOFU   30 = 36 octal
    case 7: m.word(E_TSI); m.glue(VO); m.glue(U_PEY); break;               // TSÌVOPEY  35 = 43 octal
    case 8: m.word(E_MRR); m.glue(VO); m.glue(VO_L); break;                // MRRVOL    40 = 50 octal
    case 9: m.word(E_MRR); m.glue(VO); m.glue(U_MRR); break;               // MRRVOMRR  45 = 55 octal
    case 10: m.word(E_PU); m.glue(VO); m.glue(U_MUN); break;               // PUVOMUN   50 = 62 octal
    default: m.word(E_PU); m.glue(VO); m.glue(U_HIN); break;               // PUVOHIN   55 = 67 octal
  }
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(KRRLIK);
  m.word(LU);
  if (!valid) return;  // no time: only the prefix
  const int m5 = minute / 5;
  m.word(HOURS[hour % 12]);  // always the current hour ("<hour> and <minutes>")
  if (m5 > 0) {
    m.word(SI);
    minutes_word(m5, m);
  }
  const int mm = minute % 5;  // "+ 1..4 TRRPXÌVI" (same form in singular and plural)
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_WORD);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"en","dec":".",
"notime_msg":"The clock has no time yet (no internet or NTP).",
"btn_settime":"Take time from phone/PC",
"ap_info":"Hotspot “{ap}” active. Please enter your network below under <b>Wi-Fi</b>.",
"sec_show":"Display","on":"Clock switched on","swMin":"Single minutes (+ 1–4 TRRPXÌVI)",
"brD":"Brightness day","brN":"Brightness night","cur":"Current limit (mA)",
"hint_show":"Night 0 % = display off at night. Choose the current limit to suit the power supply (256 LEDs already need approx. 256 mA idle current).",
"sec_col":"Colours",
"hint_col":"“Random” changes every full hour. “Temperature”: cold dark blue, yellow, comfort green, orange, hot red (according to the scale under additional displays).",
"g_time":"Time","g_vent":"HUFWE","g_alarm":"HRRAP","g_batt":"TSWAL","g_tout":"Temperature outside","g_tin":"Temperature inside",
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
"sec_extra":"Additional displays","swTemp":"Temperature dots (left outside, right inside)","tOnl":"Outdoor temperature from Open-Meteo (location)",
"scale_out":"Scale outside (°C)","scale_in":"Scale inside (°C)",
"swLuft":"Show HUFWE","swAlarm":"Show HRRAP","swAkku":"Show TSWAL","swExtra":"Show OEL NGATI KAMEIE",
"apiTo":"Values valid for (min, 0 = always)",
"v_out":"Outside","v_in":"Inside","v_batt":"TSWAL (battery)","v_la":"HUFWE / HRRAP","on_":"on","off_":"off",
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
}  // namespace wc_scifi_nav
static const WcLangDef WC_LANG = {
    "scifi_NAV", "Na'vi", wc_scifi_nav::GRID,
    {14, 1, 5},   // HUFWE
    {14, 10, 5},  // HRRAP
    {15, 0, 5},   // TSWAL
    {15, 6, 10},  // battery bars
    wc_scifi_nav::EXTRA, 3,  // OEL NGATI KAMEIE
    wc_scifi_nav::time_words,
    "liukrr", "LiuKrr",
    52.5200f, 13.4050f,            // Berlin
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Berlin
    "%Y-%m-%d",
    wc_scifi_nav::UI_JSON,
};
