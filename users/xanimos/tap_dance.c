#include "quantum.h"
#include "tap_dance.h"
#include "xanimos.h"

// Create a global instance of the tapdance state type
static td_state_t td_state;

void tap_dance_mod_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_mod_hold_t *mod_hold = (tap_dance_mod_hold_t *)user_data;
    switch(cur_dance(state)) {
        case TD_SINGLE_TAP:
        {
            if ((get_oneshot_mods() & mod_hold->mod) != mod_hold->mod) {
                add_oneshot_mods(mod_hold->mod);
            } else {
                del_oneshot_mods(mod_hold->mod);
            }
            break;
        }
        case TD_SINGLE_HOLD:
        {
            if ((get_mods() & mod_hold->mod) != mod_hold->mod) {
                add_mods(mod_hold->mod);
            } else {
                del_mods(mod_hold->mod);
            }
            break;
        }
        default:
        {
            // clear both mods
            del_oneshot_mods(mod_hold->mod);
            del_mods(mod_hold->mod);
            break;
        };
    }
}

void tap_dance_mod_hold_reset(tap_dance_state_t *state, void *user_data) { }

td_state_t cur_dance(tap_dance_state_t *state) {
    td_state_t tap, hold;
    switch(state->count)
    {
        case 1:
            tap = TD_SINGLE_TAP;
            hold = TD_SINGLE_HOLD;
            break;
        case 2:
            tap = TD_DOUBLE_TAP;
            hold = TD_DOUBLE_HOLD;
            break;
        default: // Any number higher than the maximum state value you return above
            tap = TD_UNKNOWN;
            hold = TD_UNKNOWN_HOLD;
    }
    return tap_hold_dance_state(state, tap, hold);
}

void alphamod_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: layer_move(_ALPHA); break;
        case TD_SINGLE_HOLD: layer_on(_MODS); break;
        default: break;
    }
}

void alphamod_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD: layer_off(_MODS); break;
        default: break;
    }
}

void zero_bs_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            SEND_STRING("0");
            break;
         default:
            register_code(KC_BSPC);
            break;
    }
}
void zero_bs_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: break;
        default:
            unregister_code(KC_BSPC);
            break;
    }
}

td_state_t tap_hold_dance_state(tap_dance_state_t *state , td_state_t tap, td_state_t hold) {
    return (!state->pressed
#ifndef PERMISSIVE_HOLD
        || state->interrupted
#endif
        ) ? tap : hold;
}

void ctl_mod_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_UNKNOWN:
            layer_move(_ALPHA); break;

        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;

        case TD_DOUBLE_HOLD: layer_on(_MODS); break;
        default: break;
    }
}

void ctl_mod_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case TD_DOUBLE_HOLD: layer_off(_MODS); break;
        default: break;
    }
}

#define ACTION_TAP_DANCE_MOD_HOLD(mod) \
    { .fn = {NULL, tap_dance_mod_hold_finished, tap_dance_mod_hold_reset}, .user_data = (void *)&((tap_dance_mod_hold_t){mod}), }

tap_dance_action_t tap_dance_actions[] = {
    [AL_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alphamod_finished, alphamod_reset),
    [COL_QU] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
    [MH_SFT] = ACTION_TAP_DANCE_MOD_HOLD(MOD_LSFT),
    [MH_CTL] = ACTION_TAP_DANCE_MOD_HOLD(MOD_LCTL),
    [MH_ALT] = ACTION_TAP_DANCE_MOD_HOLD(MOD_LALT),
    [MH_GUI] = ACTION_TAP_DANCE_MOD_HOLD(MOD_LGUI),
    [KP_0BS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, zero_bs_finished, zero_bs_reset),
    [CTL_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_mod_finished, ctl_mod_reset),
    [HOME_END] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END)
};
