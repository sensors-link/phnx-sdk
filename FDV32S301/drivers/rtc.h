/**
  ******************************************************************************
  * @file    rtc.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-15
  * @brief   This file contains all functional prototypes of the RTC firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H__
#define __RTC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx02.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/** @defgroup RTC_module_register_bit_definition
  * @{
  */

/* RTC_CON */
#define RTC_CON_RTCEN  BIT(31)
#define RTC_CON_CKSEL  BITS(28, 30)
#define RTC_CON_FMT	   BIT(24)
#define RTC_CON_ALMEN  BIT(23)
#define RTC_CON_ALMIE  BIT(22)
#define RTC_CON_PRDEN  BIT(21)
#define RTC_CON_PRDIE  BIT(20)
#define RTC_CON_WAIT   BIT(16)
#define RTC_CON_PRDS   BITS(8, 10)
#define RTC_CON_PRDSEL BIT(7)
#define RTC_CON_PRDX   BITS(0, 5)

#define RTC_CON_CKSEL_XTL		 (0 << 28)
#define RTC_CON_CKSEL_LRC		 (2 << 28)
#define RTC_CON_CKSEL_XTH_DIV128 (4 << 28)
#define RTC_CON_CKSEL_XTH_DIV256 (5 << 28)
#define RTC_CON_CKSEL_XTH_DIV512 (6 << 28)

#define RTC_CON_PRDS_NOTINT (0 << 8)
#define RTC_CON_PRDS_0P5S	(1 << 8)
#define RTC_CON_PRDS_1S		(2 << 8)
#define RTC_CON_PRDS_1MIN	(3 << 8)
#define RTC_CON_PRDS_1H		(4 << 8)
#define RTC_CON_PRDS_1DAY	(5 << 8)
#define RTC_CON_PRDS_1MONTH (6 << 8)

#define RTC_CON_CKSEL_pos (28)
#define RTC_CON_PRDS_pos  (8)
#define RTC_CON_PRDX_pos  (0) /* (x+1)*0.5s*/

/* RTC_STS */
#define RTC_STS_WAITF BIT(8)
#define RTC_STS_PRDF  BIT(4)
#define RTC_STS_ALMF  BIT(0)

/* RTC_TR */
#define RTC_TR_HOURH BITS(20, 21)
#define RTC_TR_HOURL BITS(16, 19)
#define RTC_TR_MINH	 BITS(12, 14)
#define RTC_TR_MINL	 BITS(8, 11)
#define RTC_TR_SECH	 BITS(4, 6)
#define RTC_TR_SECL	 BITS(0, 3)

#define RTC_TR_HOURH_pos (20)
#define RTC_TR_HOURL_pos (16)
#define RTC_TR_MINH_pos	 (12)
#define RTC_TR_MINL_pos	 (8)
#define RTC_TR_SECH_pos	 (4)
#define RTC_TR_SECL_pos	 (0)

/* RTC_DR */
#define RTC_DR_YEARH BITS(28, 31)
#define RTC_DR_YEARL BITS(24, 27)
#define RTC_DR_MONH	 BIT(20)
#define RTC_DR_MONL	 BITS(16, 19)
#define RTC_DR_WEEK	 BITS(8, 10)
#define RTC_DR_DAYH	 BITS(4, 5)
#define RTC_DR_DAYL	 BITS(0, 3)

#define RTC_DR_YEARH_pos (28)
#define RTC_DR_YEARL_pos (24)
#define RTC_DR_MONH_pos	 (20)
#define RTC_DR_MONL_pos	 (16)
#define RTC_DR_WEEK_pos	 (8)
#define RTC_DR_DAYH_pos	 (4)
#define RTC_DR_DAYL_pos	 (0)

/* RTC_ALM */
#define RTC_ALM_ALMWEEK	 BITS(16, 22)
#define RTC_ALM_ALMHOURH BITS(12, 13)
#define RTC_ALM_ALMHOURL BITS(8, 11)
#define RTC_ALM_ALMMINH	 BITS(4, 6)
#define RTC_ALM_ALMMINL	 BITS(0, 3)

