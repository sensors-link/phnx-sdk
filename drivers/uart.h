/**
 * @file uart.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __UART_H
#define __UART_H
#include "phnx02.h"

/* registers definitions */
#define UART1_SCON_REG REG32(UART1_BASE + 0x00U)
#define UART1_SBUF_REG REG32(UART1_BASE + 0x04U)
#define UART1_SADDR_REG REG32(UART1_BASE + 0x08U)
#define UART1_SADEN_REG REG32(UART1_BASE + 0x0CU)
#define UART1_ISR_REG REG32(UART1_BASE + 0x10U)
#define UART1_BDIV_REG REG32(UART1_BASE + 0x14U)

#define UART2_SCON_REG REG32(UART2_BASE + 0x00U)
#define UART2_SBUF_REG REG32(UART2_BASE + 0x04U)
#define UART2_SADDR_REG REG32(UART2_BASE + 0x08U)
#define UART2_SADEN_REG REG32(UART2_BASE + 0x0CU)
#define UART2_ISR_REG REG32(UART2_BASE + 0x10U)
#define UART2_BDIV_REG REG32(UART2_BASE + 0x14U)

#define LPUART_SCON_REG REG32(LPUART_BASE + 0x00U)
#define LPUART_SBUF_REG REG32(LPUART_BASE + 0x04U)
#define LPUART_SADDR_REG REG32(LPUART_BASE + 0x08U)
#define LPUART_SADEN_REG REG32(LPUART_BASE + 0x0CU)
#define LPUART_ISR_REG REG32(LPUART_BASE + 0x10U)
#define LPUART_BDIV_REG REG32(LPUART_BASE + 0x14U)

/*register bit definitions */
// uart_scon
#define UART_SCON_PACFG BIT(11)
#define UART_SCON_LPMODE BIT(10)
#define UART_SCON_SM01 BITS(8, 9)
#define UART_SCON_SM2 BIT(7)
#define UART_SCON_REN BIT(6)
#define UART_SCON_RB8 BIT(5)
#define UART_SCON_TB8 BIT(4)
#define UART_SCON_RXSIEN BIT(3)
#define UART_SCON_RIEN BIT(2)
#define UART_SCON_TIEN BIT(1)
#define UART_SCON_SFDEN BIT(0) // start bit detect enable

#define UART_SCON_SM01_pos (8)
// UART_SBUF
#define UART_SBUF_pos (0) // 0-0xff

// UART_SADDR
#define UART_SADDR_pos (0) // 0-0xff

// UART_SADEN
#define UART_SADEN_pos (0) // 0-0xff

// UART_ISR
#define UART_ISR_PE BIT(3)
#define UART_ISR_FE BIT(2)
#define UART_ISR_RI BIT(1)
#define UART_ISR_TI BIT(0)

// UART_DIV
#define UART_BDIV_pos (0) // 0-0xffff

// ext def
#define UART1_PORT_P00_P01 0
#define UART1_PORT_P16_P17 1
#define UART2_PORT_P02_P03 2
#define UART2_PORT_P04_P05 3
#define UART2_PORT_P14_P15 4
#define LPUART_PORT_P18_P19 5

#define UART_MODE_8B_SYNC 0
#define UART_MODE_10B_ASYNC 1
#define UART_MODE_11B_ASYNC 2

#define UART_VERIFY_SEL_EVEN 1
#define UART_VERIFY_SEL_ODD 0

#define UART_EN_TYPE_LPMODE (1 << 0)
#define UART_EN_TYPE_SM2 (1 << 1)
#define UART_EN_TYPE_REN (1 << 2)
#define UART_EN_TYPE_SFD (1 << 3) // start bit detect

#define UART_IRQ_TYPE_RXST (1 << 0) // rcv start int en
#define UART_IRQ_TYPE_TX (1 << 1)
#define UART_IRQ_TYPE_RX (1 << 2)

/* function declarations */
void UART_Init(UART_Type *psUart, int port, int mode, int iBaud);
void UART_DeInit(UART_Type *psUart);
void UART_RcvVerifyCfg(UART_Type *psUart, int chk);
void UART_EnableControl(UART_Type *psUart, int enType);
void UART_EnableIRQ(UART_Type *psUart, int type);
void UART_DisableIRQ(UART_Type *psUart, int type);
void UART_Send(UART_Type *psUart, u8 u8Dat);
u8 UART_Receive(UART_Type *psUart);
void UART_Send9BitData(UART_Type *psUart, u16 dat);
u16 UART_Receive9BitData(UART_Type *psUart);
void UART_SetAddrAndMask(UART_Type *psUart, u8 addr, u8 addrCMPBits);
u32 UART_ReadStatusRegester(UART_Type *psUart);
void UART_WriteStatusRegester(UART_Type *psUart, u32 val);

#endif
