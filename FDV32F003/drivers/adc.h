/**
 * @file adc.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-06-8
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __ADC_H__
#define __ADC_H__
#include "../include/phnx05.h"

// register defines
#define ADC_CFG_REG	 REG32(ADC_BASE + 0x00)
#define ADC_INTF_REG REG32(ADC_BASE + 0x04)
#define ADC_DATA_REG REG32(ADC_BASE + 0x08)

// register bits definitions
// ADC_CFG
#define ADC_CFG_SMP_CYCLE BITS(8, 9)
#define ADC_CFG_CHSEL	  BITS(4, 7)
#define ADC_CFG_VRSEL	  BITS(3)
#define ADC_CFG_SST		  BITS(2)
#define ADC_CFG_ADC_IE	  BITS(1)
#define ADC_CFG_ADC_EN	  BITS(0)

#define ADC_CFG_SMP_CYCLE_16 (0 << 8)
#define ADC_CFG_SMP_CYCLE_12 (1 << 8)
#define ADC_CFG_SMP_CYCLE_8	 (2 << 8)
#define ADC_CFG_SMP_CYCLE_4	 (3 << 8)

#define ADC_CFG_CHSEL_VSS		 (15 << 4)
#define ADC_CFG_CHSEL_VBG1P2	 (14 << 4)
#define ADC_CFG_CHSEL_VBGS1P0	 (13 << 4)
#define ADC_CFG_CHSEL_VREF_FLASH (12 << 4)
#define ADC_CFG_CHSEL_AIN11		 (11 << 4)
#define ADC_CFG_CHSEL_AIN10		 (10 << 4)
#define ADC_CFG_CHSEL_AIN9		 (9 << 4)
#define ADC_CFG_CHSEL_AIN8		 (8 << 4)
#define ADC_CFG_CHSEL_AIN7		 (7 << 4)
#define ADC_CFG_CHSEL_AIN6		 (6 << 4)
#define ADC_CFG_CHSEL_AIN5		 (5 << 4)
#define ADC_CFG_CHSEL_AIN4		 (4 << 4)
#define ADC_CFG_CHSEL_AIN3		 (3 << 4)
#define ADC_CFG_CHSEL_AIN2		 (2 << 4)
#define ADC_CFG_CHSEL_AIN1		 (1 << 4)
#define ADC_CFG_CHSEL_AIN0		 (0 << 4)

#define ADC_CFG_VRSEL_VREF (0 << 3)
#define ADC_CFG_VRSEL_VCC  (1 << 3)

#define ADC_CFG_SST_STOP  (0 << 2)
#define ADC_CFG_SST_START (1 << 2)

#define ADC_CFG_ADC_IE_DISABLE (0 << 1)
#define ADC_CFG_ADC_IE_ENABLE  (1 << 1)

#define ADC_CFG_ADC_EN_DISABLE (0 << 0)
#define ADC_CFG_ADC_EN_ENABLE  (1 << 0)

// ADC_INTF
#define ADC_INTF BIT(0)

// ADC_DATA
#define ADC_DATA BITS(0, 11)

// ADC macro define
#define ADC_CHN_AIN0  (0)
#define ADC_CHN_AIN1  (1)
#define ADC_CHN_AIN2  (2)
#define ADC_CHN_AIN3  (3)
#define ADC_CHN_AIN4  (4)
#define ADC_CHN_AIN5  (5)
#define ADC_CHN_AIN6  (6)
#define ADC_CHN_AIN7  (7)
#define ADC_CHN_AIN8  (8)
#define ADC_CHN_AIN9  (9)
#define ADC_CHN_AIN10 (10)
#define ADC_CHN_AIN11 (11)

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

void ADC_Init(int chn, int buffEn, int verfSel, int smpCycle);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_EnableIRQ(void);
void ADC_DisableIRQ(void);
void ADC_StartConvert(void);
u16	 ADC_GetSingleResultValue(void);
BOOL ADC_GetIntFlag(void);
void ADC_ClrIntFlag(void);

#endif /* __ADC_H__ */
