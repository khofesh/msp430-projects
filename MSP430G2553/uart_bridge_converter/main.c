#include <msp430.h>
#include <stdint.h>

#define SMCLK_11500 0
#define SMCLK_9600 1
#define ACLK_9600 2

#define UART_MODE SMCLK_11500

void send_uca0_data(uint8_t data);
void init_uart();
void init_clock_16mhz();
void init_gpio();

int main()
{
    WDTCTL = WDTPW + WDTHOLD;
    init_clock_16mhz();
    init_gpio();
    init_uart();

#if UART_MODE == ACLK_9600
    __bis_SR_register(LPM3_bits + GIE); // Since ACLK is source, enter LPM3, interrupts enabled
#else
    __bis_SR_register(LPM0_bits + GIE); // Since SMCLK is source, enter LPM0, interrupts enabled
#endif
}

void send_uca0_data(uint8_t data)
{
    while (!(IFG2 & UCA0TXIFG)) // USCI_A0 TX buffer ready?
    {
    }
    UCA0TXBUF = data;
}

void init_uart()
{
#if UART_MODE == SMCLK_11500
    UCA0CTL1 |= UCSSEL_2; // SMCLK
    UCA0BR0 = 138;        // 16MHz 115200
    UCA0BR1 = 0;          // 16MHz 115200
    UCA0MCTL = UCBRS_7;   // Modulation UCBRSx = 7
    UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
    IFG2 &= ~(UCA0RXIFG);
    IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
#elif UART_MODE == SMCLK_9600
    UCA0CTL1 |= UCSSEL_2;                  // SMCLK
    UCA0BR0 = 104;                         // 16MHz 9600
    UCA0BR1 = 0;                           // 16MHz 9600
    UCA0MCTL = UCBRS_0 + UCOS16 + UCBRF_3; // Modulation UCBRSx = 0
    UCA0CTL1 &= ~UCSWRST;                  // **Initialize USCI state machine**
    IFG2 &= ~(UCA0RXIFG);
    IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
#elif UART_MODE == ACLK_9600
    UCA0CTL1 |= UCSSEL_1; // ACLK
    UCA0BR0 = 3;          // 32768Hz 9600
    UCA0BR1 = 0;          // 32768Hz 9600
    UCA0MCTL = UCBRS_3;   // Modulation UCBRSx = 3
    UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
    IFG2 &= ~(UCA0RXIFG);
    IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
#else
#error "Select UART Baud Rate of 115200 or 9600"
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

void init_gpio()
{
    P1SEL = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2;
}

/***************************
 *       INTERRUPTS        *
 ***************************/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR(void)
#else
#error Compiler not supported!
#endif
{
    if (IFG2 & UCA0RXIFG)
    {
        uint8_t rx_val = UCA0RXBUF; // Must read UCxxRXBUF to clear the flag
        send_uca0_data(rx_val);
    }
}
