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
#include "phnx04.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @addtogroup ANAC
  * @{
  */

/** @defgroup ANAC_module_register_bit_definition
  * @{
  */

/* LED_CFG */
#define ANAC_LED_CFG_LED_SEL   BIT(13)
#define ANAC_LED_CFG_IBULE_CC  BITS(7, 11)
#define ANAC_LED_CFG_IBLUE_EN  BIT(6)
#define ANAC_LED_CFG_IIRLED_CC BITS(1, 5)
#define ANAC_LED_CFG_IIRLED_EN BIT(0)

#define ANAC_LED_CFG_LED_SEL_IR	  (0 << 13)
#define ANAC_LED_CFG_LED_SEL_BLUE (1 << 13)

#define ANAC_LED_CFG_IBULE_CC_pos  (7) /* 0-0x1f:0-310mA step:10mA */
#define ANAC_LED_CFG_IIRLED_CC_pos (1) /* 0-0x1f:0-310mA step:10mA */

/* PDSENS_CFG */
#define ANAC_PDSENS_CFG_CHRG BIT(7)
#define ANAC_PDSENS_CFG_GC	 BITS(2, 6)
#define ANAC_PDSENS_CFG_RST	 BIT(1)
#define ANAC_PDSENS_CFG_EN	 BIT(0)

#define ANAC_PDSENS_CFG_GC_X50	  (0 << 6)
#define ANAC_PDSENS_CFG_GC_X100	  (1 << 6)
#define ANAC_PDSENS_CFG_GC_DB	  BIT(2, 5)
#define ANAC_PDSENS_CFG_GC_DB_pos (2) /* 0-0xf: 32-17dB step:-1dB */
#define ANAC_PDSENS_CFG_GC_pos	  (2)

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

#define ANAC_CMP_CFG_VINSEL_VC1N0	(0 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N1	(1 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N2	(2 << 5)
#define ANAC_CMP_CFG_VINSEL_VREF	(3 << 5)
#define ANAC_CMP_CFG_VINSEL_VREF_VO	(4 << 5)
#define ANAC_CMP_CFG_VINSEL_VBGS	(5 << 5)
#define ANAC_CMP_CFG_VINSEL_VBGA	(6 << 5)
#define ANAC_CMP_CFG_VINSEL_V1P5S	(7 << 5)

#define ANAC_CMP_CFG_VIPSEL_VC1P0  (0 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P1  (1 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P2  (2 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P3  (3 << 2)
#define ANAC_CMP_CFG_VIPSEL_VREF   (4 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBGS   (5 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBGA   (6 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBG4A  (7 << 2)

#define ANAC_CMP_CFG_HYSSEL_pos (8)
#define ANAC_CMP_CFG_VINSEL_pos (5)
#define ANAC_CMP_CFG_VIPSEL_pos (2)

/* ADC_CFG */
#define ANAC_ADC_CFG_SMP_TIME	   BITS(13, 14)
#define ANAC_ADC_CFG_SMP_CYCLE	   BITS(11, 12)
#define ANAC_ADC_CFG_ADC_CHSEL	   BITS(7, 10)
#define ANAC_ADC_CFG_ADC_BUFEN	   BIT(6)
#define ANAC_ADC_CFG_ADC_VRSEL	   BITS(4, 5)
#define ANAC_ADC_CFG_VOLTREF_VRSEL BITS(1, 3)
#define ANAC_ADC_CFG_VOLTREF_EN	   BIT(0)

#define ANAC_ADC_CFG_SMP_TIME_1	 (0 << 13)
#define ANAC_ADC_CFG_SMP_TIME_4	 (1 << 13)
#define ANAC_ADC_CFG_SMP_TIME_8	 (2 << 13)
#define ANAC_ADC_CFG_SMP_TIME_32 (3 << 13)

#define ANAC_ADC_CFG_SMP_CYCLE_16ADCCLK (0 << 11)
#define ANAC_ADC_CFG_SMP_CYCLE_12ADCCLK (1 << 11)
#define ANAC_ADC_CFG_SMP_CYCLE_8ADCCLK	(2 << 11)
#define ANAC_ADC_CFG_SMP_CYCLE_4ADCCLK	(3 << 11)

#define ANAC_ADC_CFG_ADC_CHSEL_AIN0		 (0 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN1		 (1 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN2		 (2 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN3		 (3 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN4		 (4 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN5		 (5 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN6		 (6 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN7		 (7 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN8		 (8 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_V1P5D	 (9 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_V1P5A	 (10 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_VBGA		 (11 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_PD_VO	 (12 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_VBGS		 (13 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_V1P5S	 (14 << 7)

#define ANAC_ADC_CFG_ADC_VRSEL_INT_VREF (0 << 4)
#define ANAC_ADC_CFG_ADC_VRSEL_EXT_VREF (1 << 4)
#define ANAC_ADC_CFG_ADC_VRSEL_VCC		(2 << 4)

#define ANAC_ADC_CFG_VOLTREF_VRSEL_1P2 (0 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_1P5 (1 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_2P0 (2 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_2P5 (3 << 1)

#define ANAC_ADC_CFG_SMP_TIME_pos	   (13)
#define ANAC_ADC_CFG_SMP_CYCLE_pos	   (11)
#define ANAC_ADC_CFG_ADC_CHSEL_pos	   (7)
#define ANAC_ADC_CFG_ADC_VRSEL_pos	   (4)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_pos (1)

/* ADC_CTL */
#define ANAC_ADC_CTL_SST		BIT(2)
#define ANAC_ADC_CTL_ADC_IE		BIT(1)
#define ANAC_ADC_CTL_ADC_EN		BIT(0)

/* ANAC_CFG */
#define ANAC_ANAC_CFG_INTF_ISOEN   BIT(16)
#define ANAC_ANAC_CFG_THERMD_EN	   BIT(15)
#define ANAC_ANAC_CFG_ALDO4A_VOSEL BITS(8, 9)
#define ANAC_ANAC_CFG_ALDO4A_EN	   BIT(7)
#define ANAC_ANAC_CFG_BGR_EN	   BIT(6)
#define ANAC_ANAC_CFG_ALDO4D_LPEN  BIT(3)
#define ANAC_ANAC_CFG_ALDO4D_EN	   BIT(2)
#define ANAC_ANAC_CFG_SLDO_VRSEL   BITS(0, 1)

#define ANAC_ANAC_CFG_ALDO4A_VOSEL_1P5	(0 << 8)
#define ANAC_ANAC_CFG_ALDO4A_VOSEL_1P55 (1 << 8)
#define ANAC_ANAC_CFG_ALDO4A_VOSEL_1P6	(2 << 8)
#define ANAC_ANAC_CFG_ALDO4A_VOSEL_1P7	(3 << 8)

#define ANAC_ANAC_CFG_SLDO_VRSEL_1P5 (0 << 0)
#define ANAC_ANAC_CFG_SLDO_VRSEL_1P2 (1 << 0)

#define ANAC_ANAC_CFG_ALDO4A_VOSEL_pos (8)
#define ANAC_ANAC_CFG_SLDO_VRSEL_pos   (0)

/* LVD_CFG */
#define ANAC_LVD_CFG_IBTRIM BITS(16, 17)
#define ANAC_LVD_CFG_FLT	BITS(8, 15)
#define ANAC_LVD_CFG_LVD_IE BIT(7)
#define ANAC_LVD_CFG_VTSEL	BITS(3, 6)
#define ANAC_LVD_CFG_SRCSEL BITS(1, 2)
#define ANAC_LVD_CFG_LVD_EN BIT(0)

#define ANAC_LVD_CFG_IBTRIM_30NA  (0 << 16)
#define ANAC_LVD_CFG_IBTRIM_120NA (1 << 16)
#define ANAC_LVD_CFG_IBTRIM_240NA (2 << 16)
#define ANAC_LVD_CFG_IBTRIM_480NA (3 << 16)

#define ANAC_LVD_CFG_FLT_NOT   (0 << 8)
#define ANAC_LVD_CFG_FLT_1T2   (1 << 8)
#define ANAC_LVD_CFG_FLT_2T3   (2 << 8)
#define ANAC_LVD_CFG_FLT_3T4   (3 << 8)
#define ANAC_LVD_CFG_FLT_4T5   (4 << 8)
#define ANAC_LVD_CFG_FLT_5T6   (5 << 8)
#define ANAC_LVD_CFG_FLT_6T7   (6 << 8)
#define ANAC_LVD_CFG_FLT_7T8   (7 << 8)
#define ANAC_LVD_CFG_FLT_8T9   (8 << 8)
#define ANAC_LVD_CFG_FLT_9T10  (9 << 8)
#define ANAC_LVD_CFG_FLT_10T11 (10 << 8)
#define ANAC_LVD_CFG_FLT_11T12 (11 << 8)
#define ANAC_LVD_CFG_FLT_12T13 (12 << 8)
#define ANAC_LVD_CFG_FLT_13T14 (13 << 8)
#define ANAC_LVD_CFG_FLT_14T15 (14 << 8)
#define ANAC_LVD_CFG_FLT_15T16 (15 << 8)

#define ANAC_LVD_CFG_VTSEL_1P9V	 (0 << 3)
#define ANAC_LVD_CFG_VTSEL_2P1V	 (1 << 3)
#define ANAC_LVD_CFG_VTSEL_2P2V	 (2 << 3)
#define ANAC_LVD_CFG_VTSEL_2P3V	 (3 << 3)
#define ANAC_LVD_CFG_VTSEL_2P4V	 (4 << 3)
#define ANAC_LVD_CFG_VTSEL_2P5V	 (5 << 3)
#define ANAC_LVD_CFG_VTSEL_2P65V (6 << 3)
#define ANAC_LVD_CFG_VTSEL_2P8V	 (7 << 3)
#define ANAC_LVD_CFG_VTSEL_2P9V	 (8 << 3)
#define ANAC_LVD_CFG_VTSEL_3P05V (9 << 3)
#define ANAC_LVD_CFG_VTSEL_3P2V	 (10 << 3)
#define ANAC_LVD_CFG_VTSEL_3P35V (11 << 3)
#define ANAC_LVD_CFG_VTSEL_3P5V	 (12 << 3)
#define ANAC_LVD_CFG_VTSEL_3P7V	 (13 << 3)
#define ANAC_LVD_CFG_VTSEL_4P3V	 (14 << 3)
#define ANAC_LVD_CFG_VTSEL_1P2V	 (15 << 3)

#define ANAC_LVD_CFG_SRCSEL_LOWPWR_VCC (0 << 1)
#define ANAC_LVD_CFG_SRCSEL_VCC		   (1 << 1)
#define ANAC_LVD_CFG_SRCSEL_LVDI0	   (2 << 1)
#define ANAC_LVD_CFG_SRCSEL_LVDI1	   (3 << 1)

#define ANAC_LVD_CFG_IBTRIM_pos (16)
#define ANAC_LVD_CFG_FLT_pos	(8)
#define ANAC_LVD_CFG_VTSEL_pos	(3)
#define ANAC_LVD_CFG_SRCSEL_pos (1)

/* CLK_CFG */
#define ANAC_CLK_CFG_MRC_EN		 BIT(15)
#define ANAC_CLK_CFG_HRC_FSEL	 BITS(2, 4)
#define ANAC_CLK_CFG_HRC_EN		 BIT(1)
#define ANAC_CLK_CFG_LRC_EN		 BIT(0)

#define ANAC_CLK_CFG_HRC_FSEL_1M  (1 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_2M  (2 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_4M  (3 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_8M  (4 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_16M (5 << 2)

#define ANAC_CLK_CFG_HRC_FSEL_pos  (2)

/* AINSEL */
#define ANAC_AINSEL_GPIO4_SEL  BIT(4)
#define ANAC_AINSEL_GPIO5_SEL  BIT(5)
#define ANAC_AINSEL_GPIO6_SEL  BIT(6)
#define ANAC_AINSEL_GPIO7_SEL  BIT(7)
#define ANAC_AINSEL_GPIO12_SEL BIT(12)
#define ANAC_AINSEL_GPIO13_SEL BIT(13)
#define ANAC_AINSEL_GPIO14_SEL BIT(14)
#define ANAC_AINSEL_GPIO15_SEL BIT(15)
#define ANAC_AINSEL_GPIO16_SEL BIT(16)
#define ANAC_AINSEL_GPIO17_SEL BIT(17)
#define ANAC_AINSEL_GPIO18_SEL BIT(18)
#define ANAC_AINSEL_GPIO19_SEL BIT(19)

#define ANAC_AINSEL_GPIO4_SEL_VC1P1	 (0 << 4)
#define ANAC_AINSEL_GPIO4_SEL_AIN02	 (1 << 4)
#define ANAC_AINSEL_GPIO5_SEL_LVDI1	 (0 << 5)
#define ANAC_AINSEL_GPIO5_SEL_AIN03	 (1 << 5)
#define ANAC_AINSEL_GPIO6_SEL_VC1N1	 (0 << 6)
#define ANAC_AINSEL_GPIO6_SEL_AIN01	 (1 << 6)
#define ANAC_AINSEL_GPIO7_SEL_AIN05	 (0 << 7)
#define ANAC_AINSEL_GPIO7_SEL_VC1P2	 (1 << 7)
#define ANAC_AINSEL_GPIO12_SEL_AIN07 (0 << 12)
#define ANAC_AINSEL_GPIO12_SEL_VC1O	 (1 << 12)
#define ANAC_AINSEL_GPIO13_SEL_VC1N0 (0 << 13)
#define ANAC_AINSEL_GPIO13_SEL_VREF	 (1 << 13)
#define ANAC_AINSEL_GPIO14_SEL_VREF	 (0 << 14)
#define ANAC_AINSEL_GPIO14_SEL_AIN04 (1 << 14)
#define ANAC_AINSEL_GPIO15_SEL_TRDRV (0 << 15)
#define ANAC_AINSEL_GPIO15_SEL_ATVC	 (1 << 15)
#define ANAC_AINSEL_GPIO16_SEL_VC1P3 (0 << 16)
#define ANAC_AINSEL_GPIO16_SEL_AIN08 (1 << 16)
#define ANAC_AINSEL_GPIO17_SEL_VC1P4 (0 << 17)
#define ANAC_AINSEL_GPIO17_SEL_AIN06 (1 << 17)
#define ANAC_AINSEL_GPIO18_SEL_VC1P0 (0 << 18)
#define ANAC_AINSEL_GPIO18_SEL_AIN00 (1 << 18)
#define ANAC_AINSEL_GPIO19_SEL_VC1N0 (0 << 19)
#define ANAC_AINSEL_GPIO19_SEL_LVDI0 (1 << 19)

/* DLY_CFG */
#define ANAC_DLY_CFG_CHRG_DLY		BITS(26, 27)
#define ANAC_DLY_CFG_LED_PW			BITS(18, 25)
#define ANAC_DLY_CFG_SMOKE_DLY		BITS(10, 17)
#define ANAC_DLY_CFG_PDSENS_RST_DLY BITS(8, 9)
#define ANAC_DLY_CFG_TEMP_DLY		BITS(6, 7)
#define ANAC_DLY_CFG_ADC_DLY		BITS(4, 5)
#define ANAC_DLY_CFG_ALDO4A_DLY		BITS(2, 3)
#define ANAC_DLY_CFG_BGR_DLY		BITS(0, 1)

#define ANAC_DLY_CFG_CHRG_DLY_500  (0 << 26)
#define ANAC_DLY_CFG_CHRG_DLY_1000 (1 << 26)
#define ANAC_DLY_CFG_CHRG_DLY_1500 (2 << 26)
#define ANAC_DLY_CFG_CHRG_DLY_2000 (3 << 26)

#define ANAC_DLY_CFG_PDSENS_RST_DLY_200 (0 << 8)
#define ANAC_DLY_CFG_PDSENS_RST_DLY_300 (1 << 8)
#define ANAC_DLY_CFG_PDSENS_RST_DLY_400 (2 << 8)
#define ANAC_DLY_CFG_PDSENS_RST_DLY_500 (3 << 8)

#define ANAC_DLY_CFG_TEMP_DLY_6	 (0 << 6)
#define ANAC_DLY_CFG_TEMP_DLY_12 (1 << 6)
#define ANAC_DLY_CFG_TEMP_DLY_24 (2 << 6)
#define ANAC_DLY_CFG_TEMP_DLY_48 (3 << 6)

#define ANAC_DLY_CFG_ADC_DLY_6	(0 << 4)
#define ANAC_DLY_CFG_ADC_DLY_12 (1 << 4)
#define ANAC_DLY_CFG_ADC_DLY_24 (2 << 4)
#define ANAC_DLY_CFG_ADC_DLY_48 (3 << 4)

#define ANAC_DLY_CFG_ALDO4A_DLY_12 (0 << 2)
#define ANAC_DLY_CFG_ALDO4A_DLY_24 (1 << 2)
#define ANAC_DLY_CFG_ALDO4A_DLY_48 (2 << 2)
#define ANAC_DLY_CFG_ALDO4A_DLY_96 (3 << 2)

#define ANAC_DLY_CFG_BGR_DLY_12 (0 << 0)
#define ANAC_DLY_CFG_BGR_DLY_24 (1 << 0)
#define ANAC_DLY_CFG_BGR_DLY_48 (2 << 0)
#define ANAC_DLY_CFG_BGR_DLY_96 (3 << 0)

#define ANAC_DLY_CFG_CHRG_DLY_pos		(26)
#define ANAC_DLY_CFG_LED_PW_pos			(18)
#define ANAC_DLY_CFG_SMOKE_DLY_pos		(10)
#define ANAC_DLY_CFG_PDSENS_RST_DLY_pos (8)
#define ANAC_DLY_CFG_TEMP_DLY_pos		(6)
#define ANAC_DLY_CFG_ADC_DLY_pos		(4)
#define ANAC_DLY_CFG_ALDO4A_DLY_pos		(2)
#define ANAC_DLY_CFG_BGR_DLY_pos		(0)

/* ME_CTL */
#define ANAC_ME_CTL_ADC_TRIG_SEL BITS(8, 10)
#define ANAC_ME_CTL_THRCMP_EN	 BIT(7)
#define ANAC_ME_CTL_MODE_SEL	 BITS(5, 6)
#define ANAC_ME_CTL_ME_AUTO		 BIT(4)
#define ANAC_ME_CTL_ME_MODE		 BIT(3)
#define ANAC_ME_CTL_THR_IE		 BIT(2)
#define ANAC_ME_CTL_ANAC_EN		 BIT(0)

#define ANAC_ME_CTL_ADC_TRIG_SEL_LPTINT	 (0 << 8)
#define ANAC_ME_CTL_ADC_TRIG_SEL_TIM1INT (1 << 8)
#define ANAC_ME_CTL_ADC_TRIG_SEL_TIM2INT (2 << 8)

#define ANAC_ME_CTL_MODE_SEL_AD_AUTO	   (0 << 5)
#define ANAC_ME_CTL_MODE_SEL_TP_AUTO	   (1 << 5)
#define ANAC_ME_CTL_MODE_SEL_DARK_CUR_AUTO (2 << 5)
#define ANAC_ME_CTL_MODE_SEL_SMOKE_AUTO	   (3 << 5)

#define ANAC_ME_CTL_ADC_TRIG_SEL_pos (8)
#define ANAC_ME_CTL_MODE_SEL_pos	 (5)

/* ANAC_FLAG */
#define ANAC_ANAC_FLAG_CMP_OUT	   BIT(10)
#define ANAC_ANAC_FLAG_LVD_OUT	   BIT(9)
#define ANAC_ANAC_FLAG_ANA_OK_INTF BIT(3)
#define ANAC_ANAC_FLAG_LVD_INTF	   BIT(2)
#define ANAC_ANAC_FLAG_THR_INTF	   BIT(1)
#define ANAC_ANAC_FLAG_ADC_INTF	   BIT(0)

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
  * @brief ADC Init structure definition
  */

typedef struct
{
	u8 ADC_Channel; 						/*!< Specify ADC input channel.
											 	 This parameter can be a value of @ref ADC_channels. */

	u8 ADC_VrefSel; 						/*!< Specify the ADC reference voltage input source.
											 	 This parameter can be a value of @ref ADC_vref_selection. */

	u8 ADC_VrefVol; 						/*!< Specify the internal reference voltage VREF scale.
												 This parameter can be a value of @ref ADC_vref_voltage. */

	FunctionalState ADC_BuffCmd; 			/*!< Specifies the new state of the ADC amplifier.
												 This parameter can be set to ENABLE or DISABLE. */

	u8 ADC_SmpTimes; 						/*!< Specify ADC hardware sampling times.
											  	 This parameter can be a value of @ref ADC_sample_times. */

	u8 ADC_SmpCycle; 						/*!< Specify ADC input signal sample and hold time.
											 	 This parameter can be a value of @ref ADC_sample_cycle. */
} ADC_InitTypeDef;

/**
  * @brief LVD Init structure definition
  */

typedef struct
{
	u8 LVD_BiasCurrentTrim; 				/*!< Specifies the LVD comparator bias current trim. 
												 This parameter can be a value of @ref LVD_Bias_Current_Trim. */

	u8 LVD_FilterTime; 						/*!< Specify low voltage detection LVD_OUT filter time.
												 This parameter must range from 0 to 15. */

	u8 LVD_ThresholdVoltage; 				/*!< Specify the LVD threshold voltage.
												 This parameter can be a value of @ref LVD_threshold_voltage. */

	u8 LVD_MonitoSource; 					/*!< Specify the LVD monitor source.
												 This parameter can be a value of @ref LVD_monitor_source. */
} LVD_InitTypeDef;

/**
  * @brief ADC conversion result register number enumeration
  */

typedef enum
{
	ADC_VAL_NO0 = 0,
	ADC_VAL_NO1,
	ADC_VAL_NO2,
	ADC_VAL_NO3,
	ADC_VAL_NO4,
	ADC_VAL_NO5,
	ADC_VAL_NO6,
	ADC_VAL_NO7
} ADC_ValNo;

#define IS_ADC_RESULTNO(RESULTNO) (((RESULTNO) >= ADC_VAL_NO0) && ((RESULTNO) <= ADC_VAL_NO7))

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

#define ANAC_WPROT_V0 (0x5A5A)
#define ANAC_WPROT_V1 (0xA5A5)
#define ANAC_WPT_UNLOCK()                                                                                              \
	{                                                                                                                  \
		ANAC->WPROT = ANAC_WPROT_V0;                                                                                   \
		ANAC->WPROT = ANAC_WPROT_V1;                                                                                   \
	}
/**
  * @}
  */

/** @defgroup ANAC_ALDO4A_output_voltage
  * @{
  */

#define ANAC_ALDO4A_VOSEL_1P5V	(0)
#define ANAC_ALDO4A_VOSEL_1P55V (1)
#define ANAC_ALDO4A_VOSEL_1P6V	(2)
#define ANAC_ALDO4A_VOSEL_1P7V	(3)

#define IS_ANAC_ALDO4A_VOSEL(VOSEL)                                                                                    \
	((VOSEL) == ANAC_ALDO4A_VOSEL_1P5V || (VOSEL) == ANAC_ALDO4A_VOSEL_1P55V || (VOSEL) == ANAC_ALDO4A_VOSEL_1P6V ||   \
	 (VOSEL) == ANAC_ALDO4A_VOSEL_1P7V)
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

/** @defgroup LED_infrared_tube_select
  * @{
  */

#define LED_SEL_IIRLED (0)
#define LED_SEL_IBULE  (1)

#define IS_LED_ISEL(ISEL) ((ISEL) == LED_SEL_IIRLED || (ISEL) == LED_SEL_IBULE)
/**
  * @}
  */

/** @defgroup LED_current_value
  * @{
  */

#define IS_LED_CURRENTVAL(CURRENTVAL) ((CURRENTVAL) <= 0x1F)
/**
  * @}
  */

/** @defgroup PDSENS_gain_value
  * @{
  */

#define IS_PDSENS_GAINVAL(GAINVAL) ((GAINVAL) <= 0x1F)
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

#define CMP_VIN_SEL_VC1N0	(0)
#define CMP_VIN_SEL_VC1N1	(1)
#define CMP_VIN_SEL_VC1N2	(2)
#define CMP_VIN_SEL_VREF	(3)
#define CMP_VIN_SEL_VREF_VO	(4)
#define CMP_VIN_SEL_VBGS	(5)
#define CMP_VIN_SEL_VBGA	(6)
#define CMP_VIN_SEL_V1P5S	(7)

#define IS_CMP_VINSEL(VINSEL)                                                                                          \
	((VINSEL) == CMP_VIN_SEL_VC1N0 || (VINSEL) == CMP_VIN_SEL_VC1N1 || (VINSEL) == CMP_VIN_SEL_VC1N2 ||                \
	 (VINSEL) == CMP_VIN_SEL_VREF || (VINSEL) == CMP_VIN_SEL_VREF_VO || (VINSEL) == CMP_VIN_SEL_VBGS ||                \
	 (VINSEL) == CMP_VIN_SEL_VBGA || (VINSEL) == CMP_VIN_SEL_V1P5S)
/**
  * @}
  */

/** @defgroup CMP_positive_input_signal_selection
  * @{
  */

#define CMP_VIP_SEL_VC1P0  (0)
#define CMP_VIP_SEL_VC1P1  (1)
#define CMP_VIP_SEL_VC1P2  (2)
#define CMP_VIP_SEL_VC1P3  (3)
#define CMP_VIP_SEL_VREF   (4)
#define CMP_VIP_SEL_VBGS   (5)
#define CMP_VIP_SEL_VBGA   (6)
#define CMP_VIP_SEL_VBG4A  (7)

#define IS_CMP_VIPSEL(VIPSEL)                                                                                          \
	((VIPSEL) == CMP_VIP_SEL_VC1P0 || (VIPSEL) == CMP_VIP_SEL_VC1P1 || (VIPSEL) == CMP_VIP_SEL_VC1P2 ||                \
	 (VIPSEL) == CMP_VIP_SEL_VC1P3 || (VIPSEL) == CMP_VIP_SEL_VREF || (VIPSEL) == CMP_VIP_SEL_VBGS ||                  \
	 (VIPSEL) == CMP_VIP_SEL_VBGA || (VIPSEL) == CMP_VIP_SEL_VBG4A)
/**
  * @}
  */

/** @defgroup ADC_channels
  * @{
  */

#define ADC_CHN_AIN0	  (0)
#define ADC_CHN_AIN1	  (1)
#define ADC_CHN_AIN2	  (2)
#define ADC_CHN_AIN3	  (3)
#define ADC_CHN_AIN4	  (4)
#define ADC_CHN_AIN5	  (5)
#define ADC_CHN_AIN6	  (6)
#define ADC_CHN_AIN7	  (7)
#define ADC_CHN_AIN8	  (8)
#define ADC_CHN_V1P5D	  (9)
#define ADC_CHN_V1P5A	  (10)
#define ADC_CHN_VBGA	  (11)
#define ADC_CHN_PD_VO	  (12)
#define ADC_CHN_VBGS	  (13)
#define ADC_CHN_V1P5S	  (14)

#define IS_ADC_CHANNEL(CHANNEL)                                                                                        \
	(((CHANNEL) == ADC_CHN_AIN0) || ((CHANNEL) == ADC_CHN_AIN1) || ((CHANNEL) == ADC_CHN_AIN2) ||                      \
	 ((CHANNEL) == ADC_CHN_AIN3) || ((CHANNEL) == ADC_CHN_AIN4) || ((CHANNEL) == ADC_CHN_AIN5) ||                      \
	 ((CHANNEL) == ADC_CHN_AIN6) || ((CHANNEL) == ADC_CHN_AIN7) || ((CHANNEL) == ADC_CHN_AIN8) ||                      \
	 ((CHANNEL) == ADC_CHN_V1P5D) || ((CHANNEL) == ADC_CHN_V1P5A) || ((CHANNEL) == ADC_CHN_VBGA) ||                    \
	 ((CHANNEL) == ADC_CHN_PD_VO) || ((CHANNEL) == ADC_CHN_VBGS) || ((CHANNEL) == ADC_CHN_V1P5S))
/**
  * @}
  */

/** @defgroup ADC_vref_selection
  * @{
  */

#define ADC_VREF_SEL_INT (0)
#define ADC_VREF_SEL_EXT (1)
#define ADC_VREF_SEL_VCC (2)

#define IS_ADC_VREFSEL(VREFSEL)                                                                                        \
	(((VREFSEL) == ADC_VREF_SEL_INT) || ((VREFSEL) == ADC_VREF_SEL_EXT) || ((VREFSEL) == ADC_VREF_SEL_VCC))
/**
  * @}
  */

/** @defgroup ADC_vref_voltage
  * @{
  */

#define ADC_VREF_VOLT_1P2 (0)
#define ADC_VREF_VOLT_1P5 (1)
#define ADC_VREF_VOLT_2P0 (2)
#define ADC_VREF_VOLT_2P5 (3)

#define IS_ADC_VREFVOL(VREFVOL)                                                                                        \
	(((VREFVOL) == ADC_VREF_VOLT_1P2) || ((VREFVOL) == ADC_VREF_VOLT_1P5) || ((VREFVOL) == ADC_VREF_VOLT_2P0) ||       \
	 ((VREFVOL) == ADC_VREF_VOLT_2P5))
/**
  * @}
  */

/** @defgroup ADC_sample_times
  * @{
  */

#define ADC_SMP_TIMS_1  (0)
#define ADC_SMP_TIMS_4  (1)
#define ADC_SMP_TIMS_8  (2)
#define ADC_SMP_TIMS_32 (3)

#define IS_ADC_SMPTIMS(SMPTIMS)                                                                                        \
	(((SMPTIMS) == ADC_SMP_TIMS_1) || ((SMPTIMS) == ADC_SMP_TIMS_4) || ((SMPTIMS) == ADC_SMP_TIMS_8) ||                \
	 ((SMPTIMS) == ADC_SMP_TIMS_32))
/**
  * @}
  */

/** @defgroup ADC_sample_cycle
  * @{
  */

#define ADC_SMP_CYCLE_16 (0)
#define ADC_SMP_CYCLE_12 (1)
#define ADC_SMP_CYCLE_8	 (2)
#define ADC_SMP_CYCLE_4	 (3)

#define IS_ADC_SMPCYCLE(SMPCYCLE)                                                                                      \
	(((SMPCYCLE) == ADC_SMP_CYCLE_16) || ((SMPCYCLE) == ADC_SMP_CYCLE_12) || ((SMPCYCLE) == ADC_SMP_CYCLE_8) ||        \
	 ((SMPCYCLE) == ADC_SMP_CYCLE_4))
/**
  * @}
  */

/** @defgroup LVD_Bias_Current_Trim
  * @{
  */

#define LVD_BIAS_CURRENT_TRIM_30NA	(0)
#define LVD_BIAS_CURRENT_TRIM_120NA (1)
#define LVD_BIAS_CURRENT_TRIM_240NA (2)
#define LVD_BIAS_CURRENT_TRIM_480NA (3)

#define IS_LVD_BIAS_CURRENT_TRIM(IBTRIM)                                                                               \
	(((IBTRIM) == LVD_BIAS_CURRENT_TRIM_30NA) || ((IBTRIM) == LVD_BIAS_CURRENT_TRIM_120NA) ||                          \
	 ((IBTRIM) == LVD_BIAS_CURRENT_TRIM_240NA) || ((IBTRIM) == LVD_BIAS_CURRENT_TRIM_480NA))
/**
  * @}
  */

/** @defgroup LVD_filter_time
  * @{
  */

#define IS_LVD_FILTER_TIME(TIME) ((TIME) <= 0x0F)
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
#define LVD_MONITOR_SOURCE_VCC	 (1)
#define LVD_MONITOR_SOURCE_LVDI0 (2)
#define LVD_MONITOR_SOURCE_LVDI1 (3)

#define IS_LVD_MONITOR_SOURCE(SOURCE)                                                                                  \
	(((SOURCE) == LVD_MONITOR_SOURCE_LPVCC) || ((SOURCE) == LVD_MONITOR_SOURCE_VCC) ||                                 \
	 ((SOURCE) == LVD_MONITOR_SOURCE_LVDI0) || ((SOURCE) == LVD_MONITOR_SOURCE_LVDI1))
/**
  * @}
  */

/** @defgroup CLK_HRC_frequency_selection
  * @{
  */

#define CLK_HRC_FREQ_SEL_1M	 (1)
#define CLK_HRC_FREQ_SEL_2M	 (2)
#define CLK_HRC_FREQ_SEL_4M	 (3)
#define CLK_HRC_FREQ_SEL_8M	 (4)
#define CLK_HRC_FREQ_SEL_16M (5)

#define IS_CLK_HRC_FREQSEL(FREQSEL)                                                                                    \
	(((FREQSEL) == CLK_HRC_FREQ_SEL_1M) || ((FREQSEL) == CLK_HRC_FREQ_SEL_2M) || ((FREQSEL) == CLK_HRC_FREQ_SEL_4M) || \
	 ((FREQSEL) == CLK_HRC_FREQ_SEL_16M))
/**
  * @}
  */

/** @defgroup AINSEL_Multiplex_function_selection
  * @{
  */

#define AINSEL_MULTIPLEX_P04_SEL_VC1P1	 (8)
#define AINSEL_MULTIPLEX_P04_SEL_AIN02	 (9)
#define AINSEL_MULTIPLEX_P05_SEL_LVDI1	 (10)
#define AINSEL_MULTIPLEX_P05_SEL_AIN03	 (11)
#define AINSEL_MULTIPLEX_P06_SEL_VC1N1	 (12)
#define AINSEL_MULTIPLEX_P06_SEL_AIN01	 (13)
#define AINSEL_MULTIPLEX_P07_SEL_AIN05	 (14)
#define AINSEL_MULTIPLEX_P07_SEL_VC1P2	 (15)
#define AINSEL_MULTIPLEX_P12_SEL_AIN07   (24)
#define AINSEL_MULTIPLEX_P12_SEL_VC1O	 (25)
#define AINSEL_MULTIPLEX_P13_SEL_VC1N0   (26)
#define AINSEL_MULTIPLEX_P13_SEL_VREF	 (27)
#define AINSEL_MULTIPLEX_P14_SEL_VREF	 (28)
#define AINSEL_MULTIPLEX_P14_SEL_AIN04	 (29)
#define AINSEL_MULTIPLEX_P15_SEL_TRDRV	 (30)
#define AINSEL_MULTIPLEX_P15_SEL_ATVC	 (31)
#define AINSEL_MULTIPLEX_P16_SEL_VC1P3	 (32)
#define AINSEL_MULTIPLEX_P16_SEL_AIN08	 (33)
#define AINSEL_MULTIPLEX_P17_SEL_VC1P4	 (34)
#define AINSEL_MULTIPLEX_P17_SEL_AIN06	 (35)
#define AINSEL_MULTIPLEX_P18_SEL_VC1P0	 (36)
#define AINSEL_MULTIPLEX_P18_SEL_AIN00	 (37)
#define AINSEL_MULTIPLEX_P19_SEL_VC1N0	 (38)
#define AINSEL_MULTIPLEX_P19_SEL_LVDI0	 (39)

#define IS_AINSEL_MULTIPLEXSEL(MULTIPLEXSEL)                                                                           \
	(((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P04_SEL_VC1P1) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P04_SEL_AIN02) ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P05_SEL_LVDI1) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P05_SEL_AIN03) ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P06_SEL_VC1N1) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P06_SEL_AIN01) ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P07_SEL_AIN05) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P07_SEL_VC1P2) ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P12_SEL_AIN07) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P12_SEL_VC1O)  ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P13_SEL_VC1N0) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P13_SEL_VREF)  ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P14_SEL_VREF)  || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P14_SEL_AIN04) ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P15_SEL_TRDRV) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P15_SEL_ATVC)  ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P16_SEL_VC1P3) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P16_SEL_AIN08) ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P17_SEL_VC1P4) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P17_SEL_AIN06) ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P18_SEL_VC1P0) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P18_SEL_AIN00) ||       \
	 ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P19_SEL_VC1N0) || ((MULTIPLEXSEL) == AINSEL_MULTIPLEX_P19_SEL_LVDI0))
