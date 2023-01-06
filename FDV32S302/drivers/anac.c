/**
  ******************************************************************************
  * @file    anac.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-08-29
  * @brief   This file provides ANAC related module firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "anac.h"
#include "sysc.h"

/** @addtogroup FDV32S302_StdPeriph_Driver
  * @{
  */

/** @defgroup ANAC
  * @brief ANAC driver modules
  * @{
  */

/** @defgroup ANAC_Private_Defines
  * @{
  */

/* CMP_CFG register Mask */
#define CMP_CFG_CLEAR_Mask ((u32)0xFFFFFC01)

/* ADC_CFG register Mask */
#define ADC_CFG_CLEAR_Mask ((u32)0xFFFF8000)

/* LVD_CFG register Mask */
#define LVD_CFG_CLEAR_Mask ((u32)0xFFFC0081)

/**
  * @}
  */

/** @defgroup ANAC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the ANAC module registers to their default reset values.
  * @param  None
  * @retval None
  */
void ANAC_DeInit(void)
{
	/* Reset the ANAC module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_ANAC);
}

/**
  * @brief  Configure active LDO for analog output voltage select bits.
  * @param  OutputVol: Specify the active LDO for analog output voltage.
  *   This parameter can be one of the following values:
  *     @arg ANAC_ALDO4A_VOSEL_1P5V: active LDO for analog output voltage select 1.5V
  *     @arg ANAC_ALDO4A_VOSEL_1P55V: active LDO for analog output voltage select 1.55V
  *     @arg ANAC_ALDO4A_VOSEL_1P6V: active LDO for analog output voltage select 1.6V
  *     @arg ANAC_ALDO4A_VOSEL_1P7V: active LDO for analog output voltage select 1.7V
  * @retval None
  */
void ANAC_Aldo4aVoltageConfig(u8 OutputVol)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_ANAC_ALDO4A_VOSEL(OutputVol));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	/* Set active LDO for analog output voltage selection */
	tempreg &= ~ANAC_ANAC_CFG_ALDO4A_VOSEL;
	tempreg |= OutputVol << ANAC_ANAC_CFG_ALDO4A_VOSEL_pos;

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Configure sleep LDO output voltage select bits.
  * @param  OutputVol: Specify the sleep LDO output voltage.
  *   This parameter can be one of the following values:
  *     @arg ANAC_SLDO_VRSEL_1P5V: sleep LDO output voltage select 1.5V
  *     @arg ANAC_SLDO_VRSEL_1P2V: sleep LDO output voltage select 1.2V
  * @retval None
  */
