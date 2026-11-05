/*
  wc_lang_FR.h - Wordclock 16x16, language file FR (Français), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_FR.scad (check: python3 tools/check_lang.py FR).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_FR.txt)
  Satzbau: IL EST <Stunde> HEURE(S) [<Minuten> | MOINS <Minuten>]
  Ab :35 (MOINS) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 (nichts), :05 CINQ, :10 DIX, :15 ET QUART, :20 VINGT, :25 VINGT-CINQ, :30 ET DEMIE,
  :35 MOINS VINGT-CINQ, :40 MOINS VINGT, :45 MOINS LE QUART, :50 MOINS DIX, :55 MOINS CINQ
  UNE HEURE (Einzahl), sonst HEURES. 12 Uhr = MIDI, 0 Uhr = MINUIT, jeweils ohne HEURE(S)
  und dann „ET DEMI“ (ohne E).
  Minutenzeile: + 1 MINUTE (Einzahl), + 2..4 MINUTES.
  Zusatzwörter (Schalter „Afficher BONJOUR“): BONJOUR („Guten Tag“, Gruß).
  INFO_EN
  Sentence: IL EST <hour> HEURE(S) [<minutes> | MOINS <minutes>]
  From :35 (MOINS) on the time refers to the next hour.
  :00 (nothing), :05 CINQ, :10 DIX, :15 ET QUART, :20 VINGT, :25 VINGT-CINQ, :30 ET DEMIE,
  :35 MOINS VINGT-CINQ, :40 MOINS VINGT, :45 MOINS LE QUART, :50 MOINS DIX, :55 MOINS CINQ
  UNE HEURE (singular), otherwise HEURES. 12 o'clock = MIDI, 0 o'clock = MINUIT, both without
  HEURE(S), and then "ET DEMI" (without E).
  Minute row: + 1 MINUTE (singular), + 2..4 MINUTES.
  Extra words (switch "Afficher BONJOUR"): BONJOUR ("good day", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_fr {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xxxILxESTxxxxx*",
    "*xxUNExxxDEUXxx*",
    "*xTROISxQUATREx*",
    "*xCINQxSIXxSEPT*",
    "*xxHUITxxxNEUFx*",
    "*xxDIXxxxxONZEx*",
    "*xMIDIxxMINUITx*",
    "*xxxxHEURESxxxx*",
    "*xxxETxBONJOURx*",
    "*xxxxMOINSxxxxx*",
    "*xxVINGT-CINQxx*",
    "*xDIXxxLExQUART*",
    "*xxxxDEMIExxxxx*",
    "x+x1234xMINUTESx",
    "xxAÉRERxxALARMEx",
    "xBATTx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord IL = {0, 4, 2}, EST = {0, 7, 3};
static const WcWord HEURES = {7, 5, 6}, HEURE = {7, 5, 5}, MIDI = {6, 2, 4}, MINUIT = {6, 8, 6};
static const WcWord ET = {8, 4, 2}, MOINS = {9, 5, 5}, LE = {11, 7, 2};
static const WcWord M_CINQ = {10, 9, 4}, M_DIX = {11, 2, 3}, M_QUART = {11, 10, 5}, M_VINGT = {10, 3, 5};
static const WcWord M_VINGT_CINQ = {10, 3, 10}, DEMIE = {12, 5, 5}, DEMI = {12, 5, 4};  // VINGT-CINQ with hyphen
// hour 1..11 (index 0 = MIDI, only a placeholder: 12 o'clock is MIDI/MINUIT, chosen in time_words)
static const WcWord HOURS[12] = {{6, 2, 4},  {1, 3, 3}, {1, 9, 4},  {2, 2, 5},  {2, 8, 6},  {3, 2, 4},
                                 {3, 7, 3},  {3, 11, 4}, {4, 3, 4}, {4, 10, 4}, {5, 3, 3},  {5, 10, 4}};
// extra words (easter egg): BONJOUR ("good day", greeting)
static const WcWord EXTRA[1] = {{8, 7, 7}};
// row 14: "+ 1 2 3 4  MINUTES" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 7}, MIN_ONE = {13, 8, 6};  // MINUTES / MINUTE
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(IL);
  m.word(EST);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 24;
  if (m5 >= 7) h = (h + 1) % 24;  // from "moins vingt-cinq" on the next hour counts
  const bool twelve = (h % 12) == 0;
  if (h == 12) m.word(MIDI);
  else if (h == 0) m.word(MINUIT);
  else {
    m.word(HOURS[h % 12]);
    m.word(h % 12 == 1 ? HEURE : HEURES);  // UNE HEURE, DEUX HEURES ...
  }
  switch (m5) {
    case 0: break;
    case 1: m.word(M_CINQ); break;
    case 2: m.word(M_DIX); break;
    case 3: m.word(ET); m.word(M_QUART); break;
    case 4: m.word(M_VINGT); break;
    case 5: m.word(M_VINGT_CINQ); break;
    case 6: m.word(ET); m.word(twelve ? DEMI : DEMIE); break;  // MIDI ET DEMI, DEUX HEURES ET DEMIE
    case 7: m.word(MOINS); m.word(M_VINGT_CINQ); break;
    case 8: m.word(MOINS); m.word(M_VINGT); break;
    case 9: m.word(MOINS); m.word(LE); m.word(M_QUART); break;
    case 10: m.word(MOINS); m.word(M_DIX); break;
    default: m.word(MOINS); m.word(M_CINQ); break;
  }
  const int mm = minute % 5;  // "+ 1 MINUTE" or "+ 2..4 MINUTES"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(mm == 1 ? MIN_ONE : MIN_WORD);  // singular: without the final S
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"fr","dec":",",
"notime_msg":"L’horloge n’a pas encore l’heure (pas d’Internet ou de NTP).",
"btn_settime":"Reprendre l’heure du téléphone/PC",
"ap_info":"Point d’accès « {ap} » actif. Veuillez saisir votre réseau ci-dessous sous <b>Wi-Fi</b>.",
"sec_show":"Affichage","on":"Horloge allumée","swMin":"Minutes isolées (+ 1–4 MINUTES)",
"brD":"Luminosité jour","brN":"Luminosité nuit","cur":"Limite de courant (mA)",
"hint_show":"Nuit 0 % = affichage éteint la nuit. Choisissez la limite de courant selon l’alimentation (256 LED consomment déjà environ 256 mA au repos).",
"sec_col":"Couleurs",
"hint_col":"« Aléatoire » change à chaque heure pleine. « Température » : froid bleu foncé, jaune, confort vert, orange, chaud rouge (selon l’échelle sous affichages supplémentaires).",
"g_time":"Heure","g_vent":"AÉRER","g_alarm":"ALARME","g_batt":"BATT","g_tout":"Température extérieure","g_tin":"Température intérieure",
"pal_0":"Blanc chaud","pal_1":"Blanc","pal_2":"Rouge","pal_3":"Orange","pal_4":"Jaune","pal_5":"Vert","pal_6":"Bleu","pal_7":"Violet",
"c_random":"Aléatoire","c_temp":"Température","c_pride":"Pride","c_custom":"couleur personnalisée",
"sec_fx":"Effets",
"fx_rainbow":"Arc-en-ciel","fx_aurora":"Aurore","fx_matrix":"Matrix","fx_fire":"Feu","fx_confetti":"Confettis","fx_stars":"Ciel étoilé",
"fx_blink":"Clignoter","fx_blink_own":"Clignoter (couleur perso.)","stop":"Arrêt",
"fxd":"Durée de l’effet","blk":"Cycle de clignotement",
"hint_fx":"Durée 0 s = tourne jusqu’à « Arrêt ». Les effets tournent toujours avec au moins 10 % de luminosité, même la nuit à 0 % ou horloge éteinte.",
"fx_started":"{fx} démarré","fx_stopped":"Effet arrêté",
"txt":"Texte défilant","txt_ph":"Saisir un texte","txt_start":"Afficher le texte","txt_started":"Texte démarré",
"hint_txt":"Chaque lettre remplit toute la matrice. Dure le temps de l’effet (au moins une fois), dans la couleur de l’heure (aléatoire = arc-en-ciel). Lettres latines, grecques et cyrilliques, chiffres, ponctuation, € et ♥. HTTP : /api/set?text=…",
"sec_sun":"Jour / nuit","nmode":"Mode nuit","nm_mix":"Mixte","nm_sun":"Position du soleil","nm_fixed":"Heures fixes",
"lat":"Latitude","lon":"Longitude","nso":"Décalage début de nuit (min)","neo":"Décalage fin de nuit (min)",
"nme":"Nuit pas avant","nml":"Nuit pas après","nfs":"Nuit de","nfe":"Nuit jusqu’à",
"sunrise":"Lever du soleil","sunset":"Coucher du soleil","night_today":"Nuit aujourd’hui","now":"Maintenant",
"nmh_0":"Décalage : + après, − avant le coucher ou le lever du soleil. Coordonnées p. ex. depuis une appli de cartes (clic droit sur le lieu).",
"nmh_1":"Les heures fixes s’appliquent tous les jours.",
"nmh_2":"La nuit commence au coucher du soleil (plus décalage), mais pas avant l’heure réglée, et finit au lever du soleil (plus décalage), mais pas après l’heure réglée.",
"day":"Jour","night":"Nuit",
"sec_extra":"Affichages supplémentaires","tOnl":"Température extérieure d’Open-Meteo (lieu)",
"scale_out":"Échelle extérieure (°C)","scale_in":"Échelle intérieure (°C)",
"swExtra":"Afficher BONJOUR",
"apiTo":"Valeurs valables pendant (min, 0 = toujours)",
"v_out":"Extérieur","v_in":"Intérieur","v_batt":"Batterie","v_la":"Aérer / alarme","on_":"marche","off_":"arrêt",
"hint_extra":"Intérieur, batterie, aérer et alarme (et extérieur, si sans Open-Meteo) viennent de l’extérieur, p. ex. par navigateur, script ou maison connectée :",
"sec_api":"Commande HTTP",
"hint_api1":"Depuis d’autres systèmes par navigateur, script ou maison connectée (GET ou POST vers <code>/api/set</code>, plusieurs paramètres combinables). Luminosité, couleurs et interrupteurs sont enregistrés, les effets tournent pendant la durée réglée.",
"hint_api2":"Couleurs : warmwhite, white, red, orange, yellow, green, blue, violet, random (température : temp) ou rrggbb · Interrupteurs : on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Effets : {fx}, stop · fxcolor : nom de couleur ou rrggbb. Limite de courant, Wi-Fi et système uniquement ici dans l’interface web.",
"sec_time":"Heure","ntpD":"Serveur NTP","ntp_auto":"automatique (DHCP)","ntp_manual":"manuel","ntp_server":"Serveur",
"ntp_fallback":"Serveur de secours (si le routeur n’en fournit pas, valable après redémarrage)",
"loc":"Lieu","loc_custom":"lieu personnalisé (coordonnées)","tz_from_loc":"selon le lieu {city}",
"tz":"Fuseau horaire","tz_cet":"Europe centrale (FR, DE, CH …)","tz_wet":"Londres, Lisbonne (WET)","tz_eet":"Europe de l’Est (Kyiv, Athènes, Bucarest)",
"tz_trt":"Turquie","tz_eat":"Afrique de l’Est (Tanzanie, Kenya)","tz_utc":"UTC",
"tz_use":"USA Est","tz_usc":"USA Centre","tz_usm":"USA Montagnes","tz_usw":"USA Ouest",
"tz_wib":"Indonésie (Jakarta)","tz_cst":"Chine","tz_kst":"Corée","tz_jst":"Japon","tz_aus":"Australie Est",
"tz_custom":"personnalisé (POSIX TZ) …","tz_posix":"Fuseau horaire POSIX","ntp_active":"Serveur actif",
"ntp_hint":"Automatique : serveur du routeur (DHCP), sinon celui saisi comme secours. Passer d’automatique à manuel redémarre l’horloge.",
"ntp_nodhcp":"Le NTP par DHCP n’est pas disponible dans ce paquet de carte – le serveur saisi est utilisé.",
"sec_wifi":"Wi-Fi","ssid":"Réseau (SSID)","scan":"Chercher des réseaux","pass":"Mot de passe","pass_ph":"vide = garder l’actuel",
"host":"Nom de l’appareil (http://nom.local)","save_wifi":"Enregistrer & reconnecter",
"status":"État","ip":"IP","last_err":"Dernière erreur",
"hint_wifi":"Si le Wi-Fi n’est pas trouvé au démarrage, l’horloge ouvre le point d’accès « {ap} » (sans mot de passe, http://192.168.4.1).",
"w_conn":"connecté à {ssid}","w_ap":"Point d’accès actif ({ip})","w_none":"non connecté",
"scanning":"Recherche …","scan_none":"Aucun réseau trouvé","scan_err":"Échec de la recherche",
"wr_2":"authentification expirée","wr_15":"mot de passe erroné ?","wr_201":"réseau introuvable","wr_202":"authentification refusée (mot de passe ?)",
"wr_203":"échec de l’association","wr_204":"mot de passe erroné ?","wr_205":"échec de la connexion","wr_8":"déconnecté",
"net_hotspot":"Point d’accès {ap}","net_off":"Wi-Fi déconnecté","net_lost":"pas de connexion avec l’horloge",
"sec_sys":"Système","mir":"LED 0 devant en haut à droite (miroir)","srp":"Matrice câblée en zigzag",
"restart":"Redémarrer","reset":"Réinitialisation d’usine",
"q_restart":"Redémarrer l’horloge ?","q_reset":"Effacer tous les réglages, Wi-Fi compris ?",
"language":"Langue","firmware":"Firmware","uptime":"Temps de fonctionnement","heap":"Mémoire libre",
"footer":"{ap} – guide de montage, code et fichiers d’impression :",
"saved":"Enregistré","saved_restart":"Enregistré – l’horloge redémarre …","save_err":"Erreur lors de l’enregistrement",
"time_set":"Heure reprise","restarting":"L’horloge redémarre …",
"srv_no_network":"Aucun réseau saisi","srv_back":"Retour","srv_saved":"Wi-Fi enregistré",
"srv_connecting":"L’horloge se connecte maintenant à","srv_restart":"et redémarre pour cela. Le point d’accès disparaît.",
"srv_reach":"Ensuite joignable sous","srv_reach2":"ou par l’adresse IP du routeur ou du moniteur série.",
"srv_retry":"Si la connexion échoue, le point d’accès réapparaît après environ 30 secondes.",
"srv_not_found":"Introuvable"
})JSON";
}  // namespace wc_fr
static const WcLangDef WC_LANG = {
    "FR", "Français", wc_fr::GRID,
    {14, 2, 5},   // AÉRER
    {14, 9, 6},   // ALARME
    {15, 1, 4},   // BATT
    {15, 6, 10},  // battery bars
    wc_fr::EXTRA, 1,  // BONJOUR
    wc_fr::time_words,
    "horloge", "Horloge",
    48.8566f, 2.3522f,             // Paris
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Paris
    "%d/%m/%Y",
    wc_fr::UI_JSON,
};
