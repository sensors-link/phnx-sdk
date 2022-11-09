/**
  ******************************************************************************
  * @file    efc.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-07
  * @brief   This file contains all functional prototypes of the EFC firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EFC_H__
#define __EFC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx04.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @addtogroup EFC
  * @{
  */

/** @defgroup EFC_module_register_bit_definition
  * @{
  */

/* EFC_CR */
#define EFC_CR_ERS2KDIV	  BITS(22, 31)
#define EFC_CR_PRG2MDIV	  BITS(16, 21)
#define EFC_CR_MRDCYC	  BITS(12, 15)
#define EFC_CR_LVDWARNEN  BIT(8)
#define EFC_CR_ATDEINTEN  BIT(7)
#define EFC_CR_ATTEINTEN  BIT(6)
#define EFC_CR_FTTEINTEN  BIT(5)
#define EFC_CR_ADDREINTEN BIT(4)
#define EFC_CR_FCINTEN	  BIT(1)
#define EFC_CR_CDINTEN	  BIT(0)

#define EFC_CR_ERS2KDIV_pos (22)
#define EFC_CR_PRG2MDIV_pos (16)
#define EFC_CR_MRDCYC_pos	(12)

/* EFC_TNVS */
#define EFC_TNVS_TNVS BITS(0, 3)

#define EFC_TNVS_TNVS_pos (0)

/* EFC_TPROG */
#define EFC_TPROG_TPROG BITS(0, 3)

#define EFC_TPROG_TPROG_pos (0)

/* EFC_TPGS */
#define EFC_TPGS_TPGS BITS(0, 3)

#define EFC_TPGS_TPGS_pos (0)

/* EFC_TRCV */
#define EFC_TRCV_TPRCV	BITS(16, 19)
#define EFC_TRCV_TSERCV BITS(9, 15)
#define EFC_TRCV_TCERCV BITS(0, 8)

#define EFC_TRCV_TPRCV_pos	(16)
#define EFC_TRCV_TSERCV_pos (9)
#define EFC_TRCV_TCERCV_pos (0)

/* EFC_TERS */
#define EFC_TERS_TSERS BITS(7, 10)
#define EFC_TERS_TCERS BITS(0, 6)

#define EFC_TERS_TSERS_pos (7)
#define EFC_TERS_TCERS_pos (0)

/* EFC_OPR */
#define EFC_OPR_WE		BIT(7)
#define EFC_OPR_OPRF	BITS(4, 6)
#define EFC_OPR_OPRMODE BITS(0, 3)

#define EFC_OPR_OPRF_V0 (0x00 << 4)
#define EFC_OPR_OPRF_V1 (0x07 << 4)
#define EFC_OPR_OPRF_V2 (0x09 << 4)
#define EFC_OPR_OPRF_V3 (0x0c << 4)

#define EFC_OPR_OPRMODE_SIG_PRG	    (0 << 0)
#define EFC_OPR_OPRMODE_BLOCK_ERASE (1 << 0)
#define EFC_OPR_OPRMODE_PAGE_ERASE  (2 << 0)
#define EFC_OPR_OPRMODE_CHIP_ERASE  (3 << 0)

#define EFC_OPR_OPRF_pos	(4)
#define EFC_OPR_OPRMODE_pos (0)

/* EFC_STS */
#define EFC_STS_ATDE  BIT(7)
#define EFC_STS_ATTE  BIT(6)
#define EFC_STS_FTTE  BIT(5)
#define EFC_STS_ADDRE BIT(4)
#define EFC_STS_FCE	  BIT(1)
#define EFC_STS_CD	  BIT(0)

/**
  * @}
  */

/** @defgroup EFC_Exported_Types
  * @{
  */

/**
  * @brief EFC programming bit width type enumeration
  */

typedef enum
{
	EFC_PRG_BYTE = 0,
	EFC_PRG_HWORD,
	EFC_PRG_WORD
} EFC_PrgType;

#define IS_EFC_PRG_TYPE(TYPE) (((TYPE) == EFC_PRG_BYTE) || ((TYPE) == EFC_PRG_HWORD) || ((TYPE) == EFC_PRG_WORD))

/**
  * @brief EFC state enumeration
  */

typedef enum
{
	EFC_ERROR,
	EFC_FAIL,
	EFC_SUCCESS
} EFC_Status;

/**
  * @}
  */

/** @defgroup EFC_Exported_Constants
  * @{
  */

/**
  * @defgroup EFC_write_protection_unlock
  * @{
  */

#define EFC_WPT_VALUE_0 (0xC3)
#define EFC_WPT_VALUE_1 (0x3C)
#define EFC_WPT_UNLOCK()                                                                                               \
	{                                                                                                                  \
		EFC->WPT = EFC_WPT_VALUE_0;                                                                                    \
		EFC->WPT = EFC_WPT_VALUE_1;                                                                                    \
	}
/**
  * @}
  */

/**
  * @defgroup EFC_Margin_Read_Cycle
  * @{
  */

#define IS_EFC_MRDCYC(MRDCYC) ((MRDCYC) <= 0x0F)
/**
  * @}
  */

/**
  * @defgroup EFC_Operate_mode
  * @{
  */

#define EFC_OPR_MODE_SIG_PRG	 (0)
#define EFC_OPR_MODE_BLOCK_ERASE (1)
#define EFC_OPR_MODE_PAGE_ERASE  (2)
#define EFC_OPR_MODE_CHIP_ERASE  (3)

