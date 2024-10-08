#include "quantum.h"
#include "../xanimos.h"
#include "oled_basic.h"
#include "print.h"
#include "usb_util.h"

#ifdef MOUSE_JIGGLE_ENABLE
#   include "mouse_util.h"
#endif

#define LOGO_FRAME_SIZE 512
#define LOGO_FRAME_DURATION 700

logo_anim_t logo_anim = {
    .frame = Frame1,
    .move_up = true,
    .timer = 0
};

void oled_render_keylock_status() {
    led_t keyboard_led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\nLock:"), false);
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR("\n  "), false);
    oled_write_P(PSTR("Num"), keyboard_led_state.num_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Caps"), keyboard_led_state.caps_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Scroll"), keyboard_led_state.scroll_lock);
#else
    oled_write_P(PSTR("N"), keyboard_led_state.num_lock);
    oled_write_P(PSTR("C"), keyboard_led_state.caps_lock);
    oled_write_P(PSTR("S"), keyboard_led_state.scroll_lock);
#endif

#ifdef MOUSE_JIGGLE_ENABLE
    #ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR("\n  "), false);
    oled_write_P(PSTR("Jiggle"), mouse_state.jiggle);
    #else
    oled_write_P(PSTR("J"), mouse_state.jiggle);
    #endif
    if (mouse_state.jiggle) {
        oled_write_ln_P(PSTR(" "), false);
        oled_write_P(PSTR("X"), mouse_state.x.move_started);
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("Y"), mouse_state.y.move_started);
    } else {
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
    }
#endif
}

void oled_render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR("\n  "), false);
    oled_write_P(PSTR("Ctrl"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Alt"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Shift"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
#else
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
#endif
}

void oled_render_mod_lock_status(void) {
  oled_render_mod_status(get_mods() | get_oneshot_mods());
  oled_render_keylock_status();
}

static const char* layer_text[] = {
#ifdef OLED_DISPLAY_128X64
    "QWERTY",
    "Symbols",
    "Numbers",
    "Function",
    "Git Commands",
    "Dev Commands",
    "Mod Keys",
    "Game Mode",
    "Layer Select",
    "Mouse Keys",
    "Unknown"
#else
    "QWERT",
    "$!@#\%",
    "12345",
    "Fn <>",
    "Git:\\",
    "Dev:\\",
    "Mods ",
    "Game ",
    "Selct",
    "Mouse",
    "Unkwn"
#endif
};

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    uint8_t current_layer = get_highest_layer(layer_state);
    if (current_layer < _ALPHA || current_layer > _UNKOWN) {
        current_layer = _UNKOWN;
    }
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(":\n  "), false);
    oled_write_P(PSTR(layer_text[current_layer]), false);
    oled_write_P(PSTR("\n"), false);
#else
    oled_write_ln_P(PSTR(layer_text[current_layer]), false);
#endif
}

