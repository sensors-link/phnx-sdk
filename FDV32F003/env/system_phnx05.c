/**
 * @file system_phnx05.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-16
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "sysc.h"
#include "efc.h"
#include "uart.h"
#include "iom.h"

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
	GPIO_PinSelect(GPIO_PIN0 | GPIO_PIN1, PIN_FUNC_1);
	UART_Init(UART_MODE_10B_ASYNC, _BAUD_FREQ);
#endif
	WRITE_CSR(mtvec, &trap_entry);
	EnableGlobleIRQ();
	EnableExtIRQ();
}

void SystemCoreClockUpdate(void)
{
	int clkSrc = (SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_SYS_CLK_SEL);
	if (clkSrc == SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC)
		SystemCoreClock = 8000;
	else
		SystemCoreClock = 8000000;
}
