# riscv-tests-for-nocc-sim

This folder contains some test and macros to test the custom simulation flow of the Rocket-chip.

The macros defined in `/util/test-macros.S` allow to send results of the tests to the simulation host.

`make` will generate elf, hex and dump for each file using the riscv compiler (64 bit with 'g' extension (see more [here](https://en.wikichip.org/wiki/risc-v/standard_extensions)))