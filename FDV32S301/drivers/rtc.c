/**
  ******************************************************************************
  * @file    rtc.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-15
  * @brief   This file provides all the RTC firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"
#include "sysc.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC
  * @brief RTC driver modules
  * @{
  */

/** @defgroup RTC_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the RTC peripheral according to the specified parameters
  *         in the RTC_InitStruct.
  * @param  RTC_InitStruct: pointer to an RTC_InitTypeDef structure that contains
  *         the configuration information for the RTC peripheral.
  * @retval None
  */
void RTC_Init(RTC_InitTypeDef *RTC_InitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_RTC_CLOCK_SOURCE(RTC_InitStruct->RTC_ClockSrc));
	PARAM_CHECK(IS_RTC_TIME_FORMAT(RTC_InitStruct->RTC_TimeFormat));

	/* Get the RTC_CON value */
	tempreg = RTC->CON;

	/* Set RTC clock source selection */
	tempreg &= ~RTC_CON_CKSEL;
	tempreg |= RTC_InitStruct->RTC_ClockSrc << RTC_CON_CKSEL_pos;

	/* Set the RTC time display format */
	if (RTC_InitStruct->RTC_TimeFormat == RTC_TIME_FORMAT_12H)
	{
		/* Set the RTC time display format to 12-hour format */
		tempreg &= ~RTC_CON_FMT;
	}
	else
	{
		/* Set the RTC time display format to 24-hour format */
		tempreg |= RTC_CON_FMT;
	}

	/* Write to RTC_CON */
	RTC_WPT_UNLOCK();
	RTC->CON = tempreg;
}

/**
  * @brief  Configure the interval at which long-period interrupts are generated.
  * @param  Period: Specifies the time interval at which long-period interrupts are generated.
  *   This parameter can be one of the following values:
  *     @arg RTC_LONG_PERIOD_NO_INT: No periodic interrupt is generated
  *     @arg RTC_LONG_PERIOD_0P5S: 0.5 seconds to generate periodic interrupt
  *     @arg RTC_LONG_PERIOD_1S: 1 second to generate periodic interrupt
  *     @arg RTC_LONG_PERIOD_1MIN: 1 minute to generate periodic interrupt
  *     @arg RTC_LONG_PERIOD_1HOUR: 1 hour to generate periodic interrupt
  *     @arg RTC_LONG_PERIOD_1DAY: 1 day to generate periodic interrupt
  *     @arg RTC_LONG_PERIOD_1MON: 1 month to generate periodic interrupt
  * @retval None
  */
void RTC_LongPeriodConfig(u8 Period)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_RTC_LONG_PERIOD(Period));

	/* Get the RTC_CON value */
	tempreg = RTC->CON;

	/* Sets the time interval for generating long-period interrupts */
	tempreg &= ~RTC_CON_PRDS;
	tempreg |= Period << RTC_CON_PRDS_pos;

	/* Write to RTC_CON */
	RTC_WPT_UNLOCK();
	RTC->CON = tempreg;
}

/**
  * @brief  Configure the interval at which short-period interrupts are generated.
  * @param  Period: Specifies the time interval at which short-period interrupts are generated.
  *    - time interval: interval = Period*0.5s.
  *   This parameter value must be lower than 0x40.
  * @retval None
  */
void RTC_ShortPeriodConfig(u8 Period)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_RTC_SHORT_PERIOD(Period));

	/* Get the RTC_CON value */
	tempreg = RTC->CON;

	/* Sets the time interval for generating short-period interrupts */
	tempreg &= ~RTC_CON_PRDX;
	tempreg |= Period << RTC_CON_PRDX_pos;

	/* Write to RTC_CON */
	RTC_WPT_UNLOCK();
	RTC->CON = tempreg;
}

/**
  * @brief  Configure RTC Clock Error Calibration Compensation Value.
  * @param  CalibrationVal: Specifies the RTC clock error calibration compensation value.
  *   This parameter value must be lower than 0x200.
  * @retval None
  */
void RTC_CalibrationConfig(u16 CalibrationVal)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_RTC_CALR_VAL(CalibrationVal));

	/* Get the RTC_CALR value */
	tempreg = RTC->CALR;

	/* Set the RTC clock error calibration compensation value */
	tempreg &= ~RTC_CALR_CR;
	tempreg |= CalibrationVal << RTC_CALR_CR_pos;

	/* Write to RTC_CALR */
	RTC_WPT_UNLOCK();
	RTC->CALR = tempreg;
}

