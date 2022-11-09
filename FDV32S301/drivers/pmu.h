/**
  ******************************************************************************
  * @file    pmu.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-13
  * @brief   This file contains all functional prototypes of the PMU firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PMU_H__
#define __PMU_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx02.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @addtogroup PMU
  * @{
  */

/** @defgroup PMU_module_register_bit_definition
  * @{
  */

/* PMU_CR */
#define PMU_CR_FLSDEEPSTB	BITS(12, 15)
#define PMU_CR_HRCKEEPALIVE BIT(10)
#define PMU_CR_VDDLPCFG		BITS(8, 9)
#define PMU_CR_WDTCLKEN		BIT(7)
#define PMU_CR_LPTCLKEN		BIT(6)
#define PMU_CR_LPTCLKSEL	BIT(5)
#define PMU_CR_LVDCHIPRSTEN BIT(4)
#define PMU_CR_PDNEN		BITS(0, 3)

#define PMU_CR_VDDLPCFG_1P5 (0 << 8)
#define PMU_CR_VDDLPCFG_1P2 (1 << 8)
#define PMU_CR_VDDLPCFG_1P0 (2 << 8)
#define PMU_CR_VDDLPCFG_0P8 (3 << 8)

#define PMU_CR_PDNEN_V (0x0A << 0)

#define PMU_CR_FLSDEEPSTB_pos (12)
#define PMU_CR_VDDLPCFG_pos	  (8)
#define PMU_CR_PDNEN_pos	  (0)

/* PMU_WKCFG */
#define PMU_WKCFG_PMUWKMODE BIT(9)
#define PMU_WKCFG_GPIOWKLEV BITS(4, 7)
#define PMU_WKCFG_GPIOWKEN	BITS(0, 3)

#define PMU_WKCFG_GPIOWKLEV_pos (4)
#define PMU_WKCFG_GPIOWKEN_pos	(0)

/* PMU_SOFTRST */
#define PMU_SOFTRST_DIG	 BIT(1)
#define PMU_SOFTRST_CHIP BIT(0)

/* PMU_WKSTS */
#define PMU_WKSTS_TWCWKSTS	BIT(8)
#define PMU_WKSTS_LPUWKSTS	BIT(7)
#define PMU_WKSTS_RTCWKSTS	BIT(6)
#define PMU_WKSTS_LPTWKSTS	BIT(5)
#define PMU_WKSTS_WDTWKSTS	BIT(4)
#define PMU_WKSTS_GPIOWKSTS BITS(0, 3)

#define PMU_WKSTS_GPIOWKSTS_pos (0)

/* PMU_RSTSTS */
#define PMU_RSTSTS_PORRSTSTS	  BIT(5)
#define PMU_RSTSTS_SOFTDIGRSTSTS  BIT(4)
#define PMU_RSTSTS_SOFTCHIPRSTSTS BIT(3)
#define PMU_RSTSTS_EXTRSTSTS	  BIT(2)
#define PMU_RSTSTS_WDTRSTSTS	  BIT(1)
#define PMU_RSTSTS_LVDRSTSTS	  BIT(0)

/* PMU_INTEN */
#define PMU_INTEN_TWCWKINTEN	   BIT(14)
#define PMU_INTEN_LPUWKINTEN	   BIT(13)
#define PMU_INTEN_RTCWKINTEN	   BIT(12)
#define PMU_INTEN_GPIOWKINTEN	   BITS(8, 11)
#define PMU_INTEN_LPTWKINTEN	   BIT(7)
#define PMU_INTEN_WDTWKINTEN	   BIT(6)
#define PMU_INTEN_PORRSTINTEN	   BIT(5)
#define PMU_INTEN_SOFTDIGRSTINTEN  BIT(4)
#define PMU_INTEN_SOFTCHIPRSTINTEN BIT(3)
#define PMU_INTEN_EXTRSTINTEN	   BIT(2)
#define PMU_INTEN_WDTRSTINTEN	   BIT(1)
#define PMU_INTEN_LVDRSTINTEN	   BIT(0)

#define PMU_INTEN_GPIOWKINTEN_pos (8)

/**
  * @}
  */

/** @defgroup PMU_Exported_Constants
  * @{
  */

/**
  * @defgroup PMU_write_protection_unlock
  * @{
  */

#define PMU_WPT_VALUE_0 (0xC3)
#define PMU_WPT_VALUE_1 (0x3C)
#define PMU_WPT_UNLOCK()                                                                                               \
	{                                                                                                                  \
		PMU->WPT = PMU_WPT_VALUE_0;                                                                                    \
		PMU->WPT = PMU_WPT_VALUE_1;                                                                                    \
	}
/**
  * @}
  */

/** @defgroup PMU_VDD_low_power_voltage
  * @{
  */

