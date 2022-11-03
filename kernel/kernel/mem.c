#include <stdint.h>
#include <stddef.h>

#include <kernel/string.h>
#include <kernel/stdio.h>
#include <kernel/mem.h>

uint64_t freebase;
uint64_t freetop;
extern uint64_t _kernel_end;

void init_mem()
{
    freebase = _kernel_end;
    freetop = 0xffffffffffe09000;
}

uint64_t malloc(size_t size)
{
    uint64_t ptr;

    if((freetop - freebase) < size) {
        printf("Error! Not enough memory avalible to allocate memory!\n");
        printf("Setting ptr to 0x0!\n");
        ptr = 0x0;
    } else {
        ptr = freebase + size;
        freebase += size;
        printf("ptr: %x\n", ptr);
    }
    return ptr;
}