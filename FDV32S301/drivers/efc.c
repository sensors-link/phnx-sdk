/**
  ******************************************************************************
  * @file    efc.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-07
  * @brief   This file provides all the EFC firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "efc.h"
#include "sysc.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @defgroup EFC
  * @brief EFC driver modules
  * @{
  */

/** @defgroup EFC_Private_Defines
  * @{
  */

/* The OPR register of the EFC performs a specific sequence of operations */
#define EFC_OPR_OPEN(mode)                                                                                             \
	{                                                                                                                  \
		EFC->OPR = EFC_OPR_OPRF_V0 | (mode);                                                                           \
		EFC->OPR = EFC_OPR_OPRF_V1 | (mode);                                                                           \
		EFC->OPR = EFC_OPR_OPRF_V2 | (mode);                                                                           \
		EFC->OPR = EFC_OPR_OPRF_V3 | (mode);                                                                           \
	}
/**
  * @}
  */

/** @defgroup EFC_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the EFC peripheral.
  * @param  None
  * @retval result of initialization (TRUE or FALSE).
  */
BOOL EFC_Init(void)
{
	SYSC_ClocksTypeDef SYSC_Clocks;

	/* Get and check the system clock */
	SYSC_GetClocksFreq(&SYSC_Clocks);
	if (SYSC_Clocks.SYSCLK_Frequency < 1000000)
	{
		return FALSE;
	}

	/* Configure the relevant registers according to the system clock */
	if (SYSC_Clocks.SYSCLK_Frequency == 1000000)
	{
		/* System clock is 1MHz */
		/* The program clock is configured as 500kHz, and the erase clock is configured as 2kHz */
		EFC_WPT_UNLOCK();
		EFC->CR &= ~(EFC_CR_PRG2MDIV | EFC_CR_ERS2KDIV);
		EFC_WPT_UNLOCK();
		EFC->CR |= (1 << EFC_CR_PRG2MDIV_pos) | (0xF9 << EFC_CR_ERS2KDIV_pos);

		/* Tnvs time is configured as 6us */
		EFC_WPT_UNLOCK();
		EFC->TNVS &= ~EFC_TNVS_TNVS;
		EFC_WPT_UNLOCK();
		EFC->TNVS |= (0x03 << EFC_TNVS_TNVS_pos);

		/* Tprog time is configured as 6 us */
		EFC_WPT_UNLOCK();
		EFC->TPROG &= ~EFC_TPROG_TPROG;
		EFC_WPT_UNLOCK();
		EFC->TPROG |= (0x03 << EFC_TPROG_TPROG_pos);

		/* Tpgs time is configured as 6 us */
		EFC_WPT_UNLOCK();
		EFC->TPGS &= ~EFC_TPGS_TPGS;
		EFC_WPT_UNLOCK();
		EFC->TPGS |= (0x03 << EFC_TPGS_TPGS_pos);

		/* The Program Recovery Time is configured as 8us,
		   the Sector Erase Recovery Time is configured as 62us,
		   and the Chip Erase Recovery Time is configured as 242us */
		EFC_WPT_UNLOCK();
		EFC->TRCV &= ~(EFC_TRCV_TPRCV | EFC_TRCV_TSERCV | EFC_TRCV_TCERCV);
		EFC_WPT_UNLOCK();
		EFC->TRCV |= (0x4 << EFC_TRCV_TPRCV_pos) | (0x1F << EFC_TRCV_TSERCV_pos) | (0x79 << EFC_TRCV_TCERCV_pos);

		/* Sector Erase time is configured as 4.5ms, Chip Erase time is configured as 35ms */
		EFC_WPT_UNLOCK();
		EFC->TERS &= ~(EFC_TERS_TSERS | EFC_TERS_TCERS);
		EFC_WPT_UNLOCK();
		EFC->TERS |= (0x09 << EFC_TERS_TSERS_pos) | (0x46 << EFC_TERS_TCERS_pos);
	}
	else if (SYSC_Clocks.SYSCLK_Frequency == 2000000)
	{
		/* System clock is 2MHz */
		/* The program clock is configured as 1MHz, and the erase clock is configured as 2kHz */
		EFC_WPT_UNLOCK();
		EFC->CR &= ~(EFC_CR_PRG2MDIV | EFC_CR_ERS2KDIV);
		EFC_WPT_UNLOCK();
		EFC->CR |= (1 << EFC_CR_PRG2MDIV_pos) | (0x1F3 << EFC_CR_ERS2KDIV_pos);

		/* Tnvs time is configured as 6us */
		EFC_WPT_UNLOCK();
		EFC->TNVS &= ~EFC_TNVS_TNVS;
		EFC_WPT_UNLOCK();
		EFC->TNVS |= (0x06 << EFC_TNVS_TNVS_pos);

		/* Tprog time is configured as 6 us */
		EFC_WPT_UNLOCK();
		EFC->TPROG &= ~EFC_TPROG_TPROG;
		EFC_WPT_UNLOCK();
		EFC->TPROG |= (0x06 << EFC_TPROG_TPROG_pos);

		/* Tpgs time is configured as 6 us */
		EFC_WPT_UNLOCK();
		EFC->TPGS &= ~EFC_TPGS_TPGS;
		EFC_WPT_UNLOCK();
		EFC->TPGS |= (0x06 << EFC_TPGS_TPGS_pos);

		/* The Program Recovery Time is configured as 6us,
		   the Sector Erase Recovery Time is configured as 61us,
		   and the Chip Erase Recovery Time is configured as 241us */
		EFC_WPT_UNLOCK();
		EFC->TRCV &= ~(EFC_TRCV_TPRCV | EFC_TRCV_TSERCV | EFC_TRCV_TCERCV);
		EFC_WPT_UNLOCK();
		EFC->TRCV |= (0x6 << EFC_TRCV_TPRCV_pos) | (0x3D << EFC_TRCV_TSERCV_pos) | (0xF1 << EFC_TRCV_TCERCV_pos);

		/* Sector Erase time is configured as 4.5ms, Chip Erase time is configured as 35ms */
		EFC_WPT_UNLOCK();
		EFC->TERS &= ~(EFC_TERS_TSERS | EFC_TERS_TCERS);
		EFC_WPT_UNLOCK();
		EFC->TERS |= (0x09 << EFC_TERS_TSERS_pos) | (0x46 << EFC_TERS_TCERS_pos);
	}
	else
	{
		/* Is the other system clock */
		/* The program clock is configured as 2MHz, and the erase clock is configured as 2kHz */
		EFC_WPT_UNLOCK();
		EFC->CR &= ~(EFC_CR_PRG2MDIV | EFC_CR_ERS2KDIV);
		EFC_WPT_UNLOCK();
		EFC->CR |=
			((SYSC_Clocks.SYSCLK_Frequency / 2000000 - 1) << EFC_CR_PRG2MDIV_pos) | (0x3E7 << EFC_CR_ERS2KDIV_pos);

		/* Tnvs time is configured as 7us */
		EFC_WPT_UNLOCK();
		EFC->TNVS &= ~EFC_TNVS_TNVS;
		EFC_WPT_UNLOCK();
		EFC->TNVS |= (0x0E << EFC_TNVS_TNVS_pos);

		/* Tprog time is configured as 7 us */
		EFC_WPT_UNLOCK();
		EFC->TPROG &= ~EFC_TPROG_TPROG;
		EFC_WPT_UNLOCK();
		EFC->TPROG |= (0x0E << EFC_TPROG_TPROG_pos);

		/* Tpgs time is configured as 6 us */
		EFC_WPT_UNLOCK();
		EFC->TPGS &= ~EFC_TPGS_TPGS;
		EFC_WPT_UNLOCK();
		EFC->TPGS |= (0x0C << EFC_TPGS_TPGS_pos);

		/* The Program Recovery Time is configured as 6us,
		   the Sector Erase Recovery Time is configured as 60us,
		   and the Chip Erase Recovery Time is configured as 240us */
		EFC_WPT_UNLOCK();
		EFC->TRCV &= ~(EFC_TRCV_TPRCV | EFC_TRCV_TSERCV | EFC_TRCV_TCERCV);
		EFC_WPT_UNLOCK();
		EFC->TRCV |= (0xC << EFC_TRCV_TPRCV_pos) | (0x78 << EFC_TRCV_TSERCV_pos) | (0x1E0 << EFC_TRCV_TCERCV_pos);

		/* Sector Erase time is configured as 4.5ms, Chip Erase time is configured as 35ms */
		EFC_WPT_UNLOCK();
		EFC->TERS &= ~(EFC_TERS_TSERS | EFC_TERS_TCERS);
		EFC_WPT_UNLOCK();
		EFC->TERS |= (0x09 << EFC_TERS_TSERS_pos) | (0x46 << EFC_TERS_TCERS_pos);
	}

	return TRUE;
}

