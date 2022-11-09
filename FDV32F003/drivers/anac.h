/**
  ******************************************************************************
  * @file    anac.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-08-29
  * @brief   This file contains all functional prototypes of the ANAC-related
  *          module firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ANAC_H__
#define __ANAC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx05.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @addtogroup ANAC
  * @{
  */

/** @defgroup ANAC_module_register_bit_definition
  * @{
  */

/* ANAC_CFG */
#define ANAC_ANAC_CFG_SLDO_VRSEL   BIT(3)
#define ANAC_ANAC_CFG_HRC_EN	   BIT(2)
#define ANAC_ANAC_CFG_LRC_EN	   BIT(2)
#define ANAC_ANAC_CFG_ALDO4D_EN    BIT(0)

/* CMP_CFG */
#define ANAC_CMP_CFG_HYSSEL BITS(8, 9)
#define ANAC_CMP_CFG_VINSEL BITS(5, 7)
#define ANAC_CMP_CFG_VIPSEL BITS(2, 4)
#define ANAC_CMP_CFG_INV	BIT(1)
#define ANAC_CMP_CFG_EN		BIT(0)

#define ANAC_CMP_CFG_HYSSEL_0MV	 (0 << 8)
#define ANAC_CMP_CFG_HYSSEL_12MV (1 << 8)
#define ANAC_CMP_CFG_HYSSEL_25MV (2 << 8)
#define ANAC_CMP_CFG_HYSSEL_50MV (3 << 8)

#define ANAC_CMP_CFG_VINSEL_VC1N0		(0 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N1		(1 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N2		(2 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N3		(3 << 5)
#define ANAC_CMP_CFG_VINSEL_V1P5D		(4 << 5)
#define ANAC_CMP_CFG_VINSEL_VREF_FLASH	(5 << 5)
#define ANAC_CMP_CFG_VINSEL_VBG1P0		(6 << 5)
#define ANAC_CMP_CFG_VINSEL_VBG1P2		(7 << 5)

#define ANAC_CMP_CFG_VIPSEL_VC1P0		 (0 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P1		 (1 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P2		 (2 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P3		 (3 << 2)
#define ANAC_CMP_CFG_VIPSEL_V1P5D		 (4 << 2)
#define ANAC_CMP_CFG_VIPSEL_VREF_FLASH   (5 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBG1P0		 (6 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBG1P2		 (7 << 2)

#define ANAC_CMP_CFG_HYSSEL_pos (8)
#define ANAC_CMP_CFG_VINSEL_pos (5)
#define ANAC_CMP_CFG_VIPSEL_pos (2)

/* LVD_CFG */
#define ANAC_LVD_CFG_ACT_SEL BIT(16)
#define ANAC_LVD_CFG_FLT	 BITS(8, 15)
#define ANAC_LVD_CFG_VTSEL	 BITS(4, 7)
#define ANAC_LVD_CFG_SRCSEL  BITS(2, 3)
#define ANAC_LVD_CFG_LVD_IE  BIT(1)
#define ANAC_LVD_CFG_LVD_EN  BIT(0)

#define ANAC_LVD_CFG_VTSEL_1P9V	 (0 << 4)
#define ANAC_LVD_CFG_VTSEL_2P1V	 (1 << 4)
#define ANAC_LVD_CFG_VTSEL_2P2V	 (2 << 4)
#define ANAC_LVD_CFG_VTSEL_2P3V	 (3 << 4)
#define ANAC_LVD_CFG_VTSEL_2P4V	 (4 << 4)
#define ANAC_LVD_CFG_VTSEL_2P5V	 (5 << 4)
#define ANAC_LVD_CFG_VTSEL_2P65V (6 << 4)
#define ANAC_LVD_CFG_VTSEL_2P8V	 (7 << 4)
#define ANAC_LVD_CFG_VTSEL_2P9V	 (8 << 4)
#define ANAC_LVD_CFG_VTSEL_3P05V (9 << 4)
#define ANAC_LVD_CFG_VTSEL_3P2V	 (10 << 4)
#define ANAC_LVD_CFG_VTSEL_3P35V (11 << 4)
#define ANAC_LVD_CFG_VTSEL_3P5V	 (12 << 4)
#define ANAC_LVD_CFG_VTSEL_3P7V	 (13 << 4)
#define ANAC_LVD_CFG_VTSEL_4P3V	 (14 << 4)
#define ANAC_LVD_CFG_VTSEL_1P2V	 (15 << 4)

