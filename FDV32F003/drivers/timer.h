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
#include "phnx05.h"

// reg T0CR for timer0
#define TIMER0_T0CR_T0EN	BIT(7)
#define TIMER0_T0CR_T0RLDEN BIT(6)
#define TIMER0_T0CR_PSA		BIT(3)
#define TIMER0_T0CR_PS		BITS(0, 2)

#define TIMER0_T0CR_PS_pos (0)

// reg T0 for timer0
#define TIMER0_T0_T0 BITS(0, 7)

// reg T0RLD for timer0
#define TIMER0_T0RLD_T0RLD BITS(0, 7)

// reg TIE
#define TIMER4_TIE BIT(4)
#define TIMER3_TIE BIT(3)
#define TIMER2_TIE BIT(2)
#define TIMER1_TIE BIT(1)
#define TIMER0_TIE BIT(0)

// reg TIF
#define TIMER4_TIF BIT(4)
#define TIMER3_TIF BIT(3)
#define TIMER2_TIF BIT(2)
#define TIMER1_TIF BIT(1)
#define TIMER0_TIF BIT(0)

// reg TCR for timer1-timer4
#define TIMER_TCR_PWMON BIT(7)
#define TIMER_TCR_INTSE BIT(6)
#define TIMER_TCR_TGC	BIT(4)
#define TIMER_TCR_TCKS	BITS(2, 3)
#define TIMER_TCR_TCS	BIT(1)
#define TIMER_TCR_TON	BIT(0)

#define TIMER_TCR_TCKS_pos (2)

// reg TN for timer1-timer4
#define Timer_tN_PWMON BITS(0, 15)

// reg PWMPD for timer1-timer4
#define TIMER_PWMPD BITS(0, 15)

// reg PWMDC for timer1-timer4
#define TIMER_PWMDC BITS(0, 15)

#define TIMER0_CTRL_EN BIT(7)
#define TIMER1_CTRL_EN BIT(0)
#define TIMER2_CTRL_EN BIT(0)
#define TIMER3_CTRL_EN BIT(0)
#define TIMER4_CTRL_EN BIT(0)

typedef enum timer
{
	TIMER0 = 0,
	TIMER1 = 1,
	TIMER2 = 2,
	TIMER3 = 3,
	TIMER4 = 4,
	TIMER_MAX,
} Timer_t;

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
