#include "main.h"
#include "pt6964.h"
#include <stdarg.h>

#define PT6964_WRITEDATA   0b00000010
#define PT6964_READDATA    0b01000010
#define PT6964_SETADDRESS  0b00000011
#define PT6964_DISPLAY_ON  0b00110001
#define PT6964_DISPLAY_OFF 0b00100001

int8 reverse(int8 b) {
    int8 ret = 0;
    int i;

    for (i = 0; i < 8; ++i) {
        ret <<= 1;
        ret = ret | (b & 0x01);
        b >>= 1;
    }

    return ret;
}

void pt6964_init() {
    output_high(PIN_STB);
    output_drive(PIN_STB);

    setup_spi(SPI_MASTER | SPI_SCK_IDLE_HIGH | SPI_XMIT_L_TO_H | SPI_SAMPLE_AT_MIDDLE | SPI_CLK_DIV_16);
    output_drive(PIN_CLK);
}

void pt6964_send_command(int8 command) {
    output_drive(PIN_DATA_OUT);

    output_low(PIN_STB);
    delay_us(1);

    spi_write(command);
    delay_us(1);

    output_high(PIN_STB);
}

void pt6964_send_data(int8 address, int count, ...) {
    va_list data;
    int8 data_byte;

    va_start(data, count);

    pt6964_send_command(PT6964_WRITEDATA);

    output_drive(PIN_DATA_OUT);

    output_low(PIN_STB);
    delay_us(1);

    address = reverse(address);
    spi_write(PT6964_SETADDRESS | address);
    delay_us(1);

    while (count--) {
        data_byte = va_arg(data, int8);
        data_byte = reverse(data_byte);
        spi_write(data_byte);

        delay_us(1);
    }

    va_end(data);

    output_high(PIN_STB);
}

void pt6964_send_all_data(int8 data[14]) {
    pt6964_send_data(0, 14,
            data[0], data[1], data[2], data[3], data[4],
            data[5], data[6], data[7], data[8], data[9],
            data[10], data[11], data[12], data[13]);
}

void pt6964_set_display_on() {
    pt6964_send_command(PT6964_DISPLAY_ON);
}

void pt6964_set_display_off() {
    pt6964_send_command(PT6964_DISPLAY_OFF);
}

void pt6964_set_display_mode(int8 mode) {
    pt6964_send_command(mode);
}

void pt6964_clear_display() {
    pt6964_send_data(0, 14,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0);
}

void pt6964_read(bool keys[]) {
    int i;
    int8 current_block;
    int key_index;

    output_drive(PIN_DATA_OUT);

    output_low(PIN_STB);
    delay_us(1);

    spi_write(PT6964_READDATA);

    output_float(PIN_DATA_OUT);

    delay_us(1);

    key_index = 0;
    for (i = 0; i < 5; ++i) { //read 5 bits of key scan
        current_block = spi_read(0xFF);

        keys[key_index++] = (current_block & 0b10000000) != 0;
        keys[key_index++] = (current_block & 0b01000000) != 0;
        keys[key_index++] = (current_block & 0b00010000) != 0;
        keys[key_index++] = (current_block & 0b00001000) != 0;
    }

    output_high(PIN_STB);
}
