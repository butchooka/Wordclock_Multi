/*
  wc_lang_UA.h - Wordclock 16x16, language file UA (Українська), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_UA.scad (check: python3 tools/check_lang.py UA).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_UA.txt)
  Satzbau (gängige Umgangssprache, 12-Stunden-Zählung, Stunden als Ordnungszahl weiblich, „година“):
  ЗАРАЗ <Stunde> ГОДИНА (volle Stunde) bzw. ЗАРАЗ <Minuten> НА <nächste Stunde, Akkusativ> (:05..:30)
  bzw. ЗАРАЗ ЗА <Minuten> <nächste Stunde, Nominativ> (:35..:55). ЗАРАЗ = „jetzt“.
  Ab :05 zählt die nächste Stunde („fünf auf die dritte“ = 2:05, „in fünf die dritte“ = 2:55).
  Beispiel 2:xx (nächste Stunde ТРЕТЯ, Akkusativ ТРЕТЮ):
  :00 ДРУГА ГОДИНА, :05 П'ЯТЬ НА ТРЕТЮ, :10 ДЕСЯТЬ НА ТРЕТЮ, :15 ЧВЕРТЬ НА ТРЕТЮ,
  :20 ДВАДЦЯТЬ НА ТРЕТЮ, :25 ДВАДЦЯТЬ П'ЯТЬ НА ТРЕТЮ, :30 ПІВ НА ТРЕТЮ,
  :35 ЗА ДВАДЦЯТЬ П'ЯТЬ ТРЕТЯ, :40 ЗА ДВАДЦЯТЬ ТРЕТЯ, :45 ЗА ЧВЕРТЬ ТРЕТЯ, :50 ЗА ДЕСЯТЬ ТРЕТЯ,
  :55 ЗА П'ЯТЬ ТРЕТЯ.
  Stunden 1..12: ПЕРША, ДРУГА, ТРЕТЯ, ЧЕТВЕРТА, П'ЯТА, ШОСТА, СЬОМА, ВОСЬМА, ДЕВ'ЯТА, ДЕСЯТА,
  ОДИНАДЦЯТА, ДВАНАДЦЯТА; Akkusativ mit -У statt -А (ТРЕТЯ: -Ю statt -Я).
  Nominativ und Akkusativ teilen sich ein Wort: Stamm + А (zusammenhängend) bzw. Stamm + У (eine Lücke),
  z. B. „ПЕРШАУ“: ПЕРШ + А = ПЕРША, ПЕРШ + У = ПЕРШУ; „ТРЕТЯЮ“: ТРЕТ + Я / ТРЕТ + Ю.
  0 und 12 Uhr = ЗАРАЗ ДВАНАДЦЯТА ГОДИНА. Keine Wörter für Mitternacht/Mittag.
  Ohne gültige Uhrzeit leuchtet nur ЗАРАЗ.
  Minutenzeile: + 1 ХВИЛИНА, + 2..4 ХВИЛИНИ (ХВИЛИН + И, eine Lücke).
  Statuswörter: LÜFTEN = ПРОВІТРИ („lüfte!“), ALARM = ТРИВОГА („Alarm“, auch Luftalarm),
  AKKU = ЗАРЯД („Ladung“, wie „заряд батареї“ auf dem Handy; АКУМУЛЯТОР und БАТАРЕЯ sind zu lang für
  die Zeile mit den 10 Balken).
  Zusatzwörter (Schalter „Показувати СЛАВА УКРАЇНІ“): СЛАВА УКРАЇНІ – ГЕРОЯМ СЛАВА („Ruhm der Ukraine – den Helden
  Ruhm“, Gruß und Antwort).
  Zeichen: kyrillische Großbuchstaben (Ї mit Trema, Д/Ц mit kurzer Unterlänge) und der Apostroph in
  П'ЯТЬ/ДЕВ'ЯТА als eigenes Feld. Die Modelle nutzen die Einstellung SCHRIFT (OpenSCAD: Liberation Sans,
  Arial oder DejaVu Sans Bold) bzw. die gewählte Schrift (FreeCAD, z. B. Arial Bold) – die Schrift muss
  Kyrillisch enthalten. Metriken in Wordclock_Model.scad vorhanden (Block Cyrillic, А–Я, Ё Є І Ї Ґ).
  Füllfelder: Vorgabe der Sprache ist der Punkt (FILLER = auto), da ein X mit dem kyrillischen Х verwechselbar ist.
  INFO_EN
  Sentence (common colloquial form, 12-hour counting, hours as feminine ordinals, "година" = hour):
  ЗАРАЗ <hour> ГОДИНА (full hour) or ЗАРАЗ <minutes> НА <next hour, accusative> (:05..:30)
  or ЗАРАЗ ЗА <minutes> <next hour, nominative> (:35..:55). ЗАРАЗ = "now".
  From :05 on the next hour counts ("five onto the third" = 2:05, "in five the third" = 2:55).
  Example 2:xx (next hour ТРЕТЯ, accusative ТРЕТЮ):
  :00 ДРУГА ГОДИНА, :05 П'ЯТЬ НА ТРЕТЮ, :10 ДЕСЯТЬ НА ТРЕТЮ, :15 ЧВЕРТЬ НА ТРЕТЮ,
  :20 ДВАДЦЯТЬ НА ТРЕТЮ, :25 ДВАДЦЯТЬ П'ЯТЬ НА ТРЕТЮ, :30 ПІВ НА ТРЕТЮ,
  :35 ЗА ДВАДЦЯТЬ П'ЯТЬ ТРЕТЯ, :40 ЗА ДВАДЦЯТЬ ТРЕТЯ, :45 ЗА ЧВЕРТЬ ТРЕТЯ, :50 ЗА ДЕСЯТЬ ТРЕТЯ,
  :55 ЗА П'ЯТЬ ТРЕТЯ.
  Hours 1..12: ПЕРША, ДРУГА, ТРЕТЯ, ЧЕТВЕРТА, П'ЯТА, ШОСТА, СЬОМА, ВОСЬМА, ДЕВ'ЯТА, ДЕСЯТА,
  ОДИНАДЦЯТА, ДВАНАДЦЯТА; accusative with -У instead of -А (ТРЕТЯ: -Ю instead of -Я).
  Nominative and accusative share one word: stem + А (contiguous) or stem + У (one gap),
  e.g. "ПЕРШАУ": ПЕРШ + А = ПЕРША, ПЕРШ + У = ПЕРШУ; "ТРЕТЯЮ": ТРЕТ + Я / ТРЕТ + Ю.
  0 and 12 o'clock = ЗАРАЗ ДВАНАДЦЯТА ГОДИНА. No words for midnight/noon.
  Without a valid time only ЗАРАЗ is lit.
  Minute row: + 1 ХВИЛИНА, + 2..4 ХВИЛИНИ (ХВИЛИН + И, one gap).
  Status words: VENTILATE = ПРОВІТРИ ("ventilate!"), ALARM = ТРИВОГА ("alarm", also air raid alarm),
  BATTERY = ЗАРЯД ("charge", as in "заряд батареї" on phones; АКУМУЛЯТОР and БАТАРЕЯ are too long for
  the row with the 10 bars).
  Extra words (switch "Показувати СЛАВА УКРАЇНІ"): СЛАВА УКРАЇНІ – ГЕРОЯМ СЛАВА ("glory to Ukraine – glory to the
  heroes", greeting and answer).
  Characters: Cyrillic capitals (Ї with diaeresis, Д/Ц with a short descender) and the apostrophe in
  П'ЯТЬ/ДЕВ'ЯТА as its own cell. The models use the setting SCHRIFT (OpenSCAD: Liberation Sans, Arial or
  DejaVu Sans Bold) or the chosen font (FreeCAD, e.g. Arial Bold) - the font must contain Cyrillic.
  Metrics are in Wordclock_Model.scad (block Cyrillic, А-Я, Ё Є І Ї Ґ).
  Fillers: the language default is a dot (FILLER = auto), as an X is easily confused with the Cyrillic Х.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_ua {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
// Note: the filler is the Latin lower case "x", the Cyrillic "Х" of ХВИЛИНА is a normal letter.
static const char *const GRID[16] = {
    "*ЗАРАЗxЗАxxПІВx*",
    "*ЧВЕРТЬxxДЕСЯТЬ*",
    "*ДВАДЦЯТЬxП'ЯТЬ*",
    "*НАxОДИНАДЦЯТАУ*",
    "*xПЕРШАУxДРУГАУ*",
    "*ТРЕТЯЮxxП'ЯТАУ*",
    "*xxЧЕТВЕРТАУxxx*",
    "*ШОСТАУxВОСЬМАУ*",
    "*СЬОМАУxДЕСЯТАУ*",
    "*ДЕВ'ЯТАУxСЛАВА*",
    "*xДВАНАДЦЯТАУxx*",
    "*ГОДИНАxУКРАЇНІ*",
    "*xГЕРОЯМxСЛАВАx*",
    "+x1234xxХВИЛИНАИ",
    "ПРОВІТРИxТРИВОГА",
    "ЗАРЯДx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord ZARAZ = {0, 1, 5}, ZA = {0, 7, 2}, PIV = {0, 11, 3}, NA = {3, 1, 2}, HODYNA = {11, 1, 6};
// minute words
static const WcWord M_CHVERT = {1, 1, 6}, M_DESIAT = {1, 9, 6}, M_DVADTSIAT = {2, 1, 8}, M_PIAT = {2, 10, 5};
// hour 0..11 (0 = ДВАНАДЦЯТ-): stem, nominative ending (А / Я, right after the stem), accusative ending (У / Ю)
static const WcWord H_STEM[12] = {{10, 2, 9}, {4, 2, 4}, {4, 9, 4}, {5, 1, 4}, {6, 3, 7}, {5, 9, 4},
                                  {7, 1, 4},  {8, 1, 4}, {7, 8, 5}, {9, 1, 6}, {8, 8, 5}, {3, 4, 9}};
static const WcWord H_NOM[12] = {{10, 11, 1}, {4, 6, 1}, {4, 13, 1}, {5, 5, 1}, {6, 10, 1}, {5, 13, 1},
                                 {7, 5, 1},   {8, 5, 1}, {7, 13, 1}, {9, 7, 1}, {8, 13, 1}, {3, 13, 1}};
static const WcWord H_ACC[12] = {{10, 12, 1}, {4, 7, 1}, {4, 14, 1}, {5, 6, 1}, {6, 11, 1}, {5, 14, 1},
                                 {7, 6, 1},   {8, 6, 1}, {7, 14, 1}, {9, 8, 1}, {8, 14, 1}, {3, 14, 1}};
// extra words (easter egg): СЛАВА УКРАЇНІ - ГЕРОЯМ СЛАВА
static const WcWord EXTRA[4] = {{9, 10, 5}, {11, 8, 7}, {12, 2, 6}, {12, 9, 5}};
// row 14: "+ 1 2 3 4  ХВИЛИНА / ХВИЛИН+И" (digits in columns 2..5)
static const WcWord MIN_PLUS = {13, 0, 1}, MIN_ONE = {13, 8, 7}, MIN_STEM = {13, 8, 6}, MIN_I = {13, 15, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 2;
static inline void hour_word(int h, bool acc, WcMark &m) {
  m.word(H_STEM[h]);
  m.glue(acc ? H_ACC[h] : H_NOM[h]);
}
// minutes 5..30 as words: 1 П'ЯТЬ, 2 ДЕСЯТЬ, 3 ЧВЕРТЬ, 4 ДВАДЦЯТЬ, 5 ДВАДЦЯТЬ П'ЯТЬ, 6 ПІВ
static inline void minute_words(int k, WcMark &m) {
  switch (k) {
    case 1: m.word(M_PIAT); break;
    case 2: m.word(M_DESIAT); break;
    case 3: m.word(M_CHVERT); break;
    case 4: m.word(M_DVADTSIAT); break;
    case 5: m.word(M_DVADTSIAT); m.word(M_PIAT); break;
    default: m.word(PIV); break;
  }
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(ZARAZ);
  if (!valid) return;
  const int h = hour % 12;             // 0 = ДВАНАДЦЯТА
  const int nh = (h + 1) % 12;         // next hour
  const int m5 = minute / 5;           // 0..11
  if (m5 == 0) {                       // ДРУГА ГОДИНА
    hour_word(h, false, m);
    m.word(HODYNA);
  } else if (m5 <= 6) {                // П'ЯТЬ ... ПІВ НА ТРЕТЮ
    minute_words(m5, m);
    m.word(NA);
    hour_word(nh, true, m);
  } else {                             // ЗА ДВАДЦЯТЬ П'ЯТЬ ... ЗА П'ЯТЬ ТРЕТЯ
    m.word(ZA);
    minute_words(12 - m5, m);
    hour_word(nh, false, m);
  }
  const int mm = minute % 5;  // "+ 1 ХВИЛИНА", "+ 2..4 ХВИЛИНИ"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    if (mm == 1) m.word(MIN_ONE);
    else { m.word(MIN_STEM); m.glue(MIN_I); }
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"uk","dec":",",
"notime_msg":"Годинник ще не знає часу (немає інтернету або NTP).",
"btn_settime":"Взяти час із телефона/комп'ютера",
"ap_info":"Точка доступу «{ap}» активна. Введіть, будь ласка, свою мережу нижче в розділі <b>Wi-Fi</b>.",
"sec_show":"Відображення","on":"Годинник увімкнено","swMin":"Окремі хвилини (+ 1–4 ХВИЛИНИ)",
"brD":"Яскравість вдень","brN":"Яскравість вночі","cur":"Обмеження струму (мА)",
"hint_show":"Ніч 0 % = дисплей вночі вимкнено. Обмеження струму оберіть відповідно до блока живлення (256 світлодіодів споживають уже в спокої близько 256 мА).",
"sec_col":"Кольори",
"hint_col":"«Випадковий» змінюється щогодини. «Температура»: холодно темно-синій, жовтий, комфорт зелений, помаранчевий, жарко червоний (за шкалою в розділі «Додаткові показники»).",
"g_time":"Час","g_vent":"ПРОВІТРИ","g_alarm":"ТРИВОГА","g_batt":"ЗАРЯД","g_tout":"Температура надворі","g_tin":"Температура в приміщенні",
"pal_0":"Теплий білий","pal_1":"Білий","pal_2":"Червоний","pal_3":"Помаранчевий","pal_4":"Жовтий","pal_5":"Зелений","pal_6":"Синій","pal_7":"Фіолетовий",
"c_random":"Випадковий","c_temp":"Температура","c_pride":"Pride","c_custom":"власний колір",
"sec_fx":"Ефекти",
"fx_rainbow":"Веселка","fx_aurora":"Полярне сяйво","fx_matrix":"Матриця","fx_fire":"Вогонь","fx_confetti":"Конфеті","fx_stars":"Зоряне небо",
"fx_blink":"Блимання","fx_blink_own":"Блимання (власний колір)","stop":"Стоп",
"fxd":"Тривалість ефекту","blk":"Цикл блимання",
"hint_fx":"Тривалість 0 с = працює до «Стоп». Ефекти завжди працюють щонайменше з яскравістю 10 %, навіть уночі при 0 % або коли годинник вимкнено.",
"fx_started":"{fx} запущено","fx_stopped":"Ефект зупинено",
"txt":"Біжучий рядок","txt_ph":"Введіть текст","txt_start":"Показати текст","txt_started":"Текст запущено",
"hint_txt":"Кожна літера заповнює всю матрицю. Триває стільки, скільки ефект (щонайменше один раз), кольором часу (випадковий = веселка). Латинські, грецькі та кириличні літери, цифри, розділові знаки, € і ♥. HTTP: /api/set?text=…",
"sec_sun":"День / ніч","nmode":"Нічний режим","nm_mix":"Змішаний","nm_sun":"Положення сонця","nm_fixed":"Фіксований час",
"lat":"Широта","lon":"Довгота","nso":"Зсув початку ночі (хв)","neo":"Зсув кінця ночі (хв)",
"nme":"Ніч не раніше","nml":"Ніч не пізніше","nfs":"Ніч від","nfe":"Ніч до",
"sunrise":"Схід сонця","sunset":"Захід сонця","night_today":"Ніч сьогодні","now":"Зараз",
"nmh_0":"Зсув: + після, − до заходу чи сходу сонця. Координати, наприклад, із картографічного застосунку (правий клік на місці).",
"nmh_1":"Фіксований час діє щодня.",
"nmh_2":"Ніч починається із заходом сонця (плюс зсув), але не раніше за вказаний час, і закінчується зі сходом сонця (плюс зсув), але не пізніше за вказаний час.",
"day":"День","night":"Ніч",
"sec_extra":"Додаткові показники","tOnl":"Температура надворі з Open-Meteo (місце)",
"scale_out":"Шкала надворі (°C)","scale_in":"Шкала в приміщенні (°C)",
"swExtra":"Показувати СЛАВА УКРАЇНІ",
"apiTo":"Термін дії значень (хв, 0 = завжди)",
"v_out":"Надворі","v_in":"У приміщенні","v_batt":"Акумулятор","v_la":"Провітрювання / тривога","on_":"увімк.","off_":"вимк.",
"hint_extra":"Приміщення, акумулятор, провітрювання і тривога (і надворі без Open-Meteo) надходять ззовні, наприклад через браузер, скрипт або розумний дім:",
"sec_api":"Керування через HTTP",
"hint_api1":"З інших систем через браузер, скрипт або розумний дім (GET або POST на <code>/api/set</code>, можна поєднувати кілька параметрів). Яскравість, кольори й перемикачі зберігаються, ефекти працюють задану тривалість.",
"hint_api2":"Кольори: warmwhite, white, red, orange, yellow, green, blue, violet, random (температура: temp) або rrggbb · Перемикачі: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Ефекти: {fx}, stop · fxcolor: назва кольору або rrggbb. Обмеження струму, Wi-Fi і система лише тут, у вебінтерфейсі.",
"sec_time":"Час","ntpD":"Сервер NTP","ntp_auto":"автоматично (DHCP)","ntp_manual":"вручну","ntp_server":"Сервер",
"ntp_fallback":"Резервний сервер (якщо роутер його не надає, діє після перезапуску)",
"loc":"Місце","loc_custom":"власне місце (координати)","tz_from_loc":"за місцем {city}",
"tz":"Часовий пояс","tz_cet":"Центральна Європа (DE, PL, CZ …)","tz_wet":"Лондон, Лісабон (WET)","tz_eet":"Східна Європа (Київ, Афіни, Бухарест)",
"tz_trt":"Туреччина","tz_eat":"Східна Африка (Танзанія, Кенія)","tz_utc":"UTC",
"tz_use":"США схід","tz_usc":"США центр","tz_usm":"США гори","tz_usw":"США захід",
"tz_wib":"Індонезія (Джакарта)","tz_cst":"Китай","tz_kst":"Корея","tz_jst":"Японія","tz_aus":"Австралія схід",
"tz_custom":"власний (POSIX TZ) …","tz_posix":"Часовий пояс POSIX","ntp_active":"Активний сервер",
"ntp_hint":"Автоматично: сервер від роутера (DHCP), інакше вказаний як резервний. Перемикання між автоматично і вручну перезапускає годинник.",
"ntp_nodhcp":"NTP через DHCP недоступний у цьому пакеті плати – використовується вказаний сервер.",
"sec_wifi":"Wi-Fi","ssid":"Мережа (SSID)","scan":"Шукати мережі","pass":"Пароль","pass_ph":"порожньо = залишити поточний",
"host":"Назва пристрою (http://nazva.local)","save_wifi":"Зберегти і перепідключитися",
"status":"Стан","ip":"IP","last_err":"Остання помилка",
"hint_wifi":"Якщо під час запуску Wi-Fi не знайдено, годинник відкриває точку доступу «{ap}» (без пароля, http://192.168.4.1).",
"w_conn":"підключено до {ssid}","w_ap":"Точка доступу активна ({ip})","w_none":"не підключено",
"scanning":"Пошук …","scan_none":"Мереж не знайдено","scan_err":"Помилка пошуку",
"wr_2":"термін автентифікації минув","wr_15":"неправильний пароль?","wr_201":"мережу не знайдено","wr_202":"автентифікацію відхилено (пароль?)",
"wr_203":"помилка асоціації","wr_204":"неправильний пароль?","wr_205":"помилка з'єднання","wr_8":"від'єднано",
"net_hotspot":"Точка доступу {ap}","net_off":"Wi-Fi від'єднано","net_lost":"немає зв'язку з годинником",
"sec_sys":"Система","mir":"LED 0 спереду праворуч угорі (дзеркально)","srp":"Матриця з'єднана зигзагом",
"restart":"Перезапустити","reset":"Заводські налаштування",
"q_restart":"Перезапустити годинник?","q_reset":"Видалити всі налаштування, включно з Wi-Fi?",
"language":"Мова","firmware":"Прошивка","uptime":"Час роботи","heap":"Вільна пам'ять",
"footer":"{ap} – інструкція зі збирання, код і файли для друку:",
"saved":"Збережено","saved_restart":"Збережено – годинник перезапускається …","save_err":"Помилка збереження",
"time_set":"Час встановлено","restarting":"Годинник перезапускається …",
"srv_no_network":"Мережу не вказано","srv_back":"Назад","srv_saved":"Wi-Fi збережено",
"srv_connecting":"Годинник зараз підключається до мережі","srv_restart":"і для цього перезапускається. Точка доступу зникне.",
"srv_reach":"Потім доступний за адресою","srv_reach2":"або через IP-адресу з роутера чи послідовного монітора.",
"srv_retry":"Якщо підключення не вдасться, точка доступу з'явиться знову приблизно через 30 секунд.",
"srv_not_found":"Не знайдено"
})JSON";
}  // namespace wc_ua
static const WcLangDef WC_LANG = {
    "UA", "Українська", wc_ua::GRID,
    {14, 0, 8},   // ПРОВІТРИ
    {14, 9, 7},   // ТРИВОГА
    {15, 0, 5},   // ЗАРЯД
    {15, 6, 10},  // battery bars
    wc_ua::EXTRA, 4,  // СЛАВА УКРАЇНІ - ГЕРОЯМ СЛАВА
    wc_ua::time_words,
    "slovohodynnyk", "SlovoHodynnyk",
    50.4501f, 30.5234f,  // Київ (Kyiv)
    "EET-2EEST,M3.5.0/3,M10.5.0/4",  // Europe/Kyiv
    "%d.%m.%Y",
    wc_ua::UI_JSON,
};