void ANAC_SleepLDOVoltageConfig(u8 OutputVol)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_ANAC_SLDO_VRSEL(OutputVol));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	/* Set sleep LDO output voltage selection */
	tempreg &= ~ANAC_ANAC_CFG_SLDO_VRSEL;
	tempreg |= OutputVol << ANAC_ANAC_CFG_SLDO_VRSEL_pos;

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or disable interface circuit isolation.
  * @param  NewState: New state of interface circuit isolation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_InterfaceIsolationCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable interface circuit isolation */
		tempreg |= ANAC_ANAC_CFG_INTF_ISOEN;
	}
	else
	{
		/* Disable interface circuit isolation */
		tempreg &= ~ANAC_ANAC_CFG_INTF_ISOEN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or disable thermistor driver.
  * @param  NewState: The New State of Thermistor Drive.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_ThermistorDriveCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable thermistor drive */
		tempreg |= ANAC_ANAC_CFG_THERMD_EN;
	}
	else
	{
		/* Disable thermistor drive */
		tempreg &= ~ANAC_ANAC_CFG_THERMD_EN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or enable acitve LDO for analog.
  * @param  NewState: New state ofacitve LDO for analog.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_ActiveLDO4AnalogCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable acitve LDO for analog */
		tempreg |= ANAC_ANAC_CFG_ALDO4A_EN;
	}
	else
	{
		/* Disable acitve LDO for analog */
		tempreg &= ~ANAC_ANAC_CFG_ALDO4A_EN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or disable reference voltage enable.
  * @param  NewState: New state of reference enable.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_ReferenceVoltageCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable reference voltage enable */
		tempreg |= ANAC_ANAC_CFG_BGR_EN;
	}
	else
	{
		/* Disable reference voltage enable */
		tempreg &= ~ANAC_ANAC_CFG_BGR_EN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or disable aldo4d and sldo short circuit.
  * @param  NewState: New state of aldo4d and sldo shorting.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_Aldo4dShortSldoCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable aldo4d and sldo short circuit */
		tempreg |= ANAC_ANAC_CFG_ALDO4D_LPEN;
	}
	else
	{
		/* Disable aldo4d and sldo short circuit */
		tempreg &= ~ANAC_ANAC_CFG_ALDO4D_LPEN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or enable acitve LDO for digital.
  * @param  NewState: New state ofacitve LDO for digital.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_ActiveLDO4DigitalCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable acitve LDO for digital */
		tempreg |= ANAC_ANAC_CFG_ALDO4D_EN;
	}
	else
	{
		/* Disable acitve LDO for digital */
		tempreg &= ~ANAC_ANAC_CFG_ALDO4D_EN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Configure the LED drive current according to the incoming parameters.
  * @param  LED_Sel: Infrared tube selection.
  *   This parameter can be one of the following values:
  *     @arg LED_SEL_IIRLED: Infrared red light tube
  *     @arg LED_SEL_IBULE: Infrared blue light tube
  * @param  CurrentVal: The current value of the selected red light tube.
  *   This parameter value must be lower than 0x20.
  * @retval None
  */
void LED_DriveCurrentConfig(u8 LED_Sel, u8 CurrentVal)
{
	/* Check the parameters */
	PARAM_CHECK(IS_LED_ISEL(LED_Sel));
	PARAM_CHECK(IS_LED_CURRENTVAL(CurrentVal));

	if (LED_Sel == LED_SEL_IIRLED)
	{
		/* Set the infrared red light tube current */
		ANAC->LED_CFG &= ~ANAC_LED_CFG_IIRLED_CC;
		ANAC->LED_CFG |= CurrentVal << ANAC_LED_CFG_IIRLED_CC_pos;
	}
	else
	{
		/* Set infrared blue light tube current */
		ANAC->LED_CFG &= ~ANAC_LED_CFG_IBULE_CC;
		ANAC->LED_CFG |= CurrentVal << ANAC_LED_CFG_IBULE_CC_pos;
	}
}

/**
  * @brief  Set up automatic measurement of infrared tubes.
  * @param  LED_Sel: Infrared tube selection.
  *   This parameter can be one of the following values:
  *     @arg LED_SEL_IIRLED: Infrared red light tube
  *     @arg LED_SEL_IBULE: Infrared blue light tube
  * @retval None
  */
void LED_SetAutoInfraredTube(u8 LED_Sel)
{
	/* Check the parameters */
	PARAM_CHECK(IS_LED_ISEL(LED_Sel));

	if (LED_Sel == LED_SEL_IIRLED)
	{
		/* Set infrared red light tube */
		ANAC->LED_CFG &= ~ANAC_LED_CFG_LED_SEL;
		ANAC->LED_CFG |= ANAC_LED_CFG_LED_SEL_IR;
	}
	else
	{
		/* Set infrared blue light tube */
		ANAC->LED_CFG &= ~ANAC_LED_CFG_LED_SEL;
		ANAC->LED_CFG |= ANAC_LED_CFG_LED_SEL_BLUE;
	}
}

/**
  * @brief  Enable or disable the infrared tube driver according to the incoming parameters.
  * @param  LED_Sel: Infrared tube selection.
  *   This parameter can be one of the following values:
  *     @arg LED_SEL_IIRLED: Infrared red light tube
  *     @arg LED_SEL_IBULE: Infrared blue light tube
  * @param  NewState: New State of Infrared Tube LED Drivers.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LED_InfraredTubeCmd(u8 LED_Sel, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_LED_ISEL(LED_Sel));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (LED_Sel == LED_SEL_IIRLED)
	{
		/* Select infrared red light tube */
		if (NewState == ENABLE)
		{
			/* Enable infrared red light tube driver */
			ANAC->LED_CFG |= ANAC_LED_CFG_IIRLED_EN;
		}
		else
		{
			/* Disable infrared red light tube driver */
			ANAC->LED_CFG &= ~ANAC_LED_CFG_IIRLED_EN;
		}
	}
	else
	{
		/* Select infrared blue light tube */
		if (NewState == ENABLE)
		{
			/* Enable infrared blue light tube driver */
			ANAC->LED_CFG |= ANAC_LED_CFG_IBLUE_EN;
		}
		else
		{
			/* Disable infrared blue light tube driver */
			ANAC->LED_CFG &= ~ANAC_LED_CFG_IBLUE_EN;
		}
	}
}

/**
  * @brief  Configure the PD sensor amplification gain according to the incoming parameters.
  * @param  GainVal: Specify PD Sensor Amplification Gain.
  *   This parameter value must be lower than 0x20.
  * @retval None
  */
void PDSENS_GainConfig(u8 GainVal)
{
	/* Check the parameters */
	PARAM_CHECK(IS_PDSENS_GAINVAL(GainVal));

	/* Set PD Sensor Amplification Gain */
	ANAC->PDSENS_CFG &= ~ANAC_PDSENS_CFG_GC;
	ANAC->PDSENS_CFG |= GainVal << ANAC_PDSENS_CFG_GC_pos;
}

/**
  * @brief  Enable or disable PD Sensor filter capacitor charging.
  * @param  NewState: New State of PD Sensor Filter Capacitor Charging.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PDSENS_CapacitorChargeCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable PD Sensor filter capacitor charging */
		ANAC->PDSENS_CFG |= ANAC_PDSENS_CFG_CHRG;
	}
	else
	{
		/* Disable PD Sensor filter capacitor charging */
		ANAC->PDSENS_CFG &= ~ANAC_PDSENS_CFG_CHRG;
	}
}

/**
  * @brief  Enable or disable PD Sensor reset signal.
  * @param  NewState: New state of PD Sensor reset signal.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PDSENS_ResetCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable PD Sensor reset */
		ANAC->PDSENS_CFG |= ANAC_PDSENS_CFG_RST;
	}
	else
	{
		/* Disable PD Sensor reset */
		ANAC->PDSENS_CFG &= ~ANAC_PDSENS_CFG_RST;
	}
}

/**
  * @brief  Enable or disable PD Sensor.
  * @param  NewState: New state of PD Sensor.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PDSENS_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable PD Sensor */
		ANAC->PDSENS_CFG |= ANAC_PDSENS_CFG_EN;
	}
	else
	{
		/* Disable PD Sensor */
		ANAC->PDSENS_CFG &= ~ANAC_PDSENS_CFG_EN;
	}
}

/**
  * @brief  Initializes the CMP peripheral according to the specified parameters
  *         in the CMP_InitStruct.
  * @param  CMP_InitStruct: pointer to an CMP_InitTypeDef structure that contains
  *         the configuration information for the CMP peripheral.
  * @retval None
  */
