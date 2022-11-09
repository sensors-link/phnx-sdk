/**
  ******************************************************************************
  * @file    sysc.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-21
  * @brief   This file contains all functional prototypes of the SYSC firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSC_H__
#define __SYSC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx04.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSC
  * @{
  */

/** @defgroup SYSC_module_register_bit_definition
  * @{
  */

/* SYSC_CLKCTRCFG */
#define SYSC_CLKCTRCFG_DSP_WKUP_DLY 	BITS(24, 31)
#define SYSC_CLKCTRCFG_APB_CLK_DIV		BITS(16, 22)
#define SYSC_CLKCTRCFG_AHB_CLK_DIV		BITS(8, 14)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL		BIT(4)
#define SYSC_CLKCTRCFG_DPS_ENT_DLY_EN	BIT(0)

#define SYSC_CLKCTRCFG_SYS_CLK_SEL_HRC (0 << 4)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC (1 << 4)

#define SYSC_CLKCTRCFG_DSP_WKUP_DLY_pos (24) /* T=(x+3)/src_clk  def:0x1A(3us) */
#define SYSC_CLKCTRCFG_APB_CLK_DIV_pos	(16) /* 0-0x7f:div1-128 */
#define SYSC_CLKCTRCFG_AHB_CLK_DIV_pos	(8)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL_pos	(4)

/* SYSC_CLKENCFG */
#define SYSC_CLKENCFG_TWC_MRCK	  BIT(21)
#define SYSC_CLKENCFG_TWC		  BIT(19)
#define SYSC_CLKENCFG_LPTIM		  BIT(15)
#define SYSC_CLKENCFG_WDT		  BIT(14)
#define SYSC_CLKENCFG_PMU		  BIT(13)
#define SYSC_CLKENCFG_ANAC		  BIT(12)
#define SYSC_CLKENCFG_DCLK_HCK	  BIT(11)
#define SYSC_CLKENCFG_IOM		  BIT(10)
#define SYSC_CLKENCFG_TIM2_CNT	  BIT(7)
#define SYSC_CLKENCFG_TIM1_CNT	  BIT(6)
#define SYSC_CLKENCFG_TIM_PCK	  BIT(5)
#define SYSC_CLKENCFG_UART2		  BIT(4)
#define SYSC_CLKENCFG_UART1		  BIT(3)
#define SYSC_CLKENCFG_SPI		  BIT(2)
#define SYSC_CLKENCFG_APB		  BIT(0)

/* SYSC_MSFTRSTCFG */
#define SYSC_MSFTRSTCFG_TWC	   BIT(9)
#define SYSC_MSFTRSTCFG_ANAC   BIT(7)
#define SYSC_MSFTRSTCFG_HCLK   BIT(6)
#define SYSC_MSFTRSTCFG_TIMER  BIT(4)
#define SYSC_MSFTRSTCFG_UART2  BIT(3)
#define SYSC_MSFTRSTCFG_UART1  BIT(2)
#define SYSC_MSFTRSTCFG_SPI	   BIT(1)

/* SYSC_ANCLKDIV */
#define SYSC_ANCLKDIV_500K_CLK_DIV BITS(4, 8)
#define SYSC_ANCLKDIV_ADC_CLK_DIV  BITS(0, 3)

#define SYSC_ANCLKDIV_500K_CLK_DIV_pos (4) /* 0-1f:div(x+1) */
#define SYSC_ANCLKDIV_ADC_CLK_DIV_pos  (0) /* 0-0f:div(x+1)*2 */

/* SYSC_TIMCLKDIV */
#define SYSC_TIMCLKDIV_TIM2_DIV BITS(8, 15)
#define SYSC_TIMCLKDIV_TIM1_DIV BITS(0, 7)

#define SYSC_TIMCLKDIV_TIM2_DIV_pos (8) /* 0-ff:div(x+1) */
#define SYSC_TIMCLKDIV_TIM1_DIV_pos (0) /* 0-ff:div(x+1) */

/**
  * @}
  */

/** @defgroup SYSC_Exported_Types
  * @{
  */

