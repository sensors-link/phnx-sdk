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
void TIM_TimerInit(TIM_Type *pTim, int mode, int del)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
	PARAM_CHECK((mode != TIM_TM_AUTO_RUN) && (mode != TIM_TM_AUTO_LOAD));

	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK;

	SystemCoreClockUpdate();

	if (pTim == TIM1)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
		int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
		int cnt	 = (long long)del * pclk / 1000000;
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
		int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
		int cnt	 = (long long)del * pclk / 1000000;
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
	else if (pTim == TIM3)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM3_CNT;
		int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
		int cnt	 = (long long)del * pclk / 1000000;
		PARAM_CHECK(cnt < 1 || cnt > 0xffff);
		if (mode == TIM_TM_AUTO_RUN)
		{
			TIMERS->CON &= ~TIM_CON_TM_TIM3;
			TIM3->CTCG1 = cnt & 0xffff;
			TIM3->CTCG2 = cnt >> 16;
		}
		else
		{
			TIMERS->CON |= TIM_CON_TM_TIM3;
			TIM3->CTCG1 = cnt;
		}
	}
	else
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM4_CNT;
		int pclk = SYSC_GetAHBCLK() / (SYSC->BZTIMCLKDIV + 1);
		int cnt	 = (long long)del * pclk / 1000000;
		PARAM_CHECK(cnt < 1 || cnt > 0xffff);
		if (mode == TIM_TM_AUTO_RUN)
		{
			TIMERS->CON &= ~TIM_CON_TM_TIM4;
			TIM4->CTCG1 = cnt & 0xffff;
			TIM4->CTCG2 = cnt >> 16;
		}
		else
		{
			TIMERS->CON |= TIM_CON_TM_TIM4;
			TIM4->CTCG1 = cnt;
		}
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
void TIM_CounterInit(TIM_Type *pTim, int cntPolarity)
{
	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK;
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
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
	else if (pTim == TIM3)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM3_CNT;
		TIMERS->CON &= ~TIM_CON_TM_TIM3;
		PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) && (cntPolarity != TIM_CNT_POLARITY_LOW));
		if (cntPolarity == TIM_CNT_POLARITY_HIGH)
		{
			TIMERS->CON &= ~TIM_CON_EXTPOL_TIM3;
		}
		else
		{
			TIMERS->CON |= TIM_CON_EXTPOL_TIM3;
		}
		TIMERS->CON |= TIM_CON_EXTEN_TIM3;
	}
	else
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM4_CNT;
		TIMERS->CON &= ~TIM_CON_TM_TIM4;
		PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) && (cntPolarity != TIM_CNT_POLARITY_LOW));
		if (cntPolarity == TIM_CNT_POLARITY_HIGH)
		{
			TIMERS->CON &= ~TIM_CON_EXTPOL_TIM4;
		}
		else
		{
			TIMERS->CON |= TIM_CON_EXTPOL_TIM4;
		}
		TIMERS->CON |= TIM_CON_EXTEN_TIM4;
	}
}

/**
 * @brief pwm init
 *
 * @param pTim :TIM1-4
 * @param pwmPolarity :TIM_PMW_POL_xxxx;
 * @param freq : Hz
 * @param duty :exp:duty=50 (50%)
 * @param dtGap :us
 */