void CMP_Init(CMP_InitTypeDef *CMP_InitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_CMP_HYSSEL(CMP_InitStruct->CMP_HysSel));
	PARAM_CHECK(IS_CMP_VINSEL(CMP_InitStruct->CMP_VinSel));
	PARAM_CHECK(IS_CMP_VIPSEL(CMP_InitStruct->CMP_VipSel));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(CMP_InitStruct->CMP_InvertedOutCmd));

	/*---------------------------- CMP_CFG Configuration ------------------------*/
	/* Get the CMP_CFG value */
	tempreg = ANAC->CMP_CFG;
	/* Clear CMP_CFG initialization configuration bit */
	tempreg &= CMP_CFG_CLEAR_Mask;

	/* CMP hysteresis function selection */
	tempreg |= CMP_InitStruct->CMP_HysSel << ANAC_CMP_CFG_HYSSEL_pos;
	/* CMP negative input signal selection */
	tempreg |= CMP_InitStruct->CMP_VinSel << ANAC_CMP_CFG_VINSEL_pos;
	/* CMP positive input signal selection */
	tempreg |= CMP_InitStruct->CMP_VipSel << ANAC_CMP_CFG_VIPSEL_pos;
	if (CMP_InitStruct->CMP_InvertedOutCmd == ENABLE)
	{
		/* Set CMP result inversion output */
		tempreg |= ANAC_CMP_CFG_INV;
	}

	/* Write to CMP_CFG */
	ANAC->CMP_CFG = tempreg;
}

/**
  * @brief  Enable or disable the CMP peripheral.
  * @param  NewState: New state of the CMP peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CMP_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable CMP peripheral */
		ANAC->CMP_CFG |= ANAC_CMP_CFG_EN;
	}
	else
	{
		/* Disable CMP peripheral */
		ANAC->CMP_CFG &= ~ANAC_CMP_CFG_EN;
	}
}

/**
  * @brief  Initializes the ADC peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_ADC_CHANNEL(ADC_InitStruct->ADC_Channel));
	PARAM_CHECK(IS_ADC_VREFSEL(ADC_InitStruct->ADC_VrefSel));
	PARAM_CHECK(IS_ADC_VREFVOL(ADC_InitStruct->ADC_VrefVol));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_BuffCmd));
	PARAM_CHECK(IS_ADC_SMPTIMS(ADC_InitStruct->ADC_SmpTimes));
	PARAM_CHECK(IS_ADC_SMPCYCLE(ADC_InitStruct->ADC_SmpCycle));

	/*---------------------------- ADC_CFG Configuration ------------------------*/
	tempreg = ANAC->ADC_CFG;
	/* Clear ADC_CFG initialization configuration bit */
	tempreg &= ADC_CFG_CLEAR_Mask;

	/* ADC input channel selection */
	tempreg |= ADC_InitStruct->ADC_Channel << ANAC_ADC_CFG_ADC_CHSEL_pos;
	/* ADC reference voltage input source input selection */
	tempreg |= ADC_InitStruct->ADC_VrefSel << ANAC_ADC_CFG_ADC_VRSEL_pos;
	/* Internal reference voltage VREF gear selection */
	tempreg |= ADC_InitStruct->ADC_VrefVol << ANAC_ADC_CFG_VOLTREF_VRSEL_pos;
	/* Internal voltage reference enable control */
	if (ADC_InitStruct->ADC_VrefSel == ADC_VREF_SEL_INT)
	{
		tempreg |= ANAC_ADC_CFG_VOLTREF_EN;
	}
	
	/* ADC Amplifier Enable Control */
	if (ADC_InitStruct->ADC_BuffCmd == ENABLE)
	{
		tempreg |= ANAC_ADC_CFG_ADC_BUFEN;
	}
	
	/* Set ADC hardware sampling times */
	tempreg |= ADC_InitStruct->ADC_SmpTimes << ANAC_ADC_CFG_SMP_TIME_pos;
	/* Set ADC input signal sample and hold time */
	tempreg |= ADC_InitStruct->ADC_SmpCycle << ANAC_ADC_CFG_SMP_CYCLE_pos;

	/* Write to ADC_CFG */
	ANAC->ADC_CFG = tempreg;
}

/**
  * @brief  Returns the ADC single conversion result value..
  * @param  ValNo: The register number of the ADC conversion result to be obtained.
  *   This parameter can be one of @ref ADC_ValNo enumeration
  *     @arg ADC_VAL_NO0: 1st conversion result
  *     @arg ADC_VAL_NO1: 2nd conversion result
  *     @arg ADC_VAL_NO2: 3rd conversion result
  *     @arg ADC_VAL_NO3: 4th conversion result
  *     @arg ADC_VAL_NO4: 5th conversion result
  *     @arg ADC_VAL_NO5: 6th conversion result
  *     @arg ADC_VAL_NO6: 7th conversion result
  *     @arg ADC_VAL_NO7: 8th conversion result
  * @retval The conversion result of the corresponding number of times.
  */
u32 ADC_GetSingleResultValue(ADC_ValNo ValNo)
{
	/* Check the parameters */
	PARAM_CHECK(IS_ADC_RESULTNO(ValNo));

	/* Return the corresponding conversion result */
	return ANAC->ADC_VAL[ValNo];
}

/**
  * @brief  Returns the average value of ADC conversion results.
  * @param  None
  * @retval Conversion result average
  */
u32 ADC_GetAverageValue(void)
{
	/* Returns the average of the conversion results */
	return ANAC->AVG_VAL;
}

