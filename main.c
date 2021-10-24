/* p11_1.c Toggling P2.7 at 60 Hz using Timer_A0.4 PWM
 *
 *testing
 *testing
 *
 *
 *
 *
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
