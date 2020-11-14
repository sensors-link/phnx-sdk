/**
 * @file timer.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "sysc.h"
#include "timer.h"
#include "iom.h"

/**
 * @brief  timer init
 *
 * @param pTim :TIM1-4
 * @param mode :TIM_TM_AUTO_RUN , TIM_TM_AUTO_LOAD
 * @param del :us
 */
void TIM_TimerInit(TIM_Type *pTim, int mode, int del) {
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_IOM;
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    PARAM_CHECK((mode != TIM_TM_AUTO_RUN) && (mode != TIM_TM_AUTO_LOAD));
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_IOM;
    if (pTim == TIM1) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
        if (mode == TIM_TM_AUTO_RUN) {
            TIMERS->CON &= ~TIM_CON_TM_TIM1;
            int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
            int cnt = (long long)del * pclk / 1000000;
            TIM1->CTCG1 = cnt & 0xffff;
            TIM1->CTCG2 = cnt >> 16;

        } else {
            TIMERS->CON |= TIM_CON_TM_TIM1;
            int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
            int cnt = (long long)del * pclk / 1000000;
            PARAM_CHECK(cnt > 0xffff); // div handler can affect tim1/2
            TIM1->CTCG1 = cnt;
        }
        TIMERS->CON |= TIM_CON_TE_TIM1;
    } else if (pTim == TIM2) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
        if (mode == TIM_TM_AUTO_RUN) {
            TIMERS->CON &= ~TIM_CON_TM_TIM2;
            int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
            int cnt = (long long)del * pclk / 1000000;
            TIM2->CTCG1 = cnt & 0xffff;
            TIM2->CTCG2 = cnt >> 16;

        } else {
            TIMERS->CON |= TIM_CON_TM_TIM2;
            int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
            int cnt = (long long)del * pclk / 1000000;
            PARAM_CHECK(cnt > 0xffff); // div handler can affect tim1/2
            TIM2->CTCG1 = cnt;
        }
        TIMERS->CON |= TIM_CON_TE_TIM2;
    } else if (pTim == TIM3) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM3_CNT;
        PARAM_CHECK((mode != TIM_TM_AUTO_RUN) && (mode != TIM_TM_AUTO_LOAD));
        if (mode == TIM_TM_AUTO_RUN) {
            TIMERS->CON &= ~TIM_CON_TM_TIM3;
            int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
            int cnt = (long long)del * pclk / 1000000;
            TIM3->CTCG1 = cnt & 0xffff;
            TIM3->CTCG2 = cnt >> 16;

        } else {
            TIMERS->CON |= TIM_CON_TM_TIM3;
            int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
            int cnt = (long long)del * pclk / 1000000;
            PARAM_CHECK(cnt > 0xffff); // div handler can affect tim1/2
            TIM3->CTCG1 = cnt;
        }
        TIMERS->CON |= TIM_CON_TE_TIM3;
    } else {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM4_CNT;
        PARAM_CHECK((mode != TIM_TM_AUTO_RUN) && (mode != TIM_TM_AUTO_LOAD));
        if (mode == TIM_TM_AUTO_RUN) {
            TIMERS->CON &= ~TIM_CON_TM_TIM4;
            int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
            int cnt = (long long)del * pclk / 1000000;
            TIM4->CTCG1 = cnt & 0xffff;
            TIM4->CTCG2 = cnt >> 16;
        } else {
            TIMERS->CON |= TIM_CON_TM_TIM4;
            int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
            int cnt = (long long)del * pclk / 1000000;
            PARAM_CHECK(cnt > 0xffff); // div handler can affect tim1/2
            TIM4->CTCG1 = cnt;
        }
        TIMERS->CON |= TIM_CON_TE_TIM4;
    }
}

/**
 * @brief counter init
 *
 * @param pTim :TIM1-4
 * @param cntPolarity :TIM_CNT_POLARITY_HIGH , TIM_CNT_POLARITY_LOW
 * @param portSel :TIM1_CNT_PORT_P8_P9 , TIM2_CNT_PORT_P10_P11 ,
 * TIM3_CNT_PORT_P6_P7
 */