/**
  * @brief  Set the type selection of the periodic interrupt interval.
  * @param  PeriodType: Specifies the type of periodic interrupt interval.
  *   This parameter can be one of the following values:
  *     @arg RTC_PERIOD_TYPE_LONG: Long Period Interrupt Interval
  *     @arg RTC_PERIOD_TYPE_SHORT: Short Period Interrupt Interval
  * @retval None
  */
void RTC_SetPeriodType(u8 PeriodType)
{
	/* Check the parameters */
	PARAM_CHECK(IS_RTC_PERIOD_TYPE(PeriodType));

	/* Set the type selection of the periodic interrupt interval */
	if (PeriodType == RTC_PERIOD_TYPE_LONG)
	{
		/* Set to Long Period Interrupt Interval */
		RTC_WPT_UNLOCK();
		RTC->CON &= ~RTC_CON_PRDSEL;
	}
	else
	{
		/* Set to Short Period Interrupt Interval */
		RTC_WPT_UNLOCK();
		RTC->CON |= RTC_CON_PRDSEL;
	}
}

/**
  * @brief  Set Clock Error Calibration Register Calibration Accuracy Selection.
  * @param  CalibrationSel: Specify Calibration Accuracy Selection.
  *   This parameter can be one of the following values:
  *     @arg RTC_CALR_SEL_LOW: Normal precision 1Hz output (slow clock LRC/XTL calibration)
  *     @arg RTC_CALR_SEL_HIGH: High precision 1Hz output (fast clock XTH calibration)
  * @retval None
  */
void RTC_SetCalibrationSel(u8 CalibrationSel)
{
	/* Check the parameters */
	PARAM_CHECK(IS_RTC_CALR_SEL(CalibrationSel));

	/* Set Calibration Accuracy Selection */
	if (CalibrationSel == RTC_CALR_SEL_LOW)
	{
		/* Set to normal precision 1Hz output */
		RTC_WPT_UNLOCK();
		RTC->CALR &= ~RTC_CALR_CAL_SEL;
	}
	else
	{
		/* Set to high precision 1Hz output */
		RTC_WPT_UNLOCK();
		RTC->CALR |= RTC_CALR_CAL_SEL;
	}
}

/**
  * @brief  Enable or disable RTC alarm function configuration.
  * @param  NewState: New state of the RTC alarm function.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_AlarmCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable RTC alarm function */
		RTC_WPT_UNLOCK();
		RTC->CON |= RTC_CON_ALMEN;
	}
	else
	{
		/* Disable RTC alarm function */
		RTC_WPT_UNLOCK();
		RTC->CON &= ~RTC_CON_ALMEN;
	}
}

/**
  * @brief  Enable or disable the RTC period function configuration.
  * @param  NewState: New state of the RTC period function.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_PeriodCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable RTC period function */
		RTC_WPT_UNLOCK();
		RTC->CON |= RTC_CON_PRDEN;
	}
	else
	{
		/* Disable RTC period function */
		RTC_WPT_UNLOCK();
		RTC->CON &= ~RTC_CON_PRDEN;
	}
}

/**
  * @brief  Enable or disable RTC waiting for synchronization configuration.
  * @param  NewState: New state of the RTC waiting for synchronization.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WaitSyncCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable RTC waiting for synchronization */
		RTC_WPT_UNLOCK();
		RTC->CON |= RTC_CON_WAIT;
	}
	else
	{
		/* Disable RTC waiting for synchronization */
		RTC_WPT_UNLOCK();
		RTC->CON &= ~RTC_CON_WAIT;
	}
}

/**
  * @brief  Enable or disable the RTC calibration function configuration.
  * @param  NewState: New state of the RTC calibration function.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_CalibrationCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable RTC calibration function */
		RTC_WPT_UNLOCK();
		RTC->CALR |= RTC_CALR_CAL_EN;
	}
	else
	{
		/* Disable RTC calibration function */
		RTC_WPT_UNLOCK();
		RTC->CALR &= ~RTC_CALR_CAL_EN;
	}
}

/**
  * @brief  Enable or enable RTC 1Hz output.
  * @param  NewState: New state of RTC 1Hz output.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_1HzOutCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable RTC 1Hz output */
		RTC_WPT_UNLOCK();
		RTC->CALR |= RTC_CALR_1HZ_OE;
	}
	else
	{
		/* Disable RTC 1Hz output */
		RTC_WPT_UNLOCK();
		RTC->CALR &= ~RTC_CALR_1HZ_OE;
	}
}

