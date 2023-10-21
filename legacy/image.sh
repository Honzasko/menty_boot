if [ ! -d "build" ]; then
    mkdir build
fi

dd if=/dev/zero bs=1M count=64 of=build/raw.img
parted -s build/raw.img mklabel gpt
parted -s build/raw.img mkpart ESP fat32 2048s 100% 
parted -s build/raw.img set 1 esp on
dd if=mbr.bin of=build/raw.img bs=440 seek=0 count=1 conv=notrunc
dd if=rawsec.bin of=build/raw.img bs=512 seek=35 count=25 conv=notrunc
USED_LOOPBACK=$(sudo losetup -Pf --show build/raw.img)
sudo mkfs.fat -F 32 ${USED_LOOPBACK}p1
qemu-img convert -f raw -O qcow2 build/raw.img build/drive.qcow2