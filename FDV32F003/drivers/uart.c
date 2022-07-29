/**
 * @file uart.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "sysc.h"
#include "uart.h"
#include "iom.h"

/**
 * @brief uart init
 *
 * @param
 * @param mode : UART_MODE_8B_SYNC , UART_MODE_10B_ASYNC , UART_MODE_11B_ASYNC
 * @param iBaud :baud:
 * @return: TURE , FALSE
 */
void UART_Init(int mode, int iBaud)
{
	u32 pclk = 0;
	PARAM_CHECK((mode != UART_MODE_10B_ASYNC) && (mode != UART_MODE_8B_SYNC) && (mode != UART_MODE_11B_ASYNC));

	SystemCoreClockUpdate();

	pclk = SYSC_GetAPBCLK();

	SYSC->CLKENCFG |= SYSC_CLKENCFG_UART_PCKEN;
	UART1->SCON = 0;

	if (mode == UART_MODE_8B_SYNC)
	{
		PARAM_CHECK(pclk / (2 * iBaud) < 1);
		UART1->BDIV = (pclk + iBaud) / (2 * iBaud) - 1;
		UART1->SCON = ((UART_MODE_8B_SYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
	}
	else if (mode == UART_MODE_10B_ASYNC)
	{
		UART1->BDIV = (pclk + 8 * iBaud) / (16 * iBaud) - 1;
		// REG32(0xB700) = UART1->BDIV;
		UART1->SCON = ((UART_MODE_10B_ASYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
	}
	else
	{
		PARAM_CHECK(pclk / (16 * iBaud) < 1);
		UART1->BDIV = (pclk + 8 * iBaud) / (16 * iBaud) - 1;
		UART1->SCON = ((UART_MODE_11B_ASYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
	}
}

/**
 * @brief uart deinit
 *
 * @param void
 */
void UART_DeInit(void)
{
	int i;

	SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
	SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
	SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_UART_PSFT_RST;
	for (i = 10; i > 0; --i)
		;
	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_UART_PCKEN;
}

/**
 * @brief recieve date verify configure
 *
 * @param chk :UART_VERIFY_SEL_EVEN,UART_VERIFY_SEL_ODD
 */
void UART_RcvVerifyCfg(int chk)
{
	PARAM_CHECK((chk != UART_VERIFY_SEL_EVEN) && (chk != UART_VERIFY_SEL_ODD));
	if (chk == UART_VERIFY_SEL_EVEN)
	{
		UART1->SCON |= (1 << 11);
	}
	else
	{
		UART1->SCON &= ~(1 << 11);
	}
}
/**
 * @brief enable control
 *
 * @param enType :UART_EN_TYPE_LPMODE | UART_EN_TYPE_SM2 | UART_EN_TYPE_REN |
 * UART_EN_TYPE_SFD
 */
void UART_EnableControl(int enType)
{
	if (enType & UART_EN_TYPE_LPMODE)
		UART1->SCON |= (1 << 10);
	else
		UART1->SCON &= ~(1 << 10);

	if (enType & UART_EN_TYPE_SM2)
		UART1->SCON |= (1 << 7);
	else
		UART1->SCON &= ~(1 << 7);

	if (enType & UART_EN_TYPE_REN)
		UART1->SCON |= (1 << 6);
	else
		UART1->SCON &= ~(1 << 6);

	if (enType & UART_EN_TYPE_SFD)
		UART1->SCON |= (1 << 3);
	else
		UART1->SCON &= ~(1 << 3);
}
/**
 * @brief enable interrupt
 *
 * @param type: UART_IRQ_TYPE_RXST | UART_IRQ_TYPE_RX | UART_IRQ_TYPE_TX
 */
void UART_EnableIRQ(int type)
{
	PARAM_CHECK(UART1 != UART1);
	if (type & UART_IRQ_TYPE_RXST)
		UART1->SCON |= (1 << 2);
	if (type & UART_IRQ_TYPE_RX)
		UART1->SCON |= (1 << 1);
	if (type & UART_IRQ_TYPE_TX)
		UART1->SCON |= (1 << 0);
}
/**
 * @brief disable interrupt
 *
 * @param type: UART_IRQ_TYPE_RXST | UART_IRQ_TYPE_RX | UART_IRQ_TYPE_TX
 */
void UART_DisableIRQ(int type)
{
	if (type & UART_IRQ_TYPE_RXST)
		UART1->SCON &= ~(1 << 2);
	if (type & UART_IRQ_TYPE_RX)
		UART1->SCON &= ~(1 << 1);
	if (type & UART_IRQ_TYPE_TX)
		UART1->SCON &= ~(1 << 0);
}
/**
 * @brief uart send one data
 *
 * @param u8Dat : send data
 */
void UART_Send(u8 u8Dat)
{
	UART1->SBUF = u8Dat;
	while ((UART1->ISR & UART_ISR_TI) != UART_ISR_TI)
		;
	UART1->ISR = UART_ISR_TI;
}

/**
 * @brief uart recieve one data
 *
 * @return u8: rcv data
 */
u8 UART_Receive(void)
{
	while ((UART1->ISR & UART_ISR_RI) != UART_ISR_RI)
		;
	UART1->ISR = UART_ISR_RI;
	return UART1->SBUF;
}

/**
 * @brief uart send a 9bit data
 *
 * @param dat : send data
 */
void UART_Send9BitData(u16 dat)
{
	if (dat & (1 << 8))
	{
		UART1->SCON |= UART_SCON_TB8;
	}
	else
	{
		UART1->SCON &= ~UART_SCON_TB8;
	}
	UART1->SBUF = dat;
	while ((UART1->ISR & UART_ISR_TI) != UART_ISR_TI)
		;
	UART1->ISR = UART_ISR_TI;
}

/**
 * @brief uart recieve a 9bit data
 * @return u16: rcv data
 */
u16 UART_Receive9BitData(void)
{
	while ((UART1->ISR & UART_ISR_RI) != UART_ISR_RI)
		;
	UART1->ISR = UART_ISR_RI;
	if (UART1->SCON & UART_SCON_RB8)
		return UART1->SBUF | (1ul << 8);
	else
		return UART1->SBUF;
}
/**
 * @brief 写数据到发�?�寄存器包括bit8
 * @param dat send data
 * @note 不查询发送完成标�??? */
void UART_WriteData(u16 dat)
{
	if (dat & (1 << 8))
	{
		UART1->SCON |= UART_SCON_TB8;
	}
	else
	{
		UART1->SCON &= ~UART_SCON_TB8;
	}
	UART1->SBUF = dat;

	while (((UART1->ISR) & 0x00000001) != 0x00000001)
	{
		__asm("NOP");
	}
	UART1->ISR = (0xff << 0); // clear intf
	if (dat == '\n')
	{
		UART1->SBUF = '\r';
		while (((UART1->ISR) & 0x00000001) != 0x00000001)
		{
			__asm("NOP");
		}
		UART1->ISR = (0xff << 0); // clear intf
	}
}
/**
 * @brief 读接收寄存器数据包括bit8
 *
 * @param void
 * @return u16 rcv data
 */
u16 UART_ReadData(void)
{
	if (UART1->SCON & UART_SCON_RB8)
		return UART1->SBUF | (1ul << 8);
	else
		return UART1->SBUF;
}
/* * @brief set address and address valid bits
 *
 * @param addr:val
 * @param addrCMPBits:val
 */
void UART_SetAddrAndMask(u8 addr, u8 addrCMPBits)
{
	UART1->SADDR = addr;
	UART1->SADEN = addrCMPBits;
}

/**
 * @brief read status regester value
 *
 * @return u32
 */
u32 UART_GetIntFlag(void)
{
	return UART1->ISR;
}

/**
 * @brief write status regester value
 *
 * @param val
 */
void UART_ClrIntFlag(u32 val)
{
	UART1->ISR = val;
}