#define PMU_VDD_LPVOL_1P5 (0)
#define PMU_VDD_LPVOL_1P2 (1)

#define IS_PMU_VDD_LPVOL(LPVOL) (((LPVOL) == PMU_VDD_LPVOL_1P5) || ((LPVOL) == PMU_VDD_LPVOL_1P2))
/**
  * @}
  */

/** @defgroup PMU_low_power_clock
  * @{
  */

#define PMU_LP_CLOCK_LRC (0)
#define PMU_LP_CLOCK_XTL (1)

#define IS_PMU_LP_CLOCK(CLOCK) (((CLOCK) == PMU_LP_CLOCK_LRC) || ((CLOCK) == PMU_LP_CLOCK_XTL))
/**
  * @}
  */

/** @defgroup PMU_wake_up_mode
  * @{
  */

#define PMU_WAKE_MODE_SYNC	(0)
#define PMU_WAKE_MODE_ASYNC (1)

#define IS_PMU_WAKE_MODE(MODE) (((MODE) == PMU_WAKE_MODE_SYNC) || ((MODE) == PMU_WAKE_MODE_ASYNC))
/**
  * @}
  */

/** @defgroup PMU_IO_wake_up_level
  * @{
  */

#define PMU_IOWAKE_LEVEL_LOW  (0)
#define PMU_IOWAKE_LEVEL_HIGH (1)

#define IS_PMU_IOWAKE_LEVEL(LEVEL) (((LEVEL) == PMU_IOWAKE_LEVEL_LOW) || ((LEVEL) == PMU_IOWAKE_LEVEL_HIGH))
/**
  * @}
  */

/** @defgroup PMU_IO_wake_up_pin
  * @{
  */

#define PMU_IOWAKE_PIN16 BIT(0)
#define PMU_IOWAKE_PIN17 BIT(1)
#define PMU_IOWAKE_PIN18 BIT(2)
#define PMU_IOWAKE_PIN19 BIT(3)

#define PMU_IOWAKE_ALL (PMU_IOWAKE_PIN16 | PMU_IOWAKE_PIN17 | PMU_IOWAKE_PIN18 | PMU_IOWAKE_PIN19)

#define IS_PMU_IOWAKE_PIN(PIN) (((PIN)&PMU_IOWAKE_ALL) && (!((PIN) & (~PMU_IOWAKE_ALL))))
/**
  * @}
  */

/** @defgroup PMU_interrupts_definition
  * @{
  */

#define PMU_IT_TWCWK	   BIT(14)
#define PMU_IT_LPUWK	   BIT(13)
#define PMU_IT_RTCWK	   BIT(12)
#define PMU_IT_GP19WK	   BIT(11)
#define PMU_IT_GP18WK	   BIT(10)
#define PMU_IT_GP17WK	   BIT(9)
#define PMU_IT_GP16WK	   BIT(8)
#define PMU_IT_LPTWK	   BIT(7)
#define PMU_IT_WDTWK	   BIT(6)
#define PMU_IT_PORRST	   BIT(5)
#define PMU_IT_SOFTDIGRST  BIT(4)
#define PMU_IT_SOFTCHIPRST BIT(3)
#define PMU_IT_EXTRST	   BIT(2)
#define PMU_IT_WDTRST	   BIT(1)
#define PMU_IT_LVDRST	   BIT(0)

#define PMU_IT_ALL                                                                                                     \
	(PMU_IT_TWCWK | PMU_IT_LPUWK | PMU_IT_RTCWK | PMU_IT_GP19WK | PMU_IT_GP18WK | PMU_IT_GP17WK | PMU_IT_GP16WK |      \
	 PMU_IT_LPTWK | PMU_IT_WDTWK | PMU_IT_PORRST | PMU_IT_SOFTDIGRST | PMU_IT_SOFTCHIPRST | PMU_IT_EXTRST |            \
	 PMU_IT_WDTRST | PMU_IT_LVDRST)

#define IS_PMU_CONFIG_IT(IT) (((IT)&PMU_IT_ALL) && (!((IT) & (~(PMU_IT_ALL)))))

#define IS_PMU_GET_IT(IT)                                                                                              \
	(((IT) == PMU_IT_TWCWK) || ((IT) == PMU_IT_LPUWK) || ((IT) == PMU_IT_RTCWK) || ((IT) == PMU_IT_GP19WK) ||          \
	 ((IT) == PMU_IT_GP18WK) || ((IT) == PMU_IT_GP17WK) || ((IT) == PMU_IT_GP16WK) || ((IT) == PMU_IT_LPTWK) ||        \
	 ((IT) == PMU_IT_WDTWK) || ((IT) == PMU_IT_PORRST) || ((IT) == PMU_IT_SOFTDIGRST) ||                               \
	 ((IT) == PMU_IT_SOFTCHIPRST) || ((IT) == PMU_IT_EXTRST) || ((IT) == PMU_IT_WDTRST) || ((IT) == PMU_IT_LVDRST))
