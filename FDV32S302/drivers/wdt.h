/**
 * @file wdt.h
 * @author wyd
 * @brief
 * @version 1.0
 * @date 2021-07-19
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __WDT_H__
#define __WDT_H__

#include "phnx04.h"

// WDT_CR
#define WDT_CR_WDTINTFLAG BIT(7)
#define WDT_CR_WINTEN	  BIT(5)
#define WDT_CR_WDTR		  BIT(4)
#define WDT_CR_WOV		  BITS(0, 3)
#define WDT_CR_WOV_pos	  (0) // 0:0f  2^(wov+1) * 1/fclk 4ms

typedef enum _OV_MODE
{
	WDT_OV_INT = 0,
	WDT_OV_RST = 1,
} eOVModeType;

#define WDT_START_RST_V0 (0x69)
#define WDT_START_RST_V1 (0x96)

#define WDT_StartCount()                                                                                               \
	{                                                                                                                  \
		WDT->RST = WDT_START_RST_V0;                                                                                   \
		WDT->RST = WDT_START_RST_V1;                                                                                   \
	}
#define WDT_ClrCount()                                                                                                 \
	{                                                                                                                  \
		WDT->RST = WDT_START_RST_V0;                                                                                   \
		WDT->RST = WDT_START_RST_V1;                                                                                   \
	}
#define WDT_ClrIntFlag()                                                                                               \
	{                                                                                                                  \
		WDT->RST = WDT_START_RST_V0;                                                                                   \
		WDT->RST = WDT_START_RST_V1;                                                                                   \
	}
#define WDT_GetIntFlag() (WDT->CR & WDT_CR_WDTINTFLAG)

// extern function declare
void WDT_Init(int iDel, eOVModeType iOVMode);
void WDT_DeInit(void);

#endif /*__WDT_H__*/
