/**
 * @file   init.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */
#include <stdint.h>
#include <stdio.h>
#include "phnx02.h"

extern unsigned int SystemCoreClock;

__attribute__((weak)) void MSOFT_IntHandler(void){};
// __attribute__((weak)) void MTIM_IntHandler(void){};
__attribute__((weak)) void MEXP_Handler(void){};
__attribute__((weak)) void NMI_Handler(void){};

__attribute__((weak)) void PMU_IrqHandler(void){};
__attribute__((weak)) void LPT_IrqHandler(void){};
__attribute__((weak)) void TIMER1_IrqHandler(void){};
__attribute__((weak)) void TIMER2_IrqHandler(void){};
__attribute__((weak)) void TIMER3_IrqHandler(void){};
__attribute__((weak)) void TIMER4_IrqHandler(void){};
__attribute__((weak)) void UART1_IrqHandler(void){};
__attribute__((weak)) void UART2_IrqHandler(void){};
__attribute__((weak)) void SPI_IrqHandler(void){};
__attribute__((weak)) void ANAC_IrqHandler(void){};
__attribute__((weak)) void EFC_IrqHandler(void){};
__attribute__((weak)) void IOM_IrqHandler(void){};
__attribute__((weak)) void I2C_IrqHandler(void){};
__attribute__((weak)) void RTC_IrqHandler(void){};
__attribute__((weak)) void TWC_IrqHandler(void){};
__attribute__((weak)) void LPU_IrqHandler(void){};

void MEXT_IntHandler(void) {
    u32 src;
    src = PLIC_GetCLAIM();
    switch (src) {
    case (PMU_IRQn): {
        PMU_IrqHandler();
        break;
    }
    case (LPT_IRQn): {
        LPT_IrqHandler();
        break;
    }
    case (TIMER1_IRQn): {
        TIMER1_IrqHandler();
        break;
    }
    case (TIMER2_IRQn): {
        TIMER2_IrqHandler();
        break;
    }
    case (TIMER3_IRQn): {
        TIMER3_IrqHandler();
        break;
    }
    case (TIMER4_IRQn): {
        TIMER4_IrqHandler();
        break;
    }
    case (UART1_IRQn): {
        UART1_IrqHandler();
        break;
    }
    case (UART2_IRQn): {
        UART2_IrqHandler();
        break;
    }
    case (SPI_IRQn): {
        SPI_IrqHandler();
        break;
    }
    case (ANAC_IRQn): {
        ANAC_IrqHandler();
        break;
    }
    case (EFC_IRQn): {
        EFC_IrqHandler();
        break;
    }
    case (IOM_IRQn): {
        IOM_IrqHandler();
        break;
    }
    case (I2C_IRQn): {
        I2C_IrqHandler();
        break;
    }
    case (RTC_IRQn): {
        RTC_IrqHandler();
        break;
    }
    case (TWC_IRQn): {
        TWC_IrqHandler();
        break;
    }
    case (LPU_IRQn): {
        LPU_IrqHandler();
        break;
    }
    default:
        break;
    }
    PLIC_SetCLAIM(src);
};

unsigned int handle_trap(unsigned int mcause, unsigned int epc) {
    // External Machine-Level interrupt from PLIC
    if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == EXP_M_EXT_INT)) {
        MEXT_IntHandler();
    } else if ((mcause & MCAUSE_INT) &&
               ((mcause & MCAUSE_CAUSE) == EXP_M_SOFT_INT)) {
        MSOFT_IntHandler();
        // } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) ==
        // EXP_M_TIM_INT)){
        //     MTIM_IntHandler();
    } else if (mcause == 0x1e) {
        NMI_Handler();
    } else {
        MEXP_Handler();
        while (1) {
        };
    }
    return epc;
}
