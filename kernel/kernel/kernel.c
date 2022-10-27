#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/ints.h>

void kernel_main() {
	terminal_initialize();
	init_idt();
	terminal_write("Cotton Candy OS\n");
	terminal_write("WIP\n");
	terminal_write("Is the IDT working?\n");
	asm volatile ("int $0x3");
	terminal_write("Hooray! The IDT is working!\n");
	while (1) {}
}