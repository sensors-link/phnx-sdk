/**
  ******************************************************************************
  * @file    i2c.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-13
  * @brief   This file provides all the PMU firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "pmu.h"
#include "sysc.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @defgroup PMU
  * @brief PMU driver modules
  * @{
  */

/** @defgroup PMU_Private_Defines
  * @{
  */

/* Flags in RSTSTS register */
#define PMU_FLAGS_RSTSTS ((u32)0x0000003F)

/* IT in RSTSTS register */
#define PMU_ITS_RSTSTS ((u32)0x0000003F)

/* LPT and WDT in INTEN register */
#define PMU_LPTWDT_INTEN ((u32)0x000000C0)

/* GPIO in INTEN register */
#define PMU_GPIO_INTEN ((u32)0x00000F00)
/**
  * @}
  */

/** @defgroup PMU_Private_Functions
  * @{
  */

/**
  * @brief  Configure VDD Low Power Voltage.
  * @param  Voltage: Specify VDD Low Power Voltage.
  *   This parameter can be one of the following values:
  *     @arg PMU_VDD_LPVOL_1P5: VDD Low Power voltage selection 1.5V.
  *     @arg PMU_VDD_LPVOL_1P2: VDD Low Power voltage selection 1.2V.
  * @retval None
  */
void PMU_VDDLowPowerConfig(u8 Voltage)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_PMU_VDD_LPVOL(Voltage));

	/* Get the PMU_CR value */
	tempreg = PMU->CR;

	/* Set VDD Low Power Voltage */
	tempreg &= ~PMU_CR_VDDLPCFG;
	tempreg |= Voltage << PMU_CR_VDDLPCFG_pos;

	/* Write to PMU_CR */
	PMU_WPT_UNLOCK();
	PMU->CR = tempreg;
}

/**
  * @brief  Configure the level of GPIO wake-up.
  * @param  WKPin: Specify the pin that needs to be configured.
  *   This parameter can be any combination of the following values:
  *     @arg PMU_IOWAKE_PIN16: Wake up pin is GP16
  *     @arg PMU_IOWAKE_PIN17: Wake up pin is GP17
  *     @arg PMU_IOWAKE_PIN18: Wake up pin is GP18
  *     @arg PMU_IOWAKE_PIN19: Wake up pin is GP19
  * @param  WKLevel: Specify the GPIO wake-up level.
  *   This parameter can be one of the following values:
  *     @arg PMU_IOWAKE_LEVEL_LOW: Low level wake-up configuration
  *     @arg PMU_IOWAKE_LEVEL_HIGH: High level wake-up configuration
  * @retval None
  */
void PMU_IOWakeLevelConfig(u8 WKPin, u8 WKLevel)
{
	/* Check the parameters */
	PARAM_CHECK(IS_PMU_IOWAKE_PIN(WKPin));
	PARAM_CHECK(IS_PMU_IOWAKE_LEVEL(WKLevel));

	if (WKLevel == PMU_IOWAKE_LEVEL_LOW)
	{
		/* Set selected pin to wake-up low */
		PMU->WKCFG &= ~(WKPin << PMU_WKCFG_GPIOWKLEV_pos);
	}
	else
	{
		/* Set selected pin to wake-up high */
		PMU->WKCFG |= (WKPin << PMU_WKCFG_GPIOWKLEV_pos);
	}
}

/**
  * @brief  Set the PMU wake-up mode.
  * @param  WakeMode: Specify the PMU wake-up mode.
  *   This parameter can be one of the following values:
  *     @arg PMU_WAKE_MODE_SYNC: Synchronous wake-up mode.
  *     @arg PMU_WAKE_MODE_ASYNC: Asynchronous wake-up mode.
  * @retval None
  */
void PMU_SetWakeMode(u8 WakeMode)
{
	/* Check the parameters */
	PARAM_CHECK(IS_PMU_WAKE_MODE(WakeMode));

	/* Set the PMU wake-up mode */
	if (WakeMode == PMU_WAKE_MODE_SYNC)
	{
		/* Set PMU wake-up mode to synchronous wake-up */
		PMU->WKCFG &= ~PMU_WKCFG_PMUWKMODE;
	}
	else
	{
		/* Set PMU wake-up mode to asynchronous wake-up */
		PMU->WKCFG |= PMU_WKCFG_PMUWKMODE;
	}
}

/**
  * @brief  HRC and aLdo4d were enabled or disabled in DeepSleep mode.
  * @param  NewState: New state of HRC and aLdo4d in deep sleep mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PMU_HRCKeepAliveCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* HRC and aLDO4D Keep Alive enabled in DeepSleep mode */
		PMU_WPT_UNLOCK();
		PMU->CR |= PMU_CR_HRCKEEPALIVE;
	}
	else
	{
		/* HRC and aLDO4D Keep Alive disabled in DeepSleep mode */
		PMU_WPT_UNLOCK();
		PMU->CR &= ~PMU_CR_HRCKEEPALIVE;
	}
}