/**
  * @brief  Configure Margin Read Cycle.
  * @param  Cycle: Specify the margin reading period value.
  *	  This parameter value must be lower than 0x10.
  * @retval None
  */
void EFC_MarginReadCycleConfig(u8 Cycle)
{
	/* Check the parameters */
	PARAM_CHECK(IS_EFC_MRDCYC(Cycle));

	/* Set Margin Read Cycle */
	EFC_WPT_UNLOCK();
	EFC->CR &= ~EFC_CR_MRDCYC;
	EFC_WPT_UNLOCK();
	EFC->CR |= (Cycle << EFC_CR_MRDCYC_pos);
}

/**
  * @brief  Set CPU NVM Normal Read Delay.
  * @param  DelaySel: Selection of the number of cycles for the CPU to normally read data.
  *   This parameter can be one of the following values:
  *     @arg EFC_NRDDLY_0: CPU normally reads data without delay
  *     @arg EFC_NRDDLY_1: The CPU normally reads data with a delay of 1 cycle
  * @retval None
  */
void EFC_SetNormalReadDelay(u8 DelaySel)
{
	/* Check the parameters */
	PARAM_CHECK(IS_EFC_NRDDLY(DelaySel));

	if (DelaySel == EFC_NRDDLY_0)
	{
		/* Set the CPU to read data normally without delay */
		EFC_WPT_UNLOCK();
		EFC->CR &= ~EFC_CR_NRDDLY;
	}
	else
	{
		/* Set the CPU to normally read data with a delay of 1 cycle */
		EFC_WPT_UNLOCK();
		EFC->CR |= EFC_CR_NRDDLY;
	}
}

