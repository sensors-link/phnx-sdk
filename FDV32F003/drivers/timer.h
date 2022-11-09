/**
  ******************************************************************************
  * @file    timer.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-23
  * @brief   This file contains all functional prototypes of the TIM firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx05.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */

/** @defgroup TIM_module_register_bit_definition
  * @{
  */

/* TIM_T0CR */
#define TIM_T0CR_T0EN	  BIT(7)
#define TIM_T0CR_T0RLDEN  BIT(6)
#define TIM_T0CR_PSA	  BIT(3)
#define TIM_T0CR_PS		  BITS(0, 2)

#define TIM_T0CR_PS_pos	  (0)

/* TIM_T0 */
#define TIM_T0_T0		BITS(0, 7)

#define TIM_T0_T0_pos	(0)

/* TIM_T0RLD */
#define TIM_T0RLD_T0RLD	BITS(0, 7)

#define TIM_T0RLD_T0RLD_pos	(0)

/* TIM_TLE */
#define TIM_TIE_T4IE	BIT(4)
#define TIM_TIE_T3IE	BIT(3)
#define TIM_TIE_T2IE	BIT(2)
#define TIM_TIE_T1IE	BIT(1)
#define TIM_TIE_T0IE	BIT(0)

/* TIM_TLF */
#define TIM_TIF_T4IF	BIT(4)
#define TIM_TIF_T3IF	BIT(3)
#define TIM_TIF_T2IF	BIT(2)
#define TIM_TIF_T1IF	BIT(1)
#define TIM_TIF_T0IF	BIT(0)

/* TIM_TCR */
#define TIM_TCR_PWMON	BIT(7)
#define TIM_TCR_INTSE	BIT(6)
#define TIM_TCR_TGC		BIT(4)
#define TIM_TCR_TCKS	BITS(2, 3)
#define TIM_TCR_TCS		BIT(1)
#define TIM_TCR_TON		BIT(0)

#define TIM_TCR_TCKS_pos	(2)

/* TIM_TN */
#define TIM_TN_TN	BITS(0, 15)

#define TIM_TN_TN_pos	BITS(0)

/* TIM_PWMPD */
#define TIM_PWMPD_PWMPD	BITS(0, 15)

#define TIM_PWMPD_PWMPD_pos	(0)

/* TIM_PWMDC */
#define TIM_PWMDC_PWMDC	BITS(0, 15)

#define TIM_PWMDC_PWMDC_pos	(0)
/**
  * @}
  */

/** @defgroup TIM_Exported_Types
  * @{
  */

/**
  * @brief TIM Base Init structure definition
  */

typedef struct
{
	u8 TIM_Prescaler;						/*!< Specifies the prescaler value used to divide the TIM clock.
                                                 This parameter can be a value of @ref TIM_prescaler_value. */

	u16 TIM_PresetValue; 					/*!< Specify Timer count preset value.
												 This parameter can be a number between 0x0000 and 0xFFFF. */
} TIM_BaseInitTypeDef;

/**
  * @brief TIM PWM Init structure definition
  */

typedef struct
{
	u8 TIM_Prescaler;						/*!< Specifies the prescaler value used to divide the TIM clock.
                                                 This parameter can be a value of @ref TIM_prescaler_value. */
												 	
	u16 TIM_PWMPeriod; 						/*!< Specifies the run period value of the PWM.
												 This parameter can be a number between 0x0000 and 0xFFFF. */
											
	u16 TIM_PWMDuty; 						/*!< Specify the duty value of PWM.
												 This parameter can be a number between 0x0000 and 0xFFFF. */
} TIM_PWMInitTypeDef;

/**
  * @brief TIM count Init structure definition
  */

typedef struct
{
	u16 TIM_OverValue; 						/*!< Specifies the timer external pulse count overflow value.
												 This parameter can be a number between 0x0000 and 0xFFFF. */
} TIM_CountInitTypeDef;

/**
  * @brief TIM TIMER0 Init structure definition
  */

typedef struct
{
	u8 TIM_T0Prescaler;						/*!< Specifies the prescaler value used to divide the TIM0 clock.
												  - divide = 2^TIM_T0Prescaler.
                                                 This parameter can be a value between 0 to 8. */

	FunctionalState TIM_ReloadCmd; 			/*!< Specifies the new state for TIM0 overload enablement.
											  	 This parameter can be set either to ENABLE or DISABLE. */

	u8 TIM_ReloadValue; 					/*!< Specifies the overload count value for TIM0.
												 This parameter can be a number between 0x00 and 0xFF. */
} TIM_T0InitTypeDef;

/**
  * @}
  */

/** @defgroup TIM_Exported_Constants
  * @{
  */

/** @defgroup TIM_all_timer_peripheral
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || ((PERIPH) == TIM2) || ((PERIPH) == TIM3) || ((PERIPH) == TIM4))
/**
  * @}
  */

/** @defgroup TIM_prescaler_value
  * @{
  */
	
