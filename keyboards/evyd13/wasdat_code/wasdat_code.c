/* Copyright 2019 Evy Dekkers
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
#include "wasdat_code.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
    led_init_ports();
}

void led_init_ports(void) {
    setPinOutput(B1);
    setPinOutput(B2);
    setPinOutput(B3);
    writePinHigh(B1);
    writePinHigh(B2);
    writePinHigh(B3);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B1, !led_state.caps_lock);
        writePin(B2, !led_state.scroll_lock);
        writePin(B3, !led_state.num_lock);
    }

    return true;
}
