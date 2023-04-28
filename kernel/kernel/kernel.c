#include <kernel/limine.h>
#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/gdt.h>
#include <kernel/ints.h>
#include <kernel/dbg.h>
#include <kernel/stdio.h>

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

static volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
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
	printf("Cotton Candy OS\n");
	printf("WIP\n");
	breakpoint;
	printf("ISRs installed and working.\n");
	struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
	printf("Framebuffer address: %x\n", framebuffer->address);
	// The framebuffer is currently not used, due to errors during SSFN's simple renderer initialization.
	init_pmem();
	printf("Physical memory manager initialized.\n");
	uint32_t ptr;
	uint32_t page = pkmalloc(1000, 1, &ptr);
	printf("Allocated physical memory at %x with `pkmalloc(1000, 1, &ptr)` in the kernel.\n", ptr);
	while (1) {}
}
