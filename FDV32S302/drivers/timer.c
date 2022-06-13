/**
 * @file timer.c
 * @author
 * @brief
 * @version 0.1
 * @date 2021-07-16
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "sysc.h"
#include "timer.h"

/**
 * @brief  timer init
 *
 * @param pTim :TIM1-2
 * @param del :us
 */
void TIM_TimerInit(TIM_Type *pTim, int mode, int del)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2))
	PARAM_CHECK((mode != TIM_TM_AUTO_RUN) && (mode != TIM_TM_AUTO_LOAD));

	SystemCoreClockUpdate();
	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK;

	if (pTim == TIM1)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
		int pclk = SYSC_GetAPBCLK() / ((SYSC->TIMCLKDIV & 0xff) + 1);
		int cnt = (long long)del * pclk / 1000000;
		PARAM_CHECK(cnt < 1 || cnt > 0xffff);
		if (mode == TIM_TM_AUTO_RUN)
		{
			TIMERS->CON &= ~TIM_CON_TM_TIM1;
			TIM1->CTCG1 = cnt & 0xffff;
			TIM1->CTCG2 = cnt >> 16;
		}
		else
		{
			TIMERS->CON |= TIM_CON_TM_TIM1;
			TIM1->CTCG1 = cnt;
		}
	}
	else if (pTim == TIM2)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
		int pclk = SYSC_GetAPBCLK() / ((SYSC->TIMCLKDIV >> 8) + 1);
		int cnt = (long long)del * pclk / 1000000;
		PARAM_CHECK(cnt < 1 || cnt > 0xffff);
		if (mode == TIM_TM_AUTO_RUN)
		{
			TIMERS->CON &= ~TIM_CON_TM_TIM2;
			TIM2->CTCG1 = cnt & 0xffff;
			TIM2->CTCG2 = cnt >> 16;
		}
		else
		{
			TIMERS->CON |= TIM_CON_TM_TIM2;
			TIM2->CTCG1 = cnt;
		}
	}
}

/**
 * @brief counter init
 *
 * @param pTim :TIM1-2
 * @param cntPolarity :TIM_CNT_POLARITY_HIGH , TIM_CNT_POLARITY_LOW
 */
void TIM_CounterInit(TIM_Type *pTim, int cntPolarity)
{
	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK;
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2))
	if (pTim == TIM1)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
		TIMERS->CON &= ~TIM_CON_TM_TIM1;
		PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) && (cntPolarity != TIM_CNT_POLARITY_LOW));
		if (cntPolarity == TIM_CNT_POLARITY_HIGH)
		{
			TIMERS->CON &= ~TIM_CON_EXTPOL_TIM1;
		}
		else
		{
			TIMERS->CON |= TIM_CON_EXTPOL_TIM1;
		}
		TIMERS->CON |= TIM_CON_EXTEN_TIM1;
	}
	else if (pTim == TIM2)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
		TIMERS->CON &= ~TIM_CON_TM_TIM2;
		PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) && (cntPolarity != TIM_CNT_POLARITY_LOW));
		if (cntPolarity == TIM_CNT_POLARITY_HIGH)
		{
			TIMERS->CON &= ~TIM_CON_EXTPOL_TIM2;
		}
		else
		{
			TIMERS->CON |= TIM_CON_EXTPOL_TIM2;
		}

		TIMERS->CON |= TIM_CON_EXTEN_TIM2;
	}
}

/**
 * @brief pwm init
 *
 * @param pTim :TIM1-2
 * @param pwmPolarity :TIM_PMW_POL_xxxx;
 * @param freq : Hz
 * @param duty :exp:duty=50 (50%)
 * @param dtGap :us
 */
