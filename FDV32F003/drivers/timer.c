/**
 * @file timer.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "sysc.h"
#include "timer.h"
#include "iom.h"

/**
 * @brief  timer timing init
 *
 * @param timer :timer 1-4
 * @param delay :us
 */
void Timer_timing_Init(Timer_t timer, int delay)
{
	PARAM_CHECK((timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));

	int iDiv, iTcks;

	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER_PCKEN;

	switch (timer)
	{
	case TIMER0:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER0_PCKEN;
		TIMERS->T0CR &= ~TIMER0_T0CR_T0EN;

		TIMERS->T0CR |= TIMER0_T0CR_T0RLDEN;

		iDiv = 4;
		if (!(TIMERS->T0CR & TIMER0_T0CR_PSA))
		{
			iTcks = (TIMERS->T0CR & TIMER0_T0CR_PS) >> TIMER0_T0CR_PS_pos;
			iDiv  = 2;
			for (int i = 0; i < iTcks; i++)
				iDiv *= 2;
		}
		TIMERS->T0RLD = 0x100 - delay * SYSC_GetAPBCLK() / (iDiv * 1000000);

		TIMERS->T0 = TIMERS->T0RLD;
		TIMERS->T0CR |= TIMER0_T0CR_T0EN;
		break;
	case TIMER1:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER1_PCKEN;
		TIM1->TCR &= ~TIMER_TCR_PWMON;
		TIM1->TCR &= ~TIMER_TCR_TGC;
		TIM1->TCR &= ~TIMER_TCR_TCS;

		iTcks = (TIM1->TCR & TIMER_TCR_TCKS) >> TIMER_TCR_TCKS_pos;
		iDiv  = 1;
		for (int i = 0; i < iTcks; i++)
			iDiv *= 2;
		TIM1->PWMPD = delay * SYSC_GetAPBCLK() / (iDiv * 1000000);

		TIM1->TN = 0;
		TIM1->TCR |= TIMER_TCR_TON;
		break;
	case TIMER2:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER2_PCKEN;
		TIM2->TCR &= ~TIMER_TCR_PWMON;
		TIM2->TCR &= ~TIMER_TCR_TGC;
		TIM2->TCR &= ~TIMER_TCR_TCS;

		iTcks = (TIM2->TCR & TIMER_TCR_TCKS) >> TIMER_TCR_TCKS_pos;
		iDiv  = 1;
		for (int i = 0; i < iTcks; i++)
			iDiv *= 2;
		TIM2->PWMPD = delay * SYSC_GetAPBCLK() / (iDiv * 1000000);

		TIM2->TN = 0;
		TIM2->TCR |= TIMER_TCR_TON;
		break;
	case TIMER3:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER3_PCKEN;
		TIM3->TCR &= ~TIMER_TCR_PWMON;
		TIM3->TCR &= ~TIMER_TCR_TGC;
		TIM3->TCR &= ~TIMER_TCR_TCS;

		iTcks = (TIM3->TCR & TIMER_TCR_TCKS) >> TIMER_TCR_TCKS_pos;
		iDiv  = 1;
		for (int i = 0; i < iTcks; i++)
			iDiv *= 2;
		TIM3->PWMPD = delay * SYSC_GetAPBCLK() / (iDiv * 1000000);

		TIM3->TN = 0;
		TIM3->TCR |= TIMER_TCR_TON;
		break;
	case TIMER4:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER4_PCKEN;
		TIM4->TCR &= ~TIMER_TCR_PWMON;
		TIM4->TCR &= ~TIMER_TCR_TGC;
		TIM4->TCR &= ~TIMER_TCR_TCS;

		iTcks = (TIM4->TCR & TIMER_TCR_TCKS) >> TIMER_TCR_TCKS_pos;
		iDiv  = 1;
		for (int i = 0; i < iTcks; i++)
			iDiv *= 2;
		TIM4->PWMPD = delay * SYSC_GetAPBCLK() / (iDiv * 1000000);

		TIM4->TN = 0;
		TIM4->TCR |= TIMER_TCR_TON;
		break;
	default:
		break;
	}
}

