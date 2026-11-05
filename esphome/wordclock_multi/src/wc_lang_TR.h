/*
  wc_lang_TR.h - Wordclock 16x16, language file TR (Türkçe), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_TR.scad (check: python3 tools/check_lang.py TR).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_TR.txt)
  Satzbau: SAAT <Stunde>[Akkusativ] <Minuten> GEÇİYOR | SAAT <Stunde>[Dativ] <Minuten> VAR |
  SAAT <Stunde> BUÇUK | SAAT <Stunde> (gängige Umgangsform, 12-Stunden-Zählung).
  Ab :35 (VAR = „es fehlen noch“) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 <Stunde>, :05 <Stunde-Akk.> BEŞ GEÇİYOR, :10 ON GEÇİYOR, :15 ÇEYREK GEÇİYOR, :20 YİRMİ GEÇİYOR,
  :25 YİRMİ BEŞ GEÇİYOR, :30 <Stunde> BUÇUK, :35 <nächste Stunde-Dat.> YİRMİ BEŞ VAR, :40 YİRMİ VAR,
  :45 ÇEYREK VAR, :50 ON VAR, :55 BEŞ VAR
  Beispiele: 3:05 SAAT ÜÇÜ BEŞ GEÇİYOR, 3:30 SAAT ÜÇ BUÇUK, 3:45 SAAT DÖRDE ÇEYREK VAR.
  Stunden (Grundform / Akkusativ / Dativ): BİR/BİRİ/BİRE, İKİ/İKİYİ/İKİYE, ÜÇ/ÜÇÜ/ÜÇE,
  DÖRT/DÖRDÜ/DÖRDE, BEŞ/BEŞİ/BEŞE, ALTI/ALTIYI/ALTIYA, YEDİ/YEDİYİ/YEDİYE, SEKİZ/SEKİZİ/SEKİZE,
  DOKUZ/DOKUZU/DOKUZA, ON/ONU/ONA, ON BİR/ON BİRİ/ON BİRE, ON İKİ/ON İKİYİ/ON İKİYE.
  Im Raster steht die Endung direkt hinter dem Wort (z. B. „ÜÇÜE“): Akkusativ = zusammenhängend (ÜÇÜ),
  Dativ = Stamm + letzter Buchstabe (ÜÇ + E = ÜÇE, ein Buchstabe Lücke). DÖRT hat für die Endungen ein
  eigenes Wort „DÖRDÜE“ (t wird zu d). ON von „ONUA“ ist auch der Zehner von ON BİR und ON İKİ.
  0 und 12 Uhr = ON İKİ. Keine Wörter für Mitternacht/Mittag.
  Minutenzeile: + 1..4 DAKİKA (im Türkischen steht nach Zahlen immer die Einzahl).
  Statuswörter: LÜFTEN = HAVALANDIR, ALARM = ALARM, AKKU = PİL.
  Zusatzwörter (Schalter „VAKİT NAKİTTİR göster“): VAKİT NAKİTTİR („Zeit ist Geld“, Sprichwort).
  Sonderzeichen: Ç, Ö, Ü, Ş, İ (großes I mit Punkt; I ohne Punkt ist das normale I, z. B. ALTI).
  INFO_EN
  Sentence: SAAT <hour>[accusative] <minutes> GEÇİYOR | SAAT <hour>[dative] <minutes> VAR |
  SAAT <hour> BUÇUK | SAAT <hour> (common spoken form, 12-hour counting).
  From :35 on (VAR = "there are ... left") the time refers to the next hour.
  :00 <hour>, :05 <hour-acc.> BEŞ GEÇİYOR, :10 ON GEÇİYOR, :15 ÇEYREK GEÇİYOR, :20 YİRMİ GEÇİYOR,
  :25 YİRMİ BEŞ GEÇİYOR, :30 <hour> BUÇUK, :35 <next hour-dat.> YİRMİ BEŞ VAR, :40 YİRMİ VAR,
  :45 ÇEYREK VAR, :50 ON VAR, :55 BEŞ VAR
  Examples: 3:05 SAAT ÜÇÜ BEŞ GEÇİYOR, 3:30 SAAT ÜÇ BUÇUK, 3:45 SAAT DÖRDE ÇEYREK VAR.
  Hours (basic form / accusative / dative): BİR/BİRİ/BİRE, İKİ/İKİYİ/İKİYE, ÜÇ/ÜÇÜ/ÜÇE,
  DÖRT/DÖRDÜ/DÖRDE, BEŞ/BEŞİ/BEŞE, ALTI/ALTIYI/ALTIYA, YEDİ/YEDİYİ/YEDİYE, SEKİZ/SEKİZİ/SEKİZE,
  DOKUZ/DOKUZU/DOKUZA, ON/ONU/ONA, ON BİR/ON BİRİ/ON BİRE, ON İKİ/ON İKİYİ/ON İKİYE.
  In the grid the ending follows the word directly (e.g. "ÜÇÜE"): accusative = contiguous (ÜÇÜ),
  dative = stem + last letter (ÜÇ + E = ÜÇE, one letter gap). DÖRT has its own word "DÖRDÜE" for the
  endings (t becomes d). ON of "ONUA" is also the tens of ON BİR and ON İKİ.
  0 and 12 o'clock = ON İKİ. No words for midnight/noon.
  Minute row: + 1..4 DAKİKA (Turkish always uses the singular after numbers).
  Status words: VENTILATE = HAVALANDIR, ALARM = ALARM, BATTERY = PİL.
  Extra words (switch "VAKİT NAKİTTİR göster"): VAKİT NAKİTTİR ("time is money", proverb).
  Special letters: Ç, Ö, Ü, Ş, İ (capital I with dot; the dotless I is the normal I, e.g. ALTI).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_tr {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*SAATxONUAxÜÇÜE*",
    "*xBİRİExİKİYİEx*",
    "*xDÖRTxxALTIYIA*",
    "*DÖRDÜExSEKİZİE*",
    "*BEŞİExxYEDİYİE*",
    "*xxxDOKUZUAxxxx*",
    "*xxxxxBUÇUKxxxx*",
    "*xÇEYREKxYİRMİx*",
    "*xxxBEŞxxxONxxx*",
    "*xxxGEÇİYORxxxx*",
    "*xxxxxxVARxxxxx*",
    "*xxxxVAKİTxxxxx*",
    "*xxxNAKİTTİRxxx*",
    "x+x1234xDAKİKAxx",
    "HAVALANDIRxALARM",
    "xPİLxx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord SAAT = {0, 1, 4}, H_ON = {0, 6, 2};  // H_ON: tens of ON BİR / ON İKİ
static const WcWord BUCUK = {6, 6, 5}, GECIYOR = {9, 4, 7}, VAR = {10, 7, 3};
static const WcWord M_BES = {8, 4, 3}, M_ON = {8, 10, 2}, M_CEYREK = {7, 2, 6}, M_YIRMI = {7, 9, 5};
// hour 0..11 (0 = ON İKİ, 11 = ON BİR: H_ON + the forms of İKİ / BİR)
// basic form (:00, :30)
static const WcWord H_NOM[12] = {{1, 8, 3}, {1, 2, 3}, {1, 8, 3}, {0, 11, 2}, {2, 2, 4}, {4, 1, 3},
                                 {2, 8, 4}, {4, 8, 4}, {3, 8, 5}, {5, 4, 5},  {0, 6, 2}, {1, 2, 3}};
// accusative (:05-:25), contiguous: İKİYİ BİRİ İKİYİ ÜÇÜ DÖRDÜ BEŞİ ALTIYI YEDİYİ SEKİZİ DOKUZU ONU BİRİ
static const WcWord H_ACC[12] = {{1, 8, 5}, {1, 2, 4}, {1, 8, 5}, {0, 11, 3}, {3, 1, 5}, {4, 1, 4},
                                 {2, 8, 6}, {4, 8, 6}, {3, 8, 6}, {5, 4, 6},  {0, 6, 3}, {1, 2, 4}};
// dative (:35-:55) = stem + glued last letter: İKİY+E BİR+E İKİY+E ÜÇ+E DÖRD+E BEŞ+E ALTIY+A YEDİY+E
// SEKİZ+E DOKUZ+A ON+A BİR+E
static const WcWord H_DATS[12] = {{1, 8, 4}, {1, 2, 3}, {1, 8, 4}, {0, 11, 2}, {3, 1, 4}, {4, 1, 3},
                                  {2, 8, 5}, {4, 8, 5}, {3, 8, 5}, {5, 4, 5},  {0, 6, 2}, {1, 2, 3}};
static const WcWord H_DATE[12] = {{1, 13, 1}, {1, 6, 1}, {1, 13, 1}, {0, 14, 1}, {3, 6, 1}, {4, 5, 1},
                                  {2, 14, 1}, {4, 14, 1}, {3, 14, 1}, {5, 10, 1}, {0, 9, 1}, {1, 6, 1}};
// extra words (easter egg): VAKİT NAKİTTİR ("time is money")
static const WcWord EXTRA[2] = {{11, 5, 5}, {12, 4, 8}};
// row 14: "+ 1 2 3 4  DAKİKA" (digits in columns 3..6, always singular)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 6};  // DAKİKA
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
// 0 = basic form, 1 = accusative, 2 = dative
static inline void hour_word(int h, int form, WcMark &m) {
  if (h == 0 || h == 11) m.word(H_ON);  // ON İKİ / ON BİR
  if (form == 1) m.word(H_ACC[h]);
  else if (form == 2) { m.word(H_DATS[h]); m.glue(H_DATE[h]); }
  else m.word(H_NOM[h]);
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(SAAT);
  if (!valid) return;
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 7) h = (h + 1) % 12;  // from "yirmi beş var" on the next hour counts
  switch (m5) {
    case 0: hour_word(h, 0, m); break;
    case 1: hour_word(h, 1, m); m.word(M_BES); m.word(GECIYOR); break;
    case 2: hour_word(h, 1, m); m.word(M_ON); m.word(GECIYOR); break;
    case 3: hour_word(h, 1, m); m.word(M_CEYREK); m.word(GECIYOR); break;
    case 4: hour_word(h, 1, m); m.word(M_YIRMI); m.word(GECIYOR); break;
    case 5: hour_word(h, 1, m); m.word(M_YIRMI); m.word(M_BES); m.word(GECIYOR); break;
    case 6: hour_word(h, 0, m); m.word(BUCUK); break;
    case 7: hour_word(h, 2, m); m.word(M_YIRMI); m.word(M_BES); m.word(VAR); break;
    case 8: hour_word(h, 2, m); m.word(M_YIRMI); m.word(VAR); break;
    case 9: hour_word(h, 2, m); m.word(M_CEYREK); m.word(VAR); break;
    case 10: hour_word(h, 2, m); m.word(M_ON); m.word(VAR); break;
    default: hour_word(h, 2, m); m.word(M_BES); m.word(VAR); break;
  }
  const int mm = minute % 5;  // "+ 1..4 DAKİKA" (singular after numbers)
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_WORD);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"tr","dec":",",
"notime_msg":"Saat henüz zamanı bilmiyor (internet veya NTP yok).",
"btn_settime":"Saati telefondan/bilgisayardan al",
"ap_info":"“{ap}” erişim noktası etkin. Lütfen ağınızı aşağıda <b>Wi-Fi</b> bölümüne girin.",
"sec_show":"Ekran","on":"Saat açık","swMin":"Tek dakikalar (+ 1–4 DAKİKA)",
"brD":"Gündüz parlaklığı","brN":"Gece parlaklığı","cur":"Akım sınırı (mA)",
"hint_show":"Gece %0 = ekran gece kapalı. Akım sınırını güç kaynağına göre seçin (256 LED boşta bile yaklaşık 256 mA çeker).",
"sec_col":"Renkler",
"hint_col":"“Rastgele” her tam saatte değişir. “Sıcaklık”: soğuk koyu mavi, sarı, konfor yeşil, turuncu, sıcak kırmızı (ek göstergelerdeki ölçeğe göre).",
"g_time":"Saat","g_vent":"HAVALANDIR","g_alarm":"ALARM","g_batt":"PİL","g_tout":"Dış sıcaklık","g_tin":"İç sıcaklık",
"pal_0":"Sıcak beyaz","pal_1":"Beyaz","pal_2":"Kırmızı","pal_3":"Turuncu","pal_4":"Sarı","pal_5":"Yeşil","pal_6":"Mavi","pal_7":"Mor",
"c_random":"Rastgele","c_temp":"Sıcaklık","c_pride":"Pride","c_custom":"özel renk",
"sec_fx":"Efektler",
"fx_rainbow":"Gökkuşağı","fx_aurora":"Kutup ışıkları","fx_matrix":"Matrix","fx_fire":"Ateş","fx_confetti":"Konfeti","fx_stars":"Yıldızlı gökyüzü",
"fx_blink":"Yanıp sönme","fx_blink_own":"Yanıp sönme (özel renk)","stop":"Durdur",
"fxd":"Efekt süresi","blk":"Yanıp sönme döngüsü",
"hint_fx":"Süre 0 sn = “Durdur”a kadar çalışır. Efektler her zaman en az %10 parlaklıkla çalışır, gece %0 iken veya saat kapalıyken bile.",
"fx_started":"{fx} başlatıldı","fx_stopped":"Efekt durduruldu",
"txt":"Kayan yazı","txt_ph":"Metin girin","txt_start":"Metni göster","txt_started":"Metin başlatıldı",
"hint_txt":"Her harf tüm matrisi doldurur. Efekt süresi boyunca (en az bir kez), saatin renginde (rastgele = gökkuşağı) gösterilir. Latin, Yunan ve Kiril harfleri, rakamlar, noktalama işaretleri, € ve ♥. HTTP: /api/set?text=…",
"sec_sun":"Gündüz / gece","nmode":"Gece modu","nm_mix":"Karma","nm_sun":"Güneşin konumu","nm_fixed":"Sabit saatler",
"lat":"Enlem","lon":"Boylam","nso":"Gece başlangıcı kayması (dk)","neo":"Gece bitişi kayması (dk)",
"nme":"Gece en erken","nml":"Gece en geç","nfs":"Gece başlangıcı","nfe":"Gece bitişi",
"sunrise":"Gün doğumu","sunset":"Gün batımı","night_today":"Bu gece","now":"Şimdi",
"nmh_0":"Kayma: + gün batımı veya gün doğumundan sonra, − önce. Koordinatlar örn. bir harita uygulamasından (yere sağ tıklayın).",
"nmh_1":"Sabit saatler her gün geçerlidir.",
"nmh_2":"Gece gün batımında (kayma dahil) başlar, ancak ayarlanan saatten önce değil; gün doğumunda (kayma dahil) biter, ancak ayarlanan saatten sonra değil.",
"day":"Gündüz","night":"Gece",
"sec_extra":"Ek göstergeler","tOnl":"Dış sıcaklık Open-Meteo'dan (konum)",
"scale_out":"Dış ölçek (°C)","scale_in":"İç ölçek (°C)",
"swExtra":"VAKİT NAKİTTİR göster",
"apiTo":"Değerlerin geçerlilik süresi (dk, 0 = her zaman)",
"v_out":"Dış","v_in":"İç","v_batt":"Pil","v_la":"Havalandır / alarm","on_":"açık","off_":"kapalı",
"hint_extra":"İç, pil, havalandır ve alarm (Open-Meteo kullanılmıyorsa dış da) dışarıdan gelir, örn. tarayıcı, betik veya akıllı ev üzerinden:",
"sec_api":"HTTP kontrolü",
"hint_api1":"Diğer sistemlerden tarayıcı, betik veya akıllı ev üzerinden (<code>/api/set</code> adresine GET veya POST, birden fazla parametre birleştirilebilir). Parlaklık, renkler ve anahtarlar kaydedilir, efektler ayarlanan süre boyunca çalışır.",
"hint_api2":"Renkler: warmwhite, white, red, orange, yellow, green, blue, violet, random (sıcaklık: temp) veya rrggbb · Anahtarlar: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Efektler: {fx}, stop · fxcolor: renk adı veya rrggbb. Akım sınırı, Wi-Fi ve sistem yalnızca burada, web arayüzünde.",
"sec_time":"Saat","ntpD":"NTP sunucusu","ntp_auto":"otomatik (DHCP)","ntp_manual":"elle","ntp_server":"Sunucu",
"ntp_fallback":"Yedek sunucu (yönlendirici sağlamazsa, yeniden başlatmadan sonra geçerli)",
"loc":"Konum","loc_custom":"özel konum (koordinatlar)","tz_from_loc":"{city} konumundan",
"tz":"Saat dilimi","tz_cet":"Orta Avrupa (DE, AT, CH …)","tz_wet":"Londra, Lizbon (WET)","tz_eet":"Doğu Avrupa (Kiev, Atina, Bükreş)",
"tz_trt":"Türkiye","tz_eat":"Doğu Afrika (Tanzanya, Kenya)","tz_utc":"UTC",
"tz_use":"ABD Doğu","tz_usc":"ABD Orta","tz_usm":"ABD Dağ","tz_usw":"ABD Batı",
"tz_wib":"Endonezya (Cakarta)","tz_cst":"Çin","tz_kst":"Kore","tz_jst":"Japonya","tz_aus":"Avustralya Doğu",
"tz_custom":"özel (POSIX TZ) …","tz_posix":"POSIX saat dilimi","ntp_active":"Etkin sunucu",
"ntp_hint":"Otomatik: yönlendiriciden gelen sunucu (DHCP), yoksa girilen sunucu yedek olarak. Otomatik ve elle arasında geçiş saati yeniden başlatır.",
"ntp_nodhcp":"Bu kart paketinde DHCP üzerinden NTP mevcut değil – girilen sunucu kullanılır.",
"sec_wifi":"Wi-Fi","ssid":"Ağ (SSID)","scan":"Ağları ara","pass":"Şifre","pass_ph":"boş bırak = mevcut kalsın",
"host":"Cihaz adı (http://ad.local)","save_wifi":"Kaydet ve yeniden bağlan",
"status":"Durum","ip":"IP","last_err":"Son hata",
"hint_wifi":"Açılışta Wi-Fi bulunamazsa saat “{ap}” erişim noktasını açar (şifresiz, http://192.168.4.1).",
"w_conn":"{ssid} ağına bağlı","w_ap":"Erişim noktası etkin ({ip})","w_none":"bağlı değil",
"scanning":"Aranıyor …","scan_none":"Ağ bulunamadı","scan_err":"Arama başarısız",
"wr_2":"kimlik doğrulama süresi doldu","wr_15":"yanlış şifre?","wr_201":"ağ bulunamadı","wr_202":"kimlik doğrulama reddedildi (şifre?)",
"wr_203":"ilişkilendirme başarısız","wr_204":"yanlış şifre?","wr_205":"bağlantı başarısız","wr_8":"bağlantı kesildi",
"net_hotspot":"Erişim noktası {ap}","net_off":"Wi-Fi bağlantısı kesildi","net_lost":"saate bağlantı yok",
"sec_sys":"Sistem","mir":"LED 0 önden sağ üstte (ayna)","srp":"Matris zikzak bağlı",
"restart":"Yeniden başlat","reset":"Fabrika ayarları",
"q_restart":"Saat yeniden başlatılsın mı?","q_reset":"Wi-Fi dahil tüm ayarlar silinsin mi?",
"language":"Dil","firmware":"Yazılım","uptime":"Çalışma süresi","heap":"Boş bellek",
"footer":"{ap} – yapım kılavuzu, kod ve baskı dosyaları:",
"saved":"Kaydedildi","saved_restart":"Kaydedildi – saat yeniden başlıyor …","save_err":"Kaydetme hatası",
"time_set":"Saat alındı","restarting":"Saat yeniden başlıyor …",
"srv_no_network":"Ağ girilmedi","srv_back":"Geri","srv_saved":"Wi-Fi kaydedildi",
"srv_connecting":"Saat şimdi şu ağa bağlanıyor:","srv_restart":"ve bunun için yeniden başlıyor. Erişim noktası kaybolur.",
"srv_reach":"Ardından şu adresten erişilebilir:","srv_reach2":"veya yönlendiriciden ya da seri monitörden alınan IP adresiyle.",
"srv_retry":"Bağlantı başarısız olursa erişim noktası yaklaşık 30 saniye sonra yeniden görünür.",
"srv_not_found":"Bulunamadı"
})JSON";
}  // namespace wc_tr
static const WcLangDef WC_LANG = {
    "TR", "Türkçe", wc_tr::GRID,
    {14, 0, 10},  // HAVALANDIR
    {14, 11, 5},  // ALARM
    {15, 1, 3},   // PİL
    {15, 6, 10},  // battery bars
    wc_tr::EXTRA, 2,  // VAKİT NAKİTTİR
    wc_tr::time_words,
    "kelimesaati", "KelimeSaati",
    39.9334f, 32.8597f,  // Ankara
    "<+03>-3",           // Europe/Istanbul
    "%d.%m.%Y",
    wc_tr::UI_JSON,
};
