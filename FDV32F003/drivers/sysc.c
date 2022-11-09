/**
  ******************************************************************************
  * @file    sysc.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-21
  * @brief   This file provides all the SYSC firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sysc.h"
#include "anac.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @defgroup SYSC
  * @brief SYSC driver modules
  * @{
  */

/** @defgroup SYSC_Private_Functions
  * @{
  */

/**
  * @brief  Configure the delay time when the system wakes up from deep sleep.
  * @param  Delay: Specifies the delay time for the system to wake up from deep sleep.
  *			 - delay time: T=(x)/src_clk.
  *   This parameter value must be lower than 0x200.
  * @retval None
  */
void SYSC_WakeDelayConfig(u16 Delay)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_WAKE_DELAY(Delay));

	/* Get the SYSC_CLKCTRCFG value */
	tempreg = SYSC->CLKCTRCFG;

	/* Set the delay time for the system to wake up from deep sleep */
	tempreg &= ~SYSC_CLKCTRCFG_DSP_WKUP_DLY;
	tempreg |= Delay << SYSC_CLKCTRCFG_DSP_WKUP_DLY_pos;

	/* Write to SYSC_CLKCTRCFG */
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG = tempreg;
}

/**
  * @brief  Configures the APB clock (PCLK).
  * @param  Div: Specifies the APB clock divider. 
  *         This clock is derived from the AHB clock (HCLK).
  *   This number must be between 1 and 128.
  * @retval None
  */
void SYSC_PCLKConfig(u16 Div)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_APB_DIV(Div));

	/* Get the SYSC_CLKCTRCFG value */
	tempreg = SYSC->CLKCTRCFG;

	/* Set the APB clock */
	tempreg &= ~SYSC_CLKCTRCFG_APB_CLK_DIV;
	tempreg |= (Div - 1) << SYSC_CLKCTRCFG_APB_CLK_DIV_pos;

	/* Write to SYSC_CLKCTRCFG */
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG = tempreg;
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  Div: Specifies the AHB clock divider. 
  *	  		This clock is derived from the system clock (SYSCLK).
  *   This number must be between 1 and 128.
  * @retval None
  */
void SYSC_HCLKConfig(u16 Div)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_AHB_DIV(Div));

	/* Get the SYSC_CLKCTRCFG value */
	tempreg = SYSC->CLKCTRCFG;

	/* Set the AHB clock */
	tempreg &= ~SYSC_CLKCTRCFG_AHB_CLK_DIV;
	tempreg |= (Div - 1) << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos;

	/* Write to SYSC_CLKCTRCFG */
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG = tempreg;
}

/**
  * @brief  Configures the system clock (SYSCLK).
  * @param  ClockSrc: Specifies the clock source used as system clock.
  *   This parameter can be one of the following values:
  *     @arg SYSC_SYSCLK_SOURCE_HRC: HRC selected as system clock
  *     @arg SYSC_SYSCLK_SOURCE_LRC: LRC selected as system clock
  * @retval None
  */
void SYSC_SYSCLKConfig(u8 ClockSrc)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_SYSCLK_SOURCE(ClockSrc));

	/* Get the SYSC_CLKCTRCFG value */
	tempreg = SYSC->CLKCTRCFG;

	/* Set the AHB clock */
	tempreg &= ~SYSC_CLKCTRCFG_SYS_CLK_SEL;
	tempreg |= ClockSrc << SYSC_CLKCTRCFG_SYS_CLK_SEL_pos;

	/* Write to SYSC_CLKCTRCFG */
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG = tempreg;
}

/**
  * @brief  Configure the ANAC module ADC clock(ADCCLK).
  * @param  Div: Specifies the ADC clock divider. 
  *         This clock is derived from the system clock (SYSCLK).
  *   This parameter can be SYSC_ADCCLK_DIVx, where x can be an even number between (0..30).
  * @retval None
  */
void SYSC_ADCCLKConfig(u8 Div)
{
	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_ADCCLK_DIV(Div));

	/* Set the ADC clock */
	SYSC->ADCCLKDIV &= ~SYSC_ADCCLKDIV_ADC_CLK_DIV;
	SYSC->ADCCLKDIV |= Div << SYSC_ADCCLKDIV_ADC_CLK_DIV_pos;
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval The clock source used as system clock. The returned value can
  *   be one of the following:
  *     - 0x00: HRC used as system clock
  *     - 0x01: LRC used as system clock
  */
