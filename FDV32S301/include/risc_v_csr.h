/**
 * @file risc_v_csr.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-04-23
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef _RISCV_CSR_H
#define _RISCV_CSR_H

//#ifdef __GNUC__

// csr register define
#define MSTATUS 0x300
#define MISA 0x301
#define MIE 0x304
#define MTVEC 0x305
#define MSCRATCH 0x340
#define MEPC 0x341
#define MCAUSE 0x342
#define MTVAL 0x343
#define MIP 0x344

#define MVENDOR_ID 0xf11
#define MARCH_ID 0xf12
#define MIMP_ID 0xf13
#define MHARD_ID 0xf14
// ext def
#define CUSTOMCSR0 0xbff

// csr bits define
// mstatus
#define MSTATUS_MIE 0x00000008

#define MSTATUS_MPIE 0x00000080

#define MSTATUS_MPP 0x00001800
#define MSTATUS_FS 0x00006000
#define MSTATUS_XS 0x00018000

#define MSTATUS32_SD 0x80000000

// mtvec
#define MTVEC_BASE_ADDR 0xfffffffc
#define MTVEC_MODE 0x00000003
#define MTVEC_MODE_0 0 // def: base
#define MTVEC_MODE_1 1 // base+4*cause  cause=exception code

// mcause
#define MCAUSE_INT 0x80000000
// exception code
#define EXP_M_SOFT_INT 3
#define EXP_M_TIM_INT 7
#define EXP_M_EXT_INT 11

#define MCAUSE_CAUSE 0x7FFFFFFF
#define EXP_INST_ADDR_MIS 0
#define EXP_BREAK 3
#define EXP_ECALL 11

// mie
#define MIE_MEIE (1 << 11) // ext int en
// #define MIE_MTIE       (1<<7)   //tim int en
#define MIE_MSIE (1 << 3) // soft int en

// mip  (only read)
#define MIP_MEIP (1 << 11) // ext int pend flag
#define MIP_MTIP (1 << 7)  // tim int pend flag
#define MIP_MSIP (1 << 3)  // soft intpend flag

// CUSTOMCSR0
#define CUSTOMCSR0_SYSRESETREQ (1 << 4)
#define CUSTOMCSR0_SLEEPDEEPEN (1 << 3)

#define READ_CSR(reg)                                                          \
    ({                                                                         \
        unsigned long __tmp;                                                   \
        asm volatile("csrr %0, " #reg : "=r"(__tmp));                          \
        __tmp;                                                                 \
    })

#define WRITE_CSR(reg, val)                                                    \
    ({                                                                         \
        if (__builtin_constant_p(val) && (unsigned long)(val) < 32)            \
            asm volatile("csrw " #reg ", %0" ::"i"(val));                      \
        else                                                                   \
            asm volatile("csrw " #reg ", %0" ::"r"(val));                      \
    })

#define SWAP_CSR(reg, val)                                                     \
    ({                                                                         \
        unsigned long __tmp;                                                   \
        if (__builtin_constant_p(val) && (unsigned long)(val) < 32)            \
            asm volatile("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "i"(val));   \
        else                                                                   \
            asm volatile("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "r"(val));   \
        __tmp;                                                                 \
    })

#define SET_CSR(reg, bit)                                                      \
    ({                                                                         \
        unsigned long __tmp;                                                   \
        if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32)            \
            asm volatile("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit));   \
        else                                                                   \
            asm volatile("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit));   \
        __tmp;                                                                 \
    })

#define CLEAR_CSR(reg, bit)                                                    \
    ({                                                                         \
        unsigned long __tmp;                                                   \
        if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32)            \
            asm volatile("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit));   \
        else                                                                   \
            asm volatile("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit));   \
        __tmp;                                                                 \
    })

#define EnableGlobleIRQ() SET_CSR(mstatus, MSTATUS_MIE)
#define DisableGlobleIRQ() CLEAR_CSR(mstatus, MSTATUS_MIE)

#define EnableExtIRQ() SET_CSR(mie, MIE_MEIE)
#define DisableExtIRQ() CLEAR_CSR(mie, MIE_MEIE)

#define EnableSoftIRQ() SET_CSR(mie, MIE_MSIE)
#define DisableSoftIRQ() CLEAR_CSR(mie, MIE_MSIE)

// core plic
#define PLIC_BASE_ADDR 0xe0010000

#define PLIC_SetPriority(src, val)                                             \
    {                                                                          \
        *((volatile unsigned int *)(PLIC_BASE_ADDR + (src << 2))) = val;       \
    } // note:val>=1; =0 mask int

#define PLIC_GetPending() *((volatile unsigned int *)(PLIC_BASE_ADDR + 0x100))

#define PLIC_EnableIRQ(src)                                                    \
    *((volatile unsigned int *)(PLIC_BASE_ADDR + 0x200)) |= (1 << src)

#define PLIC_DisableIRQ(src)                                                   \
    *((volatile unsigned int *)(PLIC_BASE_ADDR + 0x200)) &= ~(1 << src)

#define PLIC_SetThreshold(val)                                                 \
    *((volatile unsigned int *)(PLIC_BASE_ADDR + 0x300)) = val // val:0-8

#define PLIC_GetCLAIM()                                                        \
    *((volatile unsigned int *)(PLIC_BASE_ADDR + 0x304)) // int ack
#define PLIC_SetCLAIM(src)                                                     \
    *((volatile unsigned int *)(PLIC_BASE_ADDR + 0x304)) = src // int completion

//#endif
// soft interrupt
#define CLINT_BASE_ADDR 0xe0000000
#define SoftTrigIRQ() (REG32(CLINT_BASE_ADDR) = 1)
#define SoftClrIRQ() (REG32(CLINT_BASE_ADDR) = 0)

#endif
