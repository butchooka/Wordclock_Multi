/*
  wc_lang_dialect_CH.h - Wordclock 16x16, language file dialect_CH (Schwizerdütsch, Swiss German), v1.0
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_dialect_CH.scad (check: python3 tools/check_lang.py dialect_CH).
  Preview of all times: see tools/preview.cpp.
  Code dialect_CH (CH = country code of Switzerland). Zurich-style Swiss German (the variant of most Swiss word clocks).
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_dialect_CH.txt)
  Satzbau (Schwizerdütsch, Zürcher Form wie bei den meisten Schweizer Wortuhren):
  ES ISCH [<Minuten> AB|VOR] [HALBI] <Stunde>
  Ab :25 („füf vor halbi drü“ = 2:25) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 <Stunde>, :05 FÜF AB, :10 ZÄH AB, :15 VIERTEL AB, :20 ZWÄNZG AB,
  :25 FÜF VOR HALBI, :30 HALBI, :35 FÜF AB HALBI, :40 ZWÄNZG VOR, :45 VIERTEL VOR,
  :50 ZÄH VOR, :55 FÜF VOR
  Beispiele: 3:00 = ES ISCH DRÜ, 3:20 = ES ISCH ZWÄNZG AB DRÜ, 3:30 = ES ISCH HALBI VIERI.
  Schwizerdütsch: „ab“ statt „nach“, HALBI statt halb, ZÄH/FÜF/ZWÄNZG statt zehn/fünf/zwanzig,
  Stunden in der Form mit -i („am vieri“): EIS, ZWÖI, DRÜ, VIERI, FÜFI, SÄCHSI, SIBNI, ACHTI,
  NÜNI, ZÄNI, ELFI, ZWÖLFI (EIS, ZWÖI und DRÜ ohne -i).
  Kein „Uhr“ zur vollen Stunde (ES ISCH DRÜ).
  12-Stunden-Anzeige: 0 und 12 Uhr = ZWÖLFI.
  Minutenzeile: + 1 MINUTE und + 2..4 MINUTE (Einzahl und Mehrzahl sind gleich, kein -n).
  Webinterface: Schweizer Hochdeutsch (ss statt ß).
  Extra-Wörter (Schalter „GRÜEZI MITENAND anzeigen“): GRÜEZI MITENAND („Grüss euch alle“).
  INFO_EN
  Sentence (Swiss German, Zurich form as used by most Swiss word clocks):
  ES ISCH [<minutes> AB|VOR] [HALBI] <hour>
  From :25 ("füf vor halbi drü" = 2:25, five before half three) on the time refers to the next hour.
  :00 <hour>, :05 FÜF AB, :10 ZÄH AB, :15 VIERTEL AB, :20 ZWÄNZG AB,
  :25 FÜF VOR HALBI, :30 HALBI, :35 FÜF AB HALBI, :40 ZWÄNZG VOR, :45 VIERTEL VOR,
  :50 ZÄH VOR, :55 FÜF VOR
  Examples: 3:00 = ES ISCH DRÜ, 3:20 = ES ISCH ZWÄNZG AB DRÜ, 3:30 = ES ISCH HALBI VIERI (half four).
  Swiss German: "ab" (past), "vor" (to), HALBI (half), ZÄH/FÜF/ZWÄNZG (ten/five/twenty),
  hours in the form with -i ("am vieri" = at four): EIS, ZWÖI, DRÜ, VIERI, FÜFI, SÄCHSI, SIBNI, ACHTI,
  NÜNI, ZÄNI, ELFI, ZWÖLFI (EIS, ZWÖI and DRÜ without -i).
  No "o'clock" word at the full hour (ES ISCH DRÜ).
  12-hour display: 0 and 12 o'clock = ZWÖLFI.
  Minute row: + 1 MINUTE and + 2..4 MINUTE (singular and plural are the same, no -n).
  Web interface: Swiss Standard German (ss instead of ß).
  Extra words (switch "GRÜEZI MITENAND anzeigen"): GRÜEZI MITENAND ("hello everybody").
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_dialect_ch {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xESxISCHxxFÜFx*",
    "*xZÄHxxZWÄNZGxx*",
    "*xxxVIERTELxxxx*",
    "*xxVORxxxxABxxx*",
    "*xxxxHALBIxxxxx*",
    "*xEISxZWÖIxDRÜx*",
    "*xVIERIxxxFÜFIx*",
    "*xSÄCHSIxSIBNIx*",
    "*xACHTIxxxNÜNIx*",
    "*xZÄNIxxxxELFIx*",
    "*xxxxZWÖLFIxxxx*",
    "*xxxxGRÜEZIxxxx*",
    "*xxxMITENANDxxx*",
    "x+x1234xMINUTExx",
    "xxLÜFTExxALARMxx",
    "xAKKUx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord ES = {0, 2, 2}, ISCH = {0, 5, 4};
static const WcWord M_FUEF = {0, 11, 3}, M_ZAEH = {1, 2, 3}, M_ZWAENZG = {1, 7, 6}, VIERTEL = {2, 4, 7};
static const WcWord VOR = {3, 3, 3}, AB = {3, 10, 2}, HALBI = {4, 5, 5};
// hour 0..11 (0 = twelve)
static const WcWord HOURS[12] = {{10, 5, 6}, {5, 2, 3}, {5, 6, 4}, {5, 11, 3}, {6, 2, 5}, {6, 10, 4},
                                 {7, 2, 6},  {7, 9, 5}, {8, 2, 5}, {8, 10, 4}, {9, 2, 4}, {9, 10, 4}};
// extra words (easter egg): GRÜEZI MITENAND
static const WcWord EXTRA[2] = {{11, 5, 6}, {12, 4, 8}};
// row 14: "+ 1 2 3 4  MINUTE" (digits in columns 3..6), singular = plural
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 6};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(ES);
  m.word(ISCH);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 5) h = (h + 1) % 12;  // from "füf vor halbi" on the next hour counts
  switch (m5) {
    case 0: break;
    case 1: m.word(M_FUEF); m.word(AB); break;
    case 2: m.word(M_ZAEH); m.word(AB); break;
    case 3: m.word(VIERTEL); m.word(AB); break;
    case 4: m.word(M_ZWAENZG); m.word(AB); break;
    case 5: m.word(M_FUEF); m.word(VOR); m.word(HALBI); break;
    case 6: m.word(HALBI); break;
    case 7: m.word(M_FUEF); m.word(AB); m.word(HALBI); break;
    case 8: m.word(M_ZWAENZG); m.word(VOR); break;
    case 9: m.word(VIERTEL); m.word(VOR); break;
    case 10: m.word(M_ZAEH); m.word(VOR); break;
    default: m.word(M_FUEF); m.word(VOR); break;
  }
  m.word(HOURS[h]);
  const int mm = minute % 5;  // "+ 1..4 MINUTE"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_WORD);  // singular and plural are both MINUTE
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"de","dec":",",
"notime_msg":"Die Uhr hat noch keine Uhrzeit (kein Internet bzw. NTP).",
"btn_settime":"Uhrzeit vom Handy/PC übernehmen",
"ap_info":"Hotspot „{ap}“ aktiv. Bitte unten unter <b>WLAN</b> dein Netzwerk eintragen.",
"sec_show":"Anzeige","on":"Uhr eingeschaltet","swMin":"Einzelminuten (+ 1–4 MINUTE)",
"brD":"Helligkeit Tag","brN":"Helligkeit Nacht","cur":"Strombegrenzung (mA)",
"hint_show":"Nacht 0 % = Anzeige nachts aus. Strombegrenzung passend zum Netzteil wählen (256 LEDs brauchen schon ca. 256 mA Ruhestrom).",
"sec_col":"Farben",
"hint_col":"„Zufall“ wechselt jede volle Stunde. „Temperatur“: kalt dunkelblau, gelb, Komfort grün, orange, heiss rot (nach der Skala unter Zusatzanzeigen).",
"g_time":"Uhrzeit","g_vent":"LÜFTE","g_alarm":"ALARM","g_batt":"AKKU","g_tout":"Temperatur aussen","g_tin":"Temperatur innen",
"pal_0":"Warmweiss","pal_1":"Weiss","pal_2":"Rot","pal_3":"Orange","pal_4":"Gelb","pal_5":"Grün","pal_6":"Blau","pal_7":"Violett",
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
"sec_extra":"Zusatzanzeigen","tOnl":"Aussentemperatur von Open-Meteo (Standort)",
"scale_out":"Skala aussen (°C)","scale_in":"Skala innen (°C)",
"swExtra":"GRÜEZI MITENAND anzeigen",
"apiTo":"Werte gültig für (min, 0 = immer)",
"v_out":"Aussen","v_in":"Innen","v_batt":"Akku","v_la":"Lüften / Alarm","on_":"an","off_":"aus",
"hint_extra":"Innen, Akku, Lüften und Alarm (und aussen, falls ohne Open-Meteo) kommen von aussen, z. B. per Browser, Skript oder Smarthome:",
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
}  // namespace wc_dialect_ch
static const WcLangDef WC_LANG = {
    "dialect_CH", "Schwizerdütsch", wc_dialect_ch::GRID,
    {14, 2, 5},   // LÜFTE
    {14, 9, 5},   // ALARM
    {15, 1, 4},   // AKKU
    {15, 6, 10},  // battery bars
    wc_dialect_ch::EXTRA, 2,  // GRÜEZI MITENAND
    wc_dialect_ch::time_words,
    "wortuehrli", "Wortuehrli",
    46.9480f, 7.4474f,             // Bern
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Zurich
    "%d.%m.%Y",
    wc_dialect_ch::UI_JSON,
};