#define RTC_ALM_ALMWEEK_pos	 (16)
#define RTC_ALM_ALMHOURH_pos (12)
#define RTC_ALM_ALMHOURL_pos (8)
#define RTC_ALM_ALMMINH_pos	 (4)
#define RTC_ALM_ALMMINL_pos	 (0)

/* RTC_CALR */
#define RTC_CALR_CAL_EN	 BIT(15)
#define RTC_CALR_CAL_SEL BIT(14)
#define RTC_CALR_1HZ_OE	 BIT(13)
#define RTC_CALR_CR		 BITS(0, 8)

#define RTC_CALR_CR_pos (0)

/**
  * @}
  */

/** @defgroup RTC_Exported_Types
  * @{
  */

/**
  * @brief RTC Init structure definition
  */

typedef struct
{
	u8 RTC_ClockSrc; 						/*!< Specify the clock source for the RTC peripheral.
								  				 This parameter can be a value of @ref RTC_clock_source. */

	u8 RTC_TimeFormat; 						/*!< Specify the time display format of the RTC peripheral.
												 This parameter can be a value of @ref RTC_time_format. */
} RTC_InitTypeDef;

/**
  * @brief RTC Date structure definition
  */

typedef struct
{
	u8 RTC_Year;
	u8 RTC_Mon;
	u8 RTC_Day;
	u8 RTC_Week;
	u8 RTC_Hour;
	u8 RTC_Min;
	u8 RTC_Sec;
} RTC_DateDef;

/**
  * @}
  */

/** @defgroup RTC_Exported_Constants
  * @{
  */

/**
  * @defgroup RTC_write_protection_unlock
  * @{
  */

#define RTC_WPR_VALUE_0 (0xCA)
#define RTC_WPR_VALUE_1 (0x53)
#define RTC_WPT_UNLOCK()                                                                                               \
	{                                                                                                                  \
		RTC->WPR = RTC_WPR_VALUE_0;                                                                                    \
		RTC->WPR = RTC_WPR_VALUE_1;                                                                                    \
	}
/**
  * @}
  */

/**
  * @defgroup RTC_clock_source
  * @{
  */

#define RTC_CLOCK_SRC_XTL		 (0)
#define RTC_CLOCK_SRC_LRC		 (2)
#define RTC_CLOCK_SRC_XTH_DIV128 (4)
#define RTC_CLOCK_SRC_XTH_DIV256 (5)
#define RTC_CLOCK_SRC_XTH_DIV512 (6)

#define IS_RTC_CLOCK_SOURCE(SOURCE)                                                                                    \
	(((SOURCE) == RTC_CLOCK_SRC_XTL) || ((SOURCE) == RTC_CLOCK_SRC_LRC) || ((SOURCE) == RTC_CLOCK_SRC_XTH_DIV128) ||   \
	 ((SOURCE) == RTC_CLOCK_SRC_XTH_DIV256) || ((SOURCE) == RTC_CLOCK_SRC_XTH_DIV512))
/**
  * @}
  */

/**
  * @defgroup RTC_time_format
  * @{
  */

#define RTC_TIME_FORMAT_12H (0)
#define RTC_TIME_FORMAT_24H (1)

#define IS_RTC_TIME_FORMAT(FORMAT) (((FORMAT) == RTC_TIME_FORMAT_12H) || ((FORMAT) == RTC_TIME_FORMAT_24H))
/**
  * @}
  */

/**
  * @defgroup RTC_long_period
  * @{
  */

#define RTC_LONG_PERIOD_NO_INT (0)
#define RTC_LONG_PERIOD_0P5S   (1)
#define RTC_LONG_PERIOD_1S	   (2)
#define RTC_LONG_PERIOD_1MIN   (3)
#define RTC_LONG_PERIOD_1HOUR  (4)
#define RTC_LONG_PERIOD_1DAY   (5)
#define RTC_LONG_PERIOD_1MON   (6)

