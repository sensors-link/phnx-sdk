/**
 * @file pmu.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __PMU_H
#define __PMU_H
#include "phnx02.h"
#include "risc_v_csr.h"
// register def
#define PMU_CR REG32(PMU_BASE + 0x00)
#define PMU_WKCFG REG32(PMU_BASE + 0x04)
#define PMU_SOFTRST REG32(PMU_BASE + 0x08)
#define PMU_WKSTS REG32(PMU_BASE + 0x0c)
#define PMU_RSTSTS REG32(PMU_BASE + 0x10)
#define PMU_INTEN REG32(PMU_BASE + 0x14)
#define PMU_WPT REG32(PMU_BASE + 0x18)
// reg bits def
#define PMU_CR_FLSDEEPSTB BITS(12, 15)
#define PMU_CR_HRCKEEPALIVE BIT(10)
#define PMU_CR_VDDLPCFG BITS(8, 9) // dp/pd valid
#define PMU_CR_VDDLPCFG_1P5 (0 << 8)
#define PMU_CR_VDDLPCFG_1P2 (1 << 8)
#define PMU_CR_VDDLPCFG_1P0 (2 << 8)
#define PMU_CR_VDDLPCFG_0P8 (3 << 8)

#define PMU_CR_WDTCLKEN BIT(7)
#define PMU_CR_LPTCLKEN BIT(6)
#define PMU_CR_LPTCLKSEL BIT(5)
#define PMU_CR_LPTCLKSEL_LRC (0 << 5)
#define PMU_CR_LPTCLKSEL_XTL (1 << 5)

#define PMU_CR_LVDCHIPRSTEN BIT(4)
#define PMU_CR_PDNEN BITS(0, 3)
#define PMU_CR_PDNEN_V 0x0a

#define PMU_WKCFG_PMUWKMODE BIT(9)
#define PMU_WKCFG_PMUWKMODE_SYCN (0 << 9)
#define PMU_WKCFG_PMUWKMODE_ASYCN (1 << 9) // ds/pd valid

#define PMU_WKCFG_GPIOWKLEV BITS(4, 7)
#define PMU_WKCFG_GPIOWKLEV_pos 4
#define PMU_WKCFG_GPIOWKLEV_LOW (0 << 4)
#define PMU_WKCFG_GPIOWKLEV_HIGH (1 << 4)

#define PMU_WKCFG_GPIOWKEN BITS(0, 3)
#define PMU_WKCFG_GPIOWKEN_pos 0
#define PMU_WKCFG_GPIOWKEN_ENABLE 1
#define PMU_WKCFG_GPIOWKEN_DISABLE 0

#define PMU_SOFTRST_DIG BIT(1)
#define PMU_SOFTRST_CHIP BIT(0)

#define PMU_WKSTS_TWCWKSTS BIT(8)
#define PMU_WKSTS_LPUWKSTS BIT(7)
#define PMU_WKSTS_RTCWKSTS BIT(6)
#define PMU_WKSTS_LPTWKSTS BIT(5)
#define PMU_WKSTS_WDTWKSTS BIT(4)
#define PMU_WKSTS_GPIOWKSTS BITS(0, 3)

#define PMU_RSTSTS_PORRSTSTS BIT(5)
#define PMU_RSTSTS_SOFTDIGRSTSTS BIT(4)
#define PMU_RSTSTS_SOFTCHIPRSTSTS BIT(3)
#define PMU_RSTSTS_EXTRSTSTS BIT(2)
#define PMU_RSTSTS_WDTRSTSTS BIT(1)
#define PMU_RSTSTS_LVDRSTSTS BIT(0)

#define PMU_INTEN_TWCWKINTEN BIT(14)
#define PMU_INTEN_LPUWKINTEN BIT(13)
#define PMU_INTEN_RTCWKINTEN BIT(12)
#define PMU_INTEN_GPIOWKINTEN BITS(8, 11)
#define PMU_INTEN_LPTWKINTEN BIT(7)
#define PMU_INTEN_WDTWKINTEN BIT(6)
#define PMU_INTEN_PORRSTINTEN BIT(5)
#define PMU_INTEN_SOFTDIGRSTINTEN BIT(4)
#define PMU_INTEN_SOFTCHIPRSTINTEN BIT(3)
#define PMU_INTEN_EXTRSTINTEN BIT(2)
#define PMU_INTEN_WDTRSTINTEN BIT(1)
#define PMU_INTEN_LVDRSTINTEN BIT(0)

#define PMU_INTEN_GPIOWKINTEN_PIN(x) (x << 8)

#define PMU_WPT_V0 0xc3
#define PMU_WPT_V1 0x3c
#define PMU_WPT_UNLOCK()                                                       \
    {                                                                          \
        PMU->WPT = 0xc3;                                                       \
        PMU->WPT = 0x3c;                                                       \
    }

// extend define
#define PMU_WK_PIN16 1
#define PMU_WK_PIN17 2
#define PMU_WK_PIN18 4
#define PMU_WK_PIN19 8

#define PMU_WK_LOW 0
#define PMU_WK_HIGH 1

#define PMU_WK_FLAG 0
#define PMU_RST_FLAG 1

// extern function

void PMU_Init(void);
void PMU_DeInit(void);
void PMU_WakeConfig(int iWkMode, int iWKLevel, int iWKPinEn);
void PMU_EnterSleep(void);
void PMU_EnterDeepSleep(void);
void PMU_EnterPowerDown(void);
void PMU_EnterPowerDown(void);
void PMU_SoftCoreReset(void);
void PMU_SoftDigitalReset(void);
void PMU_SoftChipReset(void);
void PMU_SetINTEnable(int val);
int PMU_GetIntFlag(int wk_rstREG);
void PMU_ClrIntFlag(int wk_rstREG, int val);
u32 PMU_GetBAKRValue(void);
void PMU_SetBAKRValue(u32 val);

#endif
