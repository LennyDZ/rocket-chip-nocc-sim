.section .data
.section .text
.globl fail
.type fail,@function
fail:
    li s0, 0x60000000
    li t4, 2
    sw t4, 0(s0)
    j fail

.section .data
.section .text
.globl pass
.type pass,@function
pass:
    li s0, 0x60000000
    li t4, 1
    sw t4, 0(s0)
    j pass