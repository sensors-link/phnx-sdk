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

/** @addtogroup FDV32S302_StdPeriph_Driver
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
  *			 - delay time: T=(x+3)/src_clk.
  * @retval None
  */
void SYSC_WakeDelayConfig(u8 Delay)
{
	u32 tempreg = 0;

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
void SYSC_PCLKConfig(u8 Div)
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
void SYSC_HCLKConfig(u8 Div)
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
  *   This parameter can be SYSC_ADCCLK_DIVx, where x can be an even number between (2..32).
  * @note   The ADCCLK should be a multiple of and greater than 500KHz due to the need to 
  *         provide a 500KHz clock for the ANAC module.
  * @retval None
  */
void SYSC_ADCCLKConfig(u8 Div)
{
	u32 tempreg = 0, tempdiv = 0;
	SYSC_ClocksTypeDef SYSC_Clocks;

	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_ADCCLK_DIV(Div));

	/* Get the SYSC_ANCLKDIV value */
	tempreg = SYSC->ANCLKDIV;

	/* Set the ADC clock */
	tempreg &= ~SYSC_ANCLKDIV_ADC_CLK_DIV;
	tempreg |= Div << SYSC_ANCLKDIV_ADC_CLK_DIV_pos;

	/* Get system clock */
	SYSC_GetClocksFreq(&SYSC_Clocks);

	/* Calculate the 500KHz clock frequency division of the ANAC module */
	tempdiv = SYSC_Clocks.SYSCLK_Frequency / 1000 / ((Div + 1) * 2) / 500-1;

	/* Check the 500KHz clock frequency division */
	PARAM_CHECK(IS_SYSC_ADC500KCLK_DIV(tempdiv));

	/* Set ANAC module 500KHz clock */
	tempreg &= ~SYSC_ANCLKDIV_500K_CLK_DIV;
	tempreg |= tempdiv << SYSC_ANCLKDIV_500K_CLK_DIV_pos;

	/* Write to SYSC_ANCLKDIV */
	SYSC->ANCLKDIV = tempreg;
}

/**
  * @brief  Configures the TIMER clock (TIMCLK).
  * @param  TimerSel: Specifies the timer selection to be configured.
  *   This parameter can be one of the following values:
  *     @arg SYSC_TIMSEL_TIM1: Select TIM1 for the timer to be configured
  *     @arg SYSC_TIMSEL_TIM2: Select TIM2 for the timer to be configured
  * @param  Div: Specifies the TIMER clock divider. 
  *         This clock is derived from the system clock (PCLK).
  *   This number must be between 1 and 256.
  * @retval None
  */
