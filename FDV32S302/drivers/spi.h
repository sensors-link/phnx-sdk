/**
 * @file spi.h
 * @author wyd
 * @brief
 * @version 0.1
 * @date 2021-07-16
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __SPI_H__
#define __SPI_H__

#include "phnx04.h"

// reg bit definitions
// SPI CR0
#define SPI_CR0_CPOL 	      BIT(7)
#define SPI_CR0_CPHA 	      BIT(6)
#define SPI_CR0_MSTCFIE       BIT(5)
#define SPI_CR0_DONEIE 	      BIT(4)
#define SPI_CR0_MSMODE 	      BIT(3)
#define SPI_CR0_SCLKDIV       BITS(0, 2)

#define SPI_CR0_SCLKDIV_pos   (0) // 0-7 div(2^(x+1))

// SPI SR
#define SPI_SR_SPI_CS	      BIT(2)
#define SPI_SR_MSTCFSR 	      BIT(1)
#define SPI_SR_DONESR 	      BIT(0)

// extend define
#define SPI_CPOL_LOW 	      (0)
#define SPI_CPOL_HIGH         (1)

#define SPI_CPHA_FIST 	      (0)
#define SPI_CPHA_MIDD 	      (1)

#define SPI_SLAVE 		      (0)
#define SPI_MASTER 		      (1)

#define SPI_ClrIntFlag()      { int tmp = SPI->SR; }

// extern function declare
void SPI_Init(int mode, int pol, int phase, int freq);
void SPI_DeInit(void);
void SPI_MasterConflictIRQControl(ControlStatus ctl);
void SPI_EnableIRQ(void);
void SPI_DisableIRQ(void);
void SPI_SetCSN(void);
void SPI_ClrCSN(void);
void SPI_SendData(u8 data);
u8   SPI_RecieveData(void);
u32  SPI_GetStatus(void);

#endif /*__SPI_H__*/
