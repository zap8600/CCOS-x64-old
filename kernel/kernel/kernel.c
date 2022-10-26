#include <kernel/tty.h>

void kernel_main() {
	terminal_initialize();
	terminal_write("beans!\n");
	while (1) {}
}