#define IS_EFC_OPR_MODE(MODE)                                                                                          \
	(((MODE) == EFC_OPR_MODE_SIG_PRG) || ((MODE) == EFC_OPR_MODE_BLOCK_ERASE) || 									   \
	 ((MODE) == EFC_OPR_MODE_PAGE_ERASE) || ((MODE) == EFC_OPR_MODE_CHIP_ERASE))
/**
  * @}
  */

/**
  * @defgroup EFC_Interrupt_definition
  * @{
  */

#define EFC_IT_ATDE	 BIT(7)
#define EFC_IT_ATTE	 BIT(6)
#define EFC_IT_FTTE	 BIT(5)
#define EFC_IT_ADDRE BIT(4)
#define EFC_IT_FCE	 BIT(1)
#define EFC_IT_CD	 BIT(0)

#define EFC_IT_ALL                                                                                                     \
	(EFC_IT_ATDE | EFC_IT_ATTE | EFC_IT_FTTE | EFC_IT_ADDRE | EFC_IT_FCE | EFC_IT_CD)

#define IS_EFC_CONFIG_IT(IT) (((IT)&EFC_IT_ALL) && (!((IT) & (~(EFC_IT_ALL)))))

#define IS_EFC_GET_IT(IT)                                                                                              \
	(((IT) == EFC_IT_ATDE) || ((IT) == EFC_IT_ATTE) || ((IT) == EFC_IT_FTTE) || ((IT) == EFC_IT_ADDRE) ||              \
	 ((IT) == EFC_IT_FCE) || ((IT) == EFC_IT_CD))
/**
  * @}
  */

/**
  * @defgroup EFC_flags_definition
  * @{
  */

#define EFC_FLAG_ATDE  BIT(7)
#define EFC_FLAG_ATTE  BIT(6)
#define EFC_FLAG_FTTE  BIT(5)
#define EFC_FLAG_ADDRE BIT(4)
#define EFC_FLAG_FCE   BIT(1)
#define EFC_FLAG_CD	   BIT(0)

#define EFC_FLAG_ALL                                                                                                   \
	(EFC_FLAG_ATDE | EFC_FLAG_ATTE | EFC_FLAG_FTTE | EFC_FLAG_ADDRE | EFC_FLAG_FCE | EFC_FLAG_CD)

#define IS_EFC_GET_FLAG(FLAG)                                                                                          \
	(((FLAG) == EFC_FLAG_ATDE) || ((FLAG) == EFC_FLAG_ATTE) || ((FLAG) == EFC_FLAG_FTTE) ||                            \
	 ((FLAG) == EFC_FLAG_ADDRE) || ((FLAG) == EFC_FLAG_FCE) || ((FLAG) == EFC_FLAG_CD))

#define IS_EFC_CLEAR_FLAG(FLAG) (((FLAG) & EFC_FLAG_ALL) && (!((FLAG) & (~(EFC_FLAG_ALL)))))
/**
  * @}
  */

/**
  * @defgroup EFC_memory_address
  * @{
  */

#define IS_EFC_MEM_ADDR(ADDRESS)                                                                                       \
	((((ADDRESS) >= 0x10100000) && ((ADDRESS) < 0x10108000)) ||                                                        \
	 (((ADDRESS) >= 0x10140000) && ((ADDRESS) < 0x10140400)) ||                                                        \
	 (((ADDRESS) >= 0x10180000) && ((ADDRESS) < 0x10180800)))
/**
  * @}
  */

/**
  * @defgroup EFC_EEPROM_address
  * @{
  */

#define IS_EFC_EEPROM_ADDR(ADDRESS) (((ADDRESS) >= 0x10180000) && ((ADDRESS) < 0x10180800))

/**
  * @}
  */

/**
  * @defgroup EFC_Half_word_address
  * @{
  */

#define IS_HWORD_ADDR(ADDRESS) (!((ADDRESS)&0x01))
/**
  * @}
  */

/**
  * @defgroup EFC_Whole_word_address
  * @{
  */

#define IS_WORD_ADDR(ADDRESS) (!((ADDRESS)&0x03))
/**
  * @}
  */

/**
  * @defgroup EFC_Whole_page_address
  * @{
  */

#define IS_PAGE_ADDR(ADDRESS) (!((ADDRESS)&0x1FF))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup EFC_Exported_Functions
  * @{
  */

BOOL	   EFC_Init(void);
void	   EFC_MarginReadCycleConfig(u8 Cycle);
void	   EFC_ExecuteModeFlow(u8 Mode);
void	   EFC_LVDTerminateCmd(FunctionalState NewState);
void	   EFC_ITConfig(u8 EFC_IT, FunctionalState NewState);
FlagStatus EFC_GetFlagStatus(u8 EFC_FLAG);
ITStatus   EFC_GetITStatus(u8 EFC_IT);
void	   EFC_ClearFlag(u8 EFC_FLAG);
EFC_Status EFC_GetEFCStatus(void);
EFC_Status EFC_SingleProgram(u32 Addr, u32 Data, EFC_PrgType PrgType);
EFC_Status EFC_BlockErase(u32 Addr);
EFC_Status EFC_PageErase(u32 Addr);
EFC_Status EFC_ChipErase(u32 Addr);

#ifdef __cplusplus
}
#endif

#endif /*__EFC_H__*/

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

