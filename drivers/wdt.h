/**
 * @file wdt.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __WDT_H
#define __WDT_H
#include "phnx02.h"

/* WDT definitions */
#define WDT_RST_REG REG32(WDT_BASE + 0x00)
#define WDT_CR_REG REG32(WDT_BASE + 0x04)

#define WDT_START_RST_V0 0x69
#define WDT_START_RST_V1 0x96

#define WDT_CR_WDTINTFLAG BIT(7)
#define WDT_CR_WINTEN BIT(5)
#define WDT_CR_WDTR BIT(4)
#define WDT_CR_WOV BITS(0, 3)
#define WDT_CR_WOV_pos (0) // 0:0f  2^(wov+1) * 1/fclk 4ms

typedef enum _OV_MODE {
    WDT_OV_INT = 0,
    WDT_OV_RST,
} eOVModeType;

#define WDT_StartCount()                                                       \
    {                                                                          \
        WDT_RST_REG = WDT_START_RST_V0;                                        \
        WDT_RST_REG = WDT_START_RST_V1;                                        \
    }
#define WDT_ClrCount()                                                         \
    {                                                                          \
        WDT_RST_REG = WDT_START_RST_V0;                                        \
        WDT_RST_REG = WDT_START_RST_V1;                                        \
    }
#define WDT_ClrIntFlag()                                                       \
    {                                                                          \
        WDT_RST_REG = WDT_START_RST_V0;                                        \
        WDT_RST_REG = WDT_START_RST_V1;                                        \
    }
#define WDT_GetIntFlag() (WDT_CR_REG & WDT_CR_WDTINTFLAG)

// extern function declare

void WDT_Init(int iDel, int iClkSrc, eOVModeType iOVMode);
void WDT_DeInit(void);
#endif
