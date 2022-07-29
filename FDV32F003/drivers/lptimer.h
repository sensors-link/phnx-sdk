/**
 * @file lptimer.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#ifndef __LPTIM_H__
#define __LPTIM_H__
#include "phnx05.h"

// register bits defines
// LPTIM_CR
#define LPTIM_CR_PS	  BITS(4, 6)
#define LPTIM_CR_IE	  BIT(3)
#define LPTIM_CR_PITE BIT(2)
#define LPTIM_CR_EN	  BIT(0)

#define LPTIM_CR_PS_pos (4)

// LPTIM_CFG
#define LPTIM_CFG BITS(0, 15)

#define LPTIM_CFG_pos (0) // 0-0xffff:(x+1)*(1/fclk)

// LPTIM_CNT
#define LPTIM_CNT BITS(0, 15)

// LPTIM_STS
#define LPTIM_STS BIT(0)

typedef enum _CNT_MODE
{
	LPT_SIG_TIME_CNT = 0,
	LPT_PIT_CNT,
} eCntModeType;

#define LPT_GetIntFlag() (LPTIM->INTSTS & LPTIM_STS)
#define LPT_ClrIntFlag()                                                                                               \
	{                                                                                                                  \
		LPTIM->INTSTS = LPTIM_STS;                                                                                     \
	}

// lptimer function
void LPT_Init(int iDel, int iMode);
void LPT_DeInit(void);
void LPT_EnableControl(int iCtrl);
void LPT_EnableIRQ(void);
void LPT_DisableIRQ(void);
u16	 LPT_GetCount(void);

#endif /*__LPTIM_H__*/
