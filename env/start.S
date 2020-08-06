// See LICENSE for license details.

	.section .init
	.globl _start
	.type _start,@function
/* set all registers to zero */

_start:
	csrrci x0, mstatus, 0x8  //Disable the interrupt globally
.option push
.option norelax
	la gp, __global_pointer$
.option pop
	la sp, _sp

    #csrrsi x0, 0xbfe, 0x8 // Disable I-Cache
2:
	/* Load data section */
	la a0, _data_lma
	la a1, _data
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:
	/* Clear bss section */
	la a0, __bss_start
	la a1, _end
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b
2:

	call _init

#ifdef __riscv_flen
	/* Enable FPU */
	li t0, MSTATUS_FS
	csrs mstatus, t0
	csrw fcsr, x0
#endif

	/* argc = argv = 0 */
	li a0, 0
	li a1, 0
	call main
	tail exit

1:
	j 1b
