// Bitmap Physical Memory Manager/Page Frame Allocator
#include <stddef.h>
#include <stdint.h>
#include <kernel/limine.h>

#define PMM_BLOCK_SIZE 4096

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

//Pointer to the start of the free memory region. Isn't initialized until the init_pmem function is called.
uint32_t free_mem_addr = 0;

//init_pmem function. Initializes the physical memory manager by cycling through memmap entries until usable memory is found.
void init_pmem() {
    struct limine_memmap_entry *memmap_entry;
    for (int i = 0; i < memmap_request.response->entry_count; i++) {
        memmap_entry = memmap_request.response->entries[i];
        if (memmap_entry->type == 0) {
            free_mem_addr = memmap_entry->base;
            break;
        }
    }
}

uint32_t pkmalloc(uint32_t size, int align, uint32_t *phys_addr) {
    /* Pages are aligned to 4K, or 0x1000 */
    if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    /* Save also the physical address */
    if (phys_addr) *phys_addr = free_mem_addr;

    uint32_t ret = free_mem_addr;
    free_mem_addr += size; /* Remember to increment the pointer */
    return ret;
}