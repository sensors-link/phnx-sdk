/**
 * @file wdt.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __WDT_H__
#define __WDT_H__
#include "../include/phnx05.h"

/* WDT definitions */
#define WDT_RST_REG REG32(WDT_BASE + 0x00)
#define WDT_CR_REG	REG32(WDT_BASE + 0x04)

#define WDT_START_RST_V0 (0x69)
#define WDT_START_RST_V1 (0x96)

#define WDT_CR_PS		  BITS(8, 10)
#define WDT_CR_WDTINTFLAG BIT(7)
#define WDT_CR_WINTEN	  BIT(5)
#define WDT_CR_WDTR		  BIT(4)
#define WDT_CR_WOV		  BITS(0, 3)
#define WDT_CR_WOV_pos	  (0) // 0:0f  2^(wov+1) * 1/fclk 4ms

typedef enum _OV_MODE
{
	WDT_OV_INT = 0,
	WDT_OV_RST,
} eOVModeType;

#define WDT_GetIntFlag() (WDT_CR_REG & WDT_CR_WDTINTFLAG)

// watch dog function declare
void WDT_Init(int ps, int iDel, eOVModeType iOVMode);
void WDT_Start(void);
void WDT_Clear(void);
void WDT_ClearIntFlag(void);
void WDT_DeInit(void);

#endif /*__WDT_H__*/