u8 SYSC_GetSYSCLKSource(void)
{
	return ((u8)((SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_SYS_CLK_SEL) >> SYSC_CLKCTRCFG_SYS_CLK_SEL_pos));
}

/**
  * @brief  Returns the frequencies of different on chip clocks.
  * @param  SYSC_Clocks: pointer to a SYSC_ClocksTypeDef structure which will hold
  *         the clocks frequencies.
  * @retval None
  */
void SYSC_GetClocksFreq(SYSC_ClocksTypeDef *SYSC_Clocks)
{
	u32 clksrc = 0, hclkdiv = 0, pclkdiv = 0;

	/*--------------------- Compute system clocks frequencies ---------------------*/
	/* Get system clock source */
	clksrc = SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_SYS_CLK_SEL;

	/* Check the system clock source */
	if (clksrc == SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC)
	{
		/* LRC as source clock */
		SYSC_Clocks->SYSCLK_Frequency = 8000;
	}
	else
	{
		/* The clock of HRC is 8MHz */
		SYSC_Clocks->SYSCLK_Frequency = 8000000;
	}

	/*--------------------- Compute AHB clocks frequencies ---------------------*/
	/* Get the AHB bus clock divider */
	hclkdiv = ((SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_AHB_CLK_DIV) >> SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) + 1;
	/* Calculate the AHB bus clock */
	SYSC_Clocks->HCLK_Frequency = SYSC_Clocks->SYSCLK_Frequency / hclkdiv;

	/*--------------------- Compute APB clocks frequencies ---------------------*/
	/* Get the APB bus clock divider */
	pclkdiv = ((SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_APB_CLK_DIV) >> SYSC_CLKCTRCFG_APB_CLK_DIV_pos) + 1;
	/* Calculate the APB bus clock */
	SYSC_Clocks->PCLK_Frequency = SYSC_Clocks->HCLK_Frequency / pclkdiv;
}

/**
  * @brief  Enables or disables the specified WDT peripheral.
  * @param  NewState: New state of the WDT peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSC_WDTCmd(FunctionalState NewState)
{
	u32 tempreg = 0;
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the SYSC_CLKCTRCFG value */
	tempreg = SYSC->CLKCTRCFG;

	if (NewState == ENABLE)
	{
		/* Enable WDT Counter */
		tempreg |= SYSC_CLKCTRCFG_WDT_EN;
	}
	else
	{
		/* Disable WDT Counter */
		tempreg &= ~SYSC_CLKCTRCFG_WDT_EN;
	}

	/* Write to SYSC_CLKCTRCFG */
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG = tempreg;
}

/**
  * @brief  Enable or disable selected module peripheral clocks.
  * @param  MouleClocks: Specifies the selected module clock.
  *   This parameter can be any combination of the following values:
  *     @arg SYSC_MOUDLE_CLOCK_ADC: Control ADC cfg clock
  *     @arg SYSC_MOUDLE_CLOCK_LPTIM_CK: Control LPTIMER count clock
  *     @arg SYSC_MOUDLE_CLOCK_LPTIM: Control LPTIMER APB clock
  *     @arg SYSC_MOUDLE_CLOCK_WDT: Control WDT APB clock
  *     @arg SYSC_MOUDLE_CLOCK_SYSC: Control SYSC APB clock
  *     @arg SYSC_MOUDLE_CLOCK_ANAC: Control ANAC APB clock
  *     @arg SYSC_MOUDLE_CLOCK_DCLK_HCK: Control DCLK clock
  *     @arg SYSC_MOUDLE_CLOCK_IOM: Control IOM APB clock
  *     @arg SYSC_MOUDLE_CLOCK_TIM4_CNT: Control TIMER4 count clock
  *     @arg SYSC_MOUDLE_CLOCK_TIM3_CNT: Control TIMER3 count clock
  *     @arg SYSC_MOUDLE_CLOCK_TIM2_CNT: Control TIMER2 count clock
  *     @arg SYSC_MOUDLE_CLOCK_TIM1_CNT: Control TIMER1 count clock
  *     @arg SYSC_MOUDLE_CLOCK_TIM0_CNT: Control TIMER0 count clock
  *     @arg SYSC_MOUDLE_CLOCK_TIM_PCK: Control TIMER count clock
  *     @arg SYSC_MOUDLE_CLOCK_UART: Control UART APB clock
  *     @arg SYSC_MOUDLE_CLOCK_APB: Control APB clock tree
  * @param  NewState: The new state of the selected module clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSC_PeriphClockCmd(u32 MouleClocks, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_MOUDLE_CLOCK(MouleClocks));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable selected module clock */
		SYSC->CLKENCFG |= MouleClocks;
	}
	else
	{
		/* Disable selected module clock */
		SYSC->CLKENCFG &= ~MouleClocks;
	}
}

