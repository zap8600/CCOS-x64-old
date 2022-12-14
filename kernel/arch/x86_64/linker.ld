OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(_start)
SECTIONS
{
    . = 0xffffffff80000000;

	_kernel_start = .;
    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

    /* Move to the next memory page for .rodata */
    . += CONSTANT(MAXPAGESIZE);

    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    /* Move to the next memory page for .data */
    . += CONSTANT(MAXPAGESIZE);

    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
    }
	_kernel_end = .;

    /* Discard .note.* and .eh_frame since they may cause issues on some hosts. */
    /DISCARD/ : {
        *(.eh_frame)
        *(.note .note.*)
    }
}