all:
	gcc -m32 -c src/video.c  -o video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -nolibc
	gcc -m32 -c second.c  -o second.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -nolibc
	nasm second_entry.asm -f elf -o second_entry.o
	ld -m elf_i386 -T linker.ld  second_entry.o video.o second.o -o secstage.bin -nostdlib
	objcopy -O binary secstage.bin rawsec.bin
	nasm mbr.asm -f bin -o mbr.bin
	./image.sh
	rm second_entry.o second.o video.o secstage.bin mbr.bin rawsec.bin 
	
