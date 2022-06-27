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

#define WDT_StartCount()                                                                                               \
	{                                                                                                                  \
		WDT_RST_REG = WDT_START_RST_V0;                                                                                \
		WDT_RST_REG = WDT_START_RST_V1;                                                                                \
	}
#define WDT_ClrCount()                                                                                                 \
	{                                                                                                                  \
		WDT_RST_REG = WDT_START_RST_V0;                                                                                \
		WDT_RST_REG = WDT_START_RST_V1;                                                                                \
	}
#define WDT_ClrIntFlag()                                                                                               \
	{                                                                                                                  \
		WDT_RST_REG = WDT_START_RST_V0;                                                                                \
		WDT_RST_REG = WDT_START_RST_V1;                                                                                \
	}

/**
 * @brief wdt init
 *
 * @param ps:  1-111  (1-128分频)
 * @param iDel:  delay ms  (lrc:max 256s)
 * @param iOVMode :WDT_OV_INT , WDT_OV_RST
 * note:clk source = lrc  at least 4ms err
 */
void WDT_Init(int ps, int iDel, eOVModeType iOVMode)
{
	int iTmp = 1;

	PARAM_CHECK((iOVMode != WDT_OV_INT) && (iOVMode != WDT_OV_RST));

	SYSC->CLKENCFG |= SYSC_CLKENCFG_LPWDT_PCKEN;

	// setting ps
	WDT_CR_REG |= (ps << 8) & 0xF00;

	iDel = iDel >> 2;

	while (iDel > 2)
	{
		++iTmp;
		iDel >>= 1;
	}
	PARAM_CHECK((iTmp > 16) || (iTmp == 0));
	WDT_CR_REG = iTmp - 1;
	if (iOVMode == WDT_OV_INT)
	{
		WDT_CR_REG |= WDT_CR_WINTEN;
	}
	else
	{
		WDT_CR_REG &= ~WDT_CR_WINTEN;
	}

	SYSC_WPT_UNLOCK();
	SYSC_CLKCTRCFG_REG |= SYSC_CLKCTRCFG_LPWDT_CKEN;
}

void WDT_Start(void)
{
	WDT_StartCount();
}

void WDT_Clear(void)
{
	WDT_ClrCount();
}

void WDT_ClearIntFlag(void)
{
	WDT_ClrIntFlag();
}

/**
 * @brief wdt deinit
 *
 */
void WDT_DeInit(void)
{
	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_LPWDT_PCKEN;
}
