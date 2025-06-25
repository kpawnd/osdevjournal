ISO_NAME = myos.iso
KERNEL_BIN = kernel.bin
KERNEL_OBJ = kernel.o
ASM = kernel.asm

all: $(ISO_NAME)

$(KERNEL_OBJ): $(ASM)
	nasm -f elf32 $(ASM) -o $(KERNEL_OBJ)

$(KERNEL_BIN): $(KERNEL_OBJ)
	ld -m elf_i386 -Ttext 0x100000 -e loader -o $(KERNEL_BIN) $(KERNEL_OBJ)

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
	rm -rf $(KERNEL_OBJ) $(KERNEL_BIN) $(ISO_NAME) iso

.PHONY: all run monitor clean
