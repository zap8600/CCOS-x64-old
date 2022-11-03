#include <stdint.h>
#include <stddef.h>

#include <kernel/stdio.h>

typedef struct _KHEAPBLOCKBM {
	struct _KHEAPBLOCKBM *next;
	uint32_t size;
	uint32_t used;
	uint32_t bsize;
    uint32_t lfb;
} KHEAPBLOCKBM;
 
typedef struct _KHEAPBM {
	KHEAPBLOCKBM *fblock;
} KHEAPBM;

void k_heapBMInit(KHEAPBM *heap);
int k_heapBMAddBlock(KHEAPBM *heap, uintptr_t addr, uint32_t size, uint32_t bsize);
void *kmalloc(KHEAPBM *heap, uint32_t size);
void kfree(KHEAPBM *heap, void *ptr);