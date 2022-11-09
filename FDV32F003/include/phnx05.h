/**
  ******************************************************************************
  * @file    phnx05.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-08-23
  * @brief   Device Peripheral Access Layer Header File.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PHNX05_H__
#define __PHNX05_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "risc_v_csr.h"
#include "system_phnx05.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @addtogroup PHX05_Header
  * @{
  */

/**
  * @brief IO definitions
  *
  * define access restrictions to peripheral registers
  */

#ifdef __cplusplus
#define __I volatile /*!< Defines 'read only' permissions */
#else
#define __I volatile const /*!< Defines 'read only' permissions */
#endif
#define __O	 volatile /*!< Defines 'write only' permissions */
#define __IO volatile /*!< Defines 'read / write' permissions */

/**
  * @brief interrupt number definitions
  */
typedef enum IRQn
{
	RSV_IRQn	= 0,  /*!< Reserved Interrupt */
	ADC_IRQn	= 1,  /*!< ADC Interrupt */
	LPT_IRQn	= 2,  /*!< LPT Interrupt */
	TIMER0_IRQn = 3,  /*!< TIMER0 Interrupt */
	TIMER1_IRQn = 4,  /*!< TIMER1 Interrupt */
	TIMER2_IRQn = 5,  /*!< TIMER2 Interrupt */
	TIMER3_IRQn = 6,  /*!< TIMER3 Interrupt */
	TIMER4_IRQn = 7,  /*!< TIMER4 Interrupt */
	UART1_IRQn	= 8,  /*!< UART1 Interrupt */
	ANAC_IRQn	= 9,  /*!< ANAC Interrupt */
	EFC_IRQn	= 10, /*!< EFC Interrupt */
	IOM_IRQn	= 11, /*!< IOM Interrupt */
} IRQn_Type;

/** @defgroup PHX05_Peripheral_registers_structures
  * @{
  */

/**
  * @brief SYSC Registers
  */

typedef struct
{
	__IO unsigned int CLKCTRCFG;   /*!< Offset: 0x00  SYSC system clock control register */
	__O unsigned int  WRPROCFG;	   /*!< Offset: 0x04  SYSC system protection register */
	__IO unsigned int CLKENCFG;	   /*!< Offset: 0x08  SYSC Module Clock Gating Register */
	__O unsigned int  MSFTRSTCFG;  /*!< Offset: 0x0C  SYSC module soft reset register */
	__IO unsigned int TESTCKREV;   /*!< Offset: 0x10  SYSC Test Function Reserved Register */
	__IO unsigned int ADCCLKDIV;   /*!< Offset: 0x14  SYSC ADC Clock Divider Register */
	__IO unsigned int RSTSTS;      /*!< Offset: 0x18  SYSC reset status register */
} SYSC_TypeDef;

/**
  * @brief EFC Registers
  */

typedef struct
{
	__IO unsigned int CR;	 /*!< Offset: 0x00  EFC Control Register */
	__IO unsigned int TNVS;	 /*!< Offset: 0x04  EFC Tnvs register */
	__IO unsigned int TPROG; /*!< Offset: 0x08  EFC Tprog register */
	__IO unsigned int TPGS;	 /*!< Offset: 0x0C  EFC Tpgs register */
	__IO unsigned int TRCV;	 /*!< Offset: 0x10  EFC Trcv register */
	__IO unsigned int TERS;	 /*!< Offset: 0x14  EFC Terase Register */
	__O unsigned int  WPT;	 /*!< Offset: 0x18  EFC Write Protect Register */
	__IO unsigned int OPR;	 /*!< Offset: 0x1C  EFC opcode register */
	__I unsigned int  RSV;	 /*!< Offset: 0x20  EFC reserved register */
	__IO unsigned int STS;	 /*!< Offset: 0x24  EFC Status Register */
} EFC_TypeDef;

/**
  * @brief UART Registers
  */

typedef struct
{
	__IO unsigned int SCON;	 /*!< Offset: 0x00  UART Control Register */
	__IO unsigned int SBUF;	 /*!< Offset: 0x04  UART data register */
	__IO unsigned int SADDR; /*!< Offset: 0x08  UART address register */
	__IO unsigned int SADEN; /*!< Offset: 0x0C  UART address mask register */
	__IO unsigned int ISR;	 /*!< Offset: 0x10  UART Interrupt Flag Register */
	__IO unsigned int BDIV;	 /*!< Offset: 0x14  UART Baud Rate Configuration Register */
} UART_TypeDef;

/**
  * @brief TIMER Registers
  */

typedef struct
{
	__IO unsigned int TCR;   /*!< Offset: 0x00  TIMER Control Register */
	__IO unsigned int TN;    /*!< Offset: 0x04  TIMER count value register */
	__IO unsigned int PWMPD; /*!< Offset: 0x08  TIMER PWM cycle register */
	__IO unsigned int PWMDC; /*!< Offset: 0x0C  TIMER PWM duty cycle register */
} TIM_TypeDef;