void TIM_CounterInit(TIM_Type *pTim, int cntPolarity, int portSel) {
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_IOM;
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    if (pTim == TIM1) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
        TIMERS->CON &= ~TIM_CON_TM_TIM1;
        PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) &&
                    (cntPolarity != TIM_CNT_POLARITY_LOW));
        if (cntPolarity == TIM_CNT_POLARITY_HIGH) {
            TIMERS->CON &= ~TIM_CON_EXTPOL_TIM1;
        } else {
            TIMERS->CON |= TIM_CON_EXTPOL_TIM1;
        }
        PARAM_CHECK(portSel != TIM1_CNT_PORT_P8_P9);
        IOM->AF0 &= ~IOM_AF0_P08_SEL;
        IOM->AF0 |= IOM_AF0_P08_SEL_TIM1_GATE;
        IOM->AF0 &= ~IOM_AF0_P09_SEL;
        IOM->AF0 |= IOM_AF0_P09_SEL_TIM1_EXT;
        TIMERS->CON |= TIM_CON_EXTEN_TIM1;
        TIMERS->CON |= TIM_CON_TE_TIM1;
    } else if (pTim == TIM2) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
        TIMERS->CON &= ~TIM_CON_TM_TIM2;
        PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) &&
                    (cntPolarity != TIM_CNT_POLARITY_LOW));
        if (cntPolarity == TIM_CNT_POLARITY_HIGH) {
            TIMERS->CON &= ~TIM_CON_EXTPOL_TIM2;
        } else {
            TIMERS->CON |= TIM_CON_EXTPOL_TIM2;
        }
        PARAM_CHECK(portSel != TIM2_CNT_PORT_P10_P11);
        IOM->AF0 &= ~IOM_AF0_P10_SEL;
        IOM->AF0 |= IOM_AF0_P10_SEL_TIM2_GATE;
        IOM->AF0 &= ~IOM_AF0_P11_SEL;
        IOM->AF0 |= IOM_AF0_P11_SEL_TIM2_EXT;
        TIMERS->CON |= TIM_CON_EXTEN_TIM2;
        TIMERS->CON |= TIM_CON_TE_TIM2;
    } else if (pTim == TIM3) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM3_CNT;
        TIMERS->CON &= ~TIM_CON_TM_TIM3;
        PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) &&
                    (cntPolarity != TIM_CNT_POLARITY_LOW));
        if (cntPolarity == TIM_CNT_POLARITY_HIGH) {
            TIMERS->CON &= ~TIM_CON_EXTPOL_TIM3;
        } else {
            TIMERS->CON |= TIM_CON_EXTPOL_TIM3;
        }
        PARAM_CHECK(portSel != TIM3_CNT_PORT_P0_P1);
        IOM->AF0 &= ~IOM_AF0_P00_SEL;
        IOM->AF0 |= IOM_AF0_P00_SEL_TIM3_GATE;
        IOM->AF0 &= ~IOM_AF0_P01_SEL;
        IOM->AF0 |= IOM_AF0_P01_SEL_TIM3_EXT;
        TIMERS->CON |= TIM_CON_EXTEN_TIM3;
        TIMERS->CON |= TIM_CON_TE_TIM3;
    } else {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM4_CNT;
        TIMERS->CON &= ~TIM_CON_TM_TIM4;
        PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) &&
                    (cntPolarity != TIM_CNT_POLARITY_LOW));
        if (cntPolarity == TIM_CNT_POLARITY_HIGH) {
            TIMERS->CON &= ~TIM_CON_EXTPOL_TIM4;
        } else {
            TIMERS->CON |= TIM_CON_EXTPOL_TIM4;
        }
        PARAM_CHECK(portSel != TIM4_CNT_PORT_P6_P7);
        IOM->AF0 &= ~IOM_AF0_P06_SEL;
        IOM->AF0 |= IOM_AF0_P06_SEL_TIM4_GATE;
        IOM->AF0 &= ~IOM_AF0_P07_SEL;
        IOM->AF0 |= IOM_AF0_P07_SEL_TIM4_EXT;
        TIMERS->CON |= TIM_CON_EXTEN_TIM4;
        TIMERS->CON |= TIM_CON_TE_TIM4;
    }
}