/**
  * @brief  Enables or disables the ADC software start conversion .
  * @param  NewState: new state of the ADC software start conversion.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartConvCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable ADC software to initiate conversions */
		ANAC->ADC_CTL |= ANAC_ADC_CTL_SST;
	}
	else
	{
		/* Disable ADC software to initiate conversions */
		ANAC->ADC_CTL &= ~ANAC_ADC_CTL_SST;
	}
}

/**
  * @brief  Enable or disable the ADC peripheral.
  * @param  NewState: New state of the ADC peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable ADC peripheral */
		ANAC->ADC_CTL |= ANAC_ADC_CTL_ADC_EN;
	}
	else
	{
		/* Disable ADC peripheral */
		ANAC->ADC_CTL &= ~ANAC_ADC_CTL_ADC_EN;
	}
}

/**
  * @brief  Enables or disables the ADC interrupts.
  * @param  NewState: new state of the specified ADC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the ADC interrupts */
		ANAC->ADC_CTL |= ANAC_ADC_CTL_ADC_IE;
	}
	else
	{
		/* Disable the ADC interrupts */
		ANAC->ADC_CTL &= ~ANAC_ADC_CTL_ADC_IE;
	}
}

/**
  * @brief  Initializes the LVD peripheral according to the specified parameters
  *         in the LVD_InitStruct.
  * @param  LVD_InitStruct: pointer to an LVD_InitTypeDef structure that contains
  *         the configuration information for the LVD peripheral.
  * @retval None
  */
void LVD_Init(LVD_InitTypeDef *LVD_InitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_LVD_BIAS_CURRENT_TRIM(LVD_InitStruct->LVD_BiasCurrentTrim));
	PARAM_CHECK(IS_LVD_FILTER_TIME(LVD_InitStruct->LVD_FilterTime));
	PARAM_CHECK(IS_LVD_THRESHOLD_VOL(LVD_InitStruct->LVD_ThresholdVoltage));
	PARAM_CHECK(IS_LVD_MONITOR_SOURCE(LVD_InitStruct->LVD_MonitoSource));

	/*---------------------------- LVD_CFG Configuration ------------------------*/
	tempreg = ANAC->LVD_CFG;
	/* Clear LVD_CFG initialization configuration bit */
	tempreg &= LVD_CFG_CLEAR_Mask;

	/* Set the LVD comparator bias current trim */
	tempreg |= LVD_InitStruct->LVD_BiasCurrentTrim << ANAC_LVD_CFG_IBTRIM_pos;
	/* Set low voltage detection LVD_OUT filter time */
	tempreg |= LVD_InitStruct->LVD_FilterTime << ANAC_LVD_CFG_FLT_pos;
	/* Set LVD threshold voltage selection */
	tempreg |= LVD_InitStruct->LVD_ThresholdVoltage << ANAC_LVD_CFG_VTSEL_pos;
	/* Set Set LVD monitoring source selection */
	tempreg |= LVD_InitStruct->LVD_MonitoSource << ANAC_LVD_CFG_SRCSEL_pos;

	/* Write to LVD_CFG */
	ANAC->LVD_CFG = tempreg;
}

/**
  * @brief  Enable or disable the LVD peripheral.
  * @param  NewState: New state of the LVD peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable LVD peripheral */
		ANAC_WPT_UNLOCK();
		ANAC->LVD_CFG |= ANAC_LVD_CFG_LVD_EN;
	}
	else
	{
		/* Disable LVD peripheral */
		ANAC_WPT_UNLOCK();
		ANAC->LVD_CFG &= ~ANAC_LVD_CFG_LVD_EN;
	}
}

/**
  * @brief  Enables or disables the LVD interrupts.
  * @param  NewState: new state of the specified LVD interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_ITConfig(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the LVD interrupts */
		ANAC->LVD_CFG |= ANAC_LVD_CFG_LVD_IE;
	}
	else
	{
		/* Disable the LVD interrupts */
		ANAC->LVD_CFG &= ~ANAC_LVD_CFG_LVD_IE;
	}
}

/**
  * @brief  Configure high-speed crystal oscillator frequency gear.
  * @param  FreqSel: Specify high-speed crystal oscillator frequency switching selection bit.
  *   This parameter can be one of the following values:
  *     @arg CLK_HRC_FREQ_SEL_1M: High-speed crystal oscillator frequency switching select 1MHz
  *     @arg CLK_HRC_FREQ_SEL_2M: High-speed crystal oscillator frequency switching select 2MHz
  *     @arg CLK_HRC_FREQ_SEL_4M: High-speed crystal oscillator frequency switching select 4MHz
  *     @arg CLK_HRC_FREQ_SEL_8M: High-speed crystal oscillator frequency switching select 8MHz
  *     @arg CLK_HRC_FREQ_SEL_16M: High-speed crystal oscillator frequency switching select 16MHz
  * @retval None
  */
