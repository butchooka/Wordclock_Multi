/*
  config.h - Wordclock 16x16, Arduino settings, v2.0
  Only this file needs to be changed for a build. Everything else is set in the web interface.
*/
#pragma once

// build_firmware.bat writes wc_build.h only into its temporary copy of the sketch (never into this folder)
// and sets WC_LANG_FILE there. In the Arduino IDE this file does not exist and the settings below apply.
#if defined(__has_include)
#if __has_include("wc_build.h")
#include "wc_build.h"
#endif
#endif

// ============================ LANGUAGE ============================
// Language file in src/. Grid, time words, web interface, hotspot/device name and default location/time zone
// come from it. Copy one line of the list below over the #define (v2.0 = tested, v0.9 = in test).
#ifndef WC_LANG_FILE
#define WC_LANG_FILE "src/wc_lang_dialect_BAD.h"
#endif
//
// LANGUAGES BEGIN (list written by tools/make_info.py)
//   Countries / Länder:
//     #define WC_LANG_FILE "src/wc_lang_DE.h"  Deutsch (v2.0)
//     #define WC_LANG_FILE "src/wc_lang_GB.h"  English (v2.0)
//     #define WC_LANG_FILE "src/wc_lang_CN.h"  中文 (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_CZ.h"  Čeština (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_DK.h"  Dansk (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_ES.h"  Español (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_FR.h"  Français (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_GR.h"  Ελληνικά (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_HU.h"  Magyar (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_ID.h"  Bahasa Indonesia (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_IT.h"  Italiano (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_JP.h"  日本語 (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_KR.h"  한국어 (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_NL.h"  Nederlands (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_NO.h"  Norsk (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_PL.h"  Polski (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_PT.h"  Português (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_RO.h"  Română (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_SE.h"  Svenska (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_TR.h"  Türkçe (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_TZ.h"  Kiswahili (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_UA.h"  Українська (v0.9)
//   Dialects / Dialekte:
//     #define WC_LANG_FILE "src/wc_lang_dialect_BAD.h"  Badisch (v2.0)
//     #define WC_LANG_FILE "src/wc_lang_dialect_CH.h"   Schwizerdütsch (v2.0)
//     #define WC_LANG_FILE "src/wc_lang_dialect_SWG.h"  Schwäbisch (v2.0)
//   Other languages / andere Sprachen:
//     #define WC_LANG_FILE "src/wc_lang_EO.h"         Esperanto (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_VA.h"         Latina (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_scifi_HVA.h"  Valyrio (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_scifi_NAV.h"  Na'vi (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_scifi_QYA.h"  Quenya (v0.9)
//     #define WC_LANG_FILE "src/wc_lang_scifi_TLH.h"  tlhIngan Hol (v0.9)
// LANGUAGES END

// ============================ HARDWARE ============================
// data pin of the matrix, best via level shifter to 5 V. Default GPIO2 on all boards (ESP32-C6 SuperMini / XIAO,
// Wemos D1 mini ESP32, generic ESP32). Own pin: change the number, e.g.  #define LED_PIN 32
#ifndef LED_PIN
#define LED_PIN          2
#endif
#define MA_PER_CHANNEL   18.0f     // mA per colour channel at full scale (WS2812: 15-20)
#define IDLE_MA_PER_LED  1.0f      // idle current per LED (counts towards the current limit)
#define LED_ENABLE       1         // 0 = never drive the LEDs (test whether matrix/power supply causes crashes)
#define WIFI_TX_LOW      0         // 1 = reduce Wi-Fi transmit power (helps with a weak power supply)
#define AP_PASS          ""        // hotspot password, empty = open hotspot (otherwise at least 8 characters)
// #define AP_SSID       "MyClock" // hotspot name, default: from the language file (e.g. "Wortuhr")
