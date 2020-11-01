ezfe310
=======

The SiFive HiFive1 was just discontinued, making it as good a time as any to introduce this project.

**ezfe310** is a stripped-down, bare-metal library for targeting the SiFive FE310 series of SoCs.
It's intended primarily for educators and hobbyists seeking a simple, comprehensible embedded toolchain.

**ezfe310** is in beta -- you might want to wait until any bugs in the runtime or linker script are ironed out. 
Currently, I *think* it's safe, but I *might* be inadvertantly overwriting the bootloader 
(e.g. the LEDs no longer flash upon reset).

ezfe310 features:
-----------------

* A small, well-documented linker script for the HiFive1 (`scripts/ld/hifive1.h`)
* A small, well-documented runtime for C and assembly programs (`src/runtime/crt0.s`)
* Nearly every register and field in the FE310 exposed to C programs as an lvalue/bitmask (`include/mmio.h`)
* A lightweight, legible library for basic embedded functionality (`ez.h`)
* Example programs (`src/examples`)

Quickstart
----------

0. Grab a copy of the HiFive1 Getting Started Guide and the FE310 Manual at <https://www.sifive.com/boards/hifive1>.
1. Install your favorite RISC-V versions of GCC, GDB, and OpenOCD, and populate the fields 
`RISCV_AS`, `RISCV_GCC`, `RISCV_GDB`, and `RISCV_OPENOCD` in the `Makefile` with the appropriate paths.
2. Run `make compile` to compile `src/main/main.c` (and the runtime).
3. Plug in your HiFive1, confirm that `/dev/ttyUSB1` appears, and run `make upload`. Consult the Getting Started Guide
if something doesn't work.
4. Use your favorite TTY utility (`screen`, `picocom`, `tio`, etc.) to open `/dev/ttyUSB1` at a baud rate of `115200`.

Todo
----

* Verify that the linker script, etc. won't brick anything.
* Reliable UART input.
* Interrupts.
* Builtin LEDs.
* More features from C's standard library.
* Explore GCC features (binary literals, etc.).
* Heap allocation.
* Documentation.
* Testing.
* FE310G001/HiFive Rev B support.

Thanks
------

**ezfe310** draws heavily from the work of others in the RISC-V community.
The following helped provide a foundation for the project (and are good resources in their own right):

<https://wiki.osdev.org/HiFive-1_Bare_Bones>
<https://gitlab.com/Leonhart231/hifive1>
<https://github.com/sifive/freedom-e-sdk/tree/v1_0>
