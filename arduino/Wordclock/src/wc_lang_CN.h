/*
  wc_lang_CN.h - Wordclock 16x16, language file CN (中文 / Mandarin Chinese, simplified characters), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_CN.scad (check: python3 tools/check_lang.py CN).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_CN.txt)
  Satzbau (Standardform des Hochchinesischen/Putonghua, Kurzzeichen, 12-Stunden-Zählung mit Tageszeit,
  immer auf die laufende Stunde): 现在是 <Tageszeit> <Stunde>点 [<Minuten>分 | 半 | 整]
  („jetzt ist es <Tageszeit> … Uhr …“). Stunden und Minuten werden mit chinesischen Zahlzeichen geschrieben;
  es gibt keinen Bezug auf die nächste Stunde (die Form „差五分四点“ = „fünf vor vier“ ist umgangssprachlich und
  wird nicht verwendet) und keine Viertel (一刻 ist veraltet, 三刻 selten). :30 = 半 („halb“, nachgestellt: 三点半 = 3:30).
  :00 <Stunde>点整, :05 <Stunde>点五分, :10 十分, :15 十五分, :20 二十分, :25 二十五分, :30 半,
  :35 三十五分, :40 四十分, :45 四十五分, :50 五十分, :55 五十五分
  Die Minutenzahlen werden aus Zehnerziffer (二, 三, 四, 五) + 十 + Einer 五 zusammengesetzt.
  整 („genau“) leuchtet nur zur vollen Minute :00, bei :01-:04 steht <Stunde>点 + Einzelminuten.
  Chinesisch schreibt ohne Leerzeichen; der Text wird ohne Leerzeichen zusammengesetzt (nur vor „+ 2分“).
  Stunden: 一, 两, 三, 四, 五, 六, 七, 八, 九, 十, 十一, 十二 (2 Uhr = 两点, nicht 二点; 0 Uhr und 12 Uhr = 十二点).
  Tageszeit: 凌晨 (früher Morgen) 0:00-4:59, 上午 (Vormittag) 5:00-11:59, 中午 (Mittag) 12:00-12:59,
  下午 (Nachmittag) 13:00-17:59, 晚上 (Abend) 18:00-23:59. 上 wird von 晚上 und 上午 gemeinsam genutzt.
  Beispiele: 0:00 现在是凌晨十二点整, 2:05 现在是凌晨两点五分, 12:30 现在是中午十二点半,
  15:45 现在是下午三点四十五分, 21:55 现在是晚上九点五十五分.
  Ohne gültige Uhrzeit leuchtet nur 现在是.
  Minutenzeile: + 1..4 分 (im Chinesischen keine Mehrzahl; im Text „+ 2分“).
  Statuswörter: LÜFTEN = 通风 („Lüftung“), ALARM = 警报 („Alarm, Warnung“), AKKU = 电池 („Batterie“).
  Zusatzwörter (Schalter „显示「一寸光阴一寸金」“): 一寸光阴一寸金 / 寸金难买寸光阴 („Ein Zoll Zeit ist ein Zoll Gold wert,
  doch ein Zoll Gold kauft keinen Zoll Zeit“, Sprichwort).
  Schrift: chinesische Kurzzeichen (je ein Zeichen = ein Feld) mit eigener Schrift Noto Sans SC Bold
  (lang_CN.scad); die Zeichen werden nur grob zentriert (keine Metriken). Füllfelder als Punkt (lang_CN.scad: Feld 6 = dot, gilt mit FILLER = auto).
  INFO_EN
  Sentence (standard form of Mandarin/Putonghua, simplified characters, 12-hour counting with time of day,
  always the current hour): 现在是 <time of day> <hour>点 [<minutes>分 | 半 | 整] ("now it is <time of day> …
  o'clock …"). Hours and minutes are written with Chinese numerals; there is no reference to the next hour
  (the form "差五分四点" = "five to four" is colloquial and not used) and no quarters (一刻 is old-fashioned,
  三刻 rare). :30 = 半 ("half", after the hour: 三点半 = 3:30).
  :00 <hour>点整, :05 <hour>点五分, :10 十分, :15 十五分, :20 二十分, :25 二十五分, :30 半,
  :35 三十五分, :40 四十分, :45 四十五分, :50 五十分, :55 五十五分
  The minute numbers are made of the tens digit (二, 三, 四, 五) + 十 + unit 五.
  整 ("exactly") is lit only at the full minute :00, at :01-:04 it reads <hour>点 + single minutes.
  Chinese is written without spaces; the text is joined without spaces (only before "+ 2分").
  Hours: 一, 两, 三, 四, 五, 六, 七, 八, 九, 十, 十一, 十二 (2 o'clock = 两点, not 二点; 0 and 12 o'clock = 十二点).
  Time of day: 凌晨 (early morning) 0:00-4:59, 上午 (morning) 5:00-11:59, 中午 (noon) 12:00-12:59,
  下午 (afternoon) 13:00-17:59, 晚上 (evening) 18:00-23:59. 上 is shared by 晚上 and 上午.
  Examples: 0:00 现在是凌晨十二点整, 2:05 现在是凌晨两点五分, 12:30 现在是中午十二点半,
  15:45 现在是下午三点四十五分, 21:55 现在是晚上九点五十五分.
  Without a valid time only 现在是 is lit.
  Minute row: + 1..4 分 (Chinese has no plural; in the text "+ 2分").
  Status words: VENTILATE = 通风 ("ventilation"), ALARM = 警报 ("alarm, warning"), BATTERY = 电池.
  Extra words (switch "显示「一寸光阴一寸金」"): 一寸光阴一寸金 / 寸金难买寸光阴 ("an inch of time is an inch of gold,
  but an inch of gold cannot buy an inch of time", proverb).
  Font: simplified Chinese characters (one character = one cell) with the own font Noto Sans SC Bold
  (lang_CN.scad); the characters are only roughly centred (no metrics). Fillers as dots (lang_CN.scad: field 6 = dot, used with FILLER = auto).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_cn {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xx现在是x凌晨xxxxxx*",
    "*xx晚上午x中午x下午xxx*",
    "*xxxxxxxxxxxxxx*",
    "*xx一x两x三x四x五x六x*",
    "*xx七x八x九x十一x十二x*",
    "*xxxxx点半x整xxxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xxx二x三x四x五xxxx*",
    "*xxxxxxx十五分xxxx*",
    "*xxxxxxxxxxxxxx*",
    "*xxxx一寸光阴一寸金xxx*",
    "*xxxxxxxxxxxxxx*",
    "*xxxx寸金难买寸光阴xxx*",
    "x+x1234xx分xxxxxx",
    "xxx通风xxxx警报xxxxx",
    "x电池xxx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord XIANZAISHI = {0, 3, 3};
// time of day: 凌晨 (0-4), 上午 (5-11), 中午 (12), 下午 (13-17), 晚上 (18-23); 上 shared by 晚上 and 上午
static const WcWord LINGCHEN = {0, 7, 2}, WANSHANG = {1, 3, 2}, SHANGWU = {1, 4, 2};
static const WcWord ZHONGWU = {1, 7, 2}, XIAWU = {1, 10, 2};
// hour 1..12: 一 两 三 四 五 六 七 八 九 十 十一 十二 (十 and 十一 share the cell 十)
static const WcWord HOURS[12] = {{3, 3, 1}, {3, 5, 1}, {3, 7, 1}, {3, 9, 1}, {3, 11, 1}, {3, 13, 1},
                                 {4, 3, 1}, {4, 5, 1}, {4, 7, 1}, {4, 9, 1}, {4, 9, 2}, {4, 12, 2}};
static const WcWord DIAN = {5, 6, 1}, BAN = {5, 7, 1}, ZHENG = {5, 9, 1};
// minutes: tens digit 二 三 四 五 (20..50), 十 (10), unit 五 (5), 分 (minute)
static const WcWord TENS[4] = {{7, 4, 1}, {7, 6, 1}, {7, 8, 1}, {7, 10, 1}};
static const WcWord SHI = {8, 8, 1}, M_WU = {8, 9, 1}, FEN = {8, 10, 1};
// extra words (easter egg): 一寸光阴一寸金 / 寸金难买寸光阴 (proverb about the value of time)
static const WcWord EXTRA[2] = {{10, 5, 7}, {12, 5, 7}};
// row 14: "+ 1 2 3 4  分" (digits in columns 3..6, no plural)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 9, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(XIANZAISHI);                    // 现在是
  if (!valid) return;
  const int m5 = minute / 5;
  if (hour < 5) m.glue(LINGCHEN);
  else if (hour < 12) m.glue(SHANGWU);
  else if (hour == 12) m.glue(ZHONGWU);
  else if (hour < 18) m.glue(XIAWU);
  else m.glue(WANSHANG);
  const int h12 = hour % 12;
  m.glue(HOURS[h12 == 0 ? 11 : h12 - 1]);  // 0 and 12 -> 十二
  m.glue(DIAN);                          // 点
  if (m5 == 6) {
    m.glue(BAN);                         // 三点半
  } else if (m5 > 0) {
    const int tens = m5 / 2, unit = m5 % 2;
    if (tens >= 2) m.glue(TENS[tens - 2]);  // 二十, 三十, 四十, 五十
    if (tens >= 1) m.glue(SHI);
    if (unit) m.glue(M_WU);                 // 五, 十五, 二十五 ...
    m.glue(FEN);
  } else if (minute == 0) {
    m.glue(ZHENG);                       // 三点整 (exactly)
  }
  const int mm = minute % 5;             // "+ 1..4 分"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.glue(MIN_WORD);                    // "+ 2分"
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"zh-CN","dec":".",
"notime_msg":"时钟尚未获取时间 (没有互联网或 NTP)。",
"btn_settime":"从手机/电脑设置时间",
"ap_info":"热点“{ap}”已开启。请在下方 <b>Wi-Fi</b> 中输入您的网络。",
"sec_show":"显示","on":"时钟开启","swMin":"单分钟显示 (+ 1–4 分)",
"brD":"白天亮度","brN":"夜间亮度","cur":"电流限制 (mA)",
"hint_show":"夜间 0 % = 夜间关闭显示。请根据电源适配器设置电流限制 (256 个 LED 待机时也需要约 256 mA)。",
"sec_col":"颜色",
"hint_col":"“随机”每到整点更换。“温度”: 冷 深蓝、黄、舒适 绿、橙、热 红 (根据附加显示中的范围)。",
"g_time":"时间","g_vent":"通风","g_alarm":"警报","g_batt":"电池","g_tout":"室外温度","g_tin":"室内温度",
"pal_0":"暖白","pal_1":"白","pal_2":"红","pal_3":"橙","pal_4":"黄","pal_5":"绿","pal_6":"蓝","pal_7":"紫",
"c_random":"随机","c_temp":"温度","c_pride":"Pride","c_custom":"自定义颜色",
"sec_fx":"特效",
"fx_rainbow":"彩虹","fx_aurora":"极光","fx_matrix":"矩阵","fx_fire":"火焰","fx_confetti":"彩纸","fx_stars":"星空",
"fx_blink":"闪烁","fx_blink_own":"闪烁 (自定义颜色)","stop":"停止",
"fxd":"特效时长","blk":"闪烁周期",
"hint_fx":"时长 0 秒 = 一直运行到“停止”。特效始终以至少 10 % 的亮度运行,即使夜间为 0 % 或时钟关闭。",
"fx_started":"{fx} 已开始","fx_stopped":"特效已停止",
"txt":"滚动文字","txt_ph":"输入文字","txt_start":"显示文字","txt_started":"文字已开始",
"hint_txt":"每个字母占满整个点阵。持续时间与特效时长相同（至少一遍），颜色为时间颜色（随机 = 彩虹）。支持拉丁、希腊和西里尔字母、数字、标点、€ 和 ♥，不支持汉字。HTTP：/api/set?text=…",
"sec_sun":"白天 / 夜间","nmode":"夜间模式","nm_mix":"组合","nm_sun":"太阳位置","nm_fixed":"固定时间",
"lat":"纬度","lon":"经度","nso":"夜间开始偏移 (分钟)","neo":"夜间结束偏移 (分钟)",
"nme":"夜间开始 (最早)","nml":"夜间结束 (最晚)","nfs":"夜间开始时间","nfe":"夜间结束时间",
"sunrise":"日出","sunset":"日落","night_today":"今晚","now":"现在",
"nmh_0":"偏移: + 表示日落/日出之后,− 表示之前。坐标可在地图应用中查到 (右键点击位置)。",
"nmh_1":"固定时间每天适用。",
"nmh_2":"夜间从日落 (+ 偏移) 开始,但不早于设定时间;在日出 (+ 偏移) 结束,但不晚于设定时间。",
"day":"白天","night":"夜间",
"sec_extra":"附加显示","swTemp":"温度点 (左 室外,右 室内)","tOnl":"Open-Meteo 室外温度 (位置)",
"scale_out":"室外温度范围 (°C)","scale_in":"室内温度范围 (°C)",
"swLuft":"显示通风","swAlarm":"显示警报","swAkku":"显示电池","swExtra":"显示「一寸光阴一寸金」",
"apiTo":"数值有效期 (分钟,0 = 无限期)",
"v_out":"室外温度","v_in":"室内温度","v_batt":"电池","v_la":"通风 / 警报","on_":"开","off_":"关",
"hint_extra":"室内温度、电池、通风、警报 (不使用 Open-Meteo 时还有室外温度) 由外部发送。例如通过浏览器、脚本或智能家居:",
"sec_api":"HTTP 控制",
"hint_api1":"可通过浏览器、脚本或智能家居从其他系统控制 (<code>/api/set</code> 的 GET 或 POST,可组合多个参数)。亮度、颜色和开关会被保存,特效只运行设定的时长。",
"hint_api2":"颜色: warmwhite, white, red, orange, yellow, green, blue, violet, random (温度: temp) 或 rrggbb · 开关: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle。",
"hint_api_keys":"特效: {fx}, stop · fxcolor: 颜色名称或 rrggbb。电流限制、Wi-Fi 和系统只能在此网页界面中设置。",
"sec_time":"时间","ntpD":"NTP 服务器","ntp_auto":"自动 (DHCP)","ntp_manual":"手动","ntp_server":"服务器",
"ntp_fallback":"备用服务器 (路由器未提供时使用,重启后生效)",
"loc":"位置","loc_custom":"自定义位置 (坐标)","tz_from_loc":"来自位置: {city}",
"tz":"时区","tz_cet":"中欧 (DE, AT, CH …)","tz_wet":"伦敦、里斯本 (WET)","tz_eet":"东欧 (基辅、雅典、布加勒斯特)",
"tz_trt":"土耳其","tz_eat":"东非 (坦桑尼亚、肯尼亚)","tz_utc":"UTC",
"tz_use":"美国东部","tz_usc":"美国中部","tz_usm":"美国山地","tz_usw":"美国西部",
"tz_wib":"印度尼西亚 (雅加达)","tz_cst":"中国","tz_kst":"韩国","tz_jst":"日本","tz_aus":"澳大利亚东部",
"tz_custom":"自定义 (POSIX TZ) …","tz_posix":"POSIX 时区","ntp_active":"当前服务器",
"ntp_hint":"自动: 使用路由器 (DHCP) 的服务器,否则使用输入的备用服务器。在自动和手动之间切换时时钟会重启。",
"ntp_nodhcp":"此开发板软件包不支持 DHCP NTP – 使用输入的服务器。",
"sec_wifi":"Wi-Fi","ssid":"网络 (SSID)","scan":"搜索网络","pass":"密码","pass_ph":"留空 = 保留当前密码",
"host":"设备名称 (http://name.local)","save_wifi":"保存并重新连接",
"status":"状态","ip":"IP","last_err":"上次错误",
"hint_wifi":"启动时如果找不到 Wi-Fi,时钟会开启热点“{ap}”(无密码,http://192.168.4.1)。",
"w_conn":"已连接到 {ssid}","w_ap":"热点已开启 ({ip})","w_none":"未连接",
"scanning":"正在搜索 …","scan_none":"未找到网络","scan_err":"搜索失败",
"wr_2":"认证超时","wr_15":"密码错误?","wr_201":"未找到网络","wr_202":"认证被拒绝 (密码?)",
"wr_203":"关联失败","wr_204":"密码错误?","wr_205":"连接失败","wr_8":"已断开",
"net_hotspot":"热点 {ap}","net_off":"Wi-Fi 已断开","net_lost":"无法连接到时钟",
"sec_sys":"系统","mir":"LED 0 从正面看位于右上角 (镜像)","srp":"矩阵之字形布线",
"restart":"重启","reset":"恢复出厂设置",
"q_restart":"重启时钟?","q_reset":"删除包括 Wi-Fi 在内的所有设置?",
"language":"语言","firmware":"固件","uptime":"运行时间","heap":"可用内存",
"footer":"{ap} – 制作指南、代码和打印文件:",
"saved":"已保存","saved_restart":"已保存 – 时钟正在重启 …","save_err":"保存时出错",
"time_set":"时间已设置","restarting":"时钟正在重启 …",
"srv_no_network":"未输入网络","srv_back":"返回","srv_saved":"Wi-Fi 已保存",
"srv_connecting":"时钟将连接到网络:","srv_restart":"为此将重启,热点会消失。",
"srv_reach":"之后可通过以下地址访问:","srv_reach2":"或通过路由器或串口监视器中显示的 IP 地址。",
"srv_retry":"如果连接失败,约 30 秒后热点会重新出现。",
"srv_not_found":"未找到"
})JSON";
}  // namespace wc_cn
static const WcLangDef WC_LANG = {
    "CN", "中文", wc_cn::GRID,
    {14, 3, 2},   // 通风
    {14, 9, 2},   // 警报
    {15, 1, 2},   // 电池
    {15, 6, 10},  // battery bars
    wc_cn::EXTRA, 2,  // 一寸光阴一寸金 / 寸金难买寸光阴
    wc_cn::time_words,
    "wenzizhong", "WenziZhong",
    39.9042f, 116.4074f,           // Beijing
    "CST-8",                       // Asia/Shanghai
    "%Y-%m-%d",
    wc_cn::UI_JSON,
};
