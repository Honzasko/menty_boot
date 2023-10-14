# Menty Bootloader
## System requirments
General:<br>
  - 128 MiB of RAM<br>
  - 64bit CPU<br>
BIOS:<br>
  - Support of extented functions for disk

## Build instructions
Can be build only on Linux or on Windows using WSL<br> 
Dependencies:
  - QEMU(qemu-img)
  - gcc
  - dd
  - make
  - nasm
  - ld
  - objcopy

run: 
```
git clone https://github.com/Honzasko/menty_boot.git
cd menty_boot/legacy
make
```



