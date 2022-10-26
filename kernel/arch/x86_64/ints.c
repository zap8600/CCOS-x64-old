#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/ints.h>

static struct idt_pointer idtp;
static idt_entry_t idt[256];


void isr_handler()
{
    terminal_write("Received ISR!\n");
}

void init_idt()
{
    idtp.limit = sizeof(idt);
    idtp.base  = (uintptr_t)&idt;
    idt_set_gate(0, _isr0);
    idt_set_gate(0, _isr1);
    idt_set_gate(0, _isr2);
    idt_set_gate(0, _isr3);
    idt_set_gate(0, _isr4);
    idt_set_gate(0, _isr5);
    idt_set_gate(0, _isr6);
    idt_set_gate(0, _isr7);
    idt_set_gate(0, _isr8);
    idt_set_gate(0, _isr9);
    idt_set_gate(0, _isr10);
    idt_set_gate(0, _isr11);
    idt_set_gate(0, _isr12);
    idt_set_gate(0, _isr13);
    idt_set_gate(0, _isr14);
    idt_set_gate(0, _isr15);
    idt_set_gate(0, _isr16);
    idt_set_gate(0, _isr17);
    idt_set_gate(0, _isr18);
    idt_set_gate(0, _isr19);
    idt_set_gate(0, _isr20);
    idt_set_gate(0, _isr21);
    idt_set_gate(0, _isr22);
    idt_set_gate(0, _isr23);
    idt_set_gate(0, _isr24);
    idt_set_gate(0, _isr25);
    idt_set_gate(0, _isr26);
    idt_set_gate(0, _isr27);
    idt_set_gate(0, _isr28);
    idt_set_gate(0, _isr29);
    idt_set_gate(0, _isr30);
    idt_set_gate(0, _isr31);

    asm volatile (
		"lidt %0"
		: : "m"(idtp)
	);
}

void idt_set_gate(int n, interrupt_handler_t handler)
{
    uintptr_t base = (uintptr_t)handler;
    idt[n].offset_1 = base & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].ist = 0;
    idt[n].type_attributes = 0x8F;
    idt[n].offset_2 = (base >> 16) & 0xFFFF;
    idt[n].offset_3 = (base >> 32) & 0xFFFFFFFF;
    idt[n].zero = 0;
}