typedef struct
{
	u32 SYSCLK_Frequency; /*!< returns SYSCLK clock frequency expressed in Hz */
	u32 HCLK_Frequency;	  /*!< returns HCLK clock frequency expressed in Hz */
	u32 PCLK_Frequency;	  /*!< returns PCLK clock frequency expressed in Hz */
} SYSC_ClocksTypeDef;

/**
  * @}
  */

/** @defgroup SYSC_Exported_Constants
  * @{
  */

/**
  * @defgroup SYSC_write_protection_unlock
  * @{
  */

#define SYSC_WRPROCFG_V0 (0x5A5A)
#define SYSC_WRPROCFG_V1 (0xA5A5)
#define SYSC_WPT_UNLOCK()                                                                                              \
	{                                                                                                                  \
		SYSC->WRPROCFG = SYSC_WRPROCFG_V0;                                                                             \
		SYSC->WRPROCFG = SYSC_WRPROCFG_V1;                                                                             \
	}
/**
  * @}
  */

/** @defgroup SYSC_APB_clock_divider
  * @{
  */

#define IS_SYSC_APB_DIV(DIV) (((DIV) >= 0x001) && ((DIV) <= 0x200))
/**
  * @}
  */

/** @defgroup SYSC_AHB_clock_divider
  * @{
  */

#define IS_SYSC_AHB_DIV(DIV) (((DIV) >= 0x001) && ((DIV) <= 0x200))
/**
  * @}
  */

/** @defgroup SYSC_TIM_clock_divider
  * @{
  */

#define IS_SYSC_TIM_DIV(DIV) (((DIV) >= 0x001) && ((DIV) <= 0x200))
/**
  * @}
  */

/** @defgroup SYSC_timer_selection
  * @{
  */
	
#define SYSC_TIMSEL_TIM1 (0)
#define SYSC_TIMSEL_TIM2 (2)
	
#define IS_SYSC_TIM_SEL(TIMSEL)	(((TIMSEL) == SYSC_TIMSEL_TIM1) || ((TIMSEL) == SYSC_TIMSEL_TIM2))
/**
  * @}
  */

/** @defgroup SYSC_system_clock_source
  * @{
  */

#define SYSC_SYSCLK_SOURCE_HRC (0)
#define SYSC_SYSCLK_SOURCE_LRC (1)

#define IS_SYSC_SYSCLK_SOURCE(SOURCE)	(((SOURCE) == SYSC_SYSCLK_SOURCE_HRC) || ((SOURCE) == SYSC_SYSCLK_SOURCE_LRC))
/**
  * @}
  */

/** @defgroup SYSC_ADC_clock_divider
  * @{
  */

#define SYSC_ADCCLK_DIV2  (0)
#define SYSC_ADCCLK_DIV4  (1)
#define SYSC_ADCCLK_DIV6  (2)
#define SYSC_ADCCLK_DIV8  (3)
#define SYSC_ADCCLK_DIV10 (4)
#define SYSC_ADCCLK_DIV12 (5)
#define SYSC_ADCCLK_DIV14 (6)
#define SYSC_ADCCLK_DIV16 (7)
#define SYSC_ADCCLK_DIV18 (8)
#define SYSC_ADCCLK_DIV20 (9)
#define SYSC_ADCCLK_DIV22 (10)
#define SYSC_ADCCLK_DIV24 (11)
#define SYSC_ADCCLK_DIV26 (12)
#define SYSC_ADCCLK_DIV28 (13)
#define SYSC_ADCCLK_DIV30 (14)
#define SYSC_ADCCLK_DIV32 (15)

#define IS_SYSC_ADCCLK_DIV(DIV) (((DIV) <= 0xF))

#define IS_SYSC_ADC500KCLK_DIV(DIV) (((DIV) > 0) && ((DIV) <= 0x1F))
/**
  * @}
  */

/** @defgroup SYSC_moudlue_clock
  * @{
  */

