#ifndef GDT_H
#define GDT_H
#include "stdint.h"

#define GDT_ENTRIES 3

struct gdt {
    uint16_t size;          // 2 bytes
    uint32_t address;       // 4 bytes
} __attribute__((packed));

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Only declare these here
extern void gdt_flush(uint32_t);
extern struct gdt_entry gdt[];
extern struct gdt_ptr gp;

void gdt_install();

#endif