void CLK_HRCFrequencyConfig(u8 FreqSel)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_CLK_HRC_FREQSEL(FreqSel));

	/* Get the CLK_CFG value */
	tempreg = ANAC->CLK_CFG;

	/* Set high-speed crystal oscillator frequency switching selection bits */
	tempreg &= ~ANAC_CLK_CFG_HRC_FSEL;
	tempreg |= FreqSel << ANAC_CLK_CFG_HRC_FSEL_pos;

	/* Write to CLK_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->CLK_CFG = tempreg;
}

/**
  * @brief  Enable or disable MRC clock.
  * @param  NewState: New state of the MRC clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CLK_MRCClockCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the CLK_CFG value */
	tempreg = ANAC->CLK_CFG;

	if (NewState == ENABLE)
	{
		/* Enable MRC clock */
		tempreg |= ANAC_CLK_CFG_MRC_EN;
	}
	else
	{
		/* Disable MRC clock */
		tempreg &= ~ANAC_CLK_CFG_MRC_EN;
	}

	/* Write to CLK_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->CLK_CFG = tempreg;
}

/**
  * @brief  Enable or disable HRC clock.
  * @param  NewState: New state of the HRC clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CLK_HRCClockCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the CLK_CFG value */
	tempreg = ANAC->CLK_CFG;

	if (NewState == ENABLE)
	{
		/* Enable HRC clock */
		tempreg |= ANAC_CLK_CFG_HRC_EN;
	}
	else
	{
		/* Disable HRC clock */
		tempreg &= ~ANAC_CLK_CFG_HRC_EN;
	}

	/* Write to CLK_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->CLK_CFG = tempreg;
}

/**
  * @brief  Enable or disable LRC clock.
  * @param  NewState: New state of the LRC clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CLK_LRCClockCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the CLK_CFG value */
	tempreg = ANAC->CLK_CFG;

	if (NewState == ENABLE)
	{
		/* Enable LRC clock */
		tempreg |= ANAC_CLK_CFG_LRC_EN;
	}
	else
	{
		/* Disable LRC clock */
		tempreg &= ~ANAC_CLK_CFG_LRC_EN;
	}

	/* Write to CLK_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->CLK_CFG = tempreg;
}

/**
  * @brief  Configure the analog GPIO multiplexing function.
  * @param  MultiplexSel: Specifies the analog multiplexing capabilities of GPIO.
  *   This parameter can be one of the following values:
  *     @arg AINSEL_MULTIPLEX_P04_SEL_VC1P1: GP04 multiplex select VC1P1
  *     @arg AINSEL_MULTIPLEX_P04_SEL_AIN02: GP04 multiplex select AIN02
  *     @arg AINSEL_MULTIPLEX_P05_SEL_LVDI1: GP05 multiplex select LVDI1
  *     @arg AINSEL_MULTIPLEX_P05_SEL_AIN03: GP05 multiplex select AIN03
  *     @arg AINSEL_MULTIPLEX_P06_SEL_VC1N1: GP06 multiplex select VC1N1
  *     @arg AINSEL_MULTIPLEX_P06_SEL_AIN01: GP06 multiplex select AIN01
  *     @arg AINSEL_MULTIPLEX_P07_SEL_AIN05: GP07 multiplex select AIN05
  *     @arg AINSEL_MULTIPLEX_P07_SEL_VC1P2: GP07 multiplex select VC1P2
  *     @arg AINSEL_MULTIPLEX_P12_SEL_AIN07: GP12 multiplex select AIN07
  *     @arg AINSEL_MULTIPLEX_P12_SEL_VC1O : GP12 multiplex select VC1O 
  *     @arg AINSEL_MULTIPLEX_P13_SEL_VC1N0: GP13 multiplex select VC1N0
  *     @arg AINSEL_MULTIPLEX_P13_SEL_VREF : GP13 multiplex select VREF 
  *     @arg AINSEL_MULTIPLEX_P14_SEL_VREF : GP14 multiplex select VREF 
  *     @arg AINSEL_MULTIPLEX_P14_SEL_AIN04: GP14 multiplex select AIN04
  *     @arg AINSEL_MULTIPLEX_P15_SEL_TRDRV: GP15 multiplex select TRDRV
  *     @arg AINSEL_MULTIPLEX_P15_SEL_ATVC : GP15 multiplex select ATVC 
  *     @arg AINSEL_MULTIPLEX_P16_SEL_VC1P3: GP16 multiplex select VC1P3
  *     @arg AINSEL_MULTIPLEX_P16_SEL_AIN08: GP16 multiplex select AIN08
  *     @arg AINSEL_MULTIPLEX_P17_SEL_VC1P4: GP17 multiplex select VC1P4
  *     @arg AINSEL_MULTIPLEX_P17_SEL_AIN06: GP17 multiplex select AIN06
  *     @arg AINSEL_MULTIPLEX_P18_SEL_VC1P0: GP18 multiplex select VC1P0
  *     @arg AINSEL_MULTIPLEX_P18_SEL_AIN00: GP18 multiplex select AIN00
  *     @arg AINSEL_MULTIPLEX_P19_SEL_VC1N0: GP19 multiplex select VC1N0
  *     @arg AINSEL_MULTIPLEX_P19_SEL_LVDI0: GP19 multiplex select LVDI0
  * @retval None
  */
void AINSEL_MultiplexConfig(u8 MultiplexSel)
{
	/* Check the parameters */
	PARAM_CHECK(IS_AINSEL_MULTIPLEXSEL(MultiplexSel));

	/* Clear analog GPIO alternate function pin bit */
	ANAC->AINSEL &= ~(1 << (MultiplexSel >> 1));
	/* Set the pin to simulate the GPIO multiplexing function */
	ANAC->AINSEL |= (MultiplexSel & 1) << (MultiplexSel >> 1);
}

/**
  * @brief  Configure the charging time of PDSENS capacitor.
  * @param  ChargeTime: Specify the charging time of PDSENS capacitor.
  *   This parameter can be one of the following values:
  *     @arg DLY_PD_CHRG_DLY_500 : The required charging time is 500 anac_500k_clk clock cycles
  *     @arg DLY_PD_CHRG_DLY_1000: The required charging time is 1000 anac_500k_clk clock cycles
  *     @arg DLY_PD_CHRG_DLY_1500: The required charging time is 1500 anac_500k_clk clock cycles
  *     @arg DLY_PD_CHRG_DLY_2000: The required charging time is 2000 anac_500k_clk clock cycles
  * @retval None
  */
