/**
 * @file pmu.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "sysc.h"
#include "pmu.h"
/**
 * @brief PUM init
 *
 */
void PMU_Init(void) { SYSC->CLKENCFG |= SYSC_CLKENCFG_PMU; }

/**
 * @brief PMU deinit
 *
 */
void PMU_DeInit(void) { SYSC->CLKENCFG &= ~SYSC_CLKENCFG_PMU; }

/**
 * @brief config wake pin
 *
 * @param iWkMode:PMU_WKCFG_PMUWKMODE_SYCN , PMU_WKCFG_PMUWKMODE_ASYCN
 * @param iWKLevel:PMU_WK_LOW , PMU_WK_HIGH
 * @param iWKPinEn : PMU_WK_PIN16 [| PMU_WK_PIN17 | PMU_WK_PIN18 | PMU_WK_PIN19]
 * surp,t '|' combination
 *
 */
void PMU_WakeConfig(int iWkMode, int iWKLevel, int iWKPinEn) {
    PARAM_CHECK((iWkMode != PMU_WKCFG_PMUWKMODE_SYCN) &&
                (iWkMode != PMU_WKCFG_PMUWKMODE_ASYCN));
    PARAM_CHECK((iWKLevel != PMU_WKCFG_GPIOWKLEV_LOW) &&
                (iWKLevel != PMU_WKCFG_GPIOWKLEV_HIGH));
    PMU->WKCFG |= iWkMode;
    if (iWKLevel == PMU_WK_LOW) {
        PMU->WKCFG &= ~(iWKPinEn << PMU_WKCFG_GPIOWKLEV_pos);
    } else {
        PMU->WKCFG |= (iWKPinEn << PMU_WKCFG_GPIOWKLEV_pos);
    }
    PMU->WKCFG |= iWKPinEn;
}

/**
 * @brief enter sleep mode
 *
 * note：the successive powerdown/deepsleep interval should be more than 2ms at
 * least
 */
void PMU_EnterSleep(void) {
    CLEAR_CSR(0xbff, CUSTOMCSR0_SLEEPDEEPEN);
    asm volatile("wfi");
}

/**
 * @brief enter deep sleep mode
 *
 *note：the successive powerdown/deepsleep interval should be more than 2ms at
 *least
 */
void PMU_EnterDeepSleep(void) {
    WRITE_CSR(0xbff, CUSTOMCSR0_SLEEPDEEPEN);
    asm volatile("wfi");
}

/**
 * @brief enter power down
 *
 */
void PMU_EnterPowerDown(void) {
    PMU_WPT_UNLOCK();
    PMU->CR |= 0x0a;
    CLEAR_CSR(0xbff, CUSTOMCSR0_SLEEPDEEPEN);
    asm volatile("wfi");
}

/**
 * @brief soft core reset
 *
 */
void PMU_SoftCoreReset(void) { SET_CSR(0xbff, CUSTOMCSR0_SYSRESETREQ); }
/**
 * @brief reset digital region
 *
 */
void PMU_SoftDigitalReset(void) {
    PMU_WPT_UNLOCK();
    PMU->SOFTRST |= (1 << 1);
}
/**
 * @brief reset awo and dig region
 *
 */
void PMU_SoftChipReset(void) {
    PMU_WPT_UNLOCK();
    PMU->SOFTRST |= (1 << 0);
}

/**
 * @brief: set inturrupt enable
 *
 * @param val :PMU_INTEN_xxxx,  Can using or('|') combined
 */
void PMU_SetINTEnable(int val) { PMU->INTEN |= val; }

/**
 * @brief get interrupt flags
 *
 * @param wk_rstREG:PMU_WK_FLAG  , PMU_RST_FLAG
 * @return int
 */
int PMU_GetIntFlag(int wk_rstREG) {
    PARAM_CHECK((wk_rstREG != PMU_WK_FLAG) && (wk_rstREG != PMU_RST_FLAG));
    if (wk_rstREG == PMU_WK_FLAG)
        return PMU->WKSTS;
    else
        return PMU->RSTSTS;
}

/**
 * @brief clear interrupt flag
 *
 * @param wk_rstREG PMU_WK_FLAG  , PMU_RST_FLAG
 * @param val:PMU_WKSTS_xxx , PMU_RSTSTS_xxx
 * @return int
 */
void PMU_ClrIntFlag(int wk_rstREG, int val) {
    PARAM_CHECK((wk_rstREG != PMU_WK_FLAG) && (wk_rstREG != PMU_RST_FLAG));
    if (wk_rstREG == PMU_WK_FLAG)
        PMU->WKSTS = val;
    else
        PMU->RSTSTS = val;
}
/**
 * @brief get backup register value
 *
 * @return u32 :reg val
 */
u32 PMU_GetBAKRValue(void) { return PMU->BAKR; }
/**
 * @brief set backup register value
 *
 * @param val :val
 */
void PMU_SetBAKRValue(u32 val) { PMU->BAKR = val; }
