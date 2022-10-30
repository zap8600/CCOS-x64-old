#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>

void kernel_main() {
	init_gdt();
	while (1) {}
	terminal_initialize();
	terminal_write("Cotton Candy OS\n");
	terminal_write("WIP\n");
}