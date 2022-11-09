/**
  ******************************************************************************
  * @file    crc.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-06
  * @brief   This file contains all functional prototypes of the CRC firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRC_H__
#define __CRC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx02.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRC
  * @{
  */

/** @defgroup CRC_module_register_bit_definition
  * @{
  */

/* CRC_RSL */
#define CRC_RSL_CHKPSS BIT(16)
#define CRC_RSL_CRC16  BITS(0, 15)

#define CRC_RSL_CRC16_pos (0)

/**
  * @}
  */

/** @defgroup CRC_Exported_Types
  * @{
  */

/**
  * @brief CRC data bit width type enumeration
  */

typedef enum
{
	CRC_DATA_8BIT = 0,
	CRC_DATA_16BIT,
	CRC_DATA_32BIT
} CRC_DataType;

#define IS_CRC_DATA_TYPE(TYPE) (((TYPE) == CRC_DATA_8BIT) || ((TYPE) == CRC_DATA_16BIT) || ((TYPE) == CRC_DATA_32BIT))

/**
  * @}
  */

/** @defgroup CRC_Exported_Constants
  * @{
  */

#define IS_CRC_VALID_DATA(DATA) ((DATA) != (void *)0)

#define IS_CRC_VALID_LEN(LEN) ((LEN) > 0)

/**
  * @}
  */

/** @defgroup CRC_Exported_Functions
  * @{
  */

void CRC_DeInit(void);
u16	 CRC_CalcCRC16(void *pData, CRC_DataType DataType, u32 DataLen);
BOOL CRC_CheckCRC16(void *pData, CRC_DataType DataType, u32 DataLen, u16 CrcVal);

#ifdef __cplusplus
}
#endif

#endif /* __CRC_H__ */

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

