/**
  ******************************************************************************
  * @file    iom.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-09
  * @brief   This file contains all functional prototypes of the IOM firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IOM_H__
#define __IOM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx04.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @addtogroup IOM
  * @{
  */

/** @defgroup IOM_module_register_bit_definition
  * @{
  */

/* IOM_AF0 */
#define IOM_AF0_P15_SEL BITS(30, 31)
#define IOM_AF0_P14_SEL BITS(28, 29)
#define IOM_AF0_P13_SEL BITS(26, 27)
#define IOM_AF0_P12_SEL BITS(24, 25)
#define IOM_AF0_P07_SEL BITS(14, 15)
#define IOM_AF0_P06_SEL BITS(12, 13)
#define IOM_AF0_P05_SEL BITS(10, 11)
#define IOM_AF0_P04_SEL BITS(8, 9)

#define IOM_AF0_P15_SEL_GPIO	  (0 << 30)
#define IOM_AF0_P15_SEL_UART1_TX  (1 << 30)
#define IOM_AF0_P15_SEL_SPI_SCK   (2 << 30)
#define IOM_AF0_P15_SEL_TIM2_TOG  (3 << 30)

#define IOM_AF0_P14_SEL_GPIO	 (0 << 28)
#define IOM_AF0_P14_SEL_UART1_RX (1 << 28)
#define IOM_AF0_P14_SEL_SPI_CS   (2 << 28)
#define IOM_AF0_P14_SEL_TIM1_TOG (3 << 28)

#define IOM_AF0_P13_SEL_GPIO	  (0 << 26)
#define IOM_AF0_P13_SEL_TIM2_TOG  (1 << 26)
#define IOM_AF0_P13_SEL_TIM2_EXT  (2 << 26)
#define IOM_AF0_P13_SEL_SPI_SCK   (3 << 26)

#define IOM_AF0_P12_SEL_GPIO	  (0 << 24)
#define IOM_AF0_P12_SEL_TIM1_TOG  (1 << 24)
#define IOM_AF0_P12_SEL_TIM2_GATE (2 << 24)
#define IOM_AF0_P12_SEL_SPI_CS	  (3 << 24)

#define IOM_AF0_P07_SEL_GPIO	  (0 << 14)
#define IOM_AF0_P07_SEL_JTAG_TDO  (1 << 14)
#define IOM_AF0_P07_SEL_TIM1_EXT  (2 << 14)
#define IOM_AF0_P07_SEL_UART2_TX  (3 << 14)

#define IOM_AF0_P06_SEL_GPIO	  (0 << 12)
#define IOM_AF0_P06_SEL_JTAG_TMS  (1 << 12)
#define IOM_AF0_P06_SEL_TIM1_GATE (2 << 12)
#define IOM_AF0_P06_SEL_UART2_RX  (4 << 12)

#define IOM_AF0_P05_SEL_GPIO	  (0 << 10)
#define IOM_AF0_P05_SEL_JTAG_TDI  (1 << 10)
#define IOM_AF0_P05_SEL_UART2_TX  (2 << 10)
#define IOM_AF0_P05_SEL_TWC_TX	  (3 << 10)

#define IOM_AF0_P04_SEL_GPIO	 (0 << 8)
#define IOM_AF0_P04_SEL_JTAG_TCK (1 << 8)
#define IOM_AF0_P04_SEL_UART2_RX (2 << 8)
#define IOM_AF0_P04_SEL_TWC_RX	 (3 << 8)

#define IOM_AF0_P15_SEL_pos (30)
#define IOM_AF0_P14_SEL_pos (28)
#define IOM_AF0_P13_SEL_pos (26)
#define IOM_AF0_P12_SEL_pos (24)
#define IOM_AF0_P07_SEL_pos (14)
#define IOM_AF0_P06_SEL_pos (12)
#define IOM_AF0_P05_SEL_pos (10)
#define IOM_AF0_P04_SEL_pos (8)

/* IOM_AF1 */
#define IOM_AF1_P19_SEL BITS(6, 7)
#define IOM_AF1_P18_SEL BITS(4, 5)
#define IOM_AF1_P17_SEL BITS(2, 3)
#define IOM_AF1_P16_SEL BITS(0, 1)

#define IOM_AF1_P19_SEL_GPIO	  (0 << 6)
#define IOM_AF1_P19_SEL_TWC_TX	  (1 << 6)
#define IOM_AF1_P19_SEL_SPI_MOSI  (2 << 6)
#define IOM_AF1_P19_SEL_UART1_TX  (3 << 6)

#define IOM_AF1_P18_SEL_GPIO	  (0 << 4)
#define IOM_AF1_P18_SEL_TWC_RX	  (1 << 4)
#define IOM_AF1_P18_SEL_SPI_MISO  (2 << 4)
#define IOM_AF1_P18_SEL_UART1_RX  (3 << 4)

