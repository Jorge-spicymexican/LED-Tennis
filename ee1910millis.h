#include "msp.h"

volatile int elapsed = 0;

void start_timer(void) {

      // Set up Timer32 for down count with default 3MHz clock
       TIMER32_2->CONTROL = TIMER32_CONTROL_SIZE |
               TIMER32_CONTROL_MODE;

       // Load Timer32 counter with period 3000
       TIMER32_2->LOAD= 3000;

       // Enalbe the Timer32 interrupt in NVIC
       __enable_irq();
       NVIC->ISER[0] = 1 << ((T32_INT2_IRQn) & 31);

       // Start Timer32 with interrupt enabled
       TIMER32_2->CONTROL |= TIMER32_CONTROL_ENABLE |
                   TIMER32_CONTROL_IE;
}

void reset_timer(void) {
    elapsed=0;
}
void stop_timer(void) {
// Turn off timer
       TIMER32_2->CONTROL &= ~(TIMER32_CONTROL_ENABLE |
                          TIMER32_CONTROL_IE);
}

int millis(void) {
    return elapsed;
}
void T32_INT2_IRQHandler(void)
{
    TIMER32_2->INTCLR |= BIT0;              // Clear Timer32 interrupt flag
    elapsed++;                                // Record tick
}
