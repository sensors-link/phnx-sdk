/**
 * @file system_phnx04.c
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
void SystemInit(void)
{
#if (SYSC_CLK_SRC_SEL == F_LRC)
	SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
	SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
	SYSC->CLKCTRCFG &= ~(SYSC_CLKCTRCFG_APB_CLK_DIV | SYSC_CLKCTRCFG_AHB_CLK_DIV | SYSC_CLKCTRCFG_SYS_CLK_SEL);
	SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
	SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
	SYSC->CLKCTRCFG |= (((SYSC_APB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) |
						((SYSC_AHB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) | SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC);
#else
	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC;
	u32 tmp;
	tmp = ANAC->CLK_CFG;
	tmp &= ~ANAC_CLK_CFG_HRC_FSEL;
	tmp |= (SYSC_CLK_SRC_SEL) << 2;
	ANAC->WPROT	   = ANAC_WPROT_V0;
	ANAC->WPROT	   = ANAC_WPROT_V1;
	ANAC->CLK_CFG  = tmp;
	SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
	SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
	SYSC->CLKCTRCFG &= ~(SYSC_CLKCTRCFG_APB_CLK_DIV | SYSC_CLKCTRCFG_AHB_CLK_DIV | SYSC_CLKCTRCFG_SYS_CLK_SEL);
	SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
	SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
	SYSC->CLKCTRCFG |= (((SYSC_APB_DIV) << SYSC_CLKCTRCFG_APB_CLK_DIV_pos) |
						((SYSC_AHB_DIV) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) | SYSC_CLKCTRCFG_SYS_CLK_SEL_HRC);
#endif
	SystemCoreClockUpdate();
#ifdef _DEBUG
#if defined(_UART2)
	UART_DeInit(UART2);
	UART_Init(UART2, UART2_PORT_P04_P05, UART_MODE_10B_ASYNC, _BAUD_FREQ);
#else
	UART_DeInit(UART1);
	UART_Init(UART1, UART1_PORT_P18_P19, UART_MODE_10B_ASYNC, _BAUD_FREQ);
#endif
#endif
	WRITE_CSR(mtvec, &trap_entry);
	EnableGlobleIRQ();
	EnableExtIRQ();
}

void SystemCoreClockUpdate(void)
{
	unsigned int dwTmp;
	int			 clkSrc = (SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_SYS_CLK_SEL);

	if (clkSrc == SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC)
		SystemCoreClock = 8000;
	else
	{
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
	}
}
