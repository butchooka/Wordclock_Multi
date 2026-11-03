/*
  wc_lang_NO.h - Wordclock 16x16, language file NO (Norsk), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_NO.scad (check: python3 tools/check_lang.py NO).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_NO.txt)
  Satzbau (Norwegisch Bokmål, „halv“-System): KLOKKA ER [<Minuten> OVER|PÅ] [HALV] <Stunde>
  Ab :20 bezieht sich die Uhrzeit auf die nächste Stunde (HALV TRE = 2:30, wie „halb drei“).
  :00 <Stunde>, :05 FEM OVER, :10 TI OVER, :15 KVART OVER, :20 TI PÅ HALV, :25 FEM PÅ HALV,
  :30 HALV, :35 FEM OVER HALV, :40 TI OVER HALV, :45 KVART PÅ, :50 TI PÅ, :55 FEM PÅ
  Beispiel: 9:20 = KLOKKA ER TI PÅ HALV TI.
  Kein Wort für „Uhr“ zur vollen Stunde (9:00 = KLOKKA ER NI). 12-Stunden-Anzeige: 0 und 12 Uhr = TOLV.
  OVER = nach, PÅ = vor. FEM und TI stehen je zweimal im Raster (Minuten oben, Stunden unten).
  Minutenzeile: + 1 MINUTT (Einzahl, die ersten 6 Felder von MINUTTER), + 2..4 MINUTTER.
  Zusatzwörter (Schalter „Vis HEI“): HEI („Hallo“, Gruß).
  INFO_EN
  Sentence (Norwegian Bokmål, "halv" system): KLOKKA ER [<minutes> OVER|PÅ] [HALV] <hour>
  From :20 on the time refers to the next hour (HALV TRE = 2:30, "half to three").
  :00 <hour>, :05 FEM OVER, :10 TI OVER, :15 KVART OVER, :20 TI PÅ HALV, :25 FEM PÅ HALV,
  :30 HALV, :35 FEM OVER HALV, :40 TI OVER HALV, :45 KVART PÅ, :50 TI PÅ, :55 FEM PÅ
  Example: 9:20 = KLOKKA ER TI PÅ HALV TI (ten to half ten).
  No word for "o'clock" (9:00 = KLOKKA ER NI). 12-hour display: 0 and 12 o'clock = TOLV.
  OVER = past, PÅ = to. FEM and TI are in the grid twice (minutes at the top, hours below).
  Minute row: + 1 MINUTT (singular, the first 6 cells of MINUTTER), + 2..4 MINUTTER.
  Extra words (switch "Vis HEI"): HEI ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_no {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xKLOKKAxxxERxx*",
    "*xxFEMxxxxxTIxx*",
    "*xxxxKVARTxxxxx*",
    "*xOVERxxHEIxxxx*",
    "*xxxxxxxxxxPÅxx*",
    "*xxxxxHALVxxxxx*",
    "*xETTxxxxxxTOxx*",
    "*xTRExxxxFIRExx*",
    "*xxFEMxxxSEKSxx*",
    "*xSJUxxxxÅTTExx*",
    "*xxxNIxxxxxTIxx*",
    "*xxxxELLEVExxxx*",
    "*xxxxxTOLVxxxxx*",
    "x+x1234xMINUTTER",
    "xLUFTExxxxxALARM",
    "xBATTx||||||||||",
};
// {row, column, length}, row/column counted from 0 (columns count characters, Å/Ä/Ö/Æ/Ø = one cell)
static const WcWord KLOKKA = {0, 2, 6}, ER = {0, 11, 2};
static const WcWord M_FEM = {1, 3, 3}, M_TI = {1, 11, 2}, KVART = {2, 5, 5};
static const WcWord OVER = {3, 2, 4}, PA = {4, 11, 2}, HALV = {5, 6, 4};
// hour 0..11 (0 = twelve)
static const WcWord HOURS[12] = {{12, 6, 4}, {6, 2, 3}, {6, 11, 2}, {7, 2, 3}, {7, 9, 4}, {8, 3, 3},
                                 {8, 9, 4}, {9, 2, 3}, {9, 9, 4}, {10, 4, 2}, {10, 11, 2}, {11, 5, 6}};
// extra words (easter egg): HEI ("hello", greeting)
static const WcWord EXTRA[1] = {{3, 8, 3}};
// row 14: "+ 1 2 3 4  MINUTTER" (digits in columns 3..6), singular MINUTT = the first 6 cells
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 8}, MIN_ONE = {13, 8, 6};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(KLOKKA);
  m.word(ER);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 4) h = (h + 1) % 12;  // from "ti på halv" on the next hour counts
  switch (m5) {
    case 0: break;
    case 1: m.word(M_FEM); m.word(OVER); break;
    case 2: m.word(M_TI); m.word(OVER); break;
    case 3: m.word(KVART); m.word(OVER); break;
    case 4: m.word(M_TI); m.word(PA); m.word(HALV); break;
    case 5: m.word(M_FEM); m.word(PA); m.word(HALV); break;
    case 6: m.word(HALV); break;
    case 7: m.word(M_FEM); m.word(OVER); m.word(HALV); break;
    case 8: m.word(M_TI); m.word(OVER); m.word(HALV); break;
    case 9: m.word(KVART); m.word(PA); break;
    case 10: m.word(M_TI); m.word(PA); break;
    default: m.word(M_FEM); m.word(PA); break;
  }
  m.word(HOURS[h]);
  const int mm = minute % 5;  // "+ 1 MINUTT" or "+ 2..4 MINUTTER"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(mm == 1 ? MIN_ONE : MIN_WORD);  // singular: without the plural ending
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"nb","dec":",",
"notime_msg":"Klokka har ingen tid ennå (ikke internett eller NTP).",
"btn_settime":"Hent tid fra telefon/PC",
"ap_info":"Hotspot «{ap}» aktiv. Skriv inn nettverket ditt nedenfor under <b>Wi-Fi</b>.",
"sec_show":"Visning","on":"Klokka slått på","swMin":"Enkeltminutter (+ 1–4 MINUTTER)",
"brD":"Lysstyrke dag","brN":"Lysstyrke natt","cur":"Strømgrense (mA)",
"hint_show":"Natt 0 % = skjermen av om natten. Velg strømgrensen etter strømforsyningen (256 lysdioder bruker allerede ca. 256 mA i hvile).",
"sec_col":"Farger",
"hint_col":"«Tilfeldig» skifter hver hele time. «Temperatur»: kaldt mørkeblått, gult, behagelig grønt, oransje, varmt rødt (etter skalaen under ekstra visninger).",
"g_time":"Tid","g_vent":"LUFTE","g_alarm":"ALARM","g_batt":"BATT","g_tout":"Temperatur ute","g_tin":"Temperatur inne",
"pal_0":"Varmhvit","pal_1":"Hvit","pal_2":"Rød","pal_3":"Oransje","pal_4":"Gul","pal_5":"Grønn","pal_6":"Blå","pal_7":"Fiolett",
"c_random":"Tilfeldig","c_temp":"Temperatur","c_pride":"Pride","c_custom":"egen farge",
"sec_fx":"Effekter",
"fx_rainbow":"Regnbue","fx_aurora":"Nordlys","fx_matrix":"Matrix","fx_fire":"Ild","fx_confetti":"Konfetti","fx_stars":"Stjernehimmel",
"fx_blink":"Blink","fx_blink_own":"Blink (egen farge)","stop":"Stopp",
"fxd":"Effektvarighet","blk":"Blinkesyklus",
"hint_fx":"Varighet 0 s = kjører til «Stopp». Effekter kjører alltid med minst 10 % lysstyrke, også om natten ved 0 % eller når klokka er slått av.",
"fx_started":"{fx} startet","fx_stopped":"Effekt stoppet",
"txt":"Rulletekst","txt_ph":"Skriv tekst","txt_start":"Vis tekst","txt_started":"Tekst startet",
"hint_txt":"Hver bokstav fyller hele matrisen. Vises like lenge som effektens varighet (minst én gang), i tidens farge (tilfeldig = regnbue). Latinske, greske og kyrilliske bokstaver, tall, tegnsetting, € og ♥. HTTP: /api/set?text=…",
"sec_sun":"Dag / natt","nmode":"Nattmodus","nm_mix":"Blandet","nm_sun":"Solstand","nm_fixed":"Faste tider",
"lat":"Breddegrad","lon":"Lengdegrad","nso":"Forskyvning nattens start (min)","neo":"Forskyvning nattens slutt (min)",
"nme":"Natt ikke før","nml":"Natt ikke etter","nfs":"Natt fra","nfe":"Natt til",
"sunrise":"Soloppgang","sunset":"Solnedgang","night_today":"Natt i dag","now":"Nå",
"nmh_0":"Forskyvning: + etter, − før solnedgang eller soloppgang. Koordinater f.eks. fra en kartapp (høyreklikk på stedet).",
"nmh_1":"De faste tidene gjelder hver dag.",
"nmh_2":"Natten begynner ved solnedgang (pluss forskyvning), men ikke før det innstilte tidspunktet, og slutter ved soloppgang (pluss forskyvning), men ikke etter det innstilte tidspunktet.",
"day":"Dag","night":"Natt",
"sec_extra":"Ekstra visninger","swTemp":"Temperaturpunkter (venstre ute, høyre inne)","tOnl":"Utetemperatur fra Open-Meteo (sted)",
"scale_out":"Skala ute (°C)","scale_in":"Skala inne (°C)",
"swLuft":"Vis LUFTE","swAlarm":"Vis ALARM","swAkku":"Vis BATT","swExtra":"Vis HEI",
"apiTo":"Verdier gyldige i (min, 0 = alltid)",
"v_out":"Ute","v_in":"Inne","v_batt":"Batteri","v_la":"Lufting / alarm","on_":"på","off_":"av",
"hint_extra":"Inne, batteri, lufting og alarm (og ute, hvis uten Open-Meteo) kommer utenfra, f.eks. via nettleser, skript eller smarthus:",
"sec_api":"HTTP-styring",
"hint_api1":"Fra andre systemer via nettleser, skript eller smarthus (GET eller POST til <code>/api/set</code>, flere parametere kan kombineres). Lysstyrke, farger og brytere lagres, effekter kjører i den innstilte varigheten.",
"hint_api2":"Farger: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatur: temp) eller rrggbb · Brytere: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effekter: {fx}, stop · fxcolor: fargenavn eller rrggbb. Strømgrense, Wi-Fi og system bare her i nettgrensesnittet.",
"sec_time":"Tid","ntpD":"NTP-server","ntp_auto":"automatisk (DHCP)","ntp_manual":"manuell","ntp_server":"Server",
"ntp_fallback":"Reserveserver (hvis ruteren ikke gir en, gjelder etter omstart)",
"loc":"Sted","loc_custom":"eget sted (koordinater)","tz_from_loc":"fra stedet {city}",
"tz":"Tidssone","tz_cet":"Sentral-Europa (NO, SE, DK, DE …)","tz_wet":"London, Lisboa (WET)","tz_eet":"Øst-Europa (Kyiv, Athen, Bucuresti)",
"tz_trt":"Tyrkia","tz_eat":"Øst-Afrika (Tanzania, Kenya)","tz_utc":"UTC",
"tz_use":"USA øst","tz_usc":"USA sentral","tz_usm":"USA Mountain","tz_usw":"USA vest",
"tz_wib":"Indonesia (Jakarta)","tz_cst":"Kina","tz_kst":"Korea","tz_jst":"Japan","tz_aus":"Australia øst",
"tz_custom":"egen (POSIX TZ) …","tz_posix":"POSIX-tidssone","ntp_active":"Aktiv server",
"ntp_hint":"Automatisk: server fra ruteren (DHCP), ellers den angitte som reserve. Bytte mellom automatisk og manuell starter klokka på nytt.",
"ntp_nodhcp":"DHCP-NTP er ikke tilgjengelig i denne kortpakken – den angitte serveren brukes.",
"sec_wifi":"Wi-Fi","ssid":"Nettverk (SSID)","scan":"Søk etter nettverk","pass":"Passord","pass_ph":"la stå tomt = behold nåværende",
"host":"Enhetsnavn (http://navn.local)","save_wifi":"Lagre & koble til på nytt",
"status":"Status","ip":"IP","last_err":"Siste feil",
"hint_wifi":"Hvis Wi-Fi ikke finnes ved oppstart, åpner klokka hotspoten «{ap}» (uten passord, http://192.168.4.1).",
"w_conn":"koblet til {ssid}","w_ap":"Hotspot aktiv ({ip})","w_none":"ikke tilkoblet",
"scanning":"Søker …","scan_none":"Ingen nettverk funnet","scan_err":"Søket mislyktes",
"wr_2":"autentisering utløpt","wr_15":"feil passord?","wr_201":"nettverk ikke funnet","wr_202":"autentisering avvist (passord?)",
"wr_203":"tilknytning mislyktes","wr_204":"feil passord?","wr_205":"tilkobling mislyktes","wr_8":"frakoblet",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi frakoblet","net_lost":"ingen forbindelse med klokka",
"sec_sys":"System","mir":"LED 0 forfra øverst til høyre (speilvend)","srp":"Matrise koblet i sikksakk",
"restart":"Start på nytt","reset":"Fabrikkinnstillinger",
"q_restart":"Starte klokka på nytt?","q_reset":"Slette alle innstillinger inkludert Wi-Fi?",
"language":"Språk","firmware":"Fastvare","uptime":"Oppetid","heap":"Ledig minne",
"footer":"{ap} – byggeveiledning, kode og utskriftsfiler:",
"saved":"Lagret","saved_restart":"Lagret – klokka starter på nytt …","save_err":"Feil ved lagring",
"time_set":"Tid overtatt","restarting":"Klokka starter på nytt …",
"srv_no_network":"Ingen nettverk angitt","srv_back":"Tilbake","srv_saved":"Wi-Fi lagret",
"srv_connecting":"Klokka kobler seg nå til","srv_restart":"og starter på nytt for dette. Hotspoten forsvinner.",
"srv_reach":"Deretter tilgjengelig på","srv_reach2":"eller via IP-adressen fra ruteren eller den serielle monitoren.",
"srv_retry":"Hvis tilkoblingen mislykkes, dukker hotspoten opp igjen etter omtrent 30 sekunder.",
"srv_not_found":"Ikke funnet"
})JSON";
}  // namespace wc_no
static const WcLangDef WC_LANG = {
    "NO", "Norsk", wc_no::GRID,
    {14, 1, 5},  // LUFTE
    {14, 11, 5}, // ALARM
    {15, 1, 4},  // BATT
    {15, 6, 10}, // battery bars
    wc_no::EXTRA, 1,  // HEI
    wc_no::time_words,
    "ordklokke", "Ordklokke",
    59.9139f, 10.7522f,    // Oslo
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Oslo
    "%d.%m.%Y",
    wc_no::UI_JSON,
};
