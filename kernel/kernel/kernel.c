#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>

void kernel_main()
{
	init_gdt();
	terminal_initialize();
	init_idt();
	terminal_writestring("Cotton Candy OS\n");
	terminal_writestring("WIP\n");
	asm volatile ("int $0x3");
	terminal_writestring("It works!\n");
	while (1) {}
}