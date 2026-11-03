/*
  wc_lang_DK.h - Wordclock 16x16, language file DK (Dansk), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_DK.scad (check: python3 tools/check_lang.py DK).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_DK.txt)
  Satzbau (Standard-Dänisch, „halv“-System): KLOKKEN ER [<Minuten> OVER|I] [HALV] <Stunde>
  Ab :25 bezieht sich die Uhrzeit auf die nächste Stunde (HALV TRE = 2:30, wie „halb drei“).
  :00 <Stunde>, :05 FEM OVER, :10 TI OVER, :15 KVART OVER, :20 TYVE OVER, :25 FEM I HALV,
  :30 HALV, :35 FEM OVER HALV, :40 TYVE I, :45 KVART I, :50 TI I, :55 FEM I
  Beispiel: 9:25 = KLOKKEN ER FEM I HALV TI.
  Kein Wort für „Uhr“ zur vollen Stunde (9:00 = KLOKKEN ER NI). 1 Uhr = ET. 12-Stunden-Anzeige:
  0 und 12 Uhr = TOLV. OVER = nach, I = vor. FEM und TI stehen je zweimal im Raster (Minuten oben,
  Stunden unten).
  Minutenzeile: + 1 MINUT (Einzahl, die ersten 5 Felder von MINUTTER), + 2..4 MINUTTER.
  Zusatzwörter (Schalter „Vis HEJ“): HEJ („Hallo“, Gruß).
  INFO_EN
  Sentence (standard Danish, "halv" system): KLOKKEN ER [<minutes> OVER|I] [HALV] <hour>
  From :25 on the time refers to the next hour (HALV TRE = 2:30, "half to three").
  :00 <hour>, :05 FEM OVER, :10 TI OVER, :15 KVART OVER, :20 TYVE OVER, :25 FEM I HALV,
  :30 HALV, :35 FEM OVER HALV, :40 TYVE I, :45 KVART I, :50 TI I, :55 FEM I
  Example: 9:25 = KLOKKEN ER FEM I HALV TI (five to half ten).
  No word for "o'clock" (9:00 = KLOKKEN ER NI). 1 o'clock = ET. 12-hour display: 0 and 12 o'clock
  = TOLV. OVER = past, I = to. FEM and TI are in the grid twice (minutes at the top, hours below).
  Minute row: + 1 MINUT (singular, the first 5 cells of MINUTTER), + 2..4 MINUTTER.
  Extra words (switch "Vis HEJ"): HEJ ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_dk {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xKLOKKENxxERxx*",
    "*xxFEMxxxxxTIxx*",
    "*xKVARTxxHEJxxx*",
    "*xxxxxxxxTYVExx*",
    "*xxOVERxxxxxIxx*",
    "*xxxxxHALVxxxxx*",
    "*xxETxxxxxxTOxx*",
    "*xTRExxxxFIRExx*",
    "*xxFEMxxxSEKSxx*",
    "*xSYVxxxxOTTExx*",
    "*xxxNIxxxxxTIxx*",
    "*xxxxELLEVExxxx*",
    "*xxxxxTOLVxxxxx*",
    "x+x1234xMINUTTER",
    "xUDLUFTExxxALARM",
    "xBATTx||||||||||",
};
// {row, column, length}, row/column counted from 0 (columns count characters, Å/Ä/Ö/Æ/Ø = one cell)
static const WcWord KLOKKEN = {0, 2, 7}, ER = {0, 11, 2};
static const WcWord M_FEM = {1, 3, 3}, M_TI = {1, 11, 2}, KVART = {2, 2, 5}, M_TYVE = {3, 9, 4};
static const WcWord OVER = {4, 3, 4}, I = {4, 12, 1}, HALV = {5, 6, 4};  // OVER = past, I = to
// hour 0..11 (0 = twelve)
static const WcWord HOURS[12] = {{12, 6, 4}, {6, 3, 2}, {6, 11, 2}, {7, 2, 3}, {7, 9, 4}, {8, 3, 3},
                                 {8, 9, 4}, {9, 2, 3}, {9, 9, 4}, {10, 4, 2}, {10, 11, 2}, {11, 5, 6}};
// extra words (easter egg): HEJ ("hello", greeting)
static const WcWord EXTRA[1] = {{2, 9, 3}};
// row 14: "+ 1 2 3 4  MINUTTER" (digits in columns 3..6), singular MINUT = the first 5 cells
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 8}, MIN_ONE = {13, 8, 5};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(KLOKKEN);
  m.word(ER);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 5) h = (h + 1) % 12;  // from "fem i halv" on the next hour counts
  switch (m5) {
    case 0: break;
    case 1: m.word(M_FEM); m.word(OVER); break;
    case 2: m.word(M_TI); m.word(OVER); break;
    case 3: m.word(KVART); m.word(OVER); break;
    case 4: m.word(M_TYVE); m.word(OVER); break;
    case 5: m.word(M_FEM); m.word(I); m.word(HALV); break;
    case 6: m.word(HALV); break;
    case 7: m.word(M_FEM); m.word(OVER); m.word(HALV); break;
    case 8: m.word(M_TYVE); m.word(I); break;
    case 9: m.word(KVART); m.word(I); break;
    case 10: m.word(M_TI); m.word(I); break;
    default: m.word(M_FEM); m.word(I); break;
  }
  m.word(HOURS[h]);
  const int mm = minute % 5;  // "+ 1 MINUT" or "+ 2..4 MINUTTER"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(mm == 1 ? MIN_ONE : MIN_WORD);  // singular: without the plural ending
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"da","dec":",",
"notime_msg":"Uret har endnu ingen tid (intet internet eller NTP).",
"btn_settime":"Overtag tid fra telefon/pc",
"ap_info":"Hotspot »{ap}« aktiv. Indtast dit netværk nedenfor under <b>Wi-Fi</b>.",
"sec_show":"Visning","on":"Uret tændt","swMin":"Enkelte minutter (+ 1–4 MINUTTER)",
"brD":"Lysstyrke dag","brN":"Lysstyrke nat","cur":"Strømgrænse (mA)",
"hint_show":"Nat 0 % = displayet slukket om natten. Vælg strømgrænsen efter strømforsyningen (256 lysdioder bruger allerede ca. 256 mA i hvile).",
"sec_col":"Farver",
"hint_col":"»Tilfældig« skifter hver hele time. »Temperatur«: koldt mørkeblåt, gult, behageligt grønt, orange, varmt rødt (efter skalaen under ekstra visninger).",
"g_time":"Tid","g_vent":"UDLUFTE","g_alarm":"ALARM","g_batt":"BATT","g_tout":"Temperatur ude","g_tin":"Temperatur inde",
"pal_0":"Varmhvid","pal_1":"Hvid","pal_2":"Rød","pal_3":"Orange","pal_4":"Gul","pal_5":"Grøn","pal_6":"Blå","pal_7":"Violet",
"c_random":"Tilfældig","c_temp":"Temperatur","c_pride":"Pride","c_custom":"egen farve",
"sec_fx":"Effekter",
"fx_rainbow":"Regnbue","fx_aurora":"Nordlys","fx_matrix":"Matrix","fx_fire":"Ild","fx_confetti":"Konfetti","fx_stars":"Stjernehimmel",
"fx_blink":"Blink","fx_blink_own":"Blink (egen farve)","stop":"Stop",
"fxd":"Effektvarighed","blk":"Blinkcyklus",
"hint_fx":"Varighed 0 s = kører indtil »Stop«. Effekter kører altid med mindst 10 % lysstyrke, også om natten ved 0 % eller når uret er slukket.",
"fx_started":"{fx} startet","fx_stopped":"Effekt stoppet",
"txt":"Rulletekst","txt_ph":"Skriv tekst","txt_start":"Vis tekst","txt_started":"Tekst startet",
"hint_txt":"Hvert bogstav fylder hele matrixen. Vises så længe som effektens varighed (mindst én gang), i tidens farve (tilfældig = regnbue). Latinske, græske og kyrilliske bogstaver, tal, tegnsætning, € og ♥. HTTP: /api/set?text=…",
"sec_sun":"Dag / nat","nmode":"Nattilstand","nm_mix":"Blandet","nm_sun":"Solens stilling","nm_fixed":"Faste tider",
"lat":"Breddegrad","lon":"Længdegrad","nso":"Forskydning nattens start (min)","neo":"Forskydning nattens slut (min)",
"nme":"Nat ikke før","nml":"Nat ikke efter","nfs":"Nat fra","nfe":"Nat til",
"sunrise":"Solopgang","sunset":"Solnedgang","night_today":"Nat i dag","now":"Nu",
"nmh_0":"Forskydning: + efter, − før solnedgang eller solopgang. Koordinater f.eks. fra en kort-app (højreklik på stedet).",
"nmh_1":"De faste tider gælder hver dag.",
"nmh_2":"Natten begynder ved solnedgang (plus forskydning), men ikke før det indstillede tidspunkt, og slutter ved solopgang (plus forskydning), men ikke efter det indstillede tidspunkt.",
"day":"Dag","night":"Nat",
"sec_extra":"Ekstra visninger","swTemp":"Temperaturprikker (venstre ude, højre inde)","tOnl":"Udetemperatur fra Open-Meteo (sted)",
"scale_out":"Skala ude (°C)","scale_in":"Skala inde (°C)",
"swLuft":"Vis UDLUFTE","swAlarm":"Vis ALARM","swAkku":"Vis BATT","swExtra":"Vis HEJ",
"apiTo":"Værdier gyldige i (min, 0 = altid)",
"v_out":"Ude","v_in":"Inde","v_batt":"Batteri","v_la":"Udluftning / alarm","on_":"til","off_":"fra",
"hint_extra":"Inde, batteri, udluftning og alarm (og ude, hvis uden Open-Meteo) kommer udefra, f.eks. via browser, script eller smart home:",
"sec_api":"HTTP-styring",
"hint_api1":"Fra andre systemer via browser, script eller smart home (GET eller POST til <code>/api/set</code>, flere parametre kan kombineres). Lysstyrke, farver og kontakter gemmes, effekter kører i den indstillede varighed.",
"hint_api2":"Farver: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatur: temp) eller rrggbb · Kontakter: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effekter: {fx}, stop · fxcolor: farvenavn eller rrggbb. Strømgrænse, Wi-Fi og system kun her i webgrænsefladen.",
"sec_time":"Tid","ntpD":"NTP-server","ntp_auto":"automatisk (DHCP)","ntp_manual":"manuel","ntp_server":"Server",
"ntp_fallback":"Reserveserver (hvis routeren ikke leverer en, gælder efter genstart)",
"loc":"Sted","loc_custom":"eget sted (koordinater)","tz_from_loc":"fra stedet {city}",
"tz":"Tidszone","tz_cet":"Centraleuropa (DK, SE, NO, DE …)","tz_wet":"London, Lissabon (WET)","tz_eet":"Østeuropa (Kyiv, Athen, Bukarest)",
"tz_trt":"Tyrkiet","tz_eat":"Østafrika (Tanzania, Kenya)","tz_utc":"UTC",
"tz_use":"USA øst","tz_usc":"USA central","tz_usm":"USA Mountain","tz_usw":"USA vest",
"tz_wib":"Indonesien (Jakarta)","tz_cst":"Kina","tz_kst":"Korea","tz_jst":"Japan","tz_aus":"Australien øst",
"tz_custom":"egen (POSIX TZ) …","tz_posix":"POSIX-tidszone","ntp_active":"Aktiv server",
"ntp_hint":"Automatisk: server fra routeren (DHCP), ellers den indtastede som reserve. Skift mellem automatisk og manuel genstarter uret.",
"ntp_nodhcp":"DHCP-NTP er ikke tilgængelig i denne boardpakke – den indtastede server bruges.",
"sec_wifi":"Wi-Fi","ssid":"Netværk (SSID)","scan":"Søg netværk","pass":"Adgangskode","pass_ph":"lad stå tomt = behold nuværende",
"host":"Enhedsnavn (http://navn.local)","save_wifi":"Gem & forbind igen",
"status":"Status","ip":"IP","last_err":"Seneste fejl",
"hint_wifi":"Hvis Wi-Fi ikke findes ved opstart, åbner uret hotspottet »{ap}« (uden adgangskode, http://192.168.4.1).",
"w_conn":"forbundet til {ssid}","w_ap":"Hotspot aktiv ({ip})","w_none":"ikke forbundet",
"scanning":"Søger …","scan_none":"Ingen netværk fundet","scan_err":"Søgning mislykkedes",
"wr_2":"godkendelse udløbet","wr_15":"forkert adgangskode?","wr_201":"netværk ikke fundet","wr_202":"godkendelse afvist (adgangskode?)",
"wr_203":"tilknytning mislykkedes","wr_204":"forkert adgangskode?","wr_205":"forbindelse mislykkedes","wr_8":"afbrudt",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi afbrudt","net_lost":"ingen forbindelse til uret",
"sec_sys":"System","mir":"LED 0 forfra øverst til højre (spejlvend)","srp":"Matrix forbundet i zigzag",
"restart":"Genstart","reset":"Fabriksnulstilling",
"q_restart":"Genstart uret?","q_reset":"Slet alle indstillinger inklusive Wi-Fi?",
"language":"Sprog","firmware":"Firmware","uptime":"Oppetid","heap":"Ledig hukommelse",
"footer":"{ap} – byggevejledning, kode og printfiler:",
"saved":"Gemt","saved_restart":"Gemt – uret genstarter …","save_err":"Fejl ved lagring",
"time_set":"Tid overtaget","restarting":"Uret genstarter …",
"srv_no_network":"Intet netværk indtastet","srv_back":"Tilbage","srv_saved":"Wi-Fi gemt",
"srv_connecting":"Uret forbinder nu til","srv_restart":"og genstarter for at gøre det. Hotspottet forsvinder.",
"srv_reach":"Derefter tilgængeligt på","srv_reach2":"eller via IP-adressen fra routeren eller den serielle monitor.",
"srv_retry":"Hvis forbindelsen mislykkes, vises hotspottet igen efter ca. 30 sekunder.",
"srv_not_found":"Ikke fundet"
})JSON";
}  // namespace wc_dk
static const WcLangDef WC_LANG = {
    "DK", "Dansk", wc_dk::GRID,
    {14, 1, 7},  // UDLUFTE
    {14, 11, 5}, // ALARM
    {15, 1, 4},  // BATT
    {15, 6, 10}, // battery bars
    wc_dk::EXTRA, 1,  // HEJ
    wc_dk::time_words,
    "ordur", "Ordur",
    55.6761f, 12.5683f,    // København
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Copenhagen
    "%d.%m.%Y",
    wc_dk::UI_JSON,
};
