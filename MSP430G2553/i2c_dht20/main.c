#include <msp430.h>
#include "uart.h"

unsigned int RxByteCtr;
unsigned int RxWord;

void init_clock_16mhz();

int main()
{
    WDTCTL = WDTPW + WDTHOLD;

    init_clock_16mhz();
    init_uart_gpio();
    init_uart();

#if UART_MODE == ACLK_9600
    __bis_SR_register(LPM3_bits + GIE); // Since ACLK is source, enter LPM3, interrupts enabled
#else
    __bis_SR_register(LPM0_bits + GIE); // Since SMCLK is source, enter LPM0, interrupts enabled
#endif
}

void init_clock_16mhz()
{
    if (CALBC1_16MHZ == 0xFF) // If calibration constant erased
    {
        while (1)
            ;
    }

    DCOCTL = 0;
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;
}