/**
  * @brief  Get address location of program verify read or erase verify read error.
  * @param  VerifyType: Specifies the type of verification read.
  *   This parameter can be one of the following values:
  *     @arg EFC_VERIFY_TYPE_ERASE: Erase Verify Read
  *     @arg EFC_VERIFY_TYPE_PRG: Program Verify Read
  * @retval wrong address location.
  */
u8 EFC_GetPVEVErrorAddr(u8 VerifyType)
{
	/* Check the parameters */
	PARAM_CHECK(IS_EFC_VERIFY_TYPE(VerifyType));

	/* Check the type of parity read */
	if (VerifyType == EFC_VERIFY_TYPE_ERASE)
	{
		/* Return to erase verify read error location */
		return (u8)((EFC->PVEV & EFC_PVEV_EVCNT) >> EFC_PVEV_EVCNT_pos);
	}
	else
	{
		/* Return to program verify read error location */
		return (u8)((EFC->PVEV & EFC_PVEV_PVCNT) >> EFC_PVEV_PVCNT_pos);
	}
}

/**
  * @brief  Execute the opcode flow of the corresponding mode.
  * @param  Mode: Specify the operating mode.
  *   This parameter can be one of the following values:
  *     @arg EFC_OPR_MODE_SIG_PRG: Single Program mode
  *     @arg EFC_OPR_MODE_ROW_PRG: Row Program mode
  *     @arg EFC_OPR_MODE_PAGE_ERASE: Page Erase mode
  *     @arg EFC_OPR_MODE_CHIP_ERASE: Chip Erase mode
  *     @arg EFC_OPR_MODE_PAGE_LOAD: Page Load mode
  *     @arg EFC_OPR_MODE_PE_VERIFY: Page Erase Verify Read mode
  *     @arg EFC_OPR_MODE_PP_VERIFY: Page Program Verify Read mode
  * @retval None
  */
