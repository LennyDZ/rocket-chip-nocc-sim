// In this implementation, cores all start independently. And the last core to finish handle the final instructions while other cores goes to idle.
.section .data
    coreFinishCount:
        .word 0
    coreResult:
        .word 0, 0

.section ".text.init"
.globl _start
_start:
    li s0, 0x60000000
    j multithread

multithread:
    addi t0, zero, 5
    csrr t1, mhartid
    slli t1, t1, 2
    la t2, coreResult
    add t2, t2, t1
    la t3, coreFinishCount
    li t5, 1        //t5 = 1
    sw t0, 0(t2)    //store t0 in coreResult
    amoadd.w t4, t5, 0(t3)
    beq t4, zero, idle //check if eq to 0, if yes wait other core
    beq t4, t5, join //check if eq to 1 if yes join the results
    j fail

join:
    la t0, coreResult 
    la t1, coreResult
    addi t1, t1, 4  
    lw t0, 0(t0) //t0 is coreResult[0]
    lw t1, 0(t1) //t1 is coreResult[1]
    add t2, t0, t1 //add results of the cores
    li t3, 10
    beq t2, t3, pass //5 + 5 (t2) should be 10
    j fail

idle:
    j idle