#define IS_RTC_LONG_PERIOD(PERIOD)                                                                                     \
	(((PERIOD) == RTC_LONG_PERIOD_NO_INT) || ((PERIOD) == RTC_LONG_PERIOD_0P5S) || ((PERIOD) == RTC_LONG_PERIOD_1S) || \
	 ((PERIOD) == RTC_LONG_PERIOD_1MIN) || ((PERIOD) == RTC_LONG_PERIOD_1HOUR) ||                                      \
	 ((PERIOD) == RTC_LONG_PERIOD_1DAY) || ((PERIOD) == RTC_LONG_PERIOD_1MON))
/**
  * @}
  */

/** @defgroup RTC_short_period
  * @{
  */

#define IS_RTC_SHORT_PERIOD(PERIOD) ((PERIOD) <= 0x3F)
/**
  * @}
  */

/** @defgroup RTC_calibration_compensation_value
  * @{
  */

#define IS_RTC_CALR_VAL(VAL) ((VAL) <= 0x1FF)
/**
  * @}
  */

/**
  * @defgroup RTC_period_type
  * @{
  */

#define RTC_PERIOD_TYPE_LONG  (0)
#define RTC_PERIOD_TYPE_SHORT (1)

#define IS_RTC_PERIOD_TYPE(TYPE) (((TYPE) == RTC_PERIOD_TYPE_LONG) || ((TYPE) == RTC_PERIOD_TYPE_SHORT))
/**
  * @}
  */

/**
  * @defgroup RTC_Calibration_Accuracy_Selection
  * @{
  */

#define RTC_CALR_SEL_LOW  (0)
#define RTC_CALR_SEL_HIGH (1)

#define IS_RTC_CALR_SEL(SEL) (((SEL) == RTC_CALR_SEL_LOW) || ((SEL) == RTC_CALR_SEL_HIGH))
/**
  * @}
  */

/** @defgroup RTC_interrupts_definition
  * @{
  */

#define RTC_IT_ALMIE BIT(22)
#define RTC_IT_PRDIE BIT(20)

#define RTC_IT_ALL (RTC_IT_ALMIE | RTC_IT_PRDIE)

#define IS_RTC_CONFIG_IT(IT) (((IT)&RTC_IT_ALL) && (!((IT) & (~(RTC_IT_ALL)))))

#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_ALMIE) || ((IT) == RTC_IT_PRDIE))
/**
  * @}
  */

/** @defgroup RTC_flags_definition
  * @{
  */

#define RTC_FLAG_WAITF BIT(8)
#define RTC_FLAG_PRDF  BIT(4)
#define RTC_FLAG_ALMF  BIT(0)

#define RTC_FLAG_ALL (RTC_FLAG_PRDF | RTC_FLAG_ALMF)

#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_WAITF) || ((FLAG) == RTC_FLAG_PRDF) || ((FLAG) == RTC_FLAG_ALMF))

#define IS_RTC_CLEAR_FLAG(FLAG) (((FLAG) & RTC_FLAG_ALL) && (!((FLAG) & (~(RTC_FLAG_ALL)))))
/**
  * @}
  */

/** @defgroup RTC_date_year
  * @{
  */

#define IS_RTC_DATE_YEAR(YEAR) ((YEAR) <= 99)
/**
  * @}
  */

/** @defgroup RTC_date_month
  * @{
  */

#define IS_RTC_DATE_MON(MON) (((MON) >= 1) && ((MON) <= 12))
/**
  * @}
  */

/** @defgroup RTC_date_day
  * @{
  */

#define IS_RTC_DATE_DAY(DAY) (((DAY) >= 1) && ((DAY) <= 31))
/**
  * @}
  */

/** @defgroup RTC_date_week
  * @{
  */

