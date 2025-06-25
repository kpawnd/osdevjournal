#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_COM1_BASE                            0x3F8
#define SERIAL_DATA_PORT(base)                      (base)
#define SERIAL_FIFO_COMMAND_PORT(base)              (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)              (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)             (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)               (base + 5)

#define SERIAL_LINE_ENABLE_DLAB                     0x80
#define SERIAL_LINE_STATUS_EMPTY_TRANSMIT_BUFFER    0x20

void serial_configure_line(unsigned short com);
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
int serial_is_transmit_fifo_empty(unsigned short com);
void serial_write_char(unsigned short com, char c);
void serial_write_str(unsigned short com, const char* str);

#endif //SERIAL_H
