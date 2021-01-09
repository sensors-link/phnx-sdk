/**
 * @file lib_include.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

// firmware include file
#include "anac.h"
#include "efc.h"
#include "iom.h"
#include "lptimer.h"
#include "pmu.h"
#include "spi.h"
#include "sysc.h"
#include "timer.h"
#include "twc.h"
#include "uart.h"
#include "wdt.h"


//interrupt handler function
void MSOFT_IntHandler(void);
void MEXP_Handler(void);
void NMI_Handler(void);
void PMU_IrqHandler(void);
void LPT_IrqHandler(void);
void TIMER1_IrqHandler(void);
void TIMER2_IrqHandler(void);
void TIMER3_IrqHandler(void);
void TIMER4_IrqHandler(void);
void UART1_IrqHandler(void);
void UART2_IrqHandler(void);
void SPI_IrqHandler(void);
void ANAC_IrqHandler(void);
void EFC_IrqHandler(void);
void IOM_IrqHandler(void);
void I2C_IrqHandler(void);
void RTC_IrqHandler(void);
void TWC_IrqHandler(void);
void LPU_IrqHandler(void);

#ifdef _DEBUG
extern int __wrap_printf(const char *fmt, ...);
#define printf(...) __wrap_printf(__VA_ARGS__)
#else
#define printf(...)
#endif
