#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR        /* use the special renderer for 32 bit truecolor packed pixels */
#include <kernel/ssfn.h>
#include <kernel/tty.h>

extern uint8_t fb;
extern volatile unsigned char _binary_unifont_sfn_start;

void terminal_initialize(void) {
	ssfn_src = &_binary_unifont_sfn_start;      /* the bitmap font to use */
	ssfn_dst.ptr = &fb;                  /* framebuffer address and bytes per line */
	ssfn_dst.p = 4096;
	ssfn_dst.fg = 0xFFFFFFFF;                   /* colors, white on black */
	ssfn_dst.bg = 0;
	ssfn_dst.x = 100;                           /* coordinates to draw to */
	ssfn_dst.y = 200;
}

void terminal_putentryat(char *s) {
	if(*s == '\n') {
    		ssfn_dst.y += ssfn_src->height;
    		ssfn_dst.x = 0;
	} else
    		ssfn_putc(*s);
}

void terminal_putchar(char c) {
	terminal_putentryat(c);
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
