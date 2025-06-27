global gdt_flush

gdt_flush:
    mov eax, [esp + 4]   ; get pointer to gdt_ptr struct
    lgdt [eax]

    ; Reload segment registers
    mov ax, 0x10         ; Data segment selector (GDT entry 2)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush      ; Far jump to code segment (entry 1)
.flush:
    ret