/**
 * @file   efc.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __EFC_H__
#define __EFC_H__
#include "phnx05.h"

/*register bit definitions */
// EFCCR
#define EFC_CR_ERS2KDIV	  BITS(22, 31)
#define EFC_CR_PRG2MDIV	  BITS(16, 21)
#define EFC_CR_LVDWARNEN  BIT(8)
#define EFC_CR_ATDEINTEN  BIT(7)
#define EFC_CR_ATTEINTEN  BIT(6)
#define EFC_CR_FTTEINTEN  BIT(5)
#define EFC_CR_ADDREINTEN BIT(4)
#define EFC_CR_FCINTEN	  BIT(1)
#define EFC_CR_CDINTEN	  BIT(0)

// EFC_TNVS
#define EFC_TNVS BITS(0, 3)

// EFC_TPROG
#define EFC_TPROG BITS(0, 3)

// EFC_TPGS
#define EFC_TPGS BITS(0, 3)

// EFC_TRCV
#define EFC_TRCV_TPRCV	BITS(16, 19)
#define EFC_TRCV_TSERCV BITS(9, 15)
#define EFC_TRCV_TCERCV BITS(0, 8)

// EFC_TERASE
#define EFC_TERASE_TSERS BITS(7, 10)
#define EFC_TERASE_TCERS BITS(0, 6)

// EFC_WPT
#define EFC_WPT BITS(0, 7)

#define EFC_WPT_VALUE_0 (0xC3)
#define EFC_WPT_VALUE_1 (0x3C)
// EFC WPT unlock function
#define EFC_WPT_UNLOCK()                                                                                               \
	{                                                                                                                  \
		EFC->WPT = EFC_WPT_VALUE_0;                                                                                    \
		EFC->WPT = EFC_WPT_VALUE_1;                                                                                    \
	}

// EFC_OPR
#define EFC_OPR_WE		BIT(7)
#define EFC_OPR_OPRF	BITS(4, 6)
#define EFC_OPR_OPRMODE BITS(0, 3)

#define EFC_OPR_PPRF_V0 (0x00 << 4)
#define EFC_OPR_PPRF_V1 (0x07 << 4)
#define EFC_OPR_PPRF_V2 (0x09 << 4)
#define EFC_OPR_PPRF_V3 (0x0c << 4)

#define EFC_OPR_OPRMODE_SIG_PRG	   (0)
#define EFC_OPR_OPRMODE_REV		   (1)
#define EFC_OPR_OPRMODE_PAGE_ERASE (2)
#define EFC_OPR_OPRMODE_CHIP_ERASE (3)

// EFC_STS
#define EFC_STS_ATDE  BIT(7)
#define EFC_STS_ATTE  BIT(6)
#define EFC_STS_FTTE  BIT(5)
#define EFC_STS_ADDRE BIT(4)
#define EFC_STS_FCE	  BIT(1)
#define EFC_STS_CD	  BIT(0)

// data type define
typedef enum _EFC_RETURN_TYPE
{
	EFC_SUCCESS = 0,
	EFC_SING_PRG_FAIL,
	EFC_PAGE_PRG_FAIL,
	EFC_PAGE_ERASE_FAIL,
	EFC_CHIP_ERASE_FAIL,
	EFC_PAGE_LOAD_FAIL,
	EFC_PE_VERIFY_FAIL,
	EFC_PP_VERIFY_FAIL,
	EFC_FLASH_WRITE_FAIL,
} eReturnType;

#define EFC_PRG_BYTE  (0)
#define EFC_PRG_HWORD (1)
#define EFC_PRG_WORD  (2)

#define EFC_FLASH_WRITE_WORD (1)
#define EFC_FLASH_WRITE_PAGE (0)

// efc function declare
BOOL		EFC_Init(void);
eReturnType EFC_SingleProgram(u32 Addr, int iPrgType, u32 Data);
eReturnType EFC_PageErase(u32 u32Addr);
eReturnType EFC_ChipErase(u32 u32Addr);
eReturnType EFC_FlashPageWrite(u32 u32Addr, u32 *pu32Dat, u32 u32Len, u32 u32PrgType);
BOOL		EFC_EEPROMWrite(u32 addr, u32 data, int iPrgType);

#endif /* __EFC_H__ */
