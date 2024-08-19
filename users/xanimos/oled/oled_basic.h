#pragma once

#include "quantum.h"

#include "oled_driver.h"

#ifdef LUNA_ENABLE
#    include "luna.h"
#endif

enum animation_frames {
    Frame1,
    Frame2,
    Frame3,
    Frame4,
    Frame5,
    Frame6,
    Frame7,
    MAX_FRAMES
};

typedef struct logo_anim_struct {
    // current frame
    uint8_t frame;
    // timers
    uint32_t timer;
    // animation frame movement direction
    bool move_up;
} logo_anim_t;

void oled_render_keylock_status(void);
void oled_render_mod_status(uint8_t modifiers);
void oled_render_mod_lock_status(void);
void oled_render_layer_state(void);

static void oled_render_logo(void);

void oled_layer_screen_reset(void);
