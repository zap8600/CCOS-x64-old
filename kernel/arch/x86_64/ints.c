#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/ints.h>

static struct IDTRS idtr;
static IDTEntry idt[256];


void isr_handler()
{
    terminal_write("Received ISR!\n");
}

void init_idt()
{
    idtr.limit = sizeof(idtr);
    idtr.base  = (uint32_t)&idt;
    idt_set_gate(0, (uint32_t)_isr0);
    idt_set_gate(0, (uint32_t)_isr1);
    idt_set_gate(0, (uint32_t)_isr2);
    idt_set_gate(0, (uint32_t)_isr3);
    idt_set_gate(0, (uint32_t)_isr4);
    idt_set_gate(0, (uint32_t)_isr5);
    idt_set_gate(0, (uint32_t)_isr6);
    idt_set_gate(0, (uint32_t)_isr7);
    idt_set_gate(0, (uint32_t)_isr8);
    idt_set_gate(0, (uint32_t)_isr9);
    idt_set_gate(0, (uint32_t)_isr10);
    idt_set_gate(0, (uint32_t)_isr11);
    idt_set_gate(0, (uint32_t)_isr12);
    idt_set_gate(0, (uint32_t)_isr13);
    idt_set_gate(0, (uint32_t)_isr14);
    idt_set_gate(0, (uint32_t)_isr15);
    idt_set_gate(0, (uint32_t)_isr16);
    idt_set_gate(0, (uint32_t)_isr17);
    idt_set_gate(0, (uint32_t)_isr18);
    idt_set_gate(0, (uint32_t)_isr19);
    idt_set_gate(0, (uint32_t)_isr20);
    idt_set_gate(0, (uint32_t)_isr21);
    idt_set_gate(0, (uint32_t)_isr22);
    idt_set_gate(0, (uint32_t)_isr23);
    idt_set_gate(0, (uint32_t)_isr24);
    idt_set_gate(0, (uint32_t)_isr25);
    idt_set_gate(0, (uint32_t)_isr26);
    idt_set_gate(0, (uint32_t)_isr27);
    idt_set_gate(0, (uint32_t)_isr28);
    idt_set_gate(0, (uint32_t)_isr29);
    idt_set_gate(0, (uint32_t)_isr30);
    idt_set_gate(0, (uint32_t)_isr31);

    asm volatile (
		"lidt %0"
		: : "m"(idtr)
	);
}

void idt_set_gate(int n, uint32_t base)
{
    idt[n].offset_1 = base & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].ist = 0;
    idt[n].type_attributes = 0x8F;
    idt[n].offset_2 = (base >> 16) & 0xFFFF;
    idt[n].offset_3 = (base >> 32) & 0xFFFFFFFF;
    idt[n].zero = 0;
}