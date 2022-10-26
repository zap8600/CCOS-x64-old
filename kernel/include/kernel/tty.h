#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_write(const char* data);
void terminal_writestring(const char* data);

#endif
