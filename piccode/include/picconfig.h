#ifndef PICCONFIG_H
#define PICCONFIG_H

#define CLOCK_MHZ 20000000

#ifdef _MSC_VER

#if defined(USE_PIC18F2550)
#include "ccs/18F2550.h"
#endif

#else   //CCS compiler

#if defined(USE_PIC18F2550)

#include <18F2550.h>

#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS
#FUSES CPUDIV1
#FUSES NOPROTECT                //Code not protected from reading
#FUSES BROWNOUT                 //Reset when brownout detected
//#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES PUT                    // Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES PBADEN                   //PORTB pins are configured as analog input channels on RESET
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads
#FUSES NOCPB                    //No Boot Block code protection
#FUSES LPT1OSC                  //Timer1 configured for low-power operation
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#define AUTO_ADQTIME
#device ADC=8

#byte ADCON2 = 0xfc0
#bit ACQT2 = ADCON2.5
#bit ACQT1 = ADCON2.4
#bit ACQT0 = ADCON2.3

#byte UCON=0xF6D
#bit UCON_3 = UCON.3

#byte UCFG=0xF6F
#bit UCFG_3 = UCFG.3

#byte CMCON=0xFB4
#bit CM2=CMCON.2
#bit CM1=CMCON.1
#bit CM0=CMCON.0

#byte SSPCON1=0xFC6
#byte SSPSTAT=0xFC7



#endif   //Compiler type


#endif