/**
 * @brief pwm init
 *
 * @param pTim :TIM1-4
 * @param pwmPolarity :TIM_PMW_POL_xxxx;
 * @param freq : kHz
 * @param duty :exp:duty=50 (50%)
 * @param portSel :TIMN_PWM_PORT_xxxx;
 * @param dtGap :us
 */
void TIM_PWMInit(TIM_Type *pTim, int pwmPolarity, int freq, int duty,
                 int portSel, int dtGap) {
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    SystemCoreClockUpdate();
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_IOM;
    if (pTim == TIM1) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
        TIMERS->CON |= TIM_CON_TM_TIM1;
        TIMERS->CON |= TIM_CON_PWM_TIM1;
        PARAM_CHECK(portSel != TIM1_PWM_PORT_P8_P9);
        IOM->AF0 &= ~IOM_AF0_P08_SEL;
        IOM->AF0 |= IOM_AF0_P08_SEL_TIM1_TOG;
        IOM->AF0 &= ~IOM_AF0_P09_SEL;
        IOM->AF0 |= IOM_AF0_P09_SEL_TIM1_TOGN;
        int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
        int tcnt = pclk / (freq * 1000);
        PARAM_CHECK(tcnt < 2);
        TIM1->CTCG2 = tcnt * (duty) / 100;
        TIM1->CTCG1 = tcnt - (TIM1->CTCG2);
        TIM1->PWCON &= ~TIM_PWCON_PWMCPOL;
        PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) &&
                    (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
        if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1) {
            TIM1->PWCON |= (1 << 17);
        } else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1) {
            TIM1->PWCON |= (2 << 17);
        } else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1) {
            TIM1->PWCON |= (3 << 17);
        }
        if (dtGap > 0) {
            TIM1->PWCON |= (1 << 16);
            tcnt = pclk / 1000000 * dtGap;
            PARAM_CHECK(tcnt > 0xffff);
            TIM1->PWCON &= ~0xffff;
            TIM1->PWCON |= tcnt;
        } else {
            TIM1->PWCON &= ~(1 << 16);
        }
        TIMERS->CON |= TIM_CON_TE_TIM1;
    } else if (pTim == TIM2) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
        TIMERS->CON |= TIM_CON_TM_TIM2;
        TIMERS->CON |= TIM_CON_PWM_TIM2;
        PARAM_CHECK((portSel != TIM2_PWM_PORT_P10_P11) &&
                    (portSel != TIM2_PWM_PORT_P4_P5));
        if (portSel == TIM2_PWM_PORT_P10_P11) {
            IOM->AF0 &= ~IOM_AF0_P10_SEL;
            IOM->AF0 |= IOM_AF0_P10_SEL_TIM2_TOG;
            IOM->AF0 &= ~IOM_AF0_P11_SEL;
            IOM->AF0 |= IOM_AF0_P11_SEL_TIM2_TOGN;
        } else {
            IOM->AF0 &= ~IOM_AF0_P04_SEL;
            IOM->AF0 |= IOM_AF0_P04_SEL_TIM2_TOG;
            IOM->AF0 &= ~IOM_AF0_P05_SEL;
            IOM->AF0 |= IOM_AF0_P05_SEL_TIM2_TOGN;
        }
        int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
        int tcnt = pclk / (freq * 1000);
        PARAM_CHECK(tcnt < 2);
        TIM2->CTCG2 = tcnt * (duty) / 100; //
        TIM2->CTCG1 = tcnt - (TIM2->CTCG2);

        TIM2->PWCON &= ~TIM_PWCON_PWMCPOL;
        PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) &&
                    (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
        if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1) {
            TIM2->PWCON |= (1 << 17);
        } else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1) {
            TIM2->PWCON |= (2 << 17);
        } else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1) {
            TIM2->PWCON |= (3 << 17);
        }
        if (dtGap > 0) {
            TIM2->PWCON |= (1 << 16);
            tcnt = pclk / 1000000 * dtGap;
            PARAM_CHECK(tcnt > 0xffff);
            TIM2->PWCON &= ~0xffff;
            TIM2->PWCON |= tcnt;
        } else {
            TIM2->PWCON &= ~(1 << 16);
        }
        TIMERS->CON |= TIM_CON_TE_TIM2;
    } else if (pTim == TIM3) {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM3_CNT;
        TIMERS->CON |= TIM_CON_TM_TIM3;
        TIMERS->CON |= TIM_CON_PWM_TIM3;
        PARAM_CHECK((portSel != TIM3_PWM_PORT_P14_P15) &&
                    (portSel != TIM3_PWM_PORT_P16_P13));
        if (portSel == TIM3_PWM_PORT_P14_P15) {
            IOM->AF0 &= ~IOM_AF0_P14_SEL;
            IOM->AF0 |= IOM_AF0_P14_SEL_TIM3_TOG;
            IOM->AF0 &= ~IOM_AF0_P15_SEL;
            IOM->AF0 |= IOM_AF0_P15_SEL_TIM3_TOGN;
        } else {
            IOM->AF0 |= IOM_AF1_P16_SEL_TIM3_TOG;
            IOM->AF0 &= ~IOM_AF1_P16_SEL;
            IOM->AF0 &= ~IOM_AF0_P13_SEL;
            IOM->AF0 |= IOM_AF0_P13_SEL_TIM3_TOGN;
        }
        int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
        int tcnt = pclk / (freq * 1000);
        PARAM_CHECK(tcnt < 2);
        TIM3->CTCG2 = tcnt * (duty) / 100; //
        TIM3->CTCG1 = tcnt - (TIM3->CTCG2);
        TIM3->PWCON &= ~TIM_PWCON_PWMCPOL;
        PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) &&
                    (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
        if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1) {
            TIM3->PWCON |= (1 << 17);
        } else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1) {
            TIM3->PWCON |= (2 << 17);
        } else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1) {
            TIM3->PWCON |= (3 << 17);
        }
        if (dtGap > 0) {
            TIM3->PWCON |= (1 << 16);
            tcnt = pclk / 1000000 * dtGap;
            PARAM_CHECK(tcnt > 0xffff);
            TIM3->PWCON &= ~0xffff;
            TIM3->PWCON |= tcnt;
        } else {
            TIM3->PWCON &= ~(1 << 16);
        }
        TIMERS->CON |= TIM_CON_TE_TIM3;
    } else {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM4_CNT;
        TIMERS->CON |= TIM_CON_TM_TIM4;
        TIMERS->CON |= TIM_CON_PWM_TIM4;
        PARAM_CHECK(portSel != TIM4_PWM_PORT_P6_P7);
        IOM->AF0 &= ~IOM_AF0_P06_SEL;
        IOM->AF0 |= IOM_AF0_P06_SEL_TIM4_TOG;
        IOM->AF0 &= ~IOM_AF0_P07_SEL;
        IOM->AF0 |= IOM_AF0_P07_SEL_TIM4_TOGN;

        int pclk = SYSC_GetAHBCLK() / (SYSC->BZTIMCLKDIV + 1);
        int tcnt = pclk / (freq * 1000);
        PARAM_CHECK(tcnt < 2);
        TIM4->CTCG2 = tcnt * (duty) / 100; //
        TIM4->CTCG1 = tcnt - (TIM4->CTCG2);

        TIM4->PWCON &= ~TIM_PWCON_PWMCPOL;
        PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) &&
                    (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
        if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1) {
            TIM4->PWCON |= (1 << 17);
        } else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1) {
            TIM4->PWCON |= (2 << 17);
        } else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1) {
            TIM4->PWCON |= (4 << 17);
        }
        if (dtGap > 0) {
            TIM4->PWCON |= (1 << 16);
            tcnt = pclk / 1000000 * dtGap;
            PARAM_CHECK(tcnt > 0xffff);
            TIM4->PWCON &= ~0xffff;
            TIM4->PWCON |= tcnt;
        } else {
            TIM4->PWCON &= ~(1 << 16);
        }
        TIMERS->CON |= TIM_CON_TE_TIM4;
    }
}
/**
 * @brief Timer deinit
 *
 * @param pTim:TIM1-4
 */
