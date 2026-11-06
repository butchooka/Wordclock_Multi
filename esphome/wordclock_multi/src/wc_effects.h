/*
  wc_effects.h - Wordclock 16x16, effect register (Arduino + ESPHome), v1.0

  Adding an effect:
    1. write a function  static void wc_fx_name(WcRgb *f, const WcFxCtx &c)  that fills all 256 pixels
       (f is cleared to black before the call, row 0 = top, index = row * 16 + column)
    2. add one line to WC_FX below (key = HTTP API name, never translated; uses_color = uses c.color)
    3. ESPHome: add the option to the select "fx_sel" in esphome/wordclock_multi/core.yaml (same position as in WC_FX)
       and its name ("fx_<key>") to every esphome/wordclock_multi/lang/lang_XX.yaml
    4. Arduino web interface: add "fx_<key>" to the ui_json of every src/wc_lang_XX.h (the buttons are built
       automatically from this list)
  The order of WC_FX is the effect number (1 = first entry, 0 = no effect / clock).
*/
#pragma once
#include "wc_core.h"

struct WcFxCtx {
  uint32_t ms;     // milliseconds since start of the device
  float t;         // ms / 1000
  float ts;        // seconds since the effect was started
  float cycle;     // blink cycle in seconds (setting)
  WcRgb color;     // effect colour (setting / API), used by effects with uses_color
};
typedef void (*WcFxFn)(WcRgb *f, const WcFxCtx &c);
struct WcFx { const char *key; WcFxFn fn; bool uses_color; };

// ---------------- Rainbow ----------------
static inline void wc_fx_rainbow(WcRgb *f, const WcFxCtx &c) {
  for (int r = 0; r < WC_ROWS; r++)
    for (int col = 0; col < WC_COLS; col++) wc_hsv(fmodf(c.ms / 6.0f + (r + col) * 14.0f, 360.0f), 1.0f, 1.0f, f[r * WC_COLS + col]);
}

// ---------------- Aurora: green - turquoise - blue - violet, waving veils ----------------
static inline void wc_fx_aurora(WcRgb *f, const WcFxCtx &c) {
  const float tm = c.t;
  for (int r = 0; r < WC_ROWS; r++)
    for (int col = 0; col < WC_COLS; col++) {
      const float w1 = sinf(col * 0.45f + tm * 0.6f + sinf(r * 0.35f - tm * 0.35f) * 1.6f);
      const float w2 = sinf(r * 0.5f - tm * 0.45f + sinf(col * 0.3f + tm * 0.25f) * 1.8f);
      const float hue = 130.0f + 130.0f * (0.5f + 0.25f * w1 + 0.25f * w2);
      const float val = 0.25f + 0.75f * (0.5f + 0.5f * sinf(col * 0.6f + tm * 0.9f + w2 * 1.5f));
      wc_hsv(hue, 1.0f, val, f[r * WC_COLS + col]);
    }
}

// ---------------- Matrix: green traces fall from top to bottom ----------------
static inline void wc_fx_matrix(WcRgb *f, const WcFxCtx &c) {
  for (int col = 0; col < WC_COLS; col++) {
    const uint32_t h = (uint32_t)col * 2654435761u;
    const float spd = 5.0f + ((h >> 8) % 60) / 10.0f;          // 5..11 rows per second
    const float offs = (float)((h >> 16) % 40);
    const float head = fmodf(c.t * spd + offs, WC_ROWS + 12.0f);  // head position incl. pause
    for (int r = 0; r < WC_ROWS; r++) {
      const float d = head - r;                                   // distance behind the head
      WcRgb &p = f[r * WC_COLS + col];
      if (d >= 0.0f && d < 1.0f) p = wc_rgb(180, 255, 180);
      else if (d >= 1.0f && d < 9.0f) { const float k = 1.0f - (d - 1.0f) / 8.0f; p = wc_rgb(0, (uint8_t)(255.0f * k * k), 0); }
    }
  }
}

