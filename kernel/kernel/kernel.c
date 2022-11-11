#include <kernel/limine.h>
#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>
#include <kernel/dbg.h>
#include <kernel/stdio.h>
#include <kernel/mem.h>

void _kernel_end(void);
uintptr_t vaddr = (uintptr_t) &_kernel_end;

KHEAPBM kheap;
char *ptr;

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

void kernel_main()
{
	init_gdt();
	terminal_initialize();
	init_ints();
	struct limine_memmap_entry *memmap_entry = memmap_request.response->entries[1];
    printf("Second memory-mapped entry type: %d\n", memmap_entry->type);
    printf("Second memory-mapped entry base: %x\n", memmap_entry->base);
    printf("Second memory-mapped entry length: %x\n", memmap_entry->length);
	kheapinit(&kheap);
	kaddblock(&kheap, memmap_entry->base, 0x1000, 16);
	printf("Cotton Candy OS\n");
	printf("WIP\n");
	breakpoint;
	printf("ISRs installed and working.\n");
	ptr = (char*)kmalloc(&kheap, 256);
	printf("Pointer to allocated memory: %x\n", &ptr);
	kfree(&kheap, ptr);
	printf("Allocated memory has been freed.\n");
	while (1) {}
}