/**
  * @}
  */

/** @defgroup DLY_PD_charge_time
  * @{
  */

#define DLY_PD_CHRG_DLY_500  (0)
#define DLY_PD_CHRG_DLY_1000 (1)
#define DLY_PD_CHRG_DLY_1500 (2)
#define DLY_PD_CHRG_DLY_2000 (3)

#define IS_DLY_PDCHRGDLY(PDCHRGDLY)                                                                                      \
	(((PDCHRGDLY) == DLY_PD_CHRG_DLY_500) || ((PDCHRGDLY) == DLY_PD_CHRG_DLY_1000) ||  									\
	 ((PDCHRGDLY) == DLY_PD_CHRG_DLY_1500) ||((PDCHRGDLY) == DLY_PD_CHRG_DLY_2000))
/**
  * @}
  */

/** @defgroup DLY_PD_reset_delay_time
  * @{
  */

#define DLY_PD_RST_DLY_200 (0)
#define DLY_PD_RST_DLY_300 (1)
#define DLY_PD_RST_DLY_400 (2)
#define DLY_PD_RST_DLY_500 (3)

#define IS_DLY_PDRSTDLY(PDRSTDLY)                                                                                      \
	(((PDRSTDLY) == DLY_PD_RST_DLY_200) || ((PDRSTDLY) == DLY_PD_RST_DLY_300) || ((PDRSTDLY) == DLY_PD_RST_DLY_400) || \
	 ((PDRSTDLY) == DLY_PD_RST_DLY_500))
