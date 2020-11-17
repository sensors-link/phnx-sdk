/**
 * @file spi.c
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "spi.h"
#include "sysc.h"
#include "iom.h"

/**
 * @brief  SPI init
 *
 * @param pin :SPI_PIN_0_1_2_3 , SPI_PIN_12_13_14_15 , SPI_PIN_19_18_16_17
 * @param mode:SPI_MASTER , SPI_SLAVE
 * @param pol:SPI_CPOL_HIGH , SPI_CPOL_LOW
 * @param phase:SPI_CPHA_FIST , SPI_CPHA_MIDD
 * @param freq :set N (kHz)
 */
void SPI_Init(int pin, int mode, int pol, int phase, int freq)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_SPI | SYSC_CLKENCFG_IOM;
    PARAM_CHECK((pin != SPI_PIN_0_1_2_3) && (pin != SPI_PIN_12_13_14_15) && (pin != SPI_PIN_19_18_16_17));
    if (pin == SPI_PIN_0_1_2_3)
    {
        IOM->AF0 &= ~(IOM_AF0_P00_SEL | IOM_AF0_P01_SEL | IOM_AF0_P02_SEL | IOM_AF0_P03_SEL);
        IOM->AF0 |=
            (IOM_AF0_P00_SEL_SPI_CS | IOM_AF0_P01_SEL_SPI_SCK | IOM_AF0_P02_SEL_SPI_MOSI | IOM_AF0_P03_SEL_SPI_MISO);
    }
    else if (pin == SPI_PIN_12_13_14_15)
    {
        IOM->AF0 &= ~(IOM_AF0_P12_SEL | IOM_AF0_P13_SEL | IOM_AF0_P14_SEL | IOM_AF0_P15_SEL);
        IOM->AF0 |=
            (IOM_AF0_P12_SEL_SPI_CS | IOM_AF0_P13_SEL_SPI_SCK | IOM_AF0_P14_SEL_SPI_MOSI | IOM_AF0_P15_SEL_SPI_MISO);
    }
    else
    {
        IOM->AF1 &= ~(IOM_AF1_P19_SEL | IOM_AF1_P18_SEL | IOM_AF1_P16_SEL | IOM_AF1_P17_SEL);
        IOM->AF1 |=
            (IOM_AF1_P19_SEL_SPI_CS | IOM_AF1_P18_SEL_SPI_SCK | IOM_AF1_P16_SEL_SPI_MOSI | IOM_AF1_P17_SEL_SPI_MISO);
    }
    PARAM_CHECK((pol != SPI_CPOL_HIGH) && (pol != SPI_CPOL_LOW));
    PARAM_CHECK((phase != SPI_CPHA_FIST) && (phase != SPI_CPHA_MIDD));
    PARAM_CHECK((mode != SPI_SR_MSTCFSR) && (mode != SPI_SLAVE));
    if (pol == SPI_CPOL_HIGH)
        SPI->CR0 |= SPI_CR0_CPOL;
    else
        SPI->CR0 &= ~SPI_CR0_CPOL;
    if (phase == SPI_CPHA_MIDD)
    {
        SPI->CR0 |= SPI_CR0_CPHA;
    }
    else
    {
        SPI->CR0 &= ~SPI_CR0_CPHA;
    }
    if (mode == SPI_MASTER)
    {
        SPI->CR0 |= SPI_CR0_MSMODE;
        SystemCoreClockUpdate();
        PARAM_CHECK((SystemCoreClock / (freq * 1000) < 2) || (SystemCoreClock / (freq * 1000) > 256));
        int div = SystemCoreClock / (freq * 1000);
        int tmp = 0;
        while (1)
        {
            if (div < 2)
                break;
            tmp += 1;
            div >>= 1;
        }
        SPI->CR0 &= ~SPI_CR0_SCLKDIV;
        SPI->CR0 |= ((tmp - 1) << SPI_CR0_SCLKDIV_pos);
    }
    else
    {
        SPI->CR0 &= ~SPI_CR0_MSMODE;
    }
}

/**
 * @brief spi deinit
 *
 */
void SPI_DeInit(void)
{
    int i;
    SYSC_WPT_UNLOCK();
    SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_SPI;
    for (i = 4; i > 0; --i)
        ;
    SYSC->CLKENCFG &= ~SYSC_CLKENCFG_SPI;
}

/**
 * @brief :master Conflict interrupt Control
 *
 * @param ctl :ENABLE , DISABLE
 */
void SPI_MasterConflictIRQControl(ControlStatus ctl)
{
    if (ctl == ENABLE)
    {
        SPI->CR0 |= SPI_CR0_MSTCFIE;
    }
    else
    {
        SPI->CR0 &= ~SPI_CR0_MSTCFIE;
    }
}

/**
 * @brief trasfer done interrupt enable
 *
 */
void SPI_EnableIRQ(void)
{
    SPI->CR0 |= SPI_CR0_DONEIE;
}
/**
 * @brief trasfer done interrupt disable
 *
 */
void SPI_DisableIRQ(void)
{
    SPI->CR0 &= ~SPI_CR0_DONEIE;
}

/**
 * @brief set CS high
 *
 */
void SPI_SetCSN(void)
{
    SPI->CSN = 0x01;
}
/**
 * @brief set cs low
 *
 */
void SPI_ClrCSN(void)
{
    SPI->CSN = 0;
}

/**
 * @brief send data
 *
 * @param data :8bit data
 */
void SPI_SendData(u8 data)
{
    SPI->DR = data;
}
/**
 * @brief recieve data
 *
 * @return u8 :8bit data
 */
u8 SPI_RecieveData(void)
{
    return SPI->DR;
}

/**
 * @brief get status register value
 *
 * @return u32: status reg val
 */
u32 SPI_GetStatus(void)
{
    return SPI->SR;
}
