/**
 * @file system_phnx02.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-03-16
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "sysc.h"
#include "anac.h"
#include "efc.h"
#include "uart.h"

unsigned int SystemCoreClock = 8000000;

#ifndef _BAUD_FREQ
#define _BAUD_FREQ 9600
#endif

extern void trap_entry();

/**
 * @brief 系统时钟初始化
 *
 */
void SystemInit(void) {
#if (SYSC_CLK_SRC_SEL == F_XTH)
    SYSC_CLKENCFG_REG |= SYSC_CLKENCFG_ANAC;
    ANAC_WPROT_REG = ANAC_WPROT_V0;
    ANAC_WPROT_REG = ANAC_WPROT_V1;
    ANAC_CLK_CFG_REG |= ANAC_CLK_CFG_XTH_EN;
    for (i = 10000; i > 0; i--)
        ;
#if (XTAL == 32000000)
    EFC_WPT_REG = EFC_WPT_VALUE_0;
    EFC_WPT_REG = EFC_WPT_VALUE_1;
    EFC_CR_REG |= EFC_CR_NRDDLY;
#endif
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V0;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V1;
    SYSC_CLKCTRCFG_REG &=
        ~(SYSC_CLKCTRCFG_APB_CLK_DIV | SYSC_CLKCTRCFG_AHB_CLK_DIV |
          SYSC_CLKCTRCFG_SYS_CLK_SEL);
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V0;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V1;
    SYSC_CLKCTRCFG_REG |= (((SYSC_APB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) |
                           ((SYSC_AHB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) |
                           SYSC_CLKCTRCFG_SYS_CLK_SEL_XTH);
#elif (SYSC_CLK_SRC_SEL == F_XTL)
    SYSC_CLKENCFG_REG |= SYSC_CLKENCFG_IOM | SYSC_CLKENCFG_ANAC;
    IOM->GPIO_PU &= ~(3 << 2);
    IOM->GPIO_ADS |= (3 << 2);
    ANAC_WPROT_REG = ANAC_WPROT_V0;
    ANAC_WPROT_REG = ANAC_WPROT_V1;
    ANAC_CLK_CFG_REG |= ANAC_CLK_CFG_XTL_EN;
    for (i = 10000; i > 0; i--)
        ;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V0;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V1;
    SYSC_CLKCTRCFG_REG &=
        ~(SYSC_CLKCTRCFG_APB_CLK_DIV | SYSC_CLKCTRCFG_AHB_CLK_DIV |
          SYSC_CLKCTRCFG_SYS_CLK_SEL);
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V0;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V1;
    SYSC_CLKCTRCFG_REG |= (((SYSC_APB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) |
                           ((SYSC_AHB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) |
                           SYSC_CLKCTRCFG_SYS_CLK_SEL_XTL);
#elif (SYSC_CLK_SRC_SEL == F_LRC)
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V0;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V1;
    SYSC_CLKCTRCFG_REG &=
        ~(SYSC_CLKCTRCFG_APB_CLK_DIV | SYSC_CLKCTRCFG_AHB_CLK_DIV |
          SYSC_CLKCTRCFG_SYS_CLK_SEL);
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V0;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V1;
    SYSC_CLKCTRCFG_REG |= (((SYSC_APB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) |
                           ((SYSC_AHB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) |
                           SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC);
#else
    SYSC_CLKENCFG_REG |= SYSC_CLKENCFG_ANAC;
    ANAC_WPROT_REG = ANAC_WPROT_V0;
    ANAC_WPROT_REG = ANAC_WPROT_V1;
    ANAC->CLK_CFG &= ~ANAC_CLK_CFG_HRC_FSEL;
    ANAC_WPROT_REG = ANAC_WPROT_V0;
    ANAC_WPROT_REG = ANAC_WPROT_V1;
    ANAC->CLK_CFG |= (SYSC_CLK_SRC_SEL) << 2;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V0;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V1;
    SYSC_CLKCTRCFG_REG &=
        ~(SYSC_CLKCTRCFG_APB_CLK_DIV | SYSC_CLKCTRCFG_AHB_CLK_DIV |
          SYSC_CLKCTRCFG_SYS_CLK_SEL);
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V0;
    SYSC_WRPROCFG_REG = SYSC_WRPROCFG_V1;
    SYSC_CLKCTRCFG_REG |= (((SYSC_APB_DIV) << SYSC_CLKCTRCFG_APB_CLK_DIV_pos) |
                           ((SYSC_AHB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) |
                           SYSC_CLKCTRCFG_SYS_CLK_SEL_HRC);
#endif
    SystemCoreClockUpdate();
#ifdef _DEBUG
#if defined(_UART2)
    UART_DeInit(UART2);
    UART_Init(UART2, UART2_PORT_P02_P03, UART_MODE_10B_ASYNC, _BAUD_FREQ);
#else
    UART_DeInit(UART1);
    UART_Init(UART1, UART1_PORT_P00_P01, UART_MODE_10B_ASYNC, _BAUD_FREQ);
#endif
#endif
    WRITE_CSR(mtvec, &trap_entry);
    EnableGlobleIRQ();
    EnableExtIRQ();
}

void SystemCoreClockUpdate(void) {
    unsigned int dwTmp;
    int clkSrc = (SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_SYS_CLK_SEL);
    if (clkSrc == SYSC_CLKCTRCFG_SYS_CLK_SEL_XTH)
        SystemCoreClock = XTH_FREQ;
    else if (clkSrc == SYSC_CLKCTRCFG_SYS_CLK_SEL_XTL)
        SystemCoreClock = XTL_FREQ;
    else if (clkSrc == SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC)
        SystemCoreClock = 8000;
    else {
        dwTmp = ANAC->CLK_CFG & ANAC_CLK_CFG_HRC_FSEL;
        if ((dwTmp >> 2) == 1)
            SystemCoreClock = 1000000;
        else if ((dwTmp >> 2) == 2)
            SystemCoreClock = 2000000;
        else if ((dwTmp >> 2) == 3)
            SystemCoreClock = 4000000;
        else if ((dwTmp >> 2) == 4)
            SystemCoreClock = 8000000;
        else if ((dwTmp >> 2) == 5)
            SystemCoreClock = 16000000;
        //	else if((dwTmp >> 2) == 6)
        //		SystemCoreClock= 24000000;
        // else if((dwTmp >> 2) == 7)
        // 	SystemCoreClock= 32000000;
    }
}
