/**
  ******************************************************************************
  * @file    system_phnx04.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-08-23
  * @brief   Device peripheral access layer system header files.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_PHNX04_H__
#define __SYSTEM_PHNX04_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @addtogroup FDV32S302_System
  * @{
  */

/** @defgroup FDV32S302_System_Exported_Constants
  * @{
  */

/** @defgroup FDV32S302_System_Source_Clock_Definition
  * @{
  */

#define F_HRC1M	 1
#define F_HRC2M	 2
#define F_HRC4M	 3
#define F_HRC8M	 4
#define F_HRC16M 5
#define F_LRC	 8
/**
  * @}
  */

/** @defgroup FDV32S302_System_source_clock_selection
  * @{
  */

#ifndef SYSC_CLK_SRC_SEL
#define SYSC_CLK_SRC_SEL F_HRC8M
#endif
/**
  * @}
  */

/** @defgroup FDV32S302_System_bus_clock_divider
  * @{
  */

enum _DIV
{
	DIV1 = 0,
	DIV2,
	DIV3,
	DIV4,
	DIV5,
	DIV6,
	DIV7,
	DIV8,
	DIV9,
	DIV10,
	DIV11,
	DIV12,
	DIV13,
	DIV14,
	DIV15,
	DIV16,
	DIV17,
	DIV18,
	DIV19,
	DIV20,
	DIV21,
	DIV22,
	DIV23,
	DIV24,
	DIV25,
	DIV26,
	DIV27,
	DIV28,
	DIV29,
	DIV30,
	DIV31,
	DIV32,
	DIV33,
	DIV34,
	DIV35,
	DIV36,
	DIV37,
	DIV38,
	DIV39,
	DIV40,
	DIV41,
	DIV42,
	DIV43,
	DIV44,
	DIV45,
	DIV46,
	DIV47,
	DIV48,
	DIV49,
	DIV50,
	DIV51,
	DIV52,
	DIV53,
	DIV54,
	DIV55,
	DIV56,
	DIV57,
	DIV58,
	DIV59,
	DIV60,
	DIV61,
	DIV62,
	DIV63,
	DIV64,
	DIV65,
	DIV66,
	DIV67,
	DIV68,
	DIV69,
	DIV70,
	DIV71,
	DIV72,
	DIV73,
	DIV74,
	DIV75,
	DIV76,
	DIV77,
	DIV78,
	DIV79,
	DIV80,
	DIV81,
	DIV82,
	DIV83,
	DIV84,
	DIV85,
	DIV86,
	DIV87,
	DIV88,
	DIV89,
	DIV90,
	DIV91,
	DIV92,
	DIV93,
	DIV94,
	DIV95,
	DIV96,
	DIV97,
	DIV98,
	DIV99,
	DIV100,
	DIV101,
	DIV102,
	DIV103,
	DIV104,
	DIV105,
	DIV106,
	DIV107,
	DIV108,
	DIV109,
	DIV110,
	DIV111,
	DIV112,
	DIV113,
	DIV114,
	DIV115,
	DIV116,
	DIV117,
	DIV118,
	DIV119,
	DIV120,
	DIV121,
	DIV122,
	DIV123,
	DIV124,
	DIV125,
	DIV126,
	DIV127,
	DIV128,
};
#define SYSC_AHB_DIV DIV1
#define SYSC_APB_DIV DIV1
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup FDV32S302_System_Exported_types
  * @{
  */

extern unsigned int SystemCoreClock; /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @defgroup FDV32S302_System_Exported_Functions
  * @{
  */

extern void			MSOFT_IntHandler(void);
extern void			MTIM_IntHandler(void);
extern void			MEXP_Handler(void);
extern void			NMI_Handler(void);
extern void			PMU_IrqHandler(void);
extern void			LPT_IrqHandler(void);
extern void			TIMER1_IrqHandler(void);
extern void			TIMER2_IrqHandler(void);
extern void			TIMER3_IrqHandler(void);
extern void			TIMER4_IrqHandler(void);
extern void			UART1_IrqHandler(void);
extern void			UART2_IrqHandler(void);
extern void			SPI_IrqHandler(void);
extern void			ANAC_IrqHandler(void);
extern void			EFC_IrqHandler(void);
extern void			IOM_IrqHandler(void);
extern void			I2C_IrqHandler(void);
extern void			RTC_IrqHandler(void);
extern void			TWC_IrqHandler(void);
extern void			LPU_IrqHandler(void);
extern unsigned int handle_trap(unsigned int mcause, unsigned int epc);
extern void			SystemInit(void);
extern void			SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_PHNX04_H__ */

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