/**
  * @}
  */

/** @defgroup DLY_temp_delay_time
  * @{
  */

#define DLY_TEMP_DLY_6	(0)
#define DLY_TEMP_DLY_12 (1)
#define DLY_TEMP_DLY_24 (2)
#define DLY_TEMP_DLY_48 (3)

#define IS_DLY_TEMPDLY(TEMPDLY)                                                                                        \
	(((TEMPDLY) == DLY_TEMP_DLY_6) || ((TEMPDLY) == DLY_TEMP_DLY_12) || ((TEMPDLY) == DLY_TEMP_DLY_24) ||              \
	 ((TEMPDLY) == DLY_TEMP_DLY_48))
/**
  * @}
  */

/** @defgroup DLY_adc_delay_time
  * @{
  */

#define DLY_ADC_DLY_6  (0)
#define DLY_ADC_DLY_12 (1)
#define DLY_ADC_DLY_24 (2)
#define DLY_ADC_DLY_48 (3)

#define IS_DLY_ADCDLY(ADCDLY)                                                                                          \
	(((ADCDLY) == DLY_ADC_DLY_6) || ((ADCDLY) == DLY_ADC_DLY_12) || ((ADCDLY) == DLY_ADC_DLY_24) ||                    \
	 ((ADCDLY) == DLY_ADC_DLY_48))
