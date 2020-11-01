# Identify the values declared in our linker script.
.extern _data_start
.extern _data_lma
.extern _data_end

.extern _bss_start
.extern _bss_end

.extern _heap_start
.extern _heap_end

.extern _stack_size
.extern _sp_init

.extern __global_pointer$

.extern main
.extern exit

.global _start
_start:

# Make debugging easier by indicating that backtraces should stop here.
.cfi_startproc
.cfi_undefined ra

# Set up the global and stack pointers.
.option push
.option norelax
	la gp, __global_pointer$
.option pop

	la sp, _sp_init
	
# Zero the bss.
	la t0, _bss_start
	la t1, _bss_end

zero_bss_loop:
	sw zero, (t0)
	addi t0, t0, 4
	bltu t0, t1, zero_bss_loop

# Initialize our data, copying from rom to ram.
	la t0, _data_lma
	la t1, _data_start
	la t2, _data_end
	bgeu t1, t2, init_data_finished # no data to init

init_data_loop:
	lw t3, (t0)	
	sw t3, (t1)
	addi t0, t0, 4
	addi t1, t1, 4
	bltu t1, t2, init_data_loop

init_data_finished:

# Set up a stack frame for `main`.
	addi sp, sp, -16
	sw ra, 8(sp) # actual storage location within frame is arbitrary

# We shouldn't be using `main`'s arguments, but we'll set them anyway.
	li a0, 0 # argc = 0
	li a1, 0 # argv = NULL

# Finally, call `main`.
	call main
	call exit
extra_dead_loop:
	j extra_dead_loop
.cfi_endproc
