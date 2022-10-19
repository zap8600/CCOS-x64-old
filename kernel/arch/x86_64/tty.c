#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR        /* use the special renderer for 32 bit truecolor packed pixels */
#include <kernel/ssfn.h>
#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
	ssfn_src = &_binary_console_sfn_start;      /* the bitmap font to use */
	ssfn_dst.ptr = 0xE0000000;                  /* framebuffer address and bytes per line */
	ssfn_dst.p = 4096;
	ssfn_dst.fg = 0xFFFFFFFF;                   /* colors, white on black */
	ssfn_dst.bg = 0;
	ssfn_dst.x = 100;                           /* coordinates to draw to */
	ssfn_dst.y = 200;
}

void terminal_putentryat(unsigned char c) {
	
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