/**
  * @}
  */

/** @defgroup DLY_aldo4a_delay_time
  * @{
  */

#define DLY_ALDO4A_DLY_12 (0)
#define DLY_ALDO4A_DLY_24 (1)
#define DLY_ALDO4A_DLY_48 (2)
#define DLY_ALDO4A_DLY_96 (3)

#define IS_DLY_ALDO4ADLY(ALDO4ADLY)                                                                                    \
	(((ALDO4ADLY) == DLY_ALDO4A_DLY_12) || ((ALDO4ADLY) == DLY_ALDO4A_DLY_24) || ((ALDO4ADLY) == DLY_ALDO4A_DLY_48) || \
	 ((ALDO4ADLY) == DLY_ALDO4A_DLY_96))
/**
  * @}
  */

/** @defgroup DLY_BGR_delay_time
  * @{
  */

#define DLY_BGR_DLY_12 (0)
#define DLY_BGR_DLY_24 (1)
#define DLY_BGR_DLY_48 (2)
#define DLY_BGR_DLY_96 (3)

#define IS_DLY_BGRDLY(BGRDLY)                                                                                          \
	(((BGRDLY) == DLY_BGR_DLY_12) || ((BGRDLY) == DLY_BGR_DLY_24) || ((BGRDLY) == DLY_BGR_DLY_48) ||                   \
	 ((BGRDLY) == DLY_BGR_DLY_96))
