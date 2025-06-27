extern kmain
global loader

MAGIC_NUMBER            equ 0x1BADB002
FLAGS                   equ 0x0
CHECKSUM                equ -MAGIC_NUMBER
KERNEL_STACK_SIZE       equ 4096

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
                                        ; Set up GDT
    lgdt [gdt_descriptor]
                                        ; Set up stack
    mov eax, 0xCAFEBABE
    mov esp, kernel_stack + KERNEL_STACK_SIZE
                                        ; Call kernel main
    call kmain

.loop:
    jmp .loop

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE


section .data
align 8
gdt_start:
    dq 0                                ; Null descriptor
    dq 0x00CF9A000000FFFF               ; Code segment
    dq 0x00CF92000000FFFF               ; Data segment
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start