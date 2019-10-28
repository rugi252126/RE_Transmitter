/*
Add description
*/

#include "RE_Potentiometer.h"
#include "RE_Rte.h"


static const uint8_t poti_pwm[POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K] =
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

static const uint16_t poti_raw_data[POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K] =
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

/* will use this for possible future upgrade */
static const enum adc_et adc_id_e[POTI_TOTAL_NUMBER_K] = 
{
	HAL_ADC_POTENTIOMETER1_E
};


/*
 */
RE_Poti_cls::RE_Poti_cls()
{
	#if 0
    uint8_t idx;
	
	for(idx=0u; idx < POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K; idx++)
	{
		// initialize the variables
	    poti_raw_data_u8[idx] = 0u;
	    poti_data_u8[idx] = 0u;
	    poti_debounce_time_u8[idx] = 0u;
	}
	#endif
}

/*
 */
//void RE_Poti_cls::potiF_RTE_Read_10bit_ADC(uint8_t adc_id_u8, uint16_t adc_u16)
//{
    //RTE_Read_Poti_10bit_ADC_u16[adc_id_u8] = adc_u16;
//}

/*
 */
uint8_t RE_Poti_cls::potiF_getValue(uint8_t idx) 
{
	return(poti_data_u8[idx]);
}
 
/* 
 */
void RE_Poti_cls::potiF_Cyclic(void)
{
    uint8_t idx;
	
	for(idx=0u; idx < POTI_TOTAL_NUMBER_K; idx++)
	{
		potiLF_getAllPotiStatus(idx);
		
		// apply debounce time to stabilize the data
		potiLF_stabilizePotiStatus(idx);
	}
}	

/*********************************************************************************/

/*
 Convert raw data into equivalent Pwm value.
 */
uint8_t RE_Poti_cls::potiLF_checkEquivalentPwm(uint16_t pwm_u16)
{
	uint8_t idx;
	uint8_t pwm_u8;
	
	pwm_u8 = POTI_100_PERCENT_PWM_K;
	for(idx=0u; idx < POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K; idx++)
	{
		if(pwm_u16 < poti_raw_data[idx])
		{
			pwm_u8 = poti_pwm[idx];
			break;
		}
		else
		{
			/* no action */
		}
	}
	
	return(pwm_u8);
}	

/*
 */
void RE_Poti_cls::potiLF_getAllPotiStatus(uint8_t idx)
{
	uint8_t  tmp_u8;
	uint16_t tmp_u16;
	//RE_Hal   poti_cls; // create an object from class RE_Hal
	
	
	tmp_u16 = Rte_cls.Rte_Read_Hal_ADC_Potentiometer1(); //RTE_Read_Poti_10bit_ADC_u16[idx]; // poti_cls.halF_getADC_10bit(adc_id_e[idx]);
	tmp_u8  = potiLF_checkEquivalentPwm(tmp_u16);
	if(tmp_u8 != poti_raw_data_u8[idx])
	{
		poti_debounce_time_u8[idx] = 0u; // reset debounce time because data has been changed.
		poti_raw_data_u8[idx] = tmp_u8;
	}
	else
	{
		/* no action */
	}
}

/*
 */
void RE_Poti_cls::potiLF_stabilizePotiStatus(uint8_t idx)
{
    switch(adc_id_e[idx])
	{
		case HAL_ADC_POTENTIOMETER1_E:
		{
			if(poti_debounce_time_u8[idx] >= POTI_KNOB_DEBOUNCE_TIME_K)
			{
				poti_data_u8[idx] = poti_raw_data_u8[idx];
				if(0u == idx)
				{
				    Rte_cls.Rte_Write_Potentiometer_Poti1Data(poti_data_u8[0]);
				}
                else
				{
				    // for future update if need to add more potentiometer
				}
			}
			else
			{
				poti_debounce_time_u8[idx]++;
			}
			break;
		}
		/* case ...*/
		default:
		{
			break;
		}
	}
}	