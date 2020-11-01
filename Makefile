RISCV_AS := ~/.local/bin/riscv64-unknown-elf-as
RISCV_GCC := ~/.local/bin/riscv64-unknown-elf-gcc 
RISCV_GDB := ~/.local/bin/riscv64-unknown-elf-gdb
RISCV_OPENOCD := ~/.local/bin/openocd

RISCV_ARCH := rv32imac
RISCV_ABI  := ilp32
RISCV_XLEN := 32

ASFLAGS += -o build/crt0.o
ASFLAGS += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI)

ASMSRCS += src/runtime/crt0.s

LINKERSCRIPT = scripts/ld/hifive1.lds

CSRCS   += src/main/main.c

PPFLAGS += -include include/ez.h

CFLAGS += -o build/program.img
CFLAGS += -std=c99
CFLAGS += -Os # -g -Og
CFLAGS += -ffreestanding -fno-common
CFLAGS += -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=medany

LDFLAGS += -T $(LINKERSCRIPT)
LDFLAGS += -nostdlib

.PHONY: compile
compile: crt0.o
	$(RISCV_GCC) $(PPFLAGS) $(CFLAGS) $(CSRCS) $(LDFLAGS)

crt0.o: src/runtime/crt0.s
	mkdir -p build
	$(RISCV_AS) $(ASFLAGS) $(ASMSRCS)

OPENOCDCFG := scripts/openocd/hifive1.cfg

GDB_PORT = 3333

GDB_UPLOAD_CMDS += -ex "set remotetimeout 240"
GDB_UPLOAD_CMDS += -ex "target extended-remote localhost:$(GDB_PORT)"
GDB_UPLOAD_CMDS += -ex "monitor reset halt"
GDB_UPLOAD_CMDS += -ex "monitor flash protect 0 64 last off"
GDB_UPLOAD_CMDS += -ex "load"
GDB_UPLOAD_CMDS += -ex "monitor resume"
GDB_UPLOAD_CMDS += -ex "monitor shutdown"
GDB_UPLOAD_CMDS += -ex "quit"

.PHONY: upload
upload:
	$(RISCV_OPENOCD) -f $(OPENOCDCFG) & \
	$(RISCV_GDB) build/program.img --batch $(GDB_UPLOAD_CMDS)

.PHONY: clean
clean:
	rm build/crt0.o
	rm build/program.img
	rmdir build

