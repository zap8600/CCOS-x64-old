#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>
#include <kernel/dbg.h>
#include <kernel/stdio.h>
#include <kernel/mem.h>

void _kernel_end(void);
uintptr_t vaddr = (uintptr_t) &_kernel_end + 0x100000;

void kernel_main()
{
	init_gdt();
	terminal_initialize();
	init_ints();
	printf("Cotton Candy OS\n");
	printf("WIP\n");
	breakpoint;
	printf("ISRs installed and working.\n");
	while (1) {}
}