/**
  * @}
  */

/** @defgroup ME_ADC_interrupt_source_selection
  * @{
  */

#define ME_INT_SRC_LPT	(0)
#define ME_INT_SRC_TIM1 (1)
#define ME_INT_SRC_TIM2 (2)

#define IS_ME_INTSRC(INTSRC)                                                                                           \
	(((INTSRC) == ME_INT_SRC_LPT) || ((INTSRC) == ME_INT_SRC_TIM1) || ((INTSRC) == ME_INT_SRC_TIM2))
/**
  * @}
  */

/** @defgroup ME_Automatic_measurement_mode
  * @{
  */

#define ME_AUTO_MODE_GENERRAL	 (0)
#define ME_AUTO_MODE_TEMP		 (1)
#define ME_AUTO_MODE_DARKCURRENT (2)
#define ME_AUTO_MODE_SMOKE		 (3)

#define IS_ME_AUTOMODE(AUTOMODE)                                                                                       \
	(((AUTOMODE) == ME_AUTO_MODE_GENERRAL) || ((AUTOMODE) == ME_AUTO_MODE_TEMP) ||                                     \
	 ((AUTOMODE) == ME_AUTO_MODE_DARKCURRENT) || ((AUTOMODE) == ME_AUTO_MODE_SMOKE))