void TIM_PWMInit(TIM_Type *pTim, int pwmPolarity, int freq, int duty, int dtGap)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	SystemCoreClockUpdate();
	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK;
	if (pTim == TIM1)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
		TIMERS->CON |= TIM_CON_TM_TIM1;
		TIMERS->CON |= TIM_CON_PWM_TIM1;

		int div = SYSC->TIMCLKDIV & 0xff;
		int tcnt, pclk;
		while (1)
		{
			pclk = SYSC_GetAPBCLK() / (div + 1);
			tcnt = pclk / (freq);
			if (tcnt > 0xffff)
			{
				++div;
			}
			else
			{
				if (tcnt < 1)
					--div;
				PARAM_CHECK(div < 0);
				break;
			}
		}
		SYSC->TIMCLKDIV &= ~SYSC_TIM1CLKDIV;
		SYSC->TIMCLKDIV |= div;
		TIM1->CTCG2 = tcnt * (duty) / 100;
		TIM1->CTCG1 = tcnt - (TIM1->CTCG2);
		TIM1->PWCON &= ~TIM_PWCON_PWMCPOL;
		PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
		            (pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
		if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1)
		{
			TIM1->PWCON |= (1 << 17);
		}
		else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1)
		{
			TIM1->PWCON |= (2 << 17);
		}
		else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1)
		{
			TIM1->PWCON |= (3 << 17);
		}
		if (dtGap > 0)
		{
			TIM1->PWCON |= (1 << 16);
			tcnt = (long long )pclk * dtGap / 1000000 ;
			PARAM_CHECK(tcnt > 0xffff);
			TIM1->PWCON &= ~0xffff;
			TIM1->PWCON |= tcnt;
		}
		else
		{
			TIM1->PWCON &= ~(1 << 16);
		}
	}
	else if (pTim == TIM2)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
		TIMERS->CON |= TIM_CON_TM_TIM2;
		TIMERS->CON |= TIM_CON_PWM_TIM2;

		int div = SYSC->TIMCLKDIV >> 8;
		int tcnt, pclk;
		while (1)
		{
			pclk = SYSC_GetAPBCLK() / (div + 1);
			tcnt = pclk / (freq);
			if (tcnt > 0xffff)
			{
				++div;
			}
			else
			{
				if (tcnt < 1)
					--div;
				PARAM_CHECK(div < 0);
				break;
			}
		}
		SYSC->TIMCLKDIV &= ~SYSC_TIM2CLKDIV;
		SYSC->TIMCLKDIV |= div << 8;
		TIM2->CTCG2 = tcnt * (duty) / 100;
		TIM2->CTCG1 = tcnt - (TIM2->CTCG2);

		TIM2->PWCON &= ~TIM_PWCON_PWMCPOL;
		PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
		            (pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
		if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1)
		{
			TIM2->PWCON |= (1 << 17);
		}
		else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1)
		{
			TIM2->PWCON |= (2 << 17);
		}
		else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1)
		{
			TIM2->PWCON |= (3 << 17);
		}
		if (dtGap > 0)
		{
			TIM2->PWCON |= (1 << 16);
			tcnt =  (long long )pclk * dtGap / 1000000 ;
			PARAM_CHECK(tcnt > 0xffff);
			TIM2->PWCON &= ~0xffff;
			TIM2->PWCON |= tcnt;
		}
		else
		{
			TIM2->PWCON &= ~(1 << 16);
		}
	}
}
/**
 * @brief Timer deinit
 *
 * @param pTim:TIM1-2
 */
void TIM_DeInit(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	if (pTim == TIM1)
	{
		TIMERS->CON &= ~(TIM_CON_TE_TIM1 | TIM_CON_TM_TIM1 | TIM_CON_PWM_TIM1 | TIM_CON_EXTEN_TIM1
		                 | TIM_CON_EXTPOL_TIM1 | TIM_CON_PAUSE_TIM1);
	}
	else if (pTim == TIM2)
	{
		TIMERS->CON &= ~(TIM_CON_TE_TIM2 | TIM_CON_TM_TIM2 | TIM_CON_PWM_TIM1 | TIM_CON_EXTEN_TIM1
		                 | TIM_CON_EXTPOL_TIM1 | TIM_CON_PAUSE_TIM1);
	}
	if ((TIMERS->CON & TIM_CON_TE) == 0)
	{
		SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM_PCK;
	}
}
/**
 * @brief 使能控制
 *
 * @param pTim : TIM1-2
 * @param iCtrl ：ENABLE or DISABLE
 */
