all:
	g++ -m32 -c src/asm.cpp -o asm.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector
	g++ -m32 -c src/basics.cpp -o basics.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector
	g++ -m32 -c src/ata.cpp -o ata.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector
	g++ -m32 -c src/video.cpp -o video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector
	g++ -m32 -c second.cpp -o second.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostartfiles -nostdlib -nodefaultlibs -fno-stack-protector 
	nasm second_entry.asm -f elf -o second_entry.o
	ld -m elf_i386 -T linker.ld  second_entry.o video.o  ata.o asm.o basics.o second.o -o secstage.bin -nostdlib
	objcopy -O binary secstage.bin rawsec.bin
	nasm mbr.asm -f bin -o mbr.bin
	./image.sh
	$(MAKE) clean

clean:
	rm asm.o ata.o basics.o mbr.bin 
