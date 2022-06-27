/**
 * @file phnx04.h
 * @author yongda.wang
 * @brief
 * @version 0.1
 * @date 2021-06-15
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#ifndef __PHNX04_H__
#define __PHNX04_H__

#include "risc_v_csr.h"
#include "system_phnx04.h"

#ifdef cplusplus
extern "C"
{
#endif
/* IO definitions (access restrictions to peripheral registers) */
/**
  <strong>IO Type Qualifiers</strong> are used
  \li to specify the access to peripheral variables.
  \li for automatic generation of peripheral register debug information.
 */
#ifdef __cplusplus
#define __I volatile /*!< Defines 'read only' permissions               */
#else
#define __I volatile const /*!< Defines 'read only' permissions                 */
#endif
#define __O	 volatile /*!< Defines 'write only' permissions             */
#define __IO volatile /*!< Defines 'read / write' permissions           */

	/* define interrupt number */
	typedef enum IRQn
	{
		/* ---------------------  Phonix04 Specific Interrupt Numbers
			   ------------*/
		RSV_IRQn	= 0,  /*!< Reserved Interrupt					*/
		PMU_IRQn	= 1,  /*!< PMU Interrupt						*/
		LPT_IRQn	= 2,  /*!< LPT Interrupt						*/
		TIMER1_IRQn = 3,  /*!< TIMER1 Interrupt					*/
		TIMER2_IRQn = 4,  /*!< TIMER2 Interrupt					*/
		UART1_IRQn	= 7,  /*!< UART1 Interrupt					*/
		UART2_IRQn	= 8,  /*!< UART2 Interrupt					*/
		SPI_IRQn	= 9,  /*!< SPI Interrupt						*/
		ANAC_IRQn	= 10, /*!< ANAC Interrupt						*/
		EFC_IRQn	= 11, /*!< EFC Interrupt						*/
		IOM_IRQn	= 12, /*!< IOM Interrupt						*/
		TWC_IRQn	= 15, /*!< TWC Interrupt						*/
	} IRQn_Type;

	typedef struct
	{
		__IO unsigned int CR;
		__IO unsigned int WKCFG;
		__O unsigned int  SOFTRST;
		__IO unsigned int WKSTS;
		__IO unsigned int RSTSTS;
		__IO unsigned int INTEN;
		__O unsigned int  WPT;
		__I unsigned int  RSV;
		__IO unsigned int BAKR;

	} PMU_Type;

	/* ================================================================================
	 */
	/* ================                      SYSC ================ */
	/* ================================================================================
	 */

	/**
	 * @brief System Control (SYSC)
	 */

	typedef struct /*!< SYSC Structure             */
	{
		__IO unsigned int CLKCTRCFG; /*!< CLKCTRCFG */
		__O unsigned int  WRPROCFG;	 /*!< WRPROCFG   */
		__IO unsigned int CLKENCFG;
		__O unsigned int  MSFTRSTCFG;
		__IO unsigned int RSV;
		__IO unsigned int TESTCKSEL;
		__IO unsigned int ANCLKDIV;
		__IO unsigned int TIMCLKDIV;
	} SYSC_Type;

	/* ================================================================================*/
	/* ================                       EFC ================ */
	/* ================================================================================*/

	/**
	 * @brief Embeded Flash Control (EFC)
	 */

	typedef struct /*!< EFC Structure          */
	{
		__IO unsigned int CR;	  /*!< Control Register */
		__IO unsigned int TNVS;	  /*!< ROG/ERASE/CEb/NVR/ADDRESS to Web Setup time */
		__IO unsigned int TPROG;  /*!< PROG/ERASE/CEb/NVR/ADDRESS to Web Setup time */
		__IO unsigned int TPGS;	  /*!< WEb low to PROG2 high Setup time */
		__IO unsigned int TRCV;	  /*!< Program Recovery Time */
		__IO unsigned int TERASE; /*!< Erase time */
		__O unsigned int  WPT;	  /*!< Write Protect Register     */
		__IO unsigned int OPR;	  /*!< OPR Flow Register    */
		__I unsigned int  RSV;	  /*!< reserve    */
		__IO unsigned int STS;	  /*!< Verify Register    */
	} EFC_Type;

	typedef struct
	{
		__IO unsigned int SCON;
		__IO unsigned int SBUF;
		__IO unsigned int SADDR;
		__IO unsigned int SADEN;
		__IO unsigned int ISR;
		__IO unsigned int BDIV;
	} UART_Type;

	typedef struct
	{
		__IO unsigned int CR0;
		__IO unsigned int CSN;
		__I unsigned int  SR;
		__IO unsigned int DR;
	} SPI_Type;

	typedef struct
	{
		__IO unsigned int CR;
		__IO unsigned int SWCR;
		__IO unsigned int SWBR;
		__IO unsigned int GAPW;
		__IO unsigned int CMD1;
		__IO unsigned int CMD2;
		__IO unsigned int CMD3;
		__IO unsigned int CMD4;
		__IO unsigned int CMD5;
		__IO unsigned int CMD6;
		__I unsigned int  RXD;
		__IO unsigned int TXD;
		__IO unsigned int TXS;
		__IO unsigned int INTEN;
		__IO unsigned int STS;
		__I unsigned int  DBG;
	} TWC_Type;

	/* ================================================================================
	 */
	/* ================                     TIMERS ================ */
	/* ================================================================================
	 */

	/**
	 * @brief Timer Control (TIMERS)
	 */

	typedef struct /*!< TIMERS Structure             */
	{
		__IO unsigned int CON;	   /*!< TIMCON    */
		__I unsigned int  INTFLAG; /*!< TIMINTFLAG */
		__O unsigned int  INTCLR;  /*!< TIMINTCLR  */
	} TIMERS_Type;

	/* ================================================================================
	 */
	/* ================                      TIM0 ================ */
	/* ================================================================================
	 */

	/**
	 * @brief Timer Control (TIM0)
	 */

	typedef struct /*!< TIM0 Structure            */
	{
		__IO unsigned int CTCG1; /*!< TIMCTCG1 */
		__IO unsigned int CTCG2; /*!< TIMCTCG2 */
		__I unsigned int  CTVAL; /*!< TIMCTVAL  */
		__IO unsigned int PWCON; /*!< TIMPWCON */
	} TIM_Type;

	typedef struct
	{
		__IO unsigned int ANAC_CFG;		  // 00
		__IO unsigned int LED_CFG;		  // 04
		__IO unsigned int PDSENS_CFG;	  // 08
		__IO unsigned int CMP_CFG;		  // 0C
		__IO unsigned int ADC_CFG;		  // 10
		__IO unsigned int ADC_CTL;		  // 14
		__IO unsigned int LVD_CFG;		  // 18
		__IO unsigned int CLK_CFG;		  // 1C
		__IO unsigned int AINSEL;		  // 20
		__IO unsigned int DLY_CFG;		  // 24
		__IO unsigned int ME_CTL;		  // 28
		__IO unsigned int ANAC_FLAG;	  // 2C
		__IO unsigned int THR1_DATA;	  // 30
		__IO unsigned int THR2_DATA;	  // 34
		__IO unsigned int RSV;			  // 38
		__IO unsigned int WPROT;		  // 3C
		__IO unsigned int ADC_VAL[8];	  // 40
		__IO unsigned int AVG_VAL;		  // 60
		__IO unsigned int RSV7[7];		  // 64 - 7C
		__IO unsigned int HRC_TRIM_1M;	  // 80
		__IO unsigned int HRC_TRIM_2M;	  // 84
		__IO unsigned int HRC_TRIM_4M;	  // 88
		__IO unsigned int HRC_TRIM_8M;	  // 8C
		__IO unsigned int HRC_TRIM_16M;	  // 90
		__IO unsigned int LRC_TRIM;		  // 94
		__IO unsigned int MRC_TRIM;		  // 98
		__IO unsigned int CMP_TRIM;		  // 9C
		__IO unsigned int BG4A_TRIM;	  // A0
		__IO unsigned int BG4S_TRIM;	  // A4
		__IO unsigned int BG4A_OPTRIM;	  // A8
		__IO unsigned int VOLTREF_OPTRIM; // AC
		__IO unsigned int NVR_OPTION0;	  // B0
		__IO unsigned int ANAC_REV0;	  // B4
		__IO unsigned int NVR_OPTION1;	  // B8
		__IO unsigned int NVR_OPTION2;	  // BC
		__IO unsigned int TESTCTL;		  // C0
		__IO unsigned int TEST;			  // C4
		__IO unsigned int EST_CFG;		  // C8
		__IO unsigned int EST_RAM_BIST;	  // CC
	} ANAC_Type;

	typedef struct
	{
		__IO unsigned int DATA;
		__IO unsigned int OE;
		__IO unsigned int PU;
		__IO unsigned int PD;
		__IO unsigned int OTYPE;
		__IO unsigned int ADS;
		__IO unsigned int DRS;
		__IO unsigned int AF0;
		__IO unsigned int AF1;
		__IO unsigned int INT_TYPE;
		__IO unsigned int INT_POLARITY;
		__IO unsigned int EXT_INTE;
		__IO unsigned int INTF;
		__IO unsigned int CTL;

	} IOM_Type;

	typedef struct
	{
		__IO unsigned int CR;
		__IO unsigned int CFG;
		__IO unsigned int CNT;
		__IO unsigned int INTSTS;

	} LPTIM_Type;

	typedef struct
	{
		__IO unsigned int RST;
		__IO unsigned int CR;

	} WDT_Type;

	/* enum definitions */
	typedef enum
	{
		DISABLE = 0,
		ENABLE	= !DISABLE
	} EventStatus,
		ControlStatus;
	typedef enum
	{
		FALSE = 0,
		TRUE  = !FALSE
	} BOOL;
	typedef enum
	{
		RESET = 0,
		SET	  = 1,
		MAX	  = 0X7FFFFFFF
	} FlagStatus;
	typedef enum
	{
		ERROR	= 0,
		SUCCESS = !ERROR
	} ErrStatus;

