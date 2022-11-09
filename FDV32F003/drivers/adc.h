/**
  ******************************************************************************
  * @file    adc.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-10-27
  * @brief   This file contains all functional prototypes of the ADC firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx05.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_module_register_bit_definition
  * @{
  */

/* ADC_CFG */
#define ADC_CFG_SMP_CYCLE  BITS(8, 9)
#define ADC_CFG_CHSEL      BITS(4, 7)
#define ADC_CFG_VRSEL      BIT(3)
#define ADC_CFG_SST        BIT(2)
#define ADC_CFG_ADC_IE     BIT(1)
#define ADC_CFG_ADC_EN     BIT(0)

#define ADC_CFG_SMP_CYCLE_16ADCCLK (0 << 8)
#define ADC_CFG_SMP_CYCLE_12ADCCLK (1 << 8)
#define ADC_CFG_SMP_CYCLE_8ADCCLK  (2 << 8)
#define ADC_CFG_SMP_CYCLE_4ADCCLK  (3 << 8)

#define ADC_CFG_CHSEL_AIN0	(0 << 4)
#define ADC_CFG_CHSEL_AIN1	(1 << 4)
#define ADC_CFG_CHSEL_AIN2	(2 << 4)
#define ADC_CFG_CHSEL_AIN3	(3 << 4)
#define ADC_CFG_CHSEL_AIN4	(4 << 4)
#define ADC_CFG_CHSEL_AIN5	(5 << 4)
#define ADC_CFG_CHSEL_AIN6	(6 << 4)
#define ADC_CFG_CHSEL_AIN7	(7 << 4)
#define ADC_CFG_CHSEL_AIN8	(8 << 4)
#define ADC_CFG_CHSEL_AIN9	(9 << 4)
#define ADC_CFG_CHSEL_AIN10 (10 << 4)
#define ADC_CFG_CHSEL_AIN11 (11 << 4)
#define ADC_CFG_CHSEL_VCC	(12 << 4)
#define ADC_CFG_CHSEL_VCC1	(13 << 4)
#define ADC_CFG_CHSEL_VSS	(14 << 4)
#define ADC_CFG_CHSEL_VSS1	(15 << 4)

#define ADC_CFG_SMP_CYCLE_pos  (8)
#define ADC_CFG_CHSEL_pos      (4)


/* ADC_INTF */
#define ADC_INTF_INTF BIT(0)

/* ADC_DATA */
#define ADC_DATA_DATA BITS(0, 11)

/**
  * @}
  */

/** @defgroup ADC_Exported_Types
  * @{
  */

/**
  * @brief ADC Init structure definition
  */

typedef struct
{
	u8 ADC_Channel; 						/*!< Specify ADC input channel.
											 	 This parameter can be a value of @ref ADC_channels. */

	u8 ADC_VrefSel; 						/*!< Specify the ADC reference voltage input source.
											 	 This parameter can be a value of @ref ADC_vref_selection. */

	u8 ADC_SmpCycle; 						/*!< Specify ADC input signal sample and hold time.
											 	 This parameter can be a value of @ref ADC_sample_cycle. */
} ADC_InitTypeDef;

/**
  * @}
  */

/** @defgroup ADC_Exported_Constants
  * @{
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
#define ADC_CHN_AIN9	  (9)
#define ADC_CHN_AIN10	  (10)
#define ADC_CHN_AIN11	  (11)
#define ADC_CHN_VCC	      (12)
#define ADC_CHN_VCC1	  (13)
#define ADC_CHN_VSS	      (14)
#define ADC_CHN_VSS1	  (15)

#define IS_ADC_CHANNEL(CHANNEL)                                                                                        \
	(((CHANNEL) == ADC_CHN_AIN0) || ((CHANNEL) == ADC_CHN_AIN1) || ((CHANNEL) == ADC_CHN_AIN2) ||                      \
	 ((CHANNEL) == ADC_CHN_AIN3) || ((CHANNEL) == ADC_CHN_AIN4) || ((CHANNEL) == ADC_CHN_AIN5) ||                      \
	 ((CHANNEL) == ADC_CHN_AIN6) || ((CHANNEL) == ADC_CHN_AIN7) || ((CHANNEL) == ADC_CHN_AIN8) ||                      \
	 ((CHANNEL) == ADC_CHN_AIN9) || ((CHANNEL) == ADC_CHN_AIN10) || ((CHANNEL) == ADC_CHN_AIN11) ||                   \
	 ((CHANNEL) == ADC_CHN_VCC) || ((CHANNEL) == ADC_CHN_VCC1) || ((CHANNEL) == ADC_CHN_VSS) ||                        \
	 ((CHANNEL) == ADC_CHN_VSS1))
/**
  * @}
  */

/** @defgroup ADC_vref_selection
  * @{
  */

#define ADC_VREF_SEL_EXT (0)
#define ADC_VREF_SEL_VCC (1)

#define IS_ADC_VREFSEL(VREFSEL) (((VREFSEL) == ADC_VREF_SEL_EXT) || ((VREFSEL) == ADC_VREF_SEL_VCC))
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
	(((SMPCYCLE) == ADC_SMP_CYCLE_16) || ((SMPCYCLE) == ADC_SMP_CYCLE_12) || ((SMPCYCLE) == ADC_SMP_CYCLE_8) ||       \
	 ((SMPCYCLE) == ADC_SMP_CYCLE_4))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions
  * @{
  */

void	   ADC_DeInit(void);
void	   ADC_Init(ADC_InitTypeDef *ADC_InitStruct);
u16		   ADC_GetConversionValue(void);
void	   ADC_SoftwareStartConvCmd(FunctionalState NewState);
void	   ADC_Cmd(FunctionalState NewState);
void	   ADC_ITConfig(FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(void);
ITStatus   ADC_GetITStatus(void);
void	   ADC_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

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

