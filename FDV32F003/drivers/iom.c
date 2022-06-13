/**
 * @file iom.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "sysc.h"
#include "iom.h"

/**
 * @brief GPIO 选择功能
 * @param pin :GPIO_PINxx
 * @param fun PIN_FUNC_X
 */
void GPIO_PinSelect(int pin, int fun)
{
	SYSC->CLKENCFG |= SYSC_CLKENCFG_IOM_PCKEN;
	PARAM_CHECK((pin == 0) || (pin >= (1 << 16)));
	for (int i = 0; i < 16; ++i)
	{
		if( pin & 0x0001)
		{
			IOM->AF0 &= ~(0x03 << (i << 1));
			IOM->AF0 |= (fun << (i << 1));
		}
		pin >>= 1;
	}
	for (int i = 0; i < 4; ++i)
	{
		if (pin & 0x0001)
		{
			IOM->AF1 &= ~(0x03 << (i << 1));
			IOM->AF1 |= (fun << (i << 1));
		}
		pin >>= 1;
	}
}

/**
 * @brief port pin configure
 *
 * @param pin :GPIO_PINxx     surport '|' combine
 * @param analogEn:ENABLE , DISABLE
 * @param outputEn :ENABLE , DISABLE
 * @param puEn :ENABLE , DISABLE
 * @param pdEn :ENABLE , DISABLE
 * @param outOpenDrainEn :ENABLE , DISABLE
 */
void GPIO_PinConfigure(int pin, int analogEn, int outputEn, int puEn, int pdEn,
                       int outOpenDrainEn)
{
	SYSC->CLKENCFG |= SYSC_CLKENCFG_IOM_PCKEN;
	PARAM_CHECK((pin == 0) || (pin >= (1 << 16)));
	if (analogEn == ENABLE)
	{
		IOM->AINCTRL|= pin;
	}
	else
	{
		int i;
		int pinTmp = pin;
		IOM->AINCTRL &= ~pin;
		for (i = 0; i < 16; ++i)
		{
			if (pinTmp & 0x01)
			{
				if (i < 16)
				{
					IOM->AF0 &= ~(3 << (i << 1));
				}
				else
				{
					IOM->AF1 &= ~(3 << ((i - 16) << 1));
				}
			}
			pinTmp >>= 1;
		}
		if (outputEn == ENABLE)
		{
			IOM->OE |= pin;
		}
		else
		{
			IOM->OE &= ~pin;
		}
		if (outOpenDrainEn == ENABLE)
		{
			IOM->OTYPE |= pin;
		}
		else
		{
			IOM->OTYPE &= ~pin;
		}
		if (pdEn == ENABLE)
		{
			IOM->PD |= pin;
		}
		else
		{
			IOM->PD &= ~pin;
		}
		if (puEn == ENABLE)
		{
			IOM->PU |= pin;
		}
		else
		{
			IOM->PU &= ~pin;
		}
	}
}

/**
 * @brief get data register value
 *
 * @return int:val
 */
int GPIO_GetData(void)
{
	return IOM->DATA;
}
/**
 * @brief set pin
 *
 * @param pin :GPIO_PINxx    surport '|' combine
 */
void GPIO_SetPin(int pin)
{
	IOM->DATA |= pin;
}
/**
 * @brief clear pin
 *
 * @param pin :GPIO_PINxx    surport '|' combine
 */
void GPIO_ClrPin(int pin)
{
	IOM->DATA &= ~pin;
}

/**
 * @brief pin interrupt configure
 *
 * @param pin :GPIO_PINxx     surport '|' combine
 * @param type : PIN_INT_TYPE_EDGE  , PIN_INT_TYPE_LEVEL
 * @param polarity: PIN_INT_POL_HIGH , PIN_INT_POL_LOW
 */
void GPIO_PinIntConfig(int pin, int type, int polarity)
{
	PARAM_CHECK((type != PIN_INT_TYPE_EDGE) && (type != PIN_INT_TYPE_LEVEL));
	PARAM_CHECK((polarity != PIN_INT_POL_HIGH) &&
	            (polarity != PIN_INT_POL_LOW));
	if (type == PIN_INT_TYPE_LEVEL)
	{
		IOM->INT_TYPE |= pin;
	}
	else
	{
		IOM->INT_TYPE &= ~pin;
	}
	if (polarity == PIN_INT_POL_HIGH)
	{
		IOM->INT_POLARITY |= pin;
	}
	else
	{
		IOM->INT_POLARITY &= ~pin;
	}
}
/**
 * @brief globle interrupt control
 *
 * @param syncDisEn :ENABLE , DISABLE
 * @param debounceEn :ENABLE , DISABLE
 * @param en :ENABLE , DISABLE
 */
void GPIO_GlobleIRQControl(int syncDisEn, int debounceEn, int en)
{
	if (syncDisEn == ENABLE)
	{
		IOM->CTL |= (1 << 2);
	}
	else
	{
		IOM->CTL &= ~(1 << 2);
	}
	if (debounceEn == ENABLE)
	{
		IOM->CTL |= 0x02;
	}
	else
	{
		IOM->CTL &= ~0x02;
	}
	if (en == ENABLE)
	{
		IOM->CTL |= 0x01;
	}
	else
	{
		IOM->CTL &= ~0x01;
	}
}
/**
 * @brief pin interrupt control
 *
 * @param pin :GPIO_PINxx   surport '|' combine
 * @param en:ENABLE , DISABLE
 */
void GPIO_PinIRQControl(int pin, int en)
{
	if (en == ENABLE)
	{
		IOM->EXT_INTE |= pin;
	}
	else
	{
		IOM->EXT_INTE &= ~pin;
	}
}
/**
 * @brief get interrupt flag register value
 *
 * @return int: int flag reg val
 */
int GPIO_GetIntFlag(void)
{
	return IOM->INTF;
}
/**
 * @brief clear interrupt flag
 *
 * @param pin :GPIO_PINxx surport '|' combine
 */
void GPIO_ClrIntFlag(int pin)
{
	IOM->INTF = pin;
}
