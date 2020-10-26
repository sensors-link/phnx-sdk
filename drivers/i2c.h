/**
 * @file i2c.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __I2C_H
#define __I2C_H
#include "phnx02.h"

/* TMP definitions */
#define I2C_CON REG32(I2C_BASE + 0x00)
#define I2C_ADDR REG32(I2C_BASE + 0x04)
#define I2C_DATACMD REG32(I2C_BASE + 0x08)
#define I2C_SCL REG32(I2C_BASE + 0x0c)
#define I2C_ISR REG32(I2C_BASE + 0x10)
#define I2C_TIMING REG32(I2C_BASE + 0x14)

/*register bit definitions */
// I2C_CON
#define I2C_CON_GEIE BIT(27)
#define I2C_CON_STIE BIT(26)
#define I2C_CON_STPIE BIT(25)
#define I2C_CON_ACTIE BIT(24)
#define I2C_CON_RXDIE BIT(23)
#define I2C_CON_TXABIE BIT(22)
#define I2C_CON_RDRIE BIT(21)
#define I2C_CON_TXEIE BIT(20)
#define I2C_CON_RXFIE BIT(18)
#define I2C_CON_GCEN BIT(4)
#define I2C_CON_RESTART_EN BIT(3)
#define I2C_CON_SLAVE_DIS BIT(2)
#define I2C_CON_MASTER BIT(1)
#define I2C_CON_ENABLE BIT(0)
// I2C_ADDR
#define I2C_ADDR_SAR BITS(16, 22)
#define I2C_ADDR_TAR BITS(0, 6)
#define I2C_ADDR_SAR_pos (16)
#define I2C_ADDR_TAR_pos (0)

// I2C_DATACMD
#define I2C_DATACMD_RESTART BIT(10)
#define I2C_DATACMD_STOP BIT(9)
#define I2C_DATACMD_WREN BIT(8)
#define I2C_DATACMD_DATA BITS(0, 7)

// I2C_SCL
#define I2C_SCLCR_HCNT BITS(16, 24)
#define I2C_SCLCR_LCNT BITS(0, 8)

#define I2C_SCLCR_HCNT_pos (16)
#define I2C_SCLCR_LCNT_pos (0)

// I2C_ISR
#define I2C_ISR_ABRT_SLV_ARBLOST BIT(20)
#define I2C_ISR_ARB_LOST BIT(19)
#define I2C_ISR_ABRT_GCALL_NOACK BIT(18)
#define I2C_ISR_ABRT_7B_ADDR_NOACK BIT(17)
#define I2C_ISR_ACTIVITY BIT(16)
#define I2C_ISR_R_GEN_CALL BIT(11)
#define I2C_ISR_R_START_DET BIT(10)
#define I2C_ISR_R_STOP_DET BIT(9)
#define I2C_ISR_R_ACTIVITY BIT(8)
#define I2C_ISR_R_RX_DONE BIT(7)
#define I2C_ISR_R_TX_ABRT BIT(6)
#define I2C_ISR_R_RD_REQ BIT(5)
#define I2C_ISR_R_TX_EMPTY BIT(4)
#define I2C_ISR_R_RX_FULL BIT(2)
// I2C_TIMING
#define I2C_TIMING_SDA_RX_HOLD BITS(8, 11)
#define I2C_TIMING_SDA_TX_HOLD BITS(4, 7)
#define I2C_TIMING_SDA_SETUP BITS(0, 3)

#define I2C_TIMING_SDA_RX_HOLD_pos (8)
#define I2C_TIMING_SDA_TX_HOLD_pos (7)
#define I2C_TIMING_SDA_SETUP_pos (0)

// extend define

typedef enum _I2C_IRQ_T {
    I2C_IRQ_BROADCAST = (1 << 27),
    I2C_IRQ_START_RESTART = (1 << 26),
    I2C_IRQ_STOP = (1 << 25),
    I2C_IRQ_BUZY = (1 << 24),
    I2C_IRQ_RX_TRANSFER_END = (1 << 23),
    I2C_IRQ_TX_ABORT = (1 << 22),
    I2C_IRQ_READ_REQ = (1 << 21),
    I2C_IRQ_TX_EMPORTY = (1 << 20),
    I2C_IRQ_RX_FULL = (1 << 18),
} eI2CIRQ_Type;

#define I2C_CMD_WRITE 0
#define I2C_CMD_RESTART (1 << 10)
#define I2C_CMD_STOP (1 << 9)
#define I2C_CMD_READ (1 << 8)

// #define I2C_PIN_06_07 0
#define I2C_PIN_12_13 1

// extern function declare
void I2C_Init(int pin, int masterEn, int freq, int selfAddr, int dstAddr);
void I2C_DeInit(void);
void I2C_SetAccessAddr(int addr);
void I2C_EnableIRQ(eI2CIRQ_Type IrqType);
void I2C_BroadcastControl(ControlStatus ctl);
void I2C_ReStartControl(ControlStatus ctl);
void I2C_SendData(int cmdType, u8 data);
u32 I2C_ReadStatusReg(void);
void I2C_WriteStatusReg(u32 val);

#endif
