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

void _kernel_end(void);
unsigned int vaddr = (unsigned int) &_kernel_end;

void kheapinit(KHEAPBM *heap);
int kaddblock(KHEAPBM *heap, uintptr_t addr, uint32_t size, uint32_t bsize);
void *kmalloc(KHEAPBM *heap, uint32_t size);
void kfree(KHEAPBM *heap, void *ptr);