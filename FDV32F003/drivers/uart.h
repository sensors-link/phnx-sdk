/**
 * @file uart.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __UART_H__
#define __UART_H__
#include "phnx05.h"

/*register bit definitions */
// uart_scon
#define UART_SCON_PACFG	 BIT(11)
#define UART_SCON_SM01	 BITS(8, 9)
#define UART_SCON_SM2	 BIT(7)
#define UART_SCON_REN	 BIT(6)
#define UART_SCON_RB8	 BIT(5)
#define UART_SCON_TB8	 BIT(4)
#define UART_SCON_SFDEN	 BIT(3)
#define UART_SCON_RXSIEN BIT(2)
#define UART_SCON_RIEN	 BIT(1)
#define UART_SCON_TIEN	 BIT(0) // start bit detect enable

#define UART_SCON_SM01_pos (8)

// UART_SBUF
#define UART_SBUF_pos (0) // 0-0xff

// UART_SADDR
#define UART_SADDR_pos (0) // 0-0xff

// UART_SADEN
#define UART_SADEN_pos (0) // 0-0xff

// UART_ISR
#define UART_ISR_PE	  BIT(4)
#define UART_ISR_FE	  BIT(3)
#define UART_ISR_RXSF BIT(2)
#define UART_ISR_RI	  BIT(1)
#define UART_ISR_TI	  BIT(0)

// UART_DIV
#define UART_BDIV_pos (0) // 0-0xffff

// ext def
#define UART_MODE_8B_SYNC	(0)
#define UART_MODE_10B_ASYNC (1)
#define UART_MODE_11B_ASYNC (2)

#define UART_VERIFY_SEL_EVEN (1)
#define UART_VERIFY_SEL_ODD	 (0)

#define UART_EN_TYPE_LPMODE (1 << 0)
#define UART_EN_TYPE_SM2	(1 << 1)
#define UART_EN_TYPE_REN	(1 << 2)
#define UART_EN_TYPE_SFD	(1 << 3) // start bit detect

#define UART_IRQ_TYPE_RXST (1 << 0) // rcv start int en
#define UART_IRQ_TYPE_TX   (1 << 1)
#define UART_IRQ_TYPE_RX   (1 << 2)

/* function declarations */
void UART_Init(int mode, int iBaud);
void UART_DeInit(void);
void UART_RcvVerifyCfg(int chk);
void UART_EnableControl(int enType);
void UART_EnableIRQ(int type);
void UART_DisableIRQ(int type);
void UART_Send(u8 u8Dat);
u8	 UART_Receive(void);
void UART_Send9BitData(u16 dat);
u16	 UART_Receive9BitData(void);
void UART_WriteData(u16 dat);
u16	 UART_ReadData(void);
void UART_SetAddrAndMask(u8 addr, u8 addrCMPBits);
u32	 UART_GetIntFlag(void);
void UART_ClrIntFlag(u32 val);

#endif /*__UART_H__*/
