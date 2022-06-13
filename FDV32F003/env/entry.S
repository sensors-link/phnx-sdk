// See LICENSE for license details

#ifndef ENTRY_S
#define ENTRY_S


#only save caller registers
.macro TRAP_ENTRY
  addi sp, sp, -16*4

  sw x1,  0*4(sp)
  sw x5,  1*4(sp)
  sw x6,  2*4(sp)
  sw x7,  3*4(sp)
  sw x10, 4*4(sp)
  sw x11, 5*4(sp)
  sw x12, 6*4(sp)
  sw x13, 7*4(sp)
  sw x14, 8*4(sp)
  sw x15, 9*4(sp)

.endm

#restore caller registers
.macro TRAP_EXIT

  lw x1,  0*4(sp)
  lw x5,  1*4(sp)
  lw x6,  2*4(sp)
  lw x7,  3*4(sp)
  lw x10, 4*4(sp)
  lw x11, 5*4(sp)
  lw x12, 6*4(sp)
  lw x13, 7*4(sp)
  lw x14, 8*4(sp)
  lw x15, 9*4(sp)

  addi sp, sp, 16*4
  mret
.endm

  .section      .text.entry
  .align 2
  .global trap_entry
trap_entry:
  TRAP_ENTRY

  csrr a0, mcause
  csrr a1, mepc
  call handle_trap


  csrw mepc, a0
  TRAP_EXIT


.weak handle_trap
handle_trap:
1:
  j 1b

#endif
