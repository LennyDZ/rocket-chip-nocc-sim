# Test the "pass" macro

.section ".text.init"
.globl _start
_start:
    call pass
    j _start