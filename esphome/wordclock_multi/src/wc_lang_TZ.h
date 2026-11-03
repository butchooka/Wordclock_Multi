/*
  wc_lang_TZ.h - Wordclock 16x16, language file TZ (Kiswahili), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_TZ.scad (check: python3 tools/check_lang.py TZ).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_TZ.txt)
  Besonderheit: Swahili-Zeit (saa za Kiswahili). Die Stunden zählen ab Sonnenaufgang bzw. -untergang,
  also ab 6 Uhr und ab 18 Uhr: 7 Uhr = SAA MOJA („erste Stunde“), 12 Uhr = SAA SITA, 18 Uhr = SAA KUMI NA MBILI.
  Swahili-Stunde = (Uhrzeit + 6) mod 12. Weil die Zählung zweimal am Tag gleich ist, steht die Tageszeit am Ende.
  Satzbau: NI SAA <Stunde> [NA <Minuten> | KASORO <Minuten>] <Tageszeit>
  (NI SAA = „es ist Stunde“, NA = „und“, KASORO = „weniger“). Ab :35 bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 (nichts), :05 NA DAKIKA TANO, :10 NA DAKIKA KUMI, :15 NA ROBO, :20 NA DAKIKA ISHIRINI,
  :25 NA DAKIKA ISHIRINI NA TANO, :30 NA NUSU, :35 KASORO DAKIKA ISHIRINI NA TANO,
  :40 KASORO DAKIKA ISHIRINI, :45 KASORO ROBO, :50 KASORO DAKIKA KUMI, :55 KASORO DAKIKA TANO
  Stunden (Swahili-Zeit): 7/19 Uhr MOJA, 8/20 MBILI, 9/21 TATU, 10/22 NNE, 11/23 TANO, 12/0 SITA, 1/13 SABA,
  2/14 NANE, 3/15 TISA, 4/16 KUMI, 5/17 KUMI NA MOJA, 6/18 KUMI NA MBILI (KUMI, NA, MOJA in einer Zeile).
  TANO, KUMI und NA gibt es für Stunden und Minuten getrennt (NA dreimal: Stunde 11/12, „und“, :25/:35).
  Tageszeit am Satzende (nach der genannten Stunde): ALFAJIRI 4-5 Uhr, ASUBUHI 6-11 Uhr, MCHANA 12-15 Uhr,
  JIONI 16-18 Uhr, USIKU 19-3 Uhr; z. B. 7:00 NI SAA MOJA ASUBUHI, 13:47 NI SAA NANE KASORO ROBO MCHANA,
  0:00 NI SAA SITA USIKU, 5:30 NI SAA KUMI NA MOJA NA NUSU ALFAJIRI.
  Ohne gültige Uhrzeit leuchtet nur NI SAA.
  Minutenzeile: + 1..4 DAKIKA (Swahili hat keine Mehrzahlform, DAKIKA gilt für 1 und mehrere Minuten).
  Ersatzwörter: LÜFTEN = HEWA („Luft“), ALARM = KENGELE („Glocke/Klingel“), AKKU = BETRI („Batterie“).
  Zusatzwörter (Schalter „Onyesha HAKUNA MATATA“): HAKUNA MATATA („keine Sorgen“).
  INFO_EN
  Special: Swahili time (saa za Kiswahili). Hours are counted from sunrise or sunset, i.e. from 6 h and 18 h:
  7:00 = SAA MOJA ("first hour"), 12:00 = SAA SITA, 18:00 = SAA KUMI NA MBILI.
  Swahili hour = (clock hour + 6) mod 12. As the count repeats twice a day, the time of day is added at the end.
  Sentence: NI SAA <hour> [NA <minutes> | KASORO <minutes>] <time of day>
  (NI SAA = "it is hour", NA = "and", KASORO = "less"). From :35 on the time refers to the next hour.
  :00 (nothing), :05 NA DAKIKA TANO, :10 NA DAKIKA KUMI, :15 NA ROBO, :20 NA DAKIKA ISHIRINI,
  :25 NA DAKIKA ISHIRINI NA TANO, :30 NA NUSU, :35 KASORO DAKIKA ISHIRINI NA TANO,
  :40 KASORO DAKIKA ISHIRINI, :45 KASORO ROBO, :50 KASORO DAKIKA KUMI, :55 KASORO DAKIKA TANO
  Hours (Swahili time): 7/19 h MOJA, 8/20 MBILI, 9/21 TATU, 10/22 NNE, 11/23 TANO, 12/0 SITA, 1/13 SABA,
  2/14 NANE, 3/15 TISA, 4/16 KUMI, 5/17 KUMI NA MOJA, 6/18 KUMI NA MBILI (KUMI, NA, MOJA in one row).
  TANO, KUMI and NA exist separately for hours and minutes (NA three times: hour 11/12, "and", :25/:35).
  Time of day at the end (after the hour said): ALFAJIRI 4-5 h, ASUBUHI 6-11 h, MCHANA 12-15 h,
  JIONI 16-18 h, USIKU 19-3 h; e.g. 7:00 NI SAA MOJA ASUBUHI, 13:47 NI SAA NANE KASORO ROBO MCHANA,
  0:00 NI SAA SITA USIKU, 5:30 NI SAA KUMI NA MOJA NA NUSU ALFAJIRI.
  Without a valid time only NI SAA is lit.
  Minute row: + 1..4 DAKIKA (Swahili has no plural form, DAKIKA is used for one and several minutes).
  Substitute words: VENTILATE = HEWA ("air"), ALARM = KENGELE ("bell"), BATTERY = BETRI ("battery").
  Extra words (switch "Onyesha HAKUNA MATATA"): HAKUNA MATATA ("no worries").
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_tz {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xxxxNIxSAAxxxx*",
    "*xKUMIxNAxMOJAx*",
    "*MBILIxTATUxNNE*",
    "*TANOxSITAxSABA*",
    "*NANExTISAxxxNA*",
    "*KASOROxxDAKIKA*",
    "*ROBOxNUSUxKUMI*",
    "*xxISHIRINIxNAx*",
    "*TANOxxxASUBUHI*",
    "*MCHANAxxxJIONI*",
    "*USIKUxALFAJIRI*",
    "*xxxxxxxxxxxxxx*",
    "*xHAKUNAxMATATA*",
    "x+x1234xxDAKIKAx",
    "xHEWAxxxxKENGELE",
    "BETRIx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord NI = {0, 5, 2}, SAA = {0, 8, 3};
static const WcWord H_KUMI = {1, 2, 4}, H_NA = {1, 7, 2}, H_MOJA = {1, 10, 4}, H_MBILI = {2, 1, 5};
static const WcWord NA = {4, 13, 2}, KASORO = {5, 1, 6}, DAKIKA = {5, 9, 6};
static const WcWord ROBO = {6, 1, 4}, NUSU = {6, 6, 4}, M_KUMI = {6, 11, 4};
static const WcWord M_ISHIRINI = {7, 3, 8}, M_NA = {7, 12, 2}, M_TANO = {8, 1, 4};
static const WcWord ASUBUHI = {8, 8, 7}, MCHANA = {9, 1, 6}, JIONI = {9, 10, 5};
static const WcWord USIKU = {10, 1, 5}, ALFAJIRI = {10, 7, 8};
// Swahili hour 0..11 = (clock hour + 6) % 12; 0 = KUMI NA MBILI and 11 = KUMI NA MOJA are set in time_words
static const WcWord HOURS[12] = {{1, 2, 4}, {1, 10, 4}, {2, 1, 5}, {2, 7, 4}, {2, 12, 3}, {3, 1, 4},
                                 {3, 6, 4}, {3, 11, 4}, {4, 1, 4}, {4, 6, 4}, {1, 2, 4}, {1, 2, 4}};
// extra words (easter egg): HAKUNA MATATA ("no worries")
static const WcWord EXTRA[2] = {{12, 2, 6}, {12, 9, 6}};
// row 14: "+ 1 2 3 4  DAKIKA" (digits in columns 3..6, no plural in Swahili)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 9, 6};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void minutes_word(int n5, WcMark &m) {  // n5 = 1..6 (5..30 minutes)
  switch (n5) {
    case 1: m.word(DAKIKA); m.word(M_TANO); break;
    case 2: m.word(DAKIKA); m.word(M_KUMI); break;
    case 3: m.word(ROBO); break;
    case 4: m.word(DAKIKA); m.word(M_ISHIRINI); break;
    case 5: m.word(DAKIKA); m.word(M_ISHIRINI); m.word(M_NA); m.word(M_TANO); break;
    default: m.word(NUSU); break;
  }
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(NI);
  m.word(SAA);
  if (!valid) return;  // no time: only the prefix
  const int m5 = minute / 5;
  int h = hour % 24;
  if (m5 >= 7) h = (h + 1) % 24;  // from "kasoro" on the next hour counts
  const int sw = (h + 6) % 12;      // Swahili time: 7 h = saa moja
  if (sw == 0) { m.word(H_KUMI); m.word(H_NA); m.word(H_MBILI); }       // KUMI NA MBILI (6 / 18 h)
  else if (sw == 11) { m.word(H_KUMI); m.word(H_NA); m.word(H_MOJA); }  // KUMI NA MOJA (5 / 17 h)
  else m.word(HOURS[sw]);
  if (m5 >= 1 && m5 <= 6) { m.word(NA); minutes_word(m5, m); }
  else if (m5 >= 7) { m.word(KASORO); minutes_word(12 - m5, m); }
  // time of day of the hour said
  if (h >= 4 && h <= 5) m.word(ALFAJIRI);
  else if (h >= 6 && h <= 11) m.word(ASUBUHI);
  else if (h >= 12 && h <= 15) m.word(MCHANA);
  else if (h >= 16 && h <= 18) m.word(JIONI);
  else m.word(USIKU);
  const int mm = minute % 5;  // "+ 1..4 DAKIKA"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_WORD);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"sw","dec":".",
"notime_msg":"Saa bado haina muda (hakuna intaneti au NTP).",
"btn_settime":"Chukua muda kutoka simu/kompyuta",
"ap_info":"Hotspot “{ap}” inafanya kazi. Tafadhali weka mtandao wako hapa chini chini ya <b>Wi-Fi</b>.",
"sec_show":"Onyesho","on":"Saa imewashwa","swMin":"Dakika moja moja (+ 1–4 DAKIKA)",
"brD":"Mwangaza mchana","brN":"Mwangaza usiku","cur":"Kikomo cha mkondo (mA)",
"hint_show":"Usiku 0 % = onyesho limezimwa usiku. Chagua kikomo cha mkondo kulingana na chanzo cha umeme (LED 256 tayari zinahitaji takriban mA 256 za mkondo wa kusubiri).",
"sec_col":"Rangi",
"hint_col":"“Nasibu” hubadilika kila saa kamili. “Joto”: baridi buluu iliyokolea, njano, starehe kijani, chungwa, joto jingi nyekundu (kulingana na kipimo chini ya maonyesho ya ziada).",
"g_time":"Muda","g_vent":"HEWA","g_alarm":"KENGELE","g_batt":"BETRI","g_tout":"Joto la nje","g_tin":"Joto la ndani",
"pal_0":"Nyeupe ya joto","pal_1":"Nyeupe","pal_2":"Nyekundu","pal_3":"Chungwa","pal_4":"Njano","pal_5":"Kijani","pal_6":"Buluu","pal_7":"Zambarau",
"c_random":"Nasibu","c_temp":"Joto","c_pride":"Pride","c_custom":"rangi yako",
"sec_fx":"Madoido",
"fx_rainbow":"Upinde wa mvua","fx_aurora":"Aurora","fx_matrix":"Matrix","fx_fire":"Moto","fx_confetti":"Konfeti","fx_stars":"Anga la nyota",
"fx_blink":"Kumulika","fx_blink_own":"Kumulika (rangi yako)","stop":"Simamisha",
"fxd":"Muda wa madoido","blk":"Mzunguko wa kumulika",
"hint_fx":"Muda 0 s = inaendelea hadi “Simamisha”. Madoido huendeshwa daima kwa angalau mwangaza wa 10 %, hata usiku kwa 0 % au saa ikiwa imezimwa.",
"fx_started":"{fx} imeanza","fx_stopped":"Madoido yamesimamishwa",
"txt":"Maandishi","txt_ph":"Andika maandishi","txt_start":"Onyesha maandishi","txt_started":"Maandishi yameanza",
"hint_txt":"Kila herufi hujaza matriki yote. Huonyeshwa kwa muda wa madoido (angalau mara moja), kwa rangi ya saa (nasibu = upinde wa mvua). Herufi za Kilatini, Kigiriki na Kisiriliki, tarakimu, alama za uakifishaji, € na ♥. HTTP: /api/set?text=…",
"sec_sun":"Mchana / usiku","nmode":"Hali ya usiku","nm_mix":"Mchanganyiko","nm_sun":"Mahali pa jua","nm_fixed":"Nyakati maalum",
"lat":"Latitudo","lon":"Longitudo","nso":"Tofauti ya mwanzo wa usiku (dak)","neo":"Tofauti ya mwisho wa usiku (dak)",
"nme":"Usiku si kabla ya","nml":"Usiku si baada ya","nfs":"Usiku kuanzia","nfe":"Usiku hadi",
"sunrise":"Macheo","sunset":"Machweo","night_today":"Usiku wa leo","now":"Sasa",
"nmh_0":"Tofauti: + baada ya, − kabla ya machweo au macheo. Viwianishi k.m. kutoka programu ya ramani (bofya kulia mahali).",
"nmh_1":"Nyakati maalum zinatumika kila siku.",
"nmh_2":"Usiku huanza machweo (pamoja na tofauti), lakini si kabla ya muda uliowekwa, na huisha macheo (pamoja na tofauti), lakini si baada ya muda uliowekwa.",
"day":"Mchana","night":"Usiku",
"sec_extra":"Maonyesho ya ziada","swTemp":"Nukta za joto (kushoto nje, kulia ndani)","tOnl":"Joto la nje kutoka Open-Meteo (mahali)",
"scale_out":"Kipimo cha nje (°C)","scale_in":"Kipimo cha ndani (°C)",
"swLuft":"Onyesha HEWA","swAlarm":"Onyesha KENGELE","swAkku":"Onyesha BETRI","swExtra":"Onyesha HAKUNA MATATA",
"apiTo":"Thamani ni halali kwa (dak, 0 = daima)",
"v_out":"Nje","v_in":"Ndani","v_batt":"Betri","v_la":"Hewa / kengele","on_":"imewashwa","off_":"imezimwa",
"hint_extra":"Ndani, betri, hewa na kengele (na nje, ikiwa bila Open-Meteo) hutoka nje, k.m. kupitia kivinjari, skripti au nyumba janja:",
"sec_api":"Udhibiti wa HTTP",
"hint_api1":"Kutoka mifumo mingine kupitia kivinjari, skripti au nyumba janja (GET au POST kwa <code>/api/set</code>, vigezo kadhaa vinaweza kuunganishwa). Mwangaza, rangi na swichi huhifadhiwa, madoido huendeshwa kwa muda uliowekwa.",
"hint_api2":"Rangi: warmwhite, white, red, orange, yellow, green, blue, violet, random (joto: temp) au rrggbb · Swichi: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Madoido: {fx}, stop · fxcolor: jina la rangi au rrggbb. Kikomo cha mkondo, Wi-Fi na mfumo hapa tu kwenye kiolesura cha wavuti.",
"sec_time":"Muda","ntpD":"Seva ya NTP","ntp_auto":"otomatiki (DHCP)","ntp_manual":"kwa mkono","ntp_server":"Seva",
"ntp_fallback":"Seva ya akiba (ikiwa ruta haitoi, inatumika baada ya kuwasha upya)",
"loc":"Mahali","loc_custom":"mahali pako (viwianishi)","tz_from_loc":"kutoka mahali {city}",
"tz":"Ukanda wa saa","tz_cet":"Ulaya ya Kati (DE, AT, CH …)","tz_wet":"London, Lisbon (WET)","tz_eet":"Ulaya ya Mashariki (Kyiv, Athene, Bucharest)",
"tz_trt":"Uturuki","tz_eat":"Afrika Mashariki (Tanzania, Kenya)","tz_utc":"UTC",
"tz_use":"Marekani Mashariki","tz_usc":"Marekani Kati","tz_usm":"Marekani Milimani","tz_usw":"Marekani Magharibi",
"tz_wib":"Indonesia (Jakarta)","tz_cst":"China","tz_kst":"Korea","tz_jst":"Japani","tz_aus":"Australia Mashariki",
"tz_custom":"yako (POSIX TZ) …","tz_posix":"Ukanda wa saa wa POSIX","ntp_active":"Seva inayotumika",
"ntp_hint":"Otomatiki: seva kutoka ruta (DHCP), vinginevyo iliyowekwa kama akiba. Kubadili kati ya otomatiki na kwa mkono huwasha saa upya.",
"ntp_nodhcp":"NTP kupitia DHCP haipatikani katika kifurushi hiki cha bodi – seva iliyowekwa inatumika.",
"sec_wifi":"Wi-Fi","ssid":"Mtandao (SSID)","scan":"Tafuta mitandao","pass":"Nenosiri","pass_ph":"acha tupu = baki na la sasa",
"host":"Jina la kifaa (http://jina.local)","save_wifi":"Hifadhi & unganisha upya",
"status":"Hali","ip":"IP","last_err":"Hitilafu ya mwisho",
"hint_wifi":"Ikiwa Wi-Fi haipatikani wakati wa kuwasha, saa hufungua hotspot “{ap}” (bila nenosiri, http://192.168.4.1).",
"w_conn":"imeunganishwa na {ssid}","w_ap":"Hotspot inafanya kazi ({ip})","w_none":"haijaunganishwa",
"scanning":"Inatafuta …","scan_none":"Hakuna mitandao iliyopatikana","scan_err":"Utafutaji umeshindwa",
"wr_2":"uthibitishaji umekwisha muda","wr_15":"nenosiri si sahihi?","wr_201":"mtandao haukupatikana","wr_202":"uthibitishaji umekataliwa (nenosiri?)",
"wr_203":"kuunganisha kumeshindwa","wr_204":"nenosiri si sahihi?","wr_205":"muunganisho umeshindwa","wr_8":"imetenganishwa",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi imetenganishwa","net_lost":"hakuna muunganisho na saa",
"sec_sys":"Mfumo","mir":"LED 0 mbele juu kulia (kioo)","srp":"Matrix imeunganishwa kwa zigzag",
"restart":"Washa upya","reset":"Mipangilio ya kiwandani",
"q_restart":"Washa saa upya?","q_reset":"Futa mipangilio yote pamoja na Wi-Fi?",
"language":"Lugha","firmware":"Programu dhibiti","uptime":"Muda wa kufanya kazi","heap":"Kumbukumbu iliyo wazi",
"footer":"{ap} – mwongozo wa kuunda, msimbo na faili za kuchapisha:",
"saved":"Imehifadhiwa","saved_restart":"Imehifadhiwa – saa inawashwa upya …","save_err":"Hitilafu wakati wa kuhifadhi",
"time_set":"Muda umechukuliwa","restarting":"Saa inawashwa upya …",
"srv_no_network":"Hakuna mtandao uliowekwa","srv_back":"Rudi","srv_saved":"Wi-Fi imehifadhiwa",
"srv_connecting":"Saa sasa inaunganisha na","srv_restart":"na inawashwa upya kwa ajili hiyo. Hotspot inatoweka.",
"srv_reach":"Baadaye inapatikana kwenye","srv_reach2":"au kupitia anwani ya IP kutoka ruta au kifuatiliaji cha serial.",
"srv_retry":"Muunganisho ukishindwa, hotspot hurudi baada ya takriban sekunde 30.",
"srv_not_found":"Haikupatikana"
})JSON";
}  // namespace wc_tz
static const WcLangDef WC_LANG = {
    "TZ", "Kiswahili", wc_tz::GRID,
    {14, 1, 4},   // HEWA
    {14, 9, 7},   // KENGELE
    {15, 0, 5},   // BETRI
    {15, 6, 10},  // battery bars
    wc_tz::EXTRA, 2,  // HAKUNA MATATA
    wc_tz::time_words,
    "saamaneno", "SaaManeno",
    -6.1630f, 35.7516f,  // Dodoma
    "EAT-3",             // Africa/Dar_es_Salaam
    "%d/%m/%Y",
    wc_tz::UI_JSON,
};