/**
 * @brief  timer Count init
 *
 * @param timer :timer 0-4
 * @param count :count
 */
void Timer_Count_Init(Timer_t timer, int count)
{
	PARAM_CHECK((timer != TIMER0) && (timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));

	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER_PCKEN;

	switch (timer)
	{
	case TIMER0:
		break;
	case TIMER1:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER1_PCKEN;
		TIM1->TCR &= ~TIMER_TCR_PWMON;
		TIM1->TCR &= ~TIMER_TCR_TGC;

		TIM1->TCR |= TIMER_TCR_TCS;

		TIM1->PWMPD = count;

		TIM1->TN = 0;
		TIM1->TCR |= TIMER_TCR_TON;
		break;
	case TIMER2:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER2_PCKEN;
		TIM2->TCR &= ~TIMER_TCR_PWMON;
		TIM2->TCR &= ~TIMER_TCR_TGC;

		TIM2->TCR |= TIMER_TCR_TCS;

		TIM2->PWMPD = count;

		TIM2->TN = 0;
		TIM2->TCR |= TIMER_TCR_TON;
		break;
	case TIMER3:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER3_PCKEN;
		TIM3->TCR &= ~TIMER_TCR_PWMON;
		TIM3->TCR &= ~TIMER_TCR_TGC;

		TIM3->TCR |= TIMER_TCR_TCS;

		TIM3->PWMPD = count;

		TIM3->TN = 0;
		TIM3->TCR |= TIMER_TCR_TON;
		break;
	case TIMER4:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER4_PCKEN;
		TIM4->TCR &= ~TIMER_TCR_PWMON;
		TIM4->TCR &= ~TIMER_TCR_TGC;

		TIM4->TCR |= TIMER_TCR_TCS;

		TIM4->PWMPD = count;

		TIM4->TN = 0;
		TIM4->TCR |= TIMER_TCR_TON;
		break;
	default:
		break;
	}
}

/**
 * @brief pwm init
 *
 * @param timer :timer 0-4
 * @param pwmPolarity :TIM_PMW_POL_xxxx;
 * @param freq : kHz
 * @param duty :exp:duty=50 (50%)
 * @param portSel :TIMN_PWM_PORT_xxxx;
 * @param dtGap :us
 */
