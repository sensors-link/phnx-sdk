/**
 * @file lib_include.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __LIB_INCLUDE_H__
#define __LIB_INCLUDE_H__

// firmware include file
#include "efc.h"
#include "iom.h"
#include "lptimer.h"
#include "sysc.h"
#include "timer.h"
#include "uart.h"
#include "wdt.h"

#ifdef _DEBUG
extern int __wrap_printf(const char *fmt, ...);
#define printf(...) __wrap_printf(__VA_ARGS__)
#else
#define printf(...)
#endif

#endif /*__LIB_INCLUDE_H__*/
