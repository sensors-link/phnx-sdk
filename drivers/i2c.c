/**
 * @file i2c.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */
#include "i2c.h"
#include "sysc.h"
#include "iom.h"

/**
 * @brief i2c init
 *
 * @param pin I2C_PIN_06_07 , I2C_PIN_12_13
 * @param masterEn :ENABLE , DISABLE
 * @param freq :kHz
 * @param selfAddr :7bit self addr
 * @param dstAddr :7bit access addr
 */
void I2C_Init(int pin, int masterEn, int freq, int selfAddr, int dstAddr) {
    PARAM_CHECK((pin != I2C_PIN_12_13));
    SYSC->CLKENCFG |= SYSC_CLKENCFG_IOM;
    IOM->AF0 &= ~(IOM_AF0_P12_SEL | IOM_AF0_P13_SEL);
    IOM->AF0 |= (IOM_AF0_P12_SEL_I2C_SDA | IOM_AF0_P13_SEL_I2C_SCL);
    PARAM_CHECK((selfAddr > 0x7f) || (dstAddr > 0x7f));
    SYSC->CLKENCFG |= SYSC_CLKENCFG_I2C;
    I2C->CON &= ~I2C_CON_ENABLE;
    if (masterEn == ENABLE) {
        I2C->CON |= I2C_CON_MASTER | I2C_CON_SLAVE_DIS;
        I2C->ADDR &= ~I2C_ADDR_TAR;
        I2C->ADDR |= (selfAddr << I2C_ADDR_TAR_pos);
        SystemCoreClockUpdate();
        PARAM_CHECK((((int)(SystemCoreClock / 1000 / freq) - 9) >> 1) < 1);
        I2C->SCLCR = 0;
        I2C->SCLCR = ((((SystemCoreClock / 1000 / freq) - 9) >> 1) << 16) |
                     ((((SystemCoreClock / 1000 / freq) - 9) >> 1) + 9);
    } else {
        I2C->CON &= ~(I2C_CON_MASTER | I2C_CON_SLAVE_DIS);
        I2C->ADDR &= ~I2C_ADDR_SAR;
        I2C->ADDR |= (selfAddr << I2C_ADDR_SAR_pos);
    }
    I2C->CON |= I2C_CON_ENABLE;
}
/**
 * @brief i2c deinit
 *
 */
void I2C_DeInit(void) {
    int i;
    SYSC_WPT_UNLOCK();
    SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_I2C;
    for (i = 10; i > 0; --i)
        ;
    SYSC->CLKENCFG &= ~SYSC_CLKENCFG_I2C;
}

/**
 * @brief set master access destation address
 *
 * @param addr :7bit addr
 */
void I2C_SetAccessAddr(int addr) {
    PARAM_CHECK(addr > 0x7f);
    I2C->CON &= ~I2C_CON_ENABLE;
    I2C->ADDR &= ~I2C_ADDR_TAR;
    I2C->ADDR |= addr << I2C_ADDR_TAR_pos;
    I2C->CON |= I2C_CON_ENABLE;
}
/**
 * @brief enable interrupt
 *
 * @param pIrqType : surport '|' combine
I2C_IRQ_BROADCAST      |
I2C_IRQ_START_RESTART  |
I2C_IRQ_STOP           |
I2C_IRQ_BUZY           |
I2C_IRQ_RX_TRANSFER_END|
I2C_IRQ_TX_ABORT       |
I2C_IRQ_READ_REQ       |
I2C_IRQ_TX_EMPORTY     |
I2C_IRQ_RX_FULL        |
 */
void I2C_EnableIRQ(eI2CIRQ_Type IrqType) {
    I2C->CON &= ~I2C_CON_ENABLE;
    I2C->CON |= IrqType;
    I2C->CON |= I2C_CON_ENABLE;
}

/**
 * @brief broadcast control
 *
 * @param ctl : ENABLE , DISABLE
 */
void I2C_BroadcastControl(ControlStatus ctl) {
    I2C->CON &= ~I2C_CON_ENABLE;
    if (ctl == ENABLE) {
        I2C->CON |= I2C_CON_GCEN;
    } else {
        I2C->CON &= ~I2C_CON_GCEN;
    }

    I2C->CON |= I2C_CON_ENABLE;
}
/**
 * @brief restart enable control
 *
 * @param ctl : ENABLE , DISABLE
 */
void I2C_ReStartControl(ControlStatus ctl) {
    I2C->CON &= ~I2C_CON_ENABLE;
    if (ctl == ENABLE) {
        I2C->CON |= I2C_CON_RESTART_EN;
    } else {
        I2C->CON &= ~I2C_CON_RESTART_EN;
    }

    I2C->CON |= I2C_CON_ENABLE;
}

/**
 * @brief send data
 *
 * @param cmdType : surport '|' combine
 * I2C_CMD_RESTART |
 * I2C_CMD_STOP |
 * I2C_CMD_READ |
 * I2C_CMD_WRITE
 * @param data :8bit data
 */
void I2C_SendData(int cmdType, u8 data) { I2C->DATACMD = cmdType | data; }

/**
 * @brief read interrupt status register value
 *
 * @return u32:reg val
 */
u32 I2C_ReadStatusReg(void) { return I2C->ISR; }

/**
 * @brief write interrupt status register value (write 1 clear)
 *
 * @param val :I2C_ISR_xxx     surport '|' combine
 */
void I2C_WriteStatusReg(u32 val) { I2C->ISR |= val; }
