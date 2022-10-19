#include <stdio.h>

#include <kernel/tty.h>

void _start() {
	terminal_initialize();
	printf("Hello, kernel World!\n");
}
