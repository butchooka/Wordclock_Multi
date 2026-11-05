/*
  wc_lang_IT.h - Wordclock 16x16, language file IT (Italiano), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_IT.scad (check: python3 tools/check_lang.py IT).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_IT.txt)
  Satzbau: SONO LE <Stunde> [E|MENO <Minuten>]
  Ab :35 (MENO) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 (nichts), :05 E CINQUE, :10 E DIECI, :15 E UN QUARTO, :20 E VENTI, :25 E VENTICINQUE,
  :30 E MEZZA, :35 MENO VENTICINQUE, :40 MENO VENTI, :45 MENO UN QUARTO, :50 MENO DIECI,
  :55 MENO CINQUE
  1 Uhr: È L'UNA (Einzahl), 12 Uhr: È MEZZOGIORNO, 0 Uhr: È MEZZANOTTE.
  Volle Stunde ohne Zusatzwort.
  Minutenzeile: + 1 MINUTO (Einzahl), + 2..4 MINUTI (im Raster „MINUTIO“: Mehrzahl MINUTI,
  Einzahl MINUT + O).
  Zusatzwörter (Schalter „Mostra CIAO“): CIAO („Hallo“, Gruß).
  INFO_EN
  Sentence: SONO LE <hour> [E|MENO <minutes>]
  From :35 (MENO) on the time refers to the next hour.
  :00 (nothing), :05 E CINQUE, :10 E DIECI, :15 E UN QUARTO, :20 E VENTI, :25 E VENTICINQUE,
  :30 E MEZZA, :35 MENO VENTICINQUE, :40 MENO VENTI, :45 MENO UN QUARTO, :50 MENO DIECI,
  :55 MENO CINQUE
  1 o'clock: È L'UNA (singular), 12 o'clock: È MEZZOGIORNO, 0 o'clock: È MEZZANOTTE.
  Full hour without extra word.
  Minute row: + 1 MINUTO (singular), + 2..4 MINUTI (grid "MINUTIO": plural MINUTI,
  singular MINUT + O).
  Extra words (switch "Mostra CIAO"): CIAO ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_it {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*SONOxLExÈxCIAO*",
    "*L'UNAxDUExxxxx*",
    "*xTRExQUATTROxx*",
    "*CINQUExxSEIxxx*",
    "*xSETTExxxOTTOx*",
    "*NOVExxDIECIxxx*",
    "*xxxUNDICIxxxxx*",
    "*xMEZZOGIORNOxx*",
    "*xxMEZZANOTTExx*",
    "*xxExxxxMENOxxx*",
    "*xVENTICINQUExx*",
    "*xUNxxQUARTOxxx*",
    "*DIECIxxxMEZZAx*",
    "x+x1234xMINUTIOx",
    "xAERARExALLARMEx",
    "xBATTx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord SONO = {0, 1, 4}, LE = {0, 6, 2}, E_IS = {0, 9, 1};  // E_IS = È
static const WcWord MEZZOGIORNO = {7, 2, 11}, MEZZANOTTE = {8, 3, 10};
static const WcWord E_AND = {9, 3, 1}, MENO = {9, 8, 4};
static const WcWord M_CINQUE = {10, 7, 6}, M_DIECI = {12, 1, 5}, M_UN = {11, 2, 2}, M_QUARTO = {11, 6, 6};
static const WcWord M_VENTI = {10, 2, 5}, M_VENTICINQUE = {10, 2, 11}, M_MEZZA = {12, 9, 5};
// hour 1..11 (index 0 = MEZZOGIORNO, only a placeholder: 12 o'clock is MEZZOGIORNO/MEZZANOTTE, chosen in time_words)
static const WcWord HOURS[12] = {{7, 2, 11}, {1, 1, 5}, {1, 7, 3}, {2, 2, 3},  {2, 6, 7},  {3, 1, 6},
                                 {3, 9, 3},  {4, 2, 5}, {4, 10, 4}, {5, 1, 4}, {5, 7, 5},  {6, 4, 6}};
// extra words (easter egg): CIAO ("hello", greeting)
static const WcWord EXTRA[1] = {{0, 11, 4}};
// row 14: "+ 1 2 3 4  MINUTI/MINUTO" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 6};          // MINUTI
static const WcWord MIN_STEM = {13, 8, 5}, MIN_O = {13, 14, 1};            // MINUT + O = MINUTO
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  const int m5 = minute / 5;
  int h = hour % 24;
  if (m5 >= 7) h = (h + 1) % 24;  // from "meno venticinque" on the next hour counts
  if (!valid) {                   // no time: only the prefix
    m.word(SONO);
    m.word(LE);
    return;
  }
  if (h == 12) { m.word(E_IS); m.word(MEZZOGIORNO); }
  else if (h == 0) { m.word(E_IS); m.word(MEZZANOTTE); }
  else if (h % 12 == 1) { m.word(E_IS); m.word(HOURS[1]); }  // È L'UNA
  else { m.word(SONO); m.word(LE); m.word(HOURS[h % 12]); }  // SONO LE DUE ...
  switch (m5) {
    case 0: break;
    case 1: m.word(E_AND); m.word(M_CINQUE); break;
    case 2: m.word(E_AND); m.word(M_DIECI); break;
    case 3: m.word(E_AND); m.word(M_UN); m.word(M_QUARTO); break;
    case 4: m.word(E_AND); m.word(M_VENTI); break;
    case 5: m.word(E_AND); m.word(M_VENTICINQUE); break;
    case 6: m.word(E_AND); m.word(M_MEZZA); break;
    case 7: m.word(MENO); m.word(M_VENTICINQUE); break;
    case 8: m.word(MENO); m.word(M_VENTI); break;
    case 9: m.word(MENO); m.word(M_UN); m.word(M_QUARTO); break;
    case 10: m.word(MENO); m.word(M_DIECI); break;
    default: m.word(MENO); m.word(M_CINQUE); break;
  }
  const int mm = minute % 5;  // "+ 1 MINUTO" or "+ 2..4 MINUTI"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    if (mm == 1) { m.word(MIN_STEM); m.glue(MIN_O); }  // singular: MINUT + O, text "MINUTO"
    else m.word(MIN_WORD);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"it","dec":",",
"notime_msg":"L’orologio non ha ancora l’ora (niente Internet o NTP).",
"btn_settime":"Prendi l’ora dal telefono/PC",
"ap_info":"Hotspot «{ap}» attivo. Inserisci la tua rete qui sotto in <b>Wi-Fi</b>.",
"sec_show":"Visualizzazione","on":"Orologio acceso","swMin":"Minuti singoli (+ 1–4 MINUTI)",
"brD":"Luminosità giorno","brN":"Luminosità notte","cur":"Limite di corrente (mA)",
"hint_show":"Notte 0 % = display spento di notte. Scegli il limite di corrente in base all’alimentatore (256 LED assorbono già circa 256 mA a riposo).",
"sec_col":"Colori",
"hint_col":"«Casuale» cambia a ogni ora piena. «Temperatura»: freddo blu scuro, giallo, comfort verde, arancione, caldo rosso (secondo la scala in visualizzazioni aggiuntive).",
"g_time":"Ora","g_vent":"AERARE","g_alarm":"ALLARME","g_batt":"BATT","g_tout":"Temperatura esterna","g_tin":"Temperatura interna",
"pal_0":"Bianco caldo","pal_1":"Bianco","pal_2":"Rosso","pal_3":"Arancione","pal_4":"Giallo","pal_5":"Verde","pal_6":"Blu","pal_7":"Viola",
"c_random":"Casuale","c_temp":"Temperatura","c_pride":"Pride","c_custom":"colore personalizzato",
"sec_fx":"Effetti",
"fx_rainbow":"Arcobaleno","fx_aurora":"Aurora","fx_matrix":"Matrix","fx_fire":"Fuoco","fx_confetti":"Coriandoli","fx_stars":"Cielo stellato",
"fx_blink":"Lampeggio","fx_blink_own":"Lampeggio (colore pers.)","stop":"Stop",
"fxd":"Durata effetto","blk":"Ciclo di lampeggio",
"hint_fx":"Durata 0 s = continua fino a «Stop». Gli effetti girano sempre con almeno il 10 % di luminosità, anche di notte con 0 % o con l’orologio spento.",
"fx_started":"{fx} avviato","fx_stopped":"Effetto fermato",
"txt":"Testo scorrevole","txt_ph":"Inserisci un testo","txt_start":"Mostra testo","txt_started":"Testo avviato",
"hint_txt":"Ogni lettera riempie tutta la matrice. Dura quanto l’effetto (almeno una volta), nel colore dell’ora (casuale = arcobaleno). Lettere latine, greche e cirilliche, cifre, punteggiatura, € e ♥. HTTP: /api/set?text=…",
"sec_sun":"Giorno / notte","nmode":"Modalità notte","nm_mix":"Mista","nm_sun":"Posizione del sole","nm_fixed":"Orari fissi",
"lat":"Latitudine","lon":"Longitudine","nso":"Scostamento inizio notte (min)","neo":"Scostamento fine notte (min)",
"nme":"Notte non prima delle","nml":"Notte non dopo le","nfs":"Notte dalle","nfe":"Notte fino alle",
"sunrise":"Alba","sunset":"Tramonto","night_today":"Notte oggi","now":"Adesso",
"nmh_0":"Scostamento: + dopo, − prima del tramonto o dell’alba. Coordinate p. es. da un’app di mappe (clic destro sul luogo).",
"nmh_1":"Gli orari fissi valgono ogni giorno.",
"nmh_2":"La notte inizia al tramonto (più scostamento), ma non prima dell’orario impostato, e finisce all’alba (più scostamento), ma non dopo l’orario impostato.",
"day":"Giorno","night":"Notte",
"sec_extra":"Visualizzazioni aggiuntive","tOnl":"Temperatura esterna da Open-Meteo (luogo)",
"scale_out":"Scala esterna (°C)","scale_in":"Scala interna (°C)",
"swExtra":"Mostra CIAO",
"apiTo":"Valori validi per (min, 0 = sempre)",
"v_out":"Esterno","v_in":"Interno","v_batt":"Batteria","v_la":"Aerare / allarme","on_":"acceso","off_":"spento",
"hint_extra":"Interno, batteria, aerare e allarme (ed esterno, se senza Open-Meteo) arrivano dall’esterno, p. es. via browser, script o casa intelligente:",
"sec_api":"Controllo HTTP",
"hint_api1":"Da altri sistemi via browser, script o casa intelligente (GET o POST a <code>/api/set</code>, più parametri combinabili). Luminosità, colori e interruttori vengono salvati, gli effetti girano per la durata impostata.",
"hint_api2":"Colori: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatura: temp) o rrggbb · Interruttori: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effetti: {fx}, stop · fxcolor: nome del colore o rrggbb. Limite di corrente, Wi-Fi e sistema solo qui nell’interfaccia web.",
"sec_time":"Ora","ntpD":"Server NTP","ntp_auto":"automatico (DHCP)","ntp_manual":"manuale","ntp_server":"Server",
"ntp_fallback":"Server di riserva (se il router non ne fornisce uno, vale dopo il riavvio)",
"loc":"Luogo","loc_custom":"luogo personalizzato (coordinate)","tz_from_loc":"dal luogo {city}",
"tz":"Fuso orario","tz_cet":"Europa centrale (IT, DE, CH …)","tz_wet":"Londra, Lisbona (WET)","tz_eet":"Europa orientale (Kyiv, Atene, Bucarest)",
"tz_trt":"Turchia","tz_eat":"Africa orientale (Tanzania, Kenya)","tz_utc":"UTC",
"tz_use":"USA Est","tz_usc":"USA Centro","tz_usm":"USA Montagne","tz_usw":"USA Ovest",
"tz_wib":"Indonesia (Giacarta)","tz_cst":"Cina","tz_kst":"Corea","tz_jst":"Giappone","tz_aus":"Australia Est",
"tz_custom":"personalizzato (POSIX TZ) …","tz_posix":"Fuso orario POSIX","ntp_active":"Server attivo",
"ntp_hint":"Automatico: server dal router (DHCP), altrimenti quello inserito come riserva. Passare tra automatico e manuale riavvia l’orologio.",
"ntp_nodhcp":"NTP via DHCP non è disponibile in questo pacchetto scheda – viene usato il server inserito.",
"sec_wifi":"Wi-Fi","ssid":"Rete (SSID)","scan":"Cerca reti","pass":"Password","pass_ph":"vuoto = mantieni quella attuale",
"host":"Nome dispositivo (http://nome.local)","save_wifi":"Salva e riconnetti",
"status":"Stato","ip":"IP","last_err":"Ultimo errore",
"hint_wifi":"Se all’avvio il Wi-Fi non viene trovato, l’orologio apre l’hotspot «{ap}» (senza password, http://192.168.4.1).",
"w_conn":"connesso a {ssid}","w_ap":"Hotspot attivo ({ip})","w_none":"non connesso",
"scanning":"Ricerca …","scan_none":"Nessuna rete trovata","scan_err":"Ricerca non riuscita",
"wr_2":"autenticazione scaduta","wr_15":"password errata?","wr_201":"rete non trovata","wr_202":"autenticazione rifiutata (password?)",
"wr_203":"associazione non riuscita","wr_204":"password errata?","wr_205":"connessione non riuscita","wr_8":"disconnesso",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi disconnesso","net_lost":"nessuna connessione con l’orologio",
"sec_sys":"Sistema","mir":"LED 0 davanti in alto a destra (specchio)","srp":"Matrice cablata a zigzag",
"restart":"Riavvia","reset":"Ripristino di fabbrica",
"q_restart":"Riavviare l’orologio?","q_reset":"Cancellare tutte le impostazioni, Wi-Fi compreso?",
"language":"Lingua","firmware":"Firmware","uptime":"Tempo di attività","heap":"Memoria libera",
"footer":"{ap} – istruzioni di montaggio, codice e file di stampa:",
"saved":"Salvato","saved_restart":"Salvato – l’orologio si riavvia …","save_err":"Errore durante il salvataggio",
"time_set":"Ora acquisita","restarting":"L’orologio si riavvia …",
"srv_no_network":"Nessuna rete inserita","srv_back":"Indietro","srv_saved":"Wi-Fi salvato",
"srv_connecting":"L’orologio ora si connette a","srv_restart":"e per questo si riavvia. L’hotspot scompare.",
"srv_reach":"Poi raggiungibile su","srv_reach2":"o tramite l’indirizzo IP dal router o dal monitor seriale.",
"srv_retry":"Se la connessione non riesce, l’hotspot ricompare dopo circa 30 secondi.",
"srv_not_found":"Non trovato"
})JSON";
}  // namespace wc_it
static const WcLangDef WC_LANG = {
    "IT", "Italiano", wc_it::GRID,
    {14, 1, 6},   // AERARE
    {14, 8, 7},   // ALLARME
    {15, 1, 4},   // BATT
    {15, 6, 10},  // battery bars
    wc_it::EXTRA, 1,  // CIAO
    wc_it::time_words,
    "orologio", "Orologio",
    41.9028f, 12.4964f,            // Roma
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Rome
    "%d/%m/%Y",
    wc_it::UI_JSON,
};
