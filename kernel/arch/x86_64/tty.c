#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/limine.h>
#include <kernel/io.h>

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};
 
static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

void terminal_initialize(void) {
    // Ensure we got a terminal
    if (terminal_request.response == NULL || terminal_request.response->terminal_count < 1) {
        done();
    }
}

void terminal_write(const char* data) {
    int i;
    for(i = 0; data[i] != '\0'; ++i);
    struct limine_terminal *terminal = terminal_request.response->terminals[0];
    terminal_request.response->write(terminal, data, i);
}

void terminal_writestring(const char* data) {
   terminal_write(data);
}