void EFC_ExecuteModeFlow(u8 Mode)
{
	/* Check the parameters */
	PARAM_CHECK(IS_EFC_OPR_MODE(Mode));

	/* Set to perform a specific sequence of operations */
	EFC_OPR_OPEN(Mode);
}

/**
  * @brief  Enable or disable erase margin read.
  * @param  NewState: New state of erase margin read.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EFC_EraseMarginReadCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable erase margin read */
		EFC_WPT_UNLOCK();
		EFC->CR |= EFC_CR_EMRDEN;
	}
	else
	{
		/* Disable erase margin read */
		EFC_WPT_UNLOCK();
		EFC->CR &= ~EFC_CR_EMRDEN;
	}
}

/**
  * @brief  Enable or disable program margin read.
  * @param  NewState: New state of program margin read.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EFC_ProgramMarginReadCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable program margin read */
		EFC_WPT_UNLOCK();
		EFC->CR |= EFC_CR_PMRDEN;
	}
	else
	{
		/* Disable program margin read */
		EFC_WPT_UNLOCK();
		EFC->CR &= ~EFC_CR_PMRDEN;
	}
}

/**
  * @brief  Enable or disable terminate EFC erase and write when LVD alarms.
  * @param  NewState: New state of terminate EFC erase and write when LVD alarms.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EFC_LVDTerminateCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable terminate EFC erase and write when LVD alarms */
		EFC_WPT_UNLOCK();
		EFC->CR |= EFC_CR_LVDWARNEN;
	}
	else
	{
		/* Disable terminate EFC erase and write when LVD alarms */
		EFC_WPT_UNLOCK();
		EFC->CR &= ~EFC_CR_LVDWARNEN;
	}
}

/**
  * @brief  Enables or disables the specified EFC interrupts.
  * @param  EFC_IT: specifies the EFC interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg EFC_IT_ATDE: Analog Trim Data Error interrupt
  *     @arg EFC_IT_ATTE: Analog Trim Tag Error interrupt
  *     @arg EFC_IT_FTTE: Flash Trim Tag Error interrupt
  *     @arg EFC_IT_ADDRE: Address Error interrupt
  *     @arg EFC_IT_EVE: Page Erase Verify interrupt
  *     @arg EFC_IT_PVE: Page Program Verify interrupt
  *     @arg EFC_IT_FCE: Fault Command interrupt
  *     @arg EFC_IT_CD: Command Done interrupt
  * @param  NewState: new state of the specified EFC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EFC_ITConfig(u8 EFC_IT, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_EFC_CONFIG_IT(EFC_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the selected EFC interrupts */
		EFC_WPT_UNLOCK();
		EFC->CR |= EFC_IT;
	}
	else
	{
		/* Disable the selected EFC interrupts */
		EFC_WPT_UNLOCK();
		EFC->CR &= ~EFC_IT;
	}
}

/**
  * @brief  Checks whether the specified EFC flag is set or not.
  * @param  EFC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg EFC_FLAG_ATDE: Analog Trim Data Error flag
  *     @arg EFC_FLAG_ATTE: Analog Trim Tag Error flag
  *     @arg EFC_FLAG_FTTE: Flash Trim Tag Error flag
  *     @arg EFC_FLAG_ADDRE: Address Error flag
  *     @arg EFC_FLAG_EVE: Page Erase Verify flag
  *     @arg EFC_FLAG_PVE: Page Program Verify flag
  *     @arg EFC_FLAG_FCE: Fault Command flag
  *     @arg EFC_FLAG_CD: Command Done flag
  * @retval The new state of EFC_FLAG (SET or RESET).
  */
