/**
  ******************************************************************************
  * @file    phnx04.h
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
#ifndef __PHNX04_H__
#define __PHNX04_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "risc_v_csr.h"
#include "system_phnx04.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @addtogroup PHX04_Header
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
	PMU_IRQn	= 1,  /*!< PMU Interrupt */
	LPT_IRQn	= 2,  /*!< LPT Interrupt */
	TIMER1_IRQn = 3,  /*!< TIMER1 Interrupt */
	TIMER2_IRQn = 4,  /*!< TIMER2 Interrupt */
	UART1_IRQn	= 7,  /*!< UART1 Interrupt */
	UART2_IRQn	= 8,  /*!< UART2 Interrupt */
	SPI_IRQn	= 9,  /*!< SPI Interrupt */
	ANAC_IRQn	= 10, /*!< ANAC Interrupt */
	EFC_IRQn	= 11, /*!< EFC Interrupt */
	IOM_IRQn	= 12, /*!< IOM Interrupt */
	TWC_IRQn	= 15, /*!< TWC Interrupt */
} IRQn_Type;

/** @defgroup PHX04_Peripheral_registers_structures
  * @{
  */

/**
  * @brief PMU Registers
  */

typedef struct
{
	__IO unsigned int CR;	   /*!< Offset: 0x00  PMU Control Register */
	__IO unsigned int WKCFG;   /*!< Offset: 0x04  PMU wake-up configuration register */
	__O unsigned int  SOFTRST; /*!< Offset: 0x08  PMU soft reset register */
	__IO unsigned int WKSTS;   /*!< Offset: 0x0C  PMU wake-up status register */
	__IO unsigned int RSTSTS;  /*!< Offset: 0x10  PMU reset status register */
	__IO unsigned int INTEN;   /*!< Offset: 0x14  PMU Interrupt Enable Register */
	__O unsigned int  WPT;	   /*!< Offset: 0x18  PMU write protection register */
	__I unsigned int  RSV;	   /*!< Offset: 0x1C  PMU reserved register */
	__IO unsigned int BAKR;	   /*!< Offset: 0x20  PMU Backup Register */
} PMU_TypeDef;

/**
  * @brief SYSC Registers
  */

