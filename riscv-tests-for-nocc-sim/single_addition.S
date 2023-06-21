## Simple addi test
.section ".text.init"
.globl _start
_start:
    li s0, 0x60000000
    j addnumber

addnumber:
    li t0, 2 # A
    li t1, 3 # B
    li t3, 5 # expected result of A+B
    add t2, t0, t1
    beq t2, t3, success
    call fail

success:
    call pass