void TIM_PWMInit(TIM_Type *pTim, int pwmPolarity, int freq, int duty, int dtGap)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
	SystemCoreClockUpdate();
	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK;
	if (pTim == TIM1)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
		TIMERS->CON |= TIM_CON_TM_TIM1;
		TIMERS->CON |= TIM_CON_PWM_TIM1;

		int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
		int tcnt = pclk / (freq);
		PARAM_CHECK(tcnt < 2);

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
			tcnt = (long long)pclk * dtGap / 1000000;
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

		int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
		int tcnt = pclk / (freq);
		PARAM_CHECK(tcnt < 2);

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
			tcnt = (long long)pclk * dtGap / 1000000;
			PARAM_CHECK(tcnt > 0xffff);
			TIM2->PWCON &= ~0xffff;
			TIM2->PWCON |= tcnt;
		}
		else
		{
			TIM2->PWCON &= ~(1 << 16);
		}
	}
	else if (pTim == TIM3)
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM3_CNT;
		TIMERS->CON |= TIM_CON_TM_TIM3;
		TIMERS->CON |= TIM_CON_PWM_TIM3;

		int pclk = SYSC_GetAPBCLK() / (SYSC->TIMCLKDIV + 1);
		int tcnt = pclk / (freq);
		PARAM_CHECK(tcnt < 2);

		TIM3->CTCG2 = tcnt * (duty) / 100;
		TIM3->CTCG1 = tcnt - (TIM3->CTCG2);
		TIM3->PWCON &= ~TIM_PWCON_PWMCPOL;
		PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
					(pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
		if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1)
		{
			TIM3->PWCON |= (1 << 17);
		}
		else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1)
		{
			TIM3->PWCON |= (2 << 17);
		}
		else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1)
		{
			TIM3->PWCON |= (3 << 17);
		}
		if (dtGap > 0)
		{
			TIM3->PWCON |= (1 << 16);
			tcnt = pclk / 1000000 * dtGap;
			PARAM_CHECK(tcnt > 0xffff);
			TIM3->PWCON &= ~0xffff;
			TIM3->PWCON |= tcnt;
		}
		else
		{
			TIM3->PWCON &= ~(1 << 16);
		}
	}
	else
	{
		SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM4_CNT;
		TIMERS->CON |= TIM_CON_TM_TIM4;
		TIMERS->CON |= TIM_CON_PWM_TIM4;

		int pclk = SYSC_GetAHBCLK() / (SYSC->BZTIMCLKDIV + 1);
		int tcnt = pclk / (freq);
		PARAM_CHECK(tcnt < 2);
		TIM4->CTCG2 = tcnt * (duty) / 100; //
		TIM4->CTCG1 = tcnt - (TIM4->CTCG2);

		TIM4->PWCON &= ~TIM_PWCON_PWMCPOL;
		PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
					(pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
		if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1)
		{
			TIM4->PWCON |= (1 << 17);
		}
		else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1)
		{
			TIM4->PWCON |= (2 << 17);
		}
		else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1)
		{
			TIM4->PWCON |= (4 << 17);
		}
		if (dtGap > 0)
		{
			TIM4->PWCON |= (1 << 16);
			tcnt = pclk / 1000000 * dtGap;
			PARAM_CHECK(tcnt > 0xffff);
			TIM4->PWCON &= ~0xffff;
			TIM4->PWCON |= tcnt;
		}
		else
		{
			TIM4->PWCON &= ~(1 << 16);
		}
	}
}
/**
 * @brief Timer deinit
 *
 * @param pTim:TIM1-4
 */
