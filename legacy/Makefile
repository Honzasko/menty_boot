all:
	gcc -m32 -c src/asm.c -o asm.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector
	gcc -m32 -c src/disk.c -o disk.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector
	gcc -m32 -c src/video.c -o video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector
	gcc -m32 -c second.c -o second.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector 
	nasm second_entry.asm -f elf -o second_entry.o
	ld -m elf_i386 -T linker.ld  second_entry.o video.o  disk.o asm.o second.o -o secstage.bin -nostdlib
	objcopy -O binary secstage.bin rawsec.bin
	nasm mbr.asm -f bin -o mbr.bin
	./image.sh

	