#define ANAC_LVD_CFG_SRCSEL_LOWPWR_VCC (0 << 2)
#define ANAC_LVD_CFG_SRCSEL_V5P0	   (1 << 2)
#define ANAC_LVD_CFG_SRCSEL_LVDI0	   (2 << 2)
#define ANAC_LVD_CFG_SRCSEL_LVDI1	   (3 << 2)

#define ANAC_LVD_CFG_FLT_pos	(8)
#define ANAC_LVD_CFG_VTSEL_pos	(4)
#define ANAC_LVD_CFG_SRCSEL_pos (2)

/* AINSEL */
#define ANAC_AINSEL_GPIO0_SEL  BIT(0)
#define ANAC_AINSEL_GPIO1_SEL  BIT(1)
#define ANAC_AINSEL_GPIO2_SEL  BIT(2)
#define ANAC_AINSEL_GPIO3_SEL  BIT(3)
#define ANAC_AINSEL_GPIO4_SEL  BIT(4)
#define ANAC_AINSEL_GPIO5_SEL  BIT(5)
#define ANAC_AINSEL_GPIO6_SEL  BIT(6)
#define ANAC_AINSEL_GPIO7_SEL  BIT(7)
#define ANAC_AINSEL_GPIO8_SEL  BIT(8)
#define ANAC_AINSEL_GPIO9_SEL  BIT(9)
#define ANAC_AINSEL_GPIO10_SEL BIT(10)
#define ANAC_AINSEL_GPIO11_SEL BIT(11)
#define ANAC_AINSEL_GPIO12_SEL BIT(12)
#define ANAC_AINSEL_GPIO13_SEL BIT(13)
#define ANAC_AINSEL_GPIO14_SEL BIT(14)
#define ANAC_AINSEL_GPIO15_SEL BIT(15)
#define ANAC_AINSEL_GPIO16_SEL BIT(16)

#define ANAC_AINSEL_GPIO0_SEL_RSV		 (0 << 0)
#define ANAC_AINSEL_GPIO0_SEL_VC1P0		 (1 << 0)
#define ANAC_AINSEL_GPIO1_SEL_AIN04		 (0 << 1)
#define ANAC_AINSEL_GPIO1_SEL_VC1O		 (1 << 1)
#define ANAC_AINSEL_GPIO2_SEL_LVDI0		 (0 << 2)
#define ANAC_AINSEL_GPIO2_SEL_AIN02		 (1 << 2)
#define ANAC_AINSEL_GPIO3_SEL_LVDI1		 (0 << 3)
#define ANAC_AINSEL_GPIO3_SEL_AIN03		 (1 << 3)
#define ANAC_AINSEL_GPIO4_SEL_VC1P2		 (0 << 4)
#define ANAC_AINSEL_GPIO4_SEL_AIN05		 (1 << 4)
#define ANAC_AINSEL_GPIO5_SEL_VC1P3		 (0 << 5)
#define ANAC_AINSEL_GPIO5_SEL_AIN06		 (1 << 5)
#define ANAC_AINSEL_GPIO6_SEL_VC1N0		 (0 << 6)
#define ANAC_AINSEL_GPIO6_SEL_AIN07		 (1 << 6)
#define ANAC_AINSEL_GPIO7_SEL_VREF_FLASH (0 << 7)
#define ANAC_AINSEL_GPIO7_SEL_AIN11		 (1 << 7)
#define ANAC_AINSEL_GPIO8_SEL_VC1N2		 (0 << 8)
#define ANAC_AINSEL_GPIO8_SEL_AIN08		 (1 << 8)
#define ANAC_AINSEL_GPIO9_SEL_AIN09		 (0 << 9)
#define ANAC_AINSEL_GPIO9_SEL_VC1N1		 (1 << 9)
#define ANAC_AINSEL_GPIO10_SEL_RSV		 (0 << 10)
#define ANAC_AINSEL_GPIO10_SEL_VC1N3	 (1 << 10)
#define ANAC_AINSEL_GPIO11_SEL_ATS1		 (0 << 11)
#define ANAC_AINSEL_GPIO11_SEL_AIN10	 (1 << 11)
#define ANAC_AINSEL_GPIO12_SEL_VC1P1	 (0 << 12)
#define ANAC_AINSEL_GPIO12_SEL_VREF		 (1 << 12)
#define ANAC_AINSEL_GPIO13_SEL_RSV		 (0 << 13)
#define ANAC_AINSEL_GPIO13_SEL_AIN03	 (1 << 13)
#define ANAC_AINSEL_GPIO14_SEL_RSV		 (0 << 14)
#define ANAC_AINSEL_GPIO14_SEL_AIN02	 (1 << 14)
#define ANAC_AINSEL_GPIO15_SEL_AIN01	 (0 << 15)
#define ANAC_AINSEL_GPIO15_SEL_VC1N0	 (1 << 15)
#define ANAC_AINSEL_GPIO16_SEL_AIN00	 (0 << 16)
#define ANAC_AINSEL_GPIO16_SEL_LVDI0	 (1 << 16)