void Timer_PWMInit(Timer_t timer, int freq, int duty)
{
	PARAM_CHECK((timer != TIMER0) && (timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));

	int iDiv, iTcks;

	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER_PCKEN;

	switch (timer)
	{
	case TIMER0:
		break;
	case TIMER1:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER1_PCKEN;
		TIM1->TCR &= ~TIMER_TCR_TGC;
		TIM1->TCR &= ~TIMER_TCR_TCS;

		TIM1->TCR |= TIMER_TCR_PWMON;

		iTcks = (TIM1->TCR & TIMER_TCR_TCKS) >> TIMER_TCR_TCKS_pos;
		iDiv  = 1;
		for (int i = 0; i < iTcks; i++)
			iDiv *= 2;
		TIM1->PWMPD = SYSC_GetAPBCLK() / (iDiv * freq * 1000);
		TIM1->PWMDC = SYSC_GetAPBCLK() * duty / (iDiv * freq * 1000 * 100);

		TIM1->TN = 0;
		TIM1->TCR |= TIMER_TCR_TON;
		break;
	case TIMER2:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER2_PCKEN;
		TIM2->TCR &= ~TIMER_TCR_TGC;
		TIM2->TCR &= ~TIMER_TCR_TCS;

		TIM2->TCR |= TIMER_TCR_PWMON;

		iTcks = (TIM2->TCR & TIMER_TCR_TCKS) >> TIMER_TCR_TCKS_pos;
		iDiv  = 1;
		for (int i = 0; i < iTcks; i++)
			iDiv *= 2;
		TIM2->PWMPD = SYSC_GetAPBCLK() / (iDiv * freq * 1000);
		TIM2->PWMDC = SYSC_GetAPBCLK() * duty / (iDiv * freq * 1000 * 100);

		TIM2->TN = 0;
		TIM2->TCR |= TIMER_TCR_TON;
		break;
	case TIMER3:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER3_PCKEN;
		TIM3->TCR &= ~TIMER_TCR_TGC;
		TIM3->TCR &= ~TIMER_TCR_TCS;

		TIM3->TCR |= TIMER_TCR_PWMON;

		iTcks = (TIM3->TCR & TIMER_TCR_TCKS) >> TIMER_TCR_TCKS_pos;
		iDiv  = 1;
		for (int i = 0; i < iTcks; i++)
			iDiv *= 2;
		TIM3->PWMPD = SYSC_GetAPBCLK() / (iDiv * freq * 1000);
		TIM3->PWMDC = SYSC_GetAPBCLK() * duty / (iDiv * freq * 1000 * 100);

		TIM3->TN = 0;
		TIM3->TCR |= TIMER_TCR_TON;
		break;
	case TIMER4:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER4_PCKEN;
		TIM4->TCR &= ~TIMER_TCR_TGC;
		TIM4->TCR &= ~TIMER_TCR_TCS;

		TIM4->TCR |= TIMER_TCR_PWMON;

		iTcks = (TIM4->TCR & TIMER_TCR_TCKS) >> TIMER_TCR_TCKS_pos;
		iDiv  = 1;
		for (int i = 0; i < iTcks; i++)
			iDiv *= 2;
		TIM4->PWMPD = SYSC_GetAPBCLK() / (iDiv * freq * 1000);
		TIM4->PWMDC = SYSC_GetAPBCLK() * duty / (iDiv * freq * 1000 * 100);

		TIM4->TN = 0;
		TIM4->TCR |= TIMER_TCR_TON;
		break;
	default:
		break;
	}
}
/**
 * @brief Timer deinit
 *
 * @param timer:timer 0-4
 */
void Timer_DeInit(Timer_t timer)
{
	PARAM_CHECK((timer != TIMER0) && (timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));

	switch (timer)
	{
	case TIMER0:
		TIMERS->T0CR &= ~TIMER0_T0CR_T0EN;
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER0_PCKEN;
		break;
	case TIMER1:
		TIM1->TCR &= ~TIMER_TCR_TON;
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER1_PCKEN;
		break;
	case TIMER2:
		TIM2->TCR &= ~TIMER_TCR_TON;
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER2_PCKEN;
		break;
	case TIMER3:
		TIM3->TCR &= ~TIMER_TCR_TON;
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER3_PCKEN;
		break;
	case TIMER4:
		TIM4->TCR &= ~TIMER_TCR_TON;
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER4_PCKEN;
		break;
	default:
		break;
	}
}
/**
 * @brief timer enable control
 *
 * @param timer : timer 0-4
 * @param iCtrl ENABLE or DISABLE
 */
void Timer_EnableControl(Timer_t timer, int iCtrl)
{
	PARAM_CHECK((timer != TIMER0) && (timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));
	switch (timer)
	{
	case TIMER0:
		TIMERS->TIF = (1 << 0);
		if (iCtrl == ENABLE)
		{
			TIMERS->T0CR |= TIMER0_CTRL_EN;
		}
		else
		{
			TIMERS->T0CR &= ~TIMER0_CTRL_EN;
		}
		break;
	case TIMER1:
		if (iCtrl == ENABLE)
		{
			TIMERS->TCR1 |= TIMER1_CTRL_EN;
		}
		else
		{
			TIMERS->TCR1 &= ~TIMER1_CTRL_EN;
		}
		break;
	case TIMER2:
		if (iCtrl == ENABLE)
		{
			TIMERS->TCR2 |= TIMER2_CTRL_EN;
		}
		else
		{
			TIMERS->TCR2 &= ~TIMER2_CTRL_EN;
		}
		break;
	case TIMER3:
		if (iCtrl == ENABLE)
		{
			TIMERS->TCR3 |= TIMER3_CTRL_EN;
		}
		else
		{
			TIMERS->TCR3 &= ~TIMER3_CTRL_EN;
		}
		break;
	case TIMER4:
		if (iCtrl == ENABLE)
		{
			TIMERS->TCR4 |= TIMER4_CTRL_EN;
		}
		else
		{
			TIMERS->TCR4 &= ~TIMER4_CTRL_EN;
		}
		break;
	default:
		break;
	}
}
/**
 * @brief Timer interrupt enable
 *
 * @param timer:timer 0-4
 */
