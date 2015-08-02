#ifndef KEYS_REACTION_H
#define KEYS_REACTION_H

struct KeysState {
	int key_pressed;
	bool fast_apply;
};

void keys_init( int16 ms_to_fast_apply, int keys_size );
void keys_update_state( bool keys[], struct KeysState* result );

#endif