/**
  * @}
  */

/** @defgroup ME_Trigger_ADC_conversion_source
  * @{
  */

#define ME_TRIGGER_SRC_SST (0)
#define ME_TRIGGER_SRC_INT (1)

#define IS_ME_TRIGGERSRC(TRIGGERSRC) (((TRIGGERSRC) == ME_TRIGGER_SRC_SST) || ((TRIGGERSRC) == ME_TRIGGER_SRC_INT))
/**
  * @}
  */

/** @defgroup THR_limit_value
  * @{
  */

#define IS_THR_LIMITVAL(LIMITVAL) ((LIMITVAL) <= 0xFFF)
/**
  * @}
  */

/** @defgroup ANAC_flags_definition
  * @{
  */

#define ANAC_FLAG_CMP_OUT	  BIT(10)
#define ANAC_FLAG_LVD_OUT	  BIT(9)
#define ANAC_FLAG_ANA_OK_INTF BIT(3)
#define ANAC_FLAG_LVD_INTF	  BIT(2)
#define ANAC_FLAG_THR_INTF	  BIT(1)
#define ANAC_FLAG_ADC_INTF	  BIT(0)

#define ANAC_FLAG_ALL (ANAC_FLAG_ANA_OK_INTF | ANAC_FLAG_LVD_INTF | ANAC_FLAG_THR_INTF | ANAC_FLAG_ADC_INTF)