#define RTC_DATE_WEEK_SUN (0)
#define RTC_DATE_WEEK_MON (1)
#define RTC_DATE_WEEK_TUE (2)
#define RTC_DATE_WEEK_WED (3)
#define RTC_DATE_WEEK_THU (4)
#define RTC_DATE_WEEK_FRI (5)
#define RTC_DATE_WEEK_SAT (6)

#define IS_RTC_DATE_WEEK(WEEK)                                                                                         \
	(((WEEK) == RTC_DATE_WEEK_SUN) || ((WEEK) == RTC_DATE_WEEK_MON) || ((WEEK) == RTC_DATE_WEEK_TUE) ||                \
	 ((WEEK) == RTC_DATE_WEEK_WED) || ((WEEK) == RTC_DATE_WEEK_THU) || ((WEEK) == RTC_DATE_WEEK_FRI) ||                \
	 ((WEEK) == RTC_DATE_WEEK_SAT))
/**
  * @}
  */

/** @defgroup RTC_date_hour
  * @{
  */

#define IS_RTC_DATE_HOUR(HOUR) ((HOUR) <= 23)
/**
  * @}
  */

/** @defgroup RTC_date_minute
  * @{
  */

#define IS_RTC_DATE_MIN(MIN) ((MIN) <= 59)
/**
  * @}
  */

/** @defgroup RTC_date_second
  * @{
  */

#define IS_RTC_DATE_SEC(SEC) ((SEC) <= 59)
/**
  * @}
  */

/** @defgroup RTC_Alarm_Week
  * @{
  */

#define RTC_ALM_WEEK_SUN BIT(0)
#define RTC_ALM_WEEK_MON BIT(1)
#define RTC_ALM_WEEK_TUE BIT(2)
#define RTC_ALM_WEEK_WED BIT(3)
#define RTC_ALM_WEEK_THU BIT(4)
#define RTC_ALM_WEEK_FRI BIT(5)
#define RTC_ALM_WEEK_SAT BIT(6)

#define RTC_ALM_WEEK_ALL                                                                                               \
	(RTC_ALM_WEEK_SUN | RTC_ALM_WEEK_MON | RTC_ALM_WEEK_TUE | RTC_ALM_WEEK_WED | RTC_ALM_WEEK_THU | RTC_ALM_WEEK_FRI | \
	 RTC_ALM_WEEK_SAT)

#define IS_RTC_ALARM_WEEK(WEEK) (((WEEK)&RTC_ALM_WEEK_ALL) && (!((WEEK) & (~(RTC_ALM_WEEK_ALL)))))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions
  * @{
  */

void	   RTC_Init(RTC_InitTypeDef *RTC_InitStruct);
void	   RTC_LongPeriodConfig(u8 Period);
void	   RTC_LongPeriodConfig(u8 Period);
void	   RTC_CalibrationConfig(u16 CalibrationVal);
void	   RTC_CalibrationConfig(u16 CalibrationVal);
void	   RTC_SetPeriodType(u8 PeriodType);
void	   RTC_SetCalibrationSel(u8 CalibrationSel);
void	   RTC_AlarmCmd(FunctionalState NewState);
void	   RTC_PeriodCmd(FunctionalState NewState);
void	   RTC_WaitSyncCmd(FunctionalState NewState);
void	   RTC_CalibrationCmd(FunctionalState NewState);
void	   RTC_1HzOutCmd(FunctionalState NewState);
void	   RTC_Cmd(FunctionalState NewState);
void	   RTC_ITConfig(u32 RTC_IT, FunctionalState NewState);
FlagStatus RTC_GetFlagStatus(u16 RTC_FLAG);
ITStatus   RTC_GetITStatus(u32 RTC_IT);
void	   RTC_ClearFlag(u16 RTC_FLAG);
void	   RTC_SetAlarm(u8 Week, u8 Hour, u8 Minute);
void	   RTC_SetDate(RTC_DateDef *RTC_Date);
void	   RTC_GetDate(RTC_DateDef *RTC_Date);

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */

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

