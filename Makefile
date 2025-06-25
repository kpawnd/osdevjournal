ISO_NAME = myos.iso
KERNEL_BIN = kernel.bin
ASM_OBJ = kernel.o
C_OBJ = kernel_c.o
ASM = kernel.asm
C_SRC = kernel.c

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -m elf_i386

all: $(ISO_NAME)

$(ASM_OBJ): $(ASM)
	nasm -f elf32 $(ASM) -o $(ASM_OBJ)

$(C_OBJ): $(C_SRC)
	$(CC) $(CFLAGS) $(C_SRC) -o $(C_OBJ)

$(KERNEL_BIN): $(ASM_OBJ) $(C_OBJ)
	ld $(LDFLAGS) -o $(KERNEL_BIN) $(ASM_OBJ) $(C_OBJ)

$(ISO_NAME): $(KERNEL_BIN)
	mkdir -p iso/boot/grub
	cp $(KERNEL_BIN) iso/boot/kernel.bin
	echo 'menuentry "My Kernel" { multiboot /boot/kernel.bin; boot }' > iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_NAME) iso

run: $(ISO_NAME)
	qemu-system-i386 -cdrom $(ISO_NAME)

monitor: $(ISO_NAME)
	qemu-system-i386 -cdrom $(ISO_NAME) -monitor stdio

clean:
	rm -rf $(ASM_OBJ) $(C_OBJ) $(KERNEL_BIN) $(ISO_NAME) iso

.PHONY: all run monitor clean