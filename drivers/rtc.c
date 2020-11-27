/**
 * @file rtc.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */
#include "sysc.h"
#include "pmu.h"
#include "rtc.h"
#include "iom.h"


/**
 * @brief RTC init
 *
 * @param u32ClkSrc:
 *      RTC_XTL,
        RTC_LRC,
        RTC_XTH_DIV128,
        RTC_XTH_DIV256,
        RTC_XTH_DIV512,
        RTC_XTH_DIV768,
 * @param u32HourFM:     RTC_FMT_12H , RTC_FMT_24H,
 */
void  RTC_Init(u32 u32ClkSrc,u32 u32HourFM)
{
    PARAM_CHECK( (u32ClkSrc != RTC_XTL) && (u32ClkSrc != RTC_LRC) && (u32ClkSrc != RTC_XTH_DIV128) && (u32ClkSrc != RTC_XTH_DIV256) && (u32ClkSrc != RTC_XTH_DIV512) && (u32ClkSrc !=RTC_XTH_DIV768));
    PARAM_CHECK( (u32HourFM != RTC_FMT_12H) && (u32HourFM != RTC_FMT_24H));
    SYSC->CLKENCFG |= SYSC_CLKENCFG_RTC;
    switch (u32ClkSrc)
    {
    case RTC_XTL:
        RTC->CON = RTC_CON_CKSEL_XTL;
        break;
    case RTC_LRC:
        RTC->CON = RTC_CON_CKSEL_LRC;
        break;
    case RTC_XTH_DIV128:
        RTC->CON = RTC_CON_CKSEL_XTH_DIV128;
        break;
    case RTC_XTH_DIV256:
        RTC->CON = RTC_CON_CKSEL_XTH_DIV256;
        break;
    case RTC_XTH_DIV512:
        RTC->CON = RTC_CON_CKSEL_XTH_DIV512;
        break;
    case RTC_XTH_DIV768:
        RTC->CON = RTC_CON_CKSEL_XTH_DIV768;
        break;
    }
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    if( u32HourFM == RTC_FMT_12H)
    {
        RTC->CON |= RTC_CON_FMT_12H;
    }
    else
    {
        RTC->CON |= RTC_CON_FMT_24H;
    }
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->CON |= RTC_CON_RTCEN;
}
/**
 * @brief RTC deinit
 *
 */
void RTC_DeInit(void)
{
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->CON = 0x20000000;
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->STS = 0xffffffff;
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    SYSC->CLKENCFG &= ~SYSC_CLKENCFG_RTC;
}
/**
 * @brief set date
 *
 * @param year 年 如:19 (2019)
 * @param month 月
 * @param day 天
 * @param week 星期
 *
 * @return BOOL ERROR  , SUCCESS
 */
void RTC_SetDate(int year,int month,int day,int week)
{
    PARAM_CHECK( (year<0) ||(year>99) || (month<1) || (month>12) || ( ((year%4==0)&&(month==2))? (day>29) : 0 ) || ( ((year%4!=0)&& (month==2))? (day>28) : 0 ) || ( ((month==4)||(month==6)||(month==9)||(month==11))? (day>30) : 0 ) ||( ((month==1)||(month==3)||(month==5)||(month==7)||(month==8)||(month==10)||(month==12))? (day>31) : 0 ) || (day<1) || (week<0) || (week>6));
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->CON |= RTC_CON_WAIT;
    while( ((RTC->STS & RTC_STS_WAITF) == 0)  );
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->DR =  ( (year/10)<<RTC_DR_YEARH_pos ) | ( (year%10)<<RTC_DR_YEARL_pos) | ((month/10)<<RTC_DR_MONH_pos) | ((month%10)<<RTC_DR_MONL_pos) |
     ((day/10)<<RTC_DR_DAYH_pos) | ((day%10)<<RTC_DR_DAYL_pos)  | ( (week)<<RTC_DR_WEEK_pos);

    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->CON &= ~RTC_CON_WAIT;
    while( ((RTC->STS & RTC_STS_WAITF) != 0)  );
}
/**
 * @brief : get date register value
 *
 * @return u32:date (year month day week)
 */
u32 RTC_GetData(void)
{
    return RTC->DR;
}
/**
 * @brief get year
 *
 * @return int year
 */
int RTC_GetYear(void)
{
    int yh = (RTC->DR & RTC_DR_YEARH) >> RTC_DR_YEARH_pos;
    int yl = (RTC->DR & RTC_DR_YEARL) >> RTC_DR_YEARL_pos;
    return 2000+yh*10+yl;
}

