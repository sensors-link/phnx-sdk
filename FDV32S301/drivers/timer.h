/**
 * @file timer.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */
#ifndef __TIM_H
#define __TIM_H
#include "phnx02.h"

// reg bit definitions
#define TIM_PWCON_PWMCPOL BITS(17, 18)
#define TIM_PWCON_DTEN BITS(16)
#define TIM_PWCON_DTUGAP BITS(0, 15)

#define TIM_PWCON_PWMCPOL_pos (17) // 0-3

#define TIM_PWCON_DTUGAP_pos (0) // 0-0xffff

#define TIM_CON_PAUSE BITS(24, 27)
#define TIM_CON_PAUSE_TIM1 BIT(24)
#define TIM_CON_PAUSE_TIM2 BIT(25)
#define TIM_CON_PAUSE_TIM3 BIT(26)
#define TIM_CON_PAUSE_TIM4 BIT(27)

#define TIM_CON_EXTPOL BITS(20, 23)
#define TIM_CON_EXTPOL_TIM1 BIT(20)

#define TIM_CON_EXTPOL_TIM2 BIT(21)
#define TIM_CON_EXTPOL_TIM3 BIT(22)
#define TIM_CON_EXTPOL_TIM4 BIT(23)

#define TIM_CON_EXTEN BITS(16, 19)
#define TIM_CON_EXTEN_TIM1 BIT(16)
#define TIM_CON_EXTEN_TIM2 BIT(17)
#define TIM_CON_EXTEN_TIM3 BIT(18)
#define TIM_CON_EXTEN_TIM4 BIT(19)

#define TIM_CON_PWM BITS(12, 15)
#define TIM_CON_PWM_TIM1 BIT(12)
#define TIM_CON_PWM_TIM2 BIT(13)
#define TIM_CON_PWM_TIM3 BIT(14)
#define TIM_CON_PWM_TIM4 BIT(15)

#define TIM_CON_IE BITS(8, 11)
#define TIM_CON_IE_TIM1 BIT(8)
#define TIM_CON_IE_TIM2 BIT(9)
#define TIM_CON_IE_TIM3 BIT(10)
#define TIM_CON_IE_TIM4 BIT(11)

#define TIM_CON_TM BITS(4, 7)
#define TIM_CON_TM_TIM1 BIT(4)
#define TIM_CON_TM_TIM2 BIT(5)
#define TIM_CON_TM_TIM3 BIT(6)
#define TIM_CON_TM_TIM4 BIT(7)

#define TIM_CON_TE BITS(0, 3)
#define TIM_CON_TE_TIM1 BIT(0)
#define TIM_CON_TE_TIM2 BIT(1)
#define TIM_CON_TE_TIM3 BIT(2)
#define TIM_CON_TE_TIM4 BIT(3)

#define TIM_INTFLAG BITS(0, 3)
#define TIM_INTFLAG_TIM1 BIT(0)
#define TIM_INTFLAG_TIM2 BIT(1)
#define TIM_INTFLAG_TIM3 BIT(2)
#define TIM_INTFLAG_TIM4 BIT(3)

#define TIM_INTCLR BITS(0, 3)
#define TIM_INTCLR_TIM1 BIT(0)
#define TIM_INTCLR_TIM2 BIT(1)
#define TIM_INTCLR_TIM3 BIT(2)
#define TIM_INTCLR_TIM4 BIT(3)

// extend define
#define TIM_TM_AUTO_RUN 0
#define TIM_TM_AUTO_LOAD 1

#define TIM_CNT_POLARITY_HIGH 0
#define TIM_CNT_POLARITY_LOW 1

#define TIM1_CNT_PORT_P8_P9 0
#define TIM2_CNT_PORT_P10_P11 1
#define TIM3_CNT_PORT_P0_P1 2
#define TIM4_CNT_PORT_P6_P7 3

#define TIM1_PWM_PORT_P8_P9 0
#define TIM2_PWM_PORT_P10_P11 1
#define TIM2_PWM_PORT_P4_P5 2
#define TIM3_PWM_PORT_P14_P15 3
#define TIM3_PWM_PORT_P16_P13 4
#define TIM4_PWM_PORT_P6_P7 5

#define TIM_PWM_POL_PWM0_PWM1 0
#define TIM_PWM_POL_NPWM0_PWM1 1
#define TIM_PWM_POL_PWM0_NPWM1 2
#define TIM_PWM_POL_NPWM0_NPWM1 3

// extern function declare

void TIM_TimerInit(TIM_Type *pTim, int mode, int del);
void TIM_CounterInit(TIM_Type *pTim, int cntPolarity, int portSel);
void TIM_PWMInit(TIM_Type *pTim, int pwmPolarity, int freq, int duty,
                 int portSel, int dtGap);
void TIM_DeInit(TIM_Type *pTim);
void TIM_EnableControl(TIM_Type *pTim, int iCtrl);
void TIM_EnableIRQ(TIM_Type *pTim);
void TIM_DisableIRQ(TIM_Type *pTim);
void TIM_PauseCntControl(TIM_Type *pTim, ControlStatus ctl);
FlagStatus TIM_GetIntFlag(TIM_Type *pTim);
void TIM_ClrIntFlag(TIM_Type *pTim);

#endif
