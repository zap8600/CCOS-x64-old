#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/io.h>

struct regs {
	uintptr_t r15, r14, r13, r12;
	uintptr_t r11, r10, r9, r8;
	uintptr_t rbp, rdi, rsi, rdx, rcx, rbx, rax;

	uintptr_t int_no, err_code;

	uintptr_t rip, cs, rflags, rsp, ss;
};

extern struct regs * _isr0(struct regs*);
extern struct regs * _isr1(struct regs*);
extern struct regs * _isr2(struct regs*);
extern struct regs * _isr3(struct regs*);
extern struct regs * _isr4(struct regs*);
extern struct regs * _isr5(struct regs*);
extern struct regs * _isr6(struct regs*);
extern struct regs * _isr7(struct regs*);
extern struct regs * _isr8(struct regs*);
extern struct regs * _isr9(struct regs*);
extern struct regs * _isr10(struct regs*);
extern struct regs * _isr11(struct regs*);
extern struct regs * _isr12(struct regs*);
extern struct regs * _isr13(struct regs*);
extern struct regs * _isr14(struct regs*);
extern struct regs * _isr15(struct regs*);
extern struct regs * _isr16(struct regs*);
extern struct regs * _isr17(struct regs*);
extern struct regs * _isr18(struct regs*);
extern struct regs * _isr19(struct regs*);
extern struct regs * _isr20(struct regs*);
extern struct regs * _isr21(struct regs*);
extern struct regs * _isr22(struct regs*);
extern struct regs * _isr23(struct regs*);
extern struct regs * _isr24(struct regs*);
extern struct regs * _isr25(struct regs*);
extern struct regs * _isr26(struct regs*);
extern struct regs * _isr27(struct regs*);
extern struct regs * _isr28(struct regs*);
extern struct regs * _isr29(struct regs*);
extern struct regs * _isr30(struct regs*);
extern struct regs * _isr31(struct regs*);extern struct regs * _irq0(struct regs*);
extern struct regs * _irq1(struct regs*);
extern struct regs * _irq2(struct regs*);
extern struct regs * _irq3(struct regs*);
extern struct regs * _irq4(struct regs*);
extern struct regs * _irq5(struct regs*);
extern struct regs * _irq6(struct regs*);
extern struct regs * _irq7(struct regs*);
extern struct regs * _irq8(struct regs*);
extern struct regs * _irq9(struct regs*);
extern struct regs * _irq10(struct regs*);
extern struct regs * _irq11(struct regs*);
extern struct regs * _irq12(struct regs*);
extern struct regs * _irq13(struct regs*);
extern struct regs * _irq14(struct regs*);
extern struct regs * _irq15(struct regs*);


typedef struct regs * (*interrupt_handler_t)(struct regs *);

typedef struct
{
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;
   uint8_t  ist;
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;
   uint32_t zero;
} __attribute__((packed)) idt_entry_t;

struct idt_pointer
{
   uint16_t limit;
   uintptr_t base;
} __attribute__((packed));

typedef struct {
	uintptr_t r15, r14, r13, r12;
	uintptr_t r11, r10, r9, r8;
	uintptr_t rbp, rdi, rsi, rdx, rcx, rbx, rax;

	uintptr_t int_no, err_code;

	uintptr_t rip, cs, rflags, rsp, ss;
} registers_t;

typedef int (*irq_handler_chain_t) (struct regs *);

void isr_handler(registers_t *r);
void irq_handler(registers_t *r);
void init_ints();
void idt_set_gate(int n, interrupt_handler_t handler);
void PIC_sendEOI(unsigned char irq);
void PIC_remap(int offset1, int offset2);
void irq_install_handler(size_t irq, irq_handler_chain_t handler, const char * desc);