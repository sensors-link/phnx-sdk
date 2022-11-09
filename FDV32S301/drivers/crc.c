/**
  ******************************************************************************
  * @file    crc.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-19
  * @brief   This file provides all the CRC firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "crc.h"
#include "sysc.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC
  * @brief CRC driver modules
  * @{
  */

/** @defgroup CRC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the CRC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CRC_DeInit(void)
{
	/* Reset the CRC module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_CRC);
}

/**
  * @brief  Calculate the CRC16 checksum of incoming data.
  * @param  pData: pointer to the data cache to be calculated.
  * @param  DataType: Specifies the bit width type of the data to be calculated.
  *   This parameter can be one of @ref CRC_DataType enumeration:
  *     @arg CRC_DATA_8BIT: The bit width type of the data is 8 bits
  *     @arg CRC_DATA_16BIT: The bit width type of the data is 16 bits
  *     @arg CRC_DATA_32BIT: The bit width type of the data is 32 bits
  * @param  DataLen: Specifies the length of the calculated data.
  * @retval Calculation result of CRC16.
  */
u16	 CRC_CalcCRC16(void *pData, CRC_DataType DataType, u32 DataLen)
{
	u32 i;

	/* Check the parameters */
	PARAM_CHECK(IS_CRC_VALID_DATA(pData));
	PARAM_CHECK(IS_CRC_DATA_TYPE(DataType));
	PARAM_CHECK(IS_CRC_VALID_LEN(DataLen));

	/* Initialize CRC calculation */
	CRC->RSL = 0xFFFF;

	/* Write the data to the register CRC_DAT according to the bit width */
	switch (DataType)
	{
	case CRC_DATA_8BIT: {
		u8 *pDst = (u8 *)(&CRC->DAT);
		u8 *pSrc = (u8 *)(pData);
		for (i = 0; i < DataLen; ++i)
		{
			*pDst = *pSrc++;
		}
		break;
	}
	case CRC_DATA_16BIT: {
		u16 *pDst = (u16 *)(&CRC->DAT);
		u16 *pSrc = (u16 *)(pData);
		for (i = 0; i < DataLen; ++i)
		{
			*pDst = *pSrc++;
		}
		break;
	}
	case CRC_DATA_32BIT: {
		u32 *pDst = (u32 *)(&CRC->DAT);
		u32 *pSrc = (u32 *)(pData);
		for (i = 0; i < DataLen; ++i)
		{
			*pDst = *pSrc++;
		}
		break;
	}
	default:
		break;
	}

	/* Return CRC16 calculation result */
	return (u16)(CRC->RSL & CRC_RSL_CRC16);
}

/**
  * @brief  Check CRC16 of incoming data.
  * @param  pData: pointer to the data cache to verify.
  * @param  DataType: Specifies the bit width type of the data to be checked..
  *   This parameter can be one of @ref CRC_DataType enumeration:
  *     @arg CRC_DATA_8BIT: The bit width type of the data is 8 bits
  *     @arg CRC_DATA_16BIT: The bit width type of the data is 16 bits
  *     @arg CRC_DATA_32BIT: The bit width type of the data is 32 bits
  * @param  DataLen: Specifies the length of the checked data.
  * @param  CrcVal: Specifies the value of the CRC16 to be checked.
  * @retval check result (TRUE or FALSE).
  */
BOOL CRC_CheckCRC16(void *pData, CRC_DataType DataType, u32 DataLen, u16 CrcVal)
{
	u32 i;

	/* Check the parameters */
	PARAM_CHECK(IS_CRC_VALID_DATA(pData));
	PARAM_CHECK(IS_CRC_DATA_TYPE(DataType));
	PARAM_CHECK(IS_CRC_VALID_LEN(DataLen));

	/* Initialize CRC calculation */
	CRC->RSL = 0xFFFF;

	/* Write the data to the register CRC_DAT according to the bit width */
	switch (DataType)
	{
	case CRC_DATA_8BIT: {
		u8 *pDst = (u8 *)(&CRC->DAT);
		u8 *pSrc = (u8 *)(pData);
		for (i = 0; i < DataLen; ++i)
		{
			*pDst = *pSrc++;
		}
		break;
	}
	case CRC_DATA_16BIT: {
		u16 *pDst = (u16 *)(&CRC->DAT);
		u16 *pSrc = (u16 *)(pData);
		for (i = 0; i < DataLen; ++i)
		{
			*pDst = *pSrc++;
		}
		break;
	}
	case CRC_DATA_32BIT: {
		u32 *pDst = (u32 *)(&CRC->DAT);
		u32 *pSrc = (u32 *)(pData);
		for (i = 0; i < DataLen; ++i)
		{
			*pDst = *pSrc++;
		}
		break;
	}
	default:
		break;
	}

	/* Write CRC16 value to register CRC_DAT */
	*((u16 *)&CRC->DAT) = (u32)CrcVal;

	/* Write to the CRC_DAT register to execute an instruction to synchronize */
	asm("nop");

	/* return check result */
	return (CRC->RSL & CRC_RSL_CHKPSS) ? SET : RESET;
}

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