void SYSC_TIMCLKConfig(u8 TimerSel, u16 Div)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_SYSC_TIM_SEL(TimerSel));
	PARAM_CHECK(IS_SYSC_TIM_DIV(Div));

	/* Get the SYSC_TIMCLKDIV value */
	tempreg = SYSC->TIMCLKDIV;

	/* Set the TIMER clock */
	if(TimerSel == SYSC_TIMSEL_TIM1)
	{
		tempreg &= ~SYSC_TIMCLKDIV_TIM1_DIV;
		tempreg |= (Div - 1) << SYSC_TIMCLKDIV_TIM1_DIV_pos;
	}
	else
	{
		tempreg &= ~SYSC_TIMCLKDIV_TIM2_DIV;
		tempreg |= (Div - 1) << SYSC_TIMCLKDIV_TIM2_DIV_pos;
	}

	/* Write to SYSC_TIMCLKDIV */
	SYSC->TIMCLKDIV = tempreg;
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
	u32 clksrc = 0, hrcsel = 0, hclkdiv = 0, pclkdiv = 0;

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
		/* Get HRC as the clock selection gear of the source clock */
		hrcsel = ANAC->CLK_CFG & ANAC_CLK_CFG_HRC_FSEL;

		/* Check the clock selection gear of HRC as the source clock */
		if (hrcsel == ANAC_CLK_CFG_HRC_FSEL_1M)
		{
			/* The clock of HRC is 1MHz */
			SYSC_Clocks->SYSCLK_Frequency = 1000000;
		}
		else if (hrcsel == ANAC_CLK_CFG_HRC_FSEL_2M)
		{
			/* The clock of HRC is 2MHz */
			SYSC_Clocks->SYSCLK_Frequency = 2000000;
		}
		else if (hrcsel == ANAC_CLK_CFG_HRC_FSEL_4M)
		{
			/* The clock of HRC is 4MHz */
			SYSC_Clocks->SYSCLK_Frequency = 4000000;
		}
		else if (hrcsel == ANAC_CLK_CFG_HRC_FSEL_8M)
		{
			/* The clock of HRC is 8MHz */
			SYSC_Clocks->SYSCLK_Frequency = 8000000;
		}
		else if (hrcsel == ANAC_CLK_CFG_HRC_FSEL_16M)
		{
			/* The clock of HRC is 16MHz */
			SYSC_Clocks->SYSCLK_Frequency = 16000000;
		}
		else
		{
			/* The clock of HRC is 8MHz */
			SYSC_Clocks->SYSCLK_Frequency = 8000000;
		}
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
  * @brief  Enable or disable a delay in entering deep sleep.
  * @param  NewState: New state of delay in entering deep sleep.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSC_DelayEnterDSPCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the SYSC_CLKCTRCFG value */
	tempreg = SYSC->CLKCTRCFG;

	if (NewState == ENABLE)
	{
		/* Enable a delay in entering deep sleep */
		tempreg |= SYSC_CLKCTRCFG_DPS_ENT_DLY_EN;
	}
	else
	{
		/* Disable  a delay in entering deep sleep */
		tempreg &= ~SYSC_CLKCTRCFG_DPS_ENT_DLY_EN;
	}
	/* Write to SYSC_CLKCTRCFG */
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG = tempreg;
}

/**
  * @brief  Enable or disable selected module peripheral clocks.
  * @param  MouleClocks: Specifies the selected module clock.
  *   This parameter can be any combination of the following values:
  *     @arg SYSC_MOUDLE_CLOCK_TWC_MRCK: Control TWC mrc clock
  *     @arg SYSC_MOUDLE_CLOCK_TWC: Control TWC APB clock
  *     @arg SYSC_MOUDLE_CLOCK_LPTIM: Control LPTIMER APB clock
  *     @arg SYSC_MOUDLE_CLOCK_WDT: Control WDT APB clock
  *     @arg SYSC_MOUDLE_CLOCK_PMU: Control PMU APB clock
  *     @arg SYSC_MOUDLE_CLOCK_ANAC: Control ANAC APB clock
  *     @arg SYSC_MOUDLE_CLOCK_DCLK: Control DCLK clock
  *     @arg SYSC_MOUDLE_CLOCK_IOM: Control IOM APB clock
  *     @arg SYSC_MOUDLE_CLOCK_TIM2: Control TIMER2 count clock
  *     @arg SYSC_MOUDLE_CLOCK_TIM1: Control TIMER1 count clock
  *     @arg SYSC_MOUDLE_CLOCK_TIMER: Control TIMER APB clock
  *     @arg SYSC_MOUDLE_CLOCK_UART2: Control UART2 APB clock
  *     @arg SYSC_MOUDLE_CLOCK_UART1: Control UART1 APB clock
  *     @arg SYSC_MOUDLE_CLOCK_SPI: Control SPI APB clock
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
  *     @arg SYSC_RESET_MOUDLE_TWC: Soft reset the TWC module
  *     @arg SYSC_RESET_MOUDLE_ANAC: Soft reset the ANAC module
  *     @arg SYSC_RESET_MOUDLE_HCLK: Soft reset the AHB bus
  *     @arg SYSC_RESET_MOUDLE_TIMER: Soft reset the TIMER module
  *     @arg SYSC_RESET_MOUDLE_UART2: Soft reset the UART2 module
  *     @arg SYSC_RESET_MOUDLE_UART1: Soft reset the UART1 module
  *     @arg SYSC_RESET_MOUDLE_SPI: Soft reset the SPI module
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
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