void DLY_PDChargeDelayConfig(u8 ChargeDelayTime)
{
	/* Check the parameters */
	PARAM_CHECK(IS_DLY_PDCHRGDLY(ChargeDelayTime));

	/* Set the charging time of PDSENS capacitor */
	ANAC->DLY_CFG &= ~ANAC_DLY_CFG_CHRG_DLY;
	ANAC->DLY_CFG |= ChargeDelayTime << ANAC_DLY_CFG_CHRG_DLY_pos;
}

/**
  * @brief  Configure the LED enable turn-on width.
  * @param  OpenWidth: Specifies the LED enable turn-on width.
  *   This parameter must be a 8bit value.
  * @retval None
  */
void DLY_LEDOpenWidthConfig(u8 OpenWidth)
{
	/* Set the LED enable turn-on width */
	ANAC->DLY_CFG &= ~ANAC_DLY_CFG_LED_PW;
	ANAC->DLY_CFG |= OpenWidth << ANAC_DLY_CFG_LED_PW_pos;
}

/**
  * @brief  Configure the stabilization time required for smoke sampling.
  * @param  SmokeDelayTime: Specifies the stabilization time required for smoke sampling.
  *   This parameter must be a 8bit value.
  * @retval None
  */
void DLY_SmokeDelayConfig(u8 SmokeDelayTime)
{
	/* Set the stabilization time required for smoke sampling */
	ANAC->DLY_CFG &= ~ANAC_DLY_CFG_SMOKE_DLY;
	ANAC->DLY_CFG |= SmokeDelayTime << ANAC_DLY_CFG_SMOKE_DLY_pos;
}

/**
  * @brief  Configure the stabilization time required for the Pdsensor to reset and start to stabilize.
  * @param  PDRestDelayTime: Specifies the stabilization time required for Pdsensor reset to stabilize.
  *   This parameter can be one of the following values:
  *     @arg DLY_PD_RST_DLY_200: Settling time required is 200 anac_500k_clk clock cycles
  *     @arg DLY_PD_RST_DLY_300: Settling time required is 300 anac_500k_clk clock cycles
  *     @arg DLY_PD_RST_DLY_400: Settling time required is 400 anac_500k_clk clock cycles
  *     @arg DLY_PD_RST_DLY_500: Settling time required is 500 anac_500k_clk clock cycles
  * @retval None
  */
void DLY_PDRestDelayConfig(u8 PDRestDelayTime)
{
	/* Check the parameters */
	PARAM_CHECK(IS_DLY_PDRSTDLY(PDRestDelayTime));

	/* Set the stabilization time required for Pdsensor reset to be stable */
	ANAC->DLY_CFG &= ~ANAC_DLY_CFG_PDSENS_RST_DLY;
	ANAC->DLY_CFG |= PDRestDelayTime << ANAC_DLY_CFG_PDSENS_RST_DLY_pos;
}

/**
  * @brief  Configure the stabilization time required for the temperature sensor
  *         to be turned on and stabilized.
  * @param  TempDelayTime: Specifies the stabilization time required for the
  *         temperature sensor to be turned on and stabilized.
  *   This parameter can be one of the following values:
  *     @arg DLY_TEMP_DLY_6: Settling time required is 6 anac_500k_clk clock cycles
  *     @arg DLY_TEMP_DLY_12: Settling time required is 12 anac_500k_clk clock cycles
  *     @arg DLY_TEMP_DLY_24: Settling time required is 24 anac_500k_clk clock cycles
  *     @arg DLY_TEMP_DLY_48: Settling time required is 48 anac_500k_clk clock cycles
  * @retval None
  */
void DLY_TempDelayConfig(u8 TempDelayTime)
{
	/* Check the parameters */
	PARAM_CHECK(IS_DLY_TEMPDLY(TempDelayTime));

	/* Set the stabilization time required for the temperature sensor to be
	 * turned on and stabilized */
	ANAC->DLY_CFG &= ~ANAC_DLY_CFG_TEMP_DLY;
	ANAC->DLY_CFG |= TempDelayTime << ANAC_DLY_CFG_TEMP_DLY_pos;
}

/**
  * @brief  Configure the stable time required for adc to be turned on and stabilized.
  * @param  ADCDelayTime: Specifies the stabilization time required for adc enable to stabilize.
  *   This parameter can be one of the following values:
  *     @arg DLY_ADC_DLY_6: Settling time required is 6 anac_500k_clk clock cycles
  *     @arg DLY_ADC_DLY_12: Settling time required is 12 anac_500k_clk clock cycles
  *     @arg DLY_ADC_DLY_24: Settling time required is 24 anac_500k_clk clock cycles
  *     @arg DLY_ADC_DLY_48: Settling time required is 48 anac_500k_clk clock cycles
  * @retval None
  */
void DLY_ADCDelayConfig(u8 ADCDelayTime)
{
	/* Check the parameters */
	PARAM_CHECK(IS_DLY_ADCDLY(ADCDelayTime));

	/* Set the stabilization time required for adc enable to stabilize */
	ANAC->DLY_CFG &= ~ANAC_DLY_CFG_ADC_DLY;
	ANAC->DLY_CFG |= ADCDelayTime << ANAC_DLY_CFG_ADC_DLY_pos;
}

