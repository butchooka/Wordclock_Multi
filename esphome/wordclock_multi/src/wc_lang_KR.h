/*
  wc_lang_KR.h - Wordclock 16x16, language file KR (한국어 / Korean), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_KR.scad (check: python3 tools/check_lang.py KR).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_KR.txt)
  Satzbau (Standardform, 12-Stunden-Zählung mit 오전/오후, immer auf die laufende Stunde bezogen):
  지금은 [오전 | 오후] <Stunde> 시 [<Minuten> 분 | 반]입니다 („jetzt ist es [vormittags | nachmittags] … Uhr …“).
  Die Stunde zählt koreanisch (한, 두, 세 …), die Minuten sinokoreanisch (오, 십, 이십 …); es gibt keinen Bezug
  auf die nächste Stunde („vor“) und keine Viertel. :30 = 반 („halb“, nachgestellt: 세 시 반 = 3:30).
  :00 <Stunde> 시, :05 <Stunde> 시 오 분, :10 십 분, :15 십오 분, :20 이십 분, :25 이십오 분, :30 반,
  :35 삼십오 분, :40 사십 분, :45 사십오 분, :50 오십 분, :55 오십오 분
  Die Minutenzahlen werden aus Zehnerziffer (이, 삼, 사, 오) + 십 + Einer 오 zusammengesetzt (im Text ohne
  Leerzeichen: 이십오). 입니다 („ist“) hängt ohne Leerzeichen am letzten Wort (분입니다, 시입니다, 반입니다).
  Beispiele: 3:05 지금은 오전 세 시 오 분입니다, 15:30 지금은 오후 세 시 반입니다,
  21:55 지금은 오후 아홉 시 오십오 분입니다.
  Stunden: 한, 두, 세, 네, 다섯, 여섯, 일곱, 여덟, 아홉, 열, 열한, 열두 (Kurzformen vor 시).
  오전 („vormittags“) 0:05-11:59, 오후 („nachmittags“) 12:05-23:59; 0 und 12 Uhr = 열두 시.
  Sonderfälle: 0:00-0:04 지금은 자정입니다 = „Mitternacht“, 12:00-12:04 지금은 정오입니다 = „Mittag“
  (ohne 오전/오후 und ohne 시).
  Ohne gültige Uhrzeit leuchtet nur 지금은.
  Minutenzeile: + 1..4 분 (im Koreanischen keine Mehrzahl; im Text „+ 2분“).
  Statuswörter: LÜFTEN = 환기 („Lüftung“), ALARM = 알람, AKKU = 배터리 („Batterie“).
  Zusatzwörter (Schalter „'시간은 금이다' 표시“): 시간은 금이다 („Zeit ist Gold“, Sprichwort).
  Schrift: Hangul-Silben (je eine Silbe = ein Feld) mit eigener Schrift Noto Sans KR Bold (lang_KR.scad);
  die Zeichen werden nur grob zentriert (keine Metriken). Füllfelder als Punkt (lang_KR.scad: Feld 6 = dot, gilt mit FILLER = auto).
  Offen (Testdruck): die strichreichen Silben 덟 (여덟) und 섯 (다섯, 여섯) bei 7 mm auf zugelaufene Lücken prüfen.
  INFO_EN
  Sentence (standard form, 12-hour counting with 오전/오후, always refers to the current hour):
  지금은 [오전 | 오후] <hour> 시 [<minutes> 분 | 반]입니다 ("now it is [a.m. | p.m.] … o'clock …").
  Hours use native Korean numbers (한, 두, 세 …), minutes Sino-Korean numbers (오, 십, 이십 …); there is no
  reference to the next hour ("to") and no quarters. :30 = 반 ("half", after the hour: 세 시 반 = 3:30).
  :00 <hour> 시, :05 <hour> 시 오 분, :10 십 분, :15 십오 분, :20 이십 분, :25 이십오 분, :30 반,
  :35 삼십오 분, :40 사십 분, :45 사십오 분, :50 오십 분, :55 오십오 분
  The minute numbers are made of the tens digit (이, 삼, 사, 오) + 십 + unit 오 (in the text without spaces:
  이십오). 입니다 ("is") is attached to the last word without a space (분입니다, 시입니다, 반입니다).
  Examples: 3:05 지금은 오전 세 시 오 분입니다, 15:30 지금은 오후 세 시 반입니다,
  21:55 지금은 오후 아홉 시 오십오 분입니다.
  Hours: 한, 두, 세, 네, 다섯, 여섯, 일곱, 여덟, 아홉, 열, 열한, 열두 (short forms before 시).
  오전 ("a.m.") 0:05-11:59, 오후 ("p.m.") 12:05-23:59; 0 and 12 o'clock = 열두 시.
  Special cases: 0:00-0:04 지금은 자정입니다 = "midnight", 12:00-12:04 지금은 정오입니다 = "noon"
  (without 오전/오후 and without 시).
  Without a valid time only 지금은 is lit.
  Minute row: + 1..4 분 (Korean has no plural; in the text "+ 2분").
  Status words: VENTILATE = 환기 ("ventilation"), ALARM = 알람, BATTERY = 배터리.
  Extra words (switch "'시간은 금이다' 표시"): 시간은 금이다 ("time is gold", proverb).
  Font: Hangul syllables (one syllable = one cell) with the own font Noto Sans KR Bold (lang_KR.scad);
  the characters are only roughly centred (no metrics). Fillers as dots (lang_KR.scad: field 6 = dot, used with FILLER = auto).
  Open (test print): check the stroke-rich syllables 덟 (여덟) and 섯 (다섯, 여섯) at 7 mm for closed gaps.
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_kr {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xx지금은xxx오전x오후x*",
    "*xx자정xxxxxx정오xx*",
    "*xx한xx두xx세xx네xx*",
    "*xx다섯xxxxxx여섯xx*",
    "*xx일곱xxxxxx여덟xx*",
    "*xx아홉xxxxxx열xxx*",
    "*xx열한xxxxxx열두xx*",
    "*xxxxx시xxx반xxxx*",
    "*xx이xx삼xx사xx오xx*",
    "*xxxx십xxxx오xxxx*",
    "*xxxxxxx분xxxxxx*",
    "*xxxxx입니다xxxxxx*",
    "*xxx시간은xx금이다xxx*",
    "x+x1234xx분xxxxxx",
    "xxx환기xxxxxx알람xxx",
    "x배터리xx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord JIGEUMEUN = {0, 3, 3}, OJEON = {0, 9, 2}, OHU = {0, 12, 2};
static const WcWord JAJEONG = {1, 3, 2}, JEONGO = {1, 11, 2};
static const WcWord SI = {7, 6, 1}, BAN = {7, 10, 1}, IMNIDA = {11, 6, 3};
// minutes: tens digit 이 삼 사 오 (20..50), 십 (10), unit 오 (5), 분 (minute)
static const WcWord TENS[4] = {{8, 3, 1}, {8, 6, 1}, {8, 9, 1}, {8, 12, 1}};
static const WcWord SIP = {9, 5, 1}, M_O = {9, 10, 1}, BUN = {10, 8, 1};
// hour 0..11 (0 = 열두): 열두 한 두 세 네 다섯 여섯 일곱 여덟 아홉 열 열한
static const WcWord HOURS[12] = {{6, 11, 2}, {2, 3, 1}, {2, 6, 1}, {2, 9, 1},  {2, 12, 1}, {3, 3, 2},
                                 {3, 11, 2}, {4, 3, 2}, {4, 11, 2}, {5, 3, 2}, {5, 11, 1}, {6, 3, 2}};
// extra words (easter egg): 시간은 금이다 ("time is gold")
static const WcWord EXTRA[2] = {{12, 4, 3}, {12, 9, 3}};
// row 14: "+ 1 2 3 4  분" (digits in columns 3..6, no plural)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 9, 1};
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  m.word(JIGEUMEUN);
  if (!valid) return;
  const int m5 = minute / 5;
  if (m5 == 0 && hour == 0) {
    m.word(JAJEONG);                     // 자정 (midnight)
  } else if (m5 == 0 && hour == 12) {
    m.word(JEONGO);                      // 정오 (noon)
  } else {
    m.word(hour < 12 ? OJEON : OHU);
    m.word(HOURS[hour % 12]);
    m.word(SI);
    if (m5 == 6) {
      m.word(BAN);                       // 세 시 반
    } else if (m5 > 0) {
      const int tens = m5 / 2, unit = m5 % 2;
      if (tens >= 2) { m.word(TENS[tens - 2]); m.glue(SIP); }  // 이십, 삼십, 사십, 오십
      else if (tens == 1) m.word(SIP);                         // 십
      if (unit) { if (tens) m.glue(M_O); else m.word(M_O); }   // 오, 십오, 이십오 ...
      m.word(BUN);
    }
  }
  m.glue(IMNIDA);                        // ... 분입니다
  const int mm = minute % 5;             // "+ 1..4 분"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.glue(MIN_WORD);                    // "+ 2분"
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"ko","dec":".",
"notime_msg":"시계가 아직 시간을 모릅니다 (인터넷 또는 NTP 없음).",
"btn_settime":"휴대폰/PC에서 시간 가져오기",
"ap_info":"핫스팟 “{ap}”이(가) 켜져 있습니다. 아래 <b>Wi-Fi</b>에서 네트워크를 입력하세요.",
"sec_show":"표시","on":"시계 켜짐","swMin":"개별 분 표시 (+ 1–4 분)",
"brD":"주간 밝기","brN":"야간 밝기","cur":"전류 제한 (mA)",
"hint_show":"야간 0 % = 밤에 표시가 꺼집니다. 전류 제한은 전원 어댑터에 맞게 설정하세요 (LED 256개는 대기 상태에서도 약 256 mA가 필요합니다).",
"sec_col":"색상",
"hint_col":"“무작위”는 매 정각마다 바뀝니다. “온도”: 추움 짙은 파랑, 노랑, 쾌적 초록, 주황, 더움 빨강 (추가 표시의 범위 기준).",
"g_time":"시간","g_vent":"환기","g_alarm":"알람","g_batt":"배터리","g_tout":"실외 온도","g_tin":"실내 온도",
"pal_0":"따뜻한 흰색","pal_1":"흰색","pal_2":"빨강","pal_3":"주황","pal_4":"노랑","pal_5":"초록","pal_6":"파랑","pal_7":"보라",
"c_random":"무작위","c_temp":"온도","c_pride":"Pride","c_custom":"사용자 색상",
"sec_fx":"효과",
"fx_rainbow":"무지개","fx_aurora":"오로라","fx_matrix":"매트릭스","fx_fire":"불꽃","fx_confetti":"색종이","fx_stars":"별이 빛나는 하늘",
"fx_blink":"깜빡임","fx_blink_own":"깜빡임 (사용자 색상)","stop":"정지",
"fxd":"효과 지속 시간","blk":"깜빡임 주기",
"hint_fx":"지속 시간 0초 = “정지”까지 계속됩니다. 효과는 야간 0 %이거나 시계가 꺼져 있어도 항상 최소 10 % 밝기로 실행됩니다.",
"fx_started":"{fx} 시작됨","fx_stopped":"효과 정지됨",
"txt":"텍스트 표시","txt_ph":"텍스트 입력","txt_start":"텍스트 시작","txt_started":"텍스트 시작됨",
"hint_txt":"글자 하나가 매트릭스 전체를 채웁니다. 효과 시간 동안(최소 한 번) 시간 색상으로 표시됩니다(무작위 = 무지개). 라틴, 그리스, 키릴 문자, 숫자, 문장 부호, €, ♥ 지원, 한글은 지원되지 않습니다. HTTP: /api/set?text=…",
"sec_sun":"주간 / 야간","nmode":"야간 모드","nm_mix":"혼합","nm_sun":"태양 위치","nm_fixed":"고정 시간",
"lat":"위도","lon":"경도","nso":"야간 시작 오프셋 (분)","neo":"야간 종료 오프셋 (분)",
"nme":"야간 시작 (빨라도)","nml":"야간 종료 (늦어도)","nfs":"야간 시작 시각","nfe":"야간 종료 시각",
"sunrise":"일출","sunset":"일몰","night_today":"오늘 밤","now":"현재",
"nmh_0":"오프셋: + 일몰 또는 일출 후, − 전. 좌표는 예를 들어 지도 앱에서 확인하세요 (장소를 오른쪽 클릭).",
"nmh_1":"고정 시간은 매일 적용됩니다.",
"nmh_2":"야간은 일몰(+ 오프셋)에 시작하지만 설정 시각 이전에는 시작하지 않고, 일출(+ 오프셋)에 끝나지만 설정 시각 이후에는 끝나지 않습니다.",
"day":"주간","night":"야간",
"sec_extra":"추가 표시","swTemp":"온도 점 (왼쪽 실외, 오른쪽 실내)","tOnl":"Open-Meteo의 실외 온도 (위치)",
"scale_out":"실외 범위 (°C)","scale_in":"실내 범위 (°C)",
"swLuft":"환기 표시","swAlarm":"알람 표시","swAkku":"배터리 표시","swExtra":"'시간은 금이다' 표시",
"apiTo":"값 유효 시간 (분, 0 = 항상)",
"v_out":"실외","v_in":"실내","v_batt":"배터리","v_la":"환기 / 알람","on_":"켜짐","off_":"꺼짐",
"hint_extra":"실내 온도, 배터리, 환기, 알람 (Open-Meteo를 쓰지 않으면 실외 온도도)은 외부에서 전달됩니다. 예: 브라우저, 스크립트 또는 스마트 홈:",
"sec_api":"HTTP 제어",
"hint_api1":"다른 시스템에서 브라우저, 스크립트 또는 스마트 홈으로 제어 (<code>/api/set</code>에 GET 또는 POST, 여러 매개변수 조합 가능). 밝기, 색상, 스위치는 저장되며 효과는 설정된 시간 동안 실행됩니다.",
"hint_api2":"색상: warmwhite, white, red, orange, yellow, green, blue, violet, random (온도: temp) 또는 rrggbb · 스위치: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"효과: {fx}, stop · fxcolor: 색상 이름 또는 rrggbb. 전류 제한, Wi-Fi, 시스템은 이 웹 인터페이스에서만 설정합니다.",
"sec_time":"시간","ntpD":"NTP 서버","ntp_auto":"자동 (DHCP)","ntp_manual":"수동","ntp_server":"서버",
"ntp_fallback":"예비 서버 (공유기가 제공하지 않을 때, 재시작 후 적용)",
"loc":"위치","loc_custom":"사용자 위치 (좌표)","tz_from_loc":"위치 기준: {city}",
"tz":"시간대","tz_cet":"중부 유럽 (DE, AT, CH …)","tz_wet":"런던, 리스본 (WET)","tz_eet":"동유럽 (키이우, 아테네, 부쿠레슈티)",
"tz_trt":"튀르키예","tz_eat":"동아프리카 (탄자니아, 케냐)","tz_utc":"UTC",
"tz_use":"미국 동부","tz_usc":"미국 중부","tz_usm":"미국 산악","tz_usw":"미국 서부",
"tz_wib":"인도네시아 (자카르타)","tz_cst":"중국","tz_kst":"한국","tz_jst":"일본","tz_aus":"호주 동부",
"tz_custom":"사용자 지정 (POSIX TZ) …","tz_posix":"POSIX 시간대","ntp_active":"사용 중인 서버",
"ntp_hint":"자동: 공유기(DHCP)의 서버, 없으면 입력한 예비 서버. 자동과 수동을 전환하면 시계가 재시작됩니다.",
"ntp_nodhcp":"이 보드 패키지에서는 DHCP NTP를 사용할 수 없습니다 – 입력한 서버를 사용합니다.",
"sec_wifi":"Wi-Fi","ssid":"네트워크 (SSID)","scan":"네트워크 검색","pass":"비밀번호","pass_ph":"비워 두면 = 현재 비밀번호 유지",
"host":"기기 이름 (http://name.local)","save_wifi":"저장 후 다시 연결",
"status":"상태","ip":"IP","last_err":"마지막 오류",
"hint_wifi":"시작할 때 Wi-Fi를 찾지 못하면 시계가 핫스팟 “{ap}”을(를) 엽니다 (비밀번호 없음, http://192.168.4.1).",
"w_conn":"{ssid}에 연결됨","w_ap":"핫스팟 켜짐 ({ip})","w_none":"연결되지 않음",
"scanning":"검색 중 …","scan_none":"네트워크를 찾지 못했습니다","scan_err":"검색 실패",
"wr_2":"인증 시간 초과","wr_15":"비밀번호 오류?","wr_201":"네트워크를 찾을 수 없음","wr_202":"인증 거부 (비밀번호?)",
"wr_203":"연결(association) 실패","wr_204":"비밀번호 오류?","wr_205":"연결 실패","wr_8":"연결 끊김",
"net_hotspot":"핫스팟 {ap}","net_off":"Wi-Fi 연결 끊김","net_lost":"시계와 연결되지 않음",
"sec_sys":"시스템","mir":"LED 0이 앞에서 볼 때 오른쪽 위 (미러)","srp":"매트릭스 지그재그 배선",
"restart":"재시작","reset":"공장 초기화",
"q_restart":"시계를 재시작할까요?","q_reset":"Wi-Fi를 포함한 모든 설정을 삭제할까요?",
"language":"언어","firmware":"펌웨어","uptime":"가동 시간","heap":"여유 메모리",
"footer":"{ap} – 제작 안내, 코드 및 출력 파일:",
"saved":"저장됨","saved_restart":"저장됨 – 시계가 재시작됩니다 …","save_err":"저장 중 오류",
"time_set":"시간 적용됨","restarting":"시계가 재시작됩니다 …",
"srv_no_network":"네트워크가 입력되지 않았습니다","srv_back":"뒤로","srv_saved":"Wi-Fi 저장됨",
"srv_connecting":"시계가 이제 다음 네트워크에 연결합니다:","srv_restart":"이를 위해 재시작합니다. 핫스팟은 사라집니다.",
"srv_reach":"이후 접속 주소:","srv_reach2":"또는 공유기나 시리얼 모니터에 표시된 IP 주소.",
"srv_retry":"연결에 실패하면 약 30초 후 핫스팟이 다시 나타납니다.",
"srv_not_found":"찾을 수 없음"
})JSON";
}  // namespace wc_kr
static const WcLangDef WC_LANG = {
    "KR", "한국어", wc_kr::GRID,
    {14, 3, 2},   // 환기
    {14, 11, 2},  // 알람
    {15, 1, 3},   // 배터리
    {15, 6, 10},  // battery bars
    wc_kr::EXTRA, 2,  // 시간은 금이다
    wc_kr::time_words,
    "geuljasigye", "GeuljaSigye",
    37.5665f, 126.9780f,           // Seoul
    "KST-9",                       // Asia/Seoul
    "%Y. %m. %d.",
    wc_kr::UI_JSON,
};
