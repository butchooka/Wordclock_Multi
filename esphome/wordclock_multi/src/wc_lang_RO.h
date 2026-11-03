/*
  wc_lang_RO.h - Wordclock 16x16, language file RO (Română), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_RO.scad (check: python3 tools/check_lang.py RO).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_RO.txt)
  Satzbau: ESTE ORA <Stunde> ȘI <Minuten> | ESTE ORA <nächste Stunde> FĂRĂ <Minuten> |
  ESTE ORA <Stunde> (gängige Umgangsform, 12-Stunden-Zählung; ȘI = „und“, FĂRĂ = „ohne/vor“).
  Ab :35 (FĂRĂ) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 ESTE ORA <Stunde>, :05 <Stunde> ȘI CINCI, :10 ȘI ZECE, :15 ȘI UN SFERT, :20 ȘI DOUĂZECI,
  :25 ȘI DOUĂZECI ȘI CINCI, :30 ȘI JUMĂTATE, :35 <nächste Stunde> FĂRĂ DOUĂZECI ȘI CINCI,
  :40 FĂRĂ DOUĂZECI, :45 FĂRĂ UN SFERT, :50 FĂRĂ ZECE, :55 FĂRĂ CINCI
  Beispiele: 3:05 ESTE ORA TREI ȘI CINCI, 3:30 ESTE ORA TREI ȘI JUMĂTATE, 3:45 ESTE ORA PATRU FĂRĂ UN SFERT.
  Stunden: UNU, DOUĂ, TREI, PATRU, CINCI, ȘASE, ȘAPTE, OPT, NOUĂ, ZECE, UNSPREZECE, DOUĂSPREZECE
  (nach „ora“ steht die Grundzahl, 1 Uhr = ORA UNU, 2 Uhr = ORA DOUĂ).
  CINCI und ZECE gibt es je zweimal (Stunde und Minuten), ȘI zweimal (für :25 / :35).
  0 und 12 Uhr = DOUĂSPREZECE. Keine Wörter für Mitternacht/Mittag.
  Ohne gültige Uhrzeit leuchtet nur ESTE ORA.
  Minutenzeile: + 1 MINUT, + 2..4 MINUTE (MINUT + E, zusammenhängend).
  Statuswörter: LÜFTEN = AERISIRE („Lüften“), ALARM = ALARMĂ, AKKU = BAT (Abkürzung von BATERIE;
  BATERIE ist mit 7 Buchstaben zu lang für die Zeile mit den 10 Balken).
  Zusatzwörter (Schalter „Afișează TIMPUL ZBOARĂ“): TIMPUL ZBOARĂ („die Zeit fliegt“).
  Sonderzeichen: Ă und Ș (S mit Komma darunter, nicht das türkische Ş mit Cedille); Metriken für
  OpenSCAD in Wordclock_Model.scad vorhanden. Â, Î und Ț kommen im Raster nicht vor.
  INFO_EN
  Sentence: ESTE ORA <hour> ȘI <minutes> | ESTE ORA <next hour> FĂRĂ <minutes> |
  ESTE ORA <hour> (common spoken form, 12-hour counting; ȘI = "and", FĂRĂ = "without/to").
  From :35 on (FĂRĂ) the time refers to the next hour.
  :00 ESTE ORA <hour>, :05 <hour> ȘI CINCI, :10 ȘI ZECE, :15 ȘI UN SFERT, :20 ȘI DOUĂZECI,
  :25 ȘI DOUĂZECI ȘI CINCI, :30 ȘI JUMĂTATE, :35 <next hour> FĂRĂ DOUĂZECI ȘI CINCI,
  :40 FĂRĂ DOUĂZECI, :45 FĂRĂ UN SFERT, :50 FĂRĂ ZECE, :55 FĂRĂ CINCI
  Examples: 3:05 ESTE ORA TREI ȘI CINCI, 3:30 ESTE ORA TREI ȘI JUMĂTATE, 3:45 ESTE ORA PATRU FĂRĂ UN SFERT.
  Hours: UNU, DOUĂ, TREI, PATRU, CINCI, ȘASE, ȘAPTE, OPT, NOUĂ, ZECE, UNSPREZECE, DOUĂSPREZECE
  (after "ora" the cardinal number is used, 1 o'clock = ORA UNU, 2 o'clock = ORA DOUĂ).
  CINCI and ZECE exist twice (hour and minutes), ȘI twice (for :25 / :35).
  0 and 12 o'clock = DOUĂSPREZECE. No words for midnight/noon.
  Without a valid time only ESTE ORA is lit.
  Minute row: + 1 MINUT, + 2..4 MINUTE (MINUT + E, contiguous).
  Status words: VENTILATE = AERISIRE ("ventilation"), ALARM = ALARMĂ, BATTERY = BAT (short for BATERIE;
  BATERIE with 7 letters is too long for the row with the 10 bars).
  Extra words (switch "Afișează TIMPUL ZBOARĂ"): TIMPUL ZBOARĂ ("time flies").
  Special letters: Ă and Ș (S with comma below, not the Turkish Ş with cedilla); metrics for OpenSCAD
  available in Wordclock_Model.scad. Â, Î and Ț do not occur in the grid.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_ro {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*ESTExORAxxxUNU*",
    "*DOUĂxTREIxxOPT*",
    "*PATRUxxxxCINCI*",
    "*ȘASExxxxxȘAPTE*",
    "*NOUĂxxxxxxZECE*",
    "*xxUNSPREZECExx*",
    "*xDOUĂSPREZECEx*",
    "*ȘIxxxxxxxxFĂRĂ*",
    "*DOUĂZECIxxxxȘI*",
    "*CINCIxxxxxZECE*",
    "*xxxUNxSFERTxxx*",
    "*xxxJUMĂTATExxx*",
    "*xTIMPULxZBOARĂ*",
    "x+x1234xMINUTExx",
    "AERISIRExxALARMĂ",
    "xBATxx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord ESTE = {0, 1, 4}, ORA = {0, 6, 3};
static const WcWord SI = {7, 1, 2}, FARA = {7, 11, 4}, SI2 = {8, 13, 2};  // SI2: "DOUĂZECI ȘI CINCI"
static const WcWord M_CINCI = {9, 1, 5}, M_ZECE = {9, 11, 4}, M_DOUAZECI = {8, 1, 8};
static const WcWord M_UN = {10, 4, 2}, M_SFERT = {10, 7, 5}, JUMATATE = {11, 4, 8};
// hour 0..11 (0 = DOUĂSPREZECE)
static const WcWord HOURS[12] = {{6, 2, 12}, {0, 12, 3}, {1, 1, 4}, {1, 6, 4}, {2, 1, 5},  {2, 10, 5},
                                 {3, 1, 4},  {3, 10, 5}, {1, 12, 3}, {4, 1, 4}, {4, 11, 4}, {5, 3, 10}};
// extra words (easter egg): TIMPUL ZBOARĂ ("time flies")
static const WcWord EXTRA[2] = {{12, 2, 6}, {12, 9, 6}};
// row 14: "+ 1 2 3 4  MINUT(E)" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_ONE = {13, 8, 5}, MIN_MANY = {13, 8, 6};  // MINUT / MINUTE
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(ESTE);
  m.word(ORA);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 7) h = (h + 1) % 12;  // from "fără douăzeci și cinci" on the next hour counts
  m.word(HOURS[h]);
  switch (m5) {
    case 0: break;
    case 1: m.word(SI); m.word(M_CINCI); break;
    case 2: m.word(SI); m.word(M_ZECE); break;
    case 3: m.word(SI); m.word(M_UN); m.word(M_SFERT); break;
    case 4: m.word(SI); m.word(M_DOUAZECI); break;
    case 5: m.word(SI); m.word(M_DOUAZECI); m.word(SI2); m.word(M_CINCI); break;
    case 6: m.word(SI); m.word(JUMATATE); break;
    case 7: m.word(FARA); m.word(M_DOUAZECI); m.word(SI2); m.word(M_CINCI); break;
    case 8: m.word(FARA); m.word(M_DOUAZECI); break;
    case 9: m.word(FARA); m.word(M_UN); m.word(M_SFERT); break;
    case 10: m.word(FARA); m.word(M_ZECE); break;
    default: m.word(FARA); m.word(M_CINCI); break;
  }
  const int mm = minute % 5;  // "+ 1 MINUT" / "+ 2..4 MINUTE"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(mm == 1 ? MIN_ONE : MIN_MANY);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"ro","dec":",",
"notime_msg":"Ceasul nu cunoaște încă ora (fără internet sau NTP).",
"btn_settime":"Preia ora de pe telefon/PC",
"ap_info":"Hotspotul „{ap}” este activ. Introduceți rețeaua dvs. mai jos la <b>Wi-Fi</b>.",
"sec_show":"Afișaj","on":"Ceas pornit","swMin":"Minute individuale (+ 1–4 MINUTE)",
"brD":"Luminozitate zi","brN":"Luminozitate noapte","cur":"Limită de curent (mA)",
"hint_show":"Noapte 0 % = afișaj stins noaptea. Alegeți limita de curent potrivită sursei de alimentare (256 de LED-uri consumă deja aprox. 256 mA în repaus).",
"sec_col":"Culori",
"hint_col":"„Aleatoriu” se schimbă la fiecare oră fixă. „Temperatură”: rece albastru închis, galben, confort verde, portocaliu, cald roșu (după scala de la afișaje suplimentare).",
"g_time":"Ora","g_vent":"AERISIRE","g_alarm":"ALARMĂ","g_batt":"BAT","g_tout":"Temperatură exterioară","g_tin":"Temperatură interioară",
"pal_0":"Alb cald","pal_1":"Alb","pal_2":"Roșu","pal_3":"Portocaliu","pal_4":"Galben","pal_5":"Verde","pal_6":"Albastru","pal_7":"Violet",
"c_random":"Aleatoriu","c_temp":"Temperatură","c_pride":"Pride","c_custom":"culoare proprie",
"sec_fx":"Efecte",
"fx_rainbow":"Curcubeu","fx_aurora":"Aurora boreală","fx_matrix":"Matrix","fx_fire":"Foc","fx_confetti":"Confetti","fx_stars":"Cer înstelat",
"fx_blink":"Clipire","fx_blink_own":"Clipire (culoare proprie)","stop":"Stop",
"fxd":"Durata efectului","blk":"Ciclu de clipire",
"hint_fx":"Durata 0 s = rulează până la „Stop”. Efectele rulează mereu cu cel puțin 10 % luminozitate, chiar și noaptea la 0 % sau cu ceasul oprit.",
"fx_started":"{fx} pornit","fx_stopped":"Efect oprit",
"txt":"Text defilant","txt_ph":"Introdu un text","txt_start":"Afișează textul","txt_started":"Text pornit",
"hint_txt":"Fiecare literă umple toată matricea. Rulează cât durează efectul (cel puțin o dată), în culoarea orei (aleatoriu = curcubeu). Litere latine, grecești și chirilice, cifre, punctuație, € și ♥. HTTP: /api/set?text=…",
"sec_sun":"Zi / noapte","nmode":"Mod noapte","nm_mix":"Mixt","nm_sun":"Poziția soarelui","nm_fixed":"Ore fixe",
"lat":"Latitudine","lon":"Longitudine","nso":"Decalaj început noapte (min)","neo":"Decalaj sfârșit noapte (min)",
"nme":"Noaptea nu înainte de","nml":"Noaptea nu după","nfs":"Noaptea de la","nfe":"Noaptea până la",
"sunrise":"Răsărit","sunset":"Apus","night_today":"Noaptea de azi","now":"Acum",
"nmh_0":"Decalaj: + după, − înainte de apus sau răsărit. Coordonatele de ex. dintr-o aplicație de hărți (clic dreapta pe loc).",
"nmh_1":"Orele fixe se aplică în fiecare zi.",
"nmh_2":"Noaptea începe la apus (plus decalaj), dar nu înainte de ora setată, și se termină la răsărit (plus decalaj), dar nu după ora setată.",
"day":"Zi","night":"Noapte",
"sec_extra":"Afișaje suplimentare","swTemp":"Puncte de temperatură (stânga exterior, dreapta interior)","tOnl":"Temperatura exterioară de la Open-Meteo (locație)",
"scale_out":"Scală exterior (°C)","scale_in":"Scală interior (°C)",
"swLuft":"Afișează AERISIRE","swAlarm":"Afișează ALARMĂ","swAkku":"Afișează BAT","swExtra":"Afișează TIMPUL ZBOARĂ",
"apiTo":"Valorile sunt valabile (min, 0 = mereu)",
"v_out":"Exterior","v_in":"Interior","v_batt":"Baterie","v_la":"Aerisire / alarmă","on_":"pornit","off_":"oprit",
"hint_extra":"Interior, baterie, aerisire și alarmă (și exterior, dacă fără Open-Meteo) vin din exterior, de ex. prin browser, script sau casă inteligentă:",
"sec_api":"Control HTTP",
"hint_api1":"Din alte sisteme prin browser, script sau casă inteligentă (GET sau POST la <code>/api/set</code>, se pot combina mai mulți parametri). Luminozitatea, culorile și comutatoarele se salvează, efectele rulează pe durata setată.",
"hint_api2":"Culori: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatură: temp) sau rrggbb · Comutatoare: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Efecte: {fx}, stop · fxcolor: nume de culoare sau rrggbb. Limita de curent, Wi-Fi și sistemul doar aici, în interfața web.",
"sec_time":"Ora","ntpD":"Server NTP","ntp_auto":"automat (DHCP)","ntp_manual":"manual","ntp_server":"Server",
"ntp_fallback":"Server de rezervă (dacă routerul nu oferă unul, se aplică după repornire)",
"loc":"Locație","loc_custom":"locație proprie (coordonate)","tz_from_loc":"din locația {city}",
"tz":"Fus orar","tz_cet":"Europa Centrală (DE, AT, CH …)","tz_wet":"Londra, Lisabona (WET)","tz_eet":"Europa de Est (Kiev, Atena, București)",
"tz_trt":"Turcia","tz_eat":"Africa de Est (Tanzania, Kenya)","tz_utc":"UTC",
"tz_use":"SUA Est","tz_usc":"SUA Centru","tz_usm":"SUA Munte","tz_usw":"SUA Vest",
"tz_wib":"Indonezia (Jakarta)","tz_cst":"China","tz_kst":"Coreea","tz_jst":"Japonia","tz_aus":"Australia Est",
"tz_custom":"propriu (POSIX TZ) …","tz_posix":"Fus orar POSIX","ntp_active":"Server activ",
"ntp_hint":"Automat: serverul de la router (DHCP), altfel cel introdus ca rezervă. Comutarea între automat și manual repornește ceasul.",
"ntp_nodhcp":"NTP prin DHCP nu este disponibil în acest pachet de plăci – se folosește serverul introdus.",
"sec_wifi":"Wi-Fi","ssid":"Rețea (SSID)","scan":"Caută rețele","pass":"Parolă","pass_ph":"gol = păstrează parola actuală",
"host":"Nume dispozitiv (http://nume.local)","save_wifi":"Salvează și reconectează",
"status":"Stare","ip":"IP","last_err":"Ultima eroare",
"hint_wifi":"Dacă Wi-Fi nu este găsit la pornire, ceasul deschide hotspotul „{ap}” (fără parolă, http://192.168.4.1).",
"w_conn":"conectat la {ssid}","w_ap":"Hotspot activ ({ip})","w_none":"neconectat",
"scanning":"Se caută …","scan_none":"Nu s-au găsit rețele","scan_err":"Căutarea a eșuat",
"wr_2":"autentificarea a expirat","wr_15":"parolă greșită?","wr_201":"rețea negăsită","wr_202":"autentificare respinsă (parolă?)",
"wr_203":"asocierea a eșuat","wr_204":"parolă greșită?","wr_205":"conexiunea a eșuat","wr_8":"deconectat",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi deconectat","net_lost":"nicio conexiune cu ceasul",
"sec_sys":"Sistem","mir":"LED 0 în față sus dreapta (oglindit)","srp":"Matrice conectată în zigzag",
"restart":"Repornire","reset":"Resetare din fabrică",
"q_restart":"Reporniți ceasul?","q_reset":"Ștergeți toate setările, inclusiv Wi-Fi?",
"language":"Limbă","firmware":"Firmware","uptime":"Timp de funcționare","heap":"Memorie liberă",
"footer":"{ap} – ghid de construcție, cod și fișiere de imprimare:",
"saved":"Salvat","saved_restart":"Salvat – ceasul repornește …","save_err":"Eroare la salvare",
"time_set":"Ora a fost preluată","restarting":"Ceasul repornește …",
"srv_no_network":"Nicio rețea introdusă","srv_back":"Înapoi","srv_saved":"Wi-Fi salvat",
"srv_connecting":"Ceasul se conectează acum la","srv_restart":"și repornește pentru aceasta. Hotspotul dispare.",
"srv_reach":"Apoi este accesibil la","srv_reach2":"sau prin adresa IP din router sau din monitorul serial.",
"srv_retry":"Dacă conexiunea eșuează, hotspotul reapare după aproximativ 30 de secunde.",
"srv_not_found":"Negăsit"
})JSON";
}  // namespace wc_ro
static const WcLangDef WC_LANG = {
    "RO", "Română", wc_ro::GRID,
    {14, 0, 8},   // AERISIRE
    {14, 10, 6},  // ALARMĂ
    {15, 1, 3},   // BAT
    {15, 6, 10},  // battery bars
    wc_ro::EXTRA, 2,  // TIMPUL ZBOARĂ
    wc_ro::time_words,
    "ceascucuvinte", "CeasCuCuvinte",
    44.4268f, 26.1025f,              // București
    "EET-2EEST,M3.5.0/3,M10.5.0/4",  // Europe/Bucharest
    "%d.%m.%Y",
    wc_ro::UI_JSON,
};
