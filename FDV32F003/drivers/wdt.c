/**
 * @file wdt.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "wdt.h"
#include "sysc.h"

/**
 * @brief wdt init
 *
 * @param ps:  1-111  (1-128分频)
 * @param iDel:  delay ms  (lrc:max 256s)
 * @param iOVMode :WDT_OV_INT , WDT_OV_RST
 * note:clk source = lrc  at least 4ms err
 */
void WDT_Init(int iDel, eOVModeType iOVMode)
{
	int iTmp = 1;
	PARAM_CHECK((iOVMode != WDT_OV_INT) && (iOVMode != WDT_OV_RST));
	SYSC->CLKENCFG |= SYSC_CLKENCFG_LPWDT_PCKEN;

	int iPs	 = (WDT->CR & WDT_CR_PS) >> WDT_CR_PS_pos;
	int iDiv = 1;
	for (int i = 0; i < iPs; i++)
		iDiv *= 2;
	iDel = iDel * 32 / iDiv;

	while (iDel > 2)
	{
		++iTmp;
		iDel >>= 1;
	}

	PARAM_CHECK((iTmp > 16) || (iTmp == 0));
	WDT->CR &= ~WDT_CR_WOV;
	WDT->CR |= (iTmp - 1) << WDT_CR_WOV_pos;
	if (iOVMode == WDT_OV_INT)
		WDT->CR |= WDT_CR_WINTEN;
	else
		WDT->CR &= ~WDT_CR_WINTEN;

	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG |= SYSC_CLKCTRCFG_LPWDT_CKEN;

	WDT_StartCount();
}

/**
 * @brief wdt deinit
 *
 */
void WDT_DeInit(void)
{
	SYSC_WPT_UNLOCK();
	SYSC->CLKCTRCFG &= ~SYSC_CLKCTRCFG_LPWDT_CKEN;
	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_LPWDT_PCKEN;
}
