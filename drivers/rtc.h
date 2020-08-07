/**
 * @file rtc.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __RTC_H
#define __RTC_H
#include "phnx02.h"

// reg definitions
#define RTC_CON_REG REG32(RTC_BASE + 0x00)
#define RTC_STS_REG REG32(RTC_BASE + 0x04)
#define RTC_TR_REG REG32(RTC_BASE + 0x08)
#define RTC_DR_REG REG32(RTC_BASE + 0x0c)
#define RTC_ALM_REG REG32(RTC_BASE + 0x10)
#define RTC_CALR_REG REG32(RTC_BASE + 0x14)
#define RTC_WPR_REG REG32(RTC_BASE + 0x18)
// reg bit definitions
#define RTC_CON_RTCEN BIT(31)
#define RTC_CON_CKSEL BITS(28, 30)
#define RTC_CON_CKSEL_XTL (0 << 28)
#define RTC_CON_CKSEL_LRC (2 << 28)
#define RTC_CON_CKSEL_XTH_DIV128 (4 << 28)
#define RTC_CON_CKSEL_XTH_DIV256 (5 << 28)
#define RTC_CON_CKSEL_XTH_DIV512 (6 << 28)
#define RTC_CON_CKSEL_XTH_DIV768 (7 << 28)

#define RTC_CON_FMT BIT(24)
#define RTC_CON_FMT_12H 0 << 24
#define RTC_CON_FMT_24H 1 << 24

#define RTC_CON_ALMEN BIT(23)
#define RTC_CON_ALMIE BIT(22)
#define RTC_CON_PRDEN BIT(21)
#define RTC_CON_PRDIE BIT(20)
#define RTC_CON_WAIT BIT(16)
#define RTC_CON_PRDS BITS(8, 10)
#define RTC_CON_PRDS_pos (8)

#define RTC_CON_PRDS_NOTINT (0 << 8)
#define RTC_CON_PRDS_0P5S (1 << 8)
#define RTC_CON_PRDS_1S (2 << 8)
#define RTC_CON_PRDS_1MIN (3 << 8)
#define RTC_CON_PRDS_1H (4 << 8)
#define RTC_CON_PRDS_1DAY (5 << 8)
#define RTC_CON_PRDS_1MONTH (6 << 8)

#define RTC_CON_PRDSEL BIT(7)
#define RTC_CON_PRDSEL_PRDS (0 << 7)
#define RTC_CON_PRDSEL_PRDX (1 << 7)

#define RTC_CON_PRDX BITS(0, 5)
#define RTC_CON_PRDX_pos (0) //(x+1)*0.5s

#define RTC_STS_WAITF BIT(8)
#define RTC_STS_PRDF BIT(4)
#define RTC_STS_ALMF BIT(0)

#define RTC_TR_HOURH BITS(20, 21)
#define RTC_TR_HOURL BITS(16, 19)
#define RTC_TR_MINH BITS(12, 14)
#define RTC_TR_MINL BITS(8, 11)
#define RTC_TR_SECH BITS(4, 6)
#define RTC_TR_SECL BITS(0, 3)

#define RTC_TR_HOURH_pos (20)
#define RTC_TR_HOURL_pos (16)
#define RTC_TR_MINH_pos (12)
#define RTC_TR_MINL_pos (8)
#define RTC_TR_SECH_pos (4)
#define RTC_TR_SECL_pos (0)

#define RTC_DR_YEARH BITS(28, 31)
#define RTC_DR_YEARL BITS(24, 17)
#define RTC_DR_MONH BIT(20)
#define RTC_DR_MONL BITS(16, 19)
#define RTC_DR_WEEK BITS(8, 10)
#define RTC_DR_DAYH BITS(4, 5)
#define RTC_DR_DAYL BITS(0, 3)

#define RTC_DR_YEARH_pos (28)
#define RTC_DR_YEARL_pos (24)
#define RTC_DR_MONH_pos (20)
#define RTC_DR_MONL_pos (16)
#define RTC_DR_WEEK_pos (8)
#define RTC_DR_DAYH_pos (4)
#define RTC_DR_DAYL_pos (0)

#define RTC_ALM_ALMWEEK BITS(16, 22)
#define RTC_ALM_ALMHOURH BITS(12, 13)
#define RTC_ALM_ALMHOURL BITS(8, 11)
#define RTC_ALM_ALMMINH BITS(4, 6)
#define RTC_ALM_ALMMINL BITS(0, 3)

#define RTC_ALM_ALMWEEK_pos (16)
#define RTC_ALM_ALMHOURH_pos (12)
#define RTC_ALM_ALMHOURL_pos (8)
#define RTC_ALM_ALMMINH_pos (4)
#define RTC_ALM_ALMMINL_pos (0)

#define RTC_CALR_CAL_EN BIT(15)
#define RTC_CALR_CAL_SEL BIT(14)
#define RTC_CALR_1HZ_OE BIT(13)
#define RTC_CALR_CR BITS(0, 8)
#define RTC_CALR_CR_pos (0)

#define RTC_WPR_V0 0xca
#define RTC_WPR_V1 0x53
#define RTC_WPT_UNLOCK()                                                       \
    {                                                                          \
        RTC->WPR = 0xca;                                                       \
        RTC->WPR = 0x53;                                                       \
    }

// ext def
typedef enum _CLK_SRC {
    RTC_XTL = 0,
    RTC_LRC,
    RTC_XTH_DIV128,
    RTC_XTH_DIV256,
    RTC_XTH_DIV512,
    RTC_XTH_DIV768,
} eClkSrc;

typedef enum _HOUR_FM {
    RTC_FMT_12H = 0,
    RTC_FMT_24H,
} eHourFM;

typedef enum _AlmWeek {
    RTC_ALM_EN_WEEK1 = (1 << 1),
    RTC_ALM_EN_WEEK2 = (1 << 2),
    RTC_ALM_EN_WEEK3 = (1 << 3),
    RTC_ALM_EN_WEEK4 = (1 << 4),
    RTC_ALM_EN_WEEK5 = (1 << 5),
    RTC_ALM_EN_WEEK6 = (1 << 6),
    RTC_ALM_EN_WEEK7 = (1 << 0),
} eAlmWeek;

#define RTC_PRD_SEL_TIME_DATE 0
#define RTC_PRD_SEL_N_0P5S 1
#define PRD_N_0P5S(x) (x - 1)
typedef enum _PRD_TD {
    PRD_NO_INT = 0,
    PRD_0P5S,
    PRD_1S,
    PRD_1MINUTE,
    PRD_1HOUR,
    PRD_1DAY,
    PRD_1MONTH,
} ePRD_TDType;

#define RTC_CAL_SEL_LOW 0
#define RTC_CAL_SEL_HIGH 1

// extern function declare

void RTC_Init(u32 u32ClkSrc, u32 u32HourFM);
void RTC_DeInit(void);
void RTC_SetDate(int year, int month, int day, int week);
u32 RTC_GetData(void);
int RTC_GetYear(void);
int RTC_GetMonth(void);
int RTC_GetDay(void);
int RTC_GetWeek(void);
void RTC_SetTime(int hour, int minute, int sec);
u32 RTC_GetTime(void);
int RTC_GetHour(void);
int RTC_GetMinute(void);
int RTC_GetSecond(void);
void RTC_SetAlarm(int week, int hour, int minute);
void RTC_AlarmCofig(int en, int irqEn);
void RTC_PeriodCofig(int en, int irqEn, int prd_sel, int interval);
void RTC_1HzOutConfig(int en);
void RTC_CalibrationConfig(int en, int sel, int val);

#endif
