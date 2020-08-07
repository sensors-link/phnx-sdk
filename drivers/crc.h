/**
 * @file crc.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */
#ifndef __CRC_H
#define __CRC_H
#include "phnx02.h"
/* CRC definitions */
#define CRC_RSL_REG REG32(CRC_BASE + 0x04)
#define CRC_DAT_REG REG32(CRC_BASE + 0x80)

/*register bit definitions */
// CRC_RSL
#define CRC_RSL_CHKPSS BIT(16)
#define CRC_RSL_CRC16 BITS(0, 15)

// data type define
typedef enum _DataType {
    DATA_32BIT = 0,
    DATA_16BIT,
    DATA_8BIT,
} eDataType;

// function
void CRC_Init(void);
void CRC_DeInit(void);
u16 CRC_Calculate(void *pDat, eDataType u8DataType, u32 u32Len);
BOOL CRC_Check(void *pDat, eDataType u8DataType, u32 u32Len, u16 crc);

#endif