void TIM_DeInit(TIM_Type *pTim) {
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    if (pTim == TIM1) {
        TIMERS->CON &= ~TIM_CON_TE_TIM1;
        TIMERS->CON &= ~TIM_CON_TM_TIM1;
        TIMERS->CON &= ~TIM_CON_IE_TIM1;
        TIMERS->CON &= ~TIM_CON_PWM_TIM1;
        TIMERS->CON &= ~TIM_CON_EXTEN_TIM1;
        TIMERS->CON &= ~TIM_CON_EXTPOL_TIM1;
        TIMERS->CON &= ~TIM_CON_PAUSE_TIM1;
        SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM1_CNT;
    } else if (pTim == TIM2) {
        TIMERS->CON &= ~TIM_CON_TE_TIM2;
        TIMERS->CON &= ~TIM_CON_TM_TIM2;
        TIMERS->CON &= ~TIM_CON_IE_TIM2;
        TIMERS->CON &= ~TIM_CON_PWM_TIM2;
        TIMERS->CON &= ~TIM_CON_EXTEN_TIM2;
        TIMERS->CON &= ~TIM_CON_EXTPOL_TIM2;
        TIMERS->CON &= ~TIM_CON_PAUSE_TIM2;
        SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM2_CNT;
    } else if (pTim == TIM3) {
        TIMERS->CON &= ~TIM_CON_TE_TIM3;
        TIMERS->CON &= ~TIM_CON_TM_TIM3;
        TIMERS->CON &= ~TIM_CON_IE_TIM3;
        TIMERS->CON &= ~TIM_CON_PWM_TIM3;
        TIMERS->CON &= ~TIM_CON_EXTEN_TIM3;
        TIMERS->CON &= ~TIM_CON_EXTPOL_TIM3;
        TIMERS->CON &= ~TIM_CON_PAUSE_TIM3;
        SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM3_CNT;
    } else {
        TIMERS->CON &= ~TIM_CON_TE_TIM4;
        TIMERS->CON &= ~TIM_CON_TM_TIM4;
        TIMERS->CON &= ~TIM_CON_IE_TIM4;
        TIMERS->CON &= ~TIM_CON_PWM_TIM4;
        TIMERS->CON &= ~TIM_CON_EXTEN_TIM4;
        TIMERS->CON &= ~TIM_CON_EXTPOL_TIM4;
        TIMERS->CON &= ~TIM_CON_PAUSE_TIM4;
        SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM4_CNT;
    }
    if ((TIMERS->CON & TIM_CON_TE) == 0) {
        SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM_PCK;
        SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
        SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
        SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_TIMER;
    }
}
/**
 * @brief 使能控制
 *
 * @param pTim : TIM1-4
 * @param iCtrl ：ENABLE or DISABLE
 */