/* bit operations */
#define REG32(addr)					 (*((volatile unsigned int *)(addr)))
#define REG16(addr)					 (*((volatile unsigned short *)(addr)))
#define REG8(addr)					 (*((volatile unsigned char *)(addr)))
#define BIT(x)						 ((unsigned int)0x01U << (x))
#define BITS(start, end)			 ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (end))))
#define GET_BITS(regval, start, end) (((regval)&BITS((start), (end))) >> (start))

	/* main flash and SRAM memory map */

#define FLASH_BASE ((unsigned int)0x10100000UL) /*!< main FLASH base address          */
#define SRAM_BASE  ((unsigned int)0x20000000UL) /*!< SRAM0 base address               */
	/* ================================================================================
	 */
	/* ================              Peripheral memory map ================ */
	/* ================================================================================
	 */

#define EFC_BASE	0x40000000UL
#define SYSC_BASE	0x40001000UL
#define TIMERS_BASE 0x400100A0UL
#define TIM1_BASE	0x40010000UL
#define TIM2_BASE	0x40010014UL
#define SPI_BASE	0x40010800UL
#define UART1_BASE	0x40011000UL
#define UART2_BASE	0x40010c00UL
#define TWC_BASE	0x40011800UL
#define ANAC_BASE	0x40011c00UL
#define IOM_BASE	0x40012400UL
#define PMU_BASE	0x40012c00UL
#define LPTIM_BASE	0x40013000UL
#define WDT_BASE	0x40013400UL
	/* ================================================================================
	 */
	/* ================             Peripheral declaration ================ */
	/* ================================================================================
	 */

