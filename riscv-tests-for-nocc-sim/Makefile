default: all


base_dir = $(abspath ..)
linkFile = ./util/link-p.ld
elf-gcc = riscv64-unknown-elf-gcc
elf-dump = riscv64-unknown-elf-objdump -d
gcc-flags = -march=rv64g -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles
TFLAGS = -T$(linkFile)
generated_hex = generated_hex
generated_dump = generated_dump
generated_elf = generated_elf

tests = simple_multithread single_addition failingTest passingTest mtmm

all: $(tests)

%: %.S
	mkdir $(generated_hex) -p
	mkdir $(generated_dump) -p
	mkdir $(generated_elf) -p
	$(elf-gcc) $(gcc-flags) $<  ./util/test-macros.S -o ./$(generated_elf)/$@.elf $(TFLAGS)
	elf2hex 8 $$((2 << 10)) ./$(generated_elf)/$@.elf $$((0x80000000)) > ./$(generated_hex)/$@.hex
	$(elf-dump) ./$(generated_elf)/$@.elf > $(generated_dump)/$@.dump



mtmm:
	$(elf-gcc) $(gcc-flags) ./util/test-macros.S ./mt-mm/mt-mm.c ./mt-mm/mt-mm.S -o ./$(generated_elf)/mt-mm.elf -I/util -I/mt-mm $(TFLAGS)
	elf2hex 8 $$((2 << 14)) $(generated_elf)/mt-mm.elf $$((0x80000000)) > $(generated_hex)/mt-mm.hex
	$(elf-dump) ./$(generated_elf)/mt-mm.elf > $(generated_dump)/$@.dump

clean :
	rm -rf *.hex *.elf *.dump $(generated_hex) $(generated_dump) $(generated_elf)
	

# 