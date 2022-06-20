/**
 * @file iom.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __IOM_H__
#define __IOM_H__
#include "../include/phnx05.h"

/*register defines*/
#define IOM_DATA_REG                REG32(IOM_BASE + 0x00)
#define IOM_OE_REG                  REG32(IOM_BASE + 0x04)
#define IOM_PU_REG                  REG32(IOM_BASE + 0x08)
#define IOM_PD_REG                  REG32(IOM_BASE + 0x0c)
#define IOM_OTYPE_REG               REG32(IOM_BASE + 0x10)
#define IOM_AINCTRL_REG             REG32(IOM_BASE + 0x14)
#define IOM_DRS_REG                 REG32(IOM_BASE + 0x18)
#define IOM_AF0_REG                 REG32(IOM_BASE + 0x1c)
#define IOM_AF1_REG                 REG32(IOM_BASE + 0x20)
#define IOM_INT_TYPE_REG            REG32(IOM_BASE + 0x24)
#define IOM_INT_POLARITY_REG        REG32(IOM_BASE + 0x28)
#define IOM_EXT_INTE_REG            REG32(IOM_BASE + 0x2c)
#define IOM_INTF_REG                REG32(IOM_BASE + 0x30)
#define IOM_CTL_REG                 REG32(IOM_BASE + 0x34)

/*register bit defines*/

// IOM_AF0
#define IOM_AF0_P15_SEL             BITS(30, 31)
#define IOM_AF0_P14_SEL             BITS(28, 29)
#define IOM_AF0_P13_SEL             BITS(26, 27)
#define IOM_AF0_P12_SEL             BITS(24, 25)
#define IOM_AF0_P11_SEL             BITS(22, 23)
#define IOM_AF0_P10_SEL             BITS(20, 21)
#define IOM_AF0_P09_SEL             BITS(18, 19)
#define IOM_AF0_P08_SEL             BITS(16, 17)
#define IOM_AF0_P07_SEL             BITS(14, 15)
#define IOM_AF0_P06_SEL             BITS(12, 13)
#define IOM_AF0_P05_SEL             BITS(10, 11)
#define IOM_AF0_P04_SEL             BITS(8, 9)
#define IOM_AF0_P03_SEL             BITS(6, 7)
#define IOM_AF0_P02_SEL             BITS(4, 5)
#define IOM_AF0_P01_SEL             BITS(2, 3)
#define IOM_AF0_P00_SEL             BITS(0, 1)

#define IOM_AF0_P00_SEL_GPIO        (0 << 0)
#define IOM_AF0_P00_SEL_UART1_RX    (1 << 0)
#define IOM_AF0_P00_SEL_T3_PWM      (2 << 0)
#define IOM_AF0_P00_SEL_T3G         (3 << 0)

#define IOM_AF0_P01_SEL_GPIO        (0 << 2)
#define IOM_AF0_P01_SEL_UART1_TX    (1 << 2)
#define IOM_AF0_P01_SEL_T3_PWM      (2 << 2)
#define IOM_AF0_P01_SEL_T3CK        (3 << 2)

#define IOM_AF0_P02_SEL_GPIO        (0 << 4)
#define IOM_AF0_P02_SEL_JTAG_TCK    (1 << 4)
#define IOM_AF0_P02_SEL_REV         (2 << 4)
#define IOM_AF0_P02_SEL_T2_PWM      (3 << 4)

#define IOM_AF0_P03_SEL_GPIO        (0 << 6)
#define IOM_AF0_P03_SEL_JTAG_TDI    (1 << 6)
#define IOM_AF0_P03_SEL_REV         (2 << 6)
#define IOM_AF0_P03_SEL_T2_PWM      (3 << 6)

#define IOM_AF0_P04_SEL_GPIO        (0 << 8)
#define IOM_AF0_P04_SEL_JTAG_TMS    (1 << 8)
#define IOM_AF0_P04_SEL_T4G         (2 << 8)
#define IOM_AF0_P04_SEL_T4_PWM      (3 << 8)

#define IOM_AF0_P05_SEL_GPIO        (0 << 10)
#define IOM_AF0_P05_SEL_JTAG_TDO    (1 << 10)
#define IOM_AF0_P05_SEL_T4CKI       (2 << 10)
#define IOM_AF0_P05_SEL_T4_PWM      (3 << 10)

#define IOM_AF0_P06_SEL_GPIO        (0 << 12)
#define IOM_AF0_P06_SEL_T1_PWM      (1 << 12)
#define IOM_AF0_P06_SEL_T1G         (2 << 12)
#define IOM_AF0_P06_SEL_REV         (4 << 12)

#define IOM_AF0_P07_SEL_GPIO        (0 << 14)
#define IOM_AF0_P07_SEL_T1_PWM      (1 << 14)
#define IOM_AF0_P07_SEL_T1CKI       (2 << 14)
#define IOM_AF0_P07_SEL_REV         (3 << 14)

