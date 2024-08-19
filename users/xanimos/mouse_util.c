#include "quantum.h"
#include "mouse_util.h"

#include <stdlib.h>

const uint16_t MOUSE_MOVE_TIMEOUT_MIN = 500;
const uint16_t MOUSE_MOVE_TIMEOUT_MAX = 500; //1000 - MOUSE_MOVE_TIMEOUT_MIN;

const uint32_t MOUSE_ANIM_MIN_WAIT = 25000; // > MOUSE_MOVE_TIMEOUT_MAX
const uint32_t MOUSE_ANIM_MAX_WAIT = 575000; //600000 - MIN_WAIT;

mouse_state_t mouse_state = {
    .jiggle = false,
    .next_animation = 0,
    .animation_started = false,
    .x = {
        .move_started = false,
        .input_code = 0,
        .stop_time = 0
    },
    .y = {
        .move_started = false,
        .input_code = 0,
        .stop_time = 0
    }
};

#define MOUSE_MAX_DIRECTION_CODES 2

uint16_t mouse_codes[MS_DIR_MAX][MOUSE_MAX_DIRECTION_CODES] = {
    { KC_MS_LEFT, KC_MS_RIGHT },
    { KC_MS_UP, KC_MS_DOWN }
};

void mouse_task_user(void) {
    if(mouse_state.jiggle) {

        uint32_t timer = timer_read32();
        if(mouse_state.next_animation < timer) {
            srand(mouse_state.next_animation);
            mouse_state.next_animation = timer + (rand() % MOUSE_ANIM_MAX_WAIT) + MOUSE_ANIM_MIN_WAIT;

            mouse_add_animation(&mouse_state.x, &timer, MS_DIR_X);
            mouse_add_animation(&mouse_state.y, &timer, MS_DIR_Y);
        }

        mouse_check_animation_end(&mouse_state.x, &timer);
        mouse_check_animation_end(&mouse_state.y, &timer);
    }
}

void mouse_add_animation(mouse_input_t* input, uint32_t* timer, mouse_directions_t direction) {
    input->input_code = mouse_codes[direction][rand() % MOUSE_MAX_DIRECTION_CODES];
    register_code16(input->input_code);
    input->move_started = true;
    input->stop_time = *timer + (rand() % MOUSE_MOVE_TIMEOUT_MAX) + MOUSE_MOVE_TIMEOUT_MIN;
}

void mouse_check_animation_end(mouse_input_t* input, uint32_t* timer) {
    if(input->move_started && input->stop_time < *timer) {
        mouse_end_animation(input);
    }
}

void mouse_end_animation(mouse_input_t* input) {
    unregister_code16(input->input_code);
    input->input_code = 0;
    input->move_started = false;
    input->stop_time = 0;
}

void mouse_toggle_state(void) {
    if(mouse_state.jiggle) {
        if(mouse_state.x.move_started) {
            mouse_end_animation(&mouse_state.x);
        }
        if(mouse_state.y.move_started) {
            mouse_end_animation(&mouse_state.y);
        }
    }
    mouse_state.jiggle = !mouse_state.jiggle;
}
