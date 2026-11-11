/*
  wc_lang_PT.h - Wordclock 16x16, language file PT (Português, Portugal), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_PT.scad (check: python3 tools/check_lang.py PT).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_PT.txt)
  Satzbau (europäisches Portugiesisch): SÃO / É <Stunde> [HORA(S)] [E <Minuten> | MENOS <Minuten>]
  Ab :35 (MENOS) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 HORA(S), :05 E CINCO, :10 E DEZ, :15 E UM QUARTO, :20 E VINTE, :25 E VINTE E CINCO,
  :30 E MEIA, :35 MENOS VINTE E CINCO, :40 MENOS VINTE, :45 MENOS UM QUARTO, :50 MENOS DEZ,
  :55 MENOS CINCO
  É bei UMA, MEIO-DIA (12 Uhr) und MEIA-NOITE (0 Uhr), sonst SÃO. Stunden sind weiblich (UMA, DUAS).
  HORA/HORAS nur zur vollen Stunde (É UMA HORA, SÃO TRÊS HORAS), nie bei MEIO-DIA/MEIA-NOITE.
  Minutenzeile: + 1 MINUTO (Einzahl), + 2..4 MINUTOS.
  Zusatzwörter (Schalter „Mostrar OLÁ“): OLÁ („Hallo“, Gruß).
  INFO_EN
  Sentence (European Portuguese): SÃO / É <hour> [HORA(S)] [E <minutes> | MENOS <minutes>]
  From :35 (MENOS) on the time refers to the next hour.
  :00 HORA(S), :05 E CINCO, :10 E DEZ, :15 E UM QUARTO, :20 E VINTE, :25 E VINTE E CINCO,
  :30 E MEIA, :35 MENOS VINTE E CINCO, :40 MENOS VINTE, :45 MENOS UM QUARTO, :50 MENOS DEZ,
  :55 MENOS CINCO
  É with UMA, MEIO-DIA (12 o'clock) and MEIA-NOITE (0 o'clock), otherwise SÃO. Hours are feminine
  (UMA, DUAS). HORA/HORAS only at the full hour (É UMA HORA, SÃO TRÊS HORAS), never with
  MEIO-DIA/MEIA-NOITE.
  Minute row: + 1 MINUTO (singular), + 2..4 MINUTOS.
  Extra words (switch "Mostrar OLÁ"): OLÁ ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_pt {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xÉxxSÃOxxxUMAx*",
    "*xDUASxxxTRÊSxx*",
    "*QUATROxxxCINCO*",
    "*xSEISxxSETExxx*",
    "*xxOITOxxNOVExx*",
    "*xDEZxxxxONZExx*",
    "*xxxMEIO-DIAxxx*",
    "*xxMEIA-NOITExx*",
    "*xHORASxxOLÁxxx*",
    "*xxExxxxxMENOSx*",
    "*xVINTExExCINCO*",
    "*DEZxUMxQUARTOx*",
    "*xxxxxxMEIAxxxx*",
    "x+x1234xMINUTOSx",
    "xAREJARxxALARMEx",
    "CARGAx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord E_IS = {0, 2, 1}, SAO = {0, 5, 3};  // É (singular) / SÃO (plural)
static const WcWord MEIO_DIA = {6, 4, 8}, MEIA_NOITE = {7, 3, 10}, HORAS = {8, 2, 5}, HORA = {8, 2, 4};
static const WcWord E = {9, 3, 1}, MENOS = {9, 9, 5}, E2 = {10, 8, 1};  // E2 = "e" inside VINTE E CINCO
static const WcWord M_CINCO = {10, 10, 5}, M_DEZ = {11, 1, 3}, M_VINTE = {10, 2, 5};
static const WcWord UM = {11, 5, 2}, QUARTO = {11, 8, 6}, MEIA = {12, 7, 4};
// hour 1..11 (index 0 = MEIO-DIA, only a placeholder: 12 o'clock is MEIO-DIA/MEIA-NOITE, chosen in time_words)
static const WcWord HOURS[12] = {{6, 4, 8},  {0, 11, 3}, {1, 2, 4},  {1, 9, 4}, {2, 1, 6}, {2, 10, 5},
                                 {3, 2, 4},  {3, 8, 4},  {4, 3, 4},  {4, 9, 4}, {5, 2, 3}, {5, 9, 4}};
// extra words (easter egg): OLÁ ("hello", greeting)
static const WcWord EXTRA[1] = {{8, 9, 3}};
// row 14: "+ 1 2 3 4  MINUTOS" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 7}, MIN_ONE = {13, 8, 6};  // MINUTOS / MINUTO
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  if (!valid) {
    m.word(SAO);
    return;
  }
  const int m5 = minute / 5;
  int h = hour % 24;
  if (m5 >= 7) h = (h + 1) % 24;  // from "menos vinte e cinco" on the next hour counts
  const int h12 = h % 12;
  m.word((h12 == 0 || h12 == 1) ? E_IS : SAO);  // É MEIO-DIA, É MEIA-NOITE, É UMA; SÃO DUAS ...
  if (h == 12) m.word(MEIO_DIA);
  else if (h == 0) m.word(MEIA_NOITE);
  else {
    m.word(HOURS[h12]);
    if (m5 == 0) m.word(h12 == 1 ? HORA : HORAS);  // É UMA HORA, SÃO DUAS HORAS (only at the full hour)
  }
  switch (m5) {
    case 0: break;
    case 1: m.word(E); m.word(M_CINCO); break;
    case 2: m.word(E); m.word(M_DEZ); break;
    case 3: m.word(E); m.word(UM); m.word(QUARTO); break;
    case 4: m.word(E); m.word(M_VINTE); break;
    case 5: m.word(E); m.word(M_VINTE); m.word(E2); m.word(M_CINCO); break;
    case 6: m.word(E); m.word(MEIA); break;
    case 7: m.word(MENOS); m.word(M_VINTE); m.word(E2); m.word(M_CINCO); break;
    case 8: m.word(MENOS); m.word(M_VINTE); break;
    case 9: m.word(MENOS); m.word(UM); m.word(QUARTO); break;
    case 10: m.word(MENOS); m.word(M_DEZ); break;
    default: m.word(MENOS); m.word(M_CINCO); break;
  }
  const int mm = minute % 5;  // "+ 1 MINUTO" or "+ 2..4 MINUTOS"
  if (mm > 0 && show_minutes) {
    m.word(MIN_PLUS);
    m.at(MIN_DIGIT_ROW, MIN_DIGIT_COL + mm - 1);
    m.word(mm == 1 ? MIN_ONE : MIN_WORD);  // singular: without the final S
  }
}
static const char UI_JSON[] = R"JSON({
"html_lang":"pt-PT","dec":",",
"notime_msg":"O relógio ainda não tem hora (sem Internet ou NTP).",
"btn_settime":"Usar a hora do telemóvel/PC",
"ap_info":"Ponto de acesso «{ap}» ativo. Introduza a sua rede abaixo em <b>Wi-Fi</b>.",
"sec_show":"Visualização","on":"Relógio ligado","swMin":"Minutos individuais (+ 1–4 MINUTOS)",
"brD":"Brilho de dia","brN":"Brilho de noite","cur":"Limite de corrente (mA)",
"hint_show":"Noite 0 % = ecrã desligado à noite. Escolha o limite de corrente conforme a fonte de alimentação (256 LED já consomem cerca de 256 mA em repouso).",
"sec_col":"Cores",
"hint_col":"«Aleatória» muda a cada hora certa. «Temperatura»: frio azul-escuro, amarelo, conforto verde, laranja, quente vermelho (segundo a escala em indicações adicionais).",
"g_time":"Hora","g_vent":"AREJAR","g_alarm":"ALARME","g_batt":"CARGA","g_tout":"Temperatura exterior","g_tin":"Temperatura interior",
"pal_0":"Branco quente","pal_1":"Branco","pal_2":"Vermelho","pal_3":"Laranja","pal_4":"Amarelo","pal_5":"Verde","pal_6":"Azul","pal_7":"Violeta",
"c_random":"Aleatória","c_temp":"Temperatura","c_pride":"Pride","c_custom":"cor personalizada",
"sec_fx":"Efeitos",
"fx_rainbow":"Arco-íris","fx_aurora":"Aurora","fx_matrix":"Matrix","fx_fire":"Fogo","fx_confetti":"Confetes","fx_stars":"Céu estrelado",
"fx_blink":"Piscar","fx_blink_own":"Piscar (cor personalizada)","stop":"Parar",
"fxd":"Duração do efeito","blk":"Ciclo de piscar",
"hint_fx":"Duração 0 s = funciona até «Parar». Os efeitos funcionam sempre com pelo menos 10 % de brilho, mesmo à noite com 0 % ou com o relógio desligado.",
"fx_started":"{fx} iniciado","fx_stopped":"Efeito parado",
"txt":"Texto","txt_ph":"Escreva um texto","txt_start":"Mostrar texto","txt_started":"Texto iniciado",
"hint_txt":"Cada letra ocupa toda a matriz. Dura o tempo do efeito (pelo menos uma vez), na cor da hora (aleatória = arco-íris). Letras latinas, gregas e cirílicas, algarismos, pontuação, € e ♥. HTTP: /api/set?text=…",
"sec_sun":"Dia / noite","nmode":"Modo noturno","nm_mix":"Misto","nm_sun":"Posição do sol","nm_fixed":"Horas fixas",
"lat":"Latitude","lon":"Longitude","nso":"Desvio início da noite (min)","neo":"Desvio fim da noite (min)",
"nme":"Noite não antes de","nml":"Noite não depois de","nfs":"Noite das","nfe":"Noite até às",
"sunrise":"Nascer do sol","sunset":"Pôr do sol","night_today":"Noite hoje","now":"Agora",
"nmh_0":"Desvio: + depois, − antes do pôr ou do nascer do sol. Coordenadas p. ex. de uma app de mapas (clique direito no local).",
"nmh_1":"As horas fixas aplicam-se todos os dias.",
"nmh_2":"A noite começa ao pôr do sol (mais desvio), mas não antes da hora definida, e termina ao nascer do sol (mais desvio), mas não depois da hora definida.",
"day":"Dia","night":"Noite",
"sec_extra":"Indicações adicionais","tOnl":"Temperatura exterior do Open-Meteo (local)",
"scale_out":"Escala exterior (°C)","scale_in":"Escala interior (°C)",
"swExtra":"Mostrar OLÁ",
"apiTo":"Valores válidos durante (min, 0 = sempre)",
"v_out":"Exterior","v_in":"Interior","v_batt":"Bateria","v_la":"Arejar / alarme","on_":"ligado","off_":"desligado",
"hint_extra":"Interior, bateria, arejar e alarme (e exterior, se sem Open-Meteo) vêm de fora, p. ex. por navegador, script ou casa inteligente:",
"sec_api":"Controlo HTTP",
"hint_api1":"A partir de outros sistemas por navegador, script ou casa inteligente (GET ou POST para <code>/api/set</code>, vários parâmetros combináveis). Brilho, cores e interruptores são guardados, os efeitos funcionam durante a duração definida.",
"hint_api2":"Cores: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatura: temp) ou rrggbb · Interruptores: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Efeitos: {fx}, stop · fxcolor: nome da cor ou rrggbb. Limite de corrente, Wi-Fi e sistema só aqui na interface web.",
"sec_time":"Hora","ntpD":"Servidor NTP","ntp_auto":"automático (DHCP)","ntp_manual":"manual","ntp_server":"Servidor",
"ntp_fallback":"Servidor de reserva (se o router não fornecer um, válido após reinício)",
"loc":"Local","loc_custom":"local personalizado (coordenadas)","tz_from_loc":"conforme o local {city}",
"tz":"Fuso horário","tz_cet":"Europa Central (DE, FR, ES …)","tz_wet":"Londres, Lisboa (WET)","tz_eet":"Europa de Leste (Kyiv, Atenas, Bucareste)",
"tz_trt":"Turquia","tz_eat":"África Oriental (Tanzânia, Quénia)","tz_utc":"UTC",
"tz_use":"EUA Leste","tz_usc":"EUA Centro","tz_usm":"EUA Montanha","tz_usw":"EUA Oeste",
"tz_wib":"Indonésia (Jacarta)","tz_cst":"China","tz_kst":"Coreia","tz_jst":"Japão","tz_aus":"Austrália Leste",
"tz_custom":"personalizado (POSIX TZ) …","tz_posix":"Fuso horário POSIX","ntp_active":"Servidor ativo",
"ntp_hint":"Automático: servidor do router (DHCP), caso contrário o introduzido como reserva. Mudar entre automático e manual reinicia o relógio.",
"ntp_nodhcp":"O NTP por DHCP não está disponível neste pacote de placa – é usado o servidor introduzido.",
"sec_wifi":"Wi-Fi","ssid":"Rede (SSID)","scan":"Procurar redes","pass":"Palavra-passe","pass_ph":"vazio = manter a atual",
"host":"Nome do dispositivo (http://nome.local)","save_wifi":"Guardar e voltar a ligar",
"status":"Estado","ip":"IP","last_err":"Último erro",
"hint_wifi":"Se o Wi-Fi não for encontrado no arranque, o relógio abre o ponto de acesso «{ap}» (sem palavra-passe, http://192.168.4.1).",
"w_conn":"ligado a {ssid}","w_ap":"Ponto de acesso ativo ({ip})","w_none":"não ligado",
"scanning":"A procurar …","scan_none":"Nenhuma rede encontrada","scan_err":"A procura falhou",
"wr_2":"autenticação expirada","wr_15":"palavra-passe errada?","wr_201":"rede não encontrada","wr_202":"autenticação recusada (palavra-passe?)",
"wr_203":"associação falhou","wr_204":"palavra-passe errada?","wr_205":"ligação falhou","wr_8":"desligado",
"net_hotspot":"Ponto de acesso {ap}","net_off":"Wi-Fi desligado","net_lost":"sem ligação ao relógio",
"sec_sys":"Sistema","mir":"LED 0 à frente em cima à direita (espelhado)","srp":"Matriz ligada em ziguezague",
"restart":"Reiniciar","reset":"Repor definições de fábrica",
"q_restart":"Reiniciar o relógio?","q_reset":"Apagar todas as definições, incluindo o Wi-Fi?",
"language":"Idioma","firmware":"Firmware","uptime":"Tempo de funcionamento","heap":"Memória livre",
"footer":"{ap} – guia de montagem, código e ficheiros de impressão:",
"saved":"Guardado","saved_restart":"Guardado – o relógio reinicia …","save_err":"Erro ao guardar",
"time_set":"Hora assumida","restarting":"O relógio reinicia …",
"srv_no_network":"Nenhuma rede introduzida","srv_back":"Voltar","srv_saved":"Wi-Fi guardado",
"srv_connecting":"O relógio liga-se agora a","srv_restart":"e reinicia para isso. O ponto de acesso desaparece.",
"srv_reach":"Depois acessível em","srv_reach2":"ou pelo endereço IP do router ou do monitor série.",
"srv_retry":"Se a ligação falhar, o ponto de acesso volta a aparecer após cerca de 30 segundos.",
"srv_not_found":"Não encontrado"
})JSON";
}  // namespace wc_pt
static const WcLangDef WC_LANG = {
    "PT", "Português", wc_pt::GRID,
    {14, 1, 6},   // AREJAR
    {14, 9, 6},   // ALARME
    {15, 0, 5},   // CARGA
    {15, 6, 10},  // battery bars
    wc_pt::EXTRA, 1,  // OLÁ
    wc_pt::time_words,
    "relogio", "Relogio",
    38.7223f, -9.1393f,           // Lisboa
    "GMT0BST,M3.5.0/1,M10.5.0",   // Europe/Lisbon (same rules as WET0WEST, key "wet" in webpage.h)
    "%d/%m/%Y",
    wc_pt::UI_JSON,
};
