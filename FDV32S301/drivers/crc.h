/**
 * @file crc.h
 * @author bifei.tang
 * @brief
 * @version 1.0
 * @date 2021-06-27
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#ifndef __CRC_H__
#define __CRC_H__

#include "phnx02.h"

/* CRC definitions */
#define CRC_RSL_REG REG32(CRC_BASE + 0x04)
#define CRC_DAT_REG REG32(CRC_BASE + 0x80)

/*register bit definitions */
// CRC_RSL
#define CRC_RSL_CHKPSS BIT(16)
#define CRC_RSL_CRC16  BITS(0, 15)

// data type define
typedef enum _DataType
{
	DATA_32BIT = 0,
	DATA_16BIT = 1,
	DATA_8BIT  = 2,
} eDataType;

void CRC_Init(void);
void CRC_DeInit(void);
u16	 CRC_Calculate(void *pDat, eDataType u8DataType, u32 u32Len);
BOOL CRC_Check(void *pDat, eDataType u8DataType, u32 u32Len, u16 crc);

#endif /*__CRC_H__*/
