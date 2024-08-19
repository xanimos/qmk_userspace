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

#pragma once

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_ACTIVITY_ENABLE

#define TAPPING_TERM 150
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

#define OLED_TIMEOUT 0      // this is required for custom oled timeout code
