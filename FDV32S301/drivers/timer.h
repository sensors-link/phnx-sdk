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
#include "phnx02.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */

/** @defgroup TIM_module_register_bit_definition
  * @{
  */

/* TIM_PWCON */
#define TIM_PWCON_PWMCPOL BITS(17, 18)
#define TIM_PWCON_DTEN	  BIT(16)
#define TIM_PWCON_DTUGAP  BITS(0, 15)

#define TIM_PWCON_PWMCPOL_pos (17) /* 0-3 */
#define TIM_PWCON_DTUGAP_pos  (0)  /* 0-0xffff */

/* TIM_CON */
#define TIM_CON_PAUSE	   BITS(24, 27)
#define TIM_CON_PAUSE_TIM4 BIT(27)
#define TIM_CON_PAUSE_TIM3 BIT(26)
#define TIM_CON_PAUSE_TIM2 BIT(25)
#define TIM_CON_PAUSE_TIM1 BIT(24)

#define TIM_CON_EXTPOL		BITS(20, 23)
#define TIM_CON_EXTPOL_TIM4 BIT(23)
#define TIM_CON_EXTPOL_TIM3 BIT(22)
#define TIM_CON_EXTPOL_TIM2 BIT(21)
#define TIM_CON_EXTPOL_TIM1 BIT(20)

#define TIM_CON_EXTEN	   BITS(16, 19)
#define TIM_CON_EXTEN_TIM4 BIT(19)
#define TIM_CON_EXTEN_TIM3 BIT(18)
#define TIM_CON_EXTEN_TIM2 BIT(17)
#define TIM_CON_EXTEN_TIM1 BIT(16)

#define TIM_CON_PWM		 BITS(12, 15)
#define TIM_CON_PWM_TIM4 BIT(15)
#define TIM_CON_PWM_TIM3 BIT(14)
#define TIM_CON_PWM_TIM2 BIT(13)
#define TIM_CON_PWM_TIM1 BIT(12)

#define TIM_CON_IE		BITS(8, 11)
#define TIM_CON_IE_TIM4 BIT(11)
#define TIM_CON_IE_TIM3 BIT(10)
#define TIM_CON_IE_TIM2 BIT(9)
#define TIM_CON_IE_TIM1 BIT(8)

#define TIM_CON_TM		BITS(4, 7)
#define TIM_CON_TM_TIM4 BIT(7)
#define TIM_CON_TM_TIM3 BIT(6)
#define TIM_CON_TM_TIM2 BIT(5)
#define TIM_CON_TM_TIM1 BIT(4)

#define TIM_CON_TE		BITS(0, 3)
#define TIM_CON_TE_TIM4 BIT(3)
#define TIM_CON_TE_TIM3 BIT(2)
#define TIM_CON_TE_TIM2 BIT(1)
#define TIM_CON_TE_TIM1 BIT(0)

/* TIM_INTFLAG */
#define TIM_INTFLAG		 BITS(0, 3)
#define TIM_INTFLAG_TIM4 BIT(3)
#define TIM_INTFLAG_TIM3 BIT(2)
#define TIM_INTFLAG_TIM2 BIT(1)
#define TIM_INTFLAG_TIM1 BIT(0)

/* TIM_INTCLR */
#define TIM_INTCLR		BITS(0, 3)
#define TIM_INTCLR_TIM4 BIT(3)
#define TIM_INTCLR_TIM3 BIT(2)
#define TIM_INTCLR_TIM2 BIT(1)
#define TIM_INTCLR_TIM1 BIT(0)

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
	u32 TIM_PresetValue; 					/*!< Specify Timer count preset value.
												 This parameter must obey the following rules:
											 	    - When the running mode is free running, this parameter is a 32-bit value.
											 	    - When the run mode is User Defined, this parameter is a 16-bit value. */

	u8 TIM_RunMode; 						/*!< Specifies the running mode of the timer.
											 	 This parameter can be a value of @ref TIM_run_mode. */
} TIM_BaseInitTypeDef;