#define IS_ANAC_GET_FLAG(FLAG)                                                                                         \
	(((FLAG) == ANAC_FLAG_CMP_OUT) || ((FLAG) == ANAC_FLAG_LVD_OUT) || ((FLAG) == ANAC_FLAG_ANA_OK_INTF) ||           \
	 ((FLAG) == ANAC_FLAG_LVD_INTF) || ((FLAG) == ANAC_FLAG_THR_INTF) || ((FLAG) == ANAC_FLAG_ADC_INTF))

#define IS_ANAC_CLEAR_FLAG(FLAG) (((FLAG) & ANAC_FLAG_ALL) && (!((FLAG) & (~(ANAC_FLAG_ALL)))))
/**
  * @}
  */

/** @defgroup ANAC_interrupts_definition
  * @{
  */

#define ANAC_IT_LVD_INTF BIT(2)
#define ANAC_IT_THR_INTF BIT(1)
#define ANAC_IT_ADC_INTF BIT(0)

#define IS_ANAC_GET_IT(IT) (((IT) == ANAC_IT_LVD_INTF) || ((IT) == ANAC_IT_THR_INTF) || ((IT) == ANAC_IT_ADC_INTF))
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
void	   ANAC_Aldo4aVoltageConfig(u8 OutputVol);
void	   ANAC_SleepLDOVoltageConfig(u8 OutputVol);
void	   ANAC_InterfaceIsolationCmd(FunctionalState NewState);
void	   ANAC_ThermistorDriveCmd(FunctionalState NewState);
void	   ANAC_ActiveLDO4AnalogCmd(FunctionalState NewState);
void	   ANAC_ReferenceVoltageCmd(FunctionalState NewState);
void	   ANAC_Aldo4dShortSldoCmd(FunctionalState NewState);
void	   ANAC_ActiveLDO4DigitalCmd(FunctionalState NewState);
void	   LED_DriveCurrentConfig(u8 LED_Sel, u8 CurrentVal);
void	   LED_SetAutoInfraredTube(u8 LED_Sel);
void	   LED_InfraredTubeCmd(u8 LED_Sel, FunctionalState NewState);
void	   PDSENS_GainConfig(u8 GainVal);
void	   PDSENS_CapacitorChargeCmd(FunctionalState NewState);
void	   PDSENS_ResetCmd(FunctionalState NewState);
void	   PDSENS_Cmd(FunctionalState NewState);
void	   CMP_Init(CMP_InitTypeDef *CMP_InitStruct);
void	   CMP_Cmd(FunctionalState NewState);
void	   ADC_Init(ADC_InitTypeDef *ADC_InitStruct);
u32		   ADC_GetSingleResultValue(ADC_ValNo ValNo);
u32		   ADC_GetAverageValue(void);
void	   ADC_SoftwareStartConvCmd(FunctionalState NewState);
void	   ADC_Cmd(FunctionalState NewState);
void	   ADC_ITConfig(FunctionalState NewState);
void	   LVD_Init(LVD_InitTypeDef *LVD_InitStruct);
void	   LVD_Cmd(FunctionalState NewState);
void	   LVD_ITConfig(FunctionalState NewState);
void	   CLK_HRCFrequencyConfig(u8 FreqSel);
void	   CLK_MRCClockCmd(FunctionalState NewState);
void	   CLK_HRCClockCmd(FunctionalState NewState);
void	   CLK_LRCClockCmd(FunctionalState NewState);
void	   AINSEL_MultiplexConfig(u8 MultiplexSel);
void	   DLY_PDChargeDelayConfig(u8 ChargeDelayTime);
void	   DLY_LEDOpenWidthConfig(u8 OpenWidth);
void	   DLY_SmokeDelayConfig(u8 SmokeDelayTime);
void	   DLY_PDRestDelayConfig(u8 PDRestDelayTime);
void	   DLY_TempDelayConfig(u8 TempDelayTime);
void	   DLY_ADCDelayConfig(u8 ADCDelayTime);
void	   DLY_ALDO4ADelayConfig(u8 ALDO4ADelayTime);
void	   DLY_BGRDelayConfig(u8 BGRDelayTime);
void	   ME_ADCIntSourceConfig(u8 ADCIntSource);
void	   ME_AutoModeConfig(u8 AutoMode);
void	   ME_SetTriggerSource(u8 TriggerSource);
void	   ME_ThresholdCompareCmd(FunctionalState NewState);
void	   ME_AutoMeasureCmd(FunctionalState NewState);
void	   ME_Cmd(FunctionalState NewState);
void	   ME_ITConfig(FunctionalState NewState);
void	   THR_ValueConfig(u16 LowerLimit, u16 UpperLimit);
FlagStatus ANAC_GetFlagStatus(u16 ANAC_FLAG);
ITStatus   ANAC_GetITStatus(u8 ANAC_IT);
void	   ANAC_ClearFlag(u16 ANAC_FLAG);

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

