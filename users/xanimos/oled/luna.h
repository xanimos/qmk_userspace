/*
 * Copyright 2021 QMK Community
 * Copyright 2021 Tyler Thrailkill (@snowe/@snowe2010) <tyler.b.thrailkill@gmail.com>
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

#pragma once

typedef struct luna_params_struct {
    bool is_sneaking;
    bool is_jumping;
    bool showed_jump;
} luna_t;

extern luna_t luna_state;

// status variables
extern led_t led_usb_state;
//extern int current_wpm;


void render_luna(int LUNA_X, int LUNA_Y);

