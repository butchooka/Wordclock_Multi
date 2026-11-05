/*
  wc_lang_SE.h - Wordclock 16x16, language file SE (Svenska), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_SE.scad (check: python3 tools/check_lang.py SE).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_SE.txt)
  Satzbau (Standard-Schwedisch, „halv“-System): KLOCKAN ÄR [<Minuten> ÖVER|I] [HALV] <Stunde>
  Ab :25 bezieht sich die Uhrzeit auf die nächste Stunde (HALV TRE = 2:30, wie „halb drei“).
  :00 <Stunde>, :05 FEM ÖVER, :10 TIO ÖVER, :15 KVART ÖVER, :20 TJUGO ÖVER, :25 FEM I HALV,
  :30 HALV, :35 FEM ÖVER HALV, :40 TJUGO I, :45 KVART I, :50 TIO I, :55 FEM I
  Beispiel: 9:25 = KLOCKAN ÄR FEM I HALV TIO.
  Kein Wort für „Uhr“ zur vollen Stunde (9:00 = KLOCKAN ÄR NIO). 12-Stunden-Anzeige: 0 und 12 Uhr = TOLV.
  ÖVER = nach, I = vor. FEM und TIO stehen je zweimal im Raster (Minuten oben, Stunden unten).
  Minutenzeile: + 1 MINUT (Einzahl, die ersten 5 Felder von MINUTER), + 2..4 MINUTER.
  Zusatzwörter (Schalter „Visa HEJ“): HEJ („Hallo“, Gruß).
  INFO_EN
  Sentence (standard Swedish, "halv" system): KLOCKAN ÄR [<minutes> ÖVER|I] [HALV] <hour>
  From :25 on the time refers to the next hour (HALV TRE = 2:30, "half to three").
  :00 <hour>, :05 FEM ÖVER, :10 TIO ÖVER, :15 KVART ÖVER, :20 TJUGO ÖVER, :25 FEM I HALV,
  :30 HALV, :35 FEM ÖVER HALV, :40 TJUGO I, :45 KVART I, :50 TIO I, :55 FEM I
  Example: 9:25 = KLOCKAN ÄR FEM I HALV TIO (five to half ten).
  No word for "o'clock" (9:00 = KLOCKAN ÄR NIO). 12-hour display: 0 and 12 o'clock = TOLV.
  ÖVER = past, I = to. FEM and TIO are in the grid twice (minutes at the top, hours below).
  Minute row: + 1 MINUT (singular, the first 5 cells of MINUTER), + 2..4 MINUTER.
  Extra words (switch "Visa HEJ"): HEJ ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_se {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xKLOCKANxxÄRxx*",
    "*xxFEMxxxxTIOxx*",
    "*xKVARTxxHEJxxx*",
    "*xxxxxxxTJUGOxx*",
    "*xxÖVERxxxxxIxx*",
    "*xxxxxHALVxxxxx*",
    "*xETTxxxxxTVÅxx*",
    "*xTRExxxxFYRAxx*",
    "*xxFEMxxxxSEXxx*",
    "*xSJUxxxxÅTTAxx*",
    "*xxNIOxxxxTIOxx*",
    "*xxxxELVAxxxxxx*",
    "*xxxxxTOLVxxxxx*",
    "x+x1234xMINUTERx",
    "xVÄDRAxxxxxxLARM",
    "xBATTx||||||||||",
};
// {row, column, length}, row/column counted from 0 (columns count characters, Å/Ä/Ö/Æ/Ø = one cell)
static const WcWord KLOCKAN = {0, 2, 7}, AR = {0, 11, 2};
static const WcWord M_FEM = {1, 3, 3}, M_TIO = {1, 10, 3}, KVART = {2, 2, 5}, M_TJUGO = {3, 8, 5};
static const WcWord OVER = {4, 3, 4}, I = {4, 12, 1}, HALV = {5, 6, 4};  // ÖVER = past, I = to
// hour 0..11 (0 = twelve)
static const WcWord HOURS[12] = {{12, 6, 4}, {6, 2, 3}, {6, 10, 3}, {7, 2, 3}, {7, 9, 4}, {8, 3, 3},
                                 {8, 10, 3}, {9, 2, 3}, {9, 9, 4}, {10, 3, 3}, {10, 10, 3}, {11, 5, 4}};
// extra words (easter egg): HEJ ("hello", greeting)
static const WcWord EXTRA[1] = {{2, 9, 3}};
// row 14: "+ 1 2 3 4  MINUTER" (digits in columns 3..6), singular MINUT = the first 5 cells
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 7}, MIN_ONE = {13, 8, 5};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(KLOCKAN);
  m.word(AR);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 5) h = (h + 1) % 12;  // from "fem i halv" on the next hour counts
  switch (m5) {
    case 0: break;
    case 1: m.word(M_FEM); m.word(OVER); break;
    case 2: m.word(M_TIO); m.word(OVER); break;
    case 3: m.word(KVART); m.word(OVER); break;
    case 4: m.word(M_TJUGO); m.word(OVER); break;
    case 5: m.word(M_FEM); m.word(I); m.word(HALV); break;
    case 6: m.word(HALV); break;
    case 7: m.word(M_FEM); m.word(OVER); m.word(HALV); break;
    case 8: m.word(M_TJUGO); m.word(I); break;
    case 9: m.word(KVART); m.word(I); break;
    case 10: m.word(M_TIO); m.word(I); break;
    default: m.word(M_FEM); m.word(I); break;
  }
  m.word(HOURS[h]);
  const int mm = minute % 5;  // "+ 1 MINUT" or "+ 2..4 MINUTER"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(mm == 1 ? MIN_ONE : MIN_WORD);  // singular: without the plural ending
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"sv","dec":",",
"notime_msg":"Klockan har ingen tid än (inget internet eller NTP).",
"btn_settime":"Hämta tid från telefon/dator",
"ap_info":"Hotspot ”{ap}” aktiv. Ange ditt nätverk nedan under <b>Wi-Fi</b>.",
"sec_show":"Visning","on":"Klockan påslagen","swMin":"Enstaka minuter (+ 1–4 MINUTER)",
"brD":"Ljusstyrka dag","brN":"Ljusstyrka natt","cur":"Strömgräns (mA)",
"hint_show":"Natt 0 % = displayen släckt på natten. Välj strömgränsen efter nätaggregatet (256 lysdioder drar redan ca 256 mA i vila).",
"sec_col":"Färger",
"hint_col":"”Slumpmässig” byter varje hel timme. ”Temperatur”: kallt mörkblått, gult, behagligt grönt, orange, varmt rött (enligt skalan under extra visningar).",
"g_time":"Tid","g_vent":"VÄDRA","g_alarm":"LARM","g_batt":"BATT","g_tout":"Temperatur ute","g_tin":"Temperatur inne",
"pal_0":"Varmvit","pal_1":"Vit","pal_2":"Röd","pal_3":"Orange","pal_4":"Gul","pal_5":"Grön","pal_6":"Blå","pal_7":"Violett",
"c_random":"Slumpmässig","c_temp":"Temperatur","c_pride":"Pride","c_custom":"egen färg",
"sec_fx":"Effekter",
"fx_rainbow":"Regnbåge","fx_aurora":"Norrsken","fx_matrix":"Matrix","fx_fire":"Eld","fx_confetti":"Konfetti","fx_stars":"Stjärnhimmel",
"fx_blink":"Blinka","fx_blink_own":"Blinka (egen färg)","stop":"Stopp",
"fxd":"Effektlängd","blk":"Blinkcykel",
"hint_fx":"Längd 0 s = körs tills ”Stopp”. Effekter körs alltid med minst 10 % ljusstyrka, även på natten vid 0 % eller när klockan är avstängd.",
"fx_started":"{fx} startad","fx_stopped":"Effekten stoppad",
"txt":"Rulltext","txt_ph":"Skriv text","txt_start":"Visa text","txt_started":"Texten startad",
"hint_txt":"Varje bokstav fyller hela matrisen. Visas lika länge som effektens längd (minst en gång), i tidens färg (slumpvis = regnbåge). Latinska, grekiska och kyrilliska bokstäver, siffror, skiljetecken, € och ♥. HTTP: /api/set?text=…",
"sec_sun":"Dag / natt","nmode":"Nattläge","nm_mix":"Blandat","nm_sun":"Solens läge","nm_fixed":"Fasta tider",
"lat":"Latitud","lon":"Longitud","nso":"Förskjutning nattens början (min)","neo":"Förskjutning nattens slut (min)",
"nme":"Natt inte före","nml":"Natt inte efter","nfs":"Natt från","nfe":"Natt till",
"sunrise":"Soluppgång","sunset":"Solnedgång","night_today":"Natt i dag","now":"Nu",
"nmh_0":"Förskjutning: + efter, − före solnedgång eller soluppgång. Koordinater t.ex. från en kartapp (högerklicka på platsen).",
"nmh_1":"De fasta tiderna gäller varje dag.",
"nmh_2":"Natten börjar vid solnedgången (plus förskjutning), men inte före den inställda tiden, och slutar vid soluppgången (plus förskjutning), men inte efter den inställda tiden.",
"day":"Dag","night":"Natt",
"sec_extra":"Extra visningar","tOnl":"Utetemperatur från Open-Meteo (plats)",
"scale_out":"Skala ute (°C)","scale_in":"Skala inne (°C)",
"swExtra":"Visa HEJ",
"apiTo":"Värden giltiga i (min, 0 = alltid)",
"v_out":"Ute","v_in":"Inne","v_batt":"Batteri","v_la":"Vädra / larm","on_":"på","off_":"av",
"hint_extra":"Inne, batteri, vädra och larm (och ute, om utan Open-Meteo) kommer utifrån, t.ex. via webbläsare, skript eller smarta hem:",
"sec_api":"HTTP-styrning",
"hint_api1":"Från andra system via webbläsare, skript eller smarta hem (GET eller POST till <code>/api/set</code>, flera parametrar kan kombineras). Ljusstyrka, färger och brytare sparas, effekter körs under den inställda längden.",
"hint_api2":"Färger: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatur: temp) eller rrggbb · Brytare: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effekter: {fx}, stop · fxcolor: färgnamn eller rrggbb. Strömgräns, Wi-Fi och system bara här i webbgränssnittet.",
"sec_time":"Tid","ntpD":"NTP-server","ntp_auto":"automatisk (DHCP)","ntp_manual":"manuell","ntp_server":"Server",
"ntp_fallback":"Reservserver (om routern inte anger någon, gäller efter omstart)",
"loc":"Plats","loc_custom":"egen plats (koordinater)","tz_from_loc":"från platsen {city}",
"tz":"Tidszon","tz_cet":"Centraleuropa (SE, DK, NO, DE …)","tz_wet":"London, Lissabon (WET)","tz_eet":"Östeuropa (Kyiv, Aten, Bukarest)",
"tz_trt":"Turkiet","tz_eat":"Östafrika (Tanzania, Kenya)","tz_utc":"UTC",
"tz_use":"USA öst","tz_usc":"USA central","tz_usm":"USA Mountain","tz_usw":"USA väst",
"tz_wib":"Indonesien (Jakarta)","tz_cst":"Kina","tz_kst":"Korea","tz_jst":"Japan","tz_aus":"Australien öst",
"tz_custom":"egen (POSIX TZ) …","tz_posix":"POSIX-tidszon","ntp_active":"Aktiv server",
"ntp_hint":"Automatisk: server från routern (DHCP), annars den angivna som reserv. Byte mellan automatisk och manuell startar om klockan.",
"ntp_nodhcp":"DHCP-NTP finns inte i detta kortpaket – den angivna servern används.",
"sec_wifi":"Wi-Fi","ssid":"Nätverk (SSID)","scan":"Sök nätverk","pass":"Lösenord","pass_ph":"lämna tomt = behåll nuvarande",
"host":"Enhetsnamn (http://namn.local)","save_wifi":"Spara & anslut igen",
"status":"Status","ip":"IP","last_err":"Senaste fel",
"hint_wifi":"Om Wi-Fi inte hittas vid start öppnar klockan hotspoten ”{ap}” (utan lösenord, http://192.168.4.1).",
"w_conn":"ansluten till {ssid}","w_ap":"Hotspot aktiv ({ip})","w_none":"inte ansluten",
"scanning":"Söker …","scan_none":"Inga nätverk hittades","scan_err":"Sökningen misslyckades",
"wr_2":"autentiseringen gick ut","wr_15":"fel lösenord?","wr_201":"nätverket hittades inte","wr_202":"autentisering nekad (lösenord?)",
"wr_203":"associering misslyckades","wr_204":"fel lösenord?","wr_205":"anslutningen misslyckades","wr_8":"frånkopplad",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi frånkopplat","net_lost":"ingen anslutning till klockan",
"sec_sys":"System","mir":"LED 0 framifrån uppe till höger (spegla)","srp":"Matrisen kopplad i sicksack",
"restart":"Starta om","reset":"Fabriksåterställning",
"q_restart":"Starta om klockan?","q_reset":"Radera alla inställningar inklusive Wi-Fi?",
"language":"Språk","firmware":"Firmware","uptime":"Drifttid","heap":"Ledigt minne",
"footer":"{ap} – bygganvisning, kod och utskriftsfiler:",
"saved":"Sparat","saved_restart":"Sparat – klockan startar om …","save_err":"Fel vid sparande",
"time_set":"Tiden övertagen","restarting":"Klockan startar om …",
"srv_no_network":"Inget nätverk angivet","srv_back":"Tillbaka","srv_saved":"Wi-Fi sparat",
"srv_connecting":"Klockan ansluter nu till","srv_restart":"och startar om för detta. Hotspoten försvinner.",
"srv_reach":"Därefter nåbar på","srv_reach2":"eller via IP-adressen från routern eller den seriella monitorn.",
"srv_retry":"Om anslutningen misslyckas visas hotspoten igen efter ungefär 30 sekunder.",
"srv_not_found":"Hittades inte"
})JSON";
}  // namespace wc_se
static const WcLangDef WC_LANG = {
    "SE", "Svenska", wc_se::GRID,
    {14, 1, 5},  // VÄDRA
    {14, 12, 4}, // LARM
    {15, 1, 4},  // BATT
    {15, 6, 10}, // battery bars
    wc_se::EXTRA, 1,  // HEJ
    wc_se::time_words,
    "ordklocka", "Ordklocka",
    59.3293f, 18.0686f,    // Stockholm
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Stockholm
    "%Y-%m-%d",
    wc_se::UI_JSON,
};
