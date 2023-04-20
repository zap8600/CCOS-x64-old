.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
.global stack_top
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    movq $stack_top, %rsp
    
    call kernel_main
    
    cli
1:  hlt
    jmp 1b
.size _start, . - _start