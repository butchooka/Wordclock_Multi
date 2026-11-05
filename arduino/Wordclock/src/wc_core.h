/*
  wc_core.h - Wordclock 16x16, shared core (Arduino + ESPHome), v2.0
  Plain C++ without Arduino/ESPHome dependencies. Used by:
    - arduino/Wordclock/Wordclock.ino   (#include "src/wc_core.h")
    - esphome/wordclock_multi/core.yaml       (esphome: includes:)
    - tools/preview.cpp                 (host preview of a language)

  Contents: types, palette, UTF-8 grid helpers, word marking, clock rendering (time words via the language
  file, status words, battery bars, temperature dots), temperature colours, HSV, brightness/current limit
  and LED mapping (mirror / serpentine).

  Layout contract for every language (16 x 16, row 0 = top, column 0 = left as seen from the front):
    - column 0 and 15, rows 0..12: temperature dots ("*"), left = outside, right = inside
    - rows 0..12, columns 1..14: time words (language specific)
    - row 13: minute row ("+", digits 1-4, MINUTE(S) word) - handled by the language time function
    - row 14: VENT and ALARM words, row 15: BATTERY word + 10 bars ("|")
*/
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#define WC_VERSION "2.0"
#define WC_ROWS 16
#define WC_COLS 16
#define WC_N (WC_ROWS * WC_COLS)

struct WcRgb { uint8_t r, g, b; };
struct WcWord { uint8_t r, c, n; };   // row, first column, length in cells

