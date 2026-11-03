/*
  preview.cpp - Wordclock 16x16, host preview of a language file, v2.0
  Compiles the shared core + effects + one language with any C++ compiler (no Arduino/ESPHome needed)
  and prints the words for every 5 minutes (and with single minutes), plus the lit grid for some times.

  Build and run (from the repository root):
    g++ -std=c++11 -Wall -Wextra -DLANG=DE tools/preview.cpp -o preview && ./preview
    g++ -std=c++11 -Wall -Wextra -DLANG=GB tools/preview.cpp -o preview && ./preview grid 13:47
  Arguments: (none) = all 5-minute steps of 0:00-23:59 with "+n minutes" for hh:x7,
             grid hh:mm [time] = show the lit cells of that time ("time": only the time words),
             all = every single minute of the day,
             used = grid with every cell that is never lit (filler) shown as "x" (tools/check_lang.py, make_info.py)
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define WC_STR2(x) #x
#define WC_STR(x) WC_STR2(x)
#ifndef LANG
#define LANG DE
#endif
#define WC_CAT(a, b) a##b
#define WC_LANG_PATH2(n) WC_STR(../arduino/Wordclock/src/n.h)
#define WC_LANG_PATH1(n) WC_LANG_PATH2(n)
#define WC_LANG_PATH(l) WC_LANG_PATH1(WC_CAT(wc_lang_, l))

#include "../arduino/Wordclock/src/wc_core.h"
#include "../arduino/Wordclock/src/wc_effects.h"
#include WC_LANG_PATH(LANG)

static void clock_in(WcClockIn &in, int h, int m) {
  memset(&in, 0, sizeof(in));
  in.valid = true; in.hour = h; in.minute = m; in.show_minutes = true;
  in.show_vent = in.show_alarm = in.show_battery = true; in.vent = in.alarm = true; in.battery = 75.0f;
  in.show_temp = true; in.t_out = 12.0f; in.t_in = 22.0f;
  in.t_out_lo = 5; in.t_out_hi = 30; in.t_in_lo = 20; in.t_in_hi = 25;
  in.c_time = wc_rgb(255, 255, 255); in.c_vent = in.c_alarm = in.c_battery = wc_rgb(255, 0, 0);
  in.show_extra = true;
  in.tout_scale = in.tin_scale = true;
}

static void print_grid(int h, int m, bool time_only) {
  WcClockIn in;
  clock_in(in, h, m);
  if (time_only) in.show_temp = in.show_vent = in.show_alarm = in.show_battery = in.show_extra = false;
  WcRgb f[WC_N];
  wc_render_clock(WC_LANG, in, f);
  char txt[256];
  wc_time_text(WC_LANG, true, h, m, true, txt, sizeof(txt));
  printf("%02d:%02d  %s\n", h, m, txt);
  for (int r = 0; r < WC_ROWS; r++) {
    printf("  ");
    for (int c = 0; c < WC_COLS; c++) {
      const char *a = wc_u8_at(WC_LANG.grid[r], c);
      const char *b = wc_u8_at(a, 1);
      const bool lit = f[r * WC_COLS + c].r || f[r * WC_COLS + c].g || f[r * WC_COLS + c].b;
      if (lit) printf("%.*s", (int)(b - a), a); else printf("·");
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {
  // sanity checks of the language definition
  int err = 0;
  for (int r = 0; r < WC_ROWS; r++) {
    const int n = wc_u8_count(WC_LANG.grid[r]);
    if (n != WC_COLS) { printf("ERROR: grid row %d has %d characters\n", r + 1, n); err++; }
  }
  char buf[512];
  const char *keys[] = {"html_lang", "dec", "srv_saved", "srv_not_found", "fx_rainbow", "pal_0"};
  for (size_t i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    if (!wc_json_get(WC_LANG.ui_json, keys[i], buf, sizeof(buf))) { printf("ERROR: ui_json key %s missing\n", keys[i]); err++; }
  for (int i = 0; i < WC_FX_COUNT; i++) {
    char k[40];
    snprintf(k, sizeof(k), "fx_%s", WC_FX[i].key);
    if (!wc_json_get(WC_LANG.ui_json, k, buf, sizeof(buf))) { printf("ERROR: ui_json key %s missing\n", k); err++; }
  }
  printf("Language %s (%s), host %s, hotspot %s\n", WC_LANG.code, WC_LANG.name, WC_LANG.host, WC_LANG.ap_ssid);

  if (argc >= 2 && strcmp(argv[1], "used") == 0) {
    // OR of the lit cells over every minute of the day (all displays on); "*" and "|" always count as used
    static bool used[WC_N];
    for (int v = 0; v < 3; v++)  // v = 0: valid time, 1: without single minutes, 2: no time yet
    for (int h = 0; h < 24; h++)
      for (int m = 0; m < 60; m++) {
        WcClockIn in;
        clock_in(in, h, m);
        in.show_minutes = v != 1;
        in.valid = v != 2;
        WcRgb f[WC_N];
        wc_render_clock(WC_LANG, in, f);
        for (int i = 0; i < WC_N; i++)
          if (f[i].r || f[i].g || f[i].b) used[i] = true;
      }
    for (int r = 0; r < WC_ROWS; r++) {
      for (int c = 0; c < WC_COLS; c++) {
        const char *a = wc_u8_at(WC_LANG.grid[r], c);
        const char *b = wc_u8_at(a, 1);
        if (used[r * WC_COLS + c] || *a == '*' || *a == '|') printf("%.*s", (int)(b - a), a); else printf("x");
      }
      printf("\n");
    }
    return err ? 1 : 0;
  }
  if (argc >= 3 && strcmp(argv[1], "grid") == 0) {
    int h = 0, m = 0;
    sscanf(argv[2], "%d:%d", &h, &m);
    print_grid(h, m, argc >= 4 && strcmp(argv[3], "time") == 0);
    return err ? 1 : 0;
  }
  char txt[256];
  wc_time_text(WC_LANG, false, 0, 0, true, txt, sizeof(txt));
  printf("no time  %s\n", txt);
  const bool all = argc >= 2 && strcmp(argv[1], "all") == 0;
  for (int h = 0; h < 24; h++)
    for (int m = 0; m < 60; m++) {
      if (!all && m % 5 != 0 && m % 10 != 7) continue;
      wc_time_text(WC_LANG, true, h, m, true, txt, sizeof(txt));
      printf("%02d:%02d  %s\n", h, m, txt);
    }
  if (err) printf("%d ERROR(S)\n", err);
  return err ? 1 : 0;
}
