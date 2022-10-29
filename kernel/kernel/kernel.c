#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>

void kernel_main() {
	init_gdt();
	terminal_initialize();
	terminal_write("Cotton Candy OS\n");
	terminal_write("WIP\n");
	/* terminal_write("Is the IDT working?\n");
	asm volatile ("int $0x3");
	terminal_write("Hooray! The IDT is working!\n"); */
	while (1) {}
}