/**
  * @brief  Configure aldo4a to enable the stabilization time required to turn on and stabilize.
  * @param  ALDO4ADelayTime: Specify the stabilization time required for aldo4a to be enabled to stabilize.
  *   This parameter can be one of the following values:
  *     @arg DLY_ALDO4A_DLY_12: Settling time required is 12 anac_500k_clk clock cycles
  *     @arg DLY_ALDO4A_DLY_24: Settling time required is 24 anac_500k_clk clock cycles
  *     @arg DLY_ALDO4A_DLY_48: Settling time required is 48 anac_500k_clk clock cycles
  *     @arg DLY_ALDO4A_DLY_96: Settling time required is 96 anac_500k_clk clock cycles
  * @retval None
  */
void DLY_ALDO4ADelayConfig(u8 ALDO4ADelayTime)
{
	/* Check the parameters */
	PARAM_CHECK(IS_DLY_ALDO4ADLY(ALDO4ADelayTime));

	/* Set the stabilization time required to enable aldo4a to turn on and stabilize */
	ANAC->DLY_CFG &= ~ANAC_DLY_CFG_ALDO4A_DLY;
	ANAC->DLY_CFG |= ALDO4ADelayTime << ANAC_DLY_CFG_ALDO4A_DLY_pos;
}

/**
  * @brief  Configure the stabilization time required for the BRG to be turned on and stabilized.
  * @param  ALDO4ADelayTime: Specifies the stabilization time required for the BRG enable to stabilize.
  *   This parameter can be one of the following values:
  *     @arg DLY_BGR_DLY_12: Settling time required is 12 anac_500k_clk clock cycles
  *     @arg DLY_BGR_DLY_24: Settling time required is 24 anac_500k_clk clock cycles
  *     @arg DLY_BGR_DLY_48: Settling time required is 48 anac_500k_clk clock cycles
  *     @arg DLY_BGR_DLY_96: Settling time required is 96 anac_500k_clk clock cycles
  * @retval None
  */
void DLY_BGRDelayConfig(u8 BGRDelayTime)
{
	/* Check the parameters */
	PARAM_CHECK(IS_DLY_BGRDLY(BGRDelayTime));

	/* Set the stabilization time required for BGR to be turned on and stabilized */
	ANAC->DLY_CFG &= ~ANAC_DLY_CFG_BGR_DLY;
	ANAC->DLY_CFG |= BGRDelayTime << ANAC_DLY_CFG_BGR_DLY_pos;
}

/**
  * @brief  Configure trigger ADC conversion peripheral interrupt source selection.
  * @param  ADCIntSource: Specify trigger ADC conversion peripheral interrupt source selection.
  *   This parameter can be one of the following values:
  *     @arg ME_INT_SRC_LPT: Trigger interrupt source selection LPT
  *     @arg ME_INT_SRC_TIM1: Trigger interrupt source selection TIM1
  *     @arg ME_INT_SRC_TIM2: Trigger interrupt source selection TIM2
  * @retval None
  */
void ME_ADCIntSourceConfig(u8 ADCIntSource)
{
	/* Check the parameters */
	PARAM_CHECK(IS_ME_INTSRC(ADCIntSource));

	/* Set trigger ADC conversion peripheral interrupt source */
	ANAC->ME_CTL &= ~ANAC_ME_CTL_ADC_TRIG_SEL;
	ANAC->ME_CTL |= ADCIntSource << ANAC_ME_CTL_ADC_TRIG_SEL_pos;
}

/**
  * @brief  Configure automatic measurement mode.
  * @param  ADCIntSource: Specify automatic measurement mode.
  *   This parameter can be one of the following values:
  *     @arg ME_AUTO_MODE_GENERRAL: General analog automatic measurement mode
  *     @arg ME_AUTO_MODE_TEMP: Temperature sensor automatic measurement mode
  *     @arg ME_AUTO_MODE_DARKCURRENT: Dark current automatic measurement mode
  *     @arg ME_AUTO_MODE_SMOKE: Smoke sensor automatic measurement mode
  * @retval None
  */
void ME_AutoModeConfig(u8 AutoMode)
{
	/* Check the parameters */
	PARAM_CHECK(IS_ME_AUTOMODE(AutoMode));

	/* Set automatic measurement mode */
	ANAC->ME_CTL &= ~ANAC_ME_CTL_MODE_SEL;
	ANAC->ME_CTL |= AutoMode << ANAC_ME_CTL_MODE_SEL_pos;
}

/**
  * @brief  Set trigger ADC conversion source.
  * @param  TriggerSource: Specify the trigger ADC conversion source.
  *   This parameter can be one of the following values:
  *     @arg ME_TRIGGER_SRC_SST: Software configuration SST bit triggers ADC conversion
  *     @arg ME_TRIGGER_SRC_INT: Trigger ADC conversion from peripheral interrupt
  * @retval None
  */
void ME_SetTriggerSource(u8 TriggerSource)
{
	/* Check the parameters */
	PARAM_CHECK(IS_ME_TRIGGERSRC(TriggerSource));

	/* Set trigger ADC conversion source */
	if (TriggerSource == ME_TRIGGER_SRC_SST)
	{
		/* Set software configuration SST bit to trigger ADC conversion */
		ANAC->ME_CTL &= ~ANAC_ME_CTL_ME_MODE;
	}
	else
	{
		/* Set up interrupts from peripherals to trigger ADC conversions */
		ANAC->ME_CTL |= ANAC_ME_CTL_ME_MODE;
	}
}

/**
  * @brief  Enable or disable smoke threshold comparison.
  * @param  NewState: New State of Smoke Threshold Comparison.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ME_ThresholdCompareCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable smoke threshold comparison */
		ANAC->ME_CTL |= ANAC_ME_CTL_THRCMP_EN;
	}
	else
	{
		/* Disable smoke threshold comparison */
		ANAC->ME_CTL &= ~ANAC_ME_CTL_THRCMP_EN;
	}
}

