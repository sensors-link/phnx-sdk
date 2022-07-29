/**
 * @file twc.c
 * @author wyd
 * @brief
 * @version 0.1
 * @date 2021-07-19
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#include "twc.h"
#include "sysc.h"
#include "anac.h"
#include "iom.h"

/**
 * @brief twc init
 *
 * @param pin:TWC_PIN_18_19 , TWC_PIN_04_05
 */
void TWC_Init(int pin)
{
	int i;
	PARAM_CHECK((pin != TWC_PIN_18_19) && (pin != TWC_PIN_04_05));
	SYSC->CLKENCFG |= SYSC_CLKENCFG_IOM;
	if (pin == TWC_PIN_18_19)
	{
		IOM->AF1 &= ~(IOM_AF1_P18_SEL | IOM_AF1_P19_SEL);
		IOM->AF1 |= (IOM_AF1_P18_SEL_TWC_RX | IOM_AF1_P19_SEL_TWC_TX);
	}
	else
	{
		IOM->AF0 &= ~(IOM_AF0_P04_SEL | IOM_AF0_P05_SEL);
		IOM->AF0 |= (IOM_AF0_P04_SEL_TWC_RX | IOM_AF0_P05_SEL_TWC_TX);
	}
	ANAC_WPT_UNLOCK();
	ANAC->CLK_CFG |= ANAC_CLK_CFG_MRC_EN;
	for (i = 1000; i > 0; --i)
		;

	SYSC->CLKENCFG |= SYSC_CLKENCFG_TWC;
	SYSC->CLKENCFG |= SYSC_CLKENCFG_TWC_MRCK;
}

/**
 * @brief twc deinit
 *
 */
void TWC_DeInit(void)
{
	int i;
	SYSC_WPT_UNLOCK();
	SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_TWC;
	for (i = 10; i > 0; --i)
		;

	ANAC_WPT_UNLOCK();
	ANAC->CLK_CFG &= ~ANAC_CLK_CFG_MRC_EN;
	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TWC;
	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TWC_MRCK;
}

/**
 * @brief recieve data enable control
 *
 * @param clt :ENABLE , DISABLE
 */
void TWC_RecieveControl(ControlStatus clt)
{
	if (clt == ENABLE)
	{
		TWC->CR |= TWC_CR_RXRECEN;
	}
	else
	{
		TWC->CR &= ~TWC_CR_RXRECEN;
	}
}

/**
 * @brief 接收反向控制
 *
 * @param clt :ENABLE , DISABLE
 */
void TWC_RecieveReverseControl(ControlStatus clt)
{
	if (clt == ENABLE)
	{
		TWC->CR |= TWC_CR_RX_INV_CFG;
	}
	else
	{
		TWC->CR &= ~TWC_CR_RX_INV_CFG;
	}
}

/**
 * @brief sebus configure
 *
 * @param mode :TWC_MODE_9000 , TWC_MODE_EPC
 * @param txLelCfg :TWC_TX_LEVEL_HIGH_EN , TWC_TX_LEVEL_LOW_EN
 * @param rxDecCfg :TWC_RX_DEC_MATCH_CMD_INT , TWC_RX_DEC_NO_MT_CMD_INT
 * @param rxGlitchFiltCfg:TWC_RX_FILT_NO , TWC_RX_FILT_2N_CYCLE(n)
 * @note :sebus verify check even
 */
