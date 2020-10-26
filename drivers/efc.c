/**
 * @file efc.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "efc.h"

#define EFC_OPR_OPEN(mode)                                                     \
    {                                                                          \
        EFC_OPR_REG = EFC_OPR_PPRF_V0 | (mode);                                \
        EFC_OPR_REG = EFC_OPR_PPRF_V1 | (mode);                                \
        EFC_OPR_REG = EFC_OPR_PPRF_V2 | (mode);                                \
        EFC_OPR_REG = EFC_OPR_PPRF_V3 | (mode);                                \
    }

/**
 * @brief EFC init
 *
 * @return BOOL:TRUE , FALSE
 */
BOOL EFC_Init(void) {
    SystemCoreClockUpdate();
    if (SystemCoreClock < 1000000) {
        return FALSE;
    }
    if (SystemCoreClock == 1000000) {
        EFC_WPT_UNLOCK();
        EFC->CR &= ~(EFC_CR_PRG2MDIV | EFC_CR_ERS2KDIV);
        EFC_WPT_UNLOCK();
        EFC->CR |= (1 << 16) | (0xf9 << 22);
        // EFC_Txxx config
        EFC_WPT_UNLOCK();
        EFC->TNVS = 0x03; // 6us + 1*1 = 7us
        EFC_WPT_UNLOCK();
        EFC->TPROG = 0x03; // 6us + 1*1 = 7us
        EFC_WPT_UNLOCK();
        EFC->TPGS = 0x01; // 2us + 3*1 = 6us
        EFC_WPT_UNLOCK();
        EFC->TRCV = (0x4 << 16) | (0x1f << 9) | 0x79;
        EFC_WPT_UNLOCK();
        EFC->TERASE = (0x09 << 7) | 0x46;
    } else if (SystemCoreClock == 2000000) {
        EFC_WPT_UNLOCK();
        EFC->CR &= ~(EFC_CR_PRG2MDIV | EFC_CR_ERS2KDIV);
        EFC_WPT_UNLOCK();
        EFC->CR |= (1 << 16) | (0x1f3 << 22);
        // EFC_Txxx config
        EFC_WPT_UNLOCK();
        EFC->TNVS = 0x06; // 6us + 1*0.5 = 6.5us
        EFC_WPT_UNLOCK();
        EFC->TPROG = 0x06; // 6us + 1*0.5 = 6.5us
        EFC_WPT_UNLOCK();
        EFC->TPGS = 0x04; // 4us + 3*0.5 = 5.5us
        EFC_WPT_UNLOCK();
        EFC->TRCV = (0x6 << 16) | (0x3d << 9) | 0xf1;
        EFC_WPT_UNLOCK();
        EFC->TERASE = (0x09 << 7) | 0x46;
    } else {
        EFC_WPT_UNLOCK();
        EFC->CR &= ~(EFC_CR_PRG2MDIV | EFC_CR_ERS2KDIV);
        EFC_WPT_UNLOCK();
        EFC->CR |= ((SystemCoreClock / 2000000 - 1) << 16) | (0x3e7 << 22);
        EFC_WPT_UNLOCK();
        EFC->TNVS = 0x0e;
        EFC_WPT_UNLOCK();
        EFC->TPROG = 0x0e;
        EFC_WPT_UNLOCK();
        EFC->TPGS = 0x0c;
        EFC_WPT_UNLOCK();
        EFC->TRCV = 0xcf1e0;
        EFC_WPT_UNLOCK();
        EFC->TERASE = 0x4c6;
    }
    return TRUE;
}

/**
 * @brief program one data
 *
 * @param u32Addr :program address
 * @param iPrgType :EFC_PRG_BYTE , EFC_PRG_HWORD , EFC_PRG_WORD
 * @param Data programm data
 * @return eReturnType:: EFC_SUCCESS = 0  , EFC_SING_PRG_FAIL !=0;
 */
eReturnType EFC_SingleProgram(u32 Addr, int iPrgType, u32 Data) {
    PARAM_CHECK(
        (Addr < 0x10100000) || ((Addr > 0x1011ffff) && (Addr < 0x10140000)) ||
        ((Addr > 0x10140dff) && (Addr < 0x10180000)) || (Addr > 0x101803ff));
    u32 stat = EFC_STS_REG;
    EFC_STS_REG = stat;
    EFC_OPR_OPEN(EFC_OPR_OPRMODE_SIG_PRG);
    if (iPrgType == EFC_PRG_BYTE)
        REG8(Addr) = Data;
    else if (iPrgType == EFC_PRG_HWORD) {
        PARAM_CHECK(Addr & 0x01);
        REG16(Addr) = Data;
    } else {
        PARAM_CHECK(Addr & 0x03);
        REG32(Addr) = Data;
    }
    while (!EFC_STS_REG)
        ;
    if (EFC_STS_REG != EFC_STS_CD) {
        return EFC_SING_PRG_FAIL;
    }
    return EFC_SUCCESS;
}