/* ANAC_FLAG */
#define ANAC_ANAC_FLAG_CMP_OUT	   BIT(2)
#define ANAC_ANAC_FLAG_LVD_OUT	   BIT(1)
#define ANAC_ANAC_FLAG_LVD_INTF	   BIT(0)

/**
  * @}
  */

/** @defgroup ANAC_Exported_Types
  * @{
  */

/**
  * @brief CMP Init structure definition
  */

typedef struct
{
	u8 CMP_HysSel; 							/*!< Specify the CMP hysteresis selection.
												 This parameter can be a value of @ref CMP_Hysteresis_Selection. */

	u8 CMP_VinSel; 							/*!< Specify CMP negative input signal selection.
												 This parameter can be a value of @ref CMP_negative_input_signal_selection. */

	u8 CMP_VipSel; 							/*!< Specify CMP positive input signal selection.
												 This parameter can be a value of @ref CMP_positive_input_signal_selection. */

	FunctionalState CMP_InvertedOutCmd; 	/*!< Specifies the new state for the reverse output of CMP results. 
												 This parameter can be set to ENABLE or DISABLE. */
} CMP_InitTypeDef;

/**
  * @brief LVD Init structure definition
  */

typedef struct
{
	u8 LVD_FilterTime; 						/*!< Specify low voltage detection LVD_OUT filter time,
												 The filtering unit is the LRC clock cycle.
												 This parameter must range from 0 to 0xFF. */

	u8 LVD_ThresholdVoltage; 				/*!< Specify the LVD threshold voltage.
												 This parameter can be a value of @ref LVD_threshold_voltage. */

	u8 LVD_MonitoSource; 					/*!< Specify the LVD monitor source.
												 This parameter can be a value of @ref LVD_monitor_source. */
} LVD_InitTypeDef;

/**
  * @}
  */

/** @defgroup ANAC_Exported_Constants
  * @{
  */

/**
  * @defgroup ANAC_write_protection_unlock
  * @{
  */

#define ANAC_WPROT_V0 (0xCA)
#define ANAC_WPROT_V1 (0x53)
#define ANAC_WPT_UNLOCK()                                                                                              \
	{                                                                                                                  \
		ANAC->WPROT = ANAC_WPROT_V0;                                                                                   \
		ANAC->WPROT = ANAC_WPROT_V1;                                                                                   \
	}
/**
  * @}
  */

/** @defgroup ANAC_sleep_LDO_output_voltage
  * @{
  */

#define ANAC_SLDO_VRSEL_1P5V (0)
#define ANAC_SLDO_VRSEL_1P2V (1)

#define IS_ANAC_SLDO_VRSEL(VRSEL) ((VRSEL) == ANAC_SLDO_VRSEL_1P5V || (VRSEL) == ANAC_SLDO_VRSEL_1P2V)
/**
  * @}
  */

/** @defgroup CMP_Hysteresis_Selection
  * @{
  */

