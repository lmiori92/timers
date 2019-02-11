/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Lorenzo Miori (C) 2017-2019 [ 3M4|L: memoryS60<at>gmail.com ]

    Version History
        * 1.0 initial

*/

#ifndef MY_TIMER_H_
#define MY_TIMER_H_

#include <stdbool.h>
#include <stdint.h>

extern uint32_t milliseconds_since_boot;

typedef enum
{
    SOFT_TIMER_0,
    SOFT_TIMER_1,
    SOFT_TIMER_2,
    SOFT_TIMER_3,
    SOFT_TIMER_4,
    SOFT_TIMER_5,
    SOFT_TIMER_6,
    SOFT_TIMER_7,
    SOFT_TIMER_8,
    SOFT_TIMER_9,
    SOFT_TIMER_10,
    SOFT_TIMER_NUM
} e_timer_id;

#define TIMER_RESET_VALUE     (0U)
#define TIMER_RESET(x)        ((void)timeout(TIMER_RESET_VALUE, (x)))
#define ON_TIMER_EXPIRED(cycles,identifier,callback)        if (timeout(cycles, identifier) == true) { callback; }
#define ON_TIMER_NOT_EXPIRED(cycles,identifier,callback)    if (timeout(cycles, identifier) == false) { callback; }
#define ON_TIMER(cycles,identifier,callback,callback2)    if (timeout(cycles, identifier) == true) { callback; } else { callback2; }

bool timeout(uint32_t cycles, e_timer_id timer_id);

#endif /* MY_TIMER_H_ */