typedef struct
{
	__IO unsigned int T0CR;	      /*!< Offset: 0x00  TIMER TIMER0 Control Register */
	__IO unsigned int T0;         /*!< Offset: 0x04  TIMER TIMER0 count value register */
	__IO unsigned int TIE;        /*!< Offset: 0x08  TIMER Interrupt control register */
	__IO unsigned int TIF;        /*!< Offset: 0x0C  TIMER Interrupt flag control register */
	__I unsigned int  RSV[0x10];  /*!< Offset: 0x10  TIMER reserved register */
	__IO unsigned int T0RLD;      /*!< Offset: 0x50  TIMER TIMER0 Overloaded value register */
} TIMERS_TypeDef;

/**
  * @brief LPT Registers
  */

typedef struct
{
	__IO unsigned int CR;	  /*!< Offset: 0x00  LPT Control Register */
	__IO unsigned int CFG;	  /*!< Offset: 0x04  LPT Configuration Register */
	__I unsigned int  CNT;	  /*!< Offset: 0x08  LPT count value register */
	__IO unsigned int INTSTS; /*!< Offset: 0x0C  LPT Interrupt Flag Register */
} LPTIM_TypeDef;

/**
  * @brief WDT Registers
  */

typedef struct
{
	__O unsigned int  RST; /*!< Offset: 0x00  WDT clear control register */
	__IO unsigned int CR;  /*!< Offset: 0x04  WDT Control Register */
} WDT_TypeDef;

/**
  * @brief IOM Registers
  */

typedef struct
{
	__IO unsigned int DATA;			/*!< Offset: 0x00  IO data register */
	__IO unsigned int OE;			/*!< Offset: 0x04  IO output enable register */
	__IO unsigned int PU;			/*!< Offset: 0x08  IO pull-up register */
	__IO unsigned int PD;			/*!< Offset: 0x0C  IO pull-down register */
	__IO unsigned int OTYPE;		/*!< Offset: 0x10  IO output type register */
	__IO unsigned int ADS;			/*!< Offset: 0x14  IO digital-analog configuration register */
	__IO unsigned int DRS;			/*!< Offset: 0x18  IO drive capability register */
	__IO unsigned int AF0;			/*!< Offset: 0x1C  IO Alternate Function Register 0 */
	__IO unsigned int AF1;			/*!< Offset: 0x20  IO Alternate Function Register 1 */
	__IO unsigned int INT_TYPE;		/*!< Offset: 0x24  IO interrupt type register */
	__IO unsigned int INT_POLARITY; /*!< Offset: 0x28  IO Interrupt Polarity Register */
	__IO unsigned int EXT_INTE;		/*!< Offset: 0x2C  IO external interrupt enable register */
	__IO unsigned int INTF;			/*!< Offset: 0x30  IO interrupt status flag register */
	__IO unsigned int CTL;			/*!< Offset: 0x34  IO control register */
	__O unsigned int WPROT;			/*!< Offset: 0x38  IO Write protected register */
} IOM_TypeDef;

/**
  * @brief ADCRegisters
  */

typedef struct
{
	__IO unsigned int CFG;	 /*!< Offset: 0x00  ADC Configuration register */
	__IO unsigned int INTF;	 /*!< Offset: 0x04  ADC Interrupt status register */
	__IO unsigned int DATA;	 /*!< Offset: 0x08  ADC conversion results are saved in registers */
} ADC_TypeDef;

/**
  * @brief ANAC Registers
  */

typedef struct
{
	__IO unsigned int ANAC_CFG;	  		/*!< Offset: 0x00  ANAC Analog Control Configuration Register */
	__IO unsigned int CMP_CFG;	  		/*!< Offset: 0x04  ANAC Comparator Configuration Register */
	__IO unsigned int LVD_CFG;	  		/*!< Offset: 0x08  ANAC LVD Configuration Register */
	__IO unsigned int AINSEL;	  		/*!< Offset: 0x0C  ANAC Analog IO alternate function selection register */
	__IO unsigned int CLK_TRIM;	  		/*!< Offset: 0x10  ANAC Clock tuner register */
	__IO unsigned int ANAC_FLAG;  		/*!< Offset: 0x14  ANAC Interrupt Status Register */
	__O unsigned int  WPROT;	  		/*!< Offset: 0x18  ANAC write-protect register */
	__I unsigned int  RSV0[9];		  	/*!< Offset: 0x1C  ANAC reserved register 0 */
	__IO unsigned int HRC_TRIM;		    /*!< Offset: 0x40  ANAC internal high speed clock calibration value */
	__IO unsigned int LRC_TRIM;	  		/*!< Offset: 0x44  ANAC Internal low-speed clock calibration value */
	__IO unsigned int BG4S_TRIM;  		/*!< Offset: 0x48  ANAC SLDO reference voltage calibration value */
	__IO unsigned int CMP_TRIM;	  		/*!< Offset: 0x4C  ANAC Comparator calibration value */
	__IO unsigned int HRC_IBTRIM;       /*!< Offset: 0x50  ANAC HRC current bias calibration value */
	__IO unsigned int NVR_OPTION0;  	/*!< Offset: 0x54  ANAC Simulate the TRIM configuration register */
	__I unsigned int  RSV1;		  		/*!< Offset: 0x58  ANAC reserved register 1 */
	__IO unsigned int TESTCTL;	  		/*!< Offset: 0x5C  ANAC Analog Test Multiplexed   Function Register */
	__IO unsigned int TEST;		  		/*!< Offset: 0x60  ANAC Analog Test Configuration Register */
	__I unsigned int  RSV2[7];		    /*!< Offset: 0x64  ANAC reserved register 2 */
	__IO unsigned int NVR_OPTION1;  	/*!< Offset: 0x80  ANAC BOOT NVR Storage register */
	__I unsigned int  RSV3;		  		/*!< Offset: 0x84  ANAC reserved register 3 */
	__IO unsigned int EST_CFG;		  	/*!< Offset: 0x88  ANAC EST mode configuration register */
	__IO unsigned int EST_RAM_BIST;		/*!< Offset: 0x8C  EST mode RAMBIST result register */
} ANAC_TypeDef;

