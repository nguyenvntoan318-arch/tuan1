.syntax unified
.cpu cortex-m3
.thumb

.global _estack
.global Reset_Handler

.extern main

/*================ Vector Table ================*/
.section .isr_vector,"a",%progbits

.word _estack
.word Reset_Handler

/* Các ngắt không sử dụng */
.rept 14
.word 0
.endr

/*================ Code ================*/
.section .text
.thumb_func

Reset_Handler:
    bl main

Loop:
    b Loop
