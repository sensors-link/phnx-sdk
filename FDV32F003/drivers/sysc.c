/**
 * @file sysc.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "sysc.h"

/**
 * @brief select system clock source
 *
 * @param clkSrc :SYSC_CLK_SRC_HRC  , SYSC_CLK_SRC_LRC
 */
void SYSC_SelectClockSource(int clkSrc)
{
	PARAM_CHECK((clkSrc != SYSC_CLK_SRC_HRC) && (clkSrc != SYSC_CLK_SRC_LRC));
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG &= ~SYSC_CLKCTRCFG_SYS_CLK_SEL;
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG |= (clkSrc << 0);
}

/**
 * @brief set APB clk div
 *
 * @param div :DIV1-128
 */
void SYSC_SetAPBCLKDiv(int div)
{
	PARAM_CHECK((div < DIV1) || (div > DIV128));
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG &= ~SYSC_CLKCTRCFG_APB_CLK_DIV;
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG |= (div << SYSC_CLKCTRCFG_APB_CLK_DIV_pos);
}
/**
 * @brief set AHB clk div
 *
 * @param div :DIV1-128
 */
void SYSC_SetAHBCLKDiv(int div)
{
	PARAM_CHECK((div < DIV1) || (div > DIV128));
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG &= ~SYSC_CLKCTRCFG_AHB_CLK_DIV;
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG |= (div << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos);
}

/**
 * @brief :reset peripher
 *
 * @param module: surport '|' combine
 *
 *  PRST_XX,
 *
 */
void SYSC_ResetPeripher(eRSTP_Type module)
{
	int i;
	SYSC_WPT_UNLOCK();
	SYSC->MSFTRSTCFG = module;
	for (i = 5; i > 0; --i)
		;
}

/**
 * @brief peripher clock enable
 *
 * @param perp :surport '|' combine
 * PCLK_EN_xx
 */
void SYSC_PCLKEnable(ePCLKEN_Type perp)
{
	SYSC->CLKENCFG |= perp;
}
/**
 * @brief peripher clock disable
 *
 * @param perp :surport '|' combine
 * PCLK_EN_xx
 */
void SYSC_PCLKDisable(ePCLKEN_Type perp)
{
	SYSC->CLKENCFG &= ~perp;
}

/**
 * @brief set anac , adc module clock div
 *
 * @param div : val:0-15 ==> div0-30  even
 */
void SYSC_SetADC_CLKDiv(int div)
{
	SYSC->ADCCLKDIV &= ~SYSC_ADC_SCLK_DIV;
	SYSC->ADCCLKDIV |= div << SYSC_ADC_SCLK_DIV_pos;
}
