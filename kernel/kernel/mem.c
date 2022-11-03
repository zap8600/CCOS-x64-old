#include <stdint.h>
#include <stddef.h>

#include <kernel/string.h>
#include <kernel/stdio.h>
#include <kernel/mem.h>

uintptr_t freebase;
uintptr_t freetop;
extern uintptr_t _kernel_end;

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
        return -1;
    } else {
        ptr = freebase + size;
        freebase = freebase + size;
        printf("ptr = %x", ptr);
        return ptr;
    }
}