/**
  * @brief  Enables or disables the specified RTC peripheral.
  * @param  NewState: New state of the RTC peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable RTC peripheral */
		RTC_WPT_UNLOCK();
		RTC->CON |= RTC_CON_RTCEN;
	}
	else
	{
		/* Disable RTC peripheral */
		RTC_WPT_UNLOCK();
		RTC->CON &= ~RTC_CON_RTCEN;
	}
}

/**
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  RTC_IT: specifies the RTC interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_IT_ALMIE: Alarm interrupt
  *     @arg RTC_IT_PRDIE: Periodic interrupt
  * @param  NewState: new state of the specified RTC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_ITConfig(u32 RTC_IT, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_RTC_CONFIG_IT(RTC_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the selected RTC interrupts */
		RTC_WPT_UNLOCK();
		RTC->CON |= RTC_IT;
	}
	else
	{
		/* Disable the selected RTC interrupts */
		RTC_WPT_UNLOCK();
		RTC->CON &= ~RTC_IT;
	}
}

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg RTC_FLAG_WAITF: WAIT set valid flag
  *     @arg RTC_FLAG_PRDF: Periodic interrupt status flag
  *     @arg RTC_FLAG_ALMF: Alarm interrupt status flag
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
FlagStatus RTC_GetFlagStatus(u16 RTC_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_RTC_GET_FLAG(RTC_FLAG));

	/* Check the status of the RTC flag */
	if (RTC->STS & RTC_FLAG)
	{
		/* RTC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* RTC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the RTC_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTC_IT: specifies the RTC interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg RTC_IT_ALMIE: Alarm interrupt
  *     @arg RTC_IT_PRDIE: Periodic interrupt
  * @retval The new state of RTC_IT (SET or RESET).
  */
ITStatus RTC_GetITStatus(u32 RTC_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_RTC_GET_IT(RTC_IT));

	/* Check the status of the specified RTC interrupt */
	if ((RTC->CON & RTC_IT) && (RTC_IT == RTC_IT_ALMIE) && (RTC->STS & RTC_STS_ALMF))
	{
		/* RTC_IT is set */
		bitstatus = SET;
	}
	else if ((RTC->CON & RTC_IT) && (RTC_IT == RTC_IT_PRDIE) && (RTC->STS & RTC_STS_PRDF))
	{
		/* RTC_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* RTC_IT is reset */
		bitstatus = RESET;
	}
	/* Return the RTC_IT status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for RTC.
  * @param  RTC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_FLAG_PRDF: Periodic interrupt status flag
  *     @arg RTC_FLAG_ALMF: Alarm interrupt status flag
  * @retval None
  */
void RTC_ClearFlag(u16 RTC_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_RTC_CLEAR_FLAG(RTC_FLAG));

	/* Clear the selected RTC flags */
	RTC->STS = RTC_FLAG;
}

/**
  * @brief  Set the alarm configuration of the RTC peripheral.
  * @param  Week: Specifies the weekly match value for the alarm.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_ALM_WEEK_SUN: Weekly alarm matching value is Sunday
  *     @arg RTC_ALM_WEEK_MON: Weekly alarm matching value is Monday
  *     @arg RTC_ALM_WEEK_TUE: Weekly alarm matching value is Tuesday
  *     @arg RTC_ALM_WEEK_WED: Weekly alarm matching value is Wednesday
  *     @arg RTC_ALM_WEEK_THU: Weekly alarm matching value is Thursday
  *     @arg RTC_ALM_WEEK_FRI: Weekly alarm matching value is Friday
  *     @arg RTC_ALM_WEEK_SAT: Weekly alarm matching value is Saturday
  * @param  Hour: Specifies the hour match value for the alarm.
  *   This parameter value must be lower than 24.
  * @param  Minute: Specifies the minute match value for the alarm.
  *   This parameter value must be lower than 60.
  * @retval None
  */
