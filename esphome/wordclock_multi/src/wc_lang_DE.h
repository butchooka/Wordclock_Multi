/*
  wc_lang_DE.h - Wordclock 16x16, language file DE (Deutsch), v2.0
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_DE.scad (check: python3 tools/check_lang.py DE).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_DE.txt)
  Satzbau: ES IST [<Minuten> NACH|VOR] [HALB] <Stunde> [UHR]
  Ab :25 („fünf vor halb“) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 <Stunde> UHR, :05 FÜNF NACH, :10 ZEHN NACH, :15 VIERTEL NACH, :20 ZWANZIG NACH,
  :25 FÜNF VOR HALB, :30 HALB, :35 FÜNF NACH HALB, :40 ZWANZIG VOR, :45 VIERTEL VOR,
  :50 ZEHN VOR, :55 FÜNF VOR
  Sonderfall: volle Stunde 1 Uhr = EIN UHR (nicht EINS UHR), sonst EINS (z. B. FÜNF NACH EINS).
  12-Stunden-Anzeige: 0 und 12 Uhr = ZWÖLF. UHR nur zur vollen Stunde.
  Minutenzeile: + 1 MINUTE (Einzahl), + 2..4 MINUTEN.
  Zusatzwörter (Schalter „HALLO anzeigen“): HALLO („Hallo“, Gruß).
  INFO_EN
  Sentence: ES IST [<minutes> NACH|VOR] [HALB] <hour> [UHR]
  From :25 ("five to half") on the time refers to the next hour.
  :00 <hour> UHR, :05 FÜNF NACH, :10 ZEHN NACH, :15 VIERTEL NACH, :20 ZWANZIG NACH,
  :25 FÜNF VOR HALB, :30 HALB, :35 FÜNF NACH HALB, :40 ZWANZIG VOR, :45 VIERTEL VOR,
  :50 ZEHN VOR, :55 FÜNF VOR
  Special case: full hour 1 o'clock = EIN UHR (not EINS UHR), otherwise EINS (e.g. FÜNF NACH EINS).
  12-hour display: 0 and 12 o'clock = ZWÖLF. UHR only at the full hour.
  Minute row: + 1 MINUTE (singular), + 2..4 MINUTEN.
  Extra words (switch "HALLO anzeigen"): HALLO ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_de {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xxxxESxISTxxxx*",
    "*xxFÜNFxZEHNxxx*",
    "*xxxZWANZIGxxxx*",
    "*xxxVIERTELxxxx*",
    "*xxVORxxxNACHxx*",
    "*xxxxxHALBxxxxx*",
    "*xxEINSxxZWEIxx*",
    "*xxDREIxxVIERxx*",
    "*xFÜNFxxSECHSxx*",
    "*xSIEBENxxACHTx*",
    "*xxNEUNxxZEHNxx*",
    "*xxELFxxZWÖLFxx*",
    "*xxxxxUHRxHALLO*",
    "x+x1234xMINUTENx",
    "xxLÜFTENxALARMxx",
    "xAKKUx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord ES = {0, 5, 2}, IST = {0, 8, 3};
static const WcWord M_FUENF = {1, 3, 4}, M_ZEHN = {1, 8, 4}, M_ZWANZIG = {2, 4, 7}, M_VIERTEL = {3, 4, 7};
static const WcWord VOR = {4, 3, 3}, NACH = {4, 9, 4}, HALB = {5, 6, 4}, UHR = {12, 6, 3}, H_EIN = {6, 3, 3};
// hour 0..11 (0 = twelve)
static const WcWord HOURS[12] = {{11, 8, 5}, {6, 3, 4}, {6, 9, 4}, {7, 3, 4}, {7, 9, 4}, {8, 2, 4},
                                 {8, 8, 5},  {9, 2, 6}, {9, 10, 4}, {10, 3, 4}, {10, 9, 4}, {11, 3, 3}};
// extra words (easter egg): HALLO ("hello", greeting)
static const WcWord EXTRA[1] = {{12, 10, 5}};
// row 14: "+ 1 2 3 4  MINUTEN" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 7}, MIN_ONE = {13, 8, 6};  // MINUTEN / MINUTE
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(ES);
  m.word(IST);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 5) h = (h + 1) % 12;  // from "fünf vor halb" on the next hour counts
  switch (m5) {
    case 0: break;
    case 1: m.word(M_FUENF); m.word(NACH); break;
    case 2: m.word(M_ZEHN); m.word(NACH); break;
    case 3: m.word(M_VIERTEL); m.word(NACH); break;
    case 4: m.word(M_ZWANZIG); m.word(NACH); break;
    case 5: m.word(M_FUENF); m.word(VOR); m.word(HALB); break;
    case 6: m.word(HALB); break;
    case 7: m.word(M_FUENF); m.word(NACH); m.word(HALB); break;
    case 8: m.word(M_ZWANZIG); m.word(VOR); break;
    case 9: m.word(M_VIERTEL); m.word(VOR); break;
    case 10: m.word(M_ZEHN); m.word(VOR); break;
    default: m.word(M_FUENF); m.word(VOR); break;
  }
  if (m5 == 0 && h == 1) m.word(H_EIN);  // "EIN UHR" instead of "EINS UHR"
  else m.word(HOURS[h]);
  if (m5 == 0) m.word(UHR);
  const int mm = minute % 5;             // "+ 1 MINUTE" or "+ 2..4 MINUTEN"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(mm == 1 ? MIN_ONE : MIN_WORD);  // singular: without the final N
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"de","dec":",",
"notime_msg":"Die Uhr hat noch keine Uhrzeit (kein Internet bzw. NTP).",
"btn_settime":"Uhrzeit vom Handy/PC übernehmen",
"ap_info":"Hotspot „{ap}“ aktiv. Bitte unten unter <b>WLAN</b> dein Netzwerk eintragen.",
"sec_show":"Anzeige","on":"Uhr eingeschaltet","swMin":"Einzelminuten (+ 1–4 MINUTEN)",
"brD":"Helligkeit Tag","brN":"Helligkeit Nacht","cur":"Strombegrenzung (mA)",
"hint_show":"Nacht 0 % = Anzeige nachts aus. Strombegrenzung passend zum Netzteil wählen (256 LEDs brauchen schon ca. 256 mA Ruhestrom).",
"sec_col":"Farben",
"hint_col":"„Zufall“ wechselt jede volle Stunde. „Temperatur“: kalt dunkelblau, gelb, Komfort grün, orange, heiß rot (nach der Skala unter Zusatzanzeigen).",
"g_time":"Uhrzeit","g_vent":"LÜFTEN","g_alarm":"ALARM","g_batt":"AKKU","g_tout":"Temperatur außen","g_tin":"Temperatur innen",
"pal_0":"Warmweiß","pal_1":"Weiß","pal_2":"Rot","pal_3":"Orange","pal_4":"Gelb","pal_5":"Grün","pal_6":"Blau","pal_7":"Violett",
"c_random":"Zufall","c_temp":"Temperatur","c_pride":"Pride","c_custom":"eigene Farbe",
"sec_fx":"Effekte",
"fx_rainbow":"Rainbow","fx_aurora":"Aurora","fx_matrix":"Matrix","fx_fire":"Feuer","fx_confetti":"Konfetti","fx_stars":"Sternenhimmel",
"fx_blink":"Blinken","fx_blink_own":"Blinken (eigene Farbe)","stop":"Stopp",
"fxd":"Effekt Dauer","blk":"Blinken Zyklus",
"hint_fx":"Dauer 0 s = läuft bis „Stopp“. Effekte laufen immer mit mindestens 10 % Helligkeit, auch nachts bei 0 % oder bei ausgeschalteter Uhr.",
"fx_started":"{fx} gestartet","fx_stopped":"Effekt gestoppt",
"txt":"Lauftext","txt_ph":"Text eingeben","txt_start":"Lauftext starten","txt_started":"Lauftext gestartet",
"hint_txt":"Jeder Buchstabe füllt die ganze Matrix. Läuft für die Effekt Dauer (mindestens einmal), in der Farbe der Uhrzeit (Zufall = Regenbogen). Lateinische, griechische und kyrillische Buchstaben, Ziffern, Satzzeichen, € und ♥. HTTP: /api/set?text=…",
"sec_sun":"Tag / Nacht","nmode":"Nachtmodus","nm_mix":"Mischform","nm_sun":"Sonnenstand","nm_fixed":"feste Uhrzeiten",
"lat":"Breitengrad","lon":"Längengrad","nso":"Nacht Beginn Versatz (min)","neo":"Nacht Ende Versatz (min)",
"nme":"Nacht frühestens ab","nml":"Nacht spätestens bis","nfs":"Nacht von","nfe":"Nacht bis",
"sunrise":"Sonnenaufgang","sunset":"Sonnenuntergang","night_today":"Nacht heute","now":"Jetzt",
"nmh_0":"Versatz: + nach, − vor Sonnenuntergang bzw. -aufgang. Koordinaten z. B. aus einer Karten-App (Rechtsklick auf den Ort).",
"nmh_1":"Feste Zeiten gelten jeden Tag.",
"nmh_2":"Nacht beginnt bei Sonnenuntergang (plus Versatz), aber frühestens zur eingestellten Zeit, und endet bei Sonnenaufgang (plus Versatz), aber spätestens zur eingestellten Zeit.",
"day":"Tag","night":"Nacht",
"sec_extra":"Zusatzanzeigen","tOnl":"Außentemperatur von Open-Meteo (Standort)",
"scale_out":"Skala außen (°C)","scale_in":"Skala innen (°C)",
"swExtra":"HALLO anzeigen",
"apiTo":"Werte gültig für (min, 0 = immer)",
"v_out":"Außen","v_in":"Innen","v_batt":"Akku","v_la":"Lüften / Alarm","on_":"an","off_":"aus",
"hint_extra":"Innen, Akku, Lüften und Alarm (und außen, falls ohne Open-Meteo) kommen von außen, z. B. per Browser, Skript oder Smarthome:",
"sec_api":"HTTP-Steuerung",
"hint_api1":"Aus anderen Systemen per Browser, Skript oder Smarthome (GET oder POST auf <code>/api/set</code>, mehrere Parameter kombinierbar). Helligkeit, Farben und Schalter werden gespeichert, Effekte laufen für die eingestellte Dauer.",
"hint_api2":"Farben: warmwhite, white, red, orange, yellow, green, blue, violet, random (Temperatur: temp) oder rrggbb · Schalter: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effekte: {fx}, stop · fxcolor: Farbname oder rrggbb. Strombegrenzung, WLAN und System nur hier im Webinterface.",
"sec_time":"Zeit","ntpD":"NTP-Server","ntp_auto":"automatisch (DHCP)","ntp_manual":"manuell","ntp_server":"Server",
"ntp_fallback":"Ersatzserver (falls der Router keinen liefert, gilt nach Neustart)",
"loc":"Standort","loc_custom":"eigener Standort (Koordinaten)","tz_from_loc":"aus Standort {city}",
"tz":"Zeitzone","tz_cet":"Mitteleuropa (DE, AT, CH …)","tz_wet":"London, Lissabon (WEZ)","tz_eet":"Osteuropa (Kyjiw, Athen, Bukarest)",
"tz_trt":"Türkei","tz_eat":"Ostafrika (Tansania, Kenia)","tz_utc":"UTC",
"tz_use":"USA Ost","tz_usc":"USA Zentral","tz_usm":"USA Mountain","tz_usw":"USA West",
"tz_wib":"Indonesien (Jakarta)","tz_cst":"China","tz_kst":"Korea","tz_jst":"Japan","tz_aus":"Australien Ost",
"tz_custom":"eigene (POSIX-TZ) …","tz_posix":"POSIX-Zeitzone","ntp_active":"Aktiver Server",
"ntp_hint":"Automatisch: Server aus dem Router (DHCP), sonst der eingetragene als Ersatz. Wechsel zwischen automatisch und manuell startet die Uhr neu.",
"ntp_nodhcp":"DHCP-NTP ist in diesem Boardpaket nicht verfügbar – es wird der eingetragene Server verwendet.",
"sec_wifi":"WLAN","ssid":"Netzwerk (SSID)","scan":"Netzwerke suchen","pass":"Passwort","pass_ph":"leer lassen = bisheriges behalten",
"host":"Gerätename (http://name.local)","save_wifi":"Speichern & neu verbinden",
"status":"Status","ip":"IP","last_err":"Letzter Fehler",
"hint_wifi":"Wird das WLAN beim Start nicht gefunden, öffnet die Uhr den Hotspot „{ap}“ (ohne Passwort, http://192.168.4.1).",
"w_conn":"verbunden mit {ssid}","w_ap":"Hotspot aktiv ({ip})","w_none":"nicht verbunden",
"scanning":"Suche läuft …","scan_none":"Keine Netzwerke gefunden","scan_err":"Fehler bei der Suche",
"wr_2":"Anmeldung abgelaufen","wr_15":"falsches Passwort?","wr_201":"Netz nicht gefunden","wr_202":"Anmeldung abgelehnt (Passwort?)",
"wr_203":"Zuordnung fehlgeschlagen","wr_204":"falsches Passwort?","wr_205":"Verbindung fehlgeschlagen","wr_8":"getrennt",
"net_hotspot":"Hotspot {ap}","net_off":"WLAN getrennt","net_lost":"keine Verbindung zur Uhr",
"sec_sys":"System","mir":"LED 0 vorn oben rechts (spiegeln)","srp":"Matrix im Zickzack verdrahtet",
"restart":"Neustart","reset":"Werkseinstellungen",
"q_restart":"Uhr neu starten?","q_reset":"Alle Einstellungen inkl. WLAN löschen?",
"language":"Sprache","firmware":"Firmware","uptime":"Laufzeit","heap":"Freier Speicher",
"footer":"{ap} – Bauanleitung, Code und Druckdateien:",
"saved":"Gespeichert","saved_restart":"Gespeichert – Uhr startet neu …","save_err":"Fehler beim Speichern",
"time_set":"Uhrzeit übernommen","restarting":"Uhr startet neu …",
"srv_no_network":"Kein Netzwerk angegeben","srv_back":"Zurück","srv_saved":"WLAN gespeichert",
"srv_connecting":"Die Uhr verbindet sich jetzt mit","srv_restart":"und startet dazu neu. Der Hotspot verschwindet.",
"srv_reach":"Danach erreichbar unter","srv_reach2":"oder über die IP-Adresse aus dem Router bzw. dem seriellen Monitor.",
"srv_retry":"Klappt die Verbindung nicht, erscheint der Hotspot nach etwa 30 Sekunden wieder.",
"srv_not_found":"Nicht gefunden"
})JSON";
}  // namespace wc_de
static const WcLangDef WC_LANG = {
    "DE", "Deutsch", wc_de::GRID,
    {14, 2, 6},   // LÜFTEN
    {14, 9, 5},   // ALARM
    {15, 1, 4},   // AKKU
    {15, 6, 10},  // battery bars
    wc_de::EXTRA, 1,  // HALLO
    wc_de::time_words,
    "wortuhr", "Wortuhr",
    52.5200f, 13.4050f,            // Berlin
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Berlin
    "%d.%m.%Y",
    wc_de::UI_JSON,
};
