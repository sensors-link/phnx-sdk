/**
 * @file phnx02.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */
#ifndef _PHNX02_H
#define _PHNX02_H

#ifdef cplusplus
extern "C" {
#endif
/* IO definitions (access restrictions to peripheral registers) */
/**

  <strong>IO Type Qualifiers</strong> are used
  \li to specify the access to peripheral variables.
  \li for automatic generation of peripheral register debug information.
  */
#ifdef __cplusplus
#define __I volatile /*!< Defines 'read only' permissions                 */
#else
#define __I                                                                    \
    volatile const /*!< Defines 'read only' permissions                 */
#endif
#define __O volatile  /*!< Defines 'write only' permissions                */
#define __IO volatile /*!< Defines 'read / write' permissions              */

/* define interrupt number */
typedef enum IRQn {
    /* ---------------------  Phonix02 Specific Interrupt Numbers ------------*/
    RSV_IRQn = 0,    /*!< Reserved Interrupt						*/
    PMU_IRQn = 1,    /*!< PMU Interrupt							*/
    LPT_IRQn = 2,    /*!< LPT Interrupt						*/
    TIMER1_IRQn = 3, /*!< TIMER1 Interrupt					*/
    TIMER2_IRQn = 4, /*!< TIMER2 Interrupt									*/
    TIMER3_IRQn = 5, /*!< TIMER3 Interrupt									*/
    TIMER4_IRQn = 6, /*!< TIMER4 Interrupt									*/
    UART1_IRQn = 7,  /*!< UART1 Interrupt							*/
    UART2_IRQn = 8,  /*!< UART2 Interrupt									*/
    SPI_IRQn = 9,    /*!< SPI Interrupt									*/
    ANAC_IRQn = 10,  /*!< ANAC Interrupt										*/
    EFC_IRQn = 11,   /*!< EFC Interrupt										*/
    IOM_IRQn = 12,   /*!< IOM Interrupt						*/
    I2C_IRQn = 13,   /*!< I2C Interrupt					*/
    RTC_IRQn = 14,   /*!< RTC Interrupt						*/
    TWC_IRQn = 15,   /*!< TWC Interrupt						*/
    LPU_IRQn = 16,   /*!< LPU Interrupt*/
} IRQn_Type;

//
#include "risc_v_csr.h"
#include "system_phnx02.h"
/* ================================================================================*/
/* ================                       EFC ================ */
/* ================================================================================*/

/**
 * @brief Embeded Flash Control (EFC)
 */

typedef struct {            /*!< EFC Structure          */
    __IO unsigned int CR;   /*!< Control Register */
    __IO unsigned int TNVS; /*!< ROG/ERASE/CEb/NVR/ADDRESS to Web Setup time */
    __IO unsigned int
        TPROG; /*!< PROG/ERASE/CEb/NVR/ADDRESS to Web Setup time          */
    __IO unsigned int TPGS;   /*!< WEb low to PROG2 high Setup time */
    __IO unsigned int TRCV;   /*!< Program Recovery Time */
    __IO unsigned int TERASE; /*!< Erase time */
    __O unsigned int WPT;     /*!< Write Protect Register     */
    __IO unsigned int OPR;    /*!< OPR Flow Register    */
    __I unsigned int PVEV;    /*!< Verify Register    */
    __IO unsigned int STS;    /*!< Verify Register    */
} EFC_Type;

typedef struct {
    __I unsigned int Rsv[0x04 / 4];
    __IO unsigned int CRC_RSL;
    __I unsigned int RSV[0x80 / 4 - 2];
    __IO unsigned int CRC_DAT;
} CRC_Type;

/* ================================================================================
 */
/* ================                      SYSC ================ */
/* ================================================================================
 */

/**
 * @brief System Control (SYSC)
 */

typedef struct {                 /*!< SYSC Structure             */
    __IO unsigned int CLKCTRCFG; /*!< CLKCTRCFG */
    __O unsigned int WRPROCFG;   /*!< WRPROCFG   */
    __IO unsigned int CLKENCFG;
    __O unsigned int MSFTRSTCFG;
    __IO unsigned int RSV[1];
    __IO unsigned int TESTCKSEL;
    __IO unsigned int ANCLKDIV;
    __IO unsigned int TIMCLKDIV;
    __IO unsigned int BZTIMCLKDIV;
} SYSC_Type;

/* ================================================================================
 */
/* ================                     TIMERS ================ */
/* ================================================================================
 */

/**
 * @brief Timer Control (TIMERS)
 */

typedef struct {              /*!< TIMERS Structure             */
    __IO unsigned int CON;    /*!< TIMCON    */
    __I unsigned int INTFLAG; /*!< TIMINTFLAG */
    __O unsigned int INTCLR;  /*!< TIMINTCLR  */
} TIMERS_Type;

/* ================================================================================
 */
/* ================                      TIM0 ================ */
/* ================================================================================
 */

/**
 * @brief Timer Control (TIM0)
 */

typedef struct {             /*!< TIM0 Structure            */
    __IO unsigned int CTCG1; /*!< TIMCTCG1 */
    __IO unsigned int CTCG2; /*!< TIMCTCG2 */
    __I unsigned int CTVAL;  /*!< TIMCTVAL  */
    __IO unsigned int PWCON; /*!< TIMPWCON */
} TIM_Type;

/* ================================================================================
 */
/* ================                       I2C ================ */
/* ================================================================================
 */

/**
 * @brief I2C Control (I2C)
 */

typedef struct {               /*!< I2C Structure               */
    __IO unsigned int CON;     /*!< I2C_CON     */
    __IO unsigned int ADDR;    /*!< I2C_ADDR    */
    __IO unsigned int DATACMD; /*!< I2C_DATACMD */
    __IO unsigned int SCLCR;   /*!< I2C_SCLCR     */
    __IO unsigned int ISR;     /*!< I2C_ISR     */
    __IO unsigned int TIMING;  /*!< I2C_TIMING  */
} I2C_Type;

typedef struct {
    __IO unsigned int CR0;
    __IO unsigned int CSN;
    __I unsigned int SR;
    __IO unsigned int DR;
} SPI_Type;

typedef struct {
    __IO unsigned int SCON;
    __IO unsigned int SBUF;
    __IO unsigned int SADDR;
    __IO unsigned int SADEN;
    __IO unsigned int ISR;
    __IO unsigned int BDIV;
} UART_Type;

typedef struct {
    __IO unsigned int CR;
    __IO unsigned int SWCR;
    __IO unsigned int SWBR;
    __IO unsigned int GAPW;
    __IO unsigned int CMD1;
    __IO unsigned int CMD2;
    __IO unsigned int CMD3;
    __IO unsigned int CMD4;
    __I unsigned int RXD;
    __IO unsigned int TXD;
    __IO unsigned int TXS;
    __IO unsigned int INTEN;
    __IO unsigned int STS;
    __I unsigned int DBG;
} TWC_Type;

typedef struct {
    __IO unsigned int RSV[1];     // 00
    __IO unsigned int LED_CFG;    // 04
    __IO unsigned int PDSENS_CFG; // 08
    __IO unsigned int DC_CFG;     // 0c
    __IO unsigned int CMP_CFG;    // 10
    __IO unsigned int ADC_CFG;    // 14
    __IO unsigned int ADC_CTL;    // 18
    __IO unsigned int ANAC_CFG;   // 1c
    __IO unsigned int LVD_CFG;    // 20
    __IO unsigned int CLK_CFG;    // 24
    __IO unsigned int HRC_TRIM;   // 28
    __IO unsigned int LRC_TRIM;   // 2c
    __IO unsigned int CMP_TRIM;   // 30
    __IO unsigned int BG4A_TRIM;  // 34
    __IO unsigned int BG4S_TRIM;  // 38
    __IO unsigned int TESTCTL;    // 3c
    __IO unsigned int AINSEL;     // 40
    __IO unsigned int MRC_TRIM;   // 44
    __IO unsigned int DLY_CFG;    // 48
    __IO unsigned int ME_CTL;     // 4c
    __IO unsigned int ANAC_FLAG;  // 50
    __IO unsigned int TEST;       // 54
    __O unsigned int WPROT;       // 58
    __IO unsigned int THR1_DATA;  // 5c
    __IO unsigned int THR2_DATA;  // 60
    __I unsigned int rsv0[8];
    __IO unsigned int ADC_VAL[8]; // 80
    __IO unsigned int AVG_VAL;    // A0
} ANAC_Type;

typedef struct {
    __IO unsigned int DATA;
    __IO unsigned int OE;
    __IO unsigned int PU;
    __IO unsigned int PD;
    __IO unsigned int OTYPE;
    __IO unsigned int ADS;
    __IO unsigned int DRS;
    __IO unsigned int AF0;
    __IO unsigned int AF1;
    __IO unsigned int INT_TYPE;
    __IO unsigned int INT_POLARITY;
    __IO unsigned int EXT_INTE;
    __IO unsigned int INTF;
    __IO unsigned int CTL;

} IOM_Type;

typedef struct {
    __IO unsigned int CON;
    __IO unsigned int STS;
    __IO unsigned int TR;
    __IO unsigned int DR;
    __IO unsigned int ALM;
    __IO unsigned int CALR;
    __O unsigned int WPR;

} RTC_Type;

typedef struct {
    __IO unsigned int CR;
    __IO unsigned int WKCFG;
    __O unsigned int SOFTRST;
    __IO unsigned int WKSTS;
    __IO unsigned int RSTSTS;
    __IO unsigned int INTEN;
    __O unsigned int WPT;
    __I unsigned int RSV[1];
    __IO unsigned int BAKR;

} PMU_Type;

typedef struct {
    __IO unsigned int CR;
    __IO unsigned int CFG;
    __IO unsigned int CNT;
    __IO unsigned int INTSTS;

} LPTIM_Type;

typedef struct {
    __IO unsigned int RST;
    __IO unsigned int CR;

} WDT_Type;

/* enum definitions */
typedef enum { DISABLE = 0, ENABLE = !DISABLE } EventStatus, ControlStatus;
typedef enum { FALSE = 0, TRUE = !FALSE } BOOL;
typedef enum { RESET = 0, SET = 1, MAX = 0X7FFFFFFF } FlagStatus;
typedef enum { ERROR = 0, SUCCESS = !ERROR } ErrStatus;

/* bit operations */
#define REG32(addr) (*((volatile unsigned int *)(addr)))
#define REG16(addr) (*((volatile unsigned short *)(addr)))
#define REG8(addr) (*((volatile unsigned char *)(addr)))
#define BIT(x) ((unsigned int)0x01U << (x))
#define BITS(start, end)                                                       \
    ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (end))))
