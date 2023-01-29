all: build clean

build:
	gcc -m32 -c second.c  -o second.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -nolibc
	ld -m elf_i386 -T linker.ld second.o -o secstage.bin -nostdlib
	objcopy -O binary secstage.bin rawsec.bin
	nasm mbr.asm -f bin -o mbr.bin
	cat mbr.bin rawsec.bin > bootloader.bin
	dd if=/dev/zero of=drive.img bs=512 count=40960
	dd if=bootloader.bin of=drive.img seek=0 count=6 conv=notrunc

clean:
	rm  mbr.bin rawsec.bin secstage.bin 