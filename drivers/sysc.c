/**
 * @file sysc.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "sysc.h"

/**
 * @brief select system clock source
 *
 * @param clkSrc :SYSC_CLK_SRC_HRC  , SYSC_CLK_SRC_LRC , SYSC_CLK_SRC_XTH ,
 * SYSC_CLK_SRC_XTL
 */
void SYSC_SelectClockSource(int clkSrc) {
    PARAM_CHECK((clkSrc != SYSC_CLK_SRC_HRC) && (clkSrc != SYSC_CLK_SRC_LRC) &&
                (clkSrc != SYSC_CLK_SRC_XTH) && (clkSrc != SYSC_CLK_SRC_XTL));
    SYSC_WPT_UNLOCK();
    SYSC->CLKCTRCFG &= ~SYSC_CLKCTRCFG_SYS_CLK_SEL;
    SYSC_WPT_UNLOCK();
    SYSC->CLKCTRCFG |= (clkSrc << 4);
}

/**
 * @brief set APB clk div
 *
 * @param div :DIV1-128
 */
void SYSC_SetAPBCLKDiv(int div) {
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
void SYSC_SetAHBCLKDiv(int div) {
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
void SYSC_ResetPeripher(eRSTP_Type module) {
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
void SYSC_PCLKEnable(ePCLKEN_Type perp) { SYSC->CLKENCFG |= perp; }
/**
 * @brief peripher clock disable
 *
 * @param perp :surport '|' combine
 * PCLK_EN_xx
 */
void SYSC_PCLKDisable(ePCLKEN_Type perp) { SYSC->CLKENCFG &= ~perp; }
/**
 * @brief set anac , adc module clock div
 *
 * @param div : val:0-15 ==> div2-32  even
 * @param m500kDiv: val:1-31 ==> DIV2-32
 */
void SYSC_SetANAC_CLKDiv(int div, int m500kDiv) {
    SYSC->ANCLKDIV &= ~SYSC_ANAC_ANAC_SCLK_DIV;
    SYSC->ANCLKDIV |= div << SYSC_ANAC_ANAC_SCLK_DIV_pos;
    SYSC->ANCLKDIV &= ~SYSC_ANAC_500K_CLK_DIV;
    SYSC->ANCLKDIV |= m500kDiv << SYSC_ANAC_500K_CLK_DIV_pos;
}

/**
 * @brief set time1-3 clock div
 *
 * @param div :DIVxx
 */
void SYSC_SetTimer1_3ClkDiv(int div) {
    PARAM_CHECK((div < DIV1) || (div > DIV128));
    SYSC->TIMCLKDIV = div;
}
/**
 * @brief set bz timer4 clock div
 *
 * @param div :DIVxx
 */
void SYSC_SetBZTimer4(int div) {
    PARAM_CHECK((div < DIV1) || (div > DIV128));
    SYSC->BZTIMCLKDIV = div;
}