/**
  * @brief  Enable or disable the watchdog clock.
  * @param  NewState: New state of watchdog clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PMU_WDTClockCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable watchdog clock */
		PMU_WPT_UNLOCK();
		PMU->CR |= PMU_CR_WDTCLKEN;
	}
	else
	{
		/* Disable watchdog clock */
		PMU_WPT_UNLOCK();
		PMU->CR &= ~PMU_CR_WDTCLKEN;
	}
}

/**
  * @brief  Enable or disable the Low Power Timer clock.
  * @param  NewState: New state of Low Power Timer clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PMU_LPTClockCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable Low Power Timer clock */
		PMU_WPT_UNLOCK();
		PMU->CR |= PMU_CR_LPTCLKEN;
	}
	else
	{
		/* Disable Low Power Timer clock */
		PMU_WPT_UNLOCK();
		PMU->CR &= ~PMU_CR_LPTCLKEN;
	}
}

/**
  * @brief  Enable or disable the LVD chip reset.
  * @param  NewState: New state of LVD chip reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PMU_LVDResetCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable LVD chip reset */
		PMU_WPT_UNLOCK();
		PMU->CR |= PMU_CR_LVDCHIPRSTEN;
	}
	else
	{
		/* Disable LVD chip reset */
		PMU_WPT_UNLOCK();
		PMU->CR &= ~PMU_CR_LVDCHIPRSTEN;
	}
}

/**
  * @brief  Enable or disable PowerDown mode.
  * @param  NewState: New state for PowerDown mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PMU_PowerDownCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the PMU_CR value */
	tempreg = PMU->CR;

	/* Clear the PowerDown mode enable bit of the PMU_CR register */
	tempreg &= ~PMU_CR_PDNEN;

	if (NewState == ENABLE)
	{
		/* Enable PowerDown mode */
		tempreg |= PMU_CR_PDNEN_V;
	}

	/* Write to PMU_CR */
	PMU_WPT_UNLOCK();
	PMU->CR = tempreg;
}

/**
  * @brief  Enable or disable selected GPIO wake-up function.
  * @param  WKPin: Specifies the GPIO pin used for wakeup.
  *   This parameter can be any combination of the following values:
  *     @arg PMU_IOWAKE_PIN16: Wake up pin is GP16
  *     @arg PMU_IOWAKE_PIN17: Wake up pin is GP17
  *     @arg PMU_IOWAKE_PIN18: Wake up pin is GP18
  *     @arg PMU_IOWAKE_PIN19: Wake up pin is GP19
  * @param  NewState: New state for GPIO wakeup.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PMU_GPIOWakeCmd(u8 WKPin, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_PMU_IOWAKE_PIN(WKPin));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable selected GPIO wake-up function */
		PMU->WKCFG |= WKPin << PMU_WKCFG_GPIOWKEN_pos;
	}
	else
	{
		/* Disable selected GPIO wake-up function */
		PMU->WKCFG &= ~(WKPin << PMU_WKCFG_GPIOWKEN_pos);
	}
}

/**
  * @brief  Enables or disables the specified PMU interrupts.
  * @param  PMU_IT: specifies the PMU interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg PMU_IT_TWCWK: TWC wake-up flag interrupt
  *     @arg PMU_IT_GP19WK: GP19 wake-up flag interrupt
  *     @arg PMU_IT_GP18WK: GP18 wake-up flag interrupt
  *     @arg PMU_IT_GP17WK: GP17 wake-up flag interrupt
  *     @arg PMU_IT_GP16WK: GP16 wake-up flag interrupt
  *     @arg PMU_IT_LPTWK: LPTIMER wake-up flag interrupt
  *     @arg PMU_IT_WDTWK: WDT wake-up flag interrupt
  *     @arg PMU_IT_PORRST: Power reset flag interrupt
  *     @arg PMU_IT_SOFTDIGRST: Soft Digital Reset flag interrupt
  *     @arg PMU_IT_SOFTCHIPRST: Soft Chip Reset flag interrupt
  *     @arg PMU_IT_EXTRST: External reset flag interrupt
  *     @arg PMU_IT_WDTRST: WDT reset flag interrupt
  *     @arg PMU_IT_LVDRST: LVD reset flag interrupt
  * @param  NewState: new state of the specified PMU interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PMU_ITConfig(u16 PMU_IT, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_PMU_CONFIG_IT(PMU_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the selected PMU interrupts */
		PMU->INTEN |= PMU_IT;
	}
	else
	{
		/* Disable the selected PMU interrupts */
		PMU->INTEN &= ~PMU_IT;
	}
}