#define SYSC_MOUDLE_CLOCK_TWC_MRCK	  BIT(21)
#define SYSC_MOUDLE_CLOCK_TWC		  BIT(19)
#define SYSC_MOUDLE_CLOCK_LPTIM		  BIT(15)
#define SYSC_MOUDLE_CLOCK_WDT		  BIT(14)
#define SYSC_MOUDLE_CLOCK_PMU		  BIT(13)
#define SYSC_MOUDLE_CLOCK_ANAC		  BIT(12)
#define SYSC_MOUDLE_CLOCK_DCLK		  BIT(11)
#define SYSC_MOUDLE_CLOCK_IOM		  BIT(10)
#define SYSC_MOUDLE_CLOCK_TIM2		  BIT(7)
#define SYSC_MOUDLE_CLOCK_TIM1		  BIT(6)
#define SYSC_MOUDLE_CLOCK_TIMER		  BIT(5)
#define SYSC_MOUDLE_CLOCK_UART2		  BIT(4)
#define SYSC_MOUDLE_CLOCK_UART1		  BIT(3)
#define SYSC_MOUDLE_CLOCK_SPI		  BIT(2)
#define SYSC_MOUDLE_CLOCK_APB		  BIT(0)

#define SYSC_MOUDLE_CLOCK_ALL                                                                                          \
	(SYSC_MOUDLE_CLOCK_TWC_MRCK | SYSC_MOUDLE_CLOCK_TWC | SYSC_MOUDLE_CLOCK_LPTIM | SYSC_MOUDLE_CLOCK_WDT |            \
	 SYSC_MOUDLE_CLOCK_PMU | SYSC_MOUDLE_CLOCK_ANAC | SYSC_MOUDLE_CLOCK_DCLK | SYSC_MOUDLE_CLOCK_IOM |                 \
	 SYSC_MOUDLE_CLOCK_TIM2 | SYSC_MOUDLE_CLOCK_TIM1 | SYSC_MOUDLE_CLOCK_TIMER | SYSC_MOUDLE_CLOCK_UART2 |             \
	 SYSC_MOUDLE_CLOCK_UART1 | SYSC_MOUDLE_CLOCK_SPI | SYSC_MOUDLE_CLOCK_APB)

#define IS_SYSC_MOUDLE_CLOCK(CLOCK) (((CLOCK)&SYSC_MOUDLE_CLOCK_ALL) && (!((CLOCK) & (~(SYSC_MOUDLE_CLOCK_ALL)))))
/**
  * @}
  */

/** @defgroup SYSC_reset_module
  * @{
  */

#define SYSC_RESET_MOUDLE_TWC	 BIT(9)
#define SYSC_RESET_MOUDLE_ANAC	 BIT(7)
#define SYSC_RESET_MOUDLE_HCLK	 BIT(6)
#define SYSC_RESET_MOUDLE_TIMER	 BIT(4)
#define SYSC_RESET_MOUDLE_UART2	 BIT(3)
#define SYSC_RESET_MOUDLE_UART1	 BIT(2)
#define SYSC_RESET_MOUDLE_SPI	 BIT(1)

#define SYSC_RESET_MOUDLE_ALL                                                                                          \
	(SYSC_RESET_MOUDLE_TWC | SYSC_RESET_MOUDLE_ANAC | SYSC_RESET_MOUDLE_HCLK | SYSC_RESET_MOUDLE_TIMER |               \
	 SYSC_RESET_MOUDLE_UART2 | SYSC_RESET_MOUDLE_UART1 | SYSC_RESET_MOUDLE_SPI)

#define IS_SYSC_RESET_MOUDLE(MOUDLE) (((MOUDLE) & SYSC_RESET_MOUDLE_ALL) && (!((MOUDLE) & (~(SYSC_RESET_MOUDLE_ALL)))))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SYSC_Exported_Functions
  * @{
  */

void SYSC_WakeDelayConfig(u8 Delay);
void SYSC_PCLKConfig(u16 Div);
void SYSC_HCLKConfig(u16 Div);
void SYSC_SYSCLKConfig(u8 ClockSrc);
void SYSC_ADCCLKConfig(u8 Div);
void SYSC_TIMCLKConfig(u8 TimerSel, u16 Div);
u8	 SYSC_GetSYSCLKSource(void);
void SYSC_GetClocksFreq(SYSC_ClocksTypeDef *SYSC_Clocks);
void SYSC_PeriphClockCmd(u32 MouleClocks, FunctionalState NewState);
void SYSC_ResetPeripher(u32 Module);

#ifdef __cplusplus
}
#endif

#endif /* __SYSC_H__ */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

