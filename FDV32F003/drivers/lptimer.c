/**
 * @file lptimer.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lptimer.h"
#include "sysc.h"
/**
 * @brief LPtimer init
 *
 * @param iDel:  delay ms (lrc 262s,xtl max65s)
 * @param iMode :LPT_SIG_TIME_CNT , LPT_PIT_CNT
 * note:clk source = lrc  at least 4ms err,
 */
void LPT_Init(int iDel, int iMode)
{
	int iTmp = 1;
	PARAM_CHECK((iMode != LPT_SIG_TIME_CNT) && (iMode != LPT_PIT_CNT));
	SYSC->CLKENCFG |= SYSC_CLKENCFG_LPTIM_CKEN;

	iTmp = iDel >> 2;

	PARAM_CHECK((iTmp > 0xffff) || (iTmp < 1));
	LPTIM->CR |= 1 << 4;
	LPTIM->CFG = iTmp - 1;
	if (iMode == LPT_SIG_TIME_CNT)
	{
		LPTIM_CR_REG &= ~LPTIM_CR_PITE;
	}
	else
	{
		LPTIM_CR_REG |= LPTIM_CR_PITE;
	}

	LPTIM->CR |= LPTIM_CR_EN;
}

/**
 * @brief LPT 使能控制
 *
 * @param iCtrl:ENABLE or DISABLE
 */
void LPT_EnableControl(int iCtrl)
{
	if (iCtrl == ENABLE)
		LPTIM->CR |= LPTIM_CR_EN;
	else
		LPTIM->CR &= ~LPTIM_CR_EN;
}
/**
 * @brief Lptime deinit
 *
 */
void LPT_DeInit(void)
{
	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_LPTIM_CKEN;
}

/**
 * @brief enable interrupt
 *
 */
void LPT_EnableIRQ(void)
{
	LPTIM_CR_REG |= LPTIM_CR_IE;
}
/**
 * @brief disable interrupt
 *
 */
void LPT_DisableIRQ(void)
{
	LPTIM_CR_REG &= ~LPTIM_CR_IE;
}

/**
 * @brief get current count value
 *
 * @return u16 :16bit count
 */
u16 LPT_GetCount(void)
{
	u16 tmp0;
	while (1)
	{
		tmp0	 = LPTIM->CNT & LPTIM_CNT;
		u16 tmp1 = LPTIM->CNT & LPTIM_CNT;
		if (tmp0 == tmp1)
			break;
	}
	return tmp0;
}
