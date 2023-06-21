# Rocket chip with custom simulation flow

This repo contains a modified version of the Rocket-Chip repo that allows to run simulation with a different flow that doesn't rely on FESVR/JTAG.

All credits for the orginial project goes to it ([Rocket-Chip](https://github.com/chipsalliance/rocket-chip/tree/master)), And [this paper](https://www2.eecs.berkeley.edu/Pubs/TechRpts/2016/EECS-2016-17.html)

Using this repo has the same requirement as the original repo (mostly having riscv-toolchain installed)

The original README for the Rocket-chip has been moved to `/docs/rocket-chip_readme/README.md` 

## Compile and run test :

You can compile the chip using the same process as in the Rocket-Chip repo (using `Config=... make(-debug)`)

To run a test file, you can use 
```
./emulator-...-config +FILEMAME=/path/to/test/file -m <max-cycles> -v <output-file>
```
Test files must be compiled and transform to Hex format (with a width of 8).
You can use optionnal args `-m` to set max-cylces and `-v` to generate VCD waves into a file.

Some Tests are available under `riscv-tests-for-nocc-sim`.

## Implementation details 

The main goal was to remove as much as possible the usage of C++ code for the simulation. So we removed the usage of most of those scripts.
The only C++ file left is the `emulator_nodtm.cc` which controls the verilator simulation and which functions as been reduced to toggling the clock and parsing the few available arguments. This simulation wrapper replace the original `emulator.cc`file.

We load the test program directly in the allocated memory for the chip's DRAM. We snoop for memory writes to a specific location to controls the simulation's ending (see ``config.behav_srams.v`` in the generated file in emulator dir).

Finally, we modify the bootrom to jump to the DRAM base instead of waiting for DTM interrupts, we hardcoded the output of the DTM module to disable it. And we remove all dependencies to C++ files in the Makefile.