void RTC_SetAlarm(u8 Week, u8 Hour, u8 Minute)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_RTC_ALARM_WEEK(Week));
	PARAM_CHECK(IS_RTC_DATE_HOUR(Hour));
	PARAM_CHECK(IS_RTC_DATE_MIN(Minute));

	/* Check the RTC time display format */
	if (!(RTC->CON & RTC_CON_FMT))
	{
		/* Converted to 12-hour format */
		if (Hour > 11)
		{
			/* PM */
			if (Hour > 12)
			{
				Hour -= 12;
			}
			Hour += 20;
		}

		/* 0 hour convert */
		if (Hour == 0)
		{
			Hour = 12;
		}
	}

	/* Calculate the value written to the register */
	tempreg = (Week << RTC_ALM_ALMWEEK_pos) | (Hour / 10 << RTC_ALM_ALMHOURH_pos) |
			  (Hour % 10 << RTC_ALM_ALMHOURL_pos) | (Minute / 10 << RTC_ALM_ALMMINH_pos) |
			  (Minute % 10 << RTC_ALM_ALMMINL_pos);

	/* Check if RTC is running */
	if (RTC->CON & RTC_CON_RTCEN)
	{
		/* RTC is running and needs to wait for a sync operation */
		RTC_WaitSyncCmd(ENABLE);
		while (RTC_GetFlagStatus(RTC_FLAG_WAITF) == RESET)
			;
	}

	/* Set the RTC alarm register ALM */
	RTC_WPT_UNLOCK();
	RTC->ALM = tempreg;

	/* Check if RTC is running */
	if (RTC->CON & RTC_CON_RTCEN)
	{
		/* RTC is running and needs to be disabled waiting for a sync operation */
		RTC_WaitSyncCmd(DISABLE);
		while (RTC_GetFlagStatus(RTC_FLAG_WAITF) == RESET)
			;
	}
}

/**
  * @brief  Set the RTC date according to the parameters specified in RTC_InitStruct.
  * @param  RTC_Date: Pointer to an RTC_DateDef structure that packs
  *         RTC date configuration information.
  * @retval None
  */
void RTC_SetDate(RTC_DateDef *RTC_Date)
{
	u32 tempreg1 = 0, tempreg2 = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_RTC_DATE_YEAR(RTC_Date->RTC_Year));
	PARAM_CHECK(IS_RTC_DATE_MON(RTC_Date->RTC_Mon));
	PARAM_CHECK(IS_RTC_DATE_DAY(RTC_Date->RTC_Day));
	PARAM_CHECK(IS_RTC_DATE_WEEK(RTC_Date->RTC_Week));
	PARAM_CHECK(IS_RTC_DATE_HOUR(RTC_Date->RTC_Hour));
	PARAM_CHECK(IS_RTC_DATE_MIN(RTC_Date->RTC_Min));
	PARAM_CHECK(IS_RTC_DATE_SEC(RTC_Date->RTC_Sec));

	/* Check the RTC time display format */
	if (!(RTC->CON & RTC_CON_FMT))
	{
		/* Converted to 12-hour format */
		if (RTC_Date->RTC_Hour > 11)
		{
			/* PM */
			if (RTC_Date->RTC_Hour > 12)
			{
				RTC_Date->RTC_Hour -= 12;
			}
			RTC_Date->RTC_Hour += 20;
		}

		/* 0 hour convert */
		if (RTC_Date->RTC_Hour == 0)
		{
			RTC_Date->RTC_Hour = 12;
		}
	}

	/* Calculate the value written to the register */
	tempreg1 = ((RTC_Date->RTC_Year / 10) << RTC_DR_YEARH_pos) | ((RTC_Date->RTC_Year % 10) << RTC_DR_YEARL_pos) |
			   ((RTC_Date->RTC_Mon / 10) << RTC_DR_MONH_pos) | ((RTC_Date->RTC_Mon % 10) << RTC_DR_MONL_pos) |
			   ((RTC_Date->RTC_Day / 10) << RTC_DR_DAYH_pos) | ((RTC_Date->RTC_Day % 10) << RTC_DR_DAYL_pos) |
			   ((RTC_Date->RTC_Week) << RTC_DR_WEEK_pos);
	tempreg2 = ((RTC_Date->RTC_Hour / 10) << RTC_TR_HOURH_pos) | ((RTC_Date->RTC_Hour % 10) << RTC_TR_HOURL_pos) |
			   ((RTC_Date->RTC_Min / 10) << RTC_TR_MINH_pos) | ((RTC_Date->RTC_Min % 10) << RTC_TR_MINL_pos) |
			   ((RTC_Date->RTC_Sec / 10) << RTC_TR_SECH_pos) | ((RTC_Date->RTC_Sec % 10) << RTC_TR_SECL_pos);

	/* Check if RTC is running */
	if (RTC->CON & RTC_CON_RTCEN)
	{
		/* RTC is running and needs to wait for a sync operation */
		RTC_WaitSyncCmd(ENABLE);
		while (RTC_GetFlagStatus(RTC_FLAG_WAITF) == RESET)
			;
	}

	/* Set the RTC date register DR */
	RTC_WPT_UNLOCK();
	RTC->DR = tempreg1;

	/* Set the RTC date register TR */
	RTC_WPT_UNLOCK();
	RTC->TR = tempreg2;

	/* Check if RTC is running */
	if (RTC->CON & RTC_CON_RTCEN)
	{
		/* RTC is running and needs to be disabled waiting for a sync operation */
		RTC_WaitSyncCmd(DISABLE);
		while (RTC_GetFlagStatus(RTC_FLAG_WAITF) == SET)
			;
	}
}

