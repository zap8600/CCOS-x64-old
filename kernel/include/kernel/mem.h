#include <stdint.h>
#include <stddef.h>

#include <kernel/string.h>
#include <kernel/stdio.h>
#include <kernel/limine.h>

typedef struct page
{
   uint32_t present    : 1;
   uint32_t rw         : 1;
   uint32_t user       : 1;
   uint32_t accessed   : 1;
   uint32_t dirty      : 1;
   uint32_t unused     : 7;
   uint32_t frame      : 20;
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    page_table_t *tables[1024];
    uint32_t tablesPhysical[1024];
    uint32_t physicalAddr;
} page_directory_t;

void switch_page_directory(page_directory_t *dir);
uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys);
uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);
uint32_t kmalloc(uint32_t sz);
void alloc_frame(page_t *page, int is_kernel, int is_writeable);
void free_frame(page_t *page);
void init_mem();
page_t *get_page(uint32_t address, int make, page_directory_t *dir);