#include <stdio.h>

#include <kernel/tty.h>

void kernel_main() {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	while (1) {}
}