/**
  * @brief  Get the RTC date into the parameter specified by RTC_InitStruct.
  * @param  RTC_Date: Pointer to an RTC_DateDef structure to obtain RTC date information.
  * @retval None
  */
void RTC_GetDate(RTC_DateDef *RTC_Date)
{
	u32 tempreg1 = 0, tempreg2 = 0;

	/* Check if RTC is running */
	if (RTC->CON & RTC_CON_RTCEN)
	{
		/* RTC is running and needs to wait for a sync operation */
		RTC_WaitSyncCmd(ENABLE);
		while (RTC_GetFlagStatus(RTC_FLAG_WAITF) == RESET)
			;
	}

	while (1)
	{
		/* Get the RTC date register DR */
		tempreg1 = RTC->DR;

		/* Get the RTC date register TR */
		tempreg2 = RTC->TR;

		if (tempreg2 == RTC->TR)
			break;
	}

	/* Check if RTC is running */
	if (RTC->CON & RTC_CON_RTCEN)
	{
		/* RTC is running and needs to be disabled waiting for a sync operation */
		RTC_WaitSyncCmd(DISABLE);
		while (RTC_GetFlagStatus(RTC_FLAG_WAITF) == SET)
			;
	}

	/* Convert and fill the value of the register into the structure RTC_Date */
	RTC_Date->RTC_Year =
		((tempreg1 & RTC_DR_YEARH) >> RTC_DR_YEARH_pos) * 10 + ((tempreg1 & RTC_DR_YEARL) >> RTC_DR_YEARL_pos);
	RTC_Date->RTC_Mon =
		((tempreg1 & RTC_DR_MONH) >> RTC_DR_MONH_pos) * 10 + ((tempreg1 & RTC_DR_MONL) >> RTC_DR_MONL_pos);
	RTC_Date->RTC_Day =
		((tempreg1 & RTC_DR_DAYH) >> RTC_DR_DAYH_pos) * 10 + ((tempreg1 & RTC_DR_DAYL) >> RTC_DR_DAYL_pos);
	RTC_Date->RTC_Week = (tempreg1 & RTC_DR_WEEK) >> RTC_DR_WEEK_pos;
	RTC_Date->RTC_Hour =
		((tempreg2 & RTC_TR_HOURH) >> RTC_TR_HOURH_pos) * 10 + ((tempreg2 & RTC_TR_HOURL) >> RTC_TR_HOURL_pos);
	RTC_Date->RTC_Min =
		((tempreg2 & RTC_TR_MINH) >> RTC_TR_MINH_pos) * 10 + ((tempreg2 & RTC_TR_MINL) >> RTC_TR_MINL_pos);
	RTC_Date->RTC_Sec =
		((tempreg2 & RTC_TR_SECH) >> RTC_TR_SECH_pos) * 10 + ((tempreg2 & RTC_TR_SECL) >> RTC_TR_SECL_pos);

	/* Check the RTC time display format */
	if (!(RTC->CON & RTC_CON_FMT))
	{
		/* Converted to 24-hour format */
		if (RTC_Date->RTC_Hour == 12)
		{
			/* 0 hour convert */
			RTC_Date->RTC_Hour = 0;
		}

		/* PM */
		if (RTC_Date->RTC_Hour > 20)
		{
			RTC_Date->RTC_Hour -= 20;

			/* value conversion */
			if (RTC_Date->RTC_Hour < 12)
			{
				RTC_Date->RTC_Hour += 12;
			}
		}
	}
}

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