static inline WcRgb wc_rgb(uint8_t r, uint8_t g, uint8_t b) { WcRgb c = {r, g, b}; return c; }
static inline WcRgb wc_hex(uint32_t v) { return wc_rgb((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF); }
static inline WcRgb wc_scale(WcRgb c, float v) {
  return wc_rgb((uint8_t)(c.r * v), (uint8_t)(c.g * v), (uint8_t)(c.b * v));
}

// Palette: warm white, white, red, orange, yellow, green, blue, violet (index 0..7, same in all languages)
static const WcRgb WC_PAL[8] = {{255, 140, 40}, {255, 255, 255}, {255, 0, 0}, {255, 70, 0},
                                {255, 190, 0},  {0, 255, 0},     {0, 0, 255}, {150, 0, 255}};
// Colour keys for the HTTP API (never translated)
static const char *const WC_PAL_KEYS[8] = {"warmwhite", "white", "red", "orange", "yellow", "green", "blue", "violet"};

// ------------------------------------------------------------------------------------------------
// Small random generator (xorshift32), identical on all platforms. Seed once with wc_seed().
static uint32_t wc_rng_state = 0x9E3779B9u;
static inline void wc_seed(uint32_t s) { wc_rng_state = s ? s : 0x9E3779B9u; }
static inline uint32_t wc_rand() {
  uint32_t x = wc_rng_state;
  x ^= x << 13; x ^= x >> 17; x ^= x << 5;
  return wc_rng_state = x;
}
static inline uint32_t wc_rand_n(uint32_t n) { return n ? wc_rand() % n : 0; }

// ------------------------------------------------------------------------------------------------
// UTF-8: the grid rows are UTF-8 strings with exactly 16 characters (code points) each.
static inline int wc_u8len(unsigned char c) {
  if (c < 0x80) return 1;
  if ((c >> 5) == 0x06) return 2;
  if ((c >> 4) == 0x0E) return 3;
  if ((c >> 3) == 0x1E) return 4;
  return 1;
}
// pointer to code point number idx in s (or to the terminating 0)
static inline const char *wc_u8_at(const char *s, int idx) {
  while (*s && idx > 0) { s += wc_u8len((unsigned char)*s); idx--; }
  return s;
}
static inline int wc_u8_count(const char *s) {
  int n = 0;
  while (*s) { s += wc_u8len((unsigned char)*s); n++; }
  return n;
}

// ------------------------------------------------------------------------------------------------
// Word marking. The language time function calls m.word(...) / m.at(...) / m.glue(...).
// cell != nullptr: the cells get the group number; txt != nullptr: the text (taken from the grid) is appended.
// word(): text separated by a space. glue(): text appended without a space, for a word that is split in the
// grid (e.g. IT "MINUTIO": MINUT + O = MINUTO). The lit cells are the same for word() and glue().
struct WcMark {
  int8_t *cell;
  int8_t group;
  const char *const *grid;
  char *txt;
  size_t cap, len;
  int8_t *word_id;  // optional: word index per cell (pride colouring), one id per word() run
  int widx;         // running word counter (glue() reuses the last word)

  void word(const WcWord &w) { add(w, true); }
  void glue(const WcWord &w) { add(w, false); }
  void add(const WcWord &w, bool space) {
    if (w.r >= WC_ROWS || w.n == 0) return;
    int wid = -1;
    if (word_id) { if (space) { wid = widx++; } else { wid = widx > 0 ? widx - 1 : 0; } }
    if (cell)
      for (int i = 0; i < w.n; i++) {
        const int c = w.c + i;
        if (c >= 0 && c < WC_COLS) { cell[w.r * WC_COLS + c] = group; if (word_id) word_id[w.r * WC_COLS + c] = (int8_t)wid; }
      }
    if (txt && grid && cap > 1) {
      const char *a = wc_u8_at(grid[w.r], w.c);
      const char *b = wc_u8_at(a, w.n);
      size_t n = (size_t)(b - a);
      if (space && len && len + 1 < cap) txt[len++] = ' ';
      if (len + n >= cap) n = cap - 1 - len;
      memcpy(txt + len, a, n);
      len += n;
      txt[len] = 0;
    }
  }
  void at(int r, int c) { WcWord w = {(uint8_t)r, (uint8_t)c, 1}; word(w); }
};

// valid = false: no time yet, only the prefix ("IT IS") should be marked
typedef void (*WcTimeFn)(bool valid, int hour, int minute, bool show_minutes, WcMark &m);

// One language = one WcLangDef named WC_LANG in src/wc_lang_XX.h
struct WcLangDef {
  const char *code;              // file suffix, e.g. "DE", "GB"
  const char *name;              // own name, e.g. "Deutsch"
  const char *const *grid;       // 16 rows, UTF-8, must match models/lang/lang_XX.scad
  WcWord vent, alarm, battery;   // status words (rows 14/15)
  WcWord bars;                   // battery bars (10 cells)
  const WcWord *extra;           // optional extra words (easter egg), shown with the time colour
  uint8_t extra_n;
  WcTimeFn time_words;
  // Arduino only: defaults for the first start and the texts of the web interface
  const char *host;              // mDNS name (lower case, a-z 0-9 -)
  const char *ap_ssid;           // hotspot name
  float lat, lon;                // capital of the language's main country
  const char *posix_tz;          // POSIX time zone of that capital
  const char *date_fmt;          // strftime format of the date in the web interface
  const char *ui_json;           // translations of the web interface (flat JSON object, string values only)
};

// Read a string value from the flat JSON of ui_json (simple, no nesting). Returns false if not found.
static inline bool wc_json_get(const char *json, const char *key, char *out, size_t cap) {
  if (!json || !key || !out || cap == 0) return false;
  out[0] = 0;
  const size_t kl = strlen(key);
  const char *p = json;
  while ((p = strchr(p, '"')) != nullptr) {
    p++;
    if (strncmp(p, key, kl) == 0 && p[kl] == '"') {
      const char *q = p + kl + 1;
      while (*q == ' ' || *q == '\t' || *q == '\r' || *q == '\n') q++;
      if (*q != ':') continue;
      q++;
      while (*q == ' ' || *q == '\t' || *q == '\r' || *q == '\n') q++;
      if (*q != '"') return false;
      q++;
      size_t n = 0;
      while (*q && *q != '"' && n + 1 < cap) {
        if (*q == '\\' && q[1]) {
          q++;
          out[n++] = (*q == 'n') ? '\n' : *q;
        } else {
          out[n++] = *q;
        }
        q++;
      }
      out[n] = 0;
      return true;
    }
    // skip the rest of this string
    while (*p && *p != '"') { if (*p == '\\' && p[1]) p++; p++; }
    if (*p) p++;
  }
  return false;
}

// ------------------------------------------------------------------------------------------------
// Colours
static inline void wc_hsv(float h, float s, float v, WcRgb &o) {
  h = fmodf(h, 360.0f);
  if (h < 0) h += 360.0f;
  const float c = v * s, x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f)), m = v - c;
  float r = 0, g = 0, b = 0;
  switch ((int)(h / 60.0f)) {
    case 0: r = c; g = x; break;
    case 1: r = x; g = c; break;
    case 2: g = c; b = x; break;
    case 3: g = x; b = c; break;
    case 4: r = x; b = c; break;
    default: r = c; b = x; break;
  }
  o = wc_rgb((uint8_t)((r + m) * 255.0f), (uint8_t)((g + m) * 255.0f), (uint8_t)((b + m) * 255.0f));
}

