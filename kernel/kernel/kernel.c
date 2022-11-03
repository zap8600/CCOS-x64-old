#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>
#include <kernel/dbg.h>
#include <kernel/stdio.h>
#include <kernel/mem.h>

KHEAPBM kheap;
char *ptr;

void kernel_main()
{
	init_gdt();
	terminal_initialize();
	init_idt();
	kheapinit(&kheap);
	kaddblock(&kheap, 0x100000, 0x100000, 16);
	printf("Cotton Candy OS\n");
	printf("WIP\n");
	breakpoint;
	printf("ISRs installed and working.\n");
	ptr = (char*)kmalloc(&kheap, 256);
	printf("%s\n", ptr);
	kfree(&kheap, ptr);
	while (1) {}
}