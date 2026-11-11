/*
  wc_ui_en.h - Wordclock 16x16, English web interface as alternative (Arduino only), v1.0
  Makes the English texts (ui_json of src/wc_lang_GB.h) available in every language, switch "Web interface in
  English" (setting uiEn). Only the texts are used: grid and time words of GB are not referenced and are removed by
  the linker (approx. 7 KB flash for the texts, nothing extra when the language is GB).
  Include AFTER WC_LANG_FILE: the language def of GB is renamed so that it does not collide with WC_LANG.
  If the language is GB, #pragma once skips the second include and wc_gb::UI_JSON already exists.
*/
#pragma once
#define WC_LANG WC_LANG_GB_UI_ONLY
#include "src/wc_lang_GB.h"
#undef WC_LANG

static const char *const WC_UI_EN = wc_gb::UI_JSON;
