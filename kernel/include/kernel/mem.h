#include <stdint.h>
#include <stddef.h>

#include <kernel/stdio.h>

void init_mem();
uint64_t malloc(size_t size);