#pragma once

// Tap Dance keycodes
enum td_keycodes {
    AL_MOD,
    COL_QU,
    MH_SFT,
    MH_CTL,
    MH_ALT,
    MH_GUI,
    KP_0BS,
    CTL_MOD,
    HOME_END
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_UNKNOWN_HOLD,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    uint8_t mod;
} tap_dance_mod_hold_t;

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void tap_dance_mod_hold_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_mod_hold_reset(tap_dance_state_t *state, void *user_data);

void alphamod_finished(tap_dance_state_t *state, void *user_data);
void alphamod_reset(tap_dance_state_t *state, void *user_data);

void ctl_mod_finished(tap_dance_state_t *state, void *user_data);
void ctl_mod_reset(tap_dance_state_t *state, void *user_data);

void zero_bs_finished(tap_dance_state_t *state, void *user_data);
void zero_bs_reset(tap_dance_state_t *state, void *user_data);

// functional helpers
td_state_t tap_hold_dance_state(tap_dance_state_t *state , td_state_t tap, td_state_t hold);
