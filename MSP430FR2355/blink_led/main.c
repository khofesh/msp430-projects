#include <msp430.h>

int main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
  
  // Configure GPIO
  PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode
  P1DIR |= BIT0;             // Set P1.0 to output direction (LED1)
  P1OUT &= ~BIT0;            // Turn off LED initially

  while (1)
  {
    P1OUT ^= BIT0;           // Toggle P1.0 using exclusive-OR

    for (i = 20000; i > 0; i--)
      ;
  }
}
