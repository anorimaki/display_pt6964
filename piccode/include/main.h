#ifndef MAIN_H
#define MAIN_H

/////
// PIN mapping in PIC18F2550
//
// A0: ADC for ir sensor0 
// A1: ADC for ir sensor1
// A2: servo fot ir sensor0
// A3: VREF+ for ADC
// A4: 
// A5: servo fot ir sensor1
// A6: OSC
// A7: OSC
// B0: i2c SCL for motors.
// B1: i2c SDA for motors.
// B2: i2c SDA for sonnar.
// B3: i2c SCL for sonnar
// B4:
// B5
// B6:
// B7:
// C0: 
// C1: 
// C2:
// C3: 
// C4: 
// C5
// C6: xmit RS232
// C7: rcv RS232

/*******************************************************/
// TARGET HW
/*******************************************************/
#define USE_PIC18F2550

#include "picconfig.h"

/*******************************************************/
//   INPUT/OUPUT PINS
/*******************************************************/
#if defined(USE_PIC18F2550)
//To review
#define PIN_CLK          PIN_B1
#define PIN_DATA_IN      PIN_B0

#define PIN_DATA_OUT     PIN_C7
#define PIN_STB          PIN_B3

#endif

#ifdef _MSC_VER
void ocleaner_main();
void timer0_isr();
void timer1_isr();
void tbe_isr();
void rda_isr();
#endif

#include "ccs/compilerspecs.h"


_USE_DELAY( clock=CLOCK_MHZ )
_USE_FAST_IO( A )
_USE_FAST_IO( B )
_USE_FAST_IO( C )


#endif