#define GET_BITS(regval, start, end)                                           \
    (((regval)&BITS((start), (end))) >> (start))

/* main flash and SRAM memory map */

#define FLASH_BASE                                                             \
    ((unsigned int)0x10100000UL) /*!< main FLASH base address          */
#define SRAM_BASE                                                              \
    ((unsigned int)0x20000000UL) /*!< SRAM0 base address               */
#define PAGE_BUFF_BASE 0x101c0000UL
/* ================================================================================
 */
/* ================              Peripheral memory map ================ */
/* ================================================================================
 */

#define EFC_BASE 0x40000000UL
#define CRC_BASE 0x40000c00UL
#define SYSC_BASE 0x40001000UL
#define TIMERS_BASE 0x400100A0UL
#define TIM1_BASE 0x40010000UL
#define TIM2_BASE 0x40010014UL
#define TIM3_BASE 0x40010028UL
#define TIM4_BASE 0x4001003CUL
#define I2C_BASE 0x40010400UL
#define SPI_BASE 0x40010800UL
#define UART2_BASE 0x40010c00UL
#define UART1_BASE 0x40011000UL
#define LPUART_BASE 0x40011400UL
#define TWC_BASE 0x40011800UL
#define ANAC_BASE 0x40011c00UL
#define IOM_BASE 0x40012400UL
#define RTC_BASE 0x40012800UL
#define PMU_BASE 0x40012c00UL
#define LPTIM_BASE 0x40013000UL
#define WDT_BASE 0x40013400UL
/* ================================================================================
 */