FlagStatus EFC_GetFlagStatus(u8 EFC_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_EFC_GET_FLAG(EFC_FLAG));

	/* Check the status of the EFC flag */
	if (EFC->STS & EFC_FLAG)
	{
		/* EFC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* EFC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the EFC_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified EFC interrupt has occurred or not.
  * @param  EFC_IT: specifies the EFC interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg EFC_IT_ATDE: Analog Trim Data Error interrupt
  *     @arg EFC_IT_ATTE: Analog Trim Tag Error interrupt
  *     @arg EFC_IT_FTTE: Flash Trim Tag Error interrupt
  *     @arg EFC_IT_ADDRE: Address Error interrupt
  *     @arg EFC_IT_EVE: Page Erase Verify interrupt
  *     @arg EFC_IT_PVE: Page Program Verify interrupt
  *     @arg EFC_IT_FCE: Fault Command interrupt
  *     @arg EFC_IT_CD: Command Done interrupt
  * @retval The new state of EFC_IT (SET or RESET).
  */
ITStatus EFC_GetITStatus(u8 EFC_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_EFC_GET_IT(EFC_IT));

	/* Check the status of the specified EFC interrupt */
	if ((EFC->CR & EFC_IT) && (EFC->STS & EFC_IT))
	{
		/* EFC_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* EFC_IT is reset */
		bitstatus = RESET;
	}
	/* Return the EFC_IT status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for EFC.
  * @param  EFC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg EFC_FLAG_ATDE: Analog Trim Data Error flag
  *     @arg EFC_FLAG_ATTE: Analog Trim Tag Error flag
  *     @arg EFC_FLAG_FTTE: Flash Trim Tag Error flag
  *     @arg EFC_FLAG_ADDRE: Address Error flag
  *     @arg EFC_FLAG_EVE: Page Erase Verify flag
  *     @arg EFC_FLAG_PVE: Page Program Verify flag
  *     @arg EFC_FLAG_FCE: Fault Command flag
  *     @arg EFC_FLAG_CD: Command Done flag
  * @retval None
  */
void EFC_ClearFlag(u8 EFC_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_EFC_CLEAR_FLAG(EFC_FLAG));

	/* Clear the selected EFC flags */
	EFC->STS = EFC_FLAG;
}

/**
  * @brief  Returns the EFC Status.
  * @param  None
  * @retval EFC Status, the return value can be one of @ref EFC_Status enumeration.
  */
EFC_Status EFC_GetEFCStatus(void)
{
	EFC_Status status = EFC_SUCCESS;

	if (!(EFC->STS))
	{
		/* No status flag to generate EFC exception */
		status = EFC_FAIL;
	}
	else if (EFC->STS & (~EFC_STS_CD))
	{
		/* There is an error flag generated */
		status = EFC_ERROR;
	}
	else
	{
		/* Operation completed normally */
		status = EFC_SUCCESS;
	}

	/* Return the EFC Status */
	return status;
}

/**
  * @brief  EFC single address programming.
  * @param  Addr: Specify the address to program.
  * @param  Data: specifies the data to be programmed.
  * @param  PrgType: Specifies the bit width type of the data to be programmed.
  *   This parameter can be one of @ref EFC_PrgType enumeration:
  *     @arg EFC_PRG_BYTE: single-byte programming
  *     @arg EFC_PRG_HWORD: halfword programming
  *     @arg EFC_PRG_WORD: whole word programming
  * @retval EFC processing result, the return value can be one of @ref EFC_Status enumeration.
  */
