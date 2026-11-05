/*
  wc_lang_HU.h - Wordclock 16x16, language file HU (Magyar), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_HU.scad (check: python3 tools/check_lang.py HU).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_HU.txt)
  Satzbau (gängige Umgangsform, 12-Stunden-Zählung, Viertel auf die nächste Stunde bezogen):
  MOST [<Minuten> PERCCEL MÚLT | <Minuten> PERC MÚLVA] [NEGYED | FÉL | HÁROMNEGYED] <Stunde> [ÓRA] VAN
  („most … van“ = „jetzt ist es …“; PERCCEL MÚLT = „Minuten nach“, PERC MÚLVA = „in … Minuten“).
  Ab :15 (NEGYED = „Viertel“) bezieht sich die Uhrzeit auf die nächste Stunde (wie „viertel vier“).
  ÓRA („Uhr“) steht nur bei vollen Stunden und vor/nach der vollen Stunde (:00, :05, :10, :50, :55).
  :00 <Stunde> ÓRA, :05 ÖT PERCCEL MÚLT <Stunde> ÓRA, :10 TÍZ PERCCEL MÚLT <Stunde> ÓRA,
  :15 NEGYED <nächste Stunde>, :20 ÖT PERCCEL MÚLT NEGYED, :25 ÖT PERC MÚLVA FÉL, :30 FÉL,
  :35 ÖT PERCCEL MÚLT FÉL, :40 ÖT PERC MÚLVA HÁROMNEGYED, :45 HÁROMNEGYED,
  :50 TÍZ PERC MÚLVA <nächste Stunde> ÓRA, :55 ÖT PERC MÚLVA <nächste Stunde> ÓRA
  Beispiele: 3:05 MOST ÖT PERCCEL MÚLT HÁROM ÓRA VAN, 3:30 MOST FÉL NÉGY VAN,
  3:45 MOST HÁROMNEGYED NÉGY VAN, 3:55 MOST ÖT PERC MÚLVA NÉGY ÓRA VAN.
  Stunden: EGY, KETTŐ, HÁROM, NÉGY, ÖT, HAT, HÉT, NYOLC, KILENC, TÍZ, TIZENEGY, TIZENKETTŐ
  (Stunde 2 und 12 immer als KETTŐ / TIZENKETTŐ: „fél kettő“ ist richtig, vor ÓRA ist „kettő óra“ umgangssprachlich
  üblich, standardsprachlich wäre „két óra“; das Raster hat nur KETTŐ).
  Im Raster stecken EGY in TIZENEGY, KETTŐ in TIZENKETTŐ, NEGYED in HÁROMNEGYED und PERC in PERCCEL.
  ÖT und TÍZ gibt es je zweimal (Minuten und Stunde).
  0 und 12 Uhr = TIZENKETTŐ. Keine Wörter für Mitternacht/Mittag (ÉJFÉL/DÉL).
  Ohne gültige Uhrzeit leuchtet nur MOST.
  Minutenzeile: + 1..4 PERC (im Ungarischen steht nach Zahlen immer die Einzahl).
  Statuswörter: LÜFTEN = SZELLŐZÉS („Lüftung“), ALARM = RIADÓ („Alarm“), AKKU = AKKU (ungarisch üblich).
  Zusatzwörter (Schalter „AZ IDŐ PÉNZ mutatása“): AZ IDŐ PÉNZ („Zeit ist Geld“).
  Sonderzeichen: Á, É, Í, Ó, Ö, Ú (Latin-1) und Ő (O mit Doppelakut, nicht Latin-1; Metriken in
  Wordclock_Model.scad vorhanden). Ű kommt im Raster nicht vor.
  INFO_EN
  Sentence (common spoken form, 12-hour counting, quarters refer to the next hour):
  MOST [<minutes> PERCCEL MÚLT | <minutes> PERC MÚLVA] [NEGYED | FÉL | HÁROMNEGYED] <hour> [ÓRA] VAN
  ("most ... van" = "now it is ..."; PERCCEL MÚLT = "minutes past", PERC MÚLVA = "in ... minutes").
  From :15 on (NEGYED = "quarter") the time refers to the next hour (like German "viertel vier").
  ÓRA ("o'clock") is only used at the full hour and right before/after it (:00, :05, :10, :50, :55).
  :00 <hour> ÓRA, :05 ÖT PERCCEL MÚLT <hour> ÓRA, :10 TÍZ PERCCEL MÚLT <hour> ÓRA,
  :15 NEGYED <next hour>, :20 ÖT PERCCEL MÚLT NEGYED, :25 ÖT PERC MÚLVA FÉL, :30 FÉL,
  :35 ÖT PERCCEL MÚLT FÉL, :40 ÖT PERC MÚLVA HÁROMNEGYED, :45 HÁROMNEGYED,
  :50 TÍZ PERC MÚLVA <next hour> ÓRA, :55 ÖT PERC MÚLVA <next hour> ÓRA
  Examples: 3:05 MOST ÖT PERCCEL MÚLT HÁROM ÓRA VAN, 3:30 MOST FÉL NÉGY VAN,
  3:45 MOST HÁROMNEGYED NÉGY VAN, 3:55 MOST ÖT PERC MÚLVA NÉGY ÓRA VAN.
  Hours: EGY, KETTŐ, HÁROM, NÉGY, ÖT, HAT, HÉT, NYOLC, KILENC, TÍZ, TIZENEGY, TIZENKETTŐ
  (hour 2 and 12 always as KETTŐ / TIZENKETTŐ: "fél kettő" is correct, before ÓRA "kettő óra" is common speech,
  standard language would be "két óra"; the grid only has KETTŐ).
  In the grid EGY is part of TIZENEGY, KETTŐ of TIZENKETTŐ, NEGYED of HÁROMNEGYED and PERC of PERCCEL.
  ÖT and TÍZ exist twice (minutes and hour).
  0 and 12 o'clock = TIZENKETTŐ. No words for midnight/noon (ÉJFÉL/DÉL).
  Without a valid time only MOST is lit.
  Minute row: + 1..4 PERC (Hungarian always uses the singular after numbers).
  Status words: VENTILATE = SZELLŐZÉS ("ventilation"), ALARM = RIADÓ ("alarm"), BATTERY = AKKU (common in Hungarian).
  Extra words (switch "AZ IDŐ PÉNZ mutatása"): AZ IDŐ PÉNZ ("time is money").
  Special letters: Á, É, Í, Ó, Ö, Ú (Latin-1) and Ő (O with double acute, not Latin-1; metrics are in
  Wordclock_Model.scad). Ű does not occur in the grid.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_hu {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*MOSTxxxÖTxxTÍZ*",
    "*PERCCELxxxMÚLT*",
    "*xxMÚLVAxxxFÉLx*",
    "*xxHÁROMNEGYEDx*",
    "*xxTIZENKETTŐxx*",
    "*xxxTIZENEGYxxx*",
    "*HÁROMxxxxxNÉGY*",
    "*xÖTxxHATxxHÉTx*",
    "*NYOLCxxxKILENC*",
    "*xxxxxxTÍZxxxxx*",
    "*xxÓRAxxxxxVANx*",
    "*xxxxxxxxxxxxxx*",
    "*xAZxIDŐxPÉNZxx*",
    "x+x1234xxPERCxxx",
    "SZELLŐZÉSxxRIADÓ",
    "xAKKUx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord MOST = {0, 1, 4}, VAN = {10, 11, 3}, ORA = {10, 3, 3};
static const WcWord M_OT = {0, 8, 2}, M_TIZ = {0, 12, 3};
static const WcWord PERC = {1, 1, 4}, PERCCEL = {1, 1, 7}, MULT = {1, 11, 4}, MULVA = {2, 3, 5};
static const WcWord FEL = {2, 11, 3}, HAROMNEGYED = {3, 3, 11}, NEGYED = {3, 8, 6};
// hour 0..11 (0 = TIZENKETTŐ; EGY inside TIZENEGY, KETTŐ inside TIZENKETTŐ)
static const WcWord HOURS[12] = {{4, 3, 10}, {5, 9, 3}, {4, 8, 5}, {6, 1, 5},  {6, 11, 4}, {7, 2, 2},
                                 {7, 6, 3},  {7, 11, 3}, {8, 1, 5}, {8, 9, 6}, {9, 7, 3},  {5, 4, 8}};
// extra words (easter egg): AZ IDŐ PÉNZ ("time is money")
static const WcWord EXTRA[3] = {{12, 2, 2}, {12, 5, 3}, {12, 9, 4}};
// row 14: "+ 1 2 3 4  PERC" (digits in columns 3..6, always singular)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 9, 4};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(MOST);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 3) h = (h + 1) % 12;  // from "negyed" (:15) on the next hour counts
  switch (m5) {
    case 0: break;
    case 1: m.word(M_OT); m.word(PERCCEL); m.word(MULT); break;
    case 2: m.word(M_TIZ); m.word(PERCCEL); m.word(MULT); break;
    case 3: m.word(NEGYED); break;
    case 4: m.word(M_OT); m.word(PERCCEL); m.word(MULT); m.word(NEGYED); break;
    case 5: m.word(M_OT); m.word(PERC); m.word(MULVA); m.word(FEL); break;
    case 6: m.word(FEL); break;
    case 7: m.word(M_OT); m.word(PERCCEL); m.word(MULT); m.word(FEL); break;
    case 8: m.word(M_OT); m.word(PERC); m.word(MULVA); m.word(HAROMNEGYED); break;
    case 9: m.word(HAROMNEGYED); break;
    case 10: m.word(M_TIZ); m.word(PERC); m.word(MULVA); break;
    default: m.word(M_OT); m.word(PERC); m.word(MULVA); break;
  }
  m.word(HOURS[h]);
  if (m5 <= 2 || m5 >= 10) m.word(ORA);  // "három óra", "öt perc múlva négy óra"
  m.word(VAN);
  const int mm = minute % 5;  // "+ 1..4 PERC"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_WORD);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"hu","dec":",",
"notime_msg":"Az óra még nem ismeri a pontos időt (nincs internet vagy NTP).",
"btn_settime":"Idő átvétele a telefonról/PC-ről",
"ap_info":"A(z) „{ap}” hotspot aktív. Adja meg lent a hálózatát a <b>Wi-Fi</b> résznél.",
"sec_show":"Kijelzés","on":"Óra bekapcsolva","swMin":"Egyes percek (+ 1–4 PERC)",
"brD":"Fényerő nappal","brN":"Fényerő éjjel","cur":"Áramkorlát (mA)",
"hint_show":"Éjjel 0 % = a kijelző éjjel kikapcsol. Az áramkorlátot a tápegységhez igazítsa (256 LED már nyugalmi állapotban is kb. 256 mA-t fogyaszt).",
"sec_col":"Színek",
"hint_col":"A „Véletlen” minden egész órakor változik. „Hőmérséklet”: hideg sötétkék, sárga, kellemes zöld, narancs, meleg piros (a további kijelzések skálája szerint).",
"g_time":"Idő","g_vent":"SZELLŐZÉS","g_alarm":"RIADÓ","g_batt":"AKKU","g_tout":"Külső hőmérséklet","g_tin":"Belső hőmérséklet",
"pal_0":"Meleg fehér","pal_1":"Fehér","pal_2":"Piros","pal_3":"Narancs","pal_4":"Sárga","pal_5":"Zöld","pal_6":"Kék","pal_7":"Lila",
"c_random":"Véletlen","c_temp":"Hőmérséklet","c_pride":"Pride","c_custom":"saját szín",
"sec_fx":"Effektek",
"fx_rainbow":"Szivárvány","fx_aurora":"Sarki fény","fx_matrix":"Matrix","fx_fire":"Tűz","fx_confetti":"Konfetti","fx_stars":"Csillagos ég",
"fx_blink":"Villogás","fx_blink_own":"Villogás (saját szín)","stop":"Stop",
"fxd":"Effekt időtartama","blk":"Villogási ciklus",
"hint_fx":"0 s időtartam = a „Stop”-ig fut. Az effektek mindig legalább 10 % fényerővel futnak, éjjel 0 %-nál vagy kikapcsolt óránál is.",
"fx_started":"{fx} elindítva","fx_stopped":"Effekt leállítva",
"txt":"Futószöveg","txt_ph":"Szöveg megadása","txt_start":"Szöveg indítása","txt_started":"Szöveg elindítva",
"hint_txt":"Minden betű kitölti az egész mátrixot. Az effekt időtartamáig fut (legalább egyszer), az idő színében (véletlen = szivárvány). Latin, görög és cirill betűk, számjegyek, írásjelek, € és ♥. HTTP: /api/set?text=…",
"sec_sun":"Nappal / éjjel","nmode":"Éjszakai mód","nm_mix":"Vegyes","nm_sun":"Napállás","nm_fixed":"Fix időpontok",
"lat":"Szélesség","lon":"Hosszúság","nso":"Éjszaka kezdetének eltolása (perc)","neo":"Éjszaka végének eltolása (perc)",
"nme":"Éjszaka legkorábban","nml":"Éjszaka legkésőbb","nfs":"Éjszaka ettől","nfe":"Éjszaka eddig",
"sunrise":"Napkelte","sunset":"Napnyugta","night_today":"Ma éjjel","now":"Most",
"nmh_0":"Eltolás: + után, − előtt a napnyugtához vagy napkeltéhez képest. Koordináták pl. egy térképalkalmazásból (jobb klikk a helyre).",
"nmh_1":"A fix időpontok minden nap érvényesek.",
"nmh_2":"Az éjszaka napnyugtakor kezdődik (plusz eltolás), de nem a megadott idő előtt, és napkeltekor ér véget (plusz eltolás), de nem a megadott idő után.",
"day":"Nappal","night":"Éjjel",
"sec_extra":"További kijelzések","tOnl":"Külső hőmérséklet az Open-Meteótól (helyszín)",
"scale_out":"Külső skála (°C)","scale_in":"Belső skála (°C)",
"swExtra":"AZ IDŐ PÉNZ mutatása",
"apiTo":"Az értékek érvényesek (perc, 0 = mindig)",
"v_out":"Kint","v_in":"Bent","v_batt":"Akku","v_la":"Szellőzés / riadó","on_":"be","off_":"ki",
"hint_extra":"A belső hőmérséklet, az akku, a szellőzés és a riadó (és a külső, ha nincs Open-Meteo) kívülről érkezik, pl. böngészőből, szkriptből vagy okosotthonból:",
"sec_api":"HTTP-vezérlés",
"hint_api1":"Más rendszerekből böngészővel, szkripttel vagy okosotthonnal (GET vagy POST a <code>/api/set</code> címre, több paraméter kombinálható). A fényerő, a színek és a kapcsolók mentésre kerülnek, az effektek a beállított ideig futnak.",
"hint_api2":"Színek: warmwhite, white, red, orange, yellow, green, blue, violet, random (hőmérséklet: temp) vagy rrggbb · Kapcsolók: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effektek: {fx}, stop · fxcolor: színnév vagy rrggbb. Áramkorlát, Wi-Fi és rendszer csak itt, a webes felületen.",
"sec_time":"Idő","ntpD":"NTP-szerver","ntp_auto":"automatikus (DHCP)","ntp_manual":"kézi","ntp_server":"Szerver",
"ntp_fallback":"Tartalék szerver (ha a router nem ad meg egyet, újraindítás után érvényes)",
"loc":"Helyszín","loc_custom":"saját helyszín (koordináták)","tz_from_loc":"a helyszínből: {city}",
"tz":"Időzóna","tz_cet":"Közép-Európa (DE, AT, HU …)","tz_wet":"London, Lisszabon (WET)","tz_eet":"Kelet-Európa (Kijev, Athén, Bukarest)",
"tz_trt":"Törökország","tz_eat":"Kelet-Afrika (Tanzánia, Kenya)","tz_utc":"UTC",
"tz_use":"USA kelet","tz_usc":"USA közép","tz_usm":"USA hegyvidék","tz_usw":"USA nyugat",
"tz_wib":"Indonézia (Jakarta)","tz_cst":"Kína","tz_kst":"Korea","tz_jst":"Japán","tz_aus":"Kelet-Ausztrália",
"tz_custom":"saját (POSIX TZ) …","tz_posix":"POSIX időzóna","ntp_active":"Aktív szerver",
"ntp_hint":"Automatikus: a router szervere (DHCP), egyébként a tartalékként megadott. Az automatikus és a kézi mód közti váltás újraindítja az órát.",
"ntp_nodhcp":"Az NTP DHCP-n keresztül ebben az alaplapcsomagban nem érhető el – a megadott szerver kerül használatra.",
"sec_wifi":"Wi-Fi","ssid":"Hálózat (SSID)","scan":"Hálózatok keresése","pass":"Jelszó","pass_ph":"üres = a jelenlegi jelszó marad",
"host":"Eszköznév (http://nev.local)","save_wifi":"Mentés és újracsatlakozás",
"status":"Állapot","ip":"IP","last_err":"Utolsó hiba",
"hint_wifi":"Ha induláskor nem található a Wi-Fi, az óra megnyitja a(z) „{ap}” hotspotot (jelszó nélkül, http://192.168.4.1).",
"w_conn":"csatlakozva: {ssid}","w_ap":"Hotspot aktív ({ip})","w_none":"nincs csatlakozva",
"scanning":"Keresés …","scan_none":"Nem található hálózat","scan_err":"A keresés sikertelen",
"wr_2":"a hitelesítés időtúllépés miatt megszakadt","wr_15":"hibás jelszó?","wr_201":"a hálózat nem található","wr_202":"hitelesítés elutasítva (jelszó?)",
"wr_203":"a társítás sikertelen","wr_204":"hibás jelszó?","wr_205":"a kapcsolódás sikertelen","wr_8":"leválasztva",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi leválasztva","net_lost":"nincs kapcsolat az órával",
"sec_sys":"Rendszer","mir":"0. LED elölről nézve jobbra fent (tükrözött)","srp":"Mátrix cikcakkban bekötve",
"restart":"Újraindítás","reset":"Gyári visszaállítás",
"q_restart":"Újraindítja az órát?","q_reset":"Törli az összes beállítást, a Wi-Fit is?",
"language":"Nyelv","firmware":"Firmware","uptime":"Üzemidő","heap":"Szabad memória",
"footer":"{ap} – építési útmutató, kód és nyomtatási fájlok:",
"saved":"Mentve","saved_restart":"Mentve – az óra újraindul …","save_err":"Hiba mentéskor",
"time_set":"Idő átvéve","restarting":"Az óra újraindul …",
"srv_no_network":"Nincs megadva hálózat","srv_back":"Vissza","srv_saved":"Wi-Fi mentve",
"srv_connecting":"Az óra most csatlakozik ehhez:","srv_restart":"és ehhez újraindul. A hotspot eltűnik.",
"srv_reach":"Ezután elérhető itt:","srv_reach2":"vagy a routerben, ill. a soros monitoron látható IP-címen.",
"srv_retry":"Ha a kapcsolódás nem sikerül, kb. 30 másodperc múlva újra megjelenik a hotspot.",
"srv_not_found":"Nem található"
})JSON";
}  // namespace wc_hu
static const WcLangDef WC_LANG = {
    "HU", "Magyar", wc_hu::GRID,
    {14, 0, 9},   // SZELLŐZÉS
    {14, 11, 5},  // RIADÓ
    {15, 1, 4},   // AKKU
    {15, 6, 10},  // battery bars
    wc_hu::EXTRA, 3,  // AZ IDŐ PÉNZ
    wc_hu::time_words,
    "szoora", "SzoOra",
    47.4979f, 19.0402f,            // Budapest
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Budapest
    "%Y.%m.%d.",
    wc_hu::UI_JSON,
};
