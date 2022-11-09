/**
  ******************************************************************************
  * @file    lib_include.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-09
  * @brief   This file is the total header file of all files in the firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_INCLUDE_H__
#define __LIB_INCLUDE_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* firmware include file */
#include "adc.h"
#include "anac.h"
#include "efc.h"
#include "iom.h"
#include "lptimer.h"
#include "sysc.h"
#include "timer.h"
#include "uart.h"
#include "wdt.h"

/* Debug print function definition */
#ifdef _DEBUG
extern int __wrap_printf(const char *fmt, ...);
#define printf(...) __wrap_printf(__VA_ARGS__)
#else
#define printf(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /*__LIB_INCLUDE_H__*/

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

