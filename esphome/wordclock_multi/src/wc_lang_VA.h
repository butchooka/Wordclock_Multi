/*
  wc_lang_VA.h - Wordclock 16x16, language file VA (Latina), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_VA.scad (check: python3 tools/check_lang.py VA).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_VA.txt)
  Satzbau: EST HORA <Stunde als Ordnungszahl> [ET|MINUS <Minuten>]
  Ab :35 (MINUS) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 (nichts), :05 ET QUINQUE, :10 ET DECEM, :15 ET QUADRANS, :20 ET VIGINTI,
  :25 ET VIGINTI QUINQUE, :30 ET DIMIDIA, :35 MINUS VIGINTI QUINQUE, :40 MINUS VIGINTI,
  :45 MINUS QUADRANTE (Ablativ), :50 MINUS DECEM, :55 MINUS QUINQUE
  Stunden (weiblich zu HORA): PRIMA, SECUNDA, TERTIA, QUARTA, QUINTA, SEXTA, SEPTIMA, OCTAVA,
  NONA, DECIMA, UNDECIMA (DECIMA ist das Ende von UNDECIMA).
  12 Uhr: EST MERIDIES, 0 Uhr: EST MEDIA NOX (über zwei Zeilen, jeweils ohne HORA). Volle Stunde ohne Zusatzwort.
  Moderne Zählung (HORA PRIMA = 1 Uhr), nicht die römische Tagesstunde ab Sonnenaufgang.
  Im Raster „QUADRANTES“: QUADRAN + S = QUADRANS, QUADRANTE.
  Minutenzeile: + 1 MINUTUM (Einzahl), + 2..4 MINUTA (im Raster „MINUTAUM“: Mehrzahl MINUTA,
  Einzahl MINUT + UM).
  Ersatzwörter: LÜFTEN = VENTILA („lüfte!“), ALARM = MONITUM („Warnung“), AKKU = VIGOR („Kraft“).
  Zusatzwörter (Schalter „Ostende ROMANI ITE DOMUM“): ROMANI ITE DOMUM („Römer, geht nach Hause!“) aus
  Monty Pythons „Das Leben des Brian“ - die vom Centurio korrigierte Fassung von ROMANES EUNT DOMUS.
  INFO_EN
  Sentence: EST HORA <hour as ordinal number> [ET|MINUS <minutes>]
  From :35 (MINUS) on the time refers to the next hour.
  :00 (nothing), :05 ET QUINQUE, :10 ET DECEM, :15 ET QUADRANS, :20 ET VIGINTI,
  :25 ET VIGINTI QUINQUE, :30 ET DIMIDIA, :35 MINUS VIGINTI QUINQUE, :40 MINUS VIGINTI,
  :45 MINUS QUADRANTE (ablative), :50 MINUS DECEM, :55 MINUS QUINQUE
  Hours (feminine, agreeing with HORA): PRIMA, SECUNDA, TERTIA, QUARTA, QUINTA, SEXTA, SEPTIMA,
  OCTAVA, NONA, DECIMA, UNDECIMA (DECIMA is the end of UNDECIMA).
  12 o'clock: EST MERIDIES, 0 o'clock: EST MEDIA NOX (over two rows, both without HORA). Full hour without extra word.
  Modern counting (HORA PRIMA = 1 o'clock), not the Roman day hour counted from sunrise.
  Grid "QUADRANTES": QUADRAN + S = QUADRANS, QUADRANTE.
  Minute row: + 1 MINUTUM (singular), + 2..4 MINUTA (grid "MINUTAUM": plural MINUTA,
  singular MINUT + UM).
  Substitute words: VENTILATE = VENTILA ("ventilate!"), ALARM = MONITUM ("warning"),
  BATTERY = VIGOR ("strength").
  Extra words (switch "Ostende ROMANI ITE DOMUM"): ROMANI ITE DOMUM ("Romans, go home!") from Monty Python's
  "Life of Brian" - the centurion's correction of ROMANES EUNT DOMUS.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_va {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*ESTxHORAxPRIMA*",
    "*SECUNDAxTERTIA*",
    "*QUARTAxQUINTAx*",
    "*SEXTAxSEPTIMAx*",
    "*OCTAVAxxxNONAx*",
    "*xxxUNDECIMAxxx*",
    "*MERIDIESxMEDIA*",
    "*NOXxxETxxMINUS*",
    "*VIGINTIQUINQUE*",
    "*DECEMxxDIMIDIA*",
    "*xxQUADRANTESxx*",
    "*xxROMANIxITExx*",
    "*xxxxxDOMUMxxxx*",
    "x+x1234xMINUTAUM",
    "xVENTILAxMONITUM",
    "VIGORx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord EST = {0, 1, 3}, HORA = {0, 5, 4};
static const WcWord MERIDIES = {6, 1, 8}, MEDIA = {6, 10, 5}, NOX = {7, 1, 3};  // MEDIA NOX over two rows
static const WcWord ET = {7, 6, 2}, MINUS = {7, 10, 5};
static const WcWord M_QUINQUE = {8, 8, 7}, M_DECEM = {9, 1, 5}, M_VIGINTI = {8, 1, 7}, M_DIMIDIA = {9, 8, 7};
static const WcWord M_QUADRAN = {10, 3, 7}, M_S = {10, 12, 1}, M_QUADRANTE = {10, 3, 9};  // QUADRAN+S / QUADRANTE
// hour 0..11 (index 0 = MERIDIES, only a placeholder: 0/12 o'clock is MEDIA NOX/MERIDIES, chosen in time_words;
// DECIMA is the end of UNDECIMA)
static const WcWord HOURS[12] = {{6, 1, 8}, {0, 10, 5}, {1, 1, 7}, {1, 9, 6}, {2, 1, 6},  {2, 8, 6},
                                 {3, 1, 5}, {3, 7, 7},  {4, 1, 6}, {4, 10, 4}, {5, 6, 6}, {5, 4, 8}};
// extra words (easter egg): ROMANI ITE DOMUM (Monty Python, Life of Brian: corrected "ROMANES EUNT DOMUS")
static const WcWord EXTRA[3] = {{11, 3, 6}, {11, 10, 3}, {12, 6, 5}};
// row 14: "+ 1 2 3 4  MINUTA/MINUTUM" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 6};  // MINUTA
static const WcWord MIN_STEM = {13, 8, 5}, MIN_UM = {13, 14, 2};   // MINUT + UM = MINUTUM
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  const int m5 = minute / 5;
  int h = hour % 24;
  if (m5 >= 7) h = (h + 1) % 24;  // from "minus viginti quinque" on the next hour counts
  if (!valid) {                   // no time: only the prefix
    m.word(EST);
    m.word(HORA);
    return;
  }
  m.word(EST);
  if (h == 12) m.word(MERIDIES);
  else if (h == 0) { m.word(MEDIA); m.word(NOX); }
  else { m.word(HORA); m.word(HOURS[h % 12]); }                          // HORA PRIMA ...
  switch (m5) {
    case 0: break;
    case 1: m.word(ET); m.word(M_QUINQUE); break;
    case 2: m.word(ET); m.word(M_DECEM); break;
    case 3: m.word(ET); m.word(M_QUADRAN); m.glue(M_S); break;  // QUADRANS
    case 4: m.word(ET); m.word(M_VIGINTI); break;
    case 5: m.word(ET); m.word(M_VIGINTI); m.word(M_QUINQUE); break;
    case 6: m.word(ET); m.word(M_DIMIDIA); break;
    case 7: m.word(MINUS); m.word(M_VIGINTI); m.word(M_QUINQUE); break;
    case 8: m.word(MINUS); m.word(M_VIGINTI); break;
    case 9: m.word(MINUS); m.word(M_QUADRANTE); break;  // ablative
    case 10: m.word(MINUS); m.word(M_DECEM); break;
    default: m.word(MINUS); m.word(M_QUINQUE); break;
  }
  const int mm = minute % 5;  // "+ 1 MINUTUM" or "+ 2..4 MINUTA"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    if (mm == 1) { m.word(MIN_STEM); m.glue(MIN_UM); }  // singular: MINUT + UM, text "MINUTUM"
    else m.word(MIN_WORD);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"la","dec":",",
"notime_msg":"Horologium horam nondum habet (nec interrete nec NTP).",
"btn_settime":"Horam e telephono/computatro sume",
"ap_info":"Hotspot «{ap}» activum. Rete tuum infra sub <b>Wi-Fi</b> inscribe.",
"sec_show":"Ostensio","on":"Horologium accensum","swMin":"Minuta singula (+ 1–4 MINUTA)",
"brD":"Claritas diei","brN":"Claritas noctis","cur":"Limes currentis (mA)",
"hint_show":"Nox 0 % = ostensio noctu exstincta. Limitem currentis ad alimentatorem accommoda (256 LED iam circiter 256 mA otiosi consumunt).",
"sec_col":"Colores",
"hint_col":"«Fortuitus» omni hora plena mutatur. «Temperatura»: frigidum caeruleum obscurum, flavum, commodum viride, aurantium, calidum rubrum (secundum scalam in ostensionibus additis).",
"g_time":"Hora","g_vent":"VENTILA","g_alarm":"MONITUM","g_batt":"VIGOR","g_tout":"Temperatura externa","g_tin":"Temperatura interna",
"pal_0":"Album calidum","pal_1":"Album","pal_2":"Rubrum","pal_3":"Aurantium","pal_4":"Flavum","pal_5":"Viride","pal_6":"Caeruleum","pal_7":"Violaceum",
"c_random":"Fortuitus","c_temp":"Temperatura","c_pride":"Pride","c_custom":"color proprius",
"sec_fx":"Effectus",
"fx_rainbow":"Arcus caelestis","fx_aurora":"Aurora","fx_matrix":"Matrix","fx_fire":"Ignis","fx_confetti":"Confetti","fx_stars":"Caelum stellatum",
"fx_blink":"Micatio","fx_blink_own":"Micatio (color proprius)","stop":"Siste",
"fxd":"Duratio effectus","blk":"Cyclus micationis",
"hint_fx":"Duratio 0 s = currit usque ad «Siste». Effectus semper saltem 10 % claritate currunt, etiam noctu cum 0 % aut horologio exstincto.",
"fx_started":"{fx} incohatum","fx_stopped":"Effectus sistitur",
"txt":"Textus currens","txt_ph":"Textum scribe","txt_start":"Textum ostende","txt_started":"Textus incohatus",
"hint_txt":"Quaeque littera totam matricem implet. Tam diu currit quam effectus (saltem semel), colore horae (fortuitus = arcus caelestis). Litterae Latinae, Graecae, Cyrillicae, numeri, interpunctio, € et ♥. HTTP: /api/set?text=…",
"sec_sun":"Dies / nox","nmode":"Modus nocturnus","nm_mix":"Mixtus","nm_sun":"Situs solis","nm_fixed":"Tempora fixa",
"lat":"Latitudo","lon":"Longitudo","nso":"Translatio initii noctis (min)","neo":"Translatio finis noctis (min)",
"nme":"Nox non ante","nml":"Nox non post","nfs":"Nox ab","nfe":"Nox usque ad",
"sunrise":"Ortus solis","sunset":"Occasus solis","night_today":"Nox hodie","now":"Nunc",
"nmh_0":"Translatio: + post, − ante occasum vel ortum solis. Coordinatae e.g. ex applicatione tabularum (dextro clic in locum).",
"nmh_1":"Tempora fixa omni die valent.",
"nmh_2":"Nox incipit occasu solis (cum translatione), sed non ante tempus statutum, et finitur ortu solis (cum translatione), sed non post tempus statutum.",
"day":"Dies","night":"Nox",
"sec_extra":"Ostensiones additae","swTemp":"Puncta temperaturae (sinistra externa, dextra interna)","tOnl":"Temperatura externa ex Open-Meteo (locus)",
"scale_out":"Scala externa (°C)","scale_in":"Scala interna (°C)",
"swLuft":"Ostende VENTILA","swAlarm":"Ostende MONITUM","swAkku":"Ostende VIGOR","swExtra":"Ostende ROMANI ITE DOMUM",
"apiTo":"Valores valent per (min, 0 = semper)",
"v_out":"Foris","v_in":"Intus","v_batt":"Accumulatrum","v_la":"Ventila / monitum","on_":"accensum","off_":"exstinctum",
"hint_extra":"Intus, accumulatrum, ventila et monitum (et foris, si sine Open-Meteo) extrinsecus veniunt, e.g. per navigatrum, scriptum vel domum callidam:",
"sec_api":"Moderatio HTTP",
"hint_api1":"Ex aliis systematibus per navigatrum, scriptum vel domum callidam (GET aut POST ad <code>/api/set</code>, plures parametri coniungi possunt). Claritas, colores et commutatores servantur, effectus per durationem statutam currunt.",
"hint_api2":"Colores: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatura: temp) aut rrggbb · Commutatores: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effectus: {fx}, stop · fxcolor: nomen coloris aut rrggbb. Limes currentis, Wi-Fi et systema tantum hic in interfacie interretiali.",
"sec_time":"Hora","ntpD":"Servitor NTP","ntp_auto":"automaticus (DHCP)","ntp_manual":"manualis","ntp_server":"Servitor",
"ntp_fallback":"Servitor subsidiarius (si iter ductor nullum praebet, post iteratum initium valet)",
"loc":"Locus","loc_custom":"locus proprius (coordinatae)","tz_from_loc":"ex loco {city}",
"tz":"Zona horaria","tz_cet":"Europa media (VA, IT, DE …)","tz_wet":"Londinium, Olisipo (WET)","tz_eet":"Europa orientalis (Kyiv, Athenae, Bucarestum)",
"tz_trt":"Turcia","tz_eat":"Africa orientalis (Tanzania, Kenia)","tz_utc":"UTC",
"tz_use":"USA orientales","tz_usc":"USA mediae","tz_usm":"USA montanae","tz_usw":"USA occidentales",
"tz_wib":"Indonesia (Iacarta)","tz_cst":"Sina","tz_kst":"Corea","tz_jst":"Iaponia","tz_aus":"Australia orientalis",
"tz_custom":"propria (POSIX TZ) …","tz_posix":"Zona horaria POSIX","ntp_active":"Servitor activus",
"ntp_hint":"Automaticus: servitor ab iter ductore (DHCP), aliter inscriptus ut subsidiarius. Mutatio inter automaticum et manualem horologium iterum incipit.",
"ntp_nodhcp":"NTP per DHCP in hoc fasciculo tabulae non praesto est – servitor inscriptus adhibetur.",
"sec_wifi":"Wi-Fi","ssid":"Rete (SSID)","scan":"Retia quaere","pass":"Tessera","pass_ph":"vacuum = praesentem serva",
"host":"Nomen instrumenti (http://nomen.local)","save_wifi":"Serva et reconecte",
"status":"Status","ip":"IP","last_err":"Error ultimus",
"hint_wifi":"Si Wi-Fi initio non invenitur, horologium hotspot «{ap}» aperit (sine tessera, http://192.168.4.1).",
"w_conn":"conexum cum {ssid}","w_ap":"Hotspot activum ({ip})","w_none":"non conexum",
"scanning":"Quaeritur …","scan_none":"Nulla retia inventa","scan_err":"Quaestio defecit",
"wr_2":"authenticatio exspiravit","wr_15":"tessera falsa?","wr_201":"rete non inventum","wr_202":"authenticatio reiecta (tessera?)",
"wr_203":"consociatio defecit","wr_204":"tessera falsa?","wr_205":"conexio defecit","wr_8":"disiunctum",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi disiunctum","net_lost":"nulla conexio cum horologio",
"sec_sys":"Systema","mir":"LED 0 a fronte supra dextra (speculum)","srp":"Matrix flexuose conexa",
"restart":"Iterum incipe","reset":"Restitutio ad statum officinae",
"q_restart":"Horologium iterum incipere?","q_reset":"Omnes optiones, etiam Wi-Fi, delere?",
"language":"Lingua","firmware":"Firmware","uptime":"Tempus operationis","heap":"Memoria libera",
"footer":"{ap} – instructio aedificandi, codex et fasciculi imprimendi:",
"saved":"Servatum","saved_restart":"Servatum – horologium iterum incipit …","save_err":"Error in servando",
"time_set":"Hora accepta","restarting":"Horologium iterum incipit …",
"srv_no_network":"Nullum rete inscriptum","srv_back":"Retro","srv_saved":"Wi-Fi servatum",
"srv_connecting":"Horologium nunc conectitur cum","srv_restart":"et ideo iterum incipit. Hotspot evanescit.",
"srv_reach":"Postea attingi potest per","srv_reach2":"aut per inscriptionem IP ex iter ductore vel monitore seriali.",
"srv_retry":"Si conexio deficit, hotspot post circiter 30 secunda iterum apparet.",
"srv_not_found":"Non inventum"
})JSON";
}  // namespace wc_va
static const WcLangDef WC_LANG = {
    "VA", "Latina", wc_va::GRID,
    {14, 1, 7},   // VENTILA
    {14, 9, 7},   // MONITUM
    {15, 0, 5},   // VIGOR
    {15, 6, 10},  // battery bars
    wc_va::EXTRA, 3,  // ROMANI ITE DOMUM
    wc_va::time_words,
    "horologium", "Horologium",
    41.9029f, 12.4534f,            // Città del Vaticano
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Rome (Europe/Vatican)
    "%d/%m/%Y",
    wc_va::UI_JSON,
};