static void oled_render_logo(void) {
    if (!oled_render_logo_km()) {
        return;
    }
    static const char PROGMEM raw_logo[MAX_FRAMES][LOGO_FRAME_SIZE] = {
        {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,248,255,255,127,255,255,240,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,252,255, 63,143,241,248,225,143, 63,255,248,134,  6,  6,  6,  6,  6,246,246,246,246,246,246,246,246,246,246,230,198,134,118,246,246,246,246,246,246,246,246,246,246,246,246, 54,246,246,246,230,198,134,  6,  6,  6,198,230,246,246,246,118, 54,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,252,255,199, 49,124,127,127,127,127,127,124, 49,199,255,252,192,  0,  0,  0,254,254,254,254,248,240,248,249,255,127,127, 63, 15,224,251,251,251,251,120,120,120,120,120,120,120,120,  0,  0,  3,  7,143,255,255,254,252,254,254,222, 14,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,254,255,255, 31,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 31,255,255,254,224,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,240,240,240,240,240,240,240,240,224,248,252,255,127, 31, 15,  7,  3,  7, 31, 63,255,254,248,240,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        },
        {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,248,255,255,127,255,255,240,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,252,255, 63,143,241,248,225,143, 63,255,248,134,  6,  6,  6,  6,  6,246,246,246,246,246,246,246,246,246,246,230,198,134,118,246,246,246,246,246,246,246,246,246,246,246,246, 54,246,246,246,230,198,134,  6,  6,  6,198,230,246,246,246,118, 54,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,252,255,199, 49,124,127,127,127,127,127,124, 49,199,255,252,192,  0,  0,  0,254,254,254,254,248,240,248,249,255,127,127, 63, 15,224,251,251,251,251,120,120,120,120,120,120,120,120,  0,  0,  3,  7,143,255,255,254,252,254,254,222, 14,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,254,255,255, 31,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 31,255,255,254,224,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,240,240,240,240,240,240,240,240,224,248,252,255,127, 31, 15,  7,  3,  7, 31, 63,255,254,248,240,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        },
        {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,248,255,255,127,255,255,240,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,252,255, 63,143,241,248,225,143, 63,255,248,134,  6,  6,  6,  6,  6,246,246,246,246,246,246,246,246,246,246,230,198,134,118,246,246,246,246,246,246,246,246,246,246,246,246, 54,246,246,246,230,198,134,  6,  6,  6,198,230,246,246,246,118, 54,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,252,255,199, 49,124,127,127,127,127,127,124, 49,199,255,252,192,  0,  0,  0,254,254,254,254,248,240,248,249,255,127,127, 63, 15,224,251,251,251,251,120,120,120,120,120,120,120,120,  0,  0,  3,  7,143,255,255,254,252,254,254,222, 14,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,254,255,255, 31,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 31,255,255,254,224,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,240,240,240,240,240,240,240,240,224,248,252,255,127, 31, 15,  7,  3,  7, 31, 63,255,254,248,240,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        },
        {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,248,255,255,127,255,255,240,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,252,255, 63,143,241,248,225,143, 63,255,248,134,  6,  6,  6,  6,  6,246,246,246,246,246,246,246,246,246,246,230,198,134,118,246,246,246,246,246,246,246,246,246,246,246,246, 54,246,246,246,230,198,134,  6,  6,  6,198,230,246,246,246,118, 54,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,252,255,199, 49,124,127,127,127,127,127,124, 49,199,255,252,192,  0,  0,  0,254,254,254,254,248,240,248,249,255,127,127, 63, 15,224,251,251,251,251,120,120,120,120,120,120,120,120,  0,  0,  3,  7,143,255,255,254,252,254,254,222, 14,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,254,255,255, 31,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 31,255,255,254,224,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,240,240,240,240,240,240,240,240,224,248,252,255,127, 31, 15,  7,  3,  7, 31, 63,255,254,248,240,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        },
        {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,248,255,255,127,255,255,240,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,252,255, 63,143,241,248,225,143, 63,255,248,134,  6,  6,  6,  6,  6,246,246,246,246,246,246,246,246,246,246,230,198,134,118,246,246,246,246,246,246,246,246,246,246,246,246, 54,246,246,246,230,198,134,  6,  6,  6,198,230,246,246,246,118, 54,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,252,255,199, 49,124,127,127,127,127,127,124, 49,199,255,252,192,  0,  0,  0,254,254,254,254,248,240,248,249,255,127,127, 63, 15,224,251,251,251,251,120,120,120,120,120,120,120,120,  0,  0,  3,  7,143,255,255,254,252,254,254,222, 14,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,254,255,255, 31,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 31,255,255,254,224,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,240,240,240,240,240,240,240,240,224,248,252,255,127, 31, 15,  7,  3,  7, 31, 63,255,254,248,240,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        },
        {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,248,255,255,127,255,255,240,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,252,255, 63,143,241,248,225,143, 63,255,248,134,  6,  6,  6,  6,  6,246,246,246,246,246,246,246,246,246,246,230,198,134,118,246,246,246,246,246,246,246,246,246,246,246,246, 54,246,246,246,230,198,134,  6,  6,  6,198,230,246,246,246,118, 54,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,252,255,199, 49,124,127,127,127,127,127,124, 49,199,255,252,192,  0,  0,  0,254,254,254,254,248,240,248,249,255,127,127, 63, 15,224,251,251,251,251,120,120,120,120,120,120,120,120,  0,  0,  3,  7,143,255,255,254,252,254,254,222, 14,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,254,255,255, 31,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 31,255,255,254,224,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,240,240,240,240,240,240,240,240,224,248,252,255,127, 31, 15,  7,  3,  7, 31, 63,255,254,248,240,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        },
        {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,248,255,255,127,255,255,240,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,252,255, 63,143,241,248,225,143, 63,255,248,134,  6,  6,  6,  6,  6,246,246,246,246,246,246,246,246,246,246,230,198,134,118,246,246,246,246,246,246,246,246,246,246,246,246, 54,246,246,246,230,198,134,  6,  6,  6,198,230,246,246,246,118, 54,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,252,255,199, 49,124,127,127,127,127,127,124, 49,199,255,252,192,  0,  0,  0,254,254,254,254,248,240,248,249,255,127,127, 63, 15,224,251,251,251,251,120,120,120,120,120,120,120,120,  0,  0,  3,  7,143,255,255,254,252,254,254,222, 14,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,254,255,255, 31,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 31,255,255,254,224,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,240,240,240,240,240,240,240,240,224,248,252,255,127, 31, 15,  7,  3,  7, 31, 63,255,254,248,240,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        }
    };
    // animation
    void animation_routine(void) {
        // switch frame
        if (logo_anim.move_up) {
            logo_anim.frame++;
        } else {
            logo_anim.frame--;
        }

        if (logo_anim.frame == 0) {
            logo_anim.move_up = true;
        } else if (logo_anim.frame == MAX_FRAMES-1) {
            logo_anim.move_up = false;
        }

        // render frame
        oled_write_raw_P(raw_logo[logo_anim.frame % MAX_FRAMES], LOGO_FRAME_SIZE);
    }

    // animation timer
    if(timer_elapsed32(logo_anim.timer) > LOGO_FRAME_DURATION) {
        logo_anim.timer = timer_read32();
        animation_routine();
    }
}

bool oled_task_user(void) {
    if(!oled_task_km()) {
        return false;
    }
    if (is_keyboard_master()) {
        oled_layer_screen_reset();

        if (!reset_layer.is_led_off) {
            oled_render_layer_state();
            oled_render_mod_lock_status();
#    ifdef LUNA_ENABLE
            led_usb_state = host_keyboard_led_state();
        #ifdef OLED_DISPLAY_128X64
            render_luna(12, 4);
        #else
            render_luna(0, 13);
        #endif
#    endif
        }
    } else {
        oled_render_logo();
    }
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void oled_layer_screen_reset(void) {
    if (!reset_layer.has_reset && timer_elapsed32(reset_layer.last_key_press) >= 10 SECONDS ) {
        uint8_t current_layer = get_highest_layer(layer_state);
        if (current_layer > _ALPHA && current_layer < _GAMING) {
            layer_move(_ALPHA);
            reset_layer.has_reset = true;
        }
    }
    if (timer_elapsed32(reset_layer.last_key_press) >= 1 MINUTES ) {
        if (!reset_layer.is_led_off) {
            oled_off();
            reset_layer.is_led_off = true;
        }
    } else if (reset_layer.is_led_off && !is_oled_on()) {
        oled_on();
        reset_layer.is_led_off = false;
    }
}
