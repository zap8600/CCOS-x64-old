#include <kernel/tty.h>

unsigned int vsprintf(char *dst, char* fmt, __builtin_va_list args);
unsigned int sprintf(char *dst, char* fmt, ...);
void printf(char *fmt, ...);