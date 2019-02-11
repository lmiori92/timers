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


#include "timer.h"
#ifdef __AVR
#include <avr/interrupt.h>
#include <util/atomic.h>
/* Implement the atomic block on the AVR platform by using the util/atomic.h block */
#define TIMER_ATOMIC(block)    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { block };
#else
#error "please define an architecture dependent atomic operation"
#endif
uint32_t timerbase[SOFT_TIMER_NUM];
uint32_t milliseconds_since_boot = 0;

// with cycles == 0 then the timer is reset (i.e. never "true" and internal state reset to current timestamp)
/**
 * Implementation of a timer wich is considered as "soft" since
 * it is using a counter that is updated in software off a hardware timer
 * Interrupt Service Routine.
 * If the number of cycles if equal to zero, it means "timer is on reset state" i.e.
 * the counter is set to the current value.
 * The used timebase is 1 millisecond.
 * @param cycles        the number of cycles to count before a timeout occurs
 * @param timer_id      the soft-timer identifier
 * @return  true : timer expired
 *          false: timer not yet expired or in reset state
 */
bool timeout(uint32_t cycles, e_timer_id timer_id)
{

    bool retval;
    uint32_t tmr;

    TIMER_ATOMIC(
    {
        tmr = milliseconds_since_boot;
        if (cycles == 0)
        {
            /* reset */
            timerbase[timer_id] = tmr;
            retval = false;
        }
        else if (((uint32_t)tmr - (uint32_t)timerbase[timer_id]) >= (uint32_t)cycles)
        {
            /* send */
            timerbase[timer_id] = tmr;
            retval = true;
        }
        else
        {
            /* wait */
            retval = false;
        }
    };
    );

    return retval;
}