/* ================             Peripheral declaration ================ */
/* ================================================================================
 */

#define EFC ((EFC_Type *)EFC_BASE)
#define CRC ((CRC_Type *)CRC_BASE)
#define SYSC ((SYSC_Type *)SYSC_BASE)
#define TIMERS ((TIMERS_Type *)TIMERS_BASE)
#define TIM1 ((TIM_Type *)TIM1_BASE)
#define TIM2 ((TIM_Type *)TIM2_BASE)
#define TIM3 ((TIM_Type *)TIM3_BASE)
#define TIM4 ((TIM_Type *)TIM4_BASE)
#define I2C ((I2C_Type *)I2C_BASE)
#define SPI ((SPI_Type *)SPI_BASE)
#define UART1 ((UART_Type *)UART1_BASE)
#define UART2 ((UART_Type *)UART2_BASE)
#define LPUART ((UART_Type *)LPUART_BASE)
#define TWC ((TWC_Type *)TWC_BASE)
#define ANAC ((ANAC_Type *)ANAC_BASE)
#define IOM ((IOM_Type *)IOM_BASE)
#define RTC ((RTC_Type *)RTC_BASE)
#define PMU ((PMU_Type *)PMU_BASE)
#define LPTIM ((LPTIM_Type *)LPTIM_BASE)
#define WDT ((WDT_Type *)WDT_BASE)

/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group Phonix02 */
/** @} */ /* End of group FHSJDZ */

// data type define
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef signed int s32;
typedef signed short s16;
typedef signed char s8;

#ifdef _FW_DEBUG
extern int __wrap_printf(const char *fmt, ...);
#define PARAM_CHECK(x)                                                         \
    {                                                                          \
        if (x) {                                                               \
            __wrap_printf("Wrong parameters value: file:%s,on line:%d\r\n",    \
                          __FILE__, __LINE__);
while (1)
    ;
}
}
#else
#define PARAM_CHECK(x)
#endif

#ifdef cplusplus
}
#endif

#endif /* Phonix02_H */
