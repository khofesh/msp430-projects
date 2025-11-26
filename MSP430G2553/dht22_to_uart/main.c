#include <msp430.h>
#include "dht22.h"
#include <stdio.h>

char txbuf[64];

void uart_init()
{
    UCA0CTL1 |= UCSWRST;           // Put USCI in reset mode
    UCA0CTL1 = UCSSEL_2 | UCSWRST; // Use SMCLK, still reset
    // 16MHz / 9600 = 1666.67
    UCA0BR0 = 0x82;       // 1666 & 0xFF = 130
    UCA0BR1 = 0x06;       // 1666 >> 8 = 6
    UCA0MCTL = UCBRS_6;   // Modulation UCBRSx=6
    P1SEL |= BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
    P1SEL2 |= BIT1 + BIT2;
    UCA0CTL1 &= ~UCSWRST; // Normal mode
}

void uart_send(int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        while (UCA0STAT & UCBUSY)
            ;
        UCA0TXBUF = txbuf[i];
    }
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

void delay_ms(unsigned int ms)
{
    while (ms--)
    {
        __delay_cycles(16000); // 16MHz / 16000 = 1ms
    }
}

int main()
{
    WDTCTL = WDTPW | WDTHOLD;

    init_clock_16mhz();

    uart_init();

    // Initialize DHT22 pin (P2.0) as output, high
    P2DIR |= BIT0;
    P2OUT |= BIT0;

    _BIS_SR(GIE);

    // Send startup message
    uart_send(sprintf(txbuf, "DHT22 Sensor Starting...\r\n"));
    delay_ms(2000); // Wait for sensor to stabilize

    while (1)
    {
        uart_send(sprintf(txbuf, "\r\nStarting DHT22 read...\r\n"));

        dht_start_read();

        // Wait for read to complete with timeout
        unsigned int timeout = 0;
        extern volatile unsigned char dht_current_state;
        while (dht_current_state != 0 && timeout < 10000)
        {
            __delay_cycles(160); // ~10us at 16MHz
            timeout++;
        }

        if (timeout >= 10000)
        {
            uart_send(sprintf(txbuf, "ERROR: DHT22 timeout! State: %d\r\n", dht_current_state));
        }
        else
        {
            int t = dht_get_temp();
            int h = dht_get_rh();
            
            if (dht_is_crc_valid()) {
                uart_send(sprintf(txbuf, "Temp: %3d.%1d C; RH: %3d.%1d %%\r\n", t / 10, t % 10, h / 10, h % 10));
            } else {
                uart_send(sprintf(txbuf, "CRC ERROR! T:%d.%d C; RH:%d.%d %%\r\n", t / 10, t % 10, h / 10, h % 10));
            }
        }

        // 2 seconds between readings
        delay_ms(2000);
    }

    return 0;
}
