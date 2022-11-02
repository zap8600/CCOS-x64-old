#!/bin/sh
set -e
. ./build.sh

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
