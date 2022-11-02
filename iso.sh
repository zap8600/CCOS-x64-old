#!/bin/sh
set -e
. ./build.sh

CC=cc
CPPFLAGS=
CFLAGS="-g -O2 -pipe -Wall -Wextra"
LDFLAGS=

DIR=./limine
if [ -d "$DIR" ];
then
    
else
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1

    make -C limine
fi

cp limine/limine-cd.bin limine/limine-cd-efi.bin limine/limine.sys sysroot/boot/

cat > sysroot/boot/limine.cfg << EOF
# Timeout in seconds that Limine will use before automatically booting.
TIMEOUT=5
 
# The entry name that will be displayed in the boot menu
:myOS
    # Change the protocol line depending on the used protocol.
    PROTOCOL=limine
 
    # Path to the kernel to boot. boot:/// represents the partition on which limine.cfg is located.
    KERNEL_PATH=boot:///boot/myos.elf
EOF

xorriso -as mkisofs -b boot/limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot boot/limine-cd-efi.bin -efi-boot-part --efi-boot-image --protective-msdos-label sysroot -o image.iso
./limine/limine-deploy image.iso