#define CMP_HYS_SEL_0MV	   (0)
#define CMP_HYS_SEL_12P5MV (1)
#define CMP_HYS_SEL_25MV   (2)
#define CMP_HYS_SEL_50MV   (3)

#define IS_CMP_HYSSEL(HYSSEL)                                                                                          \
	((HYSSEL) == CMP_HYS_SEL_0MV || (HYSSEL) == CMP_HYS_SEL_12P5MV || (HYSSEL) == CMP_HYS_SEL_25MV ||                  \
	 (HYSSEL) == CMP_HYS_SEL_50MV)
/**
  * @}
  */

/** @defgroup CMP_negative_input_signal_selection
  * @{
  */

#define CMP_VIN_SEL_VC1N0		(0)
#define CMP_VIN_SEL_VC1N1		(1)
#define CMP_VIN_SEL_VC1N2		(2)
#define CMP_VIN_SEL_VC1N3		(3)
#define CMP_VIN_SEL_V1P5D		(4)
#define CMP_VIN_SEL_VREF_FLASH	(5)
#define CMP_VIN_SEL_VBG1P0		(6)
#define CMP_VIN_SEL_VBG1P2		(7)

#define IS_CMP_VINSEL(VINSEL)                                                                                          \
	((VINSEL) == CMP_VIN_SEL_VC1N0 || (VINSEL) == CMP_VIN_SEL_VC1N1 || (VINSEL) == CMP_VIN_SEL_VC1N2 ||                \
	 (VINSEL) == CMP_VIN_SEL_VC1N3 || (VINSEL) == CMP_VIN_SEL_V1P5D || (VINSEL) == CMP_VIN_SEL_VREF_FLASH ||           \
	 (VINSEL) == CMP_VIN_SEL_VBG1P0 || (VINSEL) == CMP_VIN_SEL_VBG1P2)
/**
  * @}
  */

/** @defgroup CMP_positive_input_signal_selection
  * @{
  */

#define CMP_VIP_SEL_VC1P0		(0)
#define CMP_VIP_SEL_VC1P1		(1)
#define CMP_VIP_SEL_VC1P2		(2)
#define CMP_VIP_SEL_VC1P3		(3)
#define CMP_VIP_SEL_V1P5D		(4)
#define CMP_VIP_SEL_VREF_FLASH  (5)
#define CMP_VIP_SEL_VBG1P0		(6)
#define CMP_VIP_SEL_VBG1P2		(7)

#define IS_CMP_VIPSEL(VIPSEL)                                                                                          \
	((VIPSEL) == CMP_VIP_SEL_VC1P0 || (VIPSEL) == CMP_VIP_SEL_VC1P1 || (VIPSEL) == CMP_VIP_SEL_VC1P2 ||                \
	 (VIPSEL) == CMP_VIP_SEL_VC1P3 || (VIPSEL) == CMP_VIP_SEL_V1P5D || (VIPSEL) == CMP_VIP_SEL_VREF_FLASH ||           \
	 (VIPSEL) == CMP_VIP_SEL_VBG1P0 || (VIPSEL) == CMP_VIP_SEL_VBG1P2)
/**
  * @}
  */

/** @defgroup LVD_threshold_voltage
  * @{
  */

#define LVD_THRESHOLD_VOL_1P9V	(0)
#define LVD_THRESHOLD_VOL_2P1V	(1)
#define LVD_THRESHOLD_VOL_2P2V	(2)
#define LVD_THRESHOLD_VOL_2P3V	(3)
#define LVD_THRESHOLD_VOL_2P4V	(4)
#define LVD_THRESHOLD_VOL_2P5V	(5)
#define LVD_THRESHOLD_VOL_2P65V (6)
#define LVD_THRESHOLD_VOL_2P8V	(7)
#define LVD_THRESHOLD_VOL_2P9V	(8)
#define LVD_THRESHOLD_VOL_3P05V (9)
#define LVD_THRESHOLD_VOL_3P2V	(10)
#define LVD_THRESHOLD_VOL_3P35V (11)
#define LVD_THRESHOLD_VOL_3P5V	(12)
#define LVD_THRESHOLD_VOL_3P7V	(13)
#define LVD_THRESHOLD_VOL_4P3V	(14)
#define LVD_THRESHOLD_VOL_1P2V	(15)

