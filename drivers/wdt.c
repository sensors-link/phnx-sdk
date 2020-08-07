/**
 * @file wdt.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "wdt.h"
#include "sysc.h"
#include "pmu.h"

/**
 * @brief wdt init
 *
 * @param iDel:  delay ms  (lrc:max 256s xtl:max 64s)
 * @param iClkSrc: PMU_CR_LPTCLKSEL_LRC , PMU_CR_LPTCLKSEL_XTL
 * @param iOVMode :WDT_OV_INT , WDT_OV_RST
 * note:clk source = lrc  at least 4ms err
 */
void WDT_Init(int iDel, int iClkSrc, eOVModeType iOVMode) {
    int iTmp = 1;
    PARAM_CHECK((iClkSrc != PMU_CR_LPTCLKSEL_LRC) &&
                (iClkSrc != PMU_CR_LPTCLKSEL_XTL));
    PARAM_CHECK((iOVMode != WDT_OV_INT) && (iOVMode != WDT_OV_RST));
    SYSC->CLKENCFG |= SYSC_CLKENCFG_WDT | SYSC_CLKENCFG_PMU;
    PMU->WPT = PMU_WPT_V0;
    PMU->WPT = PMU_WPT_V1;
    PMU->CR &= ~PMU_CR_LPTCLKSEL;
    if (iClkSrc == PMU_CR_LPTCLKSEL_LRC) {
        PMU->WPT = PMU_WPT_V0;
        PMU->WPT = PMU_WPT_V1;
        PMU->CR |= PMU_CR_LPTCLKSEL_LRC;
        iDel = iDel >> 2;
    } else {
        PMU->WPT = PMU_WPT_V0;
        PMU->WPT = PMU_WPT_V1;
        PMU->CR |= PMU_CR_LPTCLKSEL_LRC;
    }
    while (iDel > 2) {
        ++iTmp;
        iDel >>= 1;
    }
    PARAM_CHECK((iTmp > 16) || (iTmp == 0));
    WDT_CR_REG = iTmp - 1;
    if (iOVMode == WDT_OV_INT) {
        WDT_CR_REG |= WDT_CR_WINTEN;
    } else {
        WDT_CR_REG &= ~WDT_CR_WINTEN;
    }
    PMU->WPT = PMU_WPT_V0;
    PMU->WPT = PMU_WPT_V1;
    PMU->CR |= PMU_CR_WDTCLKEN;
    WDT_StartCount();
}

/**
 * @brief wdt deinit
 *
 */
void WDT_DeInit(void) {
    PMU->WPT = PMU_WPT_V0;
    PMU->WPT = PMU_WPT_V1;
    PMU->CR &= ~PMU_CR_WDTCLKEN;
    SYSC->CLKENCFG &= ~SYSC_CLKENCFG_WDT;
}
