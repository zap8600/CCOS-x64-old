#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/ints.h>

void kernel_main() {
	terminal_initialize();
	init_idt();
	terminal_write("beans!\n");
	asm volatile ("int $0x3");
	while (1) {}
}