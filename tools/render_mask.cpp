/*
  render_mask.cpp - Wordclock 16x16, helper for tools/render_fronts.py, v1.0
  Compiles the shared core + one language and prints the lit cells of one time (same logic as the clock).
  Build: g++ -std=c++11 -DLANG=DE tools/render_mask.cpp -o render_mask
  Run:   render_mask hh:mm RRGGBB features
         features = 0 (time and minutes only) or 1 (also VENT, ALARM, battery, temperature dots)
  Output: line 1 "code<TAB>name<TAB>time text", then 16 rows of the grid (UTF-8),
          then 16 lines with 16 colours each (hex RRGGBB, 000000 = off).
  Run:   render_mask all          (used by tools/make_masks.py for the mask cache)
  Output: line 1 "code<TAB>name", 16 grid rows, 1440 lines "mask<TAB>time text" (mask = 64 hex digits, bit 255 =
          cell 0), then one line with the additional displays: "cell=RRGGBB" or "cell=T" (T = colour of the time).
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
#include WC_LANG_PATH(LANG)

static void render_bits(int h, int m, bool features, unsigned col, WcRgb *f) {
  WcClockIn in;
  memset(&in, 0, sizeof(in));
  in.valid = true; in.hour = h; in.minute = m; in.show_minutes = true;
  in.c_time = wc_hex(col);
  if (features) {
    in.show_vent = in.show_alarm = in.show_battery = in.show_tout = in.show_tin = true;
    in.vent = in.alarm = true; in.battery = 70.0f;
    in.t_out = 12.0f; in.t_in = 22.0f;
    in.t_out_lo = 5; in.t_out_hi = 30; in.t_in_lo = 20; in.t_in_hi = 25;
    in.tout_scale = in.tin_scale = true;
    in.c_vent = in.c_alarm = in.c_battery = wc_hex(col);
  } else {
    in.battery = NAN; in.t_out = NAN; in.t_in = NAN;
  }
  wc_render_clock(WC_LANG, in, f);
}

static int dump_all() {
  printf("%s\t%s\n", WC_LANG.code, WC_LANG.name);
  for (int r = 0; r < WC_ROWS; r++) printf("%s\n", WC_LANG.grid[r]);
  WcRgb f[WC_N], g[WC_N], b[WC_N];
  char txt[256];
  for (int t = 0; t < 1440; t++) {
    render_bits(t / 60, t % 60, false, 0xFFFFFF, f);
    for (int i = 0; i < WC_N; i += 4) {
      int v = 0;
      for (int k = 0; k < 4; k++) v = (v << 1) | (f[i + k].r || f[i + k].g || f[i + k].b ? 1 : 0);
      printf("%x", v);
    }
    wc_time_text(WC_LANG, true, t / 60, t % 60, true, txt, sizeof(txt));
    printf("\t%s\n", txt);
  }
  // additional displays at 10:22 with two different time colours: cells that follow the time colour = T
  render_bits(10, 22, false, 0xFFFFFF, f);
  render_bits(10, 22, true, 0xFFFFFF, g);
  render_bits(10, 22, true, 0x123456, b);
  for (int i = 0; i < WC_N; i++) {
    const bool on = g[i].r || g[i].g || g[i].b, base = f[i].r || f[i].g || f[i].b;
    if (!on || base) continue;
    if (g[i].r != b[i].r || g[i].g != b[i].g || g[i].b != b[i].b) printf("%d=T ", i);
    else printf("%d=%02X%02X%02X ", i, g[i].r, g[i].g, g[i].b);
  }
  printf("\n");
  return 0;
}

int main(int argc, char **argv) {
  if (argc >= 2 && strcmp(argv[1], "all") == 0) return dump_all();
  int h = 10, m = 22;
  unsigned col = 0xFFFFFF;
  int features = 0;
  if (argc >= 2) sscanf(argv[1], "%d:%d", &h, &m);
  if (argc >= 3) col = (unsigned)strtoul(argv[2], nullptr, 16);
  if (argc >= 4) features = atoi(argv[3]);

  WcClockIn in;
  memset(&in, 0, sizeof(in));
  in.valid = true; in.hour = h; in.minute = m; in.show_minutes = true;
  in.c_time = wc_hex(col);
  if (features) {
    in.show_vent = in.show_alarm = in.show_battery = in.show_tout = in.show_tin = true;
    in.vent = in.alarm = true; in.battery = 70.0f;
    in.t_out = 12.0f; in.t_in = 22.0f;
    in.t_out_lo = 5; in.t_out_hi = 30; in.t_in_lo = 20; in.t_in_hi = 25;
    in.tout_scale = in.tin_scale = true;
    in.c_vent = in.c_alarm = in.c_battery = wc_hex(col);
  } else {
    in.battery = NAN; in.t_out = NAN; in.t_in = NAN;
  }
  WcRgb f[WC_N];
  wc_render_clock(WC_LANG, in, f);
  char txt[256];
  wc_time_text(WC_LANG, true, h, m, true, txt, sizeof(txt));
  printf("%s\t%s\t%s\n", WC_LANG.code, WC_LANG.name, txt);
  for (int r = 0; r < WC_ROWS; r++) printf("%s\n", WC_LANG.grid[r]);
  for (int r = 0; r < WC_ROWS; r++) {
    for (int c = 0; c < WC_COLS; c++) {
      const WcRgb &p = f[r * WC_COLS + c];
      printf("%s%02X%02X%02X", c ? " " : "", p.r, p.g, p.b);
    }
    printf("\n");
  }
  return 0;
}