void TIM_EnableControl(TIM_Type *pTim, int iCtrl)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	if (iCtrl == ENABLE)
	{
		switch ((int)pTim)
		{
		case (int)TIM1:
			TIMERS->CON |= TIM_CON_TE_TIM1;
			break;
		case (int)TIM2:
			TIMERS->CON |= TIM_CON_TE_TIM2;
			break;
		}
	}
	else
	{
		switch ((int)pTim)
		{
		case (int)TIM1:
			TIMERS->CON &= ~TIM_CON_TE_TIM1;
			break;
		case (int)TIM2:
			TIMERS->CON &= ~TIM_CON_TE_TIM2;
			break;
		}
	}
}
/**
 * @brief Timer interrupt enable
 *
 * @param pTim :TIM1-2
 */
void TIM_EnableIRQ(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	if (pTim == TIM1)
	{
		TIMERS->CON |= TIM_CON_IE_TIM1;
	}
	else if (pTim == TIM2)
	{
		TIMERS->CON |= TIM_CON_IE_TIM2;
	}
}

/**
 * @brief Timer interrupt disable
 *
 * @param pTim:TIM1-2
 */
void TIM_DisableIRQ(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	if (pTim == TIM1)
	{
		TIMERS->CON &= ~TIM_CON_IE_TIM1;
	}
	else if (pTim == TIM2)
	{
		TIMERS->CON &= ~TIM_CON_IE_TIM2;
	}
}

/**
 * @brief Timer stop counter
 *
 * @param pTim :TIM1-2
 * @param ctr :ENABLE , DISABLE
 */
void TIM_PauseCntControl(TIM_Type *pTim, ControlStatus ctl)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	PARAM_CHECK((ctl != ENABLE) && (ctl != DISABLE));
	if (pTim == TIM1)
	{
		if (ctl == ENABLE)
		{
			TIMERS->CON |= TIM_CON_PAUSE_TIM1;
		}
		else
		{
			TIMERS->CON &= ~TIM_CON_PAUSE_TIM1;
		}
	}
	else if (pTim == TIM2)
	{
		if (ctl == ENABLE)
		{
			TIMERS->CON |= TIM_CON_PAUSE_TIM2;
		}
		else
		{
			TIMERS->CON &= ~TIM_CON_PAUSE_TIM2;
		}
	}
}

/**
 * @brief get timer interrupt flag
 *
 * @param pTim :TIM1-2
 * @return FlagStatus : SET , RESET
 */
FlagStatus TIM_GetIntFlag(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	if (pTim == TIM1)
	{
		return (TIMERS->INTFLAG & TIM_INTFLAG_TIM1) ? SET : RESET;
	}
	else if (pTim == TIM2)
	{
		return (TIMERS->INTFLAG & TIM_INTFLAG_TIM2) ? SET : RESET;
	}
}
/**
 * @brief clear timer interrupt flag
 *
 * @param pTim :TIM1-2
 */
void TIM_ClrIntFlag(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	if (pTim == TIM1)
	{
		TIMERS->INTCLR = TIM_INTCLR_TIM1;
		while(TIMERS->INTFLAG & TIM_INTFLAG_TIM1);
	}
	else if (pTim == TIM2)
	{
		TIMERS->INTCLR = TIM_INTCLR_TIM2;
		while(TIMERS->INTFLAG & TIM_INTFLAG_TIM2);
	}
}
/**
 * @brief 获得当前计数值
 *
 * @param pTim TIM1、TIM2
 * @return u32 计数结果
 */
u32 TIM_GetCurentCounter(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
	if (pTim == TIM1)
	{
		return TIM1->CTVAL;
	}
	else if (pTim == TIM2)
	{
		return TIM2->CTVAL;
	}
}
