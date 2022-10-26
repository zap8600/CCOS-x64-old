#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/ints.h>

void kernel_main() {
	terminal_initialize();
	init_idt();
	terminal_write("Cotton Candy OS\n");
	terminal_write("WIP\n");
	terminal_write("Hooray! The IDT was succesfully made!\n");
	while (1) {}
	asm volatile ("int $0x3");
	terminal_write("Hooray! ISRs are working!\n");
	while (1) {}
}