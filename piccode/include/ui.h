#ifndef UI_H
#define UI_H

#define UI_DIGITS_SIZE      6
#define UI_DIGIT_BLANK      10
#define UI_KEYS_SIZE        6

struct DisplayData {
	int8 digits[UI_DIGITS_SIZE];
    bool dtv;
    bool fastfordwad;
	bool hdd;
    bool ch;
	bool pause;
    bool rewind;
    bool rec;
    bool shift;
    bool time;
    bool two_points;
};

extern struct DisplayData ui_display_data;

void ui_init();
void ui_set_digits( int32 counter );
void ui_print( int32 counter );
void ui_print();

void ui_read_keys( bool keys[] );

#endif