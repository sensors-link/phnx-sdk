/**
 * @file timer.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#ifndef __TIMER_H__
#define __TIMER_H__
#include "../include/phnx05.h"

typedef enum timer
{
	TIMER0 = 0,
	TIMER1 = 1,
	TIMER2 = 2,
	TIMER3 = 3,
	TIMER4 = 4,
	TIMER_MAX,
} Timer_t;

#define TIMER0_CTRL_EN BIT(7)
#define TIMER1_CTRL_EN BIT(0)
#define TIMER2_CTRL_EN BIT(0)
#define TIMER3_CTRL_EN BIT(0)
#define TIMER4_CTRL_EN BIT(0)

// reg TIE
#define Timer_tIE  BITS(0, 4)
#define TIMER0_TIE BIT(0)
#define TIMER1_TIE BIT(1)
#define TIMER2_TIE BIT(2)
#define TIMER3_TIE BIT(3)
#define TIMER4_TIE BIT(4)

// reg TIF
#define Timer_tIF  BITS(0, 4)
#define TIMER0_TIF BIT(0)
#define TIMER1_TIF BIT(1)
#define TIMER2_TIF BIT(2)
#define TIMER3_TIF BIT(3)
#define TIMER4_TIF BIT(4)

// reg T0CR for timer0
#define TIMER0_T0CR_T0EN	BIT(7)
#define TIMER0_T0CR_T0RLDEN BIT(6)
#define TIMER0_T0CR_PSA		BIT(3)
#define TIMER0_T0CR_PS		BITS(0, 2)

// reg T0 for timer0
#define TIMER0_T0_T0 BITS(0, 7)

// reg T0RLD for timer0
#define TIMER0_T0RLD_T0RLD BITS(0, 7)

// reg TCR for timer1-timer4
#define Timer_tCR_PWMON BIT(7)
#define Timer_tCR_INTSE BIT(6)
#define Timer_tCR_TGC	BIT(4)
#define Timer_tCR_TCKS	BITS(2, 3)
#define Timer_tCR_TCS	BIT(1)
#define Timer_tCR_TON	BIT(0)

// reg TN for timer1-timer4
#define Timer_tN_PWMON BITS(0, 15)

// reg PWMPD for timer1-timer4
#define TIMER_PWMPD BITS(0, 15)

// reg PWMDC for timer1-timer4
#define TIMER_PWMDC BITS(0, 15)

// timer function declare
void	   Timer_timing_Init(Timer_t timer, int delay);
void	   Timer_Count_Init(Timer_t timer, int count);
void	   Timer_PWMInit(Timer_t timer, int freq, int duty);
void	   Timer_EnableControl(Timer_t timer, int iCtrl);
void	   Timer_EnableIRQ(Timer_t timer);
void	   Timer_DeInit(Timer_t timer);
void	   Timer_DisableIRQ(Timer_t timer);
FlagStatus Timer_GetIntFlag(Timer_t timer);
void	   Timer_ClrIntFlag(Timer_t timer);

#endif /*__TIMER_H__ */
