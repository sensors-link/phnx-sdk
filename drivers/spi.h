/**
 * @file spi.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __SPI_H
#define __SPI_H
#include "phnx02.h"

/* SPI definitions */
#define SPI_CR0_REG REG32(SPI_BASE + 0x00)
#define SPI_CSN_REG REG32(SPI_BASE + 0x04)
#define SPI_SR_REG REG32(SPI_BASE + 0x08)
#define SPI_DR_REG REG32(SPI_BASE + 0x0c)

// reg bit definitions

#define SPI_CR0_CPOL BIT(7)
#define SPI_CR0_CPHA BIT(6)
#define SPI_CR0_MSTCFIE BIT(5)
#define SPI_CR0_DONEIE BIT(4)
#define SPI_CR0_MSMODE BIT(3)
#define SPI_CR0_SCLKDIV BITS(0, 2)

#define SPI_CR0_SCLKDIV_pos (0) // 0-7 div(2^(x+1))

#define SPI_SR_MSTCFSR BIT(1)
#define SPI_SR_DONESR BIT(0)

// extend define
#define SPI_CPOL_LOW 0
#define SPI_CPOL_HIGH 1

#define SPI_CPHA_FIST 0
#define SPI_CPHA_MIDD 1

#define SPI_SLAVE 0
#define SPI_MASTER 1

#define SPI_ClrIntFlag()                                                       \
    { int tmp = SPI->SR; }

#define SPI_PIN_0_1_2_3 0
#define SPI_PIN_12_13_14_15 1
#define SPI_PIN_19_18_16_17 2

// extern function declare
void SPI_Init(int pin, int mode, int pol, int phase, int freq);
void SPI_DeInit(void);
void SPI_MasterConflictIRQControl(ControlStatus ctl);
void SPI_EnableIRQ(void);
void SPI_DisableIRQ(void);
void SPI_SetCSN(void);
void SPI_ClrCSN(void);
void SPI_SendData(u8 data);
u8 SPI_RecieveData(void);

#endif