/**
  * @}
  */

/** @addtogroup PHX05_Exported_types
  * @{
  */

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef signed int	 s32;
typedef signed short s16;
typedef signed char	 s8;

typedef enum { DISABLE = 0, ENABLE = !DISABLE } FunctionalState, ControlStatus;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum { FALSE = 0, TRUE = !FALSE } BOOL;
typedef enum { RESET = 0, SET = !RESET } FlagStatus, ITStatus;
typedef enum { ERROR = 0, SUCCESS = !ERROR } ErrStatus;

/* bit operations */
#define REG32(addr)					 (*((volatile unsigned int *)(addr)))
#define REG16(addr)					 (*((volatile unsigned short *)(addr)))
#define REG8(addr)					 (*((volatile unsigned char *)(addr)))
#define BIT(x)						 ((unsigned int)0x01U << (x))
#define BITS(start, end)			 ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (end))))
#define GET_BITS(regval, start, end) (((regval)&BITS((start), (end))) >> (start))

/**
  * @}
  */

/** @addtogroup PHX05_Peripheral_memory_map
  * @{
  */

#define FLASH_BASE		 ((unsigned int)0x00002000UL) /*!< FLASH base address in the alias region */
#define EEPROM_BASE		 ((unsigned int)0x00007000UL) /*!< EEPROM base address in the alias region */
#define SRAM_BASE		 ((unsigned int)0x0000B000UL) /*!< SRAM base address in the alias region */

#define EFC_BASE	((unsigned int)0x0000C000UL)
#define SYSC_BASE	((unsigned int)0x0000C400UL)
#define IOM_BASE	((unsigned int)0x0000C800UL)
#define ANAC_BASE	((unsigned int)0x0000CC00UL)
#define TIMERS_BASE ((unsigned int)0x0000D000UL)
#define TIM1_BASE	((unsigned int)0x0000D010UL)
#define TIM2_BASE	((unsigned int)0x0000D020UL)
#define TIM3_BASE	((unsigned int)0x0000D030UL)
#define TIM4_BASE	((unsigned int)0x0000D040UL)
#define UART1_BASE	((unsigned int)0x0000D400UL)
#define ADC_BASE	((unsigned int)0x0000D800UL)
#define LPTIM_BASE	((unsigned int)0x0000F800UL)
#define WDT_BASE	((unsigned int)0x0000FC00UL)

/**
  * @}
  */

/** @addtogroup PHX05_Peripheral_declaration
  * @{
  */

#define EFC	   ((EFC_TypeDef *)EFC_BASE)
#define SYSC   ((SYSC_TypeDef *)SYSC_BASE)
#define IOM	   ((IOM_TypeDef *)IOM_BASE)
#define ANAC   ((ANAC_TypeDef *)ANAC_BASE)
#define TIMERS ((TIMERS_TypeDef *)TIMERS_BASE)
#define TIM1   ((TIM_TypeDef *)TIM1_BASE)
#define TIM2   ((TIM_TypeDef *)TIM2_BASE)
#define TIM3   ((TIM_TypeDef *)TIM3_BASE)
#define TIM4   ((TIM_TypeDef *)TIM4_BASE)
#define UART1  ((UART_TypeDef *)UART1_BASE)
#define ADC	   ((ADC_TypeDef *)ADC_BASE)
#define LPTIM  ((LPTIM_TypeDef *)LPTIM_BASE)
#define WDT	   ((WDT_TypeDef *)WDT_BASE)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
#ifdef _FW_DEBUG
extern int __wrap_printf(const char *fmt, ...);
#define PARAM_CHECK(x)                                                                                                 \
	{                                                                                                                  \
		if (!(x))                                                                                                      \
		{                                                                                                              \
			__wrap_printf("Wrong parameters value: file:%s,on line:%d\r\n", __FILE__, __LINE__);                       \
			while (1)                                                                                                  \
				;                                                                                                      \
		}                                                                                                              \
	}
#else
#define PARAM_CHECK(x)
#endif /* _FW_DEBUG */

#ifdef __cplusplus
}
#endif

#endif /* __PHNX05_H__ */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