/**
  * @brief TIM PWM Init structure definition
  */

typedef struct
{
	u16 TIM_PWMLow; 						/*!< Specifies the low level count value of the PWM.
												 This parameter can be a number between 0x0000 and 0xFFFF. */
											
	u16 TIM_PWMHigh; 						/*!< Specifies the high level count value of the PWM.
												 This parameter can be a number between 0x0000 and 0xFFFF. */

	u8 TIM_PWMPolarity; 					/*!< Specifies the PMM polarity control state.
											 	 This parameter can be a value of @ref TIM_PWM_polarity. */

	FunctionalState TIM_DTCmd; 				/*!< Specifies the new state of the deadband control function.
											  	 This parameter can be set either to ENABLE or DISABLE. */

	u16 TIM_DTUGap; 						/*!< Specify PWM Dead Time Width.
												 This parameter can be a number between 0x0000 and 0xFFFF. */
} TIM_PWMInitTypeDef;

/**
  * @brief TIM count Init structure definition
  */

typedef struct
{
	u32 TIM_OverValue; 						/*!< Specifies the timer external pulse count overflow value. */

	u8 TIM_ExternPolarity; 					/*!< Specify the external pulse count polarity.
											 	 This parameter can be a value of @ref TIM_external_pulse_polarity. */
} TIM_CountInitTypeDef;

/**
  * @}
  */

/** @defgroup TIM_Exported_Constants
  * @{
  */

/** @defgroup TIM_run_mode
  * @{
  */

#define TIM_RUN_MODE_FREE_RUN	 (0)
#define TIM_RUN_MODE_USER_DEFINE (1)

#define IS_TIM_RUN_MODE(MODE) (((MODE) == TIM_RUN_MODE_FREE_RUN) || ((MODE) == TIM_RUN_MODE_USER_DEFINE))
/**
  * @}
  */

/** @defgroup TIM_all_timer_peripheral
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || ((PERIPH) == TIM2) || ((PERIPH) == TIM3) || ((PERIPH) == TIM4))
/**
  * @}
  */

/** @defgroup TIM_PWM_polarity
  * @{
  */

#define TIM_PWM_POL_TOG_TOGN   (0)
#define TIM_PWM_POL_NTOG_TOGN  (1)
#define TIM_PWM_POL_TOG_NTOGN  (2)
#define TIM_PWM_POL_NTOG_NTOGN (3)

#define IS_TIM_PWM_POL(POL)                                                                                            \
	(((POL) == TIM_PWM_POL_TOG_TOGN) || ((POL) == TIM_PWM_POL_NTOG_TOGN) || ((POL) == TIM_PWM_POL_TOG_NTOGN) ||        \
	 ((POL) == TIM_PWM_POL_NTOG_NTOGN))
/**
  * @}
  */

/** @defgroup TIM_external_pulse_polarity
  * @{
  */

#define TIM_EXTERN_POL_HIGH (0)
#define TIM_EXTERN_POL_LOW	(1)

#define IS_TIM_EXTERN_POL(POL) (((POL) == TIM_EXTERN_POL_HIGH) || ((POL) == TIM_EXTERN_POL_LOW))
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
void	   TIM_BaseInit(TIM_TypeDef *TIMx, TIM_BaseInitTypeDef *TIM_BaseInitStruct);
void	   TIM_PWMInit(TIM_TypeDef *TIMx, TIM_PWMInitTypeDef *TIM_PWMInitStruct);
void	   TIM_CountInit(TIM_TypeDef *TIMx, TIM_CountInitTypeDef *TIM_CountInitStruct);
void	   TIM_PauseCmd(TIM_TypeDef *TIMx, FunctionalState NewState);
void	   TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState);
void	   TIM_ITConfig(TIM_TypeDef *TIMx, FunctionalState NewState);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef *TIMx);
ITStatus   TIM_GetITStatus(TIM_TypeDef *TIMx);
void	   TIM_ClearFlag(TIM_TypeDef *TIMx);
u32		   TIM_GetCounter(TIM_TypeDef *TIMx);

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