void Timer_EnableIRQ(Timer_t timer)
{
	PARAM_CHECK((timer != TIMER0) && (timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));
	switch (timer)
	{
	case TIMER0:
		TIMERS->TIE |= (1 << 0);
		break;
	case TIMER1:
		TIMERS->TIE |= (1 << 1);
		break;
	case TIMER2:
		TIMERS->TIE |= (1 << 2);
		break;
	case TIMER3:
		TIMERS->TIE |= (1 << 3);
		break;
	case TIMER4:
		TIMERS->TIE |= (1 << 4);
		break;
	default:
		break;
	}
}

/**
 * @brief Timer interrupt disable
 *
 * @param timer:timer 0-4
 */
void Timer_DisableIRQ(Timer_t timer)
{
	PARAM_CHECK((timer != TIMER0) && (timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));
	switch (timer)
	{
	case TIMER0:
		TIMERS->TIE &= ~(1 << 0);
		break;
	case TIMER1:
		TIMERS->TIE &= ~(1 << 1);
		break;
	case TIMER2:
		TIMERS->TIE &= ~(1 << 2);
		break;
	case TIMER3:
		TIMERS->TIE &= ~(1 << 3);
		break;
	case TIMER4:
		TIMERS->TIE &= ~(1 << 4);
		break;
	default:
		break;
	}
}

/**
 * @brief get timer interrupt flag
 *
 * @param timer :timer 0-4
 * @return FlagStatus : SET , RESET
 */
FlagStatus Timer_GetIntFlag(Timer_t timer)
{
	PARAM_CHECK((timer != TIMER0) && (timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));

	int ret = RESET;

	if (TIMER0 == timer)
	{
		ret = (TIMERS->TIF & (1 << 0) ? SET : RESET);
	}
	else if (TIMER1 == timer)
	{
		ret = (TIMERS->TIF & (1 << 1) ? SET : RESET);
	}
	else if (TIMER2 == timer)
	{
		ret = (TIMERS->TIF & (1 << 2) ? SET : RESET);
	}
	else if (TIMER3 == timer)
	{
		ret = (TIMERS->TIF & (1 << 3) ? SET : RESET);
	}
	else if (TIMER4 == timer)
	{
		ret = (TIMERS->TIF & (1 << 4) ? SET : RESET);
	}

	return (FlagStatus)ret;
}
/**
 * @brief clear timer interrupt flag
 *
 * @param timer :timer 0-4
 */
void Timer_ClrIntFlag(Timer_t timer)
{
	PARAM_CHECK((timer != TIMER0) && (timer != TIMER1) && (timer != TIMER2) && (timer != TIMER3) && (timer != TIMER4));

	switch (timer)
	{
	case TIMER0:
		TIMERS->TIF = (1 << 0);
		break;
	case TIMER1:
		TIMERS->TIF = (1 << 1);
		break;
	case TIMER2:
		TIMERS->TIF = (1 << 2);
		break;
	case TIMER3:
		TIMERS->TIF = (1 << 3);
		break;
	case TIMER4:
		TIMERS->TIF = (1 << 4);
		break;
	default:
		break;
	}
}
