#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>
#include <kernel/dbg.h>
#include <kernel/stdio.h>
#include <kernel/mem.h>

void kernel_main()
{
	init_gdt();
	terminal_initialize();
	init_idt();
	printf("Cotton Candy OS\n");
	printf("WIP\n");
	breakpoint;
	printf("It works!\n");
	malloc(0x1000);
	while (1) {}
}