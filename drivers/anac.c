/**
 * @file anac.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */


#include "anac.h"
#include "sysc.h"


/**
 * @brief ANAC init
 *
 * @param freq :anac module freq (kHz)
 */
void ANAC_Init(int freq)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC;
    SystemCoreClockUpdate();
    int tmp = SystemCoreClock /1000 / freq;
    PARAM_CHECK( tmp < 2);
    int tmp1 = SystemCoreClock /1000 / (((tmp/2-1)+1)*2) /500000;
    PARAM_CHECK (tmp1 < 2);
    SYSC_SetANAC_CLKDiv(tmp/2-1,tmp1-1);
}

/**
 * @brief anac deinit
 *
 */
void ANAC_DeInit(void)
{
    int i;
    SYSC_WPT_UNLOCK();
    SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_ANAC;
    for(i=10;i>0;--i);
    SYSC->CLKENCFG &= ~SYSC_CLKENCFG_ANAC;
}


/**
 * @brief adc init
 *
 * @param chn ADC_CHN_xxx
 * @param buffEn ENABLE , DISABLE
 * @param verfSel ADC_VREF_SEL_xxx
 * @param verfVol ADC_VREF_VOLT_xxx
 * @param smpTimes ADC_SMP_TIMS_x
 * @param smpCycle ADC_SMP_CYCLE_xx
 */
void ADC_Init(int chn,int buffEn,int verfSel,int verfVol,int smpTimes,int smpCycle)
{
    ANAC->ADC_CFG = (chn<<7) | (verfSel<<4) | (verfVol<<1);
    if( buffEn == ENABLE)
    {
        ANAC->ADC_CFG |= (1<<6);
    }
    else
    {
        ANAC->ADC_CFG &= ~(1<<6);
    }
    if( verfSel == ADC_VREF_SEL_INT)
    {
        ANAC->ADC_CFG |= 0x01;
    }
    else
    {
        ANAC->ADC_CFG &= ~0x01;
    }
    ANAC->ADC_CTL = (smpTimes << 6) | (smpCycle << 4);
    if( smpTimes > 0)
    {
        ANAC->ADC_CTL |= (1<<3);
    }
}
/**
 * @brief ADC enalble
 *
 */
void ADC_Enable(void)
{
    ANAC->ADC_CTL |= 0x01;
}
/**
 * @brief ADC disable
 *
 */
void ADC_Disable(void)
{
    ANAC->ADC_CTL &= ~0x01;
}

/**
 * @brief ADC enable interrupt
 *
 */
void ADC_EnableIRQ(void)
{
    ANAC->ADC_CTL |= (1<<1);
}
/**
 * @brief start AD convert
 *
 */

/**
 * @brief ADC disable interrupt
 *
 */
void ADC_DisableIRQ(void)
{
    ANAC->ADC_CTL &= ~(1<<1);
}
/**
 * @brief ADC start convert
 *
 */
void ADC_StartConvert(void)
{
    ANAC->ADC_CTL |= (1<<2);
}


/**
 * @brief ADC get single convert result value
 *
 * @param valNo :ADC_VAL_NOx
 * @return u32 :val
 */
u32 ADC_GetSingleResultValue(int valNo)
{
    PARAM_CHECK(valNo>7);
    return ANAC->ADC_VAL[valNo];
}

/**
 * @brief get convert average value
 *
 * @return u32
 */
u32 ADC_GetAverageValue(void)
{
    return ANAC->AVG_VAL;
}
/**
 * @brief get interrupt flag
 *
 * @return BOOL
 */
BOOL ADC_GetIntFlag(void)
{
    return (ANAC->ANAC_FLAG & 0x01)? TRUE : FALSE;
}
/**
 * @brief clear interrupt flag
 *
 */
void ADC_ClrIntFlag(void)
{
    ANAC->ANAC_FLAG |= 0x01;
}
























