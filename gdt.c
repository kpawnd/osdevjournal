#include "gdt.h"

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gp;

static void gdt_set_entry(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[idx].base_low    = base & 0xFFFF;
    gdt[idx].base_mid    = (base >> 16) & 0xFF;
    gdt[idx].base_high   = (base >> 24) & 0xFF;

    gdt[idx].limit_low   = limit & 0xFFFF;
    gdt[idx].granularity = (limit >> 16) & 0x0F;
    gdt[idx].granularity |= gran & 0xF0;
    gdt[idx].access      = access;
}

void gdt_install() {
    gp.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
    gp.base  = (uint32_t)&gdt;

    gdt_set_entry(0, 0, 0, 0, 0);                   // Null
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);    // Code segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);    // Data segment

    gdt_flush((uint32_t)&gp);
}