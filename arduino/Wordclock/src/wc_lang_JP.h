/*
  wc_lang_JP.h - Wordclock 16x16, language file JP (日本語 / Japanese), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_JP.scad (check: python3 tools/check_lang.py JP).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_JP.txt)
  Satzbau (Standardform wie bei Zeitansagen, 12-Stunden-Zählung mit 午前/午後, immer auf die laufende Stunde):
  今は [午前 | 午後] <Stunde>時 [<Minuten>分 | 半] [ちょうど]です („jetzt ist es [vormittags | nachmittags] … Uhr …“).
  Stunden und Minuten werden mit Kanji-Zahlen geschrieben; es gibt keinen Bezug auf die nächste Stunde
  (die Form „… 分前“ = „vor“ ist umgangssprachlich und wird nicht verwendet) und keine Viertel.
  :30 = 半 („halb“, nachgestellt: 三時半 = 3:30).
  :00 <Stunde>時ちょうど, :05 <Stunde>時五分, :10 十分, :15 十五分, :20 二十分, :25 二十五分, :30 半,
  :35 三十五分, :40 四十分, :45 四十五分, :50 五十分, :55 五十五分
  Die Minutenzahlen werden aus Zehnerziffer (二, 三, 四, 五) + 十 + Einer 五 zusammengesetzt.
  ちょうど („genau“) leuchtet nur zur vollen Minute :00, bei :01-:04 steht <Stunde>時です + Einzelminuten.
  Japanisch schreibt ohne Leerzeichen; der Text wird ohne Leerzeichen zusammengesetzt (nur vor „+ 2分“).
  Beispiele: 3:00 今は午前三時ちょうどです, 3:05 今は午前三時五分です, 15:30 今は午後三時半です,
  21:55 今は午後九時五十五分です.
  Stunden: 零, 一, 二, 三, 四, 五, 六, 七, 八, 九, 十, 十一 (Zählung 0-11 wie bei NHK und Bahn:
  0:05 = 午前零時五分, 12:05 = 午後零時五分). 午前 („vormittags“) 0:00-11:59, 午後 („nachmittags“) 12:05-23:59.
  Sonderfall: 12:00-12:04 今は正午です = „Mittag“ (ohne 午後, 時 und ちょうど). 0:00 = 今は午前零時ちょうどです.
  Ohne gültige Uhrzeit leuchtet nur 今は.
  Minutenzeile: + 1..4 分 (im Japanischen keine Mehrzahl; im Text „+ 2分“).
  Statuswörter: LÜFTEN = 換気 („Lüftung“), ALARM = アラーム, AKKU = 電池 („Batterie“).
  Zusatzwörter (Schalter „「時は金なり」を表示“): 時は金なり („Zeit ist Geld“, Sprichwort).
  Schrift: Kanji, Hiragana und Katakana (je ein Zeichen = ein Feld) mit eigener Schrift Noto Sans JP Bold
  (lang_JP.scad); die Zeichen werden nur grob zentriert (keine Metriken). Füllfelder als Punkt (lang_JP.scad: Feld 6 = dot, gilt mit FILLER = auto).
  INFO_EN
  Sentence (standard form as in time announcements, 12-hour counting with 午前/午後, always the current hour):
  今は [午前 | 午後] <hour>時 [<minutes>分 | 半] [ちょうど]です ("now it is [a.m. | p.m.] … o'clock …").
  Hours and minutes are written with kanji numbers; there is no reference to the next hour (the form
  "… 分前" = "to" is colloquial and not used) and no quarters. :30 = 半 ("half", after the hour: 三時半 = 3:30).
  :00 <hour>時ちょうど, :05 <hour>時五分, :10 十分, :15 十五分, :20 二十分, :25 二十五分, :30 半,
  :35 三十五分, :40 四十分, :45 四十五分, :50 五十分, :55 五十五分
  The minute numbers are made of the tens digit (二, 三, 四, 五) + 十 + unit 五.
  ちょうど ("exactly") is lit only at the full minute :00, at :01-:04 it reads <hour>時です + single minutes.
  Japanese is written without spaces; the text is joined without spaces (only before "+ 2分").
  Examples: 3:00 今は午前三時ちょうどです, 3:05 今は午前三時五分です, 15:30 今は午後三時半です,
  21:55 今は午後九時五十五分です.
  Hours: 零, 一, 二, 三, 四, 五, 六, 七, 八, 九, 十, 十一 (counting 0-11 as used by NHK and the railways:
  0:05 = 午前零時五分, 12:05 = 午後零時五分). 午前 ("a.m.") 0:00-11:59, 午後 ("p.m.") 12:05-23:59.
  Special case: 12:00-12:04 今は正午です = "noon" (without 午後, 時 and ちょうど). 0:00 = 今は午前零時ちょうどです.
  Without a valid time only 今は is lit.
  Minute row: + 1..4 分 (Japanese has no plural; in the text "+ 2分").
  Status words: VENTILATE = 換気 ("ventilation"), ALARM = アラーム, BATTERY = 電池.
  Extra words (switch "「時は金なり」を表示"): 時は金なり ("time is money", proverb).
  Font: kanji, hiragana and katakana (one character = one cell) with the own font Noto Sans JP Bold
  (lang_JP.scad); the characters are only roughly centred (no metrics). Fillers as dots (lang_JP.scad: field 6 = dot, used with FILLER = auto).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_jp {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xx今はxx正午前x午後xx*",
    "*xx零xxx一xxx二xxx*",
    "*xx三xxx四xxx五xxx*",
    "*xx六xxx七xxx八xxx*",
    "*xx九xxx十一xxxxxx*",
    "*xxxxx時xxx半xxxx*",
    "*xx二xx三xx四xx五xx*",
    "*xxxx十xxxx五xxxx*",
    "*xxxxxxx分xxxxxx*",
    "*xxxxxちょうどxxxxx*",
    "*xxxxxxですxxxxxx*",
    "*xxxxx時はxxxxxxx*",
    "*xxxxxxx金なりxxxx*",
    "x+x1234xx分xxxxxx",
    "xxx換気xxxxアラームxxx",
    "x電池xxx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord IMAWA = {0, 3, 2}, SHOUGO = {0, 7, 2}, GOZEN = {0, 8, 2}, GOGO = {0, 11, 2};
static const WcWord JI = {5, 6, 1}, HAN = {5, 10, 1};
// minutes: tens digit 二 三 四 五 (20..50), 十 (10), unit 五 (5), 分 (minute)
static const WcWord TENS[4] = {{6, 3, 1}, {6, 6, 1}, {6, 9, 1}, {6, 12, 1}};
static const WcWord JUU = {7, 5, 1}, M_GO = {7, 10, 1}, FUN = {8, 8, 1};
static const WcWord CHOUDO = {9, 6, 4}, DESU = {10, 7, 2};
// hour 0..11: 零 一 二 三 四 五 六 七 八 九 十 十一 (十 and 十一 share the cell 十)
static const WcWord HOURS[12] = {{1, 3, 1}, {1, 7, 1}, {1, 11, 1}, {2, 3, 1}, {2, 7, 1}, {2, 11, 1},
                                 {3, 3, 1}, {3, 7, 1}, {3, 11, 1}, {4, 3, 1}, {4, 7, 1}, {4, 7, 2}};
// extra words (easter egg): 時は金なり ("time is money")
static const WcWord EXTRA[2] = {{11, 6, 2}, {12, 8, 3}};
// row 14: "+ 1 2 3 4  分" (digits in columns 3..6, no plural)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 9, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(IMAWA);
  if (!valid) return;
  const int m5 = minute / 5;
  if (m5 == 0 && hour == 12) {
    m.glue(SHOUGO);                      // 正午 (noon)
  } else {
    m.glue(hour < 12 ? GOZEN : GOGO);
    m.glue(HOURS[hour % 12]);
    m.glue(JI);
    if (m5 == 6) {
      m.glue(HAN);                       // 三時半
    } else if (m5 > 0) {
      const int tens = m5 / 2, unit = m5 % 2;
      if (tens >= 2) m.glue(TENS[tens - 2]);  // 二十, 三十, 四十, 五十
      if (tens >= 1) m.glue(JUU);
      if (unit) m.glue(M_GO);                 // 五, 十五, 二十五 ...
      m.glue(FUN);
    } else if (minute == 0) {
      m.glue(CHOUDO);                    // 三時ちょうど (exactly)
    }
  }
  m.glue(DESU);                          // ... です
  const int mm = minute % 5;             // "+ 1..4 分"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.glue(MIN_WORD);                    // "+ 2分"
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"ja","dec":".",
"notime_msg":"時計はまだ時刻を取得していません (インターネットまたは NTP なし)。",
"btn_settime":"スマートフォン/PC から時刻を設定",
"ap_info":"ホットスポット「{ap}」が有効です。下の <b>Wi-Fi</b> でネットワークを入力してください。",
"sec_show":"表示","on":"時計オン","swMin":"1分単位の表示 (+ 1–4 分)",
"brD":"昼間の明るさ","brN":"夜間の明るさ","cur":"電流制限 (mA)",
"hint_show":"夜間 0 % = 夜は表示が消えます。電流制限は電源アダプターに合わせて設定してください (256 個の LED は待機中でも約 256 mA 必要です)。",
"sec_col":"色",
"hint_col":"「ランダム」は毎正時に変わります。「温度」: 寒い 濃い青、黄、快適 緑、オレンジ、暑い 赤 (追加表示の範囲に基づく)。",
"g_time":"時刻","g_vent":"換気","g_alarm":"アラーム","g_batt":"電池","g_tout":"外気温","g_tin":"室温",
"pal_0":"温白色","pal_1":"白","pal_2":"赤","pal_3":"オレンジ","pal_4":"黄","pal_5":"緑","pal_6":"青","pal_7":"紫",
"c_random":"ランダム","c_temp":"温度","c_pride":"Pride","c_custom":"カスタム色",
"sec_fx":"エフェクト",
"fx_rainbow":"虹","fx_aurora":"オーロラ","fx_matrix":"マトリックス","fx_fire":"炎","fx_confetti":"紙吹雪","fx_stars":"星空",
"fx_blink":"点滅","fx_blink_own":"点滅 (カスタム色)","stop":"停止",
"fxd":"エフェクトの長さ","blk":"点滅周期",
"hint_fx":"長さ 0 秒 = 「停止」まで続きます。エフェクトは夜間 0 % や時計オフのときでも、常に最低 10 % の明るさで実行されます。",
"fx_started":"{fx} を開始しました","fx_stopped":"エフェクトを停止しました",
"txt":"スクロール文字","txt_ph":"文字を入力","txt_start":"文字を表示","txt_started":"文字表示を開始しました",
"hint_txt":"1文字ごとにマトリクス全体を使って表示します。エフェクト時間の間（最低1回）、時刻の色で表示（ランダム = 虹色）。ラテン文字、ギリシャ文字、キリル文字、数字、記号、€、♥ に対応、漢字・かなは非対応。HTTP: /api/set?text=…",
"sec_sun":"昼 / 夜","nmode":"夜間モード","nm_mix":"組み合わせ","nm_sun":"太陽の位置","nm_fixed":"固定時刻",
"lat":"緯度","lon":"経度","nso":"夜間開始のオフセット (分)","neo":"夜間終了のオフセット (分)",
"nme":"夜間開始 (最も早く)","nml":"夜間終了 (最も遅く)","nfs":"夜間開始時刻","nfe":"夜間終了時刻",
"sunrise":"日の出","sunset":"日の入り","night_today":"今夜","now":"現在",
"nmh_0":"オフセット: + は日の入り/日の出の後、− は前。座標は地図アプリなどで確認できます (場所を右クリック)。",
"nmh_1":"固定時刻は毎日適用されます。",
"nmh_2":"夜間は日の入り (+ オフセット) に始まりますが設定時刻より前には始まらず、日の出 (+ オフセット) に終わりますが設定時刻より後には終わりません。",
"day":"昼","night":"夜",
"sec_extra":"追加表示","tOnl":"Open-Meteo の外気温 (位置)",
"scale_out":"外気温の範囲 (°C)","scale_in":"室温の範囲 (°C)",
"swExtra":"「時は金なり」を表示",
"apiTo":"値の有効時間 (分、0 = 無期限)",
"v_out":"外気温","v_in":"室温","v_batt":"電池","v_la":"換気 / アラーム","on_":"オン","off_":"オフ",
"hint_extra":"室温、電池、換気、アラーム (Open-Meteo を使わない場合は外気温も) は外部から送られます。例: ブラウザー、スクリプト、スマートホーム:",
"sec_api":"HTTP 制御",
"hint_api1":"他のシステムからブラウザー、スクリプト、スマートホームで制御できます (<code>/api/set</code> に GET または POST、複数のパラメーターを組み合わせ可能)。明るさ、色、スイッチは保存され、エフェクトは設定した時間だけ実行されます。",
"hint_api2":"色: warmwhite, white, red, orange, yellow, green, blue, violet, random (温度: temp) または rrggbb · スイッチ: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle。",
"hint_api_keys":"エフェクト: {fx}, stop · fxcolor: 色の名前または rrggbb。電流制限、Wi-Fi、システムはこの Web インターフェースでのみ設定します。",
"sec_time":"時刻","ntpD":"NTP サーバー","ntp_auto":"自動 (DHCP)","ntp_manual":"手動","ntp_server":"サーバー",
"ntp_fallback":"予備サーバー (ルーターが提供しない場合、再起動後に有効)",
"loc":"場所","loc_custom":"カスタムの場所 (座標)","tz_from_loc":"場所から: {city}",
"tz":"タイムゾーン","tz_cet":"中央ヨーロッパ (DE, AT, CH …)","tz_wet":"ロンドン、リスボン (WET)","tz_eet":"東ヨーロッパ (キーウ、アテネ、ブカレスト)",
"tz_trt":"トルコ","tz_eat":"東アフリカ (タンザニア、ケニア)","tz_utc":"UTC",
"tz_use":"米国東部","tz_usc":"米国中部","tz_usm":"米国山岳部","tz_usw":"米国西部",
"tz_wib":"インドネシア (ジャカルタ)","tz_cst":"中国","tz_kst":"韓国","tz_jst":"日本","tz_aus":"オーストラリア東部",
"tz_custom":"カスタム (POSIX TZ) …","tz_posix":"POSIX タイムゾーン","ntp_active":"使用中のサーバー",
"ntp_hint":"自動: ルーター (DHCP) のサーバー、なければ入力した予備サーバー。自動と手動を切り替えると時計が再起動します。",
"ntp_nodhcp":"このボードパッケージでは DHCP NTP を使用できません – 入力したサーバーを使用します。",
"sec_wifi":"Wi-Fi","ssid":"ネットワーク (SSID)","scan":"ネットワークを検索","pass":"パスワード","pass_ph":"空欄 = 現在のパスワードを維持",
"host":"デバイス名 (http://name.local)","save_wifi":"保存して再接続",
"status":"状態","ip":"IP","last_err":"最後のエラー",
"hint_wifi":"起動時に Wi-Fi が見つからない場合、時計はホットスポット「{ap}」を開きます (パスワードなし、http://192.168.4.1)。",
"w_conn":"{ssid} に接続済み","w_ap":"ホットスポット有効 ({ip})","w_none":"未接続",
"scanning":"検索中 …","scan_none":"ネットワークが見つかりません","scan_err":"検索に失敗しました",
"wr_2":"認証タイムアウト","wr_15":"パスワードが違う?","wr_201":"ネットワークが見つかりません","wr_202":"認証が拒否されました (パスワード?)",
"wr_203":"アソシエーションに失敗しました","wr_204":"パスワードが違う?","wr_205":"接続に失敗しました","wr_8":"切断されました",
"net_hotspot":"ホットスポット {ap}","net_off":"Wi-Fi 切断","net_lost":"時計に接続できません",
"sec_sys":"システム","mir":"LED 0 が正面から見て右上 (ミラー)","srp":"マトリックスのジグザグ配線",
"restart":"再起動","reset":"工場出荷時設定に戻す",
"q_restart":"時計を再起動しますか?","q_reset":"Wi-Fi を含むすべての設定を削除しますか?",
"language":"言語","firmware":"ファームウェア","uptime":"稼働時間","heap":"空きメモリ",
"footer":"{ap} – 製作ガイド、コード、印刷データ:",
"saved":"保存しました","saved_restart":"保存しました – 時計が再起動します …","save_err":"保存中にエラー",
"time_set":"時刻を設定しました","restarting":"時計が再起動します …",
"srv_no_network":"ネットワークが入力されていません","srv_back":"戻る","srv_saved":"Wi-Fi を保存しました",
"srv_connecting":"時計は次のネットワークに接続します:","srv_restart":"そのため再起動します。ホットスポットは消えます。",
"srv_reach":"その後のアクセス先:","srv_reach2":"またはルーターやシリアルモニターに表示される IP アドレス。",
"srv_retry":"接続に失敗した場合、約 30 秒後にホットスポットが再び表示されます。",
"srv_not_found":"見つかりません"
})JSON";
}  // namespace wc_jp
static const WcLangDef WC_LANG = {
    "JP", "日本語", wc_jp::GRID,
    {14, 3, 2},   // 換気
    {14, 9, 4},   // アラーム
    {15, 1, 2},   // 電池
    {15, 6, 10},  // battery bars
    wc_jp::EXTRA, 2,  // 時は金なり
    wc_jp::time_words,
    "mojidokei", "MojiDokei",
    35.6762f, 139.6503f,           // Tokyo
    "JST-9",                       // Asia/Tokyo
    "%Y/%m/%d",
    wc_jp::UI_JSON,
};
