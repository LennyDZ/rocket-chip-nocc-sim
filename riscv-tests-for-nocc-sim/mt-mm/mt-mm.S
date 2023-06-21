##Multithread matrix multiplication test

#define sp_addr 0x82000000
#define N_OF_CORES 2

.section .data
ready:
  .word 0
nCoreComplete:
  .word 0

.section ".text.init"
.globl _start
_start:
    csrr a0, mhartid
    li a1, N_OF_CORES //set total number of cores here

    //set sp with shift for each core
    #define STKSHIFT 17
    add sp, a0, 1
    sll sp, sp, STKSHIFT
    add sp, sp, tp
    sll a2, a0, STKSHIFT
    add   tp, tp, a2
    li t0, sp_addr
    add sp, sp, t0
    j thread_entry


idle:
  j idle

.globl complete
complete:
  la t0, nCoreComplete
  li t1, 1        //t5 = 1
  amoadd.w t2, t1, 0(t0)
  li t3, N_OF_CORES
  addi t3, t3, -1
  beq t2, t3, check
  j idle

check:
  call verify

