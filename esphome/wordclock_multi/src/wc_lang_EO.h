/*
  wc_lang_EO.h - Wordclock 16x16, language file EO (Esperanto), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_EO.scad (check: python3 tools/check_lang.py EO).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_EO.txt)
  Kürzel EO (ISO-639-Sprachcode, Esperanto hat kein Hauptland). Standort Warszawa (Erstausgabe „Unua Libro“ 1887).
  Satzbau: ESTAS [<Minuten> POST | <Minuten> ANTAŬ] LA <Stunde>, zur halben Stunde ESTAS LA <Stunde> KAJ DUONO
  (ESTAS = „es ist“, POST = „nach“, ANTAŬ = „vor“, KAJ DUONO = „und eine Hälfte“, KVARONO = „Viertel“).
  Ab :35 bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 ESTAS LA <Stunde>, :05 KVIN POST, :10 DEK POST, :15 KVARONO POST, :20 DUDEK POST, :25 DUDEK KVIN POST,
  :30 LA <Stunde> KAJ DUONO, :35 DUDEK KVIN ANTAŬ, :40 DUDEK ANTAŬ, :45 KVARONO ANTAŬ, :50 DEK ANTAŬ,
  :55 KVIN ANTAŬ; z. B. 3:05 ESTAS KVIN POST LA TRIA, 3:30 ESTAS LA TRIA KAJ DUONO, 3:45 ESTAS KVARONO ANTAŬ LA KVARA.
  Stunden als Ordnungszahlen (12-Stunden-Zählung, „la tria“ = „die dritte [Stunde]“): UNUA, DUA, TRIA, KVARA,
  KVINA, SESA, SEPA, OKA, NAŬA, DEKA, DEKUNUA, DEKDUA (11 und 12 aus DEK + UNUA / DUA, im Text zusammengeschrieben).
  12 und 0 Uhr = LA DEKDUA. Ohne gültige Uhrzeit leuchtet nur ESTAS.
  Minutenzeile: + 1 MINUTO / + 2..4 MINUTOJ (Mehrzahl = angehängtes J).
  Ersatzwörter: LÜFTEN = AERUMI („lüften“), ALARM = ALARMO, AKKU = PILO („Batterie, Zelle“; BATERIO zu lang).
  Zusatzwörter (Schalter „Montri SALUTON MONDO“, aus = Standard): SALUTON MONDO („Hallo Welt“).
  Sonderzeichen: Ŭ (ANTAŬ, NAŬA) ist eine Zelle (Metriken für Ĉ Ĝ Ĥ Ĵ Ŝ Ŭ in Wordclock_Model.scad).
  INFO_EN
  Code EO (ISO 639 language code, Esperanto has no main country). Location Warszawa (first "Unua Libro", 1887).
  Sentence: ESTAS [<minutes> POST | <minutes> ANTAŬ] LA <hour>, at half past ESTAS LA <hour> KAJ DUONO
  (ESTAS = "it is", POST = "after", ANTAŬ = "before", KAJ DUONO = "and a half", KVARONO = "quarter").
  From :35 on the time refers to the next hour.
  :00 ESTAS LA <hour>, :05 KVIN POST, :10 DEK POST, :15 KVARONO POST, :20 DUDEK POST, :25 DUDEK KVIN POST,
  :30 LA <hour> KAJ DUONO, :35 DUDEK KVIN ANTAŬ, :40 DUDEK ANTAŬ, :45 KVARONO ANTAŬ, :50 DEK ANTAŬ,
  :55 KVIN ANTAŬ; e.g. 3:05 ESTAS KVIN POST LA TRIA, 3:30 ESTAS LA TRIA KAJ DUONO, 3:45 ESTAS KVARONO ANTAŬ LA KVARA.
  Hours as ordinal numbers (12-hour count, "la tria" = "the third [hour]"): UNUA, DUA, TRIA, KVARA,
  KVINA, SESA, SEPA, OKA, NAŬA, DEKA, DEKUNUA, DEKDUA (11 and 12 from DEK + UNUA / DUA, written as one word).
  12:00 and 0:00 = LA DEKDUA. Without a valid time only ESTAS is lit.
  Minute row: + 1 MINUTO / + 2..4 MINUTOJ (plural = appended J).
  Substitute words: VENTILATE = AERUMI ("to air"), ALARM = ALARMO, BATTERY = PILO ("battery, cell"; BATERIO too long).
  Extra words (switch "Montri SALUTON MONDO", off by default): SALUTON MONDO ("hello world").
  Special character: Ŭ (ANTAŬ, NAŬA) is one cell (metrics for Ĉ Ĝ Ĥ Ĵ Ŝ Ŭ in Wordclock_Model.scad).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_eo {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xESTASxxDUDEKx*",
    "*KVARONOxxKVINx*",
    "*xxDEKxxxxPOSTx*",
    "*xANTAŬxxxxxLAx*",
    "*xxDEKxUNUAxDUA*",
    "*TRIAxxxxxKVARA*",
    "*xKVINAxxxSESAx*",
    "*SEPAxxOKAxNAŬA*",
    "*xxxDEKAxxKAJxx*",
    "*xxxxDUONOxxxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xSALUTONxMONDO*",
    "*xxxxxxxxxxxxxx*",
    "x+x1234xMINUTOJx",
    "xAERUMIxxxALARMO",
    "PILOxx||||||||||",
};
// {row, column, length}, row/column counted from 0 (Ŭ is one cell)
static const WcWord ESTAS = {0, 2, 5}, M_DUDEK = {0, 9, 5}, KVARONO = {1, 1, 7}, M_KVIN = {1, 10, 4};
static const WcWord M_DEK = {2, 3, 3}, POST = {2, 10, 4}, ANTAU = {3, 2, 5}, LA = {3, 12, 2};
static const WcWord H_DEK = {4, 3, 3}, KAJ = {8, 10, 3}, DUONO = {9, 5, 5};
// hours 0..11 (0 = DEKDUA, 11 = DEKUNUA: DEK + UNUA / DUA, set in time_words)
static const WcWord HOURS[12] = {{4, 12, 3}, {4, 7, 4}, {4, 12, 3}, {5, 1, 4}, {5, 10, 5}, {6, 2, 5},
                                 {6, 10, 4}, {7, 1, 4}, {7, 7, 3}, {7, 11, 4}, {8, 4, 4}, {4, 7, 4}};
// extra words (easter egg): SALUTON MONDO ("hello world")
static const WcWord EXTRA[2] = {{11, 2, 7}, {11, 10, 5}};
// row 14: "+ 1 2 3 4  MINUTO(J)" (digits in columns 3..6, plural J glued)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 6}, MIN_J = {13, 14, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void minutes_word(int n5, WcMark &m) {  // n5 = 1..5 (5..25 minutes)
  switch (n5) {
    case 1: m.word(M_KVIN); break;
    case 2: m.word(M_DEK); break;
    case 3: m.word(KVARONO); break;
    case 4: m.word(M_DUDEK); break;
    default: m.word(M_DUDEK); m.word(M_KVIN); break;
  }
}
static inline void hour_word(int h12, WcMark &m) {  // h12 = 0..11
  if (h12 == 0) { m.word(H_DEK); m.glue(HOURS[0]); }        // DEKDUA
  else if (h12 == 11) { m.word(H_DEK); m.glue(HOURS[11]); } // DEKUNUA
  else m.word(HOURS[h12]);
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(ESTAS);
  if (!valid) return;  // no time: only the prefix
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 7) h = (h + 1) % 12;  // from "antaŭ" on the next hour counts
  if (m5 >= 1 && m5 <= 5) { minutes_word(m5, m); m.word(POST); }
  else if (m5 >= 7) { minutes_word(12 - m5, m); m.word(ANTAU); }
  m.word(LA);
  hour_word(h, m);
  if (m5 == 6) { m.word(KAJ); m.word(DUONO); }
  const int mm = minute % 5;  // "+ 1 MINUTO" / "+ 2..4 MINUTOJ"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_WORD);
    if (mm > 1) m.glue(MIN_J);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"eo","dec":",",
"notime_msg":"La horloĝo ankoraŭ ne havas la horon (neniu interreto aŭ NTP).",
"btn_settime":"Preni la horon de telefono/komputilo",
"ap_info":"Retpunkto “{ap}” aktiva. Bonvolu enigi vian reton sube ĉe <b>Wi-Fi</b>.",
"sec_show":"Montrado","on":"Horloĝo ŝaltita","swMin":"Unuopaj minutoj (+ 1–4 MINUTOJ)",
"brD":"Heleco tage","brN":"Heleco nokte","cur":"Kurentlimo (mA)",
"hint_show":"Nokte 0 % = ekrano malŝaltita nokte. Elektu la kurentlimon laŭ la elektrofonto (256 LED-oj jam bezonas ĉ. 256 mA da ripoza kurento).",
"sec_col":"Koloroj",
"hint_col":"“Hazarda” ŝanĝiĝas ĉiun plenan horon. “Temperaturo”: malvarma malhelblua, flava, komforta verda, oranĝa, varmega ruĝa (laŭ la skalo sub aldonaj montradoj).",
"g_time":"Horo","g_vent":"AERUMI","g_alarm":"ALARMO","g_batt":"PILO","g_tout":"Ekstera temperaturo","g_tin":"Interna temperaturo",
"pal_0":"Varma blanka","pal_1":"Blanka","pal_2":"Ruĝa","pal_3":"Oranĝa","pal_4":"Flava","pal_5":"Verda","pal_6":"Blua","pal_7":"Viola",
"c_random":"Hazarda","c_temp":"Temperaturo","c_pride":"Pride","c_custom":"propra koloro",
"sec_fx":"Efektoj",
"fx_rainbow":"Ĉielarko","fx_aurora":"Aŭroro","fx_matrix":"Matrico","fx_fire":"Fajro","fx_confetti":"Konfetoj","fx_stars":"Stelplena ĉielo",
"fx_blink":"Brileti","fx_blink_own":"Brileti (propra koloro)","stop":"Haltigi",
"fxd":"Daŭro de efekto","blk":"Ciklo de brileto",
"hint_fx":"Daŭro 0 s = daŭras ĝis “Haltigi”. Efektoj ĉiam funkcias kun almenaŭ 10 % da heleco, ankaŭ nokte kun 0 % aŭ kun malŝaltita horloĝo.",
"fx_started":"{fx} komenciĝis","fx_stopped":"Efekto haltigita",
"txt":"Kurtektsto","txt_ph":"Enigu tekston","txt_start":"Montri tekston","txt_started":"Teksto komenciĝis",
"hint_txt":"Ĉiu litero plenigas la tutan matricon. Daŭras tiel longe kiel la efekto (almenaŭ unufoje), en la koloro de la horo (hazarda = ĉielarko). Latinaj, grekaj kaj cirilaj literoj, ciferoj, interpunkcio, € kaj ♥. HTTP: /api/set?text=…",
"sec_sun":"Tago / nokto","nmode":"Nokta reĝimo","nm_mix":"Miksita","nm_sun":"Sunpozicio","nm_fixed":"Fiksaj horoj",
"lat":"Latitudo","lon":"Longitudo","nso":"Deŝovo de nokta komenco (min)","neo":"Deŝovo de nokta fino (min)",
"nme":"Nokto ne antaŭ","nml":"Nokto ne post","nfs":"Nokto de","nfe":"Nokto ĝis",
"sunrise":"Sunleviĝo","sunset":"Sunsubiro","night_today":"Nokto hodiaŭ","now":"Nun",
"nmh_0":"Deŝovo: + post, − antaŭ sunsubiro aŭ sunleviĝo. Koordinatoj ekz. el mapa apo (dekstra klako sur la loko).",
"nmh_1":"Fiksaj horoj validas ĉiutage.",
"nmh_2":"La nokto komenciĝas je sunsubiro (plus deŝovo), sed ne antaŭ la agordita horo, kaj finiĝas je sunleviĝo (plus deŝovo), sed ne post la agordita horo.",
"day":"Tago","night":"Nokto",
"sec_extra":"Aldonaj montradoj","tOnl":"Ekstera temperaturo de Open-Meteo (loko)",
"scale_out":"Skalo ekstere (°C)","scale_in":"Skalo interne (°C)",
"swExtra":"Montri SALUTON MONDO",
"apiTo":"Valoroj validas dum (min, 0 = ĉiam)",
"v_out":"Ekstere","v_in":"Interne","v_batt":"Pilo","v_la":"Aerumi / alarmo","on_":"ŝaltita","off_":"malŝaltita",
"hint_extra":"Interne, pilo, aerumi kaj alarmo (kaj ekstere, se sen Open-Meteo) venas de ekstere, ekz. per retumilo, skripto aŭ inteligenta hejmo:",
"sec_api":"HTTP-regado",
"hint_api1":"El aliaj sistemoj per retumilo, skripto aŭ inteligenta hejmo (GET aŭ POST al <code>/api/set</code>, pluraj parametroj kombineblas). Heleco, koloroj kaj ŝaltiloj estas konservataj, efektoj funkcias dum la agordita daŭro.",
"hint_api2":"Koloroj: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperaturo: temp) aŭ rrggbb · Ŝaltiloj: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Efektoj: {fx}, stop · fxcolor: kolornomo aŭ rrggbb. Kurentlimo, Wi-Fi kaj sistemo nur ĉi tie en la retinterfaco.",
"sec_time":"Horo","ntpD":"NTP-servilo","ntp_auto":"aŭtomata (DHCP)","ntp_manual":"permana","ntp_server":"Servilo",
"ntp_fallback":"Rezerva servilo (se la enkursigilo ne donas unu, validas post restarto)",
"loc":"Loko","loc_custom":"propra loko (koordinatoj)","tz_from_loc":"laŭ loko {city}",
"tz":"Horzono","tz_cet":"Mezeŭropo (DE, AT, CH …)","tz_wet":"Londono, Lisbono (WET)","tz_eet":"Orienta Eŭropo (Kievo, Ateno, Bukareŝto)",
"tz_trt":"Turkio","tz_eat":"Orienta Afriko (Tanzanio, Kenjo)","tz_utc":"UTC",
"tz_use":"Usono oriento","tz_usc":"Usono centro","tz_usm":"Usono montaro","tz_usw":"Usono okcidento",
"tz_wib":"Indonezio (Ĝakarto)","tz_cst":"Ĉinio","tz_kst":"Koreio","tz_jst":"Japanio","tz_aus":"Aŭstralio oriento",
"tz_custom":"propra (POSIX TZ) …","tz_posix":"POSIX-horzono","ntp_active":"Aktiva servilo",
"ntp_hint":"Aŭtomata: servilo de la enkursigilo (DHCP), alie la enigita kiel rezervo. Ŝanĝo inter aŭtomata kaj permana restartigas la horloĝon.",
"ntp_nodhcp":"NTP per DHCP ne disponeblas en ĉi tiu plat-pakaĵo – la enigita servilo estas uzata.",
"sec_wifi":"Wi-Fi","ssid":"Reto (SSID)","scan":"Serĉi retojn","pass":"Pasvorto","pass_ph":"lasi malplena = konservi la nunan",
"host":"Aparatnomo (http://nomo.local)","save_wifi":"Konservi kaj rekonekti",
"status":"Stato","ip":"IP","last_err":"Lasta eraro",
"hint_wifi":"Se la Wi-Fi ne troviĝas dum la starto, la horloĝo malfermas la retpunkton “{ap}” (sen pasvorto, http://192.168.4.1).",
"w_conn":"konektita al {ssid}","w_ap":"Retpunkto aktiva ({ip})","w_none":"ne konektita",
"scanning":"Serĉante …","scan_none":"Neniuj retoj trovitaj","scan_err":"Serĉo malsukcesis",
"wr_2":"aŭtentigo eksvalidiĝis","wr_15":"malĝusta pasvorto?","wr_201":"reto ne trovita","wr_202":"aŭtentigo rifuzita (pasvorto?)",
"wr_203":"asociiĝo malsukcesis","wr_204":"malĝusta pasvorto?","wr_205":"konekto malsukcesis","wr_8":"malkonektita",
"net_hotspot":"Retpunkto {ap}","net_off":"Wi-Fi malkonektita","net_lost":"neniu konekto al la horloĝo",
"sec_sys":"Sistemo","mir":"LED 0 antaŭe supre dekstre (spegulita)","srp":"Matrico kablita zigzage",
"restart":"Restartigi","reset":"Fabrikaj agordoj",
"q_restart":"Ĉu restartigi la horloĝon?","q_reset":"Ĉu forigi ĉiujn agordojn inkluzive de Wi-Fi?",
"language":"Lingvo","firmware":"Mikroprogramo","uptime":"Funkcidaŭro","heap":"Libera memoro",
"footer":"{ap} – konstrugvidilo, kodo kaj presdosieroj:",
"saved":"Konservita","saved_restart":"Konservita – la horloĝo restartas …","save_err":"Eraro dum konservado",
"time_set":"Horo transprenita","restarting":"La horloĝo restartas …",
"srv_no_network":"Neniu reto enigita","srv_back":"Reen","srv_saved":"Wi-Fi konservita",
"srv_connecting":"La horloĝo nun konektiĝas al","srv_restart":"kaj restartas por tio. La retpunkto malaperas.",
"srv_reach":"Poste atingebla ĉe","srv_reach2":"aŭ per la IP-adreso el la enkursigilo aŭ la seria monitoro.",
"srv_retry":"Se la konekto malsukcesas, la retpunkto reaperas post ĉ. 30 sekundoj.",
"srv_not_found":"Ne trovita"
})JSON";
}  // namespace wc_eo
static const WcLangDef WC_LANG = {
    "EO", "Esperanto", wc_eo::GRID,
    {14, 1, 6},   // AERUMI
    {14, 10, 6},  // ALARMO
    {15, 0, 4},   // PILO
    {15, 6, 10},  // battery bars
    wc_eo::EXTRA, 2,  // SALUTON MONDO
    wc_eo::time_words,
    "vorthorlogo", "VortHorlogo",
    52.2297f, 21.0122f,  // Warszawa
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Warsaw
    "%Y-%m-%d",
    wc_eo::UI_JSON,
};