/**
  * @brief  Checks whether the specified PMU flag is set or not.
  * @param  PMU_FLAG_TWCWK: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg PMU_FLAG_ATCTIVESTS: The PMU is in the ACTIVE wake up state flag
  *     @arg PMU_FLAG_TWCWK: TWC wake-up status flag
  *     @arg PMU_FLAG_LPTWK: Lptimer wake-up status flag
  *     @arg PMU_FLAG_WDTWK: WDT wake-up status flag
  *     @arg PMU_FLAG_GP19WK: GP19 wake-up status flag
  *     @arg PMU_FLAG_GP18WK: GP18 wake-up status flag
  *     @arg PMU_FLAG_GP17WK: GP17 wake-up status flag
  *     @arg PMU_FLAG_GP16WK: GP16 wake-up status flag
  *     @arg PMU_FLAG_PORRST: Power reset status flag
  *     @arg PMU_FLAG_SOFTDIGRST: Soft Digital Reset status flag
  *     @arg PMU_FLAG_SOFTCHIPRST: Soft Chip Reset status flag
  *     @arg PMU_FLAG_EXTRST: External reset status flag
  *     @arg PMU_FLAG_WDTRST: WDT reset status flag
  *     @arg PMU_FLAG_LVDRST: LVD reset status flag
  * @retval The new state of PMU_FLAG (SET or RESET).
  */
FlagStatus PMU_GetFlagStatus(u16 PMU_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_PMU_GET_FLAG(PMU_FLAG));

	/* Check the flag status register */
	if (PMU_FLAG & PMU_FLAGS_RSTSTS)
	{
		/* Check the status of the PMU reset status flag */
		if (PMU->RSTSTS & (PMU_FLAG & PMU_FLAGS_RSTSTS))
		{
			/* PMU_FLAG is set */
			bitstatus = SET;
		}
		else
		{
			/* PMU_FLAG is reset */
			bitstatus = RESET;
		}
	}
	else
	{
		/* Check the status of the PMU wake-up status flag */
		if (PMU->WKSTS & (PMU_FLAG >> 6))
		{
			/* PMU_FLAG is set */
			bitstatus = SET;
		}
		else
		{
			/* PMU_FLAG is reset */
			bitstatus = RESET;
		}
	}

	/* Return the PMU_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified PMU interrupt has occurred or not.
  * @param  PMU_IT: specifies the PMU interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg PMU_IT_TWCWK: TWC wake-up flag interrupt
  *     @arg PMU_IT_LPUWK: LPUart wake-up flag interrupt
  *     @arg PMU_IT_RTCWK: RTC wake-up flag interrupt
  *     @arg PMU_IT_GP19WK: GP19 wake-up flag interrupt
  *     @arg PMU_IT_GP18WK: GP18 wake-up flag interrupt
  *     @arg PMU_IT_GP17WK: GP17 wake-up flag interrupt
  *     @arg PMU_IT_GP16WK: GP16 wake-up flag interrupt
  *     @arg PMU_IT_LPTWK: LPTIMER wake-up flag interrupt
  *     @arg PMU_IT_WDTWK: WDT wake-up flag interrupt
  *     @arg PMU_IT_PORRST: Power reset flag interrupt
  *     @arg PMU_IT_SOFTDIGRST: Soft Digital Reset flag interrupt
  *     @arg PMU_IT_SOFTCHIPRST: Soft Chip Reset flag interrupt
  *     @arg PMU_IT_EXTRST: External reset flag interrupt
  *     @arg PMU_IT_WDTRST: WDT reset flag interrupt
  *     @arg PMU_IT_LVDRST: LVD reset flag interrupt
  * @retval The new state of PMU_IT (SET or RESET).
  */
