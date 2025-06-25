#include "kernel.h"
#include "serial.h"
#include "io.h"

int serial_is_transmit_fifo_empty(unsigned short com) {
    return inb(SERIAL_LINE_STATUS_PORT(com)) & SERIAL_LINE_STATUS_EMPTY_TRANSMIT_BUFFER;
}

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), divisor & 0xFF);          // Low byte
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0xFF);   // High byte
}

void serial_configure_line(unsigned short com) {
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);  // 8N1
}

void serial_write_char(unsigned short com, char c) {
    while (!serial_is_transmit_fifo_empty(com));
    outb(SERIAL_DATA_PORT(com), c);
}

void serial_write_str(unsigned short com, const char* str) {
    for (int i = 0; str[i] != '\0'; i++)
        serial_write_char(com, str[i]);
}