/**
 * @brief get month
 *
 * @return int :month
 */
int RTC_GetMonth(void)
{
    int mh = (RTC->DR & RTC_DR_MONH) >> RTC_DR_MONH_pos;
    int ml = (RTC->DR & RTC_DR_MONL) >> RTC_DR_MONL_pos;
    return mh*10+ml;
}
/**
 * @brief get day
 *
 * @return int day
 */
int RTC_GetDay(void)
{
    int dh = (RTC->DR & RTC_DR_DAYH) >> RTC_DR_DAYH_pos;
    int dl = (RTC->DR & RTC_DR_DAYL) >> RTC_DR_DAYL_pos;
    return dh*10+dl;
}
/**
 * @brief get week
 *
 * @return int 0-6  sunday-saturday
 */
int RTC_GetWeek(void)
{
    return (RTC->DR & RTC_DR_WEEK) >> RTC_DR_WEEK_pos;
}

/**
 * @brief 锛� set time
 *
 * @param hour :set hour
 * @param minute set minute
 * @param sec :set second
 */
void RTC_SetTime(int hour,int minute,int sec)
{
    PARAM_CHECK( (hour<0) || (hour>23) || (minute<0) || (minute>59) || (sec<0) || (sec>59));
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->CON |= RTC_CON_WAIT;
    while( ((RTC->STS & RTC_STS_WAITF) == 0) );
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->TR = ((hour/10)<<RTC_TR_HOURH_pos) | ((hour%10)<<RTC_TR_HOURL_pos) | ((minute/10)<<RTC_TR_MINH_pos) | ((minute%10)<<RTC_TR_MINL_pos) |
            ((sec/10)<<RTC_TR_SECH_pos) | ((sec%10)<<RTC_TR_SECL_pos);
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->CON &= ~RTC_CON_WAIT;
    while( ((RTC->STS & RTC_STS_WAITF) != 0) );
}

/**
 * @brief : get time register value
 *
 * @return u32锛歳eg val(hour minute second)
 */
u32 RTC_GetTime(void)
{
    return RTC->TR;
}
/**
 * @brief get hour
 *
 * @return int hour
 */
int RTC_GetHour(void)
{
    int hh = (RTC->TR & RTC_TR_HOURH) >> RTC_TR_HOURH_pos;
    int hl = (RTC->TR & RTC_TR_HOURL) >> RTC_TR_HOURL_pos;
    return hh*10 + hl;
}
/**
 * @brief get minute
 *
 * @return int:minute
 */
int RTC_GetMinute(void)
{
    int mh = (RTC->TR & RTC_TR_MINH) >> RTC_TR_MINH_pos;
    int ml = (RTC->TR & RTC_TR_MINL) >> RTC_TR_MINL_pos;
    return mh*10 + ml;
}
/**
 * @brief get second
 *
 * @return int: second
 */
int RTC_GetSecond(void)
{
    int sh = (RTC->TR & RTC_TR_SECH) >> RTC_TR_SECH_pos;
    int sl = (RTC->TR & RTC_TR_SECL) >> RTC_TR_SECL_pos;
    return sh*10 + sl;
}
/**
 * @brief :set alarm
 *
 * @param week surport '|' combin
 *  RTC_ALM_EN_WEEK1 |
    RTC_ALM_EN_WEEK2 |
    RTC_ALM_EN_WEEK3 |
    RTC_ALM_EN_WEEK4 |
    RTC_ALM_EN_WEEK5 |
    RTC_ALM_EN_WEEK6 |
    RTC_ALM_EN_WEEK7
 * @param hour 锛歨our
 * @param minute 锛歮inute
 */
void RTC_SetAlarm(int week,int hour,int minute)
{
    PARAM_CHECK((hour<0) || (hour>23) || (week<0) || (week>6) || (minute<0) || (minute>59));
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->CON |= RTC_CON_WAIT;
    while( ((RTC->STS & RTC_STS_WAITF) == 0) );
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->ALM = (week<<RTC_ALM_ALMWEEK_pos) | (hour/10<<RTC_ALM_ALMHOURH_pos) | (hour%10<<RTC_ALM_ALMHOURL_pos) |
    (minute/10<<RTC_ALM_ALMMINH_pos) | (minute%10<<RTC_ALM_ALMMINL_pos);
    RTC_WPR_REG = RTC_WPR_V0;
    RTC_WPR_REG = RTC_WPR_V1;
    RTC->CON &= ~RTC_CON_WAIT;
    while( ((RTC->STS & RTC_STS_WAITF) != 0) );
}