// Colour from the scale: below dark blue, lower quarter yellow, middle green (comfort), upper quarter orange, above red
static inline WcRgb wc_temp_color(float T, float lo, float hi) {
  if (hi <= lo) hi = lo + 1.0f;
  const float p = (T - lo) / (hi - lo);
  if (p < 0.0f) return wc_rgb(0, 0, 160);
  if (p > 1.0f) return wc_rgb(255, 0, 0);
  if (p < 0.25f) return wc_rgb(255, 190, 0);
  if (p < 0.75f) return wc_rgb(0, 255, 0);
  return wc_rgb(255, 70, 0);
}

// Row of a temperature value: row 12 = start of the scale, row 0 = end of the scale
static inline int wc_temp_row(float T, float lo, float hi) {
  if (hi <= lo) hi = lo + 1.0f;
  float p = (T - lo) / (hi - lo);
  if (p < 0.0f) p = 0.0f;
  if (p > 1.0f) p = 1.0f;
  return 12 - (int)(p * 12.0f + 0.5f);
}

// Palette selection 0..7, everything above = random colour rnd (0..7, changes every hour)
static inline WcRgb wc_pal_or_random(int sel, int rnd) {
  if (sel < 0 || sel > 7) sel = (rnd >= 0 && rnd < 8) ? rnd : 0;
  return WC_PAL[sel];
}

// new random palette index, never the same twice in a row
static inline int wc_pick_random(int old) {
  int n;
  do { n = (int)wc_rand_n(8); } while (n == old);
  return n;
}

// ------------------------------------------------------------------------------------------------
// Clock rendering
struct WcClockIn {
  bool valid;                  // time known
  int hour, minute;            // local time
  bool show_minutes, show_tout, show_tin, show_vent, show_alarm, show_battery, show_extra;
  bool vent, alarm;
  float battery;               // percent, NAN = unknown
  float t_out, t_in;           // degC, NAN = unknown
  float t_out_lo, t_out_hi, t_in_lo, t_in_hi;
  WcRgb c_time, c_vent, c_alarm, c_battery;
  bool tout_scale, tin_scale;  // true = colour from the temperature scale, false = c_tout / c_tin
  WcRgb c_tout, c_tin;
  bool pride;                  // time words in pride mode: one random colour per word
  const WcRgb *pride_col;      // per-word colours (valid when pride is set, see wc_pride_refresh)
};

// Pride colouring: one random colour per time word, re-rolled on every full minute (stable within the minute).
// minute_of_day = hour * 60 + minute (-1 = no time yet: colours are rolled once and kept).
static WcRgb wc_pride_buf[WC_N];
static int32_t wc_pride_min = -2;
static inline const WcRgb *wc_pride_refresh(int32_t minute_of_day) {
  if (minute_of_day != wc_pride_min) {
    wc_pride_min = minute_of_day;
    for (int i = 0; i < WC_N; i++)
      wc_hsv((float)(wc_rand_n(360)), 1.0f, 1.0f, wc_pride_buf[i]);
  }
  return wc_pride_buf;
}

