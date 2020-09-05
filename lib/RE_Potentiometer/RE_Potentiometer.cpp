/**
    @file RE_Potentiometer.cpp

	@brief
	This module handles the Poti implementation.
	The data coming from Poti can be used to control the speed(e.g. motor) or brightness(e.g. Light).
	It depends on the raw ADC value, the equivalent PWM will be known.

	@author Alfonso, Rudy Manalo
	@version
*/

#include "RE_Potentiometer.h"


// Poti pwm constant definition
static const uint8_t POTI_PWM[POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K] =
{
	 POTI_10_PERCENT_PWM_K
	,POTI_20_PERCENT_PWM_K
	,POTI_30_PERCENT_PWM_K
	,POTI_40_PERCENT_PWM_K
	,POTI_50_PERCENT_PWM_K
	,POTI_60_PERCENT_PWM_K
	,POTI_70_PERCENT_PWM_K
	,POTI_80_PERCENT_PWM_K
	,POTI_90_PERCENT_PWM_K
	,POTI_100_PERCENT_PWM_K
};

// Poti ADC limits constant definition
static const uint16_t POTI_RAW_DATA[POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K] =
{
	 POTI_RAW_DATA_TO_10_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_20_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_30_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_40_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_50_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_60_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_70_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_80_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_90_PERCENT_LIMIT_K
	,POTI_RAW_DATA_TO_100_PERCENT_LIMIT_K
};


// CLASS CONSTRUCTOR
// ---------------------------------------------------------------------------
Poti::Poti()
{
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void Poti::potiF_Init(void)
{
    uint8_t idx;
	
	for(idx=0u; idx < POTI_TOTAL_NUMBER_K; idx++)
	{
		// initialize into default value/state
	    poti_raw_pwm_data_[idx]  = 0u;
	    poti_pwm_data_[idx]      = 0u;
	    poti_debounce_time_[idx] = 0u;
	}	
}

// ---------------------------------------------------------------------------
// Cyclic function
void Poti::potiF_Cyclic(void)
{
    uint8_t idx;
	
	for(idx=0u; idx < POTI_TOTAL_NUMBER_K; idx++)
	{
        // check pwm status
		potiLF_getAndCheckPotiPwm(idx);
		
		// apply debounce time to stabilize the data
		potiLF_stabilizePotiPwm(idx);
	}
}	

// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Convert raw data into equivalent pwm value
uint8_t Poti::potiLF_checkEquivalentPwm(uint16_t adc_u16)
{
	uint8_t idx;
	uint8_t pwm_u8;
	
	pwm_u8 = POTI_100_PERCENT_PWM_K;
	for(idx=0u; idx < POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K; idx++)
	{
		if(adc_u16 < POTI_RAW_DATA[idx])
		{
			pwm_u8 = POTI_PWM[idx];
			break;
		}
		else
		{
			// no action
		}
	}
	
	return(pwm_u8);
}	

// ---------------------------------------------------------------------------
// Read the ADC value and check the pwm status
void Poti::potiLF_getAndCheckPotiPwm(uint8_t idx)
{
	uint8_t  tmp_u8;
	uint16_t tmp_u16;
	
	// read the ADC from Rte interface
	tmp_u16 = rte_ivar.Rte_Read_Hal_ADC_Potentiometer1();
    // check the equivalent pwm
	tmp_u8  = potiLF_checkEquivalentPwm(tmp_u16);
    // check if pwm data is changed or not
	if(tmp_u8 != poti_raw_pwm_data_[idx])
	{
		poti_debounce_time_[idx] = 0u;    // reset debounce time because pwm data is changed.
		poti_raw_pwm_data_[idx] = tmp_u8; // stored the new pwm to buffer
	}
	else
	{
		// no action
	}
}

// ---------------------------------------------------------------------------
// Stabilize the pwm data
void Poti::potiLF_stabilizePotiPwm(uint8_t idx)
{
    // Make sure the pwm data is the same until debounce time is elapsed.
	if(poti_debounce_time_[idx] >= POTI_KNOB_DEBOUNCE_TIME_K)
	{
        // pwm data is stable. It is safe to use.
		poti_pwm_data_[idx] = poti_raw_pwm_data_[idx];
        // Update Rte information as data is already stable.
		rte_ivar.Rte_Write_Potentiometer_Poti1Data(poti_pwm_data_[idx]);
	}
	else
	{
		poti_debounce_time_[idx]++;
	}
}	