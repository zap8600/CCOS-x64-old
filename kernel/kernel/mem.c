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

void *malloc(size_t size)
{
    void *ptr;

    if((freetop - freebase) < size) {
        printf("Error! Not enough memory avalible to allocate memory!");
        ptr = 0x0;
        return ptr;
    } else {
        ptr = freebase;
        freebase += size;
        printf("ptr = %x", ptr);
        return ptr;
    }
}