/**
 * @brief page program
 *
 * @param u32Addr :address
 * @return eReturnType :EFC_SUCCESS = 0 , EFC_PAGE_PRG_FAIL !=0
 * @note :u32Addr page编程地址512Byte对齐, 仅仅 flash and nvr1-7 区域有效
 */
eReturnType EFC_PageProgram(u32 u32Addr) {
    PARAM_CHECK(u32Addr & 0x1ff);
    PARAM_CHECK((u32Addr < 0x10100000) ||
                ((u32Addr > 0x1011ffff) && (u32Addr < 0x10140000)) ||
                (u32Addr > 0x10140dff));
    u32 stat = EFC_STS_REG;
    EFC_STS_REG = stat;
    EFC_OPR_OPEN(EFC_OPR_OPRMODE_ROW_PRG);
    REG32(u32Addr) = 0xffffffff;
    while (!EFC_STS_REG)
        ;
    if (EFC_STS_REG != EFC_STS_CD) {
        return EFC_PAGE_PRG_FAIL;
    }
    EFC_STS_REG = EFC_STS_CD;
    EFC_OPR_OPEN(EFC_OPR_OPRMODE_ROW_PRG);
    REG32(u32Addr + 256) = 0xffffffff;
    while (!EFC_STS_REG)
        ;
    if (EFC_STS_REG != EFC_STS_CD) {
        return EFC_PAGE_PRG_FAIL;
    }
    return EFC_SUCCESS;
}
/**
 * @brief page erase
 *
 * @param u32Addr :address
 * @return eReturnType :EFC_SUCCESS (= 0) , EFC_PAGE_ERASE_FAIL (!=0)
 * @note:eeprom only erase one word（4Byte)
 */
eReturnType EFC_PageErase(u32 u32Addr) {
    PARAM_CHECK((u32Addr < 0x10100000) ||
                ((u32Addr > 0x1011ffff) && (u32Addr < 0x10140000)) ||
                ((u32Addr > 0x10140dff) && (u32Addr < 0x10180000)) ||
                (u32Addr > 0x101803ff));
    u32 stat = EFC_STS_REG;
    EFC_STS_REG = stat;
    EFC_OPR_OPEN(EFC_OPR_OPRMODE_PAGE_ERASE);
    REG32(u32Addr) = 0xffffffff;
    while (!EFC_STS_REG)
        ;
    if (EFC_STS_REG != EFC_STS_CD) {
        return EFC_PAGE_ERASE_FAIL;
    }
    return EFC_SUCCESS;
}

/**
 * @brief chip erase
 *
 * @param u32Addr :address
 * @return eReturnType :EFC_SUCCESS (=0) , EFC_CHIP_ERASE_FAIL (!=0)
 * @note: erase flash and nvr1-7,no nvr8 and eeprom
 */
eReturnType EFC_ChipErase(u32 u32Addr) {
    PARAM_CHECK((u32Addr < 0x10100000) ||
                ((u32Addr > 0x1011ffff) && (u32Addr < 0x10140000)) ||
                ((u32Addr > 0x10140dff) && (u32Addr < 0x10180000)) ||
                (u32Addr > 0x101803ff));
    u32 stat = EFC_STS_REG;
    EFC_STS_REG = stat;
    EFC_OPR_OPEN(EFC_OPR_OPRMODE_CHIP_ERASE);
    REG32(u32Addr) = 0xffffffff;
    while (!EFC_STS_REG)
        ;
    if (EFC_STS_REG != EFC_STS_CD) {
        return EFC_CHIP_ERASE_FAIL;
    }
    return EFC_SUCCESS;
}
/**
 * @brief :load page data to PageBuff
 *
 * @param u32Addr :address
 * @return eReturnType :EFC_SUCCESS (=0) , EFC_PAGE_LOAD_FAIL (!=0)
 * @note:u32Addr page (512Byte) align
 */
eReturnType EFC_PageLoad(u32 u32Addr) {
    PARAM_CHECK(u32Addr & 0x1ff);
    PARAM_CHECK((u32Addr < 0x10100000) ||
                ((u32Addr > 0x1011ffff) && (u32Addr < 0x10140000)) ||
                (u32Addr > 0x10140dff));
    u32 stat = EFC_STS_REG;
    EFC_STS_REG = stat;
    EFC_OPR_OPEN(EFC_OPR_OPRMODE_PAGE_LOAD);
    REG32(u32Addr) = 0xffffffff;
    while (!EFC_STS_REG)
        ;
    if (EFC_STS_REG != EFC_STS_CD) {
        return EFC_PAGE_LOAD_FAIL;
    }
    return EFC_SUCCESS;
}

/**
 * @brief :page erase verify
 *
 * @param u32Addr :address
 * @return eReturnType :EFC_SUCCESS (=0) , EFC_PE_VERIFY_FAIL (!=0)
 * @note:u32Addr page (512Byte) align
 */