typedef struct
{
	__IO unsigned int CLKCTRCFG;   /*!< Offset: 0x00  SYSC system clock control register */
	__O unsigned int  WRPROCFG;	   /*!< Offset: 0x04  SYSC system protection register */
	__IO unsigned int CLKENCFG;	   /*!< Offset: 0x08  SYSC Module Clock Gating Register */
	__O unsigned int  MSFTRSTCFG;  /*!< Offset: 0x0C  SYSC module soft reset register */
	__I unsigned int  RSV;		   /*!< Offset: 0x10  SYSC reserved register */
	__IO unsigned int TESTCKREV;   /*!< Offset: 0x14  SYSC Test Function Reserved Register */
	__IO unsigned int ANCLKDIV;	   /*!< Offset: 0x18  SYSC ANAC Clock Divider Register */
	__IO unsigned int TIMCLKDIV;   /*!< Offset: 0x1C  SYSC timer clock divider register */
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
  * @brief SPI Registers
  */

typedef struct
{
	__IO unsigned int CR0; /*!< Offset: 0x00  SPI Control Register */
	__IO unsigned int CSN; /*!< Offset: 0x04  SPI Chip Select Control Register */
	__I unsigned int  SR;  /*!< Offset: 0x08  SPI Status Register */
	__IO unsigned int DR;  /*!< Offset: 0x0C  SPI data register */
} SPI_TypeDef;

/**
  * @brief TWC Registers
  */

typedef struct
{
	__IO unsigned int CR;	 /*!< Offset: 0x00  TWC Control Register */
	__IO unsigned int SWCR;	 /*!< Offset: 0x04  TWC SWAN_BUS Control Register */
	__IO unsigned int SWBR;	 /*!< Offset: 0x08  TWC SWAN_BUS Baud Rate Register */
	__IO unsigned int GAPW;	 /*!< Offset: 0x0C  TWC GAP Width Register */
	__IO unsigned int CMD1;	 /*!< Offset: 0x10  TWC hardware decode instruction 1 register */
	__IO unsigned int CMD2;	 /*!< Offset: 0x14  TWC hardware decode instruction 2 register */
	__IO unsigned int CMD3;	 /*!< Offset: 0x18  TWC hardware decode instruction 3 register */
	__IO unsigned int CMD4;	 /*!< Offset: 0x1C  TWC hardware decode instruction 4 register */
	__IO unsigned int CMD5;	 /*!< Offset: 0x20  TWC hardware decode instruction 5 register */
	__IO unsigned int CMD6;	 /*!< Offset: 0x24  TWC hardware decode instruction 6 register */
	__I unsigned int  RXD;	 /*!< Offset: 0x28  TWC receive data register */
	__IO unsigned int TXD;	 /*!< Offset: 0x2C  TWC transmit data register */
	__IO unsigned int TXS;	 /*!< Offset: 0x30  TWC software transmit start register */
	__IO unsigned int INTEN; /*!< Offset: 0x34  TWC Interrupt Enable Register */
	__IO unsigned int STS;	 /*!< Offset: 0x38  TWC Status Register */
	__I unsigned int  DBG;	 /*!< Offset: 0x3C  TWC debug register */
} TWC_TypeDef;

/**
  * @brief TIMER Registers
  */

typedef struct
{
	__IO unsigned int CTCG1; /*!< Offset: 0x00  TIMER count value 1 register */
	__IO unsigned int CTCG2; /*!< Offset: 0x04  TIMER count value 2 register */
	__I unsigned int  CTVAL; /*!< Offset: 0x08  TIMER current counter value register */
	__IO unsigned int PWCON; /*!< Offset: 0x0C  TIMER PWM Control Register */
} TIM_TypeDef;

typedef struct
{
	__IO unsigned int CON;	   /*!< Offset: 0x00  TIMER Control Register */
	__I unsigned int  INTFLAG; /*!< Offset: 0x04  TIMER interrupt flag register */
	__O unsigned int  INTCLR;  /*!< Offset: 0x08  TIMER Interrupt Clear Register */
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
} IOM_TypeDef;

/**
  * @brief ANAC Registers
  */

typedef struct
{
	__IO unsigned int ANAC_CFG;	  		/*!< Offset: 0x00  ANAC Analog Control Configuration Register */
	__IO unsigned int LED_CFG;	  		/*!< Offset: 0x04  ANAC Led Configuration Register */
	__IO unsigned int PDSENS_CFG; 		/*!< Offset: 0x08  ANAC pdsonser configuration register */
	__IO unsigned int CMP_CFG;	  		/*!< Offset: 0x0C  ANAC Comparator Configuration Register */
	__IO unsigned int ADC_CFG;	  		/*!< Offset: 0x10  ANAC ADC Configuration Register */
	__IO unsigned int ADC_CTL;	  		/*!< Offset: 0x14  ANAC ADC Control Register */
	__IO unsigned int LVD_CFG;	  		/*!< Offset: 0x18  ANAC LVD Configuration Register */
	__IO unsigned int CLK_CFG;	  		/*!< Offset: 0x1C  ANAC Clock Control Configuration Register */
	__IO unsigned int AINSEL;	  		/*!< Offset: 0x20  ANAC Analog IO alternate function selection register */
	__IO unsigned int DLY_CFG;	  		/*!< Offset: 0x24  ANAC Delay Configuration Register */
	__IO unsigned int ME_CTL;	  		/*!< Offset: 0x28  ANAC Measurement Control Register */
	__IO unsigned int ANAC_FLAG;  		/*!< Offset: 0x2C  ANAC Interrupt Status Register */
	__IO unsigned int THR1_DATA;  		/*!< Offset: 0x30  ANAC Threshold register 1 */
	__IO unsigned int THR2_DATA;  		/*!< Offset: 0x34  ANAC Threshold register 2 */
	__I unsigned int  RSV0;		  		/*!< Offset: 0x38  ANAC reserved register 0 */
	__O unsigned int  WPROT;	  		/*!< Offset: 0x3C  ANAC write-protect register */
	__IO unsigned int ADC_VAL[8]; 		/*!< Offset: 0x40  ANAC ADC conversion result storage registers */
	__IO unsigned int AVG_VAL;	  		/*!< Offset: 0x60  ANAC ADC conversion result average value storage register */
	__I unsigned int  RSV1[7];	  		/*!< Offset: 0x64  ANAC reserved registers 1 */
	__IO unsigned int HRC_TRIM_1M;		/*!< Offset: 0x80  ANAC internal high speed clock 1MHz calibration value */
	__IO unsigned int HRC_TRIM_2M;		/*!< Offset: 0x84  ANAC internal high speed clock 2MHz calibration value */
	__IO unsigned int HRC_TRIM_4M;		/*!< Offset: 0x88  ANAC internal high speed clock 4MHz calibration value */
	__IO unsigned int HRC_TRIM_8M;		/*!< Offset: 0x8C  ANAC internal high speed clock 8MHz calibration value */
	__IO unsigned int HRC_TRIM_16M;		/*!< Offset: 0x90  ANAC internal high speed clock 16MHz calibration value */
	__IO unsigned int LRC_TRIM;	  		/*!< Offset: 0x94  ANAC Internal low-speed clock calibration value */
	__IO unsigned int MRC_TRIM;	  		/*!< Offset: 0x98  ANAC MRC Calibration Configuration Register */
	__IO unsigned int CMP_TRIM;	  		/*!< Offset: 0x9C  ANAC Comparator calibration value */
	__IO unsigned int BG4A_TRIM;  		/*!< Offset: 0xA0  ANAC ALDO4A reference voltage calibration value */
	__IO unsigned int BG4S_TRIM;  		/*!< Offset: 0xA4  ANAC SLDO reference voltage calibration value */
	__IO unsigned int BG4A_OPTRIM;  	/*!< Offset: 0xA8  ANAC BG4A magnification calibration register */
	__IO unsigned int VOLTREF_OPTRIM;	/*!< Offset: 0xAC  ANAC VOLTREF magnification calibration register */
	__IO unsigned int NVR_OPTION0;  	/*!< Offset: 0xB0  ANAC Simulate the TRIM configuration register */
	__IO unsigned int RSV2;  			/*!< Offset: 0xB4  ANAC reserved registers 2 */
	__IO unsigned int NVR_OPTION1;  	/*!< Offset: 0xB8  ANAC BOOT NVR Storage register */
	__IO unsigned int NVR_OPTION2;  	/*!< Offset: 0xBC  ANAC FLASHSIZE Specifies the NVR storage register */
	__IO unsigned int TESTCTL;	  		/*!< Offset: 0xC0  ANAC Analog Test Multiplexed   Function Register */
	__IO unsigned int TEST;		  		/*!< Offset: 0xC4  ANAC Analog Test Configuration Register */
	__IO unsigned int EST_CFG;		  	/*!< Offset: 0xC8  ANAC EST mode configuration register */
	__IO unsigned int EST_RAM_BIST;		/*!< Offset: 0xCC  ANAC EST mode RAMBIST result register */
} ANAC_TypeDef;

/**
  * @}
  */

/** @addtogroup PHX04_Exported_types
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

/** @addtogroup PHX04_Peripheral_memory_map
  * @{
  */

#define FLASH_BASE		 ((unsigned int)0x10100000UL) /*!< FLASH base address in the alias region */
#define EEPROM_BASE		 ((unsigned int)0x10180000UL) /*!< EEPROM base address in the alias region */
#define SRAM_BASE		 ((unsigned int)0x20000000UL) /*!< SRAM base address in the alias region */

#define EFC_BASE	((unsigned int)0x40000000UL)
#define SYSC_BASE	((unsigned int)0x40001000UL)
#define TIMERS_BASE ((unsigned int)0x400100A0UL)
#define TIM1_BASE	((unsigned int)0x40010000UL)
#define TIM2_BASE	((unsigned int)0x40010014UL)
#define SPI_BASE	((unsigned int)0x40010800UL)
#define UART2_BASE	((unsigned int)0x40010c00UL)
#define UART1_BASE	((unsigned int)0x40011000UL)
#define TWC_BASE	((unsigned int)0x40011800UL)
#define ANAC_BASE	((unsigned int)0x40011c00UL)
#define IOM_BASE	((unsigned int)0x40012400UL)
#define PMU_BASE	((unsigned int)0x40012c00UL)
#define LPTIM_BASE	((unsigned int)0x40013000UL)
#define WDT_BASE	((unsigned int)0x40013400UL)

/**
  * @}
  */

/** @addtogroup PHX04_Peripheral_declaration
  * @{
  */

#define EFC	   ((EFC_TypeDef *)EFC_BASE)
#define SYSC   ((SYSC_TypeDef *)SYSC_BASE)
#define TIMERS ((TIMERS_TypeDef *)TIMERS_BASE)
#define TIM1   ((TIM_TypeDef *)TIM1_BASE)
#define TIM2   ((TIM_TypeDef *)TIM2_BASE)
#define SPI	   ((SPI_TypeDef *)SPI_BASE)
#define UART1  ((UART_TypeDef *)UART1_BASE)
#define UART2  ((UART_TypeDef *)UART2_BASE)
#define TWC	   ((TWC_TypeDef *)TWC_BASE)
#define ANAC   ((ANAC_TypeDef *)ANAC_BASE)
#define IOM	   ((IOM_TypeDef *)IOM_BASE)
#define PMU	   ((PMU_TypeDef *)PMU_BASE)
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

#endif /* __PHNX04_H__ */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

