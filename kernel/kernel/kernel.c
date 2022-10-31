#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>

void kernel_main() {
	init_gdt();
	terminal_initialize();
	terminal_write("Cotton Candy OS\n");
	terminal_write("WIP\n");
	while (1) {}
}