#define IS_LVD_THRESHOLD_VOL(VOL)                                                                                      \
	(((VOL) == LVD_THRESHOLD_VOL_1P9V) || ((VOL) == LVD_THRESHOLD_VOL_2P1V) || ((VOL) == LVD_THRESHOLD_VOL_2P2V) ||    \
	 ((VOL) == LVD_THRESHOLD_VOL_2P3V) || ((VOL) == LVD_THRESHOLD_VOL_2P4V) || ((VOL) == LVD_THRESHOLD_VOL_2P5V) ||    \
	 ((VOL) == LVD_THRESHOLD_VOL_2P65V) || ((VOL) == LVD_THRESHOLD_VOL_2P8V) || ((VOL) == LVD_THRESHOLD_VOL_2P9V) ||   \
	 ((VOL) == LVD_THRESHOLD_VOL_3P05V) || ((VOL) == LVD_THRESHOLD_VOL_3P2V) || ((VOL) == LVD_THRESHOLD_VOL_3P35V) ||  \
	 ((VOL) == LVD_THRESHOLD_VOL_3P5V) || ((VOL) == LVD_THRESHOLD_VOL_3P7V) || ((VOL) == LVD_THRESHOLD_VOL_4P3V) ||    \
	 ((VOL) == LVD_THRESHOLD_VOL_1P2V))
/**
  * @}
  */

/** @defgroup LVD_monitor_source
  * @{
  */

#define LVD_MONITOR_SOURCE_LPVCC (0)
#define LVD_MONITOR_SOURCE_V5P0	 (1)
#define LVD_MONITOR_SOURCE_LVDI0 (2)
#define LVD_MONITOR_SOURCE_LVDI1 (3)

#define IS_LVD_MONITOR_SOURCE(SOURCE)                                                                                  \
	(((SOURCE) == LVD_MONITOR_SOURCE_LPVCC) || ((SOURCE) == LVD_MONITOR_SOURCE_V5P0) ||                                \
	 ((SOURCE) == LVD_MONITOR_SOURCE_LVDI0) || ((SOURCE) == LVD_MONITOR_SOURCE_LVDI1))
/**
  * @}
  */

/** @defgroup AINSEL_Multiplex_function_selection
  * @{
  */

#define AINSEL_MULTIPLEX_P00_SEL_RSV		(0)
#define AINSEL_MULTIPLEX_P00_SEL_VC1P0		(1)
#define AINSEL_MULTIPLEX_P01_SEL_AIN04		(2)
#define AINSEL_MULTIPLEX_P01_SEL_VC1O		(3)
#define AINSEL_MULTIPLEX_P02_SEL_LVDI0		(4)
#define AINSEL_MULTIPLEX_P02_SEL_AIN02		(5)
#define AINSEL_MULTIPLEX_P03_SEL_LVDI1		(6)
#define AINSEL_MULTIPLEX_P03_SEL_AIN03		(7)
#define AINSEL_MULTIPLEX_P04_SEL_VC1P2		(8)
#define AINSEL_MULTIPLEX_P04_SEL_AIN05		(9)
#define AINSEL_MULTIPLEX_P05_SEL_VC1P3		(10)
#define AINSEL_MULTIPLEX_P05_SEL_AIN06		(11)
#define AINSEL_MULTIPLEX_P06_SEL_VC1N0		(12)
#define AINSEL_MULTIPLEX_P06_SEL_AIN07		(13)
#define AINSEL_MULTIPLEX_P07_SEL_VREF_FLASH (14)
#define AINSEL_MULTIPLEX_P07_SEL_AIN11		(15)
#define AINSEL_MULTIPLEX_P08_SEL_VC1N2		(16)
#define AINSEL_MULTIPLEX_P08_SEL_AIN08		(17)
#define AINSEL_MULTIPLEX_P09_SEL_AIN09		(18)
#define AINSEL_MULTIPLEX_P09_SEL_VC1N1		(19)
#define AINSEL_MULTIPLEX_P10__SEL_RSV		(20)
#define AINSEL_MULTIPLEX_P10__SEL_VC1N3		(21)
#define AINSEL_MULTIPLEX_P11__SEL_ATS1		(22)
#define AINSEL_MULTIPLEX_P11__SEL_AIN10		(23)
#define AINSEL_MULTIPLEX_P12__SEL_VC1P1		(24)
#define AINSEL_MULTIPLEX_P12__SEL_VREF		(25)
#define AINSEL_MULTIPLEX_P13__SEL_RSV		(26)
#define AINSEL_MULTIPLEX_P13__SEL_AIN03		(27)
#define AINSEL_MULTIPLEX_P14__SEL_RSV		(28)
#define AINSEL_MULTIPLEX_P14__SEL_AIN02		(29)
#define AINSEL_MULTIPLEX_P15__SEL_AIN01		(30)
#define AINSEL_MULTIPLEX_P15__SEL_VC1N0		(31)
#define AINSEL_MULTIPLEX_P16__SEL_AIN00		(32)
#define AINSEL_MULTIPLEX_P16__SEL_LVDI0		(33)

