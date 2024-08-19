#include "quantum.h"
#include "xanimos.h"
#ifdef LUNA_ENABLE
#   include "oled/luna.h"
#endif
#ifdef MOUSE_JIGGLE_ENABLE
#   include "mouse_util.h"
#endif

#ifdef OLED_ENABLE
    layer_reset_t reset_layer = {
        .is_led_off = false,
        .last_key_press = 0,
        .has_reset = false
    };
#endif

void keyboard_post_init_user(void) {
  //  debug_enable=true;
}

void matrix_scan_user(void) {
    #ifdef MOUSE_JIGGLE_ENABLE
    mouse_task_user();
    #endif
}
#ifdef OLED_ENABLE
    __attribute__((weak)) bool oled_task_km(void) {
        return true;
    }

    __attribute__((weak)) oled_rotation_t oled_init_km(oled_rotation_t rotation) {
        return rotation;
    }

    __attribute__((weak)) bool oled_render_logo_km(void) {
        return true;
    }
#endif

static const char * git_commands[] = {
    "git init",
    "git clone ",
    "git add ",
    "git diff ",
    "git reset --soft ",
    "git branch --list",
    "git checkout ",
    "git checkout -b ",
    "git remote add ",
    "git fetch ",
    "git pull",
    "git pull upstream ",
    "git push",
    "git push -u origin ",
    "git push --force-with-lease",
    "git commit ",
    "git commit -m \"feat: [ADO-]\"",  //my company standard commit format
    "git status",
    "git log",
    "git stash",
    "git stash list",
    "git stash pop ",
    "git stash show ",
    "git restore --staged ",
    "git revert ",
    "main",
    "upstream",
    "origin",
    "HEAD~"
};

static const char * dev_commands[] = {
    "npm run ",
    "npm install",
    "npm update ",
    "docker run ",
    "docker exec -it  /bin/bash"SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT),
    "docker compose up -d",
    "docker compose down",
    "docker compose build",
    "docker compose start",
    "docker compose stop",
    "start",
    "lint",
    ":style:report",
    ":report"
};

__attribute__((weak)) bool process_record_km(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(!process_record_km(keycode, record)) {
        return false;
    }
    static uint32_t boot_timer;
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        reset_layer.last_key_press = timer_read32();
        reset_layer.has_reset = false;
    }
#endif
    uint8_t mod_state = get_mods();
    switch (keycode) {
        case MD_BOOT:
        {
            if (record->event.pressed) {
                boot_timer = timer_read32();
            } else {
                if (timer_elapsed32(boot_timer) >= 500) {
                    #ifdef OLED_ENABLE
                    oled_off();
                    #endif
                    reset_keyboard();
                }
            }
            return false;
        }
        case GIT_KEYCODE_START ... GIT_KEYCODE_END:
        {
            if (record->event.pressed) {
                send_string_with_delay(git_commands[keycode - GIT_KEYCODE_START], 3);
            }
           return false;
        }
        case DEV_KEYCODE_START ... DEV_KEYCODE_END:
        {
            if (record->event.pressed) {
                send_string_with_delay(dev_commands[keycode - DEV_KEYCODE_START], 3);
//                if(keycode == D_DKE) {
//                    register_
//                }
            }
        }
        case KC_BSPC:
        {
            static bool delkey_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                }
            } else {
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            break;
        }
        case SFT_T(KC_Z):
        case SFT_T(KC_SLSH):
#ifdef LUNA_ENABLE
            if (record->event.pressed) {
                luna_state.is_sneaking = true;
            } else {
                luna_state.is_sneaking = false;
            }
#endif
            break;
        case KC_SPC:
#ifdef LUNA_ENABLE
            if (record->event.pressed) {
                luna_state.is_jumping  = true;
                luna_state.showed_jump = false;
            } else {
                luna_state.is_jumping = false;
            }
#endif
            break;
        case X_MSJIG:
        {
            #ifdef MOUSE_JIGGLE_ENABLE
            if (record->event.pressed) {
                mouse_toggle_state();
            }
            #endif
            break;
        }
        case X_AF1_1:
        {
            // This is a shortcut for JetBrains IDEs to jump
            // to the current file in the file tree
            if (record->event.pressed) {
                tap_code16_delay(A(KC_F1), 10);
                tap_code_delay(KC_1, 10);
            }
            break;
        }
        case X_ENC1:
        {
            break;
        }
        case X_ENC2:
        {
            break;
        }
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
    return false;
}
#endif