void TWC_SEBUSConfig(int mode, int txLelCfg, int rxDecCfg, int rxGlitchFiltCfg)
{
	PARAM_CHECK((mode != TWC_MODE_9000) && (mode != TWC_MODE_EPC));
	PARAM_CHECK((txLelCfg != TWC_TX_LEVEL_HIGH_EN) && (txLelCfg != TWC_TX_LEVEL_LOW_EN));
	PARAM_CHECK((rxDecCfg != TWC_RX_DEC_MATCH_CMD_INT) && (rxDecCfg != TWC_RX_DEC_NO_MT_CMD_INT));
	PARAM_CHECK(rxGlitchFiltCfg > 15);
	if (mode == TWC_MODE_9000)
	{
		TWC->CR &= ~TWC_CR_SEBUSMODE;
	}
	else
	{
		TWC->CR |= TWC_CR_SEBUSMODE;
	}
	if (txLelCfg == TWC_TX_LEVEL_HIGH_EN)
	{
		TWC->CR |= TWC_CR_TXLELCFG;
	}
	else
	{
		TWC->CR &= ~TWC_CR_TXLELCFG;
	}
	if (rxDecCfg == TWC_RX_DEC_NO_MT_CMD_INT)
	{
		TWC->CR |= TWC_CR_RXDECCFG;
	}
	else
	{
		TWC->CR &= ~TWC_CR_RXDECCFG;
	}
	TWC->CR &= ~TWC_CR_RXGLITCHFILTCFG;
	TWC->CR |= rxGlitchFiltCfg | TWC_CR_SEBUSEN;
}
/**
 * @brief set gap and gap comp time
 *
 * @param gap : 0<gap<256
 * @param gapComp:: 0<gapComp<128
 * @note:unit us,(val*10/6)us
 */
void TWC_SetGapAndGapComp(int gap, int gapComp)
{
	PARAM_CHECK((gap < 1) || (gap > 255));
	PARAM_CHECK((gapComp < 1) || (gapComp > 127));
	TWC->GAPW = (gapComp << TWC_GAPW_GAPCOMP_pos) | gap;
}
/**
 * @brief swanbus configure
 *
 * @param txBaud :TWC_SWBR_TXBR_xxK
 * @param rxBaud :TWC_SWBR_RXBR_xxK
 * @param pParam :sSwanBusCfgParam
 */
void TWC_SWANBusConfig(int txBaud, int rxBaud, sSwanBusCfgParam *pParam)
{
	TWC->SWBR = txBaud | rxBaud;
	PARAM_CHECK((pParam->txLelCfg != TWC_TX_LEVEL_HIGH_EN) && (pParam->txLelCfg != TWC_TX_LEVEL_LOW_EN));
	PARAM_CHECK((pParam->rxDecCfg != TWC_RX_DEC_MATCH_CMD_INT) && (pParam->rxDecCfg != TWC_RX_DEC_NO_MT_CMD_INT));
	PARAM_CHECK(pParam->rxGlitchFiltCfg > 15);
	if (pParam->txLelCfg == TWC_TX_LEVEL_HIGH_EN)
	{
		TWC->CR |= TWC_CR_TXLELCFG;
	}
	else
	{
		TWC->CR &= ~TWC_CR_TXLELCFG;
	}
	if (pParam->rxDecCfg == TWC_RX_DEC_NO_MT_CMD_INT)
	{
		TWC->CR |= TWC_CR_RXDECCFG;
	}
	else
	{
		TWC->CR &= ~TWC_CR_RXDECCFG;
	}
	TWC->CR &= ~(TWC_CR_RXGLITCHFILTCFG | TWC_CR_SEBUSEN);
	TWC->CR |= pParam->rxGlitchFiltCfg;

	PARAM_CHECK((pParam->rxParityCfg != TWC_RX_PARITY_HMM) && (pParam->rxParityCfg != TWC_RX_PARITY_EVEN));
	PARAM_CHECK((pParam->txCodeCfg != TWC_TX_CODE_MCT) && (pParam->txCodeCfg != TWC_TX_CODE_NRZ));
	PARAM_CHECK((pParam->txParityCfg != TWC_TX_PARITY_EVEN) && (pParam->txParityCfg != TWC_TX_PARITY_ODD));
	PARAM_CHECK(pParam->txBitCfg > 3);
	if (pParam->rxParityCfg == TWC_RX_PARITY_HMM)
	{
		TWC->SWCR |= TWC_SWCR_RXPARITYCFG;
	}
	else
	{
		TWC->SWCR &= ~TWC_SWCR_RXPARITYCFG;
	}
	if (pParam->txCodeCfg == TWC_TX_CODE_MCT)
	{
		TWC->SWCR |= TWC_SWCR_TXCODECFG;
	}
	else
	{
		TWC->SWCR &= ~TWC_SWCR_TXCODECFG;
	}
	if (pParam->txParityCfg == TWC_TX_PARITY_ODD)
	{
		TWC->SWCR |= TWC_SWCR_TXPARITYCFG;
	}
	else
	{
		TWC->SWCR &= ~TWC_SWCR_TXPARITYCFG;
	}
	TWC->SWCR &= ~TWC_SWCR_TXBITCFG;
	TWC->SWCR |= pParam->txBitCfg;
}