void TIM_DeInit(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
	if (pTim == TIM1)
	{
		TIMERS->CON &= ~TIM_CON_TE_TIM1;
		TIMERS->CON &= ~TIM_CON_TM_TIM1;
		TIMERS->CON &= ~TIM_CON_IE_TIM1;
		TIMERS->CON &= ~TIM_CON_PWM_TIM1;
		TIMERS->CON &= ~TIM_CON_EXTEN_TIM1;
		TIMERS->CON &= ~TIM_CON_EXTPOL_TIM1;
		TIMERS->CON &= ~TIM_CON_PAUSE_TIM1;
		SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM1_CNT;
	}
	else if (pTim == TIM2)
	{
		TIMERS->CON &= ~TIM_CON_TE_TIM2;
		TIMERS->CON &= ~TIM_CON_TM_TIM2;
		TIMERS->CON &= ~TIM_CON_IE_TIM2;
		TIMERS->CON &= ~TIM_CON_PWM_TIM2;
		TIMERS->CON &= ~TIM_CON_EXTEN_TIM2;
		TIMERS->CON &= ~TIM_CON_EXTPOL_TIM2;
		TIMERS->CON &= ~TIM_CON_PAUSE_TIM2;
		SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM2_CNT;
	}
	else if (pTim == TIM3)
	{
		TIMERS->CON &= ~TIM_CON_TE_TIM3;
		TIMERS->CON &= ~TIM_CON_TM_TIM3;
		TIMERS->CON &= ~TIM_CON_IE_TIM3;
		TIMERS->CON &= ~TIM_CON_PWM_TIM3;
		TIMERS->CON &= ~TIM_CON_EXTEN_TIM3;
		TIMERS->CON &= ~TIM_CON_EXTPOL_TIM3;
		TIMERS->CON &= ~TIM_CON_PAUSE_TIM3;
		SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM3_CNT;
	}
	else
	{
		TIMERS->CON &= ~TIM_CON_TE_TIM4;
		TIMERS->CON &= ~TIM_CON_TM_TIM4;
		TIMERS->CON &= ~TIM_CON_IE_TIM4;
		TIMERS->CON &= ~TIM_CON_PWM_TIM4;
		TIMERS->CON &= ~TIM_CON_EXTEN_TIM4;
		TIMERS->CON &= ~TIM_CON_EXTPOL_TIM4;
		TIMERS->CON &= ~TIM_CON_PAUSE_TIM4;
		SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM4_CNT;
	}
	if ((TIMERS->CON & TIM_CON_TE) == 0)
	{
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
void TIM_EnableControl(TIM_Type *pTim, int iCtrl)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
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
		case (int)TIM3:
			TIMERS->CON |= TIM_CON_TE_TIM3;
			break;
		case (int)TIM4:
			TIMERS->CON |= TIM_CON_TE_TIM4;
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
void TIM_EnableIRQ(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
	if (pTim == TIM1)
	{
		TIMERS->CON |= TIM_CON_IE_TIM1;
	}
	else if (pTim == TIM2)
	{
		TIMERS->CON |= TIM_CON_IE_TIM2;
	}
	else if (pTim == TIM3)
	{
		TIMERS->CON |= TIM_CON_IE_TIM3;
	}
	else
	{
		TIMERS->CON |= TIM_CON_IE_TIM4;
	}
}

/**
 * @brief Timer interrupt disable
 *
 * @param pTim:TIM1-4
 */
void TIM_DisableIRQ(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
	if (pTim == TIM1)
	{
		TIMERS->CON &= ~TIM_CON_IE_TIM1;
	}
	else if (pTim == TIM2)
	{
		TIMERS->CON &= ~TIM_CON_IE_TIM2;
	}
	else if (pTim == TIM3)
	{
		TIMERS->CON &= ~TIM_CON_IE_TIM3;
	}
	else
	{
		TIMERS->CON &= ~TIM_CON_IE_TIM4;
	}
}

/**
 * @brief Timer stop counter
 *
 * @param pTim :TIM1-4
 * @param ctr :ENABLE , DISABLE
 */
void TIM_PauseCntControl(TIM_Type *pTim, ControlStatus ctl)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
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
	else if (pTim == TIM3)
	{
		if (ctl == ENABLE)
		{
			TIMERS->CON |= TIM_CON_PAUSE_TIM3;
		}
		else
		{
			TIMERS->CON &= ~TIM_CON_PAUSE_TIM3;
		}
	}
	else
	{
		if (ctl == ENABLE)
		{
			TIMERS->CON |= TIM_CON_PAUSE_TIM4;
		}
		else
		{
			TIMERS->CON &= ~TIM_CON_PAUSE_TIM4;
		}
	}
}

/**
 * @brief get timer interrupt flag
 *
 * @param pTim :TIM1-4
 * @return FlagStatus : SET , RESET
 */
FlagStatus TIM_GetIntFlag(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
	if (pTim == TIM1)
	{
		return (TIMERS->INTFLAG & TIM_INTFLAG_TIM1) ? SET : RESET;
	}
	else if (pTim == TIM2)
	{
		return (TIMERS->INTFLAG & TIM_INTFLAG_TIM2) ? SET : RESET;
	}
	else if (pTim == TIM3)
	{
		return (TIMERS->INTFLAG & TIM_INTFLAG_TIM3) ? SET : RESET;
	}
	else if (pTim == TIM4)
	{
		return (TIMERS->INTFLAG & TIM_INTFLAG_TIM4) ? SET : RESET;
	}

	return RESET;
}
/**
 * @brief clear timer interrupt flag
 *
 * @param pTim :TIM1-4
 */
void TIM_ClrIntFlag(TIM_Type *pTim)
{
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
	if (pTim == TIM1)
	{
		TIMERS->INTCLR = TIM_INTCLR_TIM1;
		while (TIMERS->INTFLAG & TIM_INTFLAG_TIM1)
			;
	}
	else if (pTim == TIM2)
	{
		TIMERS->INTCLR = TIM_INTCLR_TIM2;
		while (TIMERS->INTFLAG & TIM_INTFLAG_TIM2)
			;
	}
	else if (pTim == TIM3)
	{
		TIMERS->INTCLR = TIM_INTCLR_TIM3;
		while (TIMERS->INTFLAG & TIM_INTFLAG_TIM3)
			;
	}
	else if (pTim == TIM4)
	{
		TIMERS->INTCLR = TIM_INTCLR_TIM4;
		while (TIMERS->INTFLAG & TIM_INTFLAG_TIM4)
			;
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
	PARAM_CHECK((pTim != TIM1) && (pTim != TIM2) && (pTim != TIM3) && (pTim != TIM4));
	if (pTim == TIM1)
	{
		return TIM1->CTVAL;
	}
	else if (pTim == TIM2)
	{
		return TIM2->CTVAL;
	}
	else if (pTim == TIM3)
	{
		return TIM3->CTVAL;
	}
	else if (pTim == TIM4)
	{
		return TIM4->CTVAL;
	}

	return 0;
}
