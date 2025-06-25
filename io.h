#ifndef IO_H
#define IO_H

#define FB_COMMAND_PORT                             0x3D4
#define FB_DATA_PORT                                0x3D5
#define FB_HIGH_BYTE_COMMAND                        14
#define FB_LOW_BYTE_COMMAND                         15

void outb(unsigned short port, unsigned char data);
extern unsigned char inb(unsigned short port);

#endif //IO_H