/**
 * @brief 硬件接收解码使能控制
 *
 * @param ctl:ENABLE or DISABLE
 */
void TWC_RecieveEncodeControl(ControlStatus ctl)
{
	if (ctl == ENABLE)
	{
		TWC->CR |= TWC_CR_RXRECEN;
	}
	else
	{
		TWC->CR &= ~TWC_CR_RXRECEN;
	}
}

/**
 * @brief set cmd1-3 register  cmd and mask
 *
 * @param cmdRegNo :TWC_CMD_1  , TWC_CMD_2 , TWC_CMD_3 , TWC_CMD_4, TWC_CMD_5,
 * TWC_CMD_6
 * @param cmd :cmd value
 * @param msk :mask value
 * @note :mask set all 1 , cmd novalid
 */
void TWC_SetCMDAndMask(int cmdRegNo, u16 cmd, u16 msk)
{
	PARAM_CHECK(cmdRegNo > 3);
	switch (cmdRegNo)
	{
	case TWC_CMD_1:
		TWC->CMD1 = (cmd << 16) | msk;
		break;
	case TWC_CMD_2:
		TWC->CMD2 = (cmd << 16) | msk;
		break;
	case TWC_CMD_3:
		TWC->CMD3 = (cmd << 16) | msk;
		break;
	case TWC_CMD_4:
		TWC->CMD4 = (cmd << 16) | msk;
		break;
	case TWC_CMD_5:
		TWC->CMD5 = (cmd << 16) | msk;
		break;
	case TWC_CMD_6:
		TWC->CMD6 = (cmd << 16) | msk;
		break;
	}
}

/**
 * @brief: recieve data
 *
 * @return u32:data
 */
u32 TWC_ReadData(void)
{
	return TWC->RXD;
}

/**
 * @brief send data
 *
 * @param dat :data
 */
void TWC_WriteData(u32 dat)
{
	TWC->TXD = dat;
}

/**
 * @brief send data enalbe
 *
 */
void TWC_SendEnable(void)
{
	TWC->TXS |= TWC_TXS_DATATXEN;
}

/**
 * @brief send data disable
 *
 */
void TWC_SendDisable(void)
{
	TWC->TXS &= ~TWC_TXS_DATATXEN;
}

/**
 * @brief :swan bus send start
 *@param clt : ENABLE, DISABLE
 */
void TWC_SwanBusSendStartConfig(ControlStatus clt)
{
	if (clt == ENABLE)
		TWC->TXS |= TWC_TXS_TXSTART;
	else
		TWC->TXS &= ~TWC_TXS_TXSTART;
}

/**
 * @brief:enable interrupt
 *
 * @param :val TWC_RX_FRAME_END | TWC_TX_FRAME_END ,支持或操作一次设置多个
 */
void TWC_EnableIRQControl(eTansferEnd_Type val)
{
	TWC->INTEN = val;
}

/**
 * @brief:Clear interrupt flag
 *
 * @param :val TWC_RX_FRAME_END | TWC_TX_FRAME_END ,支持或操作一次设置多个
 */
void TWC_ClrIntFlag(eTansferEnd_Type val)
{
	TWC->STS = val;
}

/**
 * @brief 获得状态寄存器数据
 *
 * @return u32
 */
u32 TWC_GetStatusRegData(void)
{
	return TWC->STS;
}
