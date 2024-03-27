/*
 * main.c
*/

#include <rf430frl152h.h>


/*
 * Function Prototypes
 */
void clockInit(void);
void registerInit(void);
void timerInit(void);


/*
 * Main
 */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop Watchdog Timer

    clockInit();
    registerInit();
    timerInit();

    // Enter low-power-mode before and after interrupt
    _BIS_SR(CPUOFF + GIE);
}


/*
 * Timer A0 Interrupt Service Routine
 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT ^= 0x10;                              // Set P1.4 HIGH/LOW
}


/*
 * Register Initialization
 */
void registerInit(void)
{
    // Select registers to I/O
    P1SEL0 = 0x00;
    P1SEL1 = 0x00;

    // Disable all
    P1OUT = 0x00;
    P1DIR = 0xFF;
    P2OUT = 0x00;
    P2DIR = 0xFF;

    // Set P1.4 as output
    P1DIR = 0x10;
}


/*
 * Clock Initialization
 */
void clockInit(void)
{
    CCSCTL0     =   CCSKEY;                                 // Unlock CSS
    CCSCTL1     =   0;                                      // Do not half the clock speed
    CCSCTL4     =   SELA_1 + SELM_0 + SELS_0;               // disable ACLK, enable MCLK & SMCLK
    CCSCTL5     =   DIVA__1 + DIVM__1 + DIVS__32;           // Set SMCLK divider to 32, rest to 1
    CCSCTL6     =   XTOFF;                                  // Turns off the crystal if it is not being used
    CCSCTL8     =   ACLKREQEN + MCLKREQEN + SMCLKREQEN;     // Disable clocks if they are not being used
    CCSCTL0_H   |=  0xFF;                                   // Lock CCS
}


/*
 * Timer Initialization
 */
void timerInit(void)
{
    TA0CTL      =   TASSEL_2 + ID_3;                        // Clock source SCMCLK, divider set to 8
    TA0CTL      &=  ~TAIFG;                                 // Clear Interrupt Flag
    TA0CTL      |=  MC_1;                                   // Up-Mode selected
    TA0CCTL0    =   CCIE;                                   // Capture/Compare Interrupt enabled
    TA0CCR0     =   40000;                                  // Set interval of timer
}

