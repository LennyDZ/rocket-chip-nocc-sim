#define DRAM_BASE 0x80000000

.section .text.start, "ax", @progbits
.globl _start
_start:
  csrwi 0x7c1, 0 // disable chicken bits
  li s0, DRAM_BASE
  csrr a0, mhartid
  la a1, _dtb
  jr s0

.section .text.hang, "ax", @progbits
.globl _hang
_hang:
  csrwi 0x7c1, 0    // disable chicken bits    chicken bit = bit to used to disable some feature (so here we disable the possibility of diabling stuff apparently)
  csrr a0, mhartid  //read thread id from csr (some mem for cpu infos)
  la a1, _dtb       //load _dtb address
  li t1, 0
  csrwi mie, 1
  li s0, DRAM_BASE
  jr s0

.section .rodata.dtb, "a", @progbits
.globl _dtb
.align 5, 0
_dtb:
.ascii "DTB goes here"