#define IOM_AF0_P08_SEL_GPIO        (0 << 16)
#define IOM_AF0_P08_SEL_T2_PWM      (1 << 16)
#define IOM_AF0_P08_SEL_T2G         (2 << 16)
#define IOM_AF0_P08_SEL_REV         (3 << 16)

#define IOM_AF0_P09_SEL_GPIO        (0 << 18)
#define IOM_AF0_P09_SEL_T2_PWM      (1 << 18)
#define IOM_AF0_P09_SEL_T2CKI       (2 << 18)
#define IOM_AF0_P09_SEL_REV         (3 << 18)

#define IOM_AF0_P10_SEL_GPIO        (0 << 20)
#define IOM_AF0_P10_SEL_REV1        (1 << 20)
#define IOM_AF0_P10_SEL_REV2        (2 << 20)
#define IOM_AF0_P10_SEL_T3_PWM      (3 << 20)

#define IOM_AF0_P11_SEL_GPIO        (0 << 22)
#define IOM_AF0_P11_SEL_TSTO        (1 << 22)
#define IOM_AF0_P11_SEL_T3_PWM      (2 << 22)
#define IOM_AF0_P11_SEL_REV         (3 << 22)

#define IOM_AF0_P12_SEL_GPIO        (0 << 24)
#define IOM_AF0_P12_SEL_REV1        (1 << 24)
#define IOM_AF0_P12_SEL_T3_PWM      (2 << 24)
#define IOM_AF0_P12_SEL_REV2        (3 << 24)

#define IOM_AF0_P13_SEL_GPIO        (0 << 26)
#define IOM_AF0_P13_SEL_T3_PWM      (1 << 26)
#define IOM_AF0_P13_SEL_UART1_RX    (2 << 26)
#define IOM_AF0_P13_SELT4_PWM       (3 << 26)

#define IOM_AF0_P14_SEL_GPIO        (0 << 28)
#define IOM_AF0_P14_SEL_REV         (1 << 28)
#define IOM_AF0_P14_SEL_UART1_TX    (2 << 28)
#define IOM_AF0_P14_SEL_T4_PWM      (3 << 28)

#define IOM_AF0_P15_SEL_GPIO        (0 << 30)
#define IOM_AF0_P15_SEL_UART1_RX    (1 << 30)
#define IOM_AF0_P15_SEL_T1_PWM      (2 << 30)
#define IOM_AF0_P15_SEL_REV         (3 << 30)

// IOM_AF1
#define IOM_AF1_P16_SEL             BITS(0, 1)

#define IOM_AF1_P16_SEL_GPIO        (0 << 0)
#define IOM_AF1_P16_SEL_UART1_TX    (1 << 0)
#define IOM_AF1_P16_SEL_T1_PWM      (2 << 0)
#define IOM_AF1_P16_SEL_REV         (3 << 0)


// IOM_CTL
#define IOM_CTL_LS_SYNC             BIT(2)
#define IOM_CTL_DEBOUNCE            BIT(1)
#define IOM_CTL_INTE                BIT(0)

#define GPIO_PIN0                   (1 << 0)
#define GPIO_PIN1                   (1 << 1)
#define GPIO_PIN2                   (1 << 2)
#define GPIO_PIN3                   (1 << 3)
#define GPIO_PIN4                   (1 << 4)
#define GPIO_PIN5                   (1 << 5)
#define GPIO_PIN6                   (1 << 6)
#define GPIO_PIN7                   (1 << 7)
#define GPIO_PIN8                   (1 << 8)
#define GPIO_PIN9                   (1 << 9)
#define GPIO_PIN10                  (1 << 10)
#define GPIO_PIN11                  (1 << 11)
#define GPIO_PIN12                  (1 << 12)
#define GPIO_PIN13                  (1 << 13)
#define GPIO_PIN14                  (1 << 14)
#define GPIO_PIN15                  (1 << 15)
#define GPIO_PIN16                  (1 << 16)
#define GPIO_ALL                    (0xfffff)

// extern define
#define PIN_FUNC_0                  (0)
#define PIN_FUNC_1                  (1)
#define PIN_FUNC_2                  (2)
#define PIN_FUNC_3                  (3)

#define PIN_INT_TYPE_EDGE           (0)
#define PIN_INT_TYPE_LEVEL          (1)

#define PIN_INT_POL_LOW             (0)
#define PIN_INT_POL_HIGH            (1)

// extern function declare
void GPIO_PinSelect(int pin, int fun);
void GPIO_PinConfigure(int pin, int analogEn, int outputEn, int puEn, int pdEn, int outOpenDrainEn);
int  GPIO_GetData(void);
void GPIO_SetPin(int pin);
void GPIO_ClrPin(int pin);
void GPIO_PinIntConfig(int pin, int type, int polarity);
void GPIO_GlobleIRQControl(int syncDisEn, int debounceEn, int en);
void GPIO_PinIRQControl(int pin, int en);
int  GPIO_GetIntFlag(void);
void GPIO_ClrIntFlag(int pin);

#endif /* __IOM_H__ */
