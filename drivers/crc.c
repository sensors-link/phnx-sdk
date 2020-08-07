/**
 * @file crc.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "crc.h"
#include "sysc.h"

/**
 * @brief CRC init
 *
 */
void CRC_Init(void) { SYSC->CLKENCFG |= SYSC_CLKENCFG_CRC; }

/**
 * @brief CRC deinit
 *
 */
void CRC_DeInit(void) {
    int i;
    SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
    SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
    SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_CRC;
    for (i = 10; i > 0; --i)
        ;
    SYSC->CLKENCFG &= ~SYSC_CLKENCFG_CRC;
}

/**
 * @brief get data CRC16
 *
 * @param pDat ：point data addr
 * @param u8DataType ： DATA_8BIT , DATA_16BIT , DATA_32BIT
 * @param u32Len  ：data len
 * @return u16 ：CRC16
 */
u16 CRC_Calculate(void *pDat, eDataType u8DataType, u32 u32Len) {
    int i;
    PARAM_CHECK((u8DataType != DATA_8BIT) && (u8DataType != DATA_16BIT) &&
                (u8DataType != DATA_32BIT));
    PARAM_CHECK(u32Len < 1);
    CRC_RSL_REG = 0xffff;
    switch (u8DataType) {
    case DATA_8BIT: {
        u8 *pDst = (u8 *)(&CRC_DAT_REG);
        u8 *pSrc = (u8 *)(pDat);
        for (i = 0; i < u32Len; ++i) {
            *pDst = *pSrc++;
        }
        break;
    }
    case DATA_16BIT: {
        u16 *pDst = (u16 *)(&CRC_DAT_REG);
        u16 *pSrc = (u16 *)(pDat);
        for (i = 0; i < u32Len; ++i) {
            *pDst = *pSrc++;
        }
        break;
    }
    case DATA_32BIT: {
        u32 *pSrc = (u32 *)(pDat);
        for (i = 0; i < u32Len; ++i) {
            CRC_DAT_REG = *pSrc++;
        }
        break;
    }
    default:
        break;
    }
    return CRC_RSL_REG & CRC_RSL_CRC16;
}

/**
 * @brief verify data
 *
 * @param pDat ：data addr
 * @param u8DataType ：DATA_8BIT , DATA_16BIT , DATA_32BIT
 * @param u32Len  ：data len
 * @return BOOL FALSE: 0 , TRUE 1;
 */
BOOL CRC_Check(void *pDat, eDataType u8DataType, u32 u32Len, u16 crc) {
    int i;
    PARAM_CHECK((u8DataType != DATA_8BIT) && (u8DataType != DATA_16BIT) &&
                (u8DataType != DATA_32BIT));
    PARAM_CHECK(u32Len < 1);
    CRC_RSL_REG = 0xffff;
    switch (u8DataType) {
    case DATA_8BIT: {
        u8 *pDst = (u8 *)(&CRC_DAT_REG);
        u8 *pSrc = (u8 *)(pDat);
        for (i = 0; i < u32Len; ++i) {
            *pDst = *pSrc++;
        }
        break;
    }
    case DATA_16BIT: {
        u16 *pDst = (u16 *)(&CRC_DAT_REG);
        u16 *pSrc = (u16 *)(pDat);
        for (i = 0; i < u32Len; ++i) {
            *pDst = *pSrc++;
        }
        break;
    }
    case DATA_32BIT: {
        u32 *pSrc = (u32 *)(pDat);
        for (i = 0; i < u32Len; ++i) {
            CRC_DAT_REG = *pSrc++;
        }
        break;
    }
    default:
        break;
    }
    *((u16 *)(&CRC_DAT_REG)) = crc;
    return (CRC_RSL_REG & CRC_RSL_CHKPSS) ? TRUE : FALSE;
}
