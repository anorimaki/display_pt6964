#include "main.h"
#include "ui.h"
#include "keys_reaction.h"


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
    struct KeysState keys_state;
    int32 counter = 0;
    
    ui_print(counter);
    while (TRUE) {
        ui_read_keys(keys);
        
        keys_update_state(keys, &keys_state);
        
        counter = apply_keys( keys_state.key_pressed, counter );
        
        ui_set_digits( counter );
        ui_display_data.fastfordwad = (keys_state.key_pressed>=3) && keys_state.fast_apply;
        ui_display_data.rewind = (keys_state.key_pressed<3) && (keys_state.key_pressed>=0) 
                                    && keys_state.fast_apply;
        ui_print(); 
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