EFC_Status EFC_SingleProgram(u32 Addr, u32 Data, EFC_PrgType PrgType)
{
	u32		   tempreg = 0;
	EFC_Status status  = EFC_SUCCESS;

	/* Check the parameters */
	PARAM_CHECK(IS_EFC_MEM_ADDR(Addr));
	PARAM_CHECK(IS_EFC_PRG_TYPE(PrgType));

	/* Clear EFC Status Register */
	tempreg	 = EFC->STS;
	EFC->STS = tempreg;

	/* The OPR register of the EFC performs a single-address programming operation */
	EFC_OPR_OPEN(EFC_OPR_OPRMODE_SIG_PRG);

	/* Write data to the corresponding address */
	if (PrgType == EFC_PRG_BYTE)
	{
		/* byte programming */
		REG8(Addr) = Data;
	}
	else if (PrgType == EFC_PRG_HWORD)
	{
		/* half word programming */
		PARAM_CHECK(IS_HWORD_ADDR(Addr));
		REG16(Addr) = Data;
	}
	else
	{
		/* word programming */
		PARAM_CHECK(IS_WORD_ADDR(Addr));
		REG32(Addr) = Data;
	}

	/* Check for the EFC Status */
	status = EFC_GetEFCStatus();

	/* Return the Single Program Status */
	return status;
}

/**
  * @brief  EFC page address programming.
  * @note   Need to write save data to PAGE BUFFER first.
  * @param  Addr: Specify the address to page program.
  * @retval EFC processing result, the return value can be one of @ref EFC_Status enumeration.
  */
EFC_Status EFC_PageProgram(u32 Addr)
{
	u32		   tempreg = 0;
	EFC_Status status  = EFC_SUCCESS;

	/* Check the parameters */
	PARAM_CHECK(IS_PAGE_ADDR(Addr));
	PARAM_CHECK(IS_PAGE_PRG_ADDR(Addr));

	/* Clear EFC Status Register */
	tempreg	 = EFC->STS;
	EFC->STS = tempreg;

	/* The OPR register of the EFC performs a row programming operation */
	EFC_OPR_OPEN(EFC_OPR_OPRMODE_ROW_PRG);

	/* Write any value to the first row address */
	REG32(Addr) = 0xFFFFFFFF;

	/* Check for the EFC Status */
	status = EFC_GetEFCStatus();

	/* Check if the first write result is successful */
	if (status != EFC_SUCCESS)
	{
		return status;
	}

	/* Clear EFC Status Register */
	EFC->STS = EFC_STS_CD;

	/* The OPR register of the EFC performs a row programming operation */
	EFC_OPR_OPEN(EFC_OPR_OPRMODE_ROW_PRG);

	/* Write any value to the second row address */
	REG32(Addr + 256) = 0xFFFFFFFF;

	/* Check for the EFC Status */
	status = EFC_GetEFCStatus();

	/* Return the Page Program Status */
	return status;
}

/**
  * @brief  EFC erases the specified page.
  * @param  Addr: Specify the address to Page Erase.
  * @retval EFC processing result, the return value can be one of @ref EFC_Status enumeration.
  */
EFC_Status EFC_PageErase(u32 Addr)
{
	u32		   tempreg = 0;
	EFC_Status status  = EFC_SUCCESS;

	/* Check the parameters */
	PARAM_CHECK(IS_EFC_MEM_ADDR(Addr));

	/* Clear EFC Status Register */
	tempreg	 = EFC->STS;
	EFC->STS = tempreg;

	/* The OPR register of the EFC performs the page erase operation */
	EFC_OPR_OPEN(EFC_OPR_OPRMODE_PAGE_ERASE);

	/* Write any value to the corresponding address */
	REG32(Addr) = 0xFFFFFFFF;

	/* Check for the EFC Status */
	status = EFC_GetEFCStatus();

	/* Return the Page Erase Status */
	return status;
}

/**
  * @brief  EFC erases the chip.
  * @param  Addr: Specifies the address to chip erase.
  * @retval EFC processing result, the return value can be one of @ref EFC_Status enumeration.
  */
