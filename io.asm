global outb                 ; make the label outb visible outside this file

                            ; outb - send a byte to an I/O port
                            ; stack: [esp + 8] the data byte
                            ;        [esp + 4] the I/O port
                            ;        [esp    ] return address
outb:
    mov al, [esp + 8]       ; move the data to be sent into the al register
    mov dx, [esp + 4]       ; move the address of the I/O port into the dx register
    out dx, al              ; send the data to the I/O port
    ret                     ; return to the calling function

global inb

                            ; inb - read a byte from an I/O port
                            ; stack: [esp + 4] = port
                            ; return: al contains result, returned in eax (zero-extended)
inb:
    mov dx, [esp + 4]       ; Load port into dx
    in al, dx               ; Read byte from port into al
    ret