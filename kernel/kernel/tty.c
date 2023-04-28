#include <stdint.h>
/* #include <kernel/ssfn.h> */
#include <kernel/tty.h>
#include <kernel/limine.h>
#include <kernel/io.h>
#include <kernel/string.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

void terminal_initialize(void)
{
    /*
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    */
   if (terminal_request.response == NULL || terminal_request.response->terminal_count < 1)
    {
        done();
    }
}

void terminal_write(const char* data, size_t size)
{
    struct limine_terminal *terminal = terminal_request.response->terminals[0];
    terminal_request.response->write(terminal, data, size);
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
    /*
    if(*s == '\n') {
        ssfn_dst.y += ssfn_src->height;
        ssfn_dst.x = 0;
    } else {
        ssfn_putc(*s);
    }
    */
}
