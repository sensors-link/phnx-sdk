/**
 * @file spi.c
 * @author wyd
 * @brief
 * @version 0.1
 * @date 2021-07-16
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "spi.h"
#include "sysc.h"
#include "iom.h"

/**
 * @brief  SPI init
 * @param mode:SPI_MASTER , SPI_SLAVE
 * @param pol:SPI_CPOL_HIGH , SPI_CPOL_LOW
 * @param phase:SPI_CPHA_FIST , SPI_CPHA_MIDD
 * @param freq :set N (Hz)
 * @note 分频系数有限只能是最接近的频率设置
 */
void SPI_Init(int mode, int pol, int phase, int freq)
{
	int div = 0;
	int tmp = 0;

	SYSC->CLKENCFG |= SYSC_CLKENCFG_SPI;

	PARAM_CHECK((pol != SPI_CPOL_HIGH) && (pol != SPI_CPOL_LOW));
	PARAM_CHECK((phase != SPI_CPHA_FIST) && (phase != SPI_CPHA_MIDD));
	PARAM_CHECK((mode != SPI_SR_MSTCFSR) && (mode != SPI_SLAVE));

	if (pol == SPI_CPOL_HIGH)
		SPI->CR0 |= SPI_CR0_CPOL;
	else
		SPI->CR0 &= ~SPI_CR0_CPOL;


	if (phase == SPI_CPHA_MIDD)
		SPI->CR0 |= SPI_CR0_CPHA;
	else
		SPI->CR0 &= ~SPI_CR0_CPHA;

	if (mode == SPI_MASTER)
	{
		SPI->CR0 |= SPI_CR0_MSMODE;
		SystemCoreClockUpdate();
		PARAM_CHECK((SystemCoreClock / (freq) < 1) || (SystemCoreClock / (freq) > 256));
		div = SystemCoreClock / (freq);

		while (1)
		{
			if (div < 2)
				break;

			tmp += 1;
			div >>= 1;
		}
		SPI->CR0 &= ~SPI_CR0_SCLKDIV;
		SPI->CR0 |= ((tmp - 1) << SPI_CR0_SCLKDIV_pos);
	}
	else
	{
		SPI->CR0 &= ~SPI_CR0_MSMODE;
	}
}

/**
 * @brief spi deinit
 *
 */
void SPI_DeInit(void)
{
	int i;
	SYSC_WPT_UNLOCK();
	SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_SPI;
	for (i = 4; i > 0; --i);

	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_SPI;
}

/**
 * @brief :master Conflict interrupt Control
 *
 * @param ctl :ENABLE , DISABLE
 */
void SPI_MasterConflictIRQControl(ControlStatus ctl)
{
	if (ctl == ENABLE)
		SPI->CR0 |= SPI_CR0_MSTCFIE;
	else
		SPI->CR0 &= ~SPI_CR0_MSTCFIE;
}

/**
 * @brief trasfer done interrupt enable
 *
 */
void SPI_EnableIRQ(void)
{
	SPI->CR0 |= SPI_CR0_DONEIE;
}

/**
 * @brief trasfer done interrupt disable
 *
 */
void SPI_DisableIRQ(void)
{
	SPI->CR0 &= ~SPI_CR0_DONEIE;
}

/**
 * @brief set CS high
 *
 */
void SPI_SetCSN(void)
{
	SPI->CSN = 0x01;
}

/**
 * @brief set cs low
 *
 */
void SPI_ClrCSN(void)
{
	SPI->CSN = 0;
}

/**
 * @brief send data
 *
 * @param data :8bit data
 */
void SPI_SendData(u8 data)
{
	SPI->DR = data;
	while (!(SPI->SR & SPI_SR_DONESR));
}

/**
 * @brief recieve data
 *
 * @return u8 :8bit data
 */
u8 SPI_RecieveData(void)
{
	SPI->DR = 0;
	while (!(SPI->SR & SPI_SR_DONESR));
	return SPI->DR;
}

/**
 * @brief get status register value
 *
 * @return u32: status reg val
 */
u32 SPI_GetStatus(void)
{
	return SPI->SR;
}