/**
  * @brief  Soft reset selected peripherals.
  * @param  Module: Specifies the selected peripheral.
  *   This parameter can be any combination of the following values:
  *     @arg SYSC_RESET_MOUDLE_DIG : Soft reset the digital (Global reset)
  *     @arg SYSC_RESET_MOUDLE_UART: Soft reset the UART module
  *     @arg SYSC_RESET_MOUDLE_ANAC: Soft reset the ANAC module
  *     @arg SYSC_RESET_MOUDLE_ADC : Soft reset the ADC module
  *     @arg SYSC_RESET_MOUDLE_HCLK: Soft reset the AHB bus
  *     @arg SYSC_RESET_MOUDLE_TIM4: Soft reset the TIM4 module
  *     @arg SYSC_RESET_MOUDLE_TIM3: Soft reset the TIM3 module
  *     @arg SYSC_RESET_MOUDLE_TIM2: Soft reset the TIM2 module
  *     @arg SYSC_RESET_MOUDLE_TIM1: Soft reset the TIM1 module
  *     @arg SYSC_RESET_MOUDLE_TIM0: Soft reset the TIM0 module
  * @retval None
  */
void SYSC_ResetPeripher(u32 Module)
{
	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_RESET_MOUDLE(Module));

	/* Write the MSFTRSTCFG register to reset the peripheral */
	SYSC_WPT_UNLOCK();
	SYSC->MSFTRSTCFG = Module;
}

/**
  * @brief  Checks whether the specified SYSC flag is set or not.
  * @param  SYSC_FLAG_TWCWK: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg SYSC_FLAG_LVDRST: LVD reset status flag
  *     @arg SYSC_FLAG_SOFTDIGRST: Soft Digital Reset status flag
  *     @arg SYSC_FLAG_EXTRST: External reset status flag
  *     @arg SYSC_FLAG_WDTRST: WDT reset status flag
  *     @arg SYSC_FLAG_PORRST: Power reset status flag
  * @retval The new state of SYSC_FLAG (SET or RESET).
  */
FlagStatus SYSC_GetFlagStatus(u16 SYSC_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_GET_FLAG(SYSC_FLAG));

	/* Check the status of the SYSC flag */
	if (SYSC->RSTSTS & SYSC_FLAG)
	{
		/* SYSC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* SYSC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the SYSC_FLAG status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for SYSC.
  * @param  SYSC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg SYSC_FLAG_LVDRST: LVD reset status flag
  *     @arg SYSC_FLAG_SOFTDIGRST: Soft Digital Reset status flag
  *     @arg SYSC_FLAG_EXTRST: External reset status flag
  *     @arg SYSC_FLAG_WDTRST: WDT reset status flag
  *     @arg SYSC_FLAG_PORRST: Power reset status flag
  * @retval None
  */
void SYSC_ClearFlag(u16 SYSC_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_CLEAR_FLAG(SYSC_FLAG));

	/* Clear the selected SYSC flags */
	SYSC->RSTSTS = SYSC_FLAG;
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
	/* Set the CUSTOMCSR0 bit in the CUSTOMCSR0 register */
	WRITE_CSR(0xbff, CUSTOMCSR0_SLEEPDEEPEN);

	/* Write command to enter deep sleep mode */
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

