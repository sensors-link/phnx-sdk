/**
 * @file anac.h
 * @author wyd
 * @brief
 * @version 0.1
 * @date 2021-07-16
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __ANAC_H__
#define __ANAC_H__
#include "phnx04.h"

// register bits definitions
// led_cfg
#define ANAC_LED_CFG_LED_SEL	  BIT(13)
#define ANAC_LED_CFG_LED_SEL_IR	  (0 << 13)
#define ANAC_LED_CFG_LED_SEL_BLUE (1 << 13)

#define ANAC_LED_CFG_IBULE_CC  BITS(7, 11)
#define ANAC_LED_CFG_IBLUE_EN  BIT(6)
#define ANAC_LED_CFG_IIRLED_CC BITS(1, 5)
#define ANAC_LED_CFG_IIRLED_EN BIT(0)

#define ANAC_LED_CFG_IBULE_CC_pos  (7) // 0-0x1f:0-310mA step:10mA
#define ANAC_LED_CFG_IIRLED_CC_pos (1)

// pdsens_cfg
#define ANAC_PDSENS_CFG_CHRG	BIT(7)
#define ANAC_PDSENS_CFG_GC		BITS(2, 6)
#define ANAC_PDSENS_CFG_GC_X50	(0 << 6)
#define ANAC_PDSENS_CFG_GC_X100 (1 << 6)

#define ANAC_PDSENS_CFG_GC_DB	  BIT(2, 5)
#define ANAC_PDSENS_CFG_GC_DB_pos (2) // 0-16 (x+1)dB

#define ANAC_PDSENS_CFG_RST BIT(1)
#define ANAC_PDSENS_CFG_EN	BIT(0)

// cmp_cfg
#define ANAC_CMP_CFG_HYSSEL BITS(8, 9)
#define ANAC_CMP_CFG_VINSEL BITS(5, 7)
#define ANAC_CMP_CFG_VIPSEL BITS(2, 4)
#define ANAC_CMP_CFG_INV	BIT(1)
#define ANAC_CMP_CFG_EN		BIT(0)

#define ANAC_CMP_CFG_HYSSEL_50MV (3 << 8)
#define ANAC_CMP_CFG_HYSSEL_25MV (2 << 8)
#define ANAC_CMP_CFG_HYSSEL_12MV (1 << 8)
#define ANAC_CMP_CFG_HYSSEL_0MV	 (0 << 8)

#define ANAC_CMP_CFG_VINSEL_V1P5S  (7 << 5)
#define ANAC_CMP_CFG_VINSEL_VBGA   (6 << 5)
#define ANAC_CMP_CFG_VINSEL_VBGS   (5 << 5)
#define ANAC_CMP_CFG_VINSEL_VREFVO (4 << 5)
#define ANAC_CMP_CFG_VINSEL_VREF   (3 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N2  (2 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N1  (1 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N0  (0 << 5)

#define ANAC_CMP_CFG_VIPSEL_BBG4A (7 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBGA  (6 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBGS  (5 << 2)
#define ANAC_CMP_CFG_VIPSEL_VREF  (4 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P3 (3 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P2 (2 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P1 (1 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P0 (0 << 2)

// adc_cfg
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

#define ANAC_ADC_CFG_ADC_CHSEL_V1P5S (0x0e << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_VBGS	 (0x0d << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_PD_VO (0x0c << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_VBGA	 (0x0b << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_V1P5A (0x0a << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_V1P5D (0x09 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN8	 (0x08 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN7	 (0x07 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN6	 (0x06 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN5	 (0x05 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN4	 (0x04 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN3	 (0x03 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN2	 (0x02 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN1	 (0x01 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN0	 (0x00 << 7)

#define ANAC_ADC_CFG_ADC_VRSEL_INT_VREF (0 << 4)
#define ANAC_ADC_CFG_ADC_VRSEL_EXT_VREF (1 << 4)
#define ANAC_ADC_CFG_ADC_VRSEL_VCC		(2 << 4)

#define ANAC_ADC_CFG_VOLTREF_VRSEL_1P2 (0 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_1P5 (1 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_2P0 (2 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_2P5 (3 << 1)

// adc_ctl
#define ANAC_ADC_CTL_SST	BIT(2)
#define ANAC_ADC_CTL_ADC_IE BIT(1)
#define ANAC_ADC_CTL_ADC_EN BIT(0)

// anac_cfg
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

// lvd_cfg
#define ANAC_LVD_CFG_IBTRIM BITS(16, 17)
#define ANAC_LVD_CFG_FLT	BITS(8, 15)
#define ANAC_LVD_CFG_IE		BIT(7)
#define ANAC_LVD_CFG_VTSEL	BITS(3, 6)
#define ANAC_LVD_CFG_SRCSEL BITS(1, 2)
#define ANAC_LVD_CFG_EN		BIT(0)

#define ANAC_LVD_CFG_IBTRIM_pos (16)
#define ANAC_LVD_CFG_FLT_pos	(8)
#define ANAC_LVD_CFG_VTSEL_pos	(3)

#define ANAC_LVD_CFG_SRCSEL_LOWPWR_VCC (0 << 1)
#define ANAC_LVD_CFG_SRCSEL_VCC		   (1 << 1)
#define ANAC_LVD_CFG_SRCSEL_LVDI0	   (2 << 1)
#define ANAC_LVD_CFG_SRCSEL_LVDI1	   (3 << 1)

// clk_cfg
#define ANAC_CLK_CFG_MRC_EN	  BIT(15)
#define ANAC_CLK_CFG_HRC_FSEL BITS(2, 4)
#define ANAC_CLK_CFG_HRC_EN	  BIT(1)
#define ANAC_CLK_CFG_LRC_EN	  BIT(0)

#define ANAC_CLK_CFG_HRC_FSEL_1M  (1 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_2M  (2 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_4M  (3 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_8M  (4 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_16M (5 << 2)

// ANAC_AINSEL
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

// dly_cfg
#define ANAC_DLY_CFG_CHRG_DLY		BITS(26, 27)
#define ANAC_DLY_CFG_LED_PW			BITS(18, 25)
#define ANAC_DLY_CFG_SMOKE_DLY		BITS(10, 17)
#define ANAC_DLY_CFG_PDSENS_RST_DLY BIT(8, 9)
#define ANAC_DLY_CFG_TEMP_DLY		BIT(6, 7)
#define ANAC_DLY_CFG_ADC_DLY		BIT(4, 5)
#define ANAC_DLY_CFG_ALDO4A_DLY		BIT(2, 3)
#define ANAC_DLY_CFG_BGR_DLY		BIT(0, 1)

#define ANAC_DLY_CFG_CHRG_DLY_pos		(26)
#define ANAC_DLY_CFG_LED_PW_pos			(18)
#define ANAC_DLY_CFG_SMOKE_DLY_pos		(10)
#define ANAC_DLY_CFG_PDSENS_RST_DLY_pos (8)
#define ANAC_DLY_CFG_TEMP_DLY_pos		(6)
#define ANAC_DLY_CFG_ADC_DLY_pos		(4)
#define ANAC_DLY_CFG_ALDO4A_DLY_pos		(2)
#define ANAC_DLY_CFG_BGR_DLY_pos		(0)

// me_ctl
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

// anac_flag
#define ANAC_ANAC_FLAG_CMP_OUT	   BIT(10)
#define ANAC_ANAC_FLAG_LVD_OUT	   BIT(9)
#define ANAC_ANAC_FLAG_ANA_OK_INTF BIT(3)
#define ANAC_ANAC_FLAG_LVD_INTF	   BIT(2)
#define ANAC_ANAC_FLAG_THR_INTF	   BIT(1)
#define ANAC_ANAC_FLAG_ADC_INTF	   BIT(0)

#define ANAC_WPROT_V0 0x5a5a
#define ANAC_WPROT_V1 0xa5a5
#define ANAC_WPT_UNLOCK()                                                                                              \
	{                                                                                                                  \
		ANAC->WPROT = ANAC_WPROT_V0;                                                                                   \
		ANAC->WPROT = ANAC_WPROT_V1;                                                                                   \
	}

// ADC macro define
#define ADC_CHN_AIN0  0
#define ADC_CHN_AIN1  1
#define ADC_CHN_AIN2  2
#define ADC_CHN_AIN3  3
#define ADC_CHN_AIN4  4
#define ADC_CHN_AIN5  5
#define ADC_CHN_AIN6  6
#define ADC_CHN_AIN7  7
#define ADC_CHN_AIN8  8
#define ADC_CHN_V1P5D 9
#define ADC_CHN_V1P5A 10
#define ADC_CHN_VBGA  11
#define ADC_CHN_PD_VO 12
#define ADC_CHN_VBGS  13
#define ADC_CHN_V1P5S 14

#define ADC_VREF_SEL_INT 0
#define ADC_VREF_SEL_EXT 1
#define ADC_VREF_SEL_VCC 2

#define ADC_VREF_VOLT_1P2 0
#define ADC_VREF_VOLT_1P5 1
#define ADC_VREF_VOLT_2P0 2
#define ADC_VREF_VOLT_2P5 3

#define ADC_SMP_TIMS_1	0
#define ADC_SMP_TIMS_4	1
#define ADC_SMP_TIMS_8	2
#define ADC_SMP_TIMS_32 3

#define ADC_SMP_CYCLE_16 0
#define ADC_SMP_CYCLE_12 1
#define ADC_SMP_CYCLE_8	 2
#define ADC_SMP_CYCLE_4	 3

typedef enum _ADC_VAL_NO
{
	ADC_VAL_NO0 = 0,
	ADC_VAL_NO1,
	ADC_VAL_NO2,
	ADC_VAL_NO3,
	ADC_VAL_NO4,
	ADC_VAL_NO5,
	ADC_VAL_NO6,
	ADC_VAL_NO7,
} ADC_VAL_NO;

// DCDC Buzzer macro define

// extern function declare
void ANAC_Init(int freq);
void ANAC_DeInit(void);
void ANAC_AnalogPowerEn(void);
void ADC_Init(int chn, int buffEn, int verfSel, int verfVol, int smpTimes, int smpCycle);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_EnableIRQ(void);
void ADC_DisableIRQ(void);
void ADC_StartConvert(void);
u32	 ADC_GetSingleResultValue(int valNo);
u32	 ADC_GetAverageValue(void);
BOOL ADC_GetIntFlag(void);
void ADC_ClrIntFlag(void);

#endif /*__ANAC_H__*/