#define IS_AINSEL_MULTIPLEXSEL(MULTIPLEXSEL)                                                                           \
	(((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P00_SEL_RSV)        || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P00_SEL_VC1P0)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P01_SEL_AIN04)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P01_SEL_VC1O)   || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P02_SEL_LVDI0)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P02_SEL_AIN02)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P03_SEL_LVDI1)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P03_SEL_AIN03)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P04_SEL_VC1P2)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P04_SEL_AIN05)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P05_SEL_VC1P3)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P05_SEL_AIN06)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P06_SEL_VC1N0)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P06_SEL_AIN07)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P07_SEL_VREF_FLASH) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P07_SEL_AIN11)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P08_SEL_VC1N2)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P08_SEL_AIN08)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P09_SEL_AIN09)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P09_SEL_VC1N1)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P10__SEL_RSV)       || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P10__SEL_VC1N3) || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P11__SEL_ATS1)      || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P11__SEL_AIN10) || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P12__SEL_VC1P1)     || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P12__SEL_VREF)  || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P13__SEL_RSV)       || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P13__SEL_AIN03) || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P14__SEL_RSV)       || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P14__SEL_AIN02) || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P15__SEL_AIN01)     || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P15__SEL_VC1N0) || \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P16__SEL_AIN00)     || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P16__SEL_LVDI0))
/**
  * @}
  */

/** @defgroup ANAC_flags_definition
  * @{
  */

#define ANAC_FLAG_CMP_OUT	  BIT(2)
#define ANAC_FLAG_LVD_OUT	  BIT(1)
#define ANAC_FLAG_LVD_INTF	  BIT(0)

#define IS_ANAC_GET_FLAG(FLAG)                                                                                         \
	(((FLAG) == ANAC_FLAG_CMP_OUT) || ((FLAG) == ANAC_FLAG_LVD_OUT) || ((FLAG) == ANAC_FLAG_LVD_INTF))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ANAC_Exported_Functions
  * @{
  */

void	   ANAC_DeInit(void);
void	   ANAC_SetSleepLDOVoltage(u8 OutputVol);
void	   ANAC_HRCClockCmd(FunctionalState NewState);
void	   ANAC_LRCClockCmd(FunctionalState NewState);
void	   ANAC_ActiveLDO4DigitalCmd(FunctionalState NewState);
void	   CMP_Init(CMP_InitTypeDef *CMP_InitStruct);
void	   CMP_Cmd(FunctionalState NewState);
void	   LVD_Init(LVD_InitTypeDef *LVD_InitStruct);
void	   LVD_Cmd(FunctionalState NewState);
void	   LVD_ITConfig(FunctionalState NewState);
FlagStatus LVD_GetFlagStatus(void);
ITStatus   LVD_GetITStatus(void);
void	   LVD_ClearFlag(void);
void	   AINSEL_MultiplexConfig(u8 MultiplexSel);
FlagStatus ANAC_GetFlagStatus(u16 ANAC_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __ANAC_H__ */

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

