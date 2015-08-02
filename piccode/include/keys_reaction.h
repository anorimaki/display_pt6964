#ifndef KEYS_REACTION_H
#define KEYS_REACTION_H

void keys_init( int16 ms_to_fast_apply, int keys_size );
int keys_update_state( bool keys[] );

#endif