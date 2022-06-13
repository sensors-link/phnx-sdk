/**
 * @file sys.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __SYSC_H__
#define __SYSC_H__

#include "../include/phnx05.h"

/* registers definitions */
#define SYSC_CLKCTRCFG_REG                        REG32((SYSC_BASE) + 0x00U)
#define SYSC_WRPROCFG_REG                         REG32((SYSC_BASE) + 0x04U)
#define SYSC_CLKENCFG_REG                         REG32((SYSC_BASE) + 0x08U)
#define SYSC_MSFTRSTCFG_REG                       REG32((SYSC_BASE) + 0x0cU)

#define SYSC_TESTCKSEL_REG                        REG32((SYSC_BASE) + 0x10U)
#define SYSC_ADCCLKDIV_REG                        REG32((SYSC_BASE) + 0x14U)
#define SYSC_RSTSTS_REG                           REG32((SYSC_BASE) + 0x18U)


// SYSC_CLKCTRCFG
#define SYSC_CLKCTRCFG_DSW_WKUP_DLY               BITS(23, 31)
#define SYSC_CLKCTRCFG_APB_CLK_DIV                BITS(16, 22)
#define SYSC_CLKCTRCFG_REV1                       BIT(15)
#define SYSC_CLKCTRCFG_AHB_CLK_DIV                BITS(8, 14)
#define SYSC_CLKCTRCFG_REV2                       BITS(3, 7)
#define SYSC_CLKCTRCFG_LPWDT_CKEN                 BIT(2)
#define SYSC_CLKCTRCFG_LVDCHIPRSTEN               BIT(1)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL                BIT(0)

#define SYSC_CLKCTRCFG_DSW_WKUP_DLY_pos           (23) // T=(x+3)/src_clk  def:0x10(10us)
#define SYSC_CLKCTRCFG_APB_CLK_DIV_pos            (16) // 0-0x7f:div1-128
#define SYSC_CLKCTRCFG_AHB_CLK_DIV_pos            (8)

#define SYSC_CLKCTRCFG_SYS_CLK_SEL_HRC            (0)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC            (1)

// SYSC_WRPROCFG
#define SYSC_WRPROCFG                             BITS(0, 7)
#define SYSC_WRPROCFG_V0                          (0x5a)
#define SYSC_WRPROCFG_V1                          (0xa5)

#define SYSC_WPT_UNLOCK()                         \
{                                                 \
    SYSC->WRPROCFG = SYSC_WRPROCFG_V0;            \
    SYSC->WRPROCFG = SYSC_WRPROCFG_V1;            \
}

// SYSC_CLKENCFG
#define SYSC_CLKENCFG_ADC_PCKEN                   BIT(15)
#define SYSC_CLKENCFG_LPTIM_CKEN                  BIT(14)
#define SYSC_CLKENCFG_LPTIM_PCKEN                 BIT(13)
#define SYSC_CLKENCFG_LPWDT_PCKEN                 BIT(12)
#define SYSC_CLKENCFG_PMU_PCKEN                   BIT(11)
#define SYSC_CLKENCFG_ANAC_PCKEN                  BIT(10)
#define SYSC_CLKENCFG_DCLK_HCKEN                  BIT(9)
#define SYSC_CLKENCFG_IOM_PCKEN                   BIT(8)
#define SYSC_CLKENCFG_TIMER4_PCKEN                BIT(7)
#define SYSC_CLKENCFG_TIMER3_PCKEN                BIT(6)
#define SYSC_CLKENCFG_TIMER2_PCKEN                BIT(5)
#define SYSC_CLKENCFG_TIMER1_PCKEN                BIT(4)
#define SYSC_CLKENCFG_TIMER0_PCKEN                BIT(3)
#define SYSC_CLKENCFG_TIMER_PCKEN                 BIT(2)
#define SYSC_CLKENCFG_UART_PCKEN                  BIT(1)
#define SYSC_CLKENCFG_APB_CKEN                    BIT(0)

