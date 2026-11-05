/*
  wc_lang_GR.h - Wordclock 16x16, language file GR (Ελληνικά), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_GR.scad (check: python3 tools/check_lang.py GR).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_GR.txt)
  Satzbau (gängige Umgangsform, 12-Stunden-Zählung, ab :35 auf die nächste Stunde bezogen):
  Η ΩΡΑ ΕΙΝΑΙ <Stunde> [ΚΑΙ <Minuten> | ΠΑΡΑ <Minuten>]
  („Η ώρα είναι …“ = „Die Uhrzeit ist …“; ΚΑΙ = „und“ = nach, ΠΑΡΑ = „vor“).
  Bis :30 zählt die aktuelle Stunde mit ΚΑΙ, ab :35 die nächste Stunde mit ΠΑΡΑ.
  :00 <Stunde>, :05 <Stunde> ΚΑΙ ΠΕΝΤΕ, :10 ΚΑΙ ΔΕΚΑ, :15 ΚΑΙ ΤΕΤΑΡΤΟ, :20 ΚΑΙ ΕΙΚΟΣΙ,
  :25 ΚΑΙ ΕΙΚΟΣΙ ΠΕΝΤΕ, :30 ΚΑΙ ΜΙΣΗ, :35 <nächste Stunde> ΠΑΡΑ ΕΙΚΟΣΙ ΠΕΝΤΕ, :40 ΠΑΡΑ ΕΙΚΟΣΙ,
  :45 ΠΑΡΑ ΤΕΤΑΡΤΟ, :50 ΠΑΡΑ ΔΕΚΑ, :55 ΠΑΡΑ ΠΕΝΤΕ
  Beispiele: 3:05 Η ΩΡΑ ΕΙΝΑΙ ΤΡΕΙΣ ΚΑΙ ΠΕΝΤΕ, 3:30 Η ΩΡΑ ΕΙΝΑΙ ΤΡΕΙΣ ΚΑΙ ΜΙΣΗ,
  3:45 Η ΩΡΑ ΕΙΝΑΙ ΤΕΣΣΕΡΙΣ ΠΑΡΑ ΤΕΤΑΡΤΟ, 3:55 Η ΩΡΑ ΕΙΝΑΙ ΤΕΣΣΕΡΙΣ ΠΑΡΑ ΠΕΝΤΕ.
  Stunden (weibliche Formen, weil „η ώρα“ weiblich ist): ΜΙΑ, ΔΥΟ, ΤΡΕΙΣ, ΤΕΣΣΕΡΙΣ, ΠΕΝΤΕ, ΕΞΙ, ΕΠΤΑ,
  ΟΚΤΩ, ΕΝΝΙΑ, ΔΕΚΑ, ΕΝΤΕΚΑ, ΔΩΔΕΚΑ. 0 und 12 Uhr = ΔΩΔΕΚΑ, keine Wörter für Mitternacht/Mittag.
  ΠΕΝΤΕ und ΔΕΚΑ gibt es je zweimal (Stunde und Minuten). ΚΑΙ ΜΙΣΗ statt der Kurzform „τρεισήμισι“.
  Großbuchstaben ohne Tonos (Akzent), wie in griechischer Versalschrift üblich.
  Ohne gültige Uhrzeit leuchtet nur Η ΩΡΑ ΕΙΝΑΙ.
  Minutenzeile: + 1 ΛΕΠΤΟ (Einzahl), + 2..4 ΛΕΠΤΑ (Mehrzahl); im Raster steht ΛΕΠΤΟΑ, ΛΕΠΤ + Ο bzw. ΛΕΠΤ + Α.
  Statuswörter: LÜFTEN = ΑΕΡΑΣ („Luft“; ΑΕΡΙΣΜΟΣ passt nicht neben ΣΥΝΑΓΕΡΜΟΣ), ALARM = ΣΥΝΑΓΕΡΜΟΣ,
  AKKU = ΜΠΑΤ (Abkürzung von ΜΠΑΤΑΡΙΑ, wie GB BATT).
  Zusatzwörter (Schalter „Εμφάνιση ΤΑ ΠΑΝΤΑ ΡΕΙ“): ΤΑ ΠΑΝΤΑ ΡΕΙ („alles fließt“, Heraklit).
  Sonderzeichen: griechische Großbuchstaben (U+0391..U+03A9, auch Α Ε Η Ι Κ Μ Ν Ο Ρ Τ Υ sind eigene Zeichen,
  keine lateinischen). Metriken in Wordclock_Model.scad vorhanden (Block Greek, alle 24 Großbuchstaben);
  Liberation Sans, Arial und DejaVu Sans enthalten Griechisch.
  INFO_EN
  Sentence (common spoken form, 12-hour counting, from :35 on the next hour counts):
  Η ΩΡΑ ΕΙΝΑΙ <hour> [ΚΑΙ <minutes> | ΠΑΡΑ <minutes>]
  ("Η ώρα είναι ..." = "the time is ..."; ΚΑΙ = "and" = past, ΠΑΡΑ = "to").
  Up to :30 the current hour counts with ΚΑΙ, from :35 on the next hour with ΠΑΡΑ.
  :00 <hour>, :05 <hour> ΚΑΙ ΠΕΝΤΕ, :10 ΚΑΙ ΔΕΚΑ, :15 ΚΑΙ ΤΕΤΑΡΤΟ, :20 ΚΑΙ ΕΙΚΟΣΙ,
  :25 ΚΑΙ ΕΙΚΟΣΙ ΠΕΝΤΕ, :30 ΚΑΙ ΜΙΣΗ, :35 <next hour> ΠΑΡΑ ΕΙΚΟΣΙ ΠΕΝΤΕ, :40 ΠΑΡΑ ΕΙΚΟΣΙ,
  :45 ΠΑΡΑ ΤΕΤΑΡΤΟ, :50 ΠΑΡΑ ΔΕΚΑ, :55 ΠΑΡΑ ΠΕΝΤΕ
  Examples: 3:05 Η ΩΡΑ ΕΙΝΑΙ ΤΡΕΙΣ ΚΑΙ ΠΕΝΤΕ, 3:30 Η ΩΡΑ ΕΙΝΑΙ ΤΡΕΙΣ ΚΑΙ ΜΙΣΗ,
  3:45 Η ΩΡΑ ΕΙΝΑΙ ΤΕΣΣΕΡΙΣ ΠΑΡΑ ΤΕΤΑΡΤΟ, 3:55 Η ΩΡΑ ΕΙΝΑΙ ΤΕΣΣΕΡΙΣ ΠΑΡΑ ΠΕΝΤΕ.
  Hours (feminine forms, because "η ώρα" is feminine): ΜΙΑ, ΔΥΟ, ΤΡΕΙΣ, ΤΕΣΣΕΡΙΣ, ΠΕΝΤΕ, ΕΞΙ, ΕΠΤΑ,
  ΟΚΤΩ, ΕΝΝΙΑ, ΔΕΚΑ, ΕΝΤΕΚΑ, ΔΩΔΕΚΑ. 0 and 12 o'clock = ΔΩΔΕΚΑ, no words for midnight/noon.
  ΠΕΝΤΕ and ΔΕΚΑ exist twice (hour and minutes). ΚΑΙ ΜΙΣΗ instead of the short form "τρεισήμισι".
  Capitals without tonos (accent), as usual in Greek all-caps writing.
  Without a valid time only Η ΩΡΑ ΕΙΝΑΙ is lit.
  Minute row: + 1 ΛΕΠΤΟ (singular), + 2..4 ΛΕΠΤΑ (plural); the grid has ΛΕΠΤΟΑ, ΛΕΠΤ + Ο or ΛΕΠΤ + Α.
  Status words: VENTILATE = ΑΕΡΑΣ ("air"; ΑΕΡΙΣΜΟΣ does not fit next to ΣΥΝΑΓΕΡΜΟΣ), ALARM = ΣΥΝΑΓΕΡΜΟΣ,
  BATTERY = ΜΠΑΤ (abbreviation of ΜΠΑΤΑΡΙΑ, like GB BATT).
  Extra words (switch "Εμφάνιση ΤΑ ΠΑΝΤΑ ΡΕΙ"): ΤΑ ΠΑΝΤΑ ΡΕΙ ("everything flows", Heraclitus).
  Special letters: Greek capitals (U+0391..U+03A9, also Α Ε Η Ι Κ Μ Ν Ο Ρ Τ Υ are own characters, not Latin).
  Metrics are in Wordclock_Model.scad (block Greek, all 24 capitals);
  Liberation Sans, Arial and DejaVu Sans contain Greek.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_gr {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
// All letters are Greek capitals (U+0391..U+03A9), only "x" is Latin.
static const char *const GRID[16] = {
    "*ΗxΩΡΑxΕΙΝΑΙxxx*",
    "*ΜΙΑxΔΥΟxΤΡΕΙΣx*",
    "*ΤΕΣΣΕΡΙΣxΠΕΝΤΕ*",
    "*ΕΞΙxΕΠΤΑxΟΚΤΩx*",
    "*xΕΝΝΙΑxxΔΕΚΑxx*",
    "*ΕΝΤΕΚΑxxΔΩΔΕΚΑ*",
    "*xxΚΑΙxxxΠΑΡΑxx*",
    "*ΕΙΚΟΣΙxxΠΕΝΤΕx*",
    "*ΔΕΚΑxxΤΕΤΑΡΤΟx*",
    "*xxxxxΜΙΣΗxxxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xΤΑxΠΑΝΤΑxΡΕΙx*",
    "*xxxxxxxxxxxxxx*",
    "x+x1234xxΛΕΠΤΟΑx",
    "ΑΕΡΑΣxΣΥΝΑΓΕΡΜΟΣ",
    "xΜΠΑΤx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord H_ = {0, 1, 1}, ORA = {0, 3, 3}, EINAI = {0, 7, 5};
static const WcWord KAI = {6, 3, 3}, PARA = {6, 9, 4};
static const WcWord M_EIKOSI = {7, 1, 6}, M_PENTE = {7, 9, 5}, M_DEKA = {8, 1, 4}, M_TETARTO = {8, 7, 7};
static const WcWord M_MISI = {9, 6, 4};
// hour 0..11 (0 = ΔΩΔΕΚΑ)
static const WcWord HOURS[12] = {{5, 9, 6}, {1, 1, 3}, {1, 5, 3},  {1, 9, 5}, {2, 1, 8}, {2, 10, 5},
                                 {3, 1, 3}, {3, 5, 4}, {3, 10, 4}, {4, 2, 5}, {4, 9, 4}, {5, 1, 6}};
// extra words (easter egg): ΤΑ ΠΑΝΤΑ ΡΕΙ ("everything flows")
static const WcWord EXTRA[3] = {{11, 2, 2}, {11, 5, 5}, {11, 11, 3}};
// row 14: "+ 1 2 3 4  ΛΕΠΤΟΑ" (digits in columns 3..6), ΛΕΠΤ + Ο = ΛΕΠΤΟ (1), ΛΕΠΤ + Α = ΛΕΠΤΑ (2..4)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_STEM = {13, 9, 4}, MIN_O = {13, 13, 1}, MIN_A = {13, 14, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(H_);
  m.word(ORA);
  m.word(EINAI);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 7) h = (h + 1) % 12;  // from :35 on "ΠΑΡΑ" + next hour
  m.word(HOURS[h]);
  switch (m5) {
    case 0: break;
    case 1: m.word(KAI); m.word(M_PENTE); break;
    case 2: m.word(KAI); m.word(M_DEKA); break;
    case 3: m.word(KAI); m.word(M_TETARTO); break;
    case 4: m.word(KAI); m.word(M_EIKOSI); break;
    case 5: m.word(KAI); m.word(M_EIKOSI); m.word(M_PENTE); break;
    case 6: m.word(KAI); m.word(M_MISI); break;
    case 7: m.word(PARA); m.word(M_EIKOSI); m.word(M_PENTE); break;
    case 8: m.word(PARA); m.word(M_EIKOSI); break;
    case 9: m.word(PARA); m.word(M_TETARTO); break;
    case 10: m.word(PARA); m.word(M_DEKA); break;
    default: m.word(PARA); m.word(M_PENTE); break;
  }
  const int mm = minute % 5;  // "+ 1 ΛΕΠΤΟ" / "+ 2..4 ΛΕΠΤΑ"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_STEM);
    m.glue(mm == 1 ? MIN_O : MIN_A);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"el","dec":",",
"notime_msg":"Το ρολόι δεν γνωρίζει ακόμα την ώρα (χωρίς internet ή NTP).",
"btn_settime":"Λήψη ώρας από κινητό/υπολογιστή",
"ap_info":"Το hotspot «{ap}» είναι ενεργό. Καταχωρίστε το δίκτυό σας παρακάτω στο <b>Wi-Fi</b>.",
"sec_show":"Οθόνη","on":"Ρολόι ενεργό","swMin":"Μεμονωμένα λεπτά (+ 1–4 ΛΕΠΤΑ)",
"brD":"Φωτεινότητα ημέρας","brN":"Φωτεινότητα νύχτας","cur":"Όριο ρεύματος (mA)",
"hint_show":"Νύχτα 0 % = η οθόνη σβήνει τη νύχτα. Επιλέξτε το όριο ρεύματος ανάλογα με το τροφοδοτικό (256 LED χρειάζονται ήδη περίπου 256 mA σε ηρεμία).",
"sec_col":"Χρώματα",
"hint_col":"Το «Τυχαίο» αλλάζει σε κάθε ακέραιη ώρα. «Θερμοκρασία»: κρύο σκούρο μπλε, κίτρινο, άνεση πράσινο, πορτοκαλί, ζέστη κόκκινο (σύμφωνα με την κλίμακα στις πρόσθετες ενδείξεις).",
"g_time":"Ώρα","g_vent":"ΑΕΡΑΣ","g_alarm":"ΣΥΝΑΓΕΡΜΟΣ","g_batt":"ΜΠΑΤ","g_tout":"Εξωτερική θερμοκρασία","g_tin":"Εσωτερική θερμοκρασία",
"pal_0":"Θερμό λευκό","pal_1":"Λευκό","pal_2":"Κόκκινο","pal_3":"Πορτοκαλί","pal_4":"Κίτρινο","pal_5":"Πράσινο","pal_6":"Μπλε","pal_7":"Βιολετί",
"c_random":"Τυχαίο","c_temp":"Θερμοκρασία","c_pride":"Pride","c_custom":"δικό σας χρώμα",
"sec_fx":"Εφέ",
"fx_rainbow":"Ουράνιο τόξο","fx_aurora":"Σέλας","fx_matrix":"Matrix","fx_fire":"Φωτιά","fx_confetti":"Κομφετί","fx_stars":"Έναστρος ουρανός",
"fx_blink":"Αναβόσβημα","fx_blink_own":"Αναβόσβημα (δικό σας χρώμα)","stop":"Διακοπή",
"fxd":"Διάρκεια εφέ","blk":"Κύκλος αναβοσβήματος",
"hint_fx":"Διάρκεια 0 s = τρέχει μέχρι τη «Διακοπή». Τα εφέ τρέχουν πάντα με τουλάχιστον 10 % φωτεινότητα, ακόμα και τη νύχτα με 0 % ή με το ρολόι σβηστό.",
"fx_started":"{fx} ξεκίνησε","fx_stopped":"Το εφέ σταμάτησε",
"txt":"Κυλιόμενο κείμενο","txt_ph":"Γράψε κείμενο","txt_start":"Εμφάνιση κειμένου","txt_started":"Το κείμενο ξεκίνησε",
"hint_txt":"Κάθε γράμμα γεμίζει όλη τη μήτρα. Διαρκεί όσο το εφέ (τουλάχιστον μία φορά), στο χρώμα της ώρας (τυχαίο = ουράνιο τόξο). Λατινικά, ελληνικά και κυριλλικά γράμματα, ψηφία, σημεία στίξης, € και ♥. HTTP: /api/set?text=…",
"sec_sun":"Ημέρα / νύχτα","nmode":"Λειτουργία νύχτας","nm_mix":"Μικτή","nm_sun":"Θέση ηλίου","nm_fixed":"Σταθερές ώρες",
"lat":"Γεωγραφικό πλάτος","lon":"Γεωγραφικό μήκος","nso":"Μετατόπιση αρχής νύχτας (λεπτά)","neo":"Μετατόπιση τέλους νύχτας (λεπτά)",
"nme":"Νύχτα όχι πριν από","nml":"Νύχτα όχι μετά από","nfs":"Νύχτα από","nfe":"Νύχτα έως",
"sunrise":"Ανατολή","sunset":"Δύση","night_today":"Νύχτα σήμερα","now":"Τώρα",
"nmh_0":"Μετατόπιση: + μετά, − πριν από τη δύση ή την ανατολή. Συντεταγμένες π.χ. από μια εφαρμογή χαρτών (δεξί κλικ στο σημείο).",
"nmh_1":"Οι σταθερές ώρες ισχύουν κάθε μέρα.",
"nmh_2":"Η νύχτα αρχίζει με τη δύση (συν μετατόπιση), αλλά όχι πριν από την ορισμένη ώρα, και τελειώνει με την ανατολή (συν μετατόπιση), αλλά όχι μετά την ορισμένη ώρα.",
"day":"Ημέρα","night":"Νύχτα",
"sec_extra":"Πρόσθετες ενδείξεις","tOnl":"Εξωτερική θερμοκρασία από το Open-Meteo (τοποθεσία)",
"scale_out":"Κλίμακα έξω (°C)","scale_in":"Κλίμακα μέσα (°C)",
"swExtra":"Εμφάνιση ΤΑ ΠΑΝΤΑ ΡΕΙ",
"apiTo":"Ισχύς τιμών (λεπτά, 0 = πάντα)",
"v_out":"Έξω","v_in":"Μέσα","v_batt":"Μπαταρία","v_la":"Αερισμός / συναγερμός","on_":"ναι","off_":"όχι",
"hint_extra":"Η εσωτερική θερμοκρασία, η μπαταρία, ο αερισμός και ο συναγερμός (και η εξωτερική, χωρίς Open-Meteo) έρχονται από έξω, π.χ. μέσω browser, script ή έξυπνου σπιτιού:",
"sec_api":"Έλεγχος HTTP",
"hint_api1":"Από άλλα συστήματα μέσω browser, script ή έξυπνου σπιτιού (GET ή POST στο <code>/api/set</code>, πολλές παράμετροι μπορούν να συνδυαστούν). Η φωτεινότητα, τα χρώματα και οι διακόπτες αποθηκεύονται, τα εφέ τρέχουν για την ορισμένη διάρκεια.",
"hint_api2":"Χρώματα: warmwhite, white, red, orange, yellow, green, blue, violet, random (θερμοκρασία: temp) ή rrggbb · Διακόπτες: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Εφέ: {fx}, stop · fxcolor: όνομα χρώματος ή rrggbb. Όριο ρεύματος, Wi-Fi και σύστημα μόνο εδώ στη διεπαφή web.",
"sec_time":"Ώρα","ntpD":"Διακομιστής NTP","ntp_auto":"αυτόματα (DHCP)","ntp_manual":"χειροκίνητα","ntp_server":"Διακομιστής",
"ntp_fallback":"Εφεδρικός διακομιστής (αν ο router δεν δίνει κάποιον, ισχύει μετά την επανεκκίνηση)",
"loc":"Τοποθεσία","loc_custom":"δική σας τοποθεσία (συντεταγμένες)","tz_from_loc":"από την τοποθεσία {city}",
"tz":"Ζώνη ώρας","tz_cet":"Κεντρική Ευρώπη (DE, AT, CH …)","tz_wet":"Λονδίνο, Λισαβόνα (WET)","tz_eet":"Ανατολική Ευρώπη (Κίεβο, Αθήνα, Βουκουρέστι)",
"tz_trt":"Τουρκία","tz_eat":"Ανατολική Αφρική (Τανζανία, Κένυα)","tz_utc":"UTC",
"tz_use":"ΗΠΑ Ανατολή","tz_usc":"ΗΠΑ Κέντρο","tz_usm":"ΗΠΑ Όρη","tz_usw":"ΗΠΑ Δύση",
"tz_wib":"Ινδονησία (Τζακάρτα)","tz_cst":"Κίνα","tz_kst":"Κορέα","tz_jst":"Ιαπωνία","tz_aus":"Ανατολική Αυστραλία",
"tz_custom":"δική σας (POSIX TZ) …","tz_posix":"Ζώνη ώρας POSIX","ntp_active":"Ενεργός διακομιστής",
"ntp_hint":"Αυτόματα: διακομιστής από τον router (DHCP), αλλιώς ο καταχωρισμένος ως εφεδρικός. Η αλλαγή μεταξύ αυτόματου και χειροκίνητου επανεκκινεί το ρολόι.",
"ntp_nodhcp":"Το NTP μέσω DHCP δεν είναι διαθέσιμο σε αυτό το πακέτο πλακέτας – χρησιμοποιείται ο καταχωρισμένος διακομιστής.",
"sec_wifi":"Wi-Fi","ssid":"Δίκτυο (SSID)","scan":"Αναζήτηση δικτύων","pass":"Κωδικός","pass_ph":"κενό = διατήρηση του τρέχοντος",
"host":"Όνομα συσκευής (http://onoma.local)","save_wifi":"Αποθήκευση & επανασύνδεση",
"status":"Κατάσταση","ip":"IP","last_err":"Τελευταίο σφάλμα",
"hint_wifi":"Αν το Wi-Fi δεν βρεθεί κατά την εκκίνηση, το ρολόι ανοίγει το hotspot «{ap}» (χωρίς κωδικό, http://192.168.4.1).",
"w_conn":"συνδεδεμένο με {ssid}","w_ap":"Hotspot ενεργό ({ip})","w_none":"δεν είναι συνδεδεμένο",
"scanning":"Αναζήτηση …","scan_none":"Δεν βρέθηκαν δίκτυα","scan_err":"Η αναζήτηση απέτυχε",
"wr_2":"ο έλεγχος ταυτότητας έληξε","wr_15":"λάθος κωδικός;","wr_201":"το δίκτυο δεν βρέθηκε","wr_202":"ο έλεγχος ταυτότητας απορρίφθηκε (κωδικός;)",
"wr_203":"η συσχέτιση απέτυχε","wr_204":"λάθος κωδικός;","wr_205":"η σύνδεση απέτυχε","wr_8":"αποσυνδέθηκε",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi αποσυνδεδεμένο","net_lost":"δεν υπάρχει σύνδεση με το ρολόι",
"sec_sys":"Σύστημα","mir":"LED 0 μπροστά πάνω δεξιά (κατοπτρισμός)","srp":"Μήτρα καλωδιωμένη σε ζιγκ-ζαγκ",
"restart":"Επανεκκίνηση","reset":"Επαναφορά εργοστασιακών ρυθμίσεων",
"q_restart":"Επανεκκίνηση του ρολογιού;","q_reset":"Διαγραφή όλων των ρυθμίσεων μαζί με το Wi-Fi;",
"language":"Γλώσσα","firmware":"Υλικολογισμικό","uptime":"Χρόνος λειτουργίας","heap":"Ελεύθερη μνήμη",
"footer":"{ap} – οδηγίες κατασκευής, κώδικας και αρχεία εκτύπωσης:",
"saved":"Αποθηκεύτηκε","saved_restart":"Αποθηκεύτηκε – το ρολόι επανεκκινείται …","save_err":"Σφάλμα κατά την αποθήκευση",
"time_set":"Η ώρα ελήφθη","restarting":"Το ρολόι επανεκκινείται …",
"srv_no_network":"Δεν καταχωρίστηκε δίκτυο","srv_back":"Πίσω","srv_saved":"Το Wi-Fi αποθηκεύτηκε",
"srv_connecting":"Το ρολόι συνδέεται τώρα με το","srv_restart":"και επανεκκινείται γι' αυτό. Το hotspot εξαφανίζεται.",
"srv_reach":"Στη συνέχεια είναι προσβάσιμο στο","srv_reach2":"ή μέσω της διεύθυνσης IP από τον router ή τη σειριακή οθόνη.",
"srv_retry":"Αν η σύνδεση αποτύχει, το hotspot εμφανίζεται ξανά μετά από περίπου 30 δευτερόλεπτα.",
"srv_not_found":"Δεν βρέθηκε"
})JSON";
}  // namespace wc_gr
static const WcLangDef WC_LANG = {
    "GR", "Ελληνικά", wc_gr::GRID,
    {14, 0, 5},   // ΑΕΡΑΣ
    {14, 6, 10},  // ΣΥΝΑΓΕΡΜΟΣ
    {15, 1, 4},   // ΜΠΑΤ
    {15, 6, 10},  // battery bars
    wc_gr::EXTRA, 3,  // ΤΑ ΠΑΝΤΑ ΡΕΙ
    wc_gr::time_words,
    "roloilexeon", "RoloiLexeon",
    37.9838f, 23.7275f,             // Athína
    "EET-2EEST,M3.5.0/3,M10.5.0/4",  // Europe/Athens
    "%d/%m/%Y",
    wc_gr::UI_JSON,
};
