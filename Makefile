ISO_NAME = myos.iso
KERNEL_BIN = kernel.bin
ASM_OBJ = kernel.o
IO_OBJ = io.o
C_OBJ = kernel_c.o serial.o
OBJ = $(ASM_OBJ) $(C_OBJ) $(IO_OBJ)
GDT_OBJ = gdt.o gdt_flush.o

ASM = kernel.asm
IOASM = io.asm
C_SRC = kernel.c serial.c

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -m elf_i386

all: $(ISO_NAME)

# Assembly
$(ASM_OBJ): $(ASM)
	nasm -f elf32 $< -o $@

$(IO_OBJ): $(IOASM)
	nasm -f elf32 $< -o $@

# C files
kernel_c.o: kernel.c
	$(CC) $(CFLAGS) $< -o $@

serial.o: serial.c
	$(CC) $(CFLAGS) $< -o $@

$(GDT_OBJ): gdt.c gdt.h gdt_flush.asm
	gcc $(CFLAGS) -c gdt.c -o gdt.o
	nasm -f elf32 gdt_flush.asm -o gdt_flush.o

# Link kernel
$(KERNEL_BIN): $(ASM_OBJ) $(C_OBJ) $(IO_OBJ) $(GDT_OBJ)
	ld $(LDFLAGS) -o $(KERNEL_BIN) $^

# Build ISO
$(ISO_NAME): $(KERNEL_BIN)
	mkdir -p iso/boot/grub
	cp $(KERNEL_BIN) iso/boot/kernel.bin
	echo 'menuentry "My Kernel" { multiboot /boot/kernel.bin; boot }' > iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso

# Run QEMU
run: $(ISO_NAME)
	qemu-system-i386 -cdrom $<

monitor: $(ISO_NAME)
	qemu-system-i386 -cdrom $< -serial stdio

# Clean up
clean:
	rm -f $(ASM_OBJ) $(C_OBJ) $(IO_OBJ) $(GDT_OBJ) $(KERNEL_BIN) $(ISO_NAME)
	rm -rf iso

.PHONY: all run monitor clean