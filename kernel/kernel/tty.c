#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/string.h>

void terminal_initialize(void)
{
}

void terminal_write(const char* data, size_t size)
{
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}