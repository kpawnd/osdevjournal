ENTRY(loader)

SECTIONS {
  . = 0x100000;

  .text : {
    *(.multiboot)
    *(.text*)
  }

  .bss : {
    *(.bss*)
    *(COMMON)
  }

  .data : {
    *(.data*)
  }

  .rodata : {
    *(.rodata*)
  }
}