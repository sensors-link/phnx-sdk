/**
  ******************************************************************************
  * @file    system_phnx05.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-08-24
  * @brief   Device peripheral access layer system source files.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sysc.h"
#include "anac.h"
#include "iom.h"
#include "uart.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @defgroup FDV32F003_System
  * @{
  */

/** @defgroup FDV32F003_System_Private_Defines
  * @{
  */

#ifndef _BAUD_FREQ
#define _BAUD_FREQ 9600 /*!< Default serial port baud rate. */
#endif
/**
  * @}
  */

/** @addtogroup FDV32F003_System_Private_Variables
  * @{
  */

unsigned int SystemCoreClock = 8000000; /*!< System Clock Frequency (Core Clock) */

extern void trap_entry();
/**
  * @}
  */

/** @defgroup FDV32F003_System_Private_Functions
  * @{
  */

/**
  * @brief  Initialize system clock, bus clock, set exception entry, enable
  *         global interrupt and external interrupt and update SystemCoreClock variable.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
	unsigned int tmpreg;

	/* Check the selection of the source clock */
#if (SYSC_CLK_SRC_SEL == F_LRC)
	/* Turn on ANAC clocks */
	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC;

	/* Enable low-speed crystal oscillator LRC */
	ANAC->WPROT = ANAC_WPROT_V0;
	ANAC->WPROT = ANAC_WPROT_V1;
	ANAC->ANAC_CFG |= ANAC_ANAC_CFG_LRC_EN;

	/* Calculate and configure the system clock source and bus divider value */
	tmpreg = SYSC->CLKCTRCFG;
	tmpreg &= ~(SYSC_CLKCTRCFG_APB_CLK_DIV | SYSC_CLKCTRCFG_AHB_CLK_DIV | SYSC_CLKCTRCFG_SYS_CLK_SEL);
	tmpreg |= ((SYSC_AHB_DIV << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) | (SYSC_APB_DIV << SYSC_CLKCTRCFG_APB_CLK_DIV_pos) |
			   SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC);

	/* The system clock source and bus divider value are written to the register */
	SYSC->WRPROCFG	= SYSC_WRPROCFG_V0;
	SYSC->WRPROCFG	= SYSC_WRPROCFG_V1;
	SYSC->CLKCTRCFG = tmpreg;
#else
	/* Turn on ANAC clocks */
	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC;

	/* Enable main frequency oscillator HRC */
	ANAC->WPROT = ANAC_WPROT_V0;
	ANAC->WPROT = ANAC_WPROT_V1;
	ANAC->ANAC_CFG |= ANAC_ANAC_CFG_HRC_EN;

	/* Calculate and configure the system clock source and bus divider value */
	tmpreg = SYSC->CLKCTRCFG;
	tmpreg &= ~(SYSC_CLKCTRCFG_APB_CLK_DIV | SYSC_CLKCTRCFG_AHB_CLK_DIV | SYSC_CLKCTRCFG_SYS_CLK_SEL);
	tmpreg |= ((SYSC_AHB_DIV << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos) | (SYSC_APB_DIV << SYSC_CLKCTRCFG_APB_CLK_DIV_pos) |
			   SYSC_CLKCTRCFG_SYS_CLK_SEL_HRC);

	/* The system clock source and bus divider value are written to the register */
	SYSC->WRPROCFG	= SYSC_WRPROCFG_V0;
	SYSC->WRPROCFG	= SYSC_WRPROCFG_V1;
	SYSC->CLKCTRCFG = tmpreg;
#endif

	/* Update system clock frequency variable */
	SystemCoreClockUpdate();

	/* Configure the default serial port for debugging */
#ifdef _DEBUG
	IOM_InitTypeDef	 IOM_InitStructure;
	UART_InitTypeDef UART_InitStructure;

	/* Enable the IOM and UART1 module clock */
	SYSC_PeriphClockCmd(SYSC_MOUDLE_CLOCK_IOM | SYSC_MOUDLE_CLOCK_UART, ENABLE);

	/*------------------- UART_RX GP00 -------------------*/
	IOM_InitStructure.IOM_Pin	  = GPIO_PIN0;
	IOM_InitStructure.IOM_OutCmd  = DISABLE;
	IOM_InitStructure.IOM_PuCmd	  = DISABLE;
	IOM_InitStructure.IOM_PdCmd	  = DISABLE;
	IOM_InitStructure.IOM_OutType = IOM_OTYPE_COMS;
	IOM_InitStructure.IOM_ADState = IOM_ADS_DIGITAL;
	IOM_InitStructure.IOM_DRState = IOM_DRS_HIGH;
	IOM_InitStructure.IOM_AltFunc = IOM_ALT_FUNC_P00_SEL_UART1_RX;
	IOM_Init(&IOM_InitStructure);

	/*------------------- UART_TX GP01 -------------------*/
	IOM_InitStructure.IOM_Pin	  = GPIO_PIN1;
	IOM_InitStructure.IOM_OutCmd  = DISABLE;
	IOM_InitStructure.IOM_PuCmd	  = DISABLE;
	IOM_InitStructure.IOM_PdCmd	  = DISABLE;
	IOM_InitStructure.IOM_OutType = IOM_OTYPE_COMS;
	IOM_InitStructure.IOM_ADState = IOM_ADS_DIGITAL;
	IOM_InitStructure.IOM_DRState = IOM_DRS_HIGH;
	IOM_InitStructure.IOM_AltFunc = IOM_ALT_FUNC_P01_SEL_UART1_TX;
	IOM_Init(&IOM_InitStructure);

	/*------------------- UART1 setting -------------------*/
	UART_DeInit();
	UART_InitStructure.UART_Parity = UART_PARITY_NO;
	UART_InitStructure.UART_StopBits = UART_STOPBITS_1;
	UART_InitStructure.UART_BaudRate = _BAUD_FREQ;
	UART_Init(&UART_InitStructure);
#endif

	/* Configure exception entry address */
	WRITE_CSR(mtvec, &trap_entry);

	/* Enable global interrupt */
	EnableGlobleIRQ();

	/* Enable external interrupt */
	EnableExtIRQ();
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
	unsigned int clksrc;

	/* Get system clock source */
	clksrc = SYSC->CLKCTRCFG & SYSC_CLKCTRCFG_SYS_CLK_SEL;

	/* Check the system clock source */
	if (clksrc == SYSC_CLKCTRCFG_SYS_CLK_SEL_LRC)
	{
		/* LRC as source clock */
		SystemCoreClock = 8000;
	}
	else
	{
		/* The clock of HRC is 8MHz */
		SystemCoreClock = 8000000;
	}
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