// SYSC_MSFTRSTCFG
#define SYSC_MSFTRSTCFG_SOFTDIGRST                BIT(9)
#define SYSC_MSFTRSTCFG_UART_PSFT_RST             BIT(8)
#define SYSC_MSFTRSTCFG_ANAC_SFT_RST              BIT(7)
#define SYSC_MSFTRSTCFG_ADC_SFT_RST               BIT(6)
#define SYSC_MSFTRSTCFG_HCLK_SFT_RST              BIT(5)
#define SYSC_MSFTRSTCFG_TIMER4_PSFT_RST           BIT(4)
#define SYSC_MSFTRSTCFG_TIMER3_PSFT_RST           BIT(3)
#define SYSC_MSFTRSTCFG_TIMER2_PSFT_RST           BIT(2)
#define SYSC_MSFTRSTCFG_TIMER1_PSFT_RST           BIT(1)
#define SYSC_MSFTRSTCFG_TIMER0_PSFT_RST           BIT(0)

// SYSC_TESTCKSEL
#define SYSC_TEST_CLK_CKSEL                       BITS(7, 8)
#define SYSC_TEST_HRCCLK_DIV                      BITS(0, 6)
#define SYSC_TEST_HRCCLK_DIV_pos                  (0) // div(x+1)*2

// SYSC_ADCCLKDIV
#define SYSC_ADC_SCLK_DIV                         BITS(0, 3)
#define SYSC_ADC_SCLK_DIV_pos                     (0) // 0-0f:div(x+1)*2


#define SRC_CLK_DIV2()                                                        \
	((SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_APB_CLK_DIV) >> SYSC_CLKCTRCFG_APB_CLK_DIV_pos) + 1

#define SRC_CLK_DIV1()                                                        \
	((SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_AHB_CLK_DIV) >> SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) + 1

#define SYSC_GetAPBCLK()                                                      \
    (SystemCoreClock / (SRC_CLK_DIV2()) / (SRC_CLK_DIV1()))
#define SYSC_GetAHBCLK()                                                      \
    (SystemCoreClock / (SRC_CLK_DIV1()))

// extend define
#define SYSC_CLK_SRC_HRC                          (0)
#define SYSC_CLK_SRC_LRC                          (1)

typedef enum _RST_M
{
	PRST_TIMER0                                   = (1 << 0),
	PRST_TIMER1                                   = (1 << 1),
	PRST_TIMER2                                   = (1 << 2),
	PRST_TIMER3                                   = (1 << 3),
	PRST_TIMER4                                   = (1 << 4),
	PRST_HCLK                                     = (1 << 5),
	PRST_ADC                                      = (1 << 6),
	PRST_ANAC                                     = (1 << 7),
	PRST_UART                                     = (1 << 8),
	PRST_SOFTDIG                                  = (1 << 9),
} eRSTP_Type;

typedef enum _CLK_EN
{
	PCLK_EN_ADC_PCKEN                             = (1 << 15),
	PCLK_EN_LPTIM_CKEN                            = (1 << 14),
	PCLK_EN_LPTIM_PCKEN                           = (1 << 13),
	PCLK_EN_LPWDT_PCKEN                           = (1 << 12),
	PCLK_EN_PMU_PCKEN                             = (1 << 11),
	PCLK_EN_ANAC_PCKEN                            = (1 << 10),
	PCLK_EN_DCLK_HCKEN                            = (1 << 9),
	PCLK_EN_IOM_PCKEN                             = (1 << 8),
	PCLK_EN_TIMER4_PCKEN                          = (1 << 7),
	PCLK_EN_TIMER3_PCKEN                          = (1 << 6),
	PCLK_EN_TIMER2_PCKEN                          = (1 << 5),
	PCLK_EN_TIMER1_PCKEN                          = (1 << 4),
	PCLK_EN_TIMER0_PCKEN                          = (1 << 3),
	PCLK_EN_TIMER_PCKEN                           = (1 << 2),
	PCLK_EN_UART_PCKEN                            = (1 << 1),
	PCLK_EN_APB_PCKEN                             = (1 << 0),
} ePCLKEN_Type;

// sysc function declare
void SYSC_SelectClockSource(int clkSrc);
void SYSC_SetAPBCLKDiv(int div);
void SYSC_SetAHBCLKDiv(int div);
int SYSC_APBCLK_Get(void);
int SYSC_AHBCLK_Get(void);
void SYSC_ResetPeripher(eRSTP_Type module);
void SYSC_PCLKEnable(ePCLKEN_Type perp);
void SYSC_PCLKDisable(ePCLKEN_Type perp);
void SYSC_SetANAC_CLKDiv(int div, int m500kDiv);
#endif /*__SYSC_H__*/