/**
  * @brief  Enable or disable automatic measurement mode.
  * @param  NewState: New state of automatic measurement mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ME_AutoMeasureCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable automatic measurement mode */
		ANAC->ME_CTL |= ANAC_ME_CTL_ME_AUTO;
	}
	else
	{
		/* Disable automatic measurement mode */
		ANAC->ME_CTL &= ~ANAC_ME_CTL_ME_AUTO;
	}
}

/**
  * @brief  Enable or disable measurement module peripherals.
  * @param  NewState: The new state of the measurement module peripherals.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ME_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable measurement module peripherals */
		ANAC->ME_CTL |= ANAC_ME_CTL_ANAC_EN;
	}
	else
	{
		/* Disable measurement module peripherals */
		ANAC->ME_CTL &= ~ANAC_ME_CTL_ANAC_EN;
	}
}

/**
  * @brief  Enables or disables the smoke threshold interrupts.
  * @param  NewState: new state of the specified smoke threshold interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ME_ITConfig(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the smoke threshold interrupts */
		ANAC->ME_CTL |= ANAC_ME_CTL_THR_IE;
	}
	else
	{
		/* Disable the smoke threshold interrupts */
		ANAC->ME_CTL &= ~ANAC_ME_CTL_THR_IE;
	}
}

/**
  * @brief  Configure the value of the threshold comparison.
  * @param  LowerLimit: The lower limit of the threshold comparison.
  *   This parameter must be a 12bit value.
  * @param  UpperLimit: The upper limit of the threshold comparison.
  *   This parameter must be a 12bit value.
  * @retval None
  */
void THR_ValueConfig(u16 LowerLimit, u16 UpperLimit)
{
	/* Check the parameters */
	PARAM_CHECK(IS_THR_LIMITVAL(LowerLimit));
	PARAM_CHECK(IS_THR_LIMITVAL(UpperLimit));

	/* Set the lower limit value register */
	ANAC->THR1_DATA = LowerLimit;

	/* Set the upper limit value register */
	ANAC->THR2_DATA = UpperLimit;
}

/**
  * @brief  Checks whether the specified ANAC flag is set or not.
  * @param  ANAC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg ANAC_FLAG_CMP_OUT: Comparator result output flag
  *     @arg ANAC_FLAG_LVD_OUT: Low voltage detection result output flag
  *     @arg ANAC_FLAG_ANA_OK_INTF: The analog circuit is turned on and stabilized flag
  *     @arg ANAC_FLAG_LVD_INTF: Low voltage detection interrupt flag
  *     @arg ANAC_FLAG_THR_INTF: Smoke ADC values are in the threshold range flag
  *     @arg ANAC_FLAG_ADC_INTF: ADC conversion complete interrupt flag
  * @retval The new state of ANAC_FLAG (SET or RESET).
  */
FlagStatus ANAC_GetFlagStatus(u16 ANAC_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_ANAC_GET_FLAG(ANAC_FLAG));

	/* Check the status of the ANAC flag */
	if (ANAC->ANAC_FLAG & ANAC_FLAG)
	{
		/* ANAC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* ANAC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the ANAC_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified ANAC interrupt has occurred or not.
  * @param  ANAC_IT: specifies the ANAC interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg ANAC_IT_LVD_INTF: Low voltage detection interrupt
  *     @arg ANAC_IT_THR_INTF: Smoke ADC value is in the threshold interval interrupt
  *     @arg ANAC_IT_ADC_INTF: ADC conversion complete interrupt
  * @retval The new state of ANAC_IT (SET or RESET).
  */
ITStatus ANAC_GetITStatus(u8 ANAC_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_ANAC_GET_IT(ANAC_IT));

	/* Check the status of the specified ANAC interrupt */
	if ((ANAC_IT == ANAC_IT_LVD_INTF) && (ANAC->LVD_CFG & ANAC_LVD_CFG_LVD_IE) && (ANAC->ANAC_FLAG & ANAC_IT))
	{
		/* ANAC_IT is set */
		bitstatus = SET;
	}
	else if ((ANAC_IT == ANAC_IT_THR_INTF) && (ANAC->ME_CTL & ANAC_ME_CTL_THR_IE) && (ANAC->ANAC_FLAG & ANAC_IT))
	{
		/* ANAC_IT is set */
		bitstatus = SET;
	}
	else if ((ANAC_IT == ANAC_IT_ADC_INTF) && (ANAC->ADC_CTL & ANAC_ADC_CTL_ADC_IE) && (ANAC->ANAC_FLAG & ANAC_IT))
	{
		/* ANAC_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* ANAC_IT is reset */
		bitstatus = RESET;
	}
	/* Return the ANAC_IT status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for ANAC.
  * @param  ANAC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg ANAC_FLAG_ANA_OK_INTF: The analog circuit is turned on and stabilized flag
  *     @arg ANAC_FLAG_LVD_INTF: Low voltage detection interrupt flag
  *     @arg ANAC_FLAG_THR_INTF: Smoke ADC values are in the threshold range flag
  *     @arg ANAC_FLAG_ADC_INTF: ADC conversion complete interrupt flag
  * @retval None
  */
void ANAC_ClearFlag(u16 ANAC_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_ANAC_CLEAR_FLAG(ANAC_FLAG));

	/* Clear the selected ANAC flags */
	ANAC->ANAC_FLAG = ANAC_FLAG;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

