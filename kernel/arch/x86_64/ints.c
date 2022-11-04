#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/ints.h>
#include <kernel/dbg.h>
#include <kernel/stdio.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI		0x20		/* End-of-interrupt command code */

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

static struct idt_pointer idtp;
static idt_entry_t idt[256];

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t *r)
{
    printf("Received ISR. The ISR number is %d. ", r->int_no);
    printf("The exception is %s.\n", exception_messages[r->int_no]);
}

void irq_handler(registers_t *r)
{
    PIC_sendEOI(r->int_no);
}

void init_ints()
{
    idtp.limit = sizeof(idt);
    idtp.base  = (uintptr_t)&idt;
    idt_set_gate(0, _isr0);
    idt_set_gate(1, _isr1);
    idt_set_gate(2, _isr2);
    idt_set_gate(3, _isr3);
    idt_set_gate(4, _isr4);
    idt_set_gate(5, _isr5);
    idt_set_gate(6, _isr6);
    idt_set_gate(7, _isr7);
    idt_set_gate(8, _isr8);
    idt_set_gate(9, _isr9);
    idt_set_gate(10, _isr10);
    idt_set_gate(11, _isr11);
    idt_set_gate(12, _isr12);
    idt_set_gate(13, _isr13);
    idt_set_gate(14, _isr14);
    idt_set_gate(15, _isr15);
    idt_set_gate(16, _isr16);
    idt_set_gate(17, _isr17);
    idt_set_gate(18, _isr18);
    idt_set_gate(19, _isr19);
    idt_set_gate(20, _isr20);
    idt_set_gate(21, _isr21);
    idt_set_gate(22, _isr22);
    idt_set_gate(23, _isr23);
    idt_set_gate(24, _isr24);
    idt_set_gate(25, _isr25);
    idt_set_gate(26, _isr26);
    idt_set_gate(27, _isr27);
    idt_set_gate(28, _isr28);
    idt_set_gate(29, _isr29);
    idt_set_gate(30, _isr30);
    idt_set_gate(31, _isr31);

    PIC_remap(0x20, 0x28);

    idt_set_gate(32, _irq0);
	idt_set_gate(33, _irq1);
	idt_set_gate(34, _irq2);
	idt_set_gate(35, _irq3);
	idt_set_gate(36, _irq4);
	idt_set_gate(37, _irq5);
	idt_set_gate(38, _irq6);
	idt_set_gate(39, _irq7);
	idt_set_gate(40, _irq8);
	idt_set_gate(41, _irq9);
	idt_set_gate(42, _irq10);
	idt_set_gate(43, _irq11);
	idt_set_gate(44, _irq12);
	idt_set_gate(45, _irq13);
	idt_set_gate(46, _irq14);
	idt_set_gate(47, _irq15);

    asm volatile (
		"lidt %0"
		: : "m"(idtp)
	);
}

void idt_set_gate(int n, interrupt_handler_t handler)
{
    uintptr_t base = (uintptr_t)handler;
    idt[n].offset_1 = base & 0xFFFF;
    idt[n].selector = 0x28;
    idt[n].ist = 0;
    idt[n].type_attributes = 0x8E;
    idt[n].offset_2 = (base >> 16) & 0xFFFF;
    idt[n].offset_3 = (base >> 32) & 0xFFFFFFFF;
    idt[n].zero = 0;
}

void PIC_sendEOI(unsigned char irq)
{
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
 
	outb(PIC1_COMMAND,PIC_EOI);
}

void PIC_remap(int offset1, int offset2)
{
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}