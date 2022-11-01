#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>

void kernel_main() {
	terminal_initialize();
	init_idt();
	terminal_write("Cotton Candy OS\n");
	terminal_write("WIP\n");
	asm volatile ("int $0x3");
	while (1) {}
}