#define EFC	   ((EFC_Type *)EFC_BASE)
#define SYSC   ((SYSC_Type *)SYSC_BASE)
#define TIMERS ((TIMERS_Type *)TIMERS_BASE)
#define TIM1   ((TIM_Type *)TIM1_BASE)
#define TIM2   ((TIM_Type *)TIM2_BASE)
#define SPI	   ((SPI_Type *)SPI_BASE)
#define UART1  ((UART_Type *)UART1_BASE)
#define UART2  ((UART_Type *)UART2_BASE)
#define TWC	   ((TWC_Type *)TWC_BASE)
#define ANAC   ((ANAC_Type *)ANAC_BASE)
#define IOM	   ((IOM_Type *)IOM_BASE)
#define PMU	   ((PMU_Type *)PMU_BASE)
#define LPTIM  ((LPTIM_Type *)LPTIM_BASE)
#define WDT	   ((WDT_Type *)WDT_BASE)

	/** @} */ /* End of group Device_Peripheral_Registers */
	/** @} */ /* End of group Phonix04 */
	/** @} */ /* End of group FHSJDZ */

	// data type define
	typedef unsigned int   u32;
	typedef unsigned short u16;
	typedef unsigned char  u8;

	typedef signed int	 s32;
	typedef signed short s16;
	typedef signed char	 s8;

#ifdef _FW_DEBUG
	extern int __wrap_printf(const char *fmt, ...);
#define PARAM_CHECK(x)                                                                                                 \
	{                                                                                                                  \
		if (x)                                                                                                         \
		{                                                                                                              \
			__wrap_printf("Wrong parameters value: file:%s,on line:%d\r\n", __FILE__, __LINE__);                       \
			while (1)                                                                                                  \
				;                                                                                                      \
		}                                                                                                              \
	}
#else
#define PARAM_CHECK(x)
#endif

#ifdef cplusplus
}
#endif
#endif /* __PHNX04_H__ */
