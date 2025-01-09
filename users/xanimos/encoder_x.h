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

#ifndef QMK_USERSPACE_ENCODER_H
#define QMK_USERSPACE_ENCODER_H

typedef enum encoder_layers {
    ENC_DEFAULT,
    ENC_VALORANT,
    ENC_BLENDER,
    ENC_LAYER_SIZE
} encoder_layers_t;

void update_current_encoder_layer(bool isNext);
const char* get_current_layer_text(void);

#ifndef ENCODER_COUNT
#    define ENCODER_COUNT 2
#endif

typedef enum encoder_directions {
    E_CW,
    E_CCW,
    E_DIRECTIONS
} encoder_directions_t;

void enc_default_left(encoder_directions_t direction);
void enc_default_right(encoder_directions_t direction);
void enc_valorant_left(encoder_directions_t direction);
void enc_valorant_right(encoder_directions_t direction);
void enc_blender_left(encoder_directions_t direction);
void enc_blender_right(encoder_directions_t direction);
#endif // QMK_USERSPACE_ENCODER_H