void TIM_EnableControl(TIM_Type *pTim, int iCtrl) {
    if (iCtrl == ENABLE) {
        switch ((int)pTim) {
        case (int)TIM1:
            TIMERS->CON |= TIM_CON_TE_TIM1;
            break;
        case (int)TIM2:
            TIMERS->CON |= TIM_CON_TE_TIM2;
            break;
        case (int)TIM3:
            TIMERS->CON |= TIM_CON_TE_TIM3;
            break;
        case (int)TIM4:
            TIMERS->CON |= TIM_CON_TE_TIM4;
            break;
        }
    } else {
        switch ((int)pTim) {
        case (int)TIM1:
            TIMERS->CON &= ~TIM_CON_TE_TIM1;
            break;
        case (int)TIM2:
            TIMERS->CON &= ~TIM_CON_TE_TIM2;
            break;
        case (int)TIM3:
            TIMERS->CON &= ~TIM_CON_TE_TIM3;
            break;
        case (int)TIM4:
            TIMERS->CON &= ~TIM_CON_TE_TIM4;
            break;
        }
    }
}
/**
 * @brief Timer interrupt enable
 *
 * @param pTim :TIM1-4
 */
void TIM_EnableIRQ(TIM_Type *pTim) {
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    if (pTim == TIM1) {
        TIMERS->CON |= (1 << 8);
    } else if (pTim == TIM2) {
        TIMERS->CON |= (1 << 9);
    } else if (pTim == TIM3) {
        TIMERS->CON |= (1 << 10);
    } else {
        TIMERS->CON |= (1 << 11);
    }
}

