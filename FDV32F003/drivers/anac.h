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
#include "phnx05.h"

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

#define ANAC_CMP_CFG_HYSSEL_50MV   (3 << 8)
#define ANAC_CMP_CFG_HYSSEL_25MV   (2 << 8)
#define ANAC_CMP_CFG_HYSSEL_12P5MV (1 << 8)
#define ANAC_CMP_CFG_HYSSEL_0MV	   (0 << 8)

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

#define ANAC_CMP_INV	(1 << 1)
#define ANAC_CMP_CMP_EN (1 << 0)

// LVD_CFG
#define ANAC_LVD_CFG_ACT_SEL BIT(16)
#define ANAC_LVD_CFG_FLT	 BITS(8, 15)
#define ANAC_LVD_CFG_VTSEL	 BITS(4, 7)
#define ANAC_LVD_CFG_SRCSEL	 BITS(2, 3)
#define ANAC_LVD_CFG_LVD_IE	 BIT(1)
#define ANAC_LVD_CFG_LVD_EN	 BIT(0)

#define ANAC_LVD_CFG_FLT_pos	(8)
#define ANAC_LVD_CFG_VTSEL_pos	(4)
#define ANAC_LVD_CFG_SRCSEL_pos (2)

#define ANAC_LVD_CFG_SRCSEL_LOWPWR_VCC (0 << 2)
#define ANAC_LVD_CFG_SRCSEL_V5P0	   (1 << 2)
#define ANAC_LVD_CFG_SRCSEL_LVDI0	   (2 << 2)
#define ANAC_LVD_CFG_SRCSEL_LVDI1	   (3 << 2)

// ANAC_AINSEL
#define ANAC_AINSEL_GPIO0_SEL_REV		 (0 << 0)
#define ANAC_AINSEL_GPIO0_SEL_VC1P0		 (1 << 0)
#define ANAC_AINSEL_GPIO1_SEL_AIN04		 (0 << 1)
#define ANAC_AINSEL_GPIO1_SEL_VC1O		 (1 << 1)
#define ANAC_AINSEL_GPIO2_SEL_LVDI0		 (0 << 2)
#define ANAC_AINSEL_GPIO2_SEL_AIN02		 (1 << 2)
#define ANAC_AINSEL_GPIO3_SEL_LVDI1		 (0 << 3)
#define ANAC_AINSEL_GPIO3_SEL_AIN03		 (1 << 3)
#define ANAC_AINSEL_GPIO4_SEL_VC1P2		 (0 << 4)
#define ANAC_AINSEL_GPIO4_SEL_AIN05		 (1 << 4)
#define ANAC_AINSEL_GPIO5_SEL_VC1P3		 (0 << 5)
#define ANAC_AINSEL_GPIO5_SEL_AIN06		 (1 << 5)
#define ANAC_AINSEL_GPIO6_SEL_VC1N0		 (0 << 6)
#define ANAC_AINSEL_GPIO6_SEL_AIN07		 (1 << 6)
#define ANAC_AINSEL_GPIO7_SEL_VREF_FLASH (0 << 7)
#define ANAC_AINSEL_GPIO7_SEL_AIN11		 (1 << 7)
#define ANAC_AINSEL_GPIO8_SEL_VC1N2		 (0 << 8)
#define ANAC_AINSEL_GPIO8_SEL_AIN08		 (1 << 8)
#define ANAC_AINSEL_GPIO9_SEL_AIN09		 (0 << 9)
#define ANAC_AINSEL_GPIO9_SEL_VC1N1		 (1 << 9)
#define ANAC_AINSEL_GPIO10_SEL_REV		 (0 << 10)
#define ANAC_AINSEL_GPIO10_SEL_VC1N3	 (1 << 10)
#define ANAC_AINSEL_GPIO11_SEL_ATS1		 (0 << 11)
#define ANAC_AINSEL_GPIO11_SEL_AIN10	 (1 << 11)
#define ANAC_AINSEL_GPIO12_SEL_VC1P1	 (0 << 12)
#define ANAC_AINSEL_GPIO12_SEL_VREF		 (1 << 12)
#define ANAC_AINSEL_GPIO13_SEL_REV		 (0 << 13)
#define ANAC_AINSEL_GPIO13_SEL_AIN03	 (1 << 13)
#define ANAC_AINSEL_GPIO14_SEL_REV		 (0 << 14)
#define ANAC_AINSEL_GPIO14_SEL_AIN02	 (1 << 14)
#define ANAC_AINSEL_GPIO15_SEL_AIN01	 (0 << 15)
#define ANAC_AINSEL_GPIO15_SEL_VC1N0	 (1 << 15)
#define ANAC_AINSEL_GPIO16_SEL_AIN00	 (0 << 16)
#define ANAC_AINSEL_GPIO16_SEL_LVDI0	 (1 << 16)

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

// extern function declare
void ANAC_Init(int freq);
void ANAC_DeInit(void);

#endif //__ANAC_H__
