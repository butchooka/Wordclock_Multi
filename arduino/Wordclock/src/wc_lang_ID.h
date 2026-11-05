/*
  wc_lang_ID.h - Wordclock 16x16, language file ID (Bahasa Indonesia), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_ID.scad (check: python3 tools/check_lang.py ID).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_ID.txt)
  Satzbau: SEKARANG JAM <Stunde> [LEWAT|KURANG <Minuten>] <Tageszeit>
  :30 SEKARANG JAM SETENGAH <nächste Stunde> („halb vier“). Ab :30 bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 (nichts), :05 LEWAT LIMA, :10 LEWAT SEPULUH, :15 LEWAT SEPEREMPAT, :20 LEWAT DUA PULUH,
  :25 LEWAT DUA PULUH LIMA, :30 SETENGAH <Stunde+1>, :35 KURANG DUA PULUH LIMA, :40 KURANG DUA PULUH,
  :45 KURANG SEPEREMPAT, :50 KURANG SEPULUH, :55 KURANG LIMA
  Stunden (12-Stunden-Zählung): SATU, DUA, TIGA, EMPAT, LIMA, ENAM, TUJUH, DELAPAN, SEMBILAN, SEPULUH,
  SEBELAS, DUA BELAS (BELAS ist das Ende von SEBELAS). Volle Stunde ohne Zusatzwort.
  Tageszeit am Satzende (nach der genannten Stunde): PAGI 4-10 Uhr, SIANG 11-14 Uhr, SORE 15-17 Uhr,
  MALAM 18-3 Uhr; z. B. 12 Uhr JAM DUA BELAS SIANG, 0 Uhr JAM DUA BELAS MALAM, 15:30 JAM SETENGAH EMPAT SORE.
  Im Raster: DUA PULUH = DUA + PULUH (Ende von SEPULUH in der Minutenzeile darunter).
  Minutenzeile: + 1..4 MENIT (Indonesisch hat keine Mehrzahlform, immer MENIT).
  Ersatzwörter: LÜFTEN = VENTILASI („Lüftung“), AKKU = DAYA („Energie“, wie in der Handy-Akkuanzeige;
  BATERAI ist für das Raster zu lang).
  Zusatzwörter (Schalter „Tampilkan SELAMAT DATANG“): SELAMAT DATANG („Willkommen“, Gruß).
  INFO_EN
  Sentence: SEKARANG JAM <hour> [LEWAT|KURANG <minutes>] <time of day>
  :30 SEKARANG JAM SETENGAH <next hour> ("half to four"). From :30 on the time refers to the next hour.
  :00 (nothing), :05 LEWAT LIMA, :10 LEWAT SEPULUH, :15 LEWAT SEPEREMPAT, :20 LEWAT DUA PULUH,
  :25 LEWAT DUA PULUH LIMA, :30 SETENGAH <hour+1>, :35 KURANG DUA PULUH LIMA, :40 KURANG DUA PULUH,
  :45 KURANG SEPEREMPAT, :50 KURANG SEPULUH, :55 KURANG LIMA
  Hours (12-hour count): SATU, DUA, TIGA, EMPAT, LIMA, ENAM, TUJUH, DELAPAN, SEMBILAN, SEPULUH,
  SEBELAS, DUA BELAS (BELAS is the end of SEBELAS). Full hour without extra word.
  Time of day at the end (after the hour said): PAGI 4-10 h, SIANG 11-14 h, SORE 15-17 h, MALAM 18-3 h;
  e.g. 12:00 JAM DUA BELAS SIANG, 0:00 JAM DUA BELAS MALAM, 15:30 JAM SETENGAH EMPAT SORE.
  Grid: DUA PULUH = DUA + PULUH (end of SEPULUH in the minute row below).
  Minute row: + 1..4 MENIT (Indonesian has no plural form, always MENIT).
  Substitute words: VENTILATE = VENTILASI ("ventilation"), BATTERY = DAYA ("power", as in the phone battery
  display; BATERAI is too long for the grid).
  Extra words (switch "Tampilkan SELAMAT DATANG"): SELAMAT DATANG ("welcome", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_id {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*SEKARANGxxxJAM*",
    "*SETENGAHxxSATU*",
    "*DUAxTIGAxEMPAT*",
    "*xLIMAxxxxENAMx*",
    "*TUJUHxxDELAPAN*",
    "*xxxSEMBILANxxx*",
    "*SEPULUHSEBELAS*",
    "*LEWATxxxKURANG*",
    "*SEPEREMPATxDUA*",
    "*SEPULUHxxxLIMA*",
    "*PAGIxxxxxSIANG*",
    "*SORExxxxxMALAM*",
    "*SELAMATxDATANG*",
    "x+x1234xxMENITxx",
    "xVENTILASIxALARM",
    "DAYAxx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord SEKARANG = {0, 1, 8}, JAM = {0, 12, 3}, SETENGAH = {1, 1, 8};
static const WcWord H_DUA = {2, 1, 3}, H_BELAS = {6, 10, 5};  // 12 o'clock: DUA + BELAS (end of SEBELAS)
static const WcWord LEWAT = {7, 1, 5}, KURANG = {7, 9, 6};
static const WcWord M_SEPEREMPAT = {8, 1, 10}, M_DUA = {8, 12, 3};
static const WcWord M_SEPULUH = {9, 1, 7}, M_PULUH = {9, 3, 5}, M_LIMA = {9, 11, 4};  // DUA PULUH = DUA + PULUH
static const WcWord PAGI = {10, 1, 4}, SIANG = {10, 10, 5}, SORE = {11, 1, 4}, MALAM = {11, 10, 5};
// hour 0..11 (index 0 = DUA, only a placeholder: 12 o'clock is DUA BELAS, chosen in time_words)
static const WcWord HOURS[12] = {{2, 1, 3}, {1, 11, 4}, {2, 1, 3}, {2, 5, 4},  {2, 10, 5}, {3, 2, 4},
                                 {3, 10, 4}, {4, 1, 5}, {4, 8, 7}, {5, 4, 8}, {6, 1, 7},  {6, 8, 7}};
// extra words (easter egg): SELAMAT DATANG ("welcome", greeting)
static const WcWord EXTRA[2] = {{12, 1, 7}, {12, 9, 6}};
// row 14: "+ 1 2 3 4  MENIT" (digits in columns 3..6, no plural in Indonesian)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 9, 5};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void minutes_word(int n5, WcMark &m) {  // n5 = 1..5 (5..25 minutes)
  switch (n5) {
    case 1: m.word(M_LIMA); break;
    case 2: m.word(M_SEPULUH); break;
    case 3: m.word(M_SEPEREMPAT); break;
    case 4: m.word(M_DUA); m.word(M_PULUH); break;
    default: m.word(M_DUA); m.word(M_PULUH); m.word(M_LIMA); break;
  }
}
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  const int m5 = minute / 5;
  int h = hour % 24;
  if (m5 >= 6) h = (h + 1) % 24;  // from "setengah" on the next hour counts
  m.word(SEKARANG);
  m.word(JAM);
  if (!valid) return;  // no time: only the prefix
  if (m5 == 6) m.word(SETENGAH);  // SETENGAH EMPAT = 3:30
  if (h % 12 == 0) { m.word(H_DUA); m.word(H_BELAS); }  // DUA BELAS
  else m.word(HOURS[h % 12]);
  if (m5 >= 1 && m5 <= 5) { m.word(LEWAT); minutes_word(m5, m); }
  else if (m5 >= 7) { m.word(KURANG); minutes_word(12 - m5, m); }
  // time of day of the hour said
  if (h >= 4 && h <= 10) m.word(PAGI);
  else if (h >= 11 && h <= 14) m.word(SIANG);
  else if (h >= 15 && h <= 17) m.word(SORE);
  else m.word(MALAM);
  const int mm = minute % 5;  // "+ 1..4 MENIT"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(MIN_WORD);
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"id","dec":",",
"notime_msg":"Jam belum memiliki waktu (tidak ada internet atau NTP).",
"btn_settime":"Ambil waktu dari ponsel/PC",
"ap_info":"Hotspot “{ap}” aktif. Silakan masukkan jaringan Anda di bawah pada <b>Wi-Fi</b>.",
"sec_show":"Tampilan","on":"Jam menyala","swMin":"Menit tunggal (+ 1–4 MENIT)",
"brD":"Kecerahan siang","brN":"Kecerahan malam","cur":"Batas arus (mA)",
"hint_show":"Malam 0 % = tampilan mati pada malam hari. Sesuaikan batas arus dengan catu daya (256 LED sudah memerlukan sekitar 256 mA arus diam).",
"sec_col":"Warna",
"hint_col":"“Acak” berganti setiap jam penuh. “Suhu”: dingin biru tua, kuning, nyaman hijau, oranye, panas merah (sesuai skala pada tampilan tambahan).",
"g_time":"Waktu","g_vent":"VENTILASI","g_alarm":"ALARM","g_batt":"DAYA","g_tout":"Suhu luar","g_tin":"Suhu dalam",
"pal_0":"Putih hangat","pal_1":"Putih","pal_2":"Merah","pal_3":"Oranye","pal_4":"Kuning","pal_5":"Hijau","pal_6":"Biru","pal_7":"Ungu",
"c_random":"Acak","c_temp":"Suhu","c_pride":"Pride","c_custom":"warna sendiri",
"sec_fx":"Efek",
"fx_rainbow":"Pelangi","fx_aurora":"Aurora","fx_matrix":"Matrix","fx_fire":"Api","fx_confetti":"Konfeti","fx_stars":"Langit berbintang",
"fx_blink":"Berkedip","fx_blink_own":"Berkedip (warna sendiri)","stop":"Berhenti",
"fxd":"Durasi efek","blk":"Siklus kedip",
"hint_fx":"Durasi 0 s = berjalan sampai “Berhenti”. Efek selalu berjalan dengan kecerahan minimal 10 %, juga pada malam hari dengan 0 % atau saat jam dimatikan.",
"fx_started":"{fx} dimulai","fx_stopped":"Efek dihentikan",
"txt":"Teks berjalan","txt_ph":"Masukkan teks","txt_start":"Tampilkan teks","txt_started":"Teks dimulai",
"hint_txt":"Setiap huruf memenuhi seluruh matriks. Berjalan selama durasi efek (minimal sekali), dengan warna jam (acak = pelangi). Huruf Latin, Yunani dan Kiril, angka, tanda baca, € dan ♥. HTTP: /api/set?text=…",
"sec_sun":"Siang / malam","nmode":"Mode malam","nm_mix":"Campuran","nm_sun":"Posisi matahari","nm_fixed":"Waktu tetap",
"lat":"Lintang","lon":"Bujur","nso":"Selisih awal malam (menit)","neo":"Selisih akhir malam (menit)",
"nme":"Malam tidak sebelum","nml":"Malam tidak setelah","nfs":"Malam dari","nfe":"Malam sampai",
"sunrise":"Matahari terbit","sunset":"Matahari terbenam","night_today":"Malam hari ini","now":"Sekarang",
"nmh_0":"Selisih: + setelah, − sebelum matahari terbenam atau terbit. Koordinat misalnya dari aplikasi peta (klik kanan pada tempat).",
"nmh_1":"Waktu tetap berlaku setiap hari.",
"nmh_2":"Malam dimulai saat matahari terbenam (ditambah selisih), tetapi tidak sebelum waktu yang ditetapkan, dan berakhir saat matahari terbit (ditambah selisih), tetapi tidak setelah waktu yang ditetapkan.",
"day":"Siang","night":"Malam",
"sec_extra":"Tampilan tambahan","tOnl":"Suhu luar dari Open-Meteo (lokasi)",
"scale_out":"Skala luar (°C)","scale_in":"Skala dalam (°C)",
"swExtra":"Tampilkan SELAMAT DATANG",
"apiTo":"Nilai berlaku selama (menit, 0 = selalu)",
"v_out":"Luar","v_in":"Dalam","v_batt":"Baterai","v_la":"Ventilasi / alarm","on_":"nyala","off_":"mati",
"hint_extra":"Dalam, baterai, ventilasi dan alarm (serta luar, jika tanpa Open-Meteo) datang dari luar, misalnya melalui browser, skrip atau rumah pintar:",
"sec_api":"Kontrol HTTP",
"hint_api1":"Dari sistem lain melalui browser, skrip atau rumah pintar (GET atau POST ke <code>/api/set</code>, beberapa parameter dapat digabungkan). Kecerahan, warna dan sakelar disimpan, efek berjalan selama durasi yang ditetapkan.",
"hint_api2":"Warna: warmwhite, white, red, orange, yellow, green, blue, violet, random (suhu: temp) atau rrggbb · Sakelar: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Efek: {fx}, stop · fxcolor: nama warna atau rrggbb. Batas arus, Wi-Fi dan sistem hanya di sini pada antarmuka web.",
"sec_time":"Waktu","ntpD":"Server NTP","ntp_auto":"otomatis (DHCP)","ntp_manual":"manual","ntp_server":"Server",
"ntp_fallback":"Server cadangan (jika router tidak menyediakan, berlaku setelah mulai ulang)",
"loc":"Lokasi","loc_custom":"lokasi sendiri (koordinat)","tz_from_loc":"dari lokasi {city}",
"tz":"Zona waktu","tz_cet":"Eropa Tengah (DE, AT, CH …)","tz_wet":"London, Lisboa (WET)","tz_eet":"Eropa Timur (Kyiv, Athena, Bukares)",
"tz_trt":"Turki","tz_eat":"Afrika Timur (Tanzania, Kenya)","tz_utc":"UTC",
"tz_use":"AS Timur","tz_usc":"AS Tengah","tz_usm":"AS Pegunungan","tz_usw":"AS Barat",
"tz_wib":"Indonesia (Jakarta, WIB)","tz_cst":"Tiongkok","tz_kst":"Korea","tz_jst":"Jepang","tz_aus":"Australia Timur",
"tz_custom":"sendiri (POSIX TZ) …","tz_posix":"Zona waktu POSIX","ntp_active":"Server aktif",
"ntp_hint":"Otomatis: server dari router (DHCP), jika tidak ada, server yang dimasukkan sebagai cadangan. Beralih antara otomatis dan manual memulai ulang jam.",
"ntp_nodhcp":"NTP melalui DHCP tidak tersedia pada paket board ini – server yang dimasukkan digunakan.",
"sec_wifi":"Wi-Fi","ssid":"Jaringan (SSID)","scan":"Cari jaringan","pass":"Kata sandi","pass_ph":"kosongkan = pertahankan yang sekarang",
"host":"Nama perangkat (http://nama.local)","save_wifi":"Simpan & sambungkan ulang",
"status":"Status","ip":"IP","last_err":"Kesalahan terakhir",
"hint_wifi":"Jika Wi-Fi tidak ditemukan saat mulai, jam membuka hotspot “{ap}” (tanpa kata sandi, http://192.168.4.1).",
"w_conn":"tersambung ke {ssid}","w_ap":"Hotspot aktif ({ip})","w_none":"tidak tersambung",
"scanning":"Mencari …","scan_none":"Tidak ada jaringan ditemukan","scan_err":"Pencarian gagal",
"wr_2":"autentikasi kedaluwarsa","wr_15":"kata sandi salah?","wr_201":"jaringan tidak ditemukan","wr_202":"autentikasi ditolak (kata sandi?)",
"wr_203":"asosiasi gagal","wr_204":"kata sandi salah?","wr_205":"sambungan gagal","wr_8":"terputus",
"net_hotspot":"Hotspot {ap}","net_off":"Wi-Fi terputus","net_lost":"tidak ada sambungan ke jam",
"sec_sys":"Sistem","mir":"LED 0 depan kanan atas (cermin)","srp":"Matriks dirangkai zigzag",
"restart":"Mulai ulang","reset":"Setelan pabrik",
"q_restart":"Mulai ulang jam?","q_reset":"Hapus semua pengaturan termasuk Wi-Fi?",
"language":"Bahasa","firmware":"Firmware","uptime":"Waktu aktif","heap":"Memori bebas",
"footer":"{ap} – panduan perakitan, kode dan file cetak:",
"saved":"Tersimpan","saved_restart":"Tersimpan – jam dimulai ulang …","save_err":"Kesalahan saat menyimpan",
"time_set":"Waktu diambil alih","restarting":"Jam dimulai ulang …",
"srv_no_network":"Tidak ada jaringan yang dimasukkan","srv_back":"Kembali","srv_saved":"Wi-Fi tersimpan",
"srv_connecting":"Jam sekarang menyambung ke","srv_restart":"dan dimulai ulang untuk itu. Hotspot menghilang.",
"srv_reach":"Setelah itu dapat diakses di","srv_reach2":"atau melalui alamat IP dari router atau monitor serial.",
"srv_retry":"Jika sambungan gagal, hotspot muncul kembali setelah sekitar 30 detik.",
"srv_not_found":"Tidak ditemukan"
})JSON";
}  // namespace wc_id
static const WcLangDef WC_LANG = {
    "ID", "Bahasa Indonesia", wc_id::GRID,
    {14, 1, 9},   // VENTILASI
    {14, 11, 5},  // ALARM
    {15, 0, 4},   // DAYA
    {15, 6, 10},  // battery bars
    wc_id::EXTRA, 2,  // SELAMAT DATANG
    wc_id::time_words,
    "jamkata", "JamKata",
    -6.2088f, 106.8456f,  // Jakarta
    "WIB-7",              // Asia/Jakarta
    "%d/%m/%Y",
    wc_id::UI_JSON,
};
