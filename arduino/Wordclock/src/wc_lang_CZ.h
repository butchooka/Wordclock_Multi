/*
  wc_lang_CZ.h - Wordclock 16x16, language file CZ (Čeština), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_CZ.scad (check: python3 tools/check_lang.py CZ).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_CZ.txt)
  Satzbau (digitale Form wie die Zeitansage im Radio, 12-Stunden-Zählung):
  JE|JSOU <Stunde> HODINA|HODINY|HODIN [A <Minuten> MINUT].
  Immer die aktuelle Stunde (kein Bezug auf die nächste Stunde), die Minuten werden addiert.
  Einzahl/Mehrzahl hängt an der Stunde: 1 = JE JEDNA HODINA, 2..4 = JSOU DVĚ/TŘI/ČTYŘI HODINY,
  5..12 = JE PĚT ... DVANÁCT HODIN.
  :00 <Stunde>, :05 A PĚT MINUT, :10 A DESET MINUT, :15 A PATNÁCT MINUT, :20 A DVACET MINUT,
  :25 A DVACET PĚT MINUT, :30 A TŘICET MINUT, :35 A TŘICET PĚT MINUT, :40 A ČTYŘICET MINUT,
  :45 A ČTYŘICET PĚT MINUT, :50 A PADESÁT MINUT, :55 A PADESÁT PĚT MINUT
  (nach Zahlen ab 5 steht immer der Genitiv Plural MINUT).
  Beispiele: 1:05 JE JEDNA HODINA A PĚT MINUT, 3:25 JSOU TŘI HODINY A DVACET PĚT MINUT,
  8:45 JE OSM HODIN A ČTYŘICET PĚT MINUT.
  0 und 12 Uhr = JE DVANÁCT HODIN. Keine Wörter für Mitternacht/Mittag.
  HODINA und HODINY teilen sich ein Wort „HODINAY“: HODIN + A (zusammenhängend) bzw. HODIN + Y
  (eine Lücke), HODIN allein für 5..12.
  Ohne gültige Uhrzeit bleibt das Raster dunkel (JE/JSOU hängen von der Stunde ab).
  Minutenzeile: + 1 MINUTA, + 2..4 MINUTY (MINUT + Y, eine Lücke).
  Statuswörter: LÜFTEN = VĚTRAT („lüften“, Infinitiv wie auf Hinweisschildern), ALARM = ALARM,
  AKKU = AKU (gängige Kurzform, z. B. „aku baterie“; BATERIE ist mit 7 Buchstaben zu lang für die
  Zeile mit den 10 Balken).
  Zusatzwörter (Schalter „Zobrazit ČAS LETÍ“): ČAS LETÍ („die Zeit fliegt“).
  Sonderzeichen: Á, Í (Latin-1) sowie Č, Ě, Ř, Š (Latin Extended-A), alle mit Metriken in Wordclock_Model.scad.
  INFO_EN
  Sentence (digital form like the radio time announcement, 12-hour counting):
  JE|JSOU <hour> HODINA|HODINY|HODIN [A <minutes> MINUT].
  Always the current hour (no reference to the next hour), the minutes are added.
  Singular/plural depends on the hour: 1 = JE JEDNA HODINA, 2..4 = JSOU DVĚ/TŘI/ČTYŘI HODINY,
  5..12 = JE PĚT ... DVANÁCT HODIN.
  :00 <hour>, :05 A PĚT MINUT, :10 A DESET MINUT, :15 A PATNÁCT MINUT, :20 A DVACET MINUT,
  :25 A DVACET PĚT MINUT, :30 A TŘICET MINUT, :35 A TŘICET PĚT MINUT, :40 A ČTYŘICET MINUT,
  :45 A ČTYŘICET PĚT MINUT, :50 A PADESÁT MINUT, :55 A PADESÁT PĚT MINUT
  (after numbers from 5 on always genitive plural MINUT).
  Examples: 1:05 JE JEDNA HODINA A PĚT MINUT, 3:25 JSOU TŘI HODINY A DVACET PĚT MINUT,
  8:45 JE OSM HODIN A ČTYŘICET PĚT MINUT.
  0 and 12 o'clock = JE DVANÁCT HODIN. No words for midnight/noon.
  HODINA and HODINY share one word "HODINAY": HODIN + A (contiguous) and HODIN + Y (one gap),
  HODIN alone for 5..12.
  Without a valid time the grid stays dark (JE/JSOU depend on the hour).
  Minute row: + 1 MINUTA, + 2..4 MINUTY (MINUT + Y, one gap).
  Status words: VENTILATE = VĚTRAT ("ventilate", infinitive as on signs), ALARM = ALARM,
  BATTERY = AKU (common short form, e.g. "aku baterie"; BATERIE with 7 letters is too long for the
  row with the 10 bars).
  Extra words (switch "Zobrazit ČAS LETÍ"): ČAS LETÍ ("time flies").
  Special letters: Á, Í (Latin-1) and Č, Ě, Ř, Š (Latin Extended-A), all with metrics in Wordclock_Model.scad.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_cz {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*JExJSOUxxJEDNA*",
    "*DVĚxTŘIxxČTYŘI*",
    "*PĚTxŠESTxxSEDM*",
    "*xOSMxxxxDEVĚTx*",
    "*DESETxJEDENÁCT*",
    "*xxxxDVANÁCTxxx*",
    "*xxHODINAYxxAxx*",
    "*DESETxxPATNÁCT*",
    "*DVACETxxTŘICET*",
    "*xxxČTYŘICETxxx*",
    "*xxPADESÁTxxPĚT*",
    "*xxxxMINUTxxxxx*",
    "*xxČASxxxxLETÍx*",
    "x+x1234xMINUTAYx",
    "VĚTRATxxxxxALARM",
    "xAKUxx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord JE = {0, 1, 2}, JSOU = {0, 4, 4};
// hour 0..11 (0 = DVANÁCT)
static const WcWord HOURS[12] = {{5, 5, 7}, {0, 10, 5}, {1, 1, 3}, {1, 5, 3}, {1, 10, 5}, {2, 1, 3},
                                 {2, 5, 4}, {2, 11, 4}, {3, 2, 3}, {3, 9, 5}, {4, 1, 5}, {4, 7, 8}};
// HODINAY: HODIN + A (1 o'clock) / HODIN + Y (2..4) / HODIN (5..12)
static const WcWord HODIN = {6, 3, 5}, HODIN_A = {6, 8, 1}, HODIN_Y = {6, 9, 1};
static const WcWord A = {6, 12, 1}, MINUT = {11, 5, 5};
// minutes: DESET, DVACET, TŘICET, ČTYŘICET, PADESÁT (10..50) and PĚT
static const WcWord M_TENS[5] = {{7, 1, 5}, {8, 1, 6}, {8, 9, 6}, {9, 4, 8}, {10, 3, 7}};
static const WcWord M_PATNACT = {7, 8, 7}, M_PET = {10, 12, 3};
// extra words (easter egg): ČAS LETÍ ("time flies")
static const WcWord EXTRA[2] = {{12, 3, 3}, {12, 10, 4}};
// row 14: "+ 1 2 3 4  MINUTA / MINUT+Y" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_ONE = {13, 8, 6}, MIN_STEM = {13, 8, 5}, MIN_Y = {13, 14, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  if (!valid) return;  // JE/JSOU depend on the hour: grid stays dark without time
  const int h = hour % 12;             // 0 = DVANÁCT
  const int n = h == 0 ? 12 : h;       // spoken number 1..12
  m.word(n >= 2 && n <= 4 ? JSOU : JE);
  m.word(HOURS[h]);
  m.word(HODIN);
  if (n == 1) m.glue(HODIN_A);         // HODINA
  else if (n <= 4) m.glue(HODIN_Y);    // HODINY
  const int m5 = minute / 5;           // 0..11
  if (m5 > 0) {
    m.word(A);
    if (m5 == 1) m.word(M_PET);                 // PĚT
    else if (m5 == 3) m.word(M_PATNACT);        // PATNÁCT
    else {
      m.word(M_TENS[m5 / 2 - 1]);               // DESET, DVACET, TŘICET, ČTYŘICET, PADESÁT
      if (m5 % 2) m.word(M_PET);                // ... PĚT
    }
    m.word(MINUT);
  }
  const int mm = minute % 5;  // "+ 1 MINUTA", "+ 2..4 MINUTY"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    if (mm == 1) m.word(MIN_ONE);
    else { m.word(MIN_STEM); m.glue(MIN_Y); }
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"cs","dec":",",
"notime_msg":"Hodiny zatím neznají čas (chybí internet nebo NTP).",
"btn_settime":"Převzít čas z telefonu/počítače",
"ap_info":"Hotspot „{ap}“ je aktivní. Zadejte prosím svou síť níže v části <b>Wi-Fi</b>.",
"sec_show":"Zobrazení","on":"Hodiny zapnuty","swMin":"Jednotlivé minuty (+ 1–4 MINUTY)",
"brD":"Jas ve dne","brN":"Jas v noci","cur":"Omezení proudu (mA)",
"hint_show":"Noc 0 % = displej je v noci vypnutý. Omezení proudu zvolte podle zdroje (256 LED odebírá už v klidu cca 256 mA).",
"sec_col":"Barvy",
"hint_col":"„Náhodná“ se mění každou celou hodinu. „Teplota“: zima tmavě modrá, žlutá, komfort zelená, oranžová, horko červená (podle stupnice v části Další zobrazení).",
"g_time":"Čas","g_vent":"VĚTRAT","g_alarm":"ALARM","g_batt":"AKU","g_tout":"Venkovní teplota","g_tin":"Vnitřní teplota",
"pal_0":"Teplá bílá","pal_1":"Bílá","pal_2":"Červená","pal_3":"Oranžová","pal_4":"Žlutá","pal_5":"Zelená","pal_6":"Modrá","pal_7":"Fialová",
"c_random":"Náhodná","c_temp":"Teplota","c_pride":"Pride","c_custom":"vlastní barva",
"sec_fx":"Efekty",
"fx_rainbow":"Duha","fx_aurora":"Polární záře","fx_matrix":"Matrix","fx_fire":"Oheň","fx_confetti":"Konfety","fx_stars":"Hvězdná obloha",
"fx_blink":"Blikání","fx_blink_own":"Blikání (vlastní barva)","stop":"Stop",
"fxd":"Doba trvání efektu","blk":"Cyklus blikání",
"hint_fx":"Doba 0 s = běží až do „Stop“. Efekty běží vždy alespoň s 10 % jasu, i v noci při 0 % nebo při vypnutých hodinách.",
"fx_started":"{fx} spuštěn","fx_stopped":"Efekt zastaven",
"txt":"Běžící text","txt_ph":"Zadej text","txt_start":"Zobrazit text","txt_started":"Text spuštěn",
"hint_txt":"Každé písmeno vyplní celou matici. Běží po dobu efektu (alespoň jednou), v barvě času (náhodná = duha). Latinská, řecká a cyrilská písmena, číslice, interpunkce, € a ♥. HTTP: /api/set?text=…",
"sec_sun":"Den / noc","nmode":"Noční režim","nm_mix":"Smíšený","nm_sun":"Poloha slunce","nm_fixed":"Pevné časy",
"lat":"Zeměpisná šířka","lon":"Zeměpisná délka","nso":"Posun začátku noci (min)","neo":"Posun konce noci (min)",
"nme":"Noc nejdříve","nml":"Noc nejpozději","nfs":"Noc od","nfe":"Noc do",
"sunrise":"Východ slunce","sunset":"Západ slunce","night_today":"Noc dnes","now":"Nyní",
"nmh_0":"Posun: + po, − před západem nebo východem slunce. Souřadnice např. z mapové aplikace (pravým kliknutím na místo).",
"nmh_1":"Pevné časy platí každý den.",
"nmh_2":"Noc začíná při západu slunce (plus posun), ale ne dříve než v nastavený čas, a končí při východu slunce (plus posun), ale ne později než v nastavený čas.",
"day":"Den","night":"Noc",
"sec_extra":"Další zobrazení","swTemp":"Teplotní body (vlevo venku, vpravo uvnitř)","tOnl":"Venkovní teplota z Open-Meteo (poloha)",
"scale_out":"Stupnice venku (°C)","scale_in":"Stupnice uvnitř (°C)",
"swLuft":"Zobrazit VĚTRAT","swAlarm":"Zobrazit ALARM","swAkku":"Zobrazit AKU","swExtra":"Zobrazit ČAS LETÍ",
"apiTo":"Platnost hodnot (min, 0 = stále)",
"v_out":"Venku","v_in":"Uvnitř","v_batt":"Baterie","v_la":"Větrání / alarm","on_":"zap.","off_":"vyp.",
"hint_extra":"Uvnitř, baterie, větrání a alarm (a venku bez Open-Meteo) přicházejí zvenčí, např. přes prohlížeč, skript nebo chytrou domácnost:",
"sec_api":"Ovládání přes HTTP",
"hint_api1":"Z jiných systémů přes prohlížeč, skript nebo chytrou domácnost (GET nebo POST na <code>/api/set</code>, lze kombinovat více parametrů). Jas, barvy a přepínače se uloží, efekty běží po nastavenou dobu.",
"hint_api2":"Barvy: warmwhite, white, red, orange, yellow, green, blue, violet, random (teplota: temp) nebo rrggbb · Přepínače: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Efekty: {fx}, stop · fxcolor: název barvy nebo rrggbb. Omezení proudu, Wi-Fi a systém jen zde ve webovém rozhraní.",
"sec_time":"Čas","ntpD":"Server NTP","ntp_auto":"automaticky (DHCP)","ntp_manual":"ručně","ntp_server":"Server",
"ntp_fallback":"Záložní server (pokud ho router neposkytuje, platí po restartu)",
"loc":"Poloha","loc_custom":"vlastní poloha (souřadnice)","tz_from_loc":"podle polohy {city}",
"tz":"Časové pásmo","tz_cet":"Střední Evropa (CZ, DE, AT, CH …)","tz_wet":"Londýn, Lisabon (WET)","tz_eet":"Východní Evropa (Kyjev, Atény, Bukurešť)",
"tz_trt":"Turecko","tz_eat":"Východní Afrika (Tanzanie, Keňa)","tz_utc":"UTC",
"tz_use":"USA východ","tz_usc":"USA střed","tz_usm":"USA hory","tz_usw":"USA západ",
"tz_wib":"Indonésie (Jakarta)","tz_cst":"Čína","tz_kst":"Korea","tz_jst":"Japonsko","tz_aus":"Austrálie východ",
"tz_custom":"vlastní (POSIX TZ) …","tz_posix":"Časové pásmo POSIX","ntp_active":"Aktivní server",
"ntp_hint":"Automaticky: server z routeru (DHCP), jinak zadaný jako záložní. Přepnutí mezi automaticky a ručně hodiny restartuje.",
"ntp_nodhcp":"NTP přes DHCP není v tomto balíčku desky k dispozici – použije se zadaný server.",
"sec_wifi":"Wi-Fi","ssid":"Síť (SSID)","scan":"Hledat sítě","pass":"Heslo","pass_ph":"prázdné = ponechat stávající",
"host":"Název zařízení (http://nazev.local)","save_wifi":"Uložit a znovu připojit",
"status":"Stav","ip":"IP","last_err":"Poslední chyba",
"hint_wifi":"Pokud se při spuštění Wi-Fi nenajde, hodiny otevřou hotspot „{ap}“ (bez hesla, http://192.168.4.1).",
"w_conn":"připojeno k {ssid}","w_ap":"Hotspot aktivní ({ip})","w_none":"nepřipojeno",
"scanning":"Hledám …","scan_none":"Nenalezeny žádné sítě","scan_err":"Hledání selhalo",
"wr_2":"platnost ověření vypršela","wr_15":"chybné heslo?","wr_201":"síť nenalezena","wr_202":"ověření odmítnuto (heslo?)",
"wr_203":"přidružení selhalo","wr_204":"chybné heslo?","wr_205":"připojení selhalo","wr_8":"odpojeno",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi odpojeno","net_lost":"žádné spojení s hodinami",
"sec_sys":"Systém","mir":"LED 0 zepředu vpravo nahoře (zrcadlení)","srp":"Matice zapojená cik-cak",
"restart":"Restartovat","reset":"Tovární nastavení",
"q_restart":"Restartovat hodiny?","q_reset":"Smazat všechna nastavení včetně Wi-Fi?",
"language":"Jazyk","firmware":"Firmware","uptime":"Doba běhu","heap":"Volná paměť",
"footer":"{ap} – návod ke stavbě, kód a soubory k tisku:",
"saved":"Uloženo","saved_restart":"Uloženo – hodiny se restartují …","save_err":"Chyba při ukládání",
"time_set":"Čas převzat","restarting":"Hodiny se restartují …",
"srv_no_network":"Nebyla zadána síť","srv_back":"Zpět","srv_saved":"Wi-Fi uloženo",
"srv_connecting":"Hodiny se nyní připojují k síti","srv_restart":"a kvůli tomu se restartují. Hotspot zmizí.",
"srv_reach":"Poté dostupné na","srv_reach2":"nebo přes IP adresu z routeru či sériového monitoru.",
"srv_retry":"Pokud se připojení nezdaří, hotspot se znovu objeví asi po 30 sekundách.",
"srv_not_found":"Nenalezeno"
})JSON";
}  // namespace wc_cz
static const WcLangDef WC_LANG = {
    "CZ", "Čeština", wc_cz::GRID,
    {14, 0, 6},   // VĚTRAT
    {14, 11, 5},  // ALARM
    {15, 1, 3},   // AKU
    {15, 6, 10},  // battery bars
    wc_cz::EXTRA, 2,  // ČAS LETÍ
    wc_cz::time_words,
    "slovnihodiny", "SlovniHodiny",
    50.0755f, 14.4378f,  // Praha
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Prague
    "%d.%m.%Y",
    wc_cz::UI_JSON,
};