#define TIM_PRESCALER_DIV1		(0)
#define TIM_PRESCALER_DIV2		(1)
#define TIM_PRESCALER_DIV4		(2)
#define TIM_PRESCALER_DIV8		(3)

#define IS_TIM_PRESCALER(PREVAL) (((PREVAL) == TIM_PRESCALER_DIV1) || ((PREVAL) == TIM_PRESCALER_DIV2) ||            \
								  ((PREVAL) == TIM_PRESCALER_DIV4) || ((PREVAL) == TIM_PRESCALER_DIV8))
/**
  * @}
  */

/** @defgroup TIM_T0_prescaler
  * @{
  */

#define IS_TIM_T0_PRESCALER(PREVAL) ((PREVAL) <= 0x08)
/**
  * @}
  */

/** @defgroup TIM_T0_prescaler
  * @{
  */
	
#define TIM_INT_TRIGGER_FALL	(0)
#define TIM_INT_TRIGGER_RISE	(1)

#define IS_TIM_INTTRIGGER_TYPE(TYPE) (((TYPE) == TIM_INT_TRIGGER_FALL) || ((TYPE) == TIM_INT_TRIGGER_RISE))
/**
  * @}
  */

/** @defgroup TIM_interrupts_definition
  * @{
  */
	
#define TIM_IT_T4IE BIT(4)
#define TIM_IT_T3IE BIT(3)
#define TIM_IT_T2IE BIT(2)
#define TIM_IT_T1IE BIT(1)
#define TIM_IT_T0IE BIT(0)

#define TIM_IT_ALL (TIM_IT_T4IE | TIM_IT_T3IE | TIM_IT_T2IE | TIM_IT_T1IE | TIM_IT_T0IE)

#define IS_TIM_CONFIG_IT(IT) (((IT)&TIM_IT_ALL) && (!((IT) & (~(TIM_IT_ALL)))))

#define IS_TIM_GET_IT(IT)                                                                                              \
	(((IT) == TIM_IT_T4IE) || ((IT) == TIM_IT_T3IE) || ((IT) == TIM_IT_T2IE) || ((IT) == TIM_IT_T1IE) ||             \
	 ((IT) == TIM_IT_T0IE))
/**
  * @}
  */

/** @defgroup TIM_flags_definition
  * @{
  */
	
#define TIM_FLAG_T4IF	BIT(4)
#define TIM_FLAG_T3IF	BIT(3)
#define TIM_FLAG_T2IF	BIT(2)
#define TIM_FLAG_T1IF	BIT(1)
#define TIM_FLAG_T0IF	BIT(0)

#define TIM_FLAG_ALL (TIM_FLAG_T4IF | TIM_FLAG_T3IF | TIM_FLAG_T2IF | TIM_FLAG_T1IF | TIM_FLAG_T0IF)

#define IS_TIM_GET_FLAG(FLAG)                                                                                          \
	(((FLAG) == TIM_FLAG_T4IF) || ((FLAG) == TIM_FLAG_T3IF) || ((FLAG) == TIM_FLAG_T2IF) ||                            \
	 ((FLAG) == TIM_FLAG_T1IF) || ((FLAG) == TIM_FLAG_T0IF))

#define IS_TIM_CLEAR_FLAG(FLAG) (((FLAG) & TIM_FLAG_ALL) && (!((FLAG) & (~(TIM_FLAG_ALL)))))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup TIM_Exported_Functions
  * @{
  */

void	   TIM_DeInit(TIM_TypeDef *TIMx);
void	   TIM_T0DeInit(void);
void	   TIM_BaseInit(TIM_TypeDef *TIMx, TIM_BaseInitTypeDef *TIM_BaseInitStruct);
void	   TIM_PWMInit(TIM_TypeDef *TIMx, TIM_PWMInitTypeDef *TIM_PWMInitStruct);
void	   TIM_CountInit(TIM_TypeDef *TIMx, TIM_CountInitTypeDef *TIM_CountInitStruct);
void	   TIM_T0Init(TIM_T0InitTypeDef *TIM_T0InitStruct);
void	   TIM_SetIntTriggerType(TIM_TypeDef *TIMx, u8 IntTriggerType);
void	   TIM_GatingCmd(TIM_TypeDef *TIMx, FunctionalState NewState);
void	   TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState);
void	   TIM_T0Cmd(FunctionalState NewState);
void	   TIM_ITConfig(u32 TIM_IT, FunctionalState NewState);
FlagStatus TIM_GetFlagStatus(u16 TIM_FLAG);
ITStatus   TIM_GetITStatus(u32 TIM_IT);
void	   TIM_ClearFlag(u16 TIM_FLAG);
void	   TIM_SetCounter(TIM_TypeDef *TIMx, u16 Counter);
u16		   TIM_GetCounter(TIM_TypeDef *TIMx);
void	   TIM_SetT0Counter(u8 Counter);
u8		   TIM_GetT0Counter(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

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