/**
 * @brief Alarm configure
 *
 * @param en :ENABLE , DISABLE
 * @param irqEn :ENABLE , DISABLE
 */
void RTC_AlarmCofig(int en,int irqEn)
{
    if( en == ENABLE)
    {
        RTC_WPT_UNLOCK();
        RTC->CON |= RTC_CON_ALMEN;
        if( irqEn == ENABLE)
        {
            RTC_WPT_UNLOCK();
            RTC->CON |= RTC_CON_ALMIE;
        }
        else
        {
            RTC_WPT_UNLOCK();
            RTC->CON &= ~RTC_CON_ALMIE;
        }
    }
    else
    {
        RTC_WPT_UNLOCK();
        RTC->CON &= ~RTC_CON_ALMEN;
    }

}

/**
 * @brief Alarm configure
 *
 * @param en :ENABLE , DISABLE
 * @param irqEn :ENABLE , DISABLE
 * @param prd_sel: RTC_PRD_SEL_TIME_DATE , RTC_PRD_SEL_N_0P5S
 * @param interval:ePRD_TDType,PRD_xx;
 * @note  PRD_N_0P5S(x):set 0.5*xs interval. exp:PRD_N_0P5S(2),1s interval note:1<=x<=64
 */
void RTC_PeriodCofig(int en,int irqEn,int prd_sel,int interval)
{
    if( en == ENABLE)
    {
        RTC_WPT_UNLOCK();
        RTC->CON |= RTC_CON_PRDEN;
        if( irqEn == ENABLE)
        {
            RTC_WPT_UNLOCK();
            RTC->CON |= RTC_CON_PRDIE;
        }
        else
        {
            RTC_WPT_UNLOCK();
            RTC->CON &= ~RTC_CON_PRDIE;
        }
    }
    else
    {
        RTC_WPT_UNLOCK();
        RTC->CON &= ~RTC_CON_PRDEN;
    }
    PARAM_CHECK( (prd_sel != RTC_PRD_SEL_TIME_DATE) && (prd_sel != RTC_PRD_SEL_N_0P5S));
    if( prd_sel == RTC_PRD_SEL_TIME_DATE)
    {
        RTC_WPT_UNLOCK();
        RTC->CON &= ~RTC_CON_PRDS;
        RTC_WPT_UNLOCK();
        RTC->CON |= interval<<RTC_CON_PRDS_pos;
    }
    else
    {
        PARAM_CHECK( (interval<0) || (interval>63) );
        RTC_WPT_UNLOCK();
        RTC->CON &= ~RTC_CON_PRDX;
        RTC_WPT_UNLOCK();
        RTC->CON |= interval<<RTC_CON_PRDX_pos;
    }
}
/**
 * @brief p08 1Hz output configure
 *
 * @param en :ENABLE , DISABLE
 */
void RTC_1HzOutConfig(int en)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_IOM;
    IOM->AF0 &= ~IOM_AF0_P08_SEL;
    IOM->AF0 |= IOM_AF0_P08_SEL_RTC_1HZ;
    if( en == ENABLE)
    {
        RTC_WPT_UNLOCK();
        RTC->CALR |= RTC_CALR_1HZ_OE;
    }
    else
    {
        RTC_WPT_UNLOCK();
        RTC->CALR &= ~RTC_CALR_1HZ_OE;
    }
}

/**
 * @brief calibration configure
 *
 * @param en :ENABLE , DISABLE
 * @param sel :RTC_CAL_SEL_LOW , RTC_CAL_SEL_HIGH
 * @param val : val
 */
void RTC_CalibrationConfig(int en,int sel,int val)
{
    if( en == ENABLE)
    {
        RTC_WPT_UNLOCK();
        RTC->CALR |= RTC_CALR_CAL_EN;
        PARAM_CHECK( (sel != RTC_CAL_SEL_HIGH) && (sel != RTC_CAL_SEL_LOW));
        if(sel == RTC_CAL_SEL_HIGH)
        {
            RTC_WPT_UNLOCK();
            RTC->CALR |= RTC_CALR_CAL_SEL;
        }
        else
        {
            RTC_WPT_UNLOCK();
            RTC->CALR &= ~RTC_CALR_CAL_SEL;
        }
        PARAM_CHECK(val>0x200);
        RTC_WPT_UNLOCK();
        RTC->CALR &= ~RTC_CALR_CR;
        RTC_WPT_UNLOCK();
        RTC->CALR |= val;
    }
    else
    {
        RTC_WPT_UNLOCK();
        RTC->CALR &= ~RTC_CALR_CAL_EN;
    }
}
