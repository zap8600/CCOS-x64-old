#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>
#include <kernel/dbg.h>
#include <kernel/stdio.h>
#include <kernel/mem.h>

extern uint64_t _kernel_end;

void kernel_main()
{
	init_gdt();
	terminal_initialize();
	init_idt();
	printf("Cotton Candy OS\n");
	printf("WIP\n");
	init_mem();
	breakpoint;
	printf("It works!\n");
	printf("%x", _kernel_end);
	while (1) {}
}