// Groups: 0 time/minutes/extra, 1 VENT, 2 ALARM, 3 BATTERY, 4 bars, 5 temperature outside, 6 temperature inside
static inline void wc_render_clock(const WcLangDef &L, const WcClockIn &in, WcRgb *frame) {
  int8_t cell[WC_N];
  memset(cell, -1, sizeof(cell));
  int8_t wid_arr[WC_N];
  memset(wid_arr, -1, sizeof(wid_arr));
  WcMark m = {cell, 0, L.grid, nullptr, 0, 0, wid_arr, 0};
  L.time_words(in.valid, in.hour, in.minute, in.show_minutes, m);
  if (in.show_extra)
    for (int i = 0; i < L.extra_n; i++) m.word(L.extra[i]);

  m.group = 1;
  if (in.show_vent && in.vent) m.word(L.vent);
  m.group = 2;
  if (in.show_alarm && in.alarm) m.word(L.alarm);
  float lvl = in.battery;
  if (isnan(lvl)) lvl = 0.0f;
  if (in.show_battery && lvl > 10.0f) {  // 10 % or less: BATTERY word and bars off
    m.group = 3;
    m.word(L.battery);
    int n = (int)(lvl / 10.0f);          // 20 % = 2 bars
    if (n > L.bars.n) n = L.bars.n;
    for (int i = 0; i < n; i++) cell[L.bars.r * WC_COLS + L.bars.c + i] = 4;
  }
  // column 0 = outside, column 15 = inside
  if (in.show_tout && !isnan(in.t_out)) cell[wc_temp_row(in.t_out, in.t_out_lo, in.t_out_hi) * WC_COLS + 0] = 5;
  if (in.show_tin && !isnan(in.t_in)) cell[wc_temp_row(in.t_in, in.t_in_lo, in.t_in_hi) * WC_COLS + 15] = 6;

  WcRgb gc[7];
  gc[0] = in.c_time;
  gc[1] = in.c_vent;
  gc[2] = in.c_alarm;
  gc[3] = in.c_battery;
  gc[4] = in.c_battery;                  // bars in the same colour as the BATTERY word
  gc[5] = in.tout_scale ? wc_temp_color(in.t_out, in.t_out_lo, in.t_out_hi) : in.c_tout;
  gc[6] = in.tin_scale ? wc_temp_color(in.t_in, in.t_in_lo, in.t_in_hi) : in.c_tin;
  for (int i = 0; i < WC_N; i++) {
    if (cell[i] < 0) frame[i] = wc_rgb(0, 0, 0);
    else if (in.pride && in.pride_col && cell[i] == 0 && wid_arr[i] >= 0) frame[i] = in.pride_col[wid_arr[i]];
    else frame[i] = gc[cell[i]];
  }
}

// Time as text (words separated by spaces, taken from the grid), e.g. for the web interface
static inline void wc_time_text(const WcLangDef &L, bool valid, int hour, int minute, bool show_minutes, char *out, size_t cap) {
  if (!out || !cap) return;
  out[0] = 0;
  WcMark m = {nullptr, 0, L.grid, out, cap, 0};
  L.time_words(valid, hour, minute, show_minutes, m);
}

// ------------------------------------------------------------------------------------------------
// Output: brightness bf (0..1), current limit (estimate from all colour values, gamma 1), LED mapping.
// set(index, r, g, b) is called for every LED.
template <typename F>
static inline void wc_output(const WcRgb *f, float bf, float limit_ma, float ma_per_channel, float idle_ma_per_led,
                      bool mirror, bool serpentine, F set) {
  float sum = 0.0f;
  for (int i = 0; i < WC_N; i++) sum += f[i].r + f[i].g + f[i].b;
  const float dyn = (sum / 255.0f) * ma_per_channel * bf;
  const float budget = limit_ma - idle_ma_per_led * WC_N;
  float lim = 1.0f;
  if (dyn > budget) lim = (budget > 0.0f) ? budget / dyn : 0.0f;
  const float k = bf * lim;
  for (int r = 0; r < WC_ROWS; r++)
    for (int c = 0; c < WC_COLS; c++) {
      const WcRgb &p = f[r * WC_COLS + c];
      const int cc = mirror ? (WC_COLS - 1 - c) : c;
      const int idx = (serpentine && (r & 1)) ? r * WC_COLS + (WC_COLS - 1 - cc) : r * WC_COLS + cc;
      set(idx, (uint8_t)(p.r * k), (uint8_t)(p.g * k), (uint8_t)(p.b * k));
    }
}
