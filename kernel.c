#include "kernel.h"

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

void kmain() {
    fb_write_str(0, "Hello!", FB_RED, FB_GRAY);
    fb_write_str(80, "World!", FB_GREEN, FB_GRAY);
    while (1) {}
}