/**
 * @file sys.h
 * @author wyd
 * @brief
 * @version 0.1
 * @date 2021-07-16
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __SYSC_H__
#define __SYSC_H__

#include "phnx04.h"

// SYSC_CLKCTRCFG
#define SYSC_CLKCTRCFG_DSW_WKUP_DLY BITS(24, 31)
#define SYSC_CLKCTRCFG_APB_CLK_DIV	BITS(16, 22)
#define SYSC_CLKCTRCFG_AHB_CLK_DIV	BITS(8, 14)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL	BIT(4)
#define SYSC_CLKCTRCFG_SYS_DEDLY_EN BIT(0)

#define SYSC_CLKCTRCFG_DSW_WKUP_DLY_pos (24) // T=(x+3)/src_clk  def:0x1A(3us)
#define SYSC_CLKCTRCFG_APB_CLK_DIV_pos	(16) // 0-0x7f:div1-128
#define SYSC_CLKCTRCFG_AHB_CLK_DIV_pos	(8)

#define SYSC_CLKCTRCFG_SYS_CLK_SEL_HRC (0 << 4)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC (1 << 4)

// SYSC_WRPROCFG
#define SYSC_WRPROCFG BITS(0, 15)

#define SYSC_WRPROCFG_V0 0x5a5a
#define SYSC_WRPROCFG_V1 0xa5a5
#define SYSC_WPT_UNLOCK()                                                                                              \
	{                                                                                                                  \
		SYSC->WRPROCFG = SYSC_WRPROCFG_V0;                                                                             \
		SYSC->WRPROCFG = SYSC_WRPROCFG_V1;                                                                             \
	}

// SYSC_CLKENCFG
#define SYSC_CLKENCFG_TWC_MRCK BIT(21)
#define SYSC_CLKENCFG_TWC	   BIT(19)
#define SYSC_CLKENCFG_LPTIM	   BIT(15)
#define SYSC_CLKENCFG_WDT	   BIT(14)
#define SYSC_CLKENCFG_PMU	   BIT(13)
#define SYSC_CLKENCFG_ANAC	   BIT(12)
#define SYSC_CLKENCFG_DCLK_HCK BIT(11)
#define SYSC_CLKENCFG_IOM	   BIT(10)
#define SYSC_CLKENCFG_TIM2_CNT BIT(7)
#define SYSC_CLKENCFG_TIM1_CNT BIT(6)
#define SYSC_CLKENCFG_TIM_PCK  BIT(5)
#define SYSC_CLKENCFG_UART2	   BIT(4)
#define SYSC_CLKENCFG_UART1	   BIT(3)
#define SYSC_CLKENCFG_SPI	   BIT(2)
#define SYSC_CLKENCFG_APB	   BIT(0)

// SYSC_MSFTRSTCFG
#define SYSC_MSFTRSTCFG_TWC	  BIT(9)
#define SYSC_MSFTRSTCFG_ANAC  BIT(7)
#define SYSC_MSFTRSTCFG_HCLK  BIT(6)
#define SYSC_MSFTRSTCFG_TIMER BIT(4)
#define SYSC_MSFTRSTCFG_UART2 BIT(3)
#define SYSC_MSFTRSTCFG_UART1 BIT(2)
#define SYSC_MSFTRSTCFG_SPI	  BIT(1)

// SYSC_TESTCKSEL
#define SYSC_TESTCKSEL_EN		   BIT(7)
#define SYSC_TESTCKSEL_CLK_DIV	   BITS(0, 6)
#define SYSC_TESTCKSEL_CLK_DIV_pos (0) // div(x+1)*2

// SYSC_ANCLKDIV
#define SYSC_ANAC_500K_CLK_DIV		BITS(4, 8)
#define SYSC_ANAC_ANAC_SCLK_DIV		BITS(0, 3)
#define SYSC_ANAC_500K_CLK_DIV_pos	(4) // 0-1f:div(x+1)
#define SYSC_ANAC_ANAC_SCLK_DIV_pos (0) // 0-0f:div(x+1)*2

// SYSC_TIMCLKDIV
#define SYSC_TIM1CLKDIV		BITS(0, 7)
#define SYSC_TIM1CLKDIV_pos (0) // 0-ff:div(x+1)

#define SYSC_TIM2CLKDIV		BITS(8, 15)
#define SYSC_TIM2CLKDIV_pos (8) // 0-ff:div(x+1)

#define SYSC_GetAPBCLK()                                                                                               \
	(SystemCoreClock / (((SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_APB_CLK_DIV) >> SYSC_CLKCTRCFG_APB_CLK_DIV_pos) + 1) /      \
	 (((SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_AHB_CLK_DIV) >> SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) + 1))
#define SYSC_GetAHBCLK()                                                                                               \
	(SystemCoreClock / (((SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_AHB_CLK_DIV) >> SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) + 1))

// extend define
#define SYSC_CLK_SRC_HRC (0)
#define SYSC_CLK_SRC_LRC (1)

typedef enum _RST_M
{
	PRST_SPI   = (1 << 1),
	PRST_UART1 = (1 << 2),
	PRST_UART2 = (1 << 3),
	PRST_TIMER = (1 << 4),
	PRST_HCLK  = (1 << 6),
	PRST_ANAC  = (1 << 7),
	PRST_TWC   = (1 << 9),
} eRSTP_Type;

typedef enum _CLK_EN
{
	PCLK_EN_TWC_MRCKEN	 = (1 << 21),
	PCLK_EN_TWC_PCKEN	 = (1 << 19),
	PCLK_EN_LPTIM_PCKEN	 = (1 << 15),
	PCLK_EN_LPWDT_PCKEN	 = (1 << 14),
	PCLK_EN_PMU_PCKEN	 = (1 << 13),
	PCLK_EN_ANAC_PCKEN	 = (1 << 12),
	PCLK_EN_DCLK_HCKEN	 = (1 << 11),
	PCLK_EN_IOM_PCKEN	 = (1 << 10),
	PCLK_EN_TIMER2_PCKEN = (1 << 7),
	PCLK_EN_TIMER1_PCKEN = (1 << 6),
	PCLK_EN_TIMER_PCKEN	 = (1 << 5),
	PCLK_EN_UART2_PCKEN	 = (1 << 4),
	PCLK_EN_UART1_PCKEN	 = (1 << 3),
	PCLK_EN_SPI_PCKEN	 = (1 << 2),
	PCLK_EN_APB_CKEN	 = (1 << 0),
} ePCLKEN_Type;

// extern function declare
void SYSC_SelectClockSource(int clkSrc);
void SYSC_SetAPBCLKDiv(int div);
void SYSC_SetAHBCLKDiv(int div);
void SYSC_ResetPeripher(eRSTP_Type module);
void SYSC_PCLKEnable(ePCLKEN_Type perp);
void SYSC_PCLKDisable(ePCLKEN_Type perp);
void SYSC_SetANAC_CLKDiv(int div, int m500kDiv);
void SYSC_SetTimer1ClkDiv(int div);
void SYSC_SetTimer2ClkDiv(int div);
void SYSC_TestClkOutControl(int div, ControlStatus clt);

#endif /*__SYSC_H__*/