/**
  * @}
  */

/** @defgroup PMU_flags_definition
  * @{
  */

#define PMU_FLAG_TWCWK		 BIT(14)
#define PMU_FLAG_LPUWK		 BIT(13)
#define PMU_FLAG_RTCWK		 BIT(12)
#define PMU_FLAG_LPTWK		 BIT(11)
#define PMU_FLAG_WDTWK		 BIT(10)
#define PMU_FLAG_GP19WK		 BIT(9)
#define PMU_FLAG_GP18WK		 BIT(8)
#define PMU_FLAG_GP17WK		 BIT(7)
#define PMU_FLAG_GP16WK		 BIT(6)
#define PMU_FLAG_PORRST		 BIT(5)
#define PMU_FLAG_SOFTDIGRST	 BIT(4)
#define PMU_FLAG_SOFTCHIPRST BIT(3)
#define PMU_FLAG_EXTRST		 BIT(2)
#define PMU_FLAG_WDTRST		 BIT(1)
#define PMU_FLAG_LVDRST		 BIT(0)

#define PMU_FLAG_ALL                                                                                                   \
	(PMU_FLAG_TWCWK | PMU_FLAG_LPUWK | PMU_FLAG_RTCWK | PMU_FLAG_GP19WK | PMU_FLAG_GP18WK | PMU_FLAG_GP17WK |          \
	 PMU_FLAG_GP16WK | PMU_FLAG_LPTWK | PMU_FLAG_WDTWK | PMU_FLAG_PORRST | PMU_FLAG_SOFTDIGRST |                       \
	 PMU_FLAG_SOFTCHIPRST | PMU_FLAG_EXTRST | PMU_FLAG_WDTRST | PMU_FLAG_LVDRST)

#define IS_PMU_GET_FLAG(FLAG)                                                                                          \
	(((FLAG) == PMU_FLAG_TWCWK) || ((FLAG) == PMU_FLAG_LPUWK) || ((FLAG) == PMU_FLAG_RTCWK) ||                         \
	 ((FLAG) == PMU_FLAG_GP19WK) || ((FLAG) == PMU_FLAG_GP18WK) || ((FLAG) == PMU_FLAG_GP17WK) ||                      \
	 ((FLAG) == PMU_FLAG_GP16WK) || ((FLAG) == PMU_FLAG_LPTWK) || ((FLAG) == PMU_FLAG_WDTWK) ||                        \
	 ((FLAG) == PMU_FLAG_PORRST) || ((FLAG) == PMU_FLAG_SOFTDIGRST) || ((FLAG) == PMU_FLAG_SOFTCHIPRST) ||             \
	 ((FLAG) == PMU_FLAG_EXTRST) || ((FLAG) == PMU_FLAG_WDTRST) || ((FLAG) == PMU_FLAG_LVDRST))

#define IS_PMU_CLEAR_FLAG(FLAG) (((FLAG) & PMU_FLAG_ALL) && (!((FLAG) & (~(PMU_FLAG_ALL)))))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PMU_Exported_Functions
  * @{
  */

void	   PMU_VDDLowPowerConfig(u8 Voltage);
void	   PMU_IOWakeLevelConfig(u8 WKPin, u8 WKLevel);
void	   PMU_SetLowPowerClock(u8 LPClock);
void	   PMU_SetWakeMode(u8 WakeMode);
void	   PMU_HRCKeepAliveCmd(FunctionalState NewState);
void	   PMU_WDTClockCmd(FunctionalState NewState);
void	   PMU_LPTClockCmd(FunctionalState NewState);
void	   PMU_LVDResetCmd(FunctionalState NewState);
void	   PMU_PowerDownCmd(FunctionalState NewState);
void	   PMU_GPIOWakeCmd(u8 WKPin, FunctionalState NewState);
void	   PMU_ITConfig(u16 PMU_IT, FunctionalState NewState);
FlagStatus PMU_GetFlagStatus(u16 PMU_FLAG);
ITStatus   PMU_GetITStatus(u16 PMU_IT);
void	   PMU_ClearFlag(u16 PMU_FLAG);
void	   PMU_SoftDigitalReset(void);
void	   PMU_SoftChipReset(void);
void	   PMU_SoftCoreReset(void);
void	   PMU_EnterSleep(void);
void	   PMU_EnterDeepSleep(void);
void	   PMU_EnterPowerDown(void);

#ifdef __cplusplus
}
#endif

#endif /* __PMU_H__ */

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

