/**
  ******************************************************************************
  * @file    init.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-08-24
  * @brief   This file provides the processing entry for all exception
  *			 handling and peripheral interrupts.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "phnx05.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @defgroup FDV32F003_INIT
  * @{
  */

/**
  * @brief Weak declaration of exception and interrupt handlers
  */

__attribute__((weak)) void MSOFT_IntHandler(void){};
__attribute__((weak)) void MTIM_IntHandler(void){};
__attribute__((weak)) void MEXP_Handler(void){};
__attribute__((weak)) void NMI_Handler(void){};
__attribute__((weak)) void ADC_IrqHandler(void){};
__attribute__((weak)) void LPT_IrqHandler(void){};
__attribute__((weak)) void TIMER0_IrqHandler(void){};
__attribute__((weak)) void TIMER1_IrqHandler(void){};
__attribute__((weak)) void TIMER2_IrqHandler(void){};
__attribute__((weak)) void TIMER3_IrqHandler(void){};
__attribute__((weak)) void TIMER4_IrqHandler(void){};
__attribute__((weak)) void UART1_IrqHandler(void){};
__attribute__((weak)) void ANAC_IrqHandler(void){};
__attribute__((weak)) void EFC_IrqHandler(void){};
__attribute__((weak)) void IOM_IrqHandler(void){};

/** @defgroup FDV32F003_INIT_Private_Functions
  * @{
  */

/**
  * @brief  Handling machine external interrupts.
  * @param  None
  * @retval None
  */
static void MEXT_IntHandler(void)
{
	u32 src;
	/* Get the interrupt source of the interrupt */
	src = PLIC_GetCLAIM();

	/* Handle the corresponding interrupt */
	switch (src)
	{
	case (ADC_IRQn): {
		ADC_IrqHandler();
		break;
	}
	case (LPT_IRQn): {
		LPT_IrqHandler();
		break;
	}
	case (TIMER0_IRQn): {
		TIMER0_IrqHandler();
		break;
	}
	case (TIMER1_IRQn): {
		TIMER1_IrqHandler();
		break;
	}
	case (TIMER2_IRQn): {
		TIMER2_IrqHandler();
		break;
	}
	case (TIMER3_IRQn): {
		TIMER3_IrqHandler();
		break;
	}
	case (TIMER4_IRQn): {
		TIMER4_IrqHandler();
		break;
	}
	case (UART1_IRQn): {
		UART1_IrqHandler();
		break;
	}
	case (ANAC_IRQn): {
		ANAC_IrqHandler();
		break;
	}
	case (EFC_IRQn): {
		EFC_IrqHandler();
		break;
	}
	case (IOM_IRQn): {
		IOM_IrqHandler();
		break;
	}
	default:
		break;
	}
	/* Clear interrupt source */
	PLIC_SetCLAIM(src);
}

/**
  * @brief  Handling Machine Exception Traps.
  * @param  mcause: The cause of machine abnormality.
  * @param  epc: The PC value of the instruction the processor was executing
  *         before the exception was entered.
  * @retval None
  */
unsigned int handle_trap(unsigned int mcause, unsigned int epc)
{
	/* External Machine-Level interrupt from PLIC */
	if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == EXP_M_EXT_INT))
	{
		/* Machine external interrupt */
		MEXT_IntHandler();
	}
	else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == EXP_M_SOFT_INT))
	{
		/* Machine software interrupt */
		MSOFT_IntHandler();
	}
	else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == EXP_M_TIM_INT))
	{
		/* Machine timer interrupt */
		MTIM_IntHandler();
	}
	else if (mcause == EXP_NMI)
	{
		/* Nmi exception (WDT interrupt) */
		NMI_Handler();
	}
	else
	{
		/* Unknown exception */
		MEXP_Handler();
		while (1)
		{
		};
	}

	/* Returns the return address of the exception */
	return epc;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

