/**
 * @file   system_phnx02.h
 * @author bifie.tang
 * @brief
 * @version 0.1
 * @date 2020-03-16
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __SYSTEM_PHNX02_H
#define __SYSTEM_PHNX02_H
#ifdef __cplusplus
extern "C" {
#endif

// user verify xth
#ifndef XTH_FREQ
#define XTH_FREQ 8000000
#endif
#ifndef XTL_FREQ
#define XTL_FREQ 32768
#endif
#define F_XTH -1
#define F_XTL 0
#define F_HRC1M 1
#define F_HRC2M 2
#define F_HRC4M 3
#define F_HRC8M 4
#define F_HRC16M 5
//#define F_HRC24M 6
//#define F_HRC32M 7
#define F_LRC 8

// user configure
#ifndef SYSC_CLK_SRC_SEL
#define SYSC_CLK_SRC_SEL F_HRC8M
#endif

enum _DIV {
    DIV1 = 0,
    DIV2,
    DIV3,
    DIV4,
    DIV5,
    DIV6,
    DIV7,
    DIV8,
    DIV9,
    DIV10,
    DIV11,
    DIV12,
    DIV13,
    DIV14,
    DIV15,
    DIV16,
    DIV17,
    DIV18,
    DIV19,
    DIV20,
    DIV21,
    DIV22,
    DIV23,
    DIV24,
    DIV25,
    DIV26,
    DIV27,
    DIV28,
    DIV29,
    DIV30,
    DIV31,
    DIV32,
    DIV33,
    DIV34,
    DIV35,
    DIV36,
    DIV37,
    DIV38,
    DIV39,
    DIV40,
    DIV41,
    DIV42,
    DIV43,
    DIV44,
    DIV45,
    DIV46,
    DIV47,
    DIV48,
    DIV49,
    DIV50,
    DIV51,
    DIV52,
    DIV53,
    DIV54,
    DIV55,
    DIV56,
    DIV57,
    DIV58,
    DIV59,
    DIV60,
    DIV61,
    DIV62,
    DIV63,
    DIV64,
    DIV65,
    DIV66,
    DIV67,
    DIV68,
    DIV69,
    DIV70,
    DIV71,
    DIV72,
    DIV73,
    DIV74,
    DIV75,
    DIV76,
    DIV77,
    DIV78,
    DIV79,
    DIV80,
    DIV81,
    DIV82,
    DIV83,
    DIV84,
    DIV85,
    DIV86,
    DIV87,
    DIV88,
    DIV89,
    DIV90,
    DIV91,
    DIV92,
    DIV93,
    DIV94,
    DIV95,
    DIV96,
    DIV97,
    DIV98,
    DIV99,
    DIV100,
    DIV101,
    DIV102,
    DIV103,
    DIV104,
    DIV105,
    DIV106,
    DIV107,
    DIV108,
    DIV109,
    DIV110,
    DIV111,
    DIV112,
    DIV113,
    DIV114,
    DIV115,
    DIV116,
    DIV117,
    DIV118,
    DIV119,
    DIV120,
    DIV121,
    DIV122,
    DIV123,
    DIV124,
    DIV125,
    DIV126,
    DIV127,
    DIV128,
};
// user configure
#define SYSC_AHB_DIV DIV1
#define SYSC_APB_DIV DIV1

// extern varible declare
extern unsigned int SystemCoreClock;
// extern function declare
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif
