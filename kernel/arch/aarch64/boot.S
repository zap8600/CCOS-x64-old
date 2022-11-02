.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
.globl stack_top
stack_top:

.section text
.globl _start
.type _start @function
_start:
    ldr x30, =stack_top
    mov sp, x30
    bl kmain
hang:
    b hang