// ---------------- Fire: classic heat simulation per column, flames rise from the bottom ----------------
static inline void wc_fx_fire(WcRgb *f, const WcFxCtx &c) {
  static uint8_t heat[WC_COLS][WC_ROWS];  // [column][0 = bottom]
  static uint32_t last = 0;
  if (c.ms - last >= 40 || c.ms < last) {
    last = c.ms;
    for (int x = 0; x < WC_COLS; x++) {
      for (int y = 0; y < WC_ROWS; y++) {  // cool down
        const int cool = (int)wc_rand_n(36);
        heat[x][y] = heat[x][y] > cool ? heat[x][y] - cool : 0;
      }
      for (int y = WC_ROWS - 1; y >= 2; y--) heat[x][y] = (heat[x][y - 1] + 2 * heat[x][y - 2]) / 3;  // rise
      if (wc_rand_n(255) < 130) {          // new spark near the bottom
        const int y = (int)wc_rand_n(3);
        const int v = heat[x][y] + 160 + (int)wc_rand_n(95);
        heat[x][y] = v > 255 ? 255 : v;
      }
    }
  }
  for (int x = 0; x < WC_COLS; x++)
    for (int r = 0; r < WC_ROWS; r++) {
      const uint8_t t192 = (uint8_t)((heat[x][WC_ROWS - 1 - r] * 191) / 255);
      const uint8_t ramp = (uint8_t)((t192 & 0x3F) << 2);
      WcRgb &p = f[r * WC_COLS + x];
      if (t192 & 0x80) p = wc_rgb(255, 255, ramp);
      else if (t192 & 0x40) p = wc_rgb(255, ramp, 0);
      else p = wc_rgb(ramp, 0, 0);
    }
}

// ---------------- Confetti: random coloured dots that fade out ----------------
static inline void wc_fx_confetti(WcRgb *f, const WcFxCtx &c) {
  static WcRgb buf[WC_N];
  static uint32_t last = 0;
  if (c.ms - last >= 50 || c.ms < last) {
    last = c.ms;
    for (int i = 0; i < WC_N; i++) buf[i] = wc_scale(buf[i], 0.88f);
    for (int k = 0; k < 2; k++) wc_hsv((float)wc_rand_n(360), 0.85f, 1.0f, buf[wc_rand_n(WC_N)]);
  }
  memcpy(f, buf, sizeof(buf));
}

// ---------------- Stars: dark blue sky, every pixel twinkles with its own speed and phase ----------------
static inline void wc_fx_stars(WcRgb *f, const WcFxCtx &c) {
  for (int i = 0; i < WC_N; i++) {
    const uint32_t h = (uint32_t)(i + 1) * 2654435761u;
    const float phase = ((h >> 8) & 1023) / 1023.0f * 6.2831853f;
    const float speed = 0.5f + ((h >> 18) & 255) / 255.0f * 1.5f;
    float v = sinf(c.t * speed + phase);
    v = v > 0.0f ? v * v * v * v * v * v : 0.0f;   // mostly dark, short bright moments
    const int warm = (h >> 4) & 1;                  // half of the stars slightly warm
    f[i] = wc_rgb((uint8_t)(255 * v), (uint8_t)((warm ? 215 : 235) * v), (uint8_t)(6 + (warm ? 170 : 249) * v));
  }
}

// ---------------- Blink: slow breathing of the whole matrix in the effect colour ----------------
static inline void wc_fx_blink(WcRgb *f, const WcFxCtx &c) {
  const float cyc = c.cycle > 0.1f ? c.cycle : 0.1f;
  float v = 0.5f - 0.5f * cosf(6.2831853f * c.ts / cyc);
  v = 0.04f + 0.96f * v;
  const WcRgb p = wc_scale(c.color, v);
  for (int i = 0; i < WC_N; i++) f[i] = p;
}

// ---------------- Register ----------------
static const WcFx WC_FX[] = {
    {"rainbow", wc_fx_rainbow, false},
    {"aurora", wc_fx_aurora, false},
    {"matrix", wc_fx_matrix, false},
    {"fire", wc_fx_fire, false},
    {"confetti", wc_fx_confetti, false},
    {"stars", wc_fx_stars, false},
    {"blink", wc_fx_blink, true},
};
static const int WC_FX_COUNT = (int)(sizeof(WC_FX) / sizeof(WC_FX[0]));

// effect number from key: 1..WC_FX_COUNT, 0 = "stop", -1 = unknown
static inline int wc_fx_find(const char *key) {
  if (!key) return -1;
  if (strcmp(key, "stop") == 0) return 0;
  for (int i = 0; i < WC_FX_COUNT; i++)
    if (strcmp(key, WC_FX[i].key) == 0) return i + 1;
  return -1;
}
static inline const char *wc_fx_key(int id) { return (id >= 1 && id <= WC_FX_COUNT) ? WC_FX[id - 1].key : "stop"; }

static inline void wc_fx_render(int id, WcRgb *f, const WcFxCtx &c) {
  memset(f, 0, sizeof(WcRgb) * WC_N);
  if (id >= 1 && id <= WC_FX_COUNT) WC_FX[id - 1].fn(f, c);
}
