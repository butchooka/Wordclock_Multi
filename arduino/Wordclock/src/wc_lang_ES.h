/*
  wc_lang_ES.h - Wordclock 16x16, language file ES (Español), v0.9
  Grid, word positions, time grammar and web interface texts.
  The grid must be identical to models/lang/lang_ES.scad (check: python3 tools/check_lang.py ES).
  Preview of all times: see tools/preview.cpp.
  INFO_DE (tools/make_info.py writes the lines between the markers to docs/languages/LANG_ES.txt)
  Satzbau: ES LA UNA / SON LAS <Stunde> [Y|MENOS <Minuten>] [EN PUNTO]
  Ab :35 (MENOS) bezieht sich die Uhrzeit auf die nächste Stunde.
  :00 EN PUNTO, :05 Y CINCO, :10 Y DIEZ, :15 Y CUARTO, :20 Y VEINTE, :25 Y VEINTICINCO,
  :30 Y MEDIA, :35 MENOS VEINTICINCO, :40 MENOS VEINTE, :45 MENOS CUARTO, :50 MENOS DIEZ,
  :55 MENOS CINCO
  Einzahl nur bei 1 Uhr (ES LA UNA), sonst SON LAS (SON LAS DOS ...).
  12-Stunden-Anzeige: 0 und 12 Uhr = LAS DOCE (kein mediodía/medianoche).
  CINCO der Minuten ist das Ende von VEINTICINCO (gemeinsame Buchstaben).
  Minutenzeile: + 1 MINUTO (Einzahl), + 2..4 MINUTOS.
  Zusatzwörter (Schalter „Mostrar HOLA“): HOLA („Hallo“, Gruß).
  INFO_EN
  Sentence: ES LA UNA / SON LAS <hour> [Y|MENOS <minutes>] [EN PUNTO]
  From :35 (MENOS) on the time refers to the next hour.
  :00 EN PUNTO, :05 Y CINCO, :10 Y DIEZ, :15 Y CUARTO, :20 Y VEINTE, :25 Y VEINTICINCO,
  :30 Y MEDIA, :35 MENOS VEINTICINCO, :40 MENOS VEINTE, :45 MENOS CUARTO, :50 MENOS DIEZ,
  :55 MENOS CINCO
  Singular only for one o'clock (ES LA UNA), otherwise SON LAS (SON LAS DOS ...).
  12-hour display: 0 and 12 o'clock = LAS DOCE (no mediodía/medianoche).
  CINCO of the minutes is the end of VEINTICINCO (shared letters).
  Minute row: + 1 MINUTO (singular), + 2..4 MINUTOS.
  Extra words (switch "Mostrar HOLA"): HOLA ("hello", greeting).
  INFO_END
*/
#pragma once
#include "wc_core.h"
namespace wc_es {
// Row 1 = top. "*" temperature dot, "|" battery bar, "x" filler (never lit; printed as FILLER in the models)
static const char *const GRID[16] = {
    "*xESxSONxLASxxx*",
    "*xUNAxxxDOSxxxx*",
    "*xTRESxxCUATROx*",
    "*xCINCOxxSEISxx*",
    "*xSIETExxxOCHOx*",
    "*xNUEVExxxDIEZx*",
    "*xONCExxxDOCExx*",
    "*xxxYxxxMENOSxx*",
    "*xVEINTICINCOxx*",
    "*VEINTExxxDIEZx*",
    "*xxxCUARTOxHOLA*",
    "*xxxxxMEDIAxxxx*",
    "*xxxENxPUNTOxxx*",
    "x+x1234xMINUTOSx",
    "xVENTILARxALARMA",
    "xBATxx||||||||||",
};
// {row, column, length}, row/column counted from 0
static const WcWord ES = {0, 2, 2}, SON = {0, 5, 3}, LA = {0, 9, 2}, LAS = {0, 9, 3};
static const WcWord Y = {7, 4, 1}, MENOS = {7, 8, 5}, EN = {12, 4, 2}, PUNTO = {12, 7, 5};
static const WcWord M_VEINTICINCO = {8, 2, 11}, M_CINCO = {8, 8, 5}, M_VEINTE = {9, 1, 6}, M_DIEZ = {9, 10, 4};
static const WcWord M_CUARTO = {10, 4, 6}, MEDIA = {11, 6, 5};
// hour 0..11 (0 = DOCE)
static const WcWord HOURS[12] = {{6, 9, 4}, {1, 2, 3}, {1, 8, 3}, {2, 2, 4}, {2, 8, 6},  {3, 2, 5},
                                 {3, 9, 4}, {4, 2, 5}, {4, 10, 4}, {5, 2, 5}, {5, 10, 4}, {6, 2, 4}};
// extra words (easter egg): HOLA ("hello", greeting)
static const WcWord EXTRA[1] = {{10, 11, 4}};
// row 14: "+ 1 2 3 4  MINUTOS" (digits in columns 3..6)
static const WcWord MIN_PLUS = {13, 1, 1}, MIN_WORD = {13, 8, 7}, MIN_ONE = {13, 8, 6};  // MINUTOS / MINUTO
static const int MIN_DIGIT_ROW = 13, MIN_DIGIT_COL = 3;
static inline void time_words(bool valid, int hour, int minute, bool show_minutes, WcMark &m) {
  const int m5 = minute / 5;
  int h = hour % 12;
  if (m5 >= 7) h = (h + 1) % 12;  // from "menos veinticinco" on the next hour counts
  const bool one = (h == 1);
  if (!valid) {  // prefix without time: ES
    m.word(ES);
    return;
  }
  if (one) { m.word(ES); m.word(LA); }  // ES LA UNA
  else { m.word(SON); m.word(LAS); }    // SON LAS DOS ...
  m.word(HOURS[h]);
  switch (m5) {
    case 0: m.word(EN); m.word(PUNTO); break;
    case 1: m.word(Y); m.word(M_CINCO); break;
    case 2: m.word(Y); m.word(M_DIEZ); break;
    case 3: m.word(Y); m.word(M_CUARTO); break;
    case 4: m.word(Y); m.word(M_VEINTE); break;
    case 5: m.word(Y); m.word(M_VEINTICINCO); break;
    case 6: m.word(Y); m.word(MEDIA); break;
    case 7: m.word(MENOS); m.word(M_VEINTICINCO); break;
    case 8: m.word(MENOS); m.word(M_VEINTE); break;
    case 9: m.word(MENOS); m.word(M_CUARTO); break;
    case 10: m.word(MENOS); m.word(M_DIEZ); break;
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
"html_lang":"es","dec":",",
"notime_msg":"El reloj aún no tiene hora (sin Internet o NTP).",
"btn_settime":"Tomar la hora del móvil/PC",
"ap_info":"Punto de acceso «{ap}» activo. Introduce tu red abajo en <b>Wi-Fi</b>.",
"sec_show":"Pantalla","on":"Reloj encendido","swMin":"Minutos sueltos (+ 1–4 MINUTOS)",
"brD":"Brillo de día","brN":"Brillo de noche","cur":"Límite de corriente (mA)",
"hint_show":"Noche 0 % = pantalla apagada por la noche. Elige el límite de corriente según la fuente de alimentación (256 LED ya necesitan aprox. 256 mA en reposo).",
"sec_col":"Colores",
"hint_col":"«Aleatorio» cambia cada hora en punto. «Temperatura»: frío azul oscuro, amarillo, confort verde, naranja, calor rojo (según la escala en indicaciones adicionales).",
"g_time":"Hora","g_vent":"VENTILAR","g_alarm":"ALARMA","g_batt":"BAT","g_tout":"Temperatura exterior","g_tin":"Temperatura interior",
"pal_0":"Blanco cálido","pal_1":"Blanco","pal_2":"Rojo","pal_3":"Naranja","pal_4":"Amarillo","pal_5":"Verde","pal_6":"Azul","pal_7":"Violeta",
"c_random":"Aleatorio","c_temp":"Temperatura","c_pride":"Pride","c_custom":"color propio",
"sec_fx":"Efectos",
"fx_rainbow":"Arcoíris","fx_aurora":"Aurora","fx_matrix":"Matrix","fx_fire":"Fuego","fx_confetti":"Confeti","fx_stars":"Cielo estrellado",
"fx_blink":"Parpadeo","fx_blink_own":"Parpadeo (color propio)","stop":"Parar",
"fxd":"Duración del efecto","blk":"Ciclo de parpadeo",
"hint_fx":"Duración 0 s = funciona hasta «Parar». Los efectos funcionan siempre con al menos un 10 % de brillo, incluso de noche con 0 % o con el reloj apagado.",
"fx_started":"{fx} iniciado","fx_stopped":"Efecto parado",
"txt":"Texto","txt_ph":"Escribe un texto","txt_start":"Mostrar texto","txt_started":"Texto iniciado",
"hint_txt":"Cada letra ocupa toda la matriz. Dura lo que la duración del efecto (al menos una vez), en el color de la hora (aleatorio = arcoíris). Letras latinas, griegas y cirílicas, cifras, signos de puntuación, € y ♥. HTTP: /api/set?text=…",
"sec_sun":"Día / noche","nmode":"Modo noche","nm_mix":"Mixto","nm_sun":"Posición del sol","nm_fixed":"Horas fijas",
"lat":"Latitud","lon":"Longitud","nso":"Desfase inicio de noche (min)","neo":"Desfase fin de noche (min)",
"nme":"Noche no antes de","nml":"Noche no después de","nfs":"Noche desde","nfe":"Noche hasta",
"sunrise":"Salida del sol","sunset":"Puesta del sol","night_today":"Noche hoy","now":"Ahora",
"nmh_0":"Desfase: + después, − antes de la puesta o salida del sol. Coordenadas p. ej. de una app de mapas (clic derecho en el lugar).",
"nmh_1":"Las horas fijas valen todos los días.",
"nmh_2":"La noche empieza con la puesta del sol (más desfase), pero no antes de la hora ajustada, y termina con la salida del sol (más desfase), pero no después de la hora ajustada.",
"day":"Día","night":"Noche",
"sec_extra":"Indicaciones adicionales","swTemp":"Puntos de temperatura (izquierda exterior, derecha interior)","tOnl":"Temperatura exterior de Open-Meteo (ubicación)",
"scale_out":"Escala exterior (°C)","scale_in":"Escala interior (°C)",
"swLuft":"Mostrar VENTILAR","swAlarm":"Mostrar ALARMA","swAkku":"Mostrar BAT","swExtra":"Mostrar HOLA",
"apiTo":"Valores válidos durante (min, 0 = siempre)",
"v_out":"Exterior","v_in":"Interior","v_batt":"Batería","v_la":"Ventilar / alarma","on_":"sí","off_":"no",
"hint_extra":"Interior, batería, ventilar y alarma (y exterior, si es sin Open-Meteo) vienen de fuera, p. ej. por navegador, script o casa inteligente:",
"sec_api":"Control HTTP",
"hint_api1":"Desde otros sistemas por navegador, script o casa inteligente (GET o POST a <code>/api/set</code>, se pueden combinar varios parámetros). Brillo, colores e interruptores se guardan, los efectos funcionan durante la duración ajustada.",
"hint_api2":"Colores: warmwhite, white, red, orange, yellow, green, blue, violet, random (temperatura: temp) o rrggbb · Interruptores: on, show_minutes, show_temp, show_vent, show_alarm, show_battery, show_extra · fxdur, fxcycle.",
"hint_api_keys":"Efectos: {fx}, stop · fxcolor: nombre de color o rrggbb. Límite de corriente, Wi-Fi y sistema solo aquí en la interfaz web.",
"sec_time":"Hora","ntpD":"Servidor NTP","ntp_auto":"automático (DHCP)","ntp_manual":"manual","ntp_server":"Servidor",
"ntp_fallback":"Servidor de reserva (si el router no ofrece ninguno, vale tras reiniciar)",
"loc":"Ubicación","loc_custom":"ubicación propia (coordenadas)","tz_from_loc":"según la ubicación {city}",
"tz":"Zona horaria","tz_cet":"Europa Central (ES, DE, FR …)","tz_wet":"Londres, Lisboa (WET)","tz_eet":"Europa del Este (Kiev, Atenas, Bucarest)",
"tz_trt":"Turquía","tz_eat":"África Oriental (Tanzania, Kenia)","tz_utc":"UTC",
"tz_use":"EE. UU. Este","tz_usc":"EE. UU. Centro","tz_usm":"EE. UU. Montaña","tz_usw":"EE. UU. Oeste",
"tz_wib":"Indonesia (Yakarta)","tz_cst":"China","tz_kst":"Corea","tz_jst":"Japón","tz_aus":"Australia Este",
"tz_custom":"propia (POSIX TZ) …","tz_posix":"Zona horaria POSIX","ntp_active":"Servidor activo",
"ntp_hint":"Automático: servidor del router (DHCP), si no, el introducido como reserva. Cambiar entre automático y manual reinicia el reloj.",
"ntp_nodhcp":"NTP por DHCP no está disponible en este paquete de placa – se usa el servidor introducido.",
"sec_wifi":"Wi-Fi","ssid":"Red (SSID)","scan":"Buscar redes","pass":"Contraseña","pass_ph":"vacío = mantener la actual",
"host":"Nombre del dispositivo (http://nombre.local)","save_wifi":"Guardar y conectar",
"status":"Estado","ip":"IP","last_err":"Último error",
"hint_wifi":"Si al arrancar no se encuentra la Wi-Fi, el reloj abre el punto de acceso «{ap}» (sin contraseña, http://192.168.4.1).",
"w_conn":"conectado a {ssid}","w_ap":"Punto de acceso activo ({ip})","w_none":"no conectado",
"scanning":"Buscando …","scan_none":"No se encontraron redes","scan_err":"Error en la búsqueda",
"wr_2":"autenticación caducada","wr_15":"¿contraseña incorrecta?","wr_201":"red no encontrada","wr_202":"autenticación rechazada (¿contraseña?)",
"wr_203":"asociación fallida","wr_204":"¿contraseña incorrecta?","wr_205":"conexión fallida","wr_8":"desconectado",
"net_hotspot":"Punto de acceso {ap}","net_off":"Wi-Fi desconectada","net_lost":"sin conexión con el reloj",
"sec_sys":"Sistema","mir":"LED 0 delante arriba a la derecha (espejo)","srp":"Matriz cableada en zigzag",
"restart":"Reiniciar","reset":"Restablecer de fábrica",
"q_restart":"¿Reiniciar el reloj?","q_reset":"¿Borrar todos los ajustes incluida la Wi-Fi?",
"language":"Idioma","firmware":"Firmware","uptime":"Tiempo en marcha","heap":"Memoria libre",
"footer":"{ap} – instrucciones de montaje, código y archivos de impresión:",
"saved":"Guardado","saved_restart":"Guardado – el reloj se reinicia …","save_err":"Error al guardar",
"time_set":"Hora tomada","restarting":"El reloj se reinicia …",
"srv_no_network":"No se ha introducido ninguna red","srv_back":"Volver","srv_saved":"Wi-Fi guardada",
"srv_connecting":"El reloj se conecta ahora a","srv_restart":"y se reinicia para ello. El punto de acceso desaparece.",
"srv_reach":"Después accesible en","srv_reach2":"o por la dirección IP del router o del monitor serie.",
"srv_retry":"Si la conexión falla, el punto de acceso vuelve a aparecer tras unos 30 segundos.",
"srv_not_found":"No encontrado"
})JSON";
}  // namespace wc_es
static const WcLangDef WC_LANG = {
    "ES", "Español", wc_es::GRID,
    {14, 1, 8},   // VENTILAR
    {14, 10, 6},  // ALARMA
    {15, 1, 3},   // BAT
    {15, 6, 10},  // battery bars
    wc_es::EXTRA, 1,  // HOLA
    wc_es::time_words,
    "reloj", "Reloj",
    40.4168f, -3.7038f,            // Madrid
    "CET-1CEST,M3.5.0,M10.5.0/3",  // Europe/Madrid
    "%d/%m/%Y",
    wc_es::UI_JSON,
};
