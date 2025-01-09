/* Copyright 2024 Daniel Weeks <daniel@xdboards.xyz>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "quantum.h"
#include "encoder_x.h"

static const char* encoder_layers[ENC_LAYER_SIZE] = {
"Default", "Valorant", "Blender"
};


void (*encoder_layer_actions[ENC_LAYER_SIZE][ENCODER_COUNT])(encoder_directions_t) = {
    [ENC_DEFAULT] = {
        [0] = enc_default_left,
        [1] = enc_default_right,
    },
    [ENC_VALORANT] = {
        [0] = enc_default_left,
        [1] = enc_default_right,
    },
    [ENC_BLENDER] = {
        [0] = enc_blender_left,
        [1] = enc_blender_right,
    },
};

encoder_layers_t current_encoder_layer = ENC_DEFAULT;

void update_current_encoder_layer(bool isNext) {
    if (isNext) {
        current_encoder_layer++;
        if (current_encoder_layer == ENC_LAYER_SIZE) {
            current_encoder_layer = ENC_DEFAULT;
        }
    } else {
        if (current_encoder_layer == ENC_DEFAULT) {
            current_encoder_layer = ENC_LAYER_SIZE;
        }
        current_encoder_layer--;
    }
}

const char* get_current_layer_text() {
    return encoder_layers[current_encoder_layer];
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_directions_t direction = clockwise ? E_CW : E_CCW;
    encoder_layer_actions[current_encoder_layer][index](direction);
    return false;
}

void enc_default_left(encoder_directions_t direction){
    // Volume control
    if (direction == E_CW) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}
void enc_default_right(encoder_directions_t direction){
    // Page up/Page down
    if (direction == E_CW) {
        tap_code(KC_PGUP);
    } else {
        tap_code(KC_PGDN);
    }
}
void enc_valorant_left(encoder_directions_t direction){

}
void enc_valorant_right(encoder_directions_t direction){

}
void enc_blender_left(encoder_directions_t direction){

}
void enc_blender_right(encoder_directions_t direction){

}