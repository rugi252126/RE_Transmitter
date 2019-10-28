#ifndef RE_POTENTIOMETER_H_
#define RE_POTENTIOMETER_H_

#include "RE_Hal.h"

#define POTI_CYCLIC_TIME_K                      200u//20u                        // 200ms
#define POTI_KNOB_DEBOUNCE_TIME_K               (1000u/POTI_CYCLIC_TIME_K) // 1sec.
#define POTI_TOTAL_NUMBER_K                     1u                         // total number of available potentiometer
#define POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K     10u

#define POTI_10_PERCENT_PWM_K                   10u
#define POTI_RAW_DATA_TO_10_PERCENT_LIMIT_K     100u
#define POTI_20_PERCENT_PWM_K                   20u
#define POTI_RAW_DATA_TO_20_PERCENT_LIMIT_K     200u
#define POTI_30_PERCENT_PWM_K                   30u
#define POTI_RAW_DATA_TO_30_PERCENT_LIMIT_K     300u
#define POTI_40_PERCENT_PWM_K                   40u
#define POTI_RAW_DATA_TO_40_PERCENT_LIMIT_K     400u
#define POTI_50_PERCENT_PWM_K                   50u
#define POTI_RAW_DATA_TO_50_PERCENT_LIMIT_K     500u
#define POTI_60_PERCENT_PWM_K                   60u
#define POTI_RAW_DATA_TO_60_PERCENT_LIMIT_K     600u
#define POTI_70_PERCENT_PWM_K                   70u
#define POTI_RAW_DATA_TO_70_PERCENT_LIMIT_K     700u
#define POTI_80_PERCENT_PWM_K                   80u
#define POTI_RAW_DATA_TO_80_PERCENT_LIMIT_K     800u
#define POTI_90_PERCENT_PWM_K                   90u
#define POTI_RAW_DATA_TO_90_PERCENT_LIMIT_K     900u
#define POTI_100_PERCENT_PWM_K                  100u
#define POTI_RAW_DATA_TO_100_PERCENT_LIMIT_K    1000u

class RE_Poti_cls
{
public:
    /*!
	 */
	RE_Poti_cls(); 
	
	/*!
	 */
	uint8_t potiF_getValue(uint8_t idx); 

    /*
	 */
	//void potiF_RTE_Read_10bit_ADC(uint8_t adc_id_u8, uint16_t adc_u16);	
	
	/*!
	 */
	 void potiF_Cyclic(void);

protected:
    uint8_t poti_raw_data_u8[POTI_TOTAL_NUMBER_K];
	uint8_t poti_data_u8[POTI_TOTAL_NUMBER_K];
	uint8_t poti_debounce_time_u8[POTI_TOTAL_NUMBER_K];
	//uint16_t RTE_Read_Poti_10bit_ADC_u16[POTI_TOTAL_NUMBER_K];

private:

	/*!
	 */
	uint8_t potiLF_checkEquivalentPwm(uint16_t pwm_u16); 
	
	/*!
	 */
	void potiLF_getAllPotiStatus(uint8_t idx);
	
	/*!
	 */
	void potiLF_stabilizePotiStatus(uint8_t idx);
	
};

#endif // RE_POTENTIOMETER_H_