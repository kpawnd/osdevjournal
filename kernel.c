#include "kernel.h"
#include "serial.h"
#include "io.h"
#include "gdt.h"

static unsigned short cursor_pos = 0;

void scroll_up() {
    volatile char* fb = (volatile char*) FB;

    // move each line up by one row
    for (int row = 1; row < SCREEN_HEIGHT; row++) {
        for (int col = 0; col < SCREEN_WIDTH; col++) {
            int from = (row * SCREEN_WIDTH + col) * 2;
            int to   = ((row - 1) * SCREEN_WIDTH + col) * 2;

            fb[to]     = fb[from];     // copy char
            fb[to + 1] = fb[from + 1]; // copy attr
        }
    }

    // clear last line
    for (int col = 0; col < SCREEN_WIDTH; col++) {
        int i = ((SCREEN_HEIGHT - 1) * SCREEN_WIDTH + col) * 2;
        fb[i]     = ' ';
        fb[i + 1] = (BG << 4) | (FG & 0x0F);
    }
}


void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    volatile char *fb = (volatile char *) FB;
    fb[i * 2]     = c;
    fb[i * 2 + 1] = (bg << 4) | (fg & 0x0F);
}

void fb_write_str(unsigned int i, const char* str, unsigned char fg, unsigned char bg)
{
    volatile char *fb = (volatile char *) FB;
    for (unsigned int j = 0; str[j] != '\0'; j++) {
        fb[(i + j) * 2]     = str[j];
        fb[(i + j) * 2 + 1] = (bg << 4) | (fg & 0x0F);
    }
}

void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

int write(char *buf, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        fb_write_cell(cursor_pos, buf[i], FG, BG);
        cursor_pos++;

        if (cursor_pos >= SCREEN_WIDTH * SCREEN_HEIGHT) {
            scroll_up();
            cursor_pos -= SCREEN_WIDTH;
        }

        fb_move_cursor(cursor_pos);
    }

    return len;
}

void kmain() {
    char test[] = "Hello World!";
    write(test, sizeof(test));
    gdt_install();

    serial_configure_baud_rate(SERIAL_COM1_BASE, 1);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_write_str(SERIAL_COM1_BASE, "Serial initialized!\n");
    for (volatile int d = 0; d < 100000; d++) {}

    while (1) {}
}