#define IOM_AF1_P17_SEL_GPIO	  (0 << 2)
#define IOM_AF1_P17_SEL_TIM2_TOGN (1 << 2)
#define IOM_AF1_P17_SEL_RSV		  (2 << 2)
#define IOM_AF1_P17_SEL_SPI_MISO  (3 << 2)

#define IOM_AF1_P16_SEL_GPIO	 (0 << 0)
#define IOM_AF1_P16_SEL_TIM1_TOG (1 << 0)
#define IOM_AF1_P16_SEL_TSTO	 (2 << 0)
#define IOM_AF1_P16_SEL_SPI_MOSI (3 << 0)

#define IOM_AF1_P19_SEL_pos (6)
#define IOM_AF1_P18_SEL_pos (4)
#define IOM_AF1_P17_SEL_pos (2)
#define IOM_AF1_P16_SEL_pos (0)

/* IOM_CTL */
#define IOM_CTL_LS_SYNC	 BIT(2)
#define IOM_CTL_DEBOUNCE BIT(1)
#define IOM_CTL_INTE	 BIT(0)

/**
  * @}
  */

/** @defgroup IOM_Exported_Types
  * @{
  */

/**
  * @brief IOM Init structure definition
  */

typedef struct
{
	u32 IOM_Pin; 							/*!< Specifies the IOM pins to be configured.
												 This parameter can be any value of @ref IOM_pins_define */

	FunctionalState IOM_OutCmd; 			/*!< Specifies the new state of the selected pin output.
												 This parameter can be set either to ENABLE or DISABLE. */

	FunctionalState IOM_PuCmd; 				/*!< Specifies the new state of the selected pin pull-up.
												 This parameter can be set either to ENABLE or DISABLE. */

	FunctionalState IOM_PdCmd; 				/*!< Specifies the new state of the selected pin pull-down.
											  	 This parameter can be set either to ENABLE or DISABLE. */

	u8 IOM_OutType; 						/*!< Specifies the output type of the selected pin.
										   		 This parameter can be a value of @ref IOM_out_type. */

	u8 IOM_ADState; 						/*!< Specifies the digital-to-analog configuration state of the selected pin.
												 This parameter can be a value of @ref IOM_AD_state. */

	u8 IOM_DRState; 						/*!< Specifies the drive capability state of the selected pin.
												 This parameter can be a value of @ref IOM_drive_state. */

	u8 IOM_AltFunc; 						/*!< Specifies the alternate function of the selected pin.
												 This parameter can be a value of @ref IOM_alternate_function. */

} IOM_InitTypeDef;

/**
  * @}
  */

/** @defgroup IOM_Exported_Constants
  * @{
  */

/** @defgroup IOM_pins_define
  * @{
  */

#define GPIO_PIN4  (1 << 4)
#define GPIO_PIN5  (1 << 5)
#define GPIO_PIN6  (1 << 6)
#define GPIO_PIN7  (1 << 7)
#define GPIO_PIN12 (1 << 12)
#define GPIO_PIN13 (1 << 13)
#define GPIO_PIN14 (1 << 14)
#define GPIO_PIN15 (1 << 15)
#define GPIO_PIN16 (1 << 16)
#define GPIO_PIN17 (1 << 17)
#define GPIO_PIN18 (1 << 18)
#define GPIO_PIN19 (1 << 19)

#define GPIO_ALL                                                                                                       \
	(GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7 | GPIO_PIN12 | GPIO_PIN13 | GPIO_PIN14 |     					   \
	 GPIO_PIN15 | GPIO_PIN16 |GPIO_PIN17 | GPIO_PIN18 | GPIO_PIN19)

#define IS_IOM_PIN(PIN) (((PIN) & GPIO_ALL) && (!((PIN) & (~GPIO_ALL))))

#define IS_GET_IOM_PIN(PIN)                                                                                            \
	(((PIN) == GPIO_PIN4) || ((PIN) == GPIO_PIN5) || ((PIN) == GPIO_PIN6) || ((PIN) == GPIO_PIN7) ||                  \
	 ((PIN) == GPIO_PIN12) || ((PIN) == GPIO_PIN13) || ((PIN) == GPIO_PIN14) || ((PIN) == GPIO_PIN15) ||              \
	 ((PIN) == GPIO_PIN16) || ((PIN) == GPIO_PIN17) || ((PIN) == GPIO_PIN18) || ((PIN) == GPIO_PIN19))

/**
  * @}
  */

/** @defgroup IOM_out_type
  * @{
  */
	
#define IOM_OTYPE_COMS	(0)
#define IOM_OTYPE_DRAIN (1)

#define IS_IOM_OTYPE(OTYPE) (((OTYPE) == IOM_OTYPE_COMS) || ((OTYPE) == IOM_OTYPE_DRAIN))
/**
  * @}
  */

/** @defgroup IOM_AD_state
  * @{
  */

#define IOM_ADS_DIGITAL (0)
#define IOM_ADS_ANALOG	(1)

#define IS_IOM_ADS(ADS) (((ADS) == IOM_ADS_DIGITAL) || ((ADS) == IOM_ADS_ANALOG))
/**
  * @}
  */

/** @defgroup IOM_drive_state
  * @{
  */

#define IOM_DRS_LOW	 (0)
#define IOM_DRS_HIGH (1)

#define IS_IOM_DRS(DRS) (((DRS) == IOM_DRS_LOW) || ((DRS) == IOM_DRS_HIGH))
/**
  * @}
  */

/** @defgroup IOM_alternate_function
  * @{
  */

#define IOM_ALT_FUNC_0 (0)
#define IOM_ALT_FUNC_1 (1)
#define IOM_ALT_FUNC_2 (2)
#define IOM_ALT_FUNC_3 (3)

#define IOM_ALT_FUNC_ALL (3)

#define IOM_ALT_FUNC_P04_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P04_JTAG_TCK IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P04_UART2_RX IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P04_TWC_RX	  IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P05_SEL_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P05_SEL_JTAG_TDI IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P05_SEL_UART2_TX IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P05_SEL_TWC_TX	  IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P06_SEL_GPIO	   IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P06_SEL_JTAG_TMS  IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P06_SEL_TIM1_GATE IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P06_SEL_UART2_RX  IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P07_SEL_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P07_SEL_JTAG_TDO IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P07_SEL_TIM1_EXT IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P07_SEL_UART2_TX IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P12_SEL_GPIO	   IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P12_SEL_TIM1_TOG  IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P12_SEL_TIM2_GATE IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P12_SEL_SPI_CS	   IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P13_SEL_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P13_SEL_TIM2_TOG IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P13_SEL_TIM2_EXT IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P13_SEL_SPI_SCK  IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P14_SEL_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P14_SEL_UART1_RX IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P14_SEL_SPI_CS   IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P14_SEL_TIM1_TOG IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P15_SEL_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P15_SEL_UART1_TX IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P15_SEL_SPI_SCK  IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P15_SEL_TIM2_TOG IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P16_SEL_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P16_SEL_TIM1_TOG IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P16_SEL_TSTO	  IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P16_SEL_SPI_MOSI IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P17_SEL_GPIO	   IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P17_SEL_TIM2_TOGN IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P17_SEL_RSV	   IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P17_SEL_SPI_MISO  IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P18_SEL_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P18_SEL_TWC_RX	  IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P18_SEL_SPI_MISO IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P18_SEL_UART1_RX IOM_ALT_FUNC_3

#define IOM_ALT_FUNC_P19_SEL_GPIO	  IOM_ALT_FUNC_0
#define IOM_ALT_FUNC_P19_SEL_TWC_TX	  IOM_ALT_FUNC_1
#define IOM_ALT_FUNC_P19_SEL_SPI_MOSI IOM_ALT_FUNC_2
#define IOM_ALT_FUNC_P19_SEL_UART1_TX IOM_ALT_FUNC_3

#define IS_IOM_ALTFUNC(ALTFUNC)                                                                                        \
	(((ALTFUNC) == IOM_ALT_FUNC_0) || ((ALTFUNC) == IOM_ALT_FUNC_1) || ((ALTFUNC) == IOM_ALT_FUNC_2) ||                \
	 ((ALTFUNC) == IOM_ALT_FUNC_3))
/**
  * @}
  */

/** @defgroup IOM_interrupt_type
  * @{
  */

#define IOM_INT_TYPE_EDGE  (0)
#define IOM_INT_TYPE_LEVEL (1)

#define IS_IOM_INTTYPE(INTTYPE) (((INTTYPE) == IOM_INT_TYPE_EDGE) || ((INTTYPE) == IOM_INT_TYPE_LEVEL))
/**
  * @}
  */

/** @defgroup IOM_interrupt_polarity
  * @{
  */

#define IOM_INT_POL_LOW	 (0)
#define IOM_INT_POL_HIGH (1)

#define IS_IOM_INTPOL(INTPOL) (((INTPOL) == IOM_INT_POL_LOW) || ((INTPOL) == IOM_INT_POL_HIGH))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup IOM_Exported_Functions
  * @{
  */

void	   IOM_Init(IOM_InitTypeDef *IOM_InitStruct);
void	   IOM_SetPinIntProperty(u32 IOM_Pin, u8 IntType, u8 IntPolarity);
void	   IOM_SyncAPBCmd(FunctionalState NewState);
void	   IOM_DebounceCmd(FunctionalState NewState);
void	   IOM_GlobalIntCmd(FunctionalState NewState);
void	   IOM_ITConfig(u32 IOM_Pin, FunctionalState NewState);
FlagStatus IOM_GetFlagStatus(u32 IOM_Pin);
ITStatus   IOM_GetITStatus(u32 IOM_Pin);
void	   IOM_ClearFlag(u32 IOM_Pin);
u32		   IOM_GetData(void);
void	   IOM_SetPin(u32 IOM_Pin);
void	   IOM_ClrPin(u32 IOM_Pin);

#ifdef __cplusplus
}
#endif

#endif /* __IOM_H__ */

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

