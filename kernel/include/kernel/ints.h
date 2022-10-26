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
extern struct regs * _isr31(struct regs*);

typedef struct regs * (*interrupt_handler_t)(struct regs *);

typedef struct {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint32_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint8_t zero;            // reserved
} __attribute__((packed)) idt_entry_t;

struct idt_pointer
{
   uint16_t limit;
   uintptr_t base;
} __attribute__((packed));

void isr_handler();
void init_idt();