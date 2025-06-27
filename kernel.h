#ifndef KERNEL_H
#define KERNEL_H

#include "stdint.h"

#define SCREEN_WIDTH        80
#define SCREEN_HEIGHT       25
#define FG                  FB_WHITE
#define BG                  FB_BLACK
#define FB_BLACK             0
#define FB_BLUE              1
#define FB_GREEN             2
#define FB_CYAN              3
#define FB_RED               4
#define FB_MAGENTA           5
#define FB_BROWN             6
#define FB_WHITE             7
#define FB_GRAY              8
#define FB_LIGHT_BLUE        9
#define FB_LIGHT_GREEN       10
#define FB_LIGHT_CYAN        11
#define FB_LIGHT_RED         12
#define FB_LIGHT_MAGENTA     13
#define FB_LIGHT_BROWN       14
#define FB_DARK_BLUE         15
#define FB_DARK_GREEN        16
#define FB_DARK_CYAN         17
#define FB_DARK_RED          18
#define FB_DARK_MAGENTA      19
#define FB_DARK_BROWN        20
#define FB                   0x000B8000

extern void outb(unsigned short port, unsigned char val);


#endif //KERNEL_H
