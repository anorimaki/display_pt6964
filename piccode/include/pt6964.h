#ifndef PT6964_H
#define PI6964_H

#include "ccs/compilerspecs.h"

void pt6964_init() ;

void pt6964_read( bool keys[] );

void pt6964_send_data( int8 address, int count, ... );

void pt6964_send_all_data( int8 data[14] );

void pt6964_set_display_on();
void pt6964_set_display_off();

#define PT6964_MODE_4_DIGITS  0b00000000
#define PT6964_MODE_5_DIGITS  0b10000000
#define PT6964_MODE_6_DIGITS  0b01000000
#define PT6964_MODE_7_DIGITS  0b11000000
void pt6964_set_display_mode( int8 mode );

void pt6964_clear_display();

#endif
