# Documentation

## Overview
The program configures the **RF430FRL152H** microcontroller to:
1. Stop the Watchdog Timer (WDT) upon startup.
2. Initialize the system clock, registers, and timer.
3. Enter low-power mode with interrupts enabled.
4. Blink an LED connected to **P1.4** using a timer interrupt.

---

## File Contents
### **Header File**
```c
#include <rf430frl152h.h>
```
This header file includes device-specific definitions for the RF430FRL152H microcontroller.

---

### **Function Prototypes**
```c
void clockInit(void);
void registerInit(void);
void timerInit(void);
```
- **`clockInit()`**: Initializes the system clock.
- **`registerInit()`**: Configures I/O registers and sets P1.4 as output.
- **`timerInit()`**: Configures Timer A0 for periodic interrupts.

---

### **Main Function**
```c
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop Watchdog Timer

    clockInit();
    registerInit();
    timerInit();

    // Enter low-power mode with global interrupts enabled
    _BIS_SR(CPUOFF + GIE);
}
```
- Stops the Watchdog Timer to prevent unexpected resets.
- Initializes the clock, registers, and timer.
- Enters low-power mode (LPM0) with global interrupts enabled.

---

### **Interrupt Service Routine (ISR)**
```c
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT ^= 0x10;                              // Toggle P1.4 (LED connected here)
}
```
- This ISR toggles the state of the LED connected to P1.4 each time Timer A0 reaches the specified interval.

---

## Initialization Functions

### **1. `registerInit()`**
Configures the GPIO ports:
```c
void registerInit(void)
{
    // Select registers to I/O
    P1SEL0 = 0x00;
    P1SEL1 = 0x00;

    // Disable all outputs initially
    P1OUT = 0x00;
    P1DIR = 0xFF;
    P2OUT = 0x00;
    P2DIR = 0xFF;

    // Set P1.4 as output
    P1DIR = 0x10;
}
```
- Disables all GPIO pins initially.
- Sets P1.4 as an output for LED control.

### **2. `clockInit()`**
Initializes the system clock:
```c
void clockInit(void)
{
    CCSCTL0     =   CCSKEY;                                 // Unlock CSS
    CCSCTL1     =   0;                                      // Do not halve the clock speed
    CCSCTL4     =   SELA_1 + SELM_0 + SELS_0;               // Disable ACLK, enable MCLK & SMCLK
    CCSCTL5     =   DIVA__1 + DIVM__1 + DIVS__32;           // SMCLK divider = 32
    CCSCTL6     =   XTOFF;                                  // Disable unused crystal
    CCSCTL8     =   ACLKREQEN + MCLKREQEN + SMCLKREQEN;     // Disable clocks if unused
    CCSCTL0_H   |=  0xFF;                                   // Lock CCS
}
```
- Sets up the main clock (MCLK) and sub-main clock (SMCLK).
- Disables unused peripherals for power saving.

### **3. `timerInit()`**
Configures Timer A0 for periodic interrupts:
```c
void timerInit(void)
{
    TA0CTL      =   TASSEL_2 + ID_3;                        // Clock source SMCLK, divider = 8
    TA0CTL      &=  ~TAIFG;                                 // Clear interrupt flag
    TA0CTL      |=  MC_1;                                   // Up-mode (counts to TA0CCR0)
    TA0CCTL0    =   CCIE;                                   // Enable capture/compare interrupt
    TA0CCR0     =   40000;                                  // Timer interval
}
```
- Sets Timer A0 to use SMCLK as its clock source.
- Configures an interrupt at intervals defined by `TA0CCR0`.

---

## Summary
This program demonstrates the following key concepts for the RF430FRL152H microcontroller:
1. Low-power mode usage with interrupts.
2. Configuring GPIO pins for output.
3. Setting up and using Timer A0 for periodic interrupts.
4. Blinking an LED as a simple example of embedded control.