/**
 * @brief Timer interrupt disable
 *
 * @param pTim:TIM1-4
 */
void TIM_DisableIRQ(TIM_Type *pTim) {
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    if (pTim == TIM1) {
        TIMERS->CON &= ~(1 << 8);
    } else if (pTim == TIM2) {
        TIMERS->CON &= ~(1 << 9);
    } else if (pTim == TIM3) {
        TIMERS->CON &= ~(1 << 10);
    } else {
        TIMERS->CON &= ~(1 << 11);
    }
}

/**
 * @brief Timer stop counter
 *
 * @param pTim :TIM1-4
 * @param ctr :ENABLE , DISABLE
 */
void TIM_PauseCntControl(TIM_Type *pTim, ControlStatus ctl) {
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    PARAM_CHECK((ctl != ENABLE) && (ctl != DISABLE));
    if (pTim == TIM1) {
        if (ctl == ENABLE) {
            TIMERS->CON |= (1 << 24);
        } else {
            TIMERS->CON &= ~(1 << 24);
        }

    } else if (pTim == TIM2) {
        if (ctl == ENABLE) {
            TIMERS->CON |= (1 << 25);
        } else {
            TIMERS->CON &= ~(1 << 25);
        }
    } else if (pTim == TIM3) {
        if (ctl == ENABLE) {
            TIMERS->CON |= (1 << 26);
        } else {
            TIMERS->CON &= ~(1 << 26);
        }
    } else {
        if (ctl == ENABLE) {
            TIMERS->CON |= (1 << 27);
        } else {
            TIMERS->CON &= ~(1 << 27);
        }
    }
}

/**
 * @brief get timer interrupt flag
 *
 * @param pTim :TIM1-4
 * @return FlagStatus : SET , RESET
 */
FlagStatus TIM_GetIntFlag(TIM_Type *pTim) {
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    if (pTim == TIM1) {
        return (TIMERS->INTFLAG & (1 << 0)) ? SET : RESET;
    } else if (pTim == TIM2) {
        return (TIMERS->INTFLAG & (1 << 1)) ? SET : RESET;
    } else if (pTim == TIM3) {
        return (TIMERS->INTFLAG & (1 << 2)) ? SET : RESET;
    } else {
        return (TIMERS->INTFLAG & (1 << 3)) ? SET : RESET;
    }
}
/**
 * @brief clear timer interrupt flag
 *
 * @param pTim :TIM1-4
 */
void TIM_ClrIntFlag(TIM_Type *pTim) {
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) &&
                (pTim != TIM4));
    if (pTim == TIM1) {
        TIMERS->INTCLR = (1 << 0);
    } else if (pTim == TIM2) {
        TIMERS->INTCLR = (1 << 1);
    } else if (pTim == TIM3) {
        TIMERS->INTCLR = (1 << 2);
    } else {
        TIMERS->INTCLR = (1 << 3);
    }
}
