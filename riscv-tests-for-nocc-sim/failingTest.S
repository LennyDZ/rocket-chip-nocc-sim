##This test is meant to fail in order to test the failure macro

.section ".text.init"
.globl _start
_start:
    call fail
    j _start