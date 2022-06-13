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
 * @brief 系统时钟初始
 *
 */
void SystemInit(void)
{

#if (SYSC_CLK_SRC_SEL == F_LRC)
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
	GPIO_PinSelect(GPIO_PIN0 | GPIO_PIN1, PIN_FUNC_1);
	UART_Init(UART_MODE_10B_ASYNC, 9600);
#endif
	WRITE_CSR(mtvec, &trap_entry);
	EnableGlobleIRQ();
	EnableExtIRQ();
}

void SystemCoreClockUpdate(void)
{
	unsigned int dwTmp;
	int clkSrc = (SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_SYS_CLK_SEL);
	if (clkSrc == SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC)
		SystemCoreClock = 8000;
}
