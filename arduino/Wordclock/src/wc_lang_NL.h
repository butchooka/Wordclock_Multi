/*
  wc_lang_NL.h - Wordclock 16x16, language file NL (Nederlands), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_NL.scad (check: python3 tools/check_lang.py NL).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_NL.txt)
  Satzbau (Standard-Niederländisch, „half“-System): HET IS [<Minuten> OVER|VOOR] [HALF] <Stunde> [UUR]
  Ab :20 bezieht sich die Uhrzeit auf die nächste Stunde (wie im Deutschen „halb zehn“).
  :00 <Stunde> UUR, :05 VIJF OVER, :10 TIEN OVER, :15 KWART OVER, :20 TIEN VOOR HALF,
  :25 VIJF VOOR HALF, :30 HALF, :35 VIJF OVER HALF, :40 TIEN OVER HALF, :45 KWART VOOR,
  :50 TIEN VOOR, :55 VIJF VOOR
  Beispiel: 9:30 = HET IS HALF TIEN.
  UUR nur zur vollen Stunde. 12-Stunden-Anzeige: 0 und 12 Uhr = TWAALF.
  Minutenzeile: + 1 MINUUT (Einzahl), + 2..4 MINUTEN (im Raster „MINUUTEN“: MINUUT = die ersten
  6 Felder, MINUTEN = MINU + TEN, das zweite U bleibt dunkel).
  Zusatzwörter (Schalter „HALLO tonen“): HALLO („Hallo“, Gruß).
  INFO_EN
  Sentence (standard Dutch, "half" system): HET IS [<minutes> OVER|VOOR] [HALF] <hour> [UUR]
  From :20 on the time refers to the next hour.
  :00 <hour> UUR, :05 VIJF OVER, :10 TIEN OVER, :15 KWART OVER, :20 TIEN VOOR HALF,
  :25 VIJF VOOR HALF, :30 HALF, :35 VIJF OVER HALF, :40 TIEN OVER HALF, :45 KWART VOOR,
  :50 TIEN VOOR, :55 VIJF VOOR
  Example: 9:30 = HET IS HALF TIEN (half on the way to ten).
  UUR only at the full hour. 12-hour display: 0 and 12 o'clock = TWAALF.
  Minute row: + 1 MINUUT (singular), + 2..4 MINUTEN (grid "MINUUTEN": MINUUT = the first
  6 cells, MINUTEN = MINU + TEN, the second U stays dark).
  Extra words (switch "HALLO tonen"): HALLO ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_nl {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xHETxISxHALLOx*",
    "*xVIJFxxTIENxxx*",
    "*xxKWARTxxxxxxx*",
    "*xVOORxxxOVERxx*",
    "*xxxxHALFxxxxxx*",
    "*xEENxxxxTWEExx*",
    "*DRIExxxxVIERxx*",
    "*xVIJFxxxxZESxx*",
    "*xxxZEVENxxxxxx*",
    "*ACHTxxxNEGENxx*",
    "*xTIENxxxxELFxx*",
    "*xxTWAALFxxxxxx*",
    "*xxxxxxUURxxxxx*",
    "x+x1234xMINUUTEN",
    "xLUCHTENxxxALARM",
    "xACCUx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord HET = {0, 2, 3}, IS = {0, 6, 2};
static const WcWord M_VIJF = {1, 2, 4}, M_TIEN = {1, 8, 4}, KWART = {2, 3, 5};
static const WcWord VOOR = {3, 2, 4}, OVER = {3, 9, 4}, HALF = {4, 5, 4}, UUR = {12, 7, 3};
// hour 0..11 (0 = twelve)
static const WcWord HOURS[12] = {{11, 3, 6}, {5, 2, 3}, {5, 9, 4},  {6, 1, 4},  {6, 9, 4},  {7, 2, 4},
                                 {7, 10, 3}, {8, 4, 5}, {9, 1, 4},  {9, 8, 5},  {10, 2, 4}, {10, 10, 3}};
// extra words (easter egg): HALLO ("hello", greeting)
static const WcWord EXTRA[1] = {{0, 9, 5}};
// row 14: "+ 1 2 3 4  MINUUTEN" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_ONE = {13, 8, 6};     // MINUUT
static const WcWord MIN_STEM = {13, 8, 4}, MIN_END = {13, 13, 3};    // MINU + TEN = MINUTEN
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(HET);
  m.word(IS);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 4) h = (h + 1) % 12;  // from "tien voor half" on the next hour counts
  switch (m5) {
    case 0: break;
    case 1: m.word(M_VIJF); m.word(OVER); break;
    case 2: m.word(M_TIEN); m.word(OVER); break;
    case 3: m.word(KWART); m.word(OVER); break;
    case 4: m.word(M_TIEN); m.word(VOOR); m.word(HALF); break;
    case 5: m.word(M_VIJF); m.word(VOOR); m.word(HALF); break;
    case 6: m.word(HALF); break;
    case 7: m.word(M_VIJF); m.word(OVER); m.word(HALF); break;
    case 8: m.word(M_TIEN); m.word(OVER); m.word(HALF); break;
    case 9: m.word(KWART); m.word(VOOR); break;
    case 10: m.word(M_TIEN); m.word(VOOR); break;
    default: m.word(M_VIJF); m.word(VOOR); break;
  }
  m.word(HOURS[h]);
  if (m5 == 0) m.word(UUR);
  const int mm = minute % 5;  // "+ 1 MINUUT" or "+ 2..4 MINUTEN"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    if (mm == 1) {
      m.word(MIN_ONE);  // singular MINUUT
    } else {
      m.word(MIN_STEM);  // plural MINUTEN = MINU + TEN
      m.glue(MIN_END);
    }
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"nl","dec":",",
"notime_msg":"De klok heeft nog geen tijd (geen internet of NTP).",
"btn_settime":"Tijd van telefoon/pc overnemen",
"ap_info":"Hotspot ‘{ap}’ actief. Voer hieronder bij <b>Wifi</b> je netwerk in.",
"sec_show":"Weergave","on":"Klok ingeschakeld","swMin":"Losse minuten (+ 1–4 MINUTEN)",
"brD":"Helderheid dag","brN":"Helderheid nacht","cur":"Stroomlimiet (mA)",
"hint_show":"Nacht 0 % = display 's nachts uit. Kies de stroomlimiet passend bij de voeding (256 leds verbruiken in rust al ca. 256 mA).",
"sec_col":"Kleuren",
"hint_col":"‘Willekeurig’ wisselt elk heel uur. ‘Temperatuur’: koud donkerblauw, geel, comfortabel groen, oranje, heet rood (volgens de schaal bij extra weergaven).",
"g_time":"Tijd","g_vent":"LUCHTEN","g_alarm":"ALARM","g_batt":"ACCU","g_tout":"Temperatuur buiten","g_tin":"Temperatuur binnen",
"pal_0":"Warm wit","pal_1":"Wit","pal_2":"Rood","pal_3":"Oranje","pal_4":"Geel","pal_5":"Groen","pal_6":"Blauw","pal_7":"Violet",
"c_random":"Willekeurig","c_temp":"Temperatuur","c_pride":"Pride","c_custom":"eigen kleur",
"sec_fx":"Effecten",
"fx_rainbow":"Regenboog","fx_aurora":"Noorderlicht","fx_matrix":"Matrix","fx_fire":"Vuur","fx_confetti":"Confetti","fx_stars":"Sterrenhemel",
"fx_blink":"Knipperen","fx_blink_own":"Knipperen (eigen kleur)","stop":"Stop",
"fxd":"Effectduur","blk":"Knippercyclus",
"hint_fx":"Duur 0 s = loopt tot ‘Stop’. Effecten lopen altijd met minstens 10 % helderheid, ook 's nachts bij 0 % of bij uitgeschakelde klok.",
"fx_started":"{fx} gestart","fx_stopped":"Effect gestopt",
"txt":"Lichtkrant","txt_ph":"Tekst invoeren","txt_start":"Tekst starten","txt_started":"Tekst gestart",
"hint_txt":"Elke letter vult de hele matrix. Loopt zo lang als de effectduur (minstens één keer), in de kleur van de tijd (willekeurig = regenboog). Latijnse, Griekse en Cyrillische letters, cijfers, leestekens, € en ♥. HTTP: /api/set?text=…",
"sec_sun":"Dag / nacht","nmode":"Nachtmodus","nm_mix":"Gemengd","nm_sun":"Zonnestand","nm_fixed":"Vaste tijden",
"lat":"Breedtegraad","lon":"Lengtegraad","nso":"Verschuiving begin nacht (min)","neo":"Verschuiving einde nacht (min)",
"nme":"Nacht niet vóór","nml":"Nacht niet na","nfs":"Nacht vanaf","nfe":"Nacht tot",
"sunrise":"Zonsopkomst","sunset":"Zonsondergang","night_today":"Nacht vandaag","now":"Nu",
"nmh_0":"Verschuiving: + na, − vóór zonsondergang of zonsopkomst. Coördinaten bijv. uit een kaarten-app (rechtsklik op de plek).",
"nmh_1":"De vaste tijden gelden elke dag.",
"nmh_2":"De nacht begint bij zonsondergang (plus verschuiving), maar niet vóór de ingestelde tijd, en eindigt bij zonsopkomst (plus verschuiving), maar niet na de ingestelde tijd.",
"day":"Dag","night":"Nacht",
"sec_extra":"Extra weergaven","tOnl":"Buitentemperatuur van Open-Meteo (locatie)",
"scale_out":"Schaal buiten (°C)","scale_in":"Schaal binnen (°C)",
"swExtra":"HALLO tonen",
"apiTo":"Waarden geldig gedurende (min, 0 = altijd)",
"v_out":"Buiten","v_in":"Binnen","v_batt":"Accu","v_la":"Luchten / alarm","on_":"aan","off_":"uit",
"hint_extra":"Binnen, accu, luchten en alarm (en buiten, als zonder Open-Meteo) komen van buitenaf, bijv. via browser, script of smart home:",
"sec_api":"HTTP-besturing",
"hint_api1":"Vanuit andere systemen via browser, script of smart home (GET of POST naar <code>/api/set</code>, meerdere parameters combineerbaar). Helderheid, kleuren en schakelaars worden opgeslagen, effecten lopen gedurende de ingestelde duur.",
"hint_api2":"Kleuren: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatuur: temp) of rrggbb · Schakelaars: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effecten: {fx}, stop · fxcolor: kleurnaam of rrggbb. Stroomlimiet, wifi en systeem alleen hier in de webinterface.",
"sec_time":"Tijd","ntpD":"NTP-server","ntp_auto":"automatisch (DHCP)","ntp_manual":"handmatig","ntp_server":"Server",
"ntp_fallback":"Reserveserver (als de router er geen levert, geldt na herstart)",
"loc":"Locatie","loc_custom":"eigen locatie (coördinaten)","tz_from_loc":"van locatie {city}",
"tz":"Tijdzone","tz_cet":"Midden-Europa (NL, BE, DE …)","tz_wet":"Londen, Lissabon (WET)","tz_eet":"Oost-Europa (Kyiv, Athene, Boekarest)",
"tz_trt":"Turkije","tz_eat":"Oost-Afrika (Tanzania, Kenia)","tz_utc":"UTC",
"tz_use":"VS Oost","tz_usc":"VS Centraal","tz_usm":"VS Mountain","tz_usw":"VS West",
"tz_wib":"Indonesië (Jakarta)","tz_cst":"China","tz_kst":"Korea","tz_jst":"Japan","tz_aus":"Australië Oost",
"tz_custom":"eigen (POSIX TZ) …","tz_posix":"POSIX-tijdzone","ntp_active":"Actieve server",
"ntp_hint":"Automatisch: server van de router (DHCP), anders de ingevoerde als reserve. Wisselen tussen automatisch en handmatig herstart de klok.",
"ntp_nodhcp":"DHCP-NTP is in dit boardpakket niet beschikbaar – de ingevoerde server wordt gebruikt.",
"sec_wifi":"Wifi","ssid":"Netwerk (SSID)","scan":"Netwerken zoeken","pass":"Wachtwoord","pass_ph":"leeg laten = huidige behouden",
"host":"Apparaatnaam (http://naam.local)","save_wifi":"Opslaan & opnieuw verbinden",
"status":"Status","ip":"IP","last_err":"Laatste fout",
"hint_wifi":"Als de wifi bij het opstarten niet gevonden wordt, opent de klok de hotspot ‘{ap}’ (zonder wachtwoord, http://192.168.4.1).",
"w_conn":"verbonden met {ssid}","w_ap":"Hotspot actief ({ip})","w_none":"niet verbonden",
"scanning":"Zoeken …","scan_none":"Geen netwerken gevonden","scan_err":"Zoeken mislukt",
"wr_2":"authenticatie verlopen","wr_15":"verkeerd wachtwoord?","wr_201":"netwerk niet gevonden","wr_202":"authenticatie geweigerd (wachtwoord?)",
"wr_203":"koppeling mislukt","wr_204":"verkeerd wachtwoord?","wr_205":"verbinding mislukt","wr_8":"verbinding verbroken",
"net_hotspot":"Hotspot {ap}","net_off":"Wifi verbroken","net_lost":"geen verbinding met de klok",
"sec_sys":"Systeem","mir":"Led 0 voorkant rechtsboven (spiegelen)","srp":"Matrix zigzag bedraad",
"restart":"Herstarten","reset":"Fabrieksinstellingen",
"q_restart":"De klok herstarten?","q_reset":"Alle instellingen inclusief wifi wissen?",
"language":"Taal","firmware":"Firmware","uptime":"Looptijd","heap":"Vrij geheugen",
"footer":"{ap} – bouwhandleiding, code en printbestanden:",
"saved":"Opgeslagen","saved_restart":"Opgeslagen – klok herstart …","save_err":"Fout bij opslaan",
"time_set":"Tijd overgenomen","restarting":"Klok herstart …",
"srv_no_network":"Geen netwerk ingevoerd","srv_back":"Terug","srv_saved":"Wifi opgeslagen",
"srv_connecting":"De klok verbindt nu met","srv_restart":"en herstart daarvoor. De hotspot verdwijnt.",
"srv_reach":"Daarna bereikbaar op","srv_reach2":"of via het IP-adres uit de router of de seriële monitor.",
"srv_retry":"Als de verbinding mislukt, verschijnt de hotspot na ongeveer 30 seconden weer.",
"srv_not_found":"Niet gevonden"
})JSON";
}  // namespace wc_nl
static const WcLangDef WC_LANG = {
    "NL", "Nederlands", wc_nl::GRID,
    {14, 1, 7},   // LUCHTEN
    {14, 11, 5},  // ALARM
    {15, 1, 4},   // ACCU
    {15, 6, 10},  // battery bars
    wc_nl::EXTRA, 1,  // HALLO
    wc_nl::time_words,
    "woordklok", "Woordklok",
    52.3676f, 4.9041f,             // Amsterdam
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Amsterdam
    "%d-%m-%Y",
    wc_nl::UI_JSON,
};
