#include "main.h"
#include "ui.h"
#include "keys_reaction.h"


#ifdef _MSC_VER
#define USE_RS232 0 
#include "ccs/rs232.h"
#else
//#use rs232( baud=19200, parity=N, xmit=PIN_C6, rcv=PIN_C7, bits=8, DISABLE_INTS )
#endif

void init() {
    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_OFF);

#ifdef USE_PIC18F2550
    //Disable USB
    UCON_3 = 0;
    UCFG_3 = 1;
    //Disable comparators
    setup_comparator(NC_NC_NC_NC);
    //CM2 = 1;
    //CM1 = 1;
    //CM0 = 1;
#endif

    set_tris_a(0xFF);
    set_tris_b(0xFF);
    set_tris_c(0xFF);

    enable_interrupts(GLOBAL);
}


int32 apply_keys( int key, int32 counter ) {
    if ( key == 5 ) {
        return counter+1;
    }
    if ( key == 4 ) {
        return counter+10;
    }
    if ( key == 3 ) {
        return counter+100;
    }
    if ( key == 0 ) {
        return counter-1;
    }
    return counter;
}


void main_loop() {
    bool keys[UI_KEYS_SIZE];
    int key;
    int32 counter = 0;
    
    ui_print(counter);
    while (TRUE) {
        ui_read_keys(keys);
        
        key = keys_update_state(keys);
        
        counter = apply_keys( key, counter );

        ui_print( counter );
    }
}


void main() {
    init();

    delay_ms(200);

    ui_init();
    
    keys_init( 1000, UI_KEYS_SIZE );
    
    main_loop();
}


#include "ui.c"
#include "pt6964.c"
#include "keys_reaction.c"
