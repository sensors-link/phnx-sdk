/**
 * @file anac.h
 * @author David.lin
 * @brief
 * @version 0.1
 * @date 2021-06-04
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __ANAC_H__
#define __ANAC_H__
#include "../include/phnx05.h"
// register definitions
#define ANAC_CFG_REG		 REG32(ANAC_BASE + 0x00)
#define ANAC_CMP_CFG_REG	 REG32(ANAC_BASE + 0x04)
#define ANAC_LVD_CFG_REG	 REG32(ANAC_BASE + 0x08)
#define ANAC_AINSEL_REG		 REG32(ANAC_BASE + 0x0C)
#define ANAC_CLK_TRIM_REG	 REG32(ANAC_BASE + 0x10)
#define ANAC_FLG_REG		 REG32(ANAC_BASE + 0x14)
#define ANAC_WPROT_REG		 REG32(ANAC_BASE + 0x18)
#define ANAC_HRC_TRIM_REG	 REG32(ANAC_BASE + 0x40)
#define ANAC_LRC_TRIM_REG	 REG32(ANAC_BASE + 0x44)
#define ANAC_BG4S_TRIM_REG	 REG32(ANAC_BASE + 0x48)
#define ANAC_CMP_TRIM_REG	 REG32(ANAC_BASE + 0x4C)
#define ANAC_HRC_IBTRIM_REG	 REG32(ANAC_BASE + 0x50)
#define ANAC_NVR_OPTION0_REG REG32(ANAC_BASE + 0x54)
#define ANAC_ANAC_REV0_REG	 REG32(ANAC_BASE + 0x58)
#define ANAC_TESTCTL_REG	 REG32(ANAC_BASE + 0x5C)
#define ANAC_TEST_REG		 REG32(ANAC_BASE + 0x60)
#define ANAC_NVR_OPTION1_REG REG32(ANAC_BASE + 0x80)
#define EST_CFG_REG			 REG32(ANAC_BASE + 0x88)
#define EST_RAM_BIST_REG	 REG32(ANAC_BASE + 0x8C)

// register bits definitions
// ANAC_CFG
#define ANAC_SLDO_VRSEL BIT(3)
#define ANAC_HRC_EN		BIT(2)
#define ANAC_LRC_EN		BIT(1)
#define ALDO4D_EN		BIT(0)

// CMP_CFG
#define ANAC_CMP_CFG_HYSSEL BITS(8, 9)
#define ANAC_CMP_CFG_VINSEL BITS(5, 7)
#define ANAC_CMP_CFG_VIPSEL BITS(2, 4)
#define ANAC_CMP_CFG_INV	BIT(1)
#define ANAC_CMP_CFG_EN		BIT(0)

#define ANAC_CMP_CFG_HYSSEL_50MV (3 << 8)
#define ANAC_CMP_CFG_HYSSEL_25MV (2 << 8)
#define ANAC_CMP_CFG_HYSSEL_12MV (1 << 8)
#define ANAC_CMP_CFG_HYSSEL_0MV	 (0 << 8)

#define ANAC_CMP_CFG_VINSEL_VBG1P2	   (7 << 5)
#define ANAC_CMP_CFG_VINSEL_VBG1P0	   (6 << 5)
#define ANAC_CMP_CFG_VINSEL_VREF_FLASH (5 << 5)
#define ANAC_CMP_CFG_VINSEL_V1P5D	   (4 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N3	   (3 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N2	   (2 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N1	   (1 << 5)
#define ANAC_CMP_CFG_VINSEL_VC1N0	   (0 << 5)

#define ANAC_CMP_CFG_VIPSEL_VBG1P2	   (7 << 2)
#define ANAC_CMP_CFG_VIPSEL_VBG1P0	   (6 << 2)
#define ANAC_CMP_CFG_VIPSEL_VREF_FLASH (5 << 2)
#define ANAC_CMP_CFG_VIPSEL_V1P5D	   (4 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P3	   (3 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P2	   (2 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P1	   (1 << 2)
#define ANAC_CMP_CFG_VIPSEL_VC1P0	   (0 << 2)
#define ANAC_CMP_INV				   (1 << 1)
#define ANAC_CMP_CMP_EN				   (1 << 0)

// LVD_CFG
#define ANAC_LVD_CFG_FLT	BITS(8, 15)
#define ANAC_LVD_CFG_VTSEL	BITS(4, 7)
#define ANAC_LVD_CFG_SRCSEL BITS(2, 3)
#define ANAC_LVD_CFG_LVD_IE BIT(1)
#define ANAC_LVD_CFG_LVD_EN BIT(0)

#define ANAC_LVD_CFG_FLT_pos   (8)
#define ANAC_LVD_CFG_VTSEL_pos (4)

#define ANAC_LVD_CFG_SRCSEL_LOWPWR_VCC (0 << 1)
#define ANAC_LVD_CFG_SRCSEL_VCC		   (1 << 1)
#define ANAC_LVD_CFG_SRCSEL_LVDI0	   (2 << 1)
#define ANAC_LVD_CFG_SRCSEL_LVDI1	   (3 << 1)

// ANAC_AINSEL
#define ANAC_AINSEL_GPIO0_SEL_IND	 (0 << 0)
#define ANAC_AINSEL_GPIO0_SEL_VC1P0	 (1 << 0)
#define ANAC_AINSEL_GPIO1_SEL_AIN04	 (0 << 1)
#define ANAC_AINSEL_GPIO1_SEL_VC1O	 (1 << 1)
#define ANAC_AINSEL_GPIO2_SEL_XTHI	 (0 << 2)
#define ANAC_AINSEL_GPIO2_SEL_AIN11	 (1 << 2)
#define ANAC_AINSEL_GPIO3_SEL_XTHO	 (0 << 3)
#define ANAC_AINSEL_GPIO3_SEL_VC1O	 (1 << 3)
#define ANAC_AINSEL_GPIO4_SEL_LVDI0	 (0 << 4)
#define ANAC_AINSEL_GPIO4_SEL_AIN02	 (1 << 4)
#define ANAC_AINSEL_GPIO5_SEL_LVDI1	 (0 << 5)
#define ANAC_AINSEL_GPIO5_SEL_VC1P6	 (1 << 5)
#define ANAC_AINSEL_GPIO6_SEL_VC1P2	 (0 << 6)
#define ANAC_AINSEL_GPIO6_SEL_AIN05	 (1 << 6)
#define ANAC_AINSEL_GPIO7_SEL_VC1P3	 (0 << 7)
#define ANAC_AINSEL_GPIO7_SEL_AIN06	 (1 << 7)
#define ANAC_AINSEL_GPIO8_SEL_VC1N0	 (0 << 8)
#define ANAC_AINSEL_GPIO8_SEL_AIN07	 (1 << 8)
#define ANAC_AINSEL_GPIO9_SEL_AIN09	 (0 << 9)
#define ANAC_AINSEL_GPIO9_SEL_LVDI0	 (1 << 9)
#define ANAC_AINSEL_GPIO10_SEL_VC1P4 (0 << 10)
#define ANAC_AINSEL_GPIO10_SEL_VC1N3 (1 << 10)
#define ANAC_AINSEL_GPIO11_SEL_AIN09 (0 << 11)
#define ANAC_AINSEL_GPIO11_SEL_AIN10 (1 << 11)
#define ANAC_AINSEL_GPIO12_SEL_TRDRV (0 << 12)
#define ANAC_AINSEL_GPIO12_SEL_VREF	 (1 << 12)
#define ANAC_AINSEL_GPIO13_SEL_		 (0 << 13)
#define ANAC_AINSEL_GPIO13_SEL_AIN03 (1 << 13)
#define ANAC_AINSEL_GPIO14_SEL_VREF	 (0 << 14)
#define ANAC_AINSEL_GPIO14_SEL_AIN10 (1 << 14)
#define ANAC_AINSEL_GPIO15_SEL_AIN01 (0 << 15)
#define ANAC_AINSEL_GPIO15_SEL_VC1N0 (1 << 15)
#define ANAC_AINSEL_GPIO16_SEL_AIN00 (0 << 16)
#define ANAC_AINSEL_GPIO16_SEL_LVDI0 (1 << 16)
// FLAG
#define ANAC_ANAC_FLAG_CMP_OUT	BIT(2)
#define ANAC_ANAC_FLAG_LVD_OUT	BIT(1)
#define ANAC_ANAC_FLAG_LVD_INTF BIT(0)

// WPROT
#define ANAC_WPROT_V0 (0xca)
#define ANAC_WPROT_V1 (0x53)
#define ANAC_WPT_UNLOCK()                                                                                              \
	{                                                                                                                  \
		ANAC->WPROT = ANAC_WPROT_V0;                                                                                   \
		ANAC->WPROT = ANAC_WPROT_V1;                                                                                   \
	}

// HRC_TRIM
#define ANAC_HRC_TRIM BITS(0, 6)

// LRC_TRIM
#define ANAC_LRC_TRIM BITS(0, 5)

// BG4S_TRIM
#define ANAC_BG4S_TRIM BITS(0, 4)

// CMP_TRIM
#define ANAC_CMP_TRIM BITS(0, 6)

// HRC_IBTRIM
#define ANAC_HRC_IBTRIM BITS(0, 6)

// NVR_OPTION0
#define ANAC_NVR_OPTION0_LVD_IBTRIM BITS(3, 4)
#define ANAC_NVR_OPTION0_ADC_IBSEL	BITS(1, 2)
#define ANAC_NVR_OPTION0_ADC_VSSEL	BIT(0)

// ANAC_REV0
#define ANAC_ANAC_REV0 BITS(0, 7)

// TESTCTL
//#define ANAC_TESTCTL                               BITS(0, 15)

// TEST
#define ANAC_TEST_TSTO_SEL BITS(8, 10)
#define ANAC_TEST_TESTMODE BITS(0, 7)

// NVR_OPTION1
#define ANAC_NVR_OPTION1 BITS(0, 31)

// extern function declare
void ANAC_Init(int freq);
void ANAC_DeInit(void);

#endif //__ANAC_H__
