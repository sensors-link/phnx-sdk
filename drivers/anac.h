/**
 * @file anac.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __ANAC_H
#define __ANAC_H
#include "phnx02.h"
// register definitions
#define ANAC_LED_CFG_REG    REG32(ANAC_BASE + 0x04)
#define ANAC_PDSENS_CFG_REG REG32(ANAC_BASE + 0x08)
#define ANAC_DC_CFG_REG     REG32(ANAC_BASE + 0x0C)
#define ANAC_CMP_CFG_REG    REG32(ANAC_BASE + 0x10)
#define ANAC_ADC_CFG_REG    REG32(ANAC_BASE + 0x14)
#define ANAC_ADC_CTL_REG    REG32(ANAC_BASE + 0x18)
#define ANAC_ANAC_CFG_REG   REG32(ANAC_BASE + 0x1C)
#define ANAC_LVD_CFG_REG    REG32(ANAC_BASE + 0x20)
#define ANAC_CLK_CFG_REG    REG32(ANAC_BASE + 0x24)
#define ANAC_HRC_TRIM_REG   REG32(ANAC_BASE + 0x28)
#define ANAC_LRC_TRIM_REG   REG32(ANAC_BASE + 0x2C)
#define ANAC_CMP_TRIM_REG   REG32(ANAC_BASE + 0x30)
#define ANAC_BG4A_TRIM_REG  REG32(ANAC_BASE + 0x34)
#define ANAC_BG4S_TRIM_REG  REG32(ANAC_BASE + 0x38)
#define ANAC_TESTCTL_REG    REG32(ANAC_BASE + 0x3C)
#define ANAC_AINSEL_REG     REG32(ANAC_BASE + 0x40)
#define ANAC_MRC_TRIM_REG   REG32(ANAC_BASE + 0x44)
#define ANAC_DLY_CFG_REG    REG32(ANAC_BASE + 0x48)
#define ANAC_ME_CTL_REG     REG32(ANAC_BASE + 0x4C)
#define ANAC_ANAC_FLAG_REG  REG32(ANAC_BASE + 0x50)
#define ANAC_TEST_REG       REG32(ANAC_BASE + 0x54)
#define ANAC_WPROT_REG      REG32(ANAC_BASE + 0x58)
#define ANAC_THR1_DATA_REG  REG32(ANAC_BASE + 0x5C)
#define ANAC_THR2_DATA_REG  REG32(ANAC_BASE + 0x60)

// register bits definitions
// led_cfg
#define ANAC_LED_CFG_LED_SEL      BIT(13)
#define ANAC_LED_CFG_LED_SEL_IR   (0 << 13)
#define ANAC_LED_CFG_LED_SEL_BLUE (1 << 13)

#define ANAC_LED_CFG_INDLED_EN BIT(12)
#define ANAC_LED_CFG_IBULE_CC  BITS(7, 11)
#define ANAC_LED_CFG_IBLUE_EN  BIT(6)
#define ANAC_LED_CFG_IIRLED_CC BITS(1, 5)
#define ANAC_LED_CFG_IIRLED_EN BIT(0)

#define ANAC_LED_CFG_IBULE_CC_pos  (7) // 0-0x1f:0-310mA step:10mA
#define ANAC_LED_CFG_IIRLED_CC_pos (1)

// pdsens_cfg
#define ANAC_PDSENS_CFG_CHRG    BIT(7)
#define ANAC_PDSENS_CFG_GC      BITS(2, 6)
#define ANAC_PDSENS_CFG_GC_X50  (0 << 6)
#define ANAC_PDSENS_CFG_GC_X100 (1 << 6)

#define ANAC_PDSENS_CFG_GC_DB     BIT(2, 5)
#define ANAC_PDSENS_CFG_GC_DB_pos (2) // 0-16 (x+1)dB

#define ANAC_PDSENS_CFG_RST BIT(1)
#define ANAC_PDSENS_CFG_EN  BIT(0)

// dcbz_cfg
#define ANAC_DCBZ_CFG_BZ_PWM_SEL   BITS(18, 19)
#define ANAC_DCBZ_CFG_BZ_MSEL      BIT(17)
#define ANAC_DCBZ_CFG_BZ_EN        BIT(16)
#define ANAC_DCBZ_CFG_DCDC_DISCH   BIT(11)
#define ANAC_DCBZ_CFG_DCDC_VOSW    BITS(9, 10)
#define ANAC_DCBZ_CFG_DCDC_TONTRIM BITS(7, 8)
#define ANAC_DCBZ_CFG_DCDC_VOTRIM  BITS(5, 6)
#define ANAC_DCBZ_CFG_DCDC_VSL     BITS(3, 4)
#define ANAC_DCBZ_CFG_DCDC_IPK     BITS(1, 2)
#define ANAC_DCBZ_CFG_DCDC_EN      BIT(0)

#define ANAC_DCBZ_CFG_BZ_PWM_SEL_TIM4_TOG (0 << 18)
#define ANAC_DCBZ_CFG_BZ_PWM_SEL_TIM1_TOG (1 << 18)
#define ANAC_DCBZ_CFG_BZ_PWM_SEL_TIM2_TOG (2 << 18)
#define ANAC_DCBZ_CFG_BZ_PWM_SEL_TIM3_TOG (3 << 18)

#define ANAC_DCBZ_CFG_DCDC_VOSW_BZ  (0 << 9)
#define ANAC_DCBZ_CFG_DCDC_VOSW_LED (2 << 9)

#define ANAC_DCBZ_CFG_DCDC_VOSW_pos    (9)
#define ANAC_DCBZ_CFG_DCDC_TONTRIM_pos (7)
#define ANAC_DCBZ_CFG_DCDC_VOTRIM_pos  (5)
#define ANAC_DCBZ_CFG_DCDC_VSL_pos     (3)
#define ANAC_DCBZ_CFG_DCDC_IPK_pos     (1)

#define ANAC_DCBZ_CFG_DCDC_VSL_4P5V (0 << 3)
#define ANAC_DCBZ_CFG_DCDC_VSL_5P5V (1 << 3)
#define ANAC_DCBZ_CFG_DCDC_VSL_8V   (2 << 3)
#define ANAC_DCBZ_CFG_DCDC_VSL_10V  (3 << 3)

#define ANAC_DCBZ_CFG_DCDC_IPK_1   (0 << 1)
#define ANAC_DCBZ_CFG_DCDC_IPK_0P8 (1 << 1)
#define ANAC_DCBZ_CFG_DCDC_IPK_0P9 (2 << 1)
#define ANAC_DCBZ_CFG_DCDC_IPK_1P1 (3 << 1)

// cmp_cfg
// #define ANAC_CMP_CFG_FLT    BITS(10, 13)
#define ANAC_CMP_CFG_HYSSEL BITS(8, 9)
#define ANAC_CMP_CFG_VINSEL BITS(5, 7)
#define ANAC_CMP_CFG_VIPSEL BITS(2, 4)
#define ANAC_CMP_CFG_INV    BIT(1)
#define ANAC_CMP_CFG_EN     BIT(0)

#define ANAC_CMP_CFG_FLT_pos (10)

#define ANAC_CMP_CFG_HYSSEL_50MV (3 << 8)
#define ANAC_CMP_CFG_HYSSEL_25MV (2 << 8)
#define ANAC_CMP_CFG_HYSSEL_12MV (1 << 8)
#define ANAC_CMP_CFG_HYSSEL_0MV  (0 << 8)

#define ANAC_CMP_CFG_VINSEL_V1P5S    (7 << 5)
#define ANAC_CMP_CFG_VINSEL_VBGA     (6 << 5)
#define ANAC_CMP_CFG_VINSEL_VBGS     (5 << 5)
#define ANAC_CMP_CFG_VINSEL_V1P5D    (4 << 5)
#define ANAC_CMP_CFG_VINSEL_INT_VREF (3 << 5)
#define ANAC_CMP_CFG_VINSEL_VREF     (2 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N1    (1 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N0    (0 << 5)

#define ANAC_CMP_CFG_VIPSEL_BVS_VO (7 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBGA   (6 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P5  (5 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P4  (4 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P3  (3 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P2  (2 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P1  (1 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P0  (0 << 2)

// adc_cfg
#define ANAC_ADC_CFG_ADC_IBSEL     BITS(11, 12)
#define ANAC_ADC_CFG_ADC_CHSEL     BITS(7, 10)
#define ANAC_ADC_CFG_ADC_BUFEN     BIT(6)
#define ANAC_ADC_CFG_ADC_VRSEL     BITS(4, 5)
#define ANAC_ADC_CFG_VOLTREF_VRSEL BITS(1, 3)
#define ANAC_ADC_CFG_VOLTREF_EN    BIT(0)

#define ANAC_ADC_CFG_ADC_IBSEL_pos (11)

#define ANAC_ADC_CFG_ADC_CHSEL_TSENS     (0x0e << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_BVS_VO    (0x0d << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_PDSENS_VO (0x0c << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN11     (0x0b << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN10     (0x0a << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN9      (0x09 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN8      (0x08 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN7      (0x07 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN6      (0x06 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN5      (0x05 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN4      (0x04 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN3      (0x03 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN2      (0x02 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN1      (0x01 << 7)
#define ANAC_ADC_CFG_ADC_CHSEL_AIN0      (0x00 << 7)

#define ANAC_ADC_CFG_ADC_VRSEL_INT_VREF (0 << 4)
#define ANAC_ADC_CFG_ADC_VRSEL_EXT_VREF (1 << 4)
#define ANAC_ADC_CFG_ADC_VRSEL_VCC      (2 << 4)

#define ANAC_ADC_CFG_VOLTREF_VRSEL_1P2 (0 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_1P5 (1 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_2P0 (2 << 1)
#define ANAC_ADC_CFG_VOLTREF_VRSEL_2P5 (3 << 1)

// adc_ctl
#define ANAC_ADC_CTL_SMP_TIME   BITS(6, 7)
#define ANAC_ADC_CTL_SMP_CYCLE  BITS(4, 5)
#define ANAC_ADC_CTL_MULTI_MODE BIT(3)
#define ANAC_ADC_CTL_SST        BIT(2)
#define ANAC_ADC_CTL_ADC_IE     BIT(1)
#define ANAC_ADC_CTL_ADC_EN     BIT(0)

#define ANAC_ADC_CTL_SMP_TIME_1 (0 << 6)
#define ANAC_ADC_CTL_SMP_TIME_2 (1 << 6)
#define ANAC_ADC_CTL_SMP_TIME_4 (2 << 6)
#define ANAC_ADC_CTL_SMP_TIME_8 (3 << 6)

#define ANAC_ADC_CTL_SMP_CYCLE_16ADCCLK (0 << 4)
#define ANAC_ADC_CTL_SMP_CYCLE_12ADCCLK (1 << 4)
#define ANAC_ADC_CTL_SMP_CYCLE_8ADCCLK  (2 << 4)
#define ANAC_ADC_CTL_SMP_CYCLE_4ADCCLK  (3 << 4)

// anac_cfg
#define ANAC_ANAC_CFG_INTF_ISOEN   BIT(16)
#define ANAC_ANAC_CFG_THERMD_EN    BIT(15)
#define ANAC_ANAC_CFG_BVS_ISNKSEL  BITS(11, 14)
#define ANAC_ANAC_CFG_BVS_EN       BIT(10)
#define ANAC_ANAC_CFG_ALDO4A_VOSEL BITS(8, 9)
#define ANAC_ANAC_CFG_ALDO4A_EN    BIT(7)
#define ANAC_ANAC_CFG_BGR_EN       BIT(6)
#define ANAC_ANAC_CFG_ALDO4D_IBSEL BITS(4, 5)
#define ANAC_ANAC_CFG_ALDO4D_LPEN  BIT(3)
#define ANAC_ANAC_CFG_ALDO4D_EN    BIT(2)
#define ANAC_ANAC_CFG_SLDO_VRSEL   BITS(0, 1)

#define ANAC_ANAC_CFG_BVS_ISNKSEL_0MA   (0 << 11)
#define ANAC_ANAC_CFG_BVS_ISNKSEL_7P5MA (1 << 11)
#define ANAC_ANAC_CFG_BVS_ISNKSEL_15MA  (2 << 11)
#define ANAC_ANAC_CFG_BVS_ISNKSEL_30MA  (3 << 11)

#define ANAC_ANAC_CFG_ALDO4A_VOSEL_1P5  (0 << 8)
#define ANAC_ANAC_CFG_ALDO4A_VOSEL_1P55 (1 << 8)
#define ANAC_ANAC_CFG_ALDO4A_VOSEL_1P6  (2 << 8)
#define ANAC_ANAC_CFG_ALDO4A_VOSEL_1P7  (3 << 8)

#define ANAC_ANAC_CFG_ALDO4D_IBSEL_pos (4)

#define ANAC_ANAC_CFG_SLDO_VRSEL_1P5 (0 << 8)
#define ANAC_ANAC_CFG_SLDO_VRSEL_1P2 (1 << 8)
// #define ANAC_ANAC_CFG_SLDO_VRSEL_1P0 (2 << 8)
// #define ANAC_ANAC_CFG_SLDO_VRSEL_0P8 (3 << 8)

// lvd_cfg
#define ANAC_LVD_CFG_IBTRIM BITS(16, 17)
#define ANAC_LVD_CFG_FLT    BITS(8, 15)
#define ANAC_LVD_CFG_IE     BIT(7)
#define ANAC_LVD_CFG_VTSEL  BITS(3, 6)
#define ANAC_LVD_CFG_SRCSEL BITS(1, 2)
#define ANAC_LVD_CFG_EN     BIT(0)

#define ANAC_LVD_CFG_IBTRIM_pos (16)
#define ANAC_LVD_CFG_FLT_pos    (8)
#define ANAC_LVD_CFG_VTSEL_pos  (3)

#define ANAC_LVD_CFG_SRCSEL_LOWPWR_V5P0 (0 << 1)
#define ANAC_LVD_CFG_SRCSEL_V5P0        (1 << 1)
#define ANAC_LVD_CFG_SRCSEL_LVDI0       (2 << 1)
#define ANAC_LVD_CFG_SRCSEL_LVDI1       (3 << 1)

// clk_cfg
#define ANAC_CLK_CFG_HRC_DLYTRIM BIT(16)
#define ANAC_CLK_CFG_MRC_EN      BIT(15)
#define ANAC_CLK_CFG_XTH_EN      BIT(14)
#define ANAC_CLK_CFG_XTL_RTRIM   BITS(12, 13)
#define ANAC_CLK_CFG_XTL_CSET    BITS(6, 11)
#define ANAC_CLK_CFG_XTL_EN      BIT(5)
#define ANAC_CLK_CFG_HRC_FSEL    BITS(2, 4)
#define ANAC_CLK_CFG_HRC_EN      BIT(1)
#define ANAC_CLK_CFG_LRC_EN      BIT(0)

#define ANAC_CLK_CFG_XTL_RTRIM_pos (12)
#define ANAC_CLK_CFG_XTL_CSET_pos  (6)

// #define ANAC_CLK_CFG_HRC_FSEL_8M (0 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_1M  (1 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_2M  (2 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_4M  (3 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_8M  (4 << 2)
#define ANAC_CLK_CFG_HRC_FSEL_16M (5 << 2)
// #define ANAC_CLK_CFG_HRC_FSEL_24M (6 << 2)
// #define ANAC_CLK_CFG_HRC_FSEL_32M (7 << 2)
// ANAC_AINSEL
#define ANAC_AINSEL_GPIO0_SEL_IND    (0 << 0)
#define ANAC_AINSEL_GPIO0_SEL_VC1P0  (1 << 0)
#define ANAC_AINSEL_GPIO1_SEL_AIN04  (0 << 1)
#define ANAC_AINSEL_GPIO1_SEL_VC1O   (1 << 1)
#define ANAC_AINSEL_GPIO2_SEL_XTHI   (0 << 2)
#define ANAC_AINSEL_GPIO2_SEL_AIN11  (1 << 2)
#define ANAC_AINSEL_GPIO3_SEL_XTHO   (0 << 3)
#define ANAC_AINSEL_GPIO3_SEL_VC1O   (1 << 3)
#define ANAC_AINSEL_GPIO4_SEL_LVDI0  (0 << 4)
#define ANAC_AINSEL_GPIO4_SEL_AIN02  (1 << 4)
#define ANAC_AINSEL_GPIO5_SEL_LVDI1  (0 << 5)
#define ANAC_AINSEL_GPIO5_SEL_VC1P6  (1 << 5)
#define ANAC_AINSEL_GPIO6_SEL_VC1P2  (0 << 6)
#define ANAC_AINSEL_GPIO6_SEL_AIN05  (1 << 6)
#define ANAC_AINSEL_GPIO7_SEL_VC1P3  (0 << 7)
#define ANAC_AINSEL_GPIO7_SEL_AIN06  (1 << 7)
#define ANAC_AINSEL_GPIO8_SEL_VC1N0  (0 << 8)
#define ANAC_AINSEL_GPIO8_SEL_AIN07  (1 << 8)
#define ANAC_AINSEL_GPIO9_SEL_VC1N1  (0 << 9)
#define ANAC_AINSEL_GPIO9_SEL_LVDI0  (1 << 9)
#define ANAC_AINSEL_GPIO10_SEL_VC1P4 (0 << 10)
#define ANAC_AINSEL_GPIO10_SEL_AIN08 (1 << 10)
#define ANAC_AINSEL_GPIO11_SEL_AIN09 (0 << 11)
#define ANAC_AINSEL_GPIO11_SEL_VC1N1 (1 << 11)
#define ANAC_AINSEL_GPIO12_SEL_TRDRV (0 << 12)
#define ANAC_AINSEL_GPIO12_SEL_LVDI1 (1 << 12)
#define ANAC_AINSEL_GPIO13_SEL_TSENS (0 << 13)
#define ANAC_AINSEL_GPIO13_SEL_VC1P5 (1 << 13)
#define ANAC_AINSEL_GPIO14_SEL_VREF (0 << 14)
#define ANAC_AINSEL_GPIO14_SEL_AIN10 (1 << 14)
#define ANAC_AINSEL_GPIO15_SEL_VC1P1 (0 << 15)
#define ANAC_AINSEL_GPIO15_SEL_ATVC (1 << 15)
#define ANAC_AINSEL_GPIO16_SEL_XTLI (0 << 16)
#define ANAC_AINSEL_GPIO16_SEL_AIN03 (1 << 16)
#define ANAC_AINSEL_GPIO17_SEL_XTLO (0 << 17)
#define ANAC_AINSEL_GPIO17_SEL_AIN02 (1 << 17)
#define ANAC_AINSEL_GPIO18_SEL_AIN01 (0 << 18)
#define ANAC_AINSEL_GPIO18_SEL_VC1N0 (1 << 18)
#define ANAC_AINSEL_GPIO19_SEL_AIN00 (0 << 19)
#define ANAC_AINSEL_GPIO19_SEL_LVDI0 (1 << 19)

// dly_cfg
#define ANAC_DLY_CFG_LED_PW         BITS(18, 25)
#define ANAC_DLY_CFG_SMOKE_DLY      BITS(10, 17)
#define ANAC_DLY_CFG_PDSENS_RST_DLY BIT(8, 9)
#define ANAC_DLY_CFG_TEMP_DLY       BIT(6, 7)
#define ANAC_DLY_CFG_ADC_DLY        BIT(4, 5)
#define ANAC_DLY_CFG_ALDO4A_DLY     BIT(2, 3)
#define ANAC_DLY_CFG_BGR_DLY        BIT(0, 1)

#define ANAC_DLY_CFG_LED_PW_pos         (18)
#define ANAC_DLY_CFG_SMOKE_DLY_pos      (10)
#define ANAC_DLY_CFG_PDSENS_RST_DLY_pos (8)
#define ANAC_DLY_CFG_TEMP_DLY_pos       (6)
#define ANAC_DLY_CFG_ADC_DLY_pos        (4)
#define ANAC_DLY_CFG_ALDO4A_DLY_pos     (2)
#define ANAC_DLY_CFG_BGR_DLY_pos        (0)

// me_ctl
#define ANAC_ME_CTL_ADC_TRIG_SEL BITS(8, 10)
#define ANAC_ME_CTL_THRCMP_EN    BIT(7)
#define ANAC_ME_CTL_MODE_SEL     BITS(5, 6)
#define ANAC_ME_CTL_ME_AUTO      BIT(4)
#define ANAC_ME_CTL_ME_MODE      BIT(3)
#define ANAC_ME_CTL_THR_IE       BIT(2)
#define ANAC_ME_CTL_ME_RST       BIT(1)
#define ANAC_ME_CTL_ANAC_EN      BIT(0)

#define ANAC_ME_CTL_ADC_TRIG_SEL_LPTINT  (0 << 8)
#define ANAC_ME_CTL_ADC_TRIG_SEL_TIM1INT (1 << 8)
#define ANAC_ME_CTL_ADC_TRIG_SEL_TIM2INT (2 << 8)
#define ANAC_ME_CTL_ADC_TRIG_SEL_TIM3INT (3 << 8)
#define ANAC_ME_CTL_ADC_TRIG_SEL_TIM4INT (4 << 8)
#define ANAC_ME_CTL_ADC_TRIG_SEL_RTCINT  (5 << 8)

#define ANAC_ME_CTL_MODE_SEL_AD_AUTO       (0 << 5)
#define ANAC_ME_CTL_MODE_SEL_TP_AUTO       (1 << 5)
#define ANAC_ME_CTL_MODE_SEL_DARK_CUR_AUTO (2 << 5)
#define ANAC_ME_CTL_MODE_SEL_SMOKE_AUTO    (3 << 5)

// anac_flag
#define ANAC_ANAC_FLAG_BZ_FO       BIT(11)
#define ANAC_ANAC_FLAG_CMP_OUT     BIT(10)
#define ANAC_ANAC_FLAG_LVD_OUT     BIT(9)
#define ANAC_ANAC_FLAG_DCDC_VOK    BIT(8)
#define ANAC_ANAC_FLAG_ANA_OK_INTF BIT(3)
#define ANAC_ANAC_FLAG_LVD_INTF    BIT(2)
#define ANAC_ANAC_FLAG_THR_INTF    BIT(1)
#define ANAC_ANAC_FLAG_ADC_INTF    BIT(0)

#define ANAC_WPROT_V0 0x5a5a
#define ANAC_WPROT_V1 0xa5a5
#define ANAC_WPT_UNLOCK()                                                                                              \
    {                                                                                                                  \
        ANAC->WPROT = 0x5a5a;                                                                                          \
        ANAC->WPROT = 0xa5a5;                                                                                          \
    }

// ADC macro define
#define ADC_CHN_AIN0     0
#define ADC_CHN_AIN1     1
#define ADC_CHN_AIN2     2
#define ADC_CHN_AIN3     3
#define ADC_CHN_AIN4     4
#define ADC_CHN_AIN5     5
#define ADC_CHN_AIN6     6
#define ADC_CHN_AIN7     7
#define ADC_CHN_AIN8     8
#define ADC_CHN_AIN9     9
#define ADC_CHN_AIN10    10
#define ADC_CHN_AIN11    11
#define ADC_CHN_SENSOR_O 12
#define ADC_CHN_BVS_O    13
#define ADC_CHN_TSENS    14

#define ADC_VREF_SEL_INT 0
#define ADC_VREF_SEL_EXT 1
#define ADC_VREF_SEL_VCC 2

#define ADC_VREF_VOLT_1P2 0
#define ADC_VREF_VOLT_1P5 1
#define ADC_VREF_VOLT_2P0 2
#define ADC_VREF_VOLT_2P5 3

#define ADC_SMP_TIMS_1 0
#define ADC_SMP_TIMS_2 1
#define ADC_SMP_TIMS_4 2
#define ADC_SMP_TIMS_8 3

#define ADC_SMP_CYCLE_16 0
#define ADC_SMP_CYCLE_12 1
#define ADC_SMP_CYCLE_8  2
#define ADC_SMP_CYCLE_4  3

typedef enum _ADC_VAL_NO
{
    ADC_VAL_NO0 = 0,
    ADC_VAL_NO1,
    ADC_VAL_NO2,
    ADC_VAL_NO3,
    ADC_VAL_NO4,
    ADC_VAL_NO5,
    ADC_VAL_NO6,
    ADC_VAL_NO7,
} ADC_VAL_NO;

// DCDC Buzzer macro define

// extern function declare
void ANAC_Init(int freq);
void ANAC_DeInit(void);
void ADC_Init(int chn, int buffEn, int verfSel, int verfVol, int smpTimes, int smpCycle);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_EnableIRQ(void);
void ADC_DisableIRQ(void);
void ADC_StartConvert(void);
u32  ADC_GetSingleResultValue(int valNo);
u32  ADC_GetAverageValue(void);
BOOL ADC_GetIntFlag(void);
void ADC_ClrIntFlag(void);

#endif
