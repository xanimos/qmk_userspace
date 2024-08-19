#pragma once

typedef struct {
    uint16_t input_code;
    uint32_t stop_time;
    bool move_started;
} mouse_input_t;

typedef struct {
    bool jiggle;
    uint32_t next_animation;
    bool animation_started;
    mouse_input_t x;
    mouse_input_t y;
} mouse_state_t;

extern mouse_state_t mouse_state;

typedef enum {
    MS_DIR_X,
    MS_DIR_Y,
    MS_DIR_MAX
} mouse_directions_t;

void mouse_task_user(void);
void mouse_toggle_state(void);
void mouse_stop_movement(void);
void mouse_add_animation(mouse_input_t* input, uint32_t* timer, mouse_directions_t direction);
void mouse_check_animation_end(mouse_input_t* input, uint32_t* timer);
void mouse_end_animation(mouse_input_t* input);
