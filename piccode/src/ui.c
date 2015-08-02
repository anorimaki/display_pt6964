#include "main.h"
#include "ui.h"
#include "pt6964.h"

#define PT6964_MODE PT6964_MODE_7_DIGITS

//
//Module data
//
struct DisplayData ui_display_data;

int8 ui_internal_display_data[14] = {0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0};

const int8 ui_digits_bit_mask[UI_DIGITS_SIZE] = {
    0b00000100, 0b00001000, 0b00010000, 0b00100000,
    0b10000000, 0b00000001
};

const int8 ui_digits_address_mask[11] = {// 7 segments
    0b01111110, 0b00110000, 0b01101101, 0b01111001, 0b00110011,
    0b01011011, 0b01011111, 0b01110000, 0b01111111, 0b01111011,
    0b00000000
}; //10 -> Special value: BLANK

//
//Private module functions declaration
//
void ui_apply_digit(int postion, int address);

//
//Implementation
//
void ui_init() {
    pt6964_init();

    pt6964_clear_display();
    pt6964_set_display_mode(PT6964_MODE);
    pt6964_set_display_off();
    pt6964_set_display_mode(PT6964_MODE);
    pt6964_set_display_on();
}


void ui_print(int32 counter) {
    int i = 0;
    while (counter > 0) {
        ui_display_data.digits[i] = counter % 10;
        counter /= 10;
        ++i;
    }

    if (i == 0) {
        ui_display_data.digits[0] = 0;
        ++i;
    }

    for (; i < UI_DIGITS_SIZE; ++i) {
        ui_display_data.digits[i] = UI_DIGIT_BLANK;
    }
    ui_print();
}


void ui_print() {
    ui_apply_digit(0, 0);
    ui_apply_digit(1, 0);
    ui_apply_digit(2, 0);
    ui_apply_digit(3, 0);
    ui_apply_digit(4, 0);
    ui_apply_digit(5, 1);

    pt6964_send_all_data(ui_internal_display_data);
    pt6964_set_display_mode(PT6964_MODE);
    pt6964_set_display_on();
}


void ui_read_keys(bool keys[]) {
    bool internal_keys[20];

    pt6964_read(internal_keys);

    keys[0] = internal_keys[1];
    keys[1] = internal_keys[0];
    keys[2] = internal_keys[5];
    keys[3] = internal_keys[4];
    keys[4] = internal_keys[3];
    keys[5] = internal_keys[2];
}



//
//Private module functions implementation
//
void ui_apply_digit(int position, int address) {
    int i;
    int8 value = ui_display_data.digits[position];
    int8 bit_mask = ui_digits_bit_mask[position];
    int8 address_mask = ui_digits_address_mask[value];

    for (i = 0; i < 7; i++) {
        if (address_mask & 0x01) {
            ui_internal_display_data[ address ] |= bit_mask;
        } else {
            ui_internal_display_data[ address ] &= ~bit_mask;
        }
        address += 2;
        address_mask >>= 1;
    }
}



