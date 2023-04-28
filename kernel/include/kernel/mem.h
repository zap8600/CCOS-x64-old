void init_pmem(); // Initializes the physical memory manager by cycling through memmap entries until usable memory is found.
void list_memmap(); // Prints the memory map to the screen.
uint32_t pkmalloc(uint32_t size, int align, uint32_t *phys_addr); // Allocates physical memory using a WaterMark allocator.