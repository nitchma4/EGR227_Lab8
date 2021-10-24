/* p11_1.c Toggling P2.7 at 60 Hz using Timer_A0.4 PWM
 *
 * This program uses Timer_A0.4 to generate PWM output at 60 Hz
 * and 33.3% duty cycle.
 * Subsystem Master Clock (SMCLK) running at 3 MHz is used.
 * Timer_A0 is configured to count up from 0 to 50,000-1, which
 * is loaded in TIMER_A0->CCR[0].
 * The timer counter roll over interval is:
 * 3,000,000 / 50,000 = 60 Hz.
 * TIMER_A0->CCR[4] is loaded with 50000/3 and CCR4 is configured
 * as reset/set mode. The output is set to 1 at the beginning
 * of the counting cycle when the counter is 0. When the counter
 * counts up to 50000/3, the output is reset to 0 and stays 0 until
 * the next counting cycle. So the output stays at 1 for 1/3=33.3% of the time.
 *
 * Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */

#include "msp.h"

void delayMs(int n);

int main(void) {
    /* Configure P2.7 as Timer A0.4 output */
    P2->SEL0 |= 0x80;
    P2->SEL1 &= ~0x80;
    P2->DIR |= 0x80;

    /* configure TimerA0.4 as PWM */
    TIMER_A0->CCR[0] = 37500-1;     /* PWM Period */
    TIMER_A0->CCR[4] = (37500/9);     /* CCR4 PWM duty cycle */
    TIMER_A0->CCTL[4] = 0xE0;       /* CCR4 reset/set mode */
    TIMER_A0->CTL = 0x0214;          /* use SMCLK, count up, clear TA0R register */
    TIMER_A0->EX0 = 1;

    while (1) {
    }
}
