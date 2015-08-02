#include "main.h"
#include "keys_reaction.h"

#define KEYS_NO_KEY -1
#define KEYS_MIN_COUNTER_TO_APPLY 3

            //Note: don't apply timer scaler in macros (divide by 256) to avoid significan looses due to 
            // round operations with integers.
            // Scaler timer will be applied after ms multiplication.
#define KEYS_FAST_APPLY_TIMER_WITHOUT_SCALER_MHZ (CLOCK_MHZ>>2)     //Divide by 4 (Tcy = Tosc*4, Tcy=CLKO period)
#define KEYS_FAST_APPLY_TIMER_WITHOUT_SCALER_FOR_MS (KEYS_FAST_APPLY_TIMER_WITHOUT_SCALER_MHZ/1000)

//
// Module data
//
static struct {
	int key_pressed;
	int key_pressed_counter;
	bool fast_apply;
} keys_state;

static struct {
	int keys_size;
	int16 fastapply_timer_counter;
} keys_config;

//
//	Internal functions declaration
//
int keys_find_pressed( bool keys[] );
void keys_enable_fastapply_counter();
void keys_disable_fastapply_counter();

//
//	Implementation
//

void keys_init(int16 ms_to_fast_apply, int k_size) {
    int32 needed_tics0 = ms_to_fast_apply * KEYS_FAST_APPLY_TIMER_WITHOUT_SCALER_FOR_MS;
    int16 needed_tics = needed_tics0 >> 8; //Divide by 256 (T0 set to DIV_256)

    keys_config.keys_size = k_size;
    keys_config.fastapply_timer_counter = 0xFFFF - needed_tics;
}


int keys_update_state( bool keys[] ) {
	if ( (keys_state.key_pressed!=KEYS_NO_KEY) && keys[keys_state.key_pressed] ) {
		if ( keys_state.key_pressed_counter <= KEYS_MIN_COUNTER_TO_APPLY ) {
			++keys_state.key_pressed_counter;
		}
		if ( keys_state.key_pressed_counter == KEYS_MIN_COUNTER_TO_APPLY) {
			keys_enable_fastapply_counter();
			return keys_state.key_pressed;
		}
		if ( keys_state.fast_apply ) {
			return keys_state.key_pressed;
		}
		return KEYS_NO_KEY;
	}
	
	keys_state.key_pressed = keys_find_pressed( keys );
	keys_state.key_pressed_counter = 0;
	keys_state.fast_apply = false;
	keys_disable_fastapply_counter();
	
	return KEYS_NO_KEY;
}

//
//	Internal functions implementation
//
#INT_TIMER0
void timer0_isr() {
	keys_state.fast_apply = true;
	keys_disable_fastapply_counter();
}


void keys_enable_fastapply_counter() {
	setup_timer_0( T0_INTERNAL | T0_DIV_256 );
	set_timer0( keys_config.fastapply_timer_counter );
	enable_interrupts(INT_TIMER0);
}


void keys_disable_fastapply_counter() {
	disable_interrupts(INT_TIMER0);
	setup_timer_0( T0_OFF );
}


int keys_find_pressed( bool keys[] ) {
	int i;
	
	for( i=0; i<keys_config.keys_size; ++i ) {
		if ( keys[i] ) {
			return i;
		}
	}
	return KEYS_NO_KEY;
}