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
#include "phnx05.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSC
  * @{
  */

/** @defgroup SYSC_module_register_bit_definition
  * @{
  */

/* SYSC_CLKCTRCFG */
#define SYSC_CLKCTRCFG_DSP_WKUP_DLY 	BITS(23, 31)
#define SYSC_CLKCTRCFG_APB_CLK_DIV		BITS(16, 22)
#define SYSC_CLKCTRCFG_AHB_CLK_DIV		BITS(8, 14)
#define SYSC_CLKCTRCFG_WDT_EN			BIT(2)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL		BIT(0)

#define SYSC_CLKCTRCFG_SYS_CLK_SEL_HRC (0 << 4)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC (1 << 4)

#define SYSC_CLKCTRCFG_DSP_WKUP_DLY_pos (23) /* T=(x)/src_clk  def:0xA0(20us) */
#define SYSC_CLKCTRCFG_APB_CLK_DIV_pos	(16) /* 0-0x7f:div1-128 */
#define SYSC_CLKCTRCFG_AHB_CLK_DIV_pos	(8)
#define SYSC_CLKCTRCFG_SYS_CLK_SEL_pos	(0)

/* SYSC_CLKENCFG */
#define SYSC_CLKENCFG_ADC		  BIT(15)
#define SYSC_CLKENCFG_LPTIM_CK    BIT(14)
#define SYSC_CLKENCFG_LPTIM		  BIT(13)
#define SYSC_CLKENCFG_WDT		  BIT(12)
#define SYSC_CLKENCFG_PMU		  BIT(11)
#define SYSC_CLKENCFG_ANAC		  BIT(10)
#define SYSC_CLKENCFG_DCLK_HCK	  BIT(9)
#define SYSC_CLKENCFG_IOM		  BIT(8)
#define SYSC_CLKENCFG_TIM4_CNT	  BIT(7)
#define SYSC_CLKENCFG_TIM3_CNT	  BIT(6)
#define SYSC_CLKENCFG_TIM2_CNT	  BIT(5)
#define SYSC_CLKENCFG_TIM1_CNT	  BIT(4)
#define SYSC_CLKENCFG_TIM0_CNT	  BIT(3)
#define SYSC_CLKENCFG_TIM_PCK	  BIT(2)
#define SYSC_CLKENCFG_UART		  BIT(1)
#define SYSC_CLKENCFG_APB		  BIT(0)

/* SYSC_MSFTRSTCFG */
#define SYSC_MSFTRSTCFG_DIG	   BIT(9)
#define SYSC_MSFTRSTCFG_UART   BIT(8)
#define SYSC_MSFTRSTCFG_ANAC   BIT(7)
#define SYSC_MSFTRSTCFG_ADC    BIT(6)
#define SYSC_MSFTRSTCFG_HCLK   BIT(5)
#define SYSC_MSFTRSTCFG_TIM4   BIT(4)
#define SYSC_MSFTRSTCFG_TIM3   BIT(3)
#define SYSC_MSFTRSTCFG_TIM2   BIT(2)
#define SYSC_MSFTRSTCFG_TIM1   BIT(1)
#define SYSC_MSFTRSTCFG_TIM0   BIT(0)

/* SYSC_ADCCLKDIV */
#define SYSC_ADCCLKDIV_ADC_CLK_DIV  BITS(0, 3)

#define SYSC_ADCCLKDIV_ADC_CLK_DIV_pos  (0) /* 0-0f:div(x)*2 */

/* SYSC_RSTSTS */
#define SYSC_RSTSTS_LVDRSTSTS		BIT(4)
#define SYSC_RSTSTS_SOFTDIGRSTSTS	BIT(3)
#define SYSC_RSTSTS_EXTRSTSTS		BIT(2)
#define SYSC_RSTSTS_WDTRSTSTS		BIT(1)
#define SYSC_RSTSTS_PORRSTSTS		BIT(0)

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

#define SYSC_WRPROCFG_V0 (0x5A)
#define SYSC_WRPROCFG_V1 (0xA5)
#define SYSC_WPT_UNLOCK()                                                                                              \
	{                                                                                                                  \
		SYSC->WRPROCFG = SYSC_WRPROCFG_V0;                                                                             \
		SYSC->WRPROCFG = SYSC_WRPROCFG_V1;                                                                             \
	}
/**
  * @}
  */

/** @defgroup SYSC_wake_up_delay
  * @{
  */

#define IS_SYSC_WAKE_DELAY(DELAY) ((DELAY) <= 0x1FF)
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

/** @defgroup SYSC_system_clock_source
  * @{
  */

#define SYSC_SYSCLK_SOURCE_HRC (0)
#define SYSC_SYSCLK_SOURCE_LRC (1)

#define IS_SYSC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == SYSC_SYSCLK_SOURCE_HRC) || ((SOURCE) == SYSC_SYSCLK_SOURCE_LRC))
/**
  * @}
  */

/** @defgroup SYSC_ADC_clock_divider
  * @{
  */
	
#define SYSC_ADCCLK_DIV0  (0)
#define SYSC_ADCCLK_DIV2  (1)
#define SYSC_ADCCLK_DIV4  (2)
#define SYSC_ADCCLK_DIV6  (3)
#define SYSC_ADCCLK_DIV8  (4)
#define SYSC_ADCCLK_DIV10 (5)
#define SYSC_ADCCLK_DIV12 (6)
#define SYSC_ADCCLK_DIV14 (7)
#define SYSC_ADCCLK_DIV16 (8)
#define SYSC_ADCCLK_DIV18 (9)
#define SYSC_ADCCLK_DIV20 (10)
#define SYSC_ADCCLK_DIV22 (11)
#define SYSC_ADCCLK_DIV24 (12)
#define SYSC_ADCCLK_DIV26 (13)
#define SYSC_ADCCLK_DIV28 (14)
#define SYSC_ADCCLK_DIV30 (15)

#define IS_SYSC_ADCCLK_DIV(DIV) (((DIV) <= 0xF))
/**
  * @}
  */

/** @defgroup SYSC_moudlue_clock
  * @{
  */

#define SYSC_MOUDLE_CLOCK_ADC		  BIT(15)
#define SYSC_MOUDLE_CLOCK_LPTIM_CK    BIT(14)
#define SYSC_MOUDLE_CLOCK_LPTIM		  BIT(13)
#define SYSC_MOUDLE_CLOCK_WDT		  BIT(12)
#define SYSC_MOUDLE_CLOCK_PMU		  BIT(11)
#define SYSC_MOUDLE_CLOCK_ANAC		  BIT(10)
#define SYSC_MOUDLE_CLOCK_DCLK		  BIT(9)
#define SYSC_MOUDLE_CLOCK_IOM		  BIT(8)
#define SYSC_MOUDLE_CLOCK_TIM4		  BIT(7)
#define SYSC_MOUDLE_CLOCK_TIM3		  BIT(6)
#define SYSC_MOUDLE_CLOCK_TIM2		  BIT(5)
#define SYSC_MOUDLE_CLOCK_TIM1		  BIT(4)
#define SYSC_MOUDLE_CLOCK_TIM0		  BIT(3)
#define SYSC_MOUDLE_CLOCK_TIMER		  BIT(2)
#define SYSC_MOUDLE_CLOCK_UART		  BIT(1)
#define SYSC_MOUDLE_CLOCK_APB		  BIT(0)

#define SYSC_MOUDLE_CLOCK_ALL                                                                                          \
	(SYSC_MOUDLE_CLOCK_ADC | SYSC_MOUDLE_CLOCK_LPTIM_CK | SYSC_MOUDLE_CLOCK_LPTIM | SYSC_MOUDLE_CLOCK_WDT |            \
	 SYSC_MOUDLE_CLOCK_PMU | SYSC_MOUDLE_CLOCK_ANAC | SYSC_MOUDLE_CLOCK_DCLK | SYSC_MOUDLE_CLOCK_IOM |                 \
	 SYSC_MOUDLE_CLOCK_TIM4 | SYSC_MOUDLE_CLOCK_TIM3 | SYSC_MOUDLE_CLOCK_TIM2 | SYSC_MOUDLE_CLOCK_TIM1 |               \
	 SYSC_MOUDLE_CLOCK_TIM0 | SYSC_MOUDLE_CLOCK_TIMER | SYSC_MOUDLE_CLOCK_UART | SYSC_MOUDLE_CLOCK_APB)

#define IS_SYSC_MOUDLE_CLOCK(CLOCK) (((CLOCK)&SYSC_MOUDLE_CLOCK_ALL) && (!((CLOCK) & (~(SYSC_MOUDLE_CLOCK_ALL)))))
/**
  * @}
  */

/** @defgroup SYSC_reset_module
  * @{
  */

#define SYSC_RESET_MOUDLE_DIG	BIT(9)
#define SYSC_RESET_MOUDLE_UART 	BIT(8)
#define SYSC_RESET_MOUDLE_ANAC 	BIT(7)
#define SYSC_RESET_MOUDLE_ADC  	BIT(6)
#define SYSC_RESET_MOUDLE_HCLK 	BIT(5)
#define SYSC_RESET_MOUDLE_TIM4 	BIT(4)
#define SYSC_RESET_MOUDLE_TIM3 	BIT(3)
#define SYSC_RESET_MOUDLE_TIM2 	BIT(2)
#define SYSC_RESET_MOUDLE_TIM1 	BIT(1)
#define SYSC_RESET_MOUDLE_TIM0 	BIT(0)

#define SYSC_RESET_MOUDLE_ALL                                                                                          \
	(SYSC_RESET_MOUDLE_DIG | SYSC_RESET_MOUDLE_UART | SYSC_RESET_MOUDLE_ANAC | SYSC_RESET_MOUDLE_ADC |                 \
	 SYSC_RESET_MOUDLE_HCLK | SYSC_RESET_MOUDLE_TIM4 | SYSC_RESET_MOUDLE_TIM3 | SYSC_RESET_MOUDLE_TIM2 | 			   \
	 SYSC_RESET_MOUDLE_TIM1 | SYSC_RESET_MOUDLE_TIM0)

#define IS_SYSC_RESET_MOUDLE(MOUDLE) (((MOUDLE) & SYSC_RESET_MOUDLE_ALL) && (!((MOUDLE) & (~(SYSC_RESET_MOUDLE_ALL)))))
/**
  * @}
  */

/** @defgroup SYSC_flags_definition
  * @{
  */
	
#define SYSC_FLAG_LVDRST		 BIT(4)
#define SYSC_FLAG_SOFTDIGRST	 BIT(3)
#define SYSC_FLAG_EXTRST		 BIT(2)
#define SYSC_FLAG_WDTRST		 BIT(1)
#define SYSC_FLAG_PORRST		 BIT(0)

#define SYSC_FLAG_ALL                                                                                                   \
	(SYSC_FLAG_LVDRST | SYSC_FLAG_SOFTDIGRST | SYSC_FLAG_EXTRST | SYSC_FLAG_WDTRST | SYSC_FLAG_PORRST)

#define IS_SYSC_GET_FLAG(FLAG)                                                                                          \
	(((FLAG) == SYSC_FLAG_LVDRST) || ((FLAG) == SYSC_FLAG_SOFTDIGRST) || ((FLAG) == SYSC_FLAG_EXTRST) ||			    \
	 ((FLAG) == SYSC_FLAG_WDTRST) || ((FLAG) == SYSC_FLAG_PORRST))

#define IS_SYSC_CLEAR_FLAG(FLAG) (((FLAG) & SYSC_FLAG_ALL) && (!((FLAG) & (~(SYSC_FLAG_ALL)))))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SYSC_Exported_Functions
  * @{
  */

void	   SYSC_WakeDelayConfig(u16 Delay);
void	   SYSC_PCLKConfig(u16 Div);
void	   SYSC_HCLKConfig(u16 Div);
void	   SYSC_SYSCLKConfig(u8 ClockSrc);
void	   SYSC_ADCCLKConfig(u8 Div);
u8		   SYSC_GetSYSCLKSource(void);
void	   SYSC_GetClocksFreq(SYSC_ClocksTypeDef *SYSC_Clocks);
void	   SYSC_WDTCmd(FunctionalState NewState);
void	   SYSC_PeriphClockCmd(u32 MouleClocks, FunctionalState NewState);
void	   SYSC_ResetPeripher(u32 Module);
FlagStatus SYSC_GetFlagStatus(u16 SYSC_FLAG);
void	   SYSC_ClearFlag(u16 SYSC_FLAG);
void	   PMU_SoftCoreReset(void);
void	   PMU_EnterSleep(void);
void	   PMU_EnterDeepSleep(void);

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

