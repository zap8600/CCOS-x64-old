.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    movq $stack_top, %rsp
    movq %rbp, %rsp

    call _init

2:  
    jmp 2b
    call kernel_main

    cli
1:	hlt
	jmp 1b
.size _start, . - _start