EFC_Status EFC_ChipErase(u32 Addr)
{
	u32		   tempreg = 0;
	EFC_Status status  = EFC_SUCCESS;

	/* Check the parameters */
	PARAM_CHECK(IS_EFC_MEM_ADDR(Addr));

	/* Clear EFC Status Register */
	tempreg	 = EFC->STS;
	EFC->STS = tempreg;

	/* The OPR register of the EFC performs the chip erase operation */
	EFC_OPR_OPEN(EFC_OPR_OPRMODE_CHIP_ERASE);

	/* Write any value to the corresponding address */
	REG32(Addr) = 0xFFFFFFFF;

	/* Check for the EFC Status */
	status = EFC_GetEFCStatus();

	/* Return the Chip Erase Status */
	return status;
}

/**
  * @brief  EFC loads a page of data into Page Buffer.
  * @note   Loaded data is saved in PAGE BUFFER.
  * @param  Addr: Specify the address to page load.
  * @retval EFC processing result, the return value can be one of @ref EFC_Status enumeration.
  */
EFC_Status EFC_PageLoad(u32 Addr)
{
	u32		   tempreg = 0;
	EFC_Status status  = EFC_SUCCESS;

	/* Check the parameters */
	PARAM_CHECK(IS_PAGE_ADDR(Addr));
	PARAM_CHECK(IS_PAGE_PRG_ADDR(Addr));

	/* Clear EFC Status Register */
	tempreg	 = EFC->STS;
	EFC->STS = tempreg;

	/* The OPR register of the EFC performs a page load operation */
	EFC_OPR_OPEN(EFC_OPR_OPRMODE_PAGE_LOAD);

	/* Write any value to the corresponding address */
	REG32(Addr) = 0xFFFFFFFF;

	/* Check for the EFC Status */
	status = EFC_GetEFCStatus();

	/* Return the Page Load Status */
	return status;
}

/**
  * @brief  EFC Page Erase Verification.
  * @param  Addr: Specify the address to Page Erase Verify.
  * @retval EFC processing result, the return value can be one of @ref EFC_Status enumeration.
  */
EFC_Status EFC_PageEraseVerify(u32 Addr)
{
	u32		   tempreg = 0;
	EFC_Status status  = EFC_SUCCESS;

	/* Check the parameters */
	PARAM_CHECK(IS_PAGE_ADDR(Addr));
	PARAM_CHECK(IS_PAGE_PRG_ADDR(Addr));

	/* Clear EFC Status Register */
	tempreg	 = EFC->STS;
	EFC->STS = tempreg;

	/* The OPR register of the EFC performs a page erase verification operation */
	EFC_OPR_OPEN(EFC_OPR_OPRMODE_PE_VERIFY);

	/* Write any value to the corresponding address */
	REG32(Addr) = 0xFFFFFFFF;

	/* Check for the EFC Status */
	status = EFC_GetEFCStatus();

	/* Return the Page Erase Verify Status */
	return status;
}

/**
  * @brief  EFC Page Program Verification.
  * @param  Addr: Specify the address to Page Program Verify
  * @retval EFC processing result, the return value can be one of @ref EFC_Status enumeration.
  */
EFC_Status EFC_PageProgramVerify(u32 Addr)
{
	u32		   tempreg = 0;
	EFC_Status status  = EFC_SUCCESS;

	/* Check the parameters */
	PARAM_CHECK(IS_PAGE_ADDR(Addr));
	PARAM_CHECK(IS_PAGE_PRG_ADDR(Addr));

	/* Clear EFC Status Register */
	tempreg	 = EFC->STS;
	EFC->STS = tempreg;

	/* The OPR register of the EFC performs a page programming verification operation */
	EFC_OPR_OPEN(EFC_OPR_OPRMODE_PP_VERIFY);

	/* Write any value to the corresponding address */
	REG32(Addr) = 0xFFFFFFFF;

	/* Check for the EFC Status */
	status = EFC_GetEFCStatus();

	/* Return the Program Verify Status */
	return status;
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