eReturnType EFC_PageEraseVerify(u32 u32Addr) {
    PARAM_CHECK(u32Addr & 0x1ff);
    PARAM_CHECK((u32Addr < 0x10100000) ||
                ((u32Addr > 0x1011ffff) && (u32Addr < 0x10140000)) ||
                (u32Addr > 0x10140dff));
    u32 stat = EFC_STS_REG;
    EFC_STS_REG = stat;
    EFC_OPR_OPEN(EFC_OPR_OPRMODE_PE_V);
    REG32(u32Addr) = 0xffffffff;
    while (!EFC_STS_REG)
        ;
    if (EFC_STS_REG != EFC_STS_CD) {
        return EFC_PE_VERIFY_FAIL;
    }
    return EFC_SUCCESS;
}
/**
 * @brief :page program verify
 *
 * @param u32Addr :address
 * @return eReturnType :EFC_SUCCESS (=0) , EFC_PP_VERIFY_FAIL (!=0)
 * @note:u32Addr page (512Byte) align
 */
eReturnType EFC_ProgramVerify(u32 u32Addr) {
    PARAM_CHECK(u32Addr & 0x1ff);
    PARAM_CHECK((u32Addr < 0x10100000) ||
                ((u32Addr > 0x1011ffff) && (u32Addr < 0x10140000)) ||
                (u32Addr > 0x10140dff));
    u32 stat = EFC_STS_REG;
    EFC_STS_REG = stat;
    EFC_OPR_OPEN(EFC_OPR_OPRMODE_PP_V);
    REG32(u32Addr) = 0xffffffff;
    while (!EFC_STS_REG)
        ;
    if (EFC_STS_REG != EFC_STS_CD) {
        return EFC_PP_VERIFY_FAIL;
    }
    return EFC_SUCCESS;
}

/**
 * @brief: Flash write block data
 *
 * @param u32Addr : address
 * @param pu32Dat : data
 * @param u32Len : date length
 * @param u32PrgType EFC_FLASH_WRITE_WORD , EFC_FLASH_WRITE_PAGE
 * @return eReturnType
 * @note: addr page (512Byte) align,call page erase
 */
eReturnType EFC_FlashPageWrite(u32 u32Addr, u32 *pu32Dat, u32 u32Len,
                               u32 u32PrgType) {
    PARAM_CHECK(u32Addr & 0x1ff);
    PARAM_CHECK((u32Addr < 0x10100000) ||
                ((u32Addr > 0x1011ffff) && (u32Addr < 0x10140000)) ||
                (u32Addr > 0x10140dff));
    PARAM_CHECK(u32Len & 0x1ff);
    if (EFC_PageErase(u32Addr) != EFC_SUCCESS) {
        return EFC_PAGE_ERASE_FAIL;
    }
    if (EFC_PageEraseVerify(u32Addr) != EFC_SUCCESS) {
        return EFC_PE_VERIFY_FAIL;
    }
    if (u32PrgType == EFC_FLASH_WRITE_WORD) {
        int i;
        for (i = 0; i < u32Len; ++i) {
            if (EFC_SingleProgram(u32Addr + (i << 2), EFC_PRG_WORD, *pu32Dat) !=
                EFC_SUCCESS) {
                return EFC_SING_PRG_FAIL;
            }
            if (REG32(u32Addr + (i << 2)) != *pu32Dat) {
                return EFC_FLASH_WRITE_FAIL;
            }
            ++pu32Dat;
        }
    } else {
        int i;
        for (i = 0; i < u32Len; ++i) {
            REG32(PAGE_BUFF_BASE + (i << 2)) = *pu32Dat;
        }
        if (EFC_PageProgram(u32Addr) != EFC_SUCCESS) {
            return EFC_FLASH_WRITE_FAIL;
        }
        if (EFC_ProgramVerify(u32Addr) != EFC_SUCCESS) {
            return EFC_PP_VERIFY_FAIL;
        }
    }
    return EFC_SUCCESS;
}

/**
 * @brief :eeprom write one data
 *
 * @param addr:addr
 * @param data :data
 * @param iPrgType :EFC_PRG_BYTE , EFC_PRG_HWORD , EFC_PRG_WORD
 * @return BOOL:TRUE , FALSE
 */
BOOL EFC_EEPROMWrite(u32 addr, u32 data, int iPrgType) {
    PARAM_CHECK((addr < 0x10180000) || (addr > 0x101803ff));
    if (EFC_PageErase(addr) != EFC_SUCCESS) {
        return FALSE;
    }
    if (REG32(addr) != 0xffffffff)
        return FALSE;
    EFC_SingleProgram(addr, iPrgType, data);
    if (iPrgType == EFC_PRG_BYTE) {
        if (REG8(addr) != (data & 0xff))
            return FALSE;
    } else if (iPrgType == EFC_PRG_HWORD) {
        if (REG16(addr) != (data & 0xffff))
            return FALSE;
    } else {
        if (REG32(addr) != data)
            return FALSE;
    }

    return TRUE;
}