ITStatus PMU_GetITStatus(u16 PMU_IT)
{
	u8		 posbit		= 0;
	ITStatus flagstatus = RESET;
	ITStatus bitstatus	= RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_PMU_GET_IT(PMU_IT));

	/* Check the flag status register */
	if (PMU_IT & PMU_ITS_RSTSTS)
	{
		/* Check the status of the PMU reset status flag */
		if (PMU->RSTSTS & (PMU_IT & PMU_ITS_RSTSTS))
		{
			/* PMU reset status flag is set */
			flagstatus = SET;
		}
		else
		{
			/* PMU reset status flag is reset */
			flagstatus = RESET;
		}
	}
	else
	{
		/* Find the number of mobile bits */
		if (PMU_IT & PMU_LPTWDT_INTEN)
		{
			posbit = 2;
		}
		else if (PMU_IT & PMU_GPIO_INTEN)
		{
			posbit = 8;
		}
		else
		{
			posbit = 6;
		}

		/* Check the status of the PMU wake-up status flag */
		if (PMU->WKSTS & (PMU_IT >> posbit))
		{
			/* PMU wake-up status is set */
			flagstatus = SET;
		}
		else
		{
			/* PMU wake-up status is reset */
			flagstatus = RESET;
		}
	}

	/* Check the status of the specified PMU interrupt */
	if ((PMU->INTEN & PMU_IT) && flagstatus)
	{
		/* PMU_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* PMU_IT is reset */
		bitstatus = RESET;
	}

	/* Return the PMU_IT status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for PMU.
  * @param  PMU_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg PMU_FLAG_TWCWK: TWC wake-up status flag
  *     @arg PMU_FLAG_LPTWK: Lptimer wake-up status flag
  *     @arg PMU_FLAG_WDTWK: WDT wake-up status flag
  *     @arg PMU_FLAG_GP19WK: GP19 wake-up status flag
  *     @arg PMU_FLAG_GP18WK: GP18 wake-up status flag
  *     @arg PMU_FLAG_GP17WK: GP17 wake-up status flag
  *     @arg PMU_FLAG_GP16WK: GP16 wake-up status flag
  *     @arg PMU_FLAG_PORRST: Power reset status flag
  *     @arg PMU_FLAG_SOFTDIGRST: Soft Digital Reset status flag
  *     @arg PMU_FLAG_SOFTCHIPRST: Soft Chip Reset status flag
  *     @arg PMU_FLAG_EXTRST: External reset status flag
  *     @arg PMU_FLAG_WDTRST: WDT reset status flag
  *     @arg PMU_FLAG_LVDRST: LVD reset status flag
  * @retval None
  */
void PMU_ClearFlag(u16 PMU_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_PMU_CLEAR_FLAG(PMU_FLAG));

	/* Clear the selected PMU reset status flags */
	PMU->RSTSTS = PMU_FLAG & PMU_FLAGS_RSTSTS;

	/* Clear the selected PMU wake-up status flags */
	PMU->WKSTS = PMU_FLAG >> 6;
}

/**
  * @brief  PMU soft reset the Digital.
  * @note   Only valid for DIG power domain.
  * @param  None
  * @retval None
  */
void PMU_SoftDigitalReset(void)
{
	/* Set Digital Soft Reset */
	PMU_WPT_UNLOCK();
	PMU->SOFTRST |= PMU_SOFTRST_DIG;
}

/**
  * @brief  PMU soft reset the chip.
  * @note   Valid for both AWO and DIG power domains.
  * @param  None
  * @retval None
  */
void PMU_SoftChipReset(void)
{
	/* Set Chip Soft Reset */
	PMU_WPT_UNLOCK();
	PMU->SOFTRST |= PMU_SOFTRST_CHIP;
}

/**
  * @brief  PMU soft reset the core.
  * @param  None
  * @retval None
  */
void PMU_SoftCoreReset(void)
{
	/* Write the CUSTOMCSR0 register to reset the core */
	SET_CSR(0xbff, CUSTOMCSR0_SYSRESETREQ);
}

/**
  * @brief  PMU enters sleep mode.
  * @param  None
  * @retval None
  */
void PMU_EnterSleep(void)
{
	/* Disable PowerDown mode */
	PMU_PowerDownCmd(DISABLE);

	/* Clear the CUSTOMCSR0 bit in the CUSTOMCSR0 register */
	CLEAR_CSR(0xbff, CUSTOMCSR0_SLEEPDEEPEN);

	/* Write command to enter sleep mode */
	asm volatile("wfi");
}

/**
  * @brief  PMU enters deep sleep mode.
  * @param  None
  * @retval None
  */
void PMU_EnterDeepSleep(void)
{
	/* Disable PowerDown mode */
	PMU_PowerDownCmd(DISABLE);

	/* Set the CUSTOMCSR0 bit in the CUSTOMCSR0 register */
	WRITE_CSR(0xbff, CUSTOMCSR0_SLEEPDEEPEN);

	/* Write command to enter deep sleep mode */
	asm volatile("wfi");
}

/**
  * @brief  PMU enters power down mode.
  * @param  None
  * @retval None
  */
void PMU_EnterPowerDown(void)
{
	/* Enable PowerDown mode */
	PMU_PowerDownCmd(ENABLE);

	/* Clear the CUSTOMCSR0 bit in the CUSTOMCSR0 register */
	CLEAR_CSR(0xbff, CUSTOMCSR0_SLEEPDEEPEN);

	/* Write command to enter power down mode */
	asm volatile("wfi");
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

