/**
    @file RE_Potentiometer.h

	@brief
	This module handles the Poti implementation.
	The data coming from Poti can be used to control the speed(e.g. motor) or brightness(e.g. Light).
	It depends on the raw ADC value, the equivalent PWM will be known.

	@author Alfonso, Rudy Manalo
	@version
*/

#ifndef RE_POTENTIOMETER_H_
#define RE_POTENTIOMETER_H_

#include "RE_Rte.h"

/*!
    @defined 
    @abstract Module macro definitions
    @discussion Defines the cyclic time, debounce time, number of potentiometer, total number of elements,
    equivalent pwm(in percentage form) and poti ADC limits.
*/

#define POTI_CYCLIC_TIME_K                      200u                       // 200ms -> module cyclic time
#define POTI_KNOB_DEBOUNCE_TIME_K               (1000u/POTI_CYCLIC_TIME_K) // 1sec. time to stabilize the reading
#define POTI_TOTAL_NUMBER_K                     1u                         // total number of available potentiometer
#define POTI_TOTAL_NUMBER_OF_PWM_ELEMENTS_K     10u                        // total number of elements

#define POTI_10_PERCENT_PWM_K                   10u                        // 10% pwm
#define POTI_RAW_DATA_TO_10_PERCENT_LIMIT_K     100u                       // 10% ADC limit
#define POTI_20_PERCENT_PWM_K                   20u                        // 20% pwm
#define POTI_RAW_DATA_TO_20_PERCENT_LIMIT_K     200u                       // 20% ADC limit
#define POTI_30_PERCENT_PWM_K                   30u                        // 30% pwm
#define POTI_RAW_DATA_TO_30_PERCENT_LIMIT_K     300u                       // 30% ADC limit
#define POTI_40_PERCENT_PWM_K                   40u                        // 40% pwm
#define POTI_RAW_DATA_TO_40_PERCENT_LIMIT_K     400u                       // 40% ADC limit
#define POTI_50_PERCENT_PWM_K                   50u                        // 50% pwm
#define POTI_RAW_DATA_TO_50_PERCENT_LIMIT_K     500u                       // 50% ADC limit
#define POTI_60_PERCENT_PWM_K                   60u                        // 60% pwm
#define POTI_RAW_DATA_TO_60_PERCENT_LIMIT_K     600u                       // 60% ADC limit
#define POTI_70_PERCENT_PWM_K                   70u                        // 70% pwm
#define POTI_RAW_DATA_TO_70_PERCENT_LIMIT_K     700u                       // 70% ADC limit
#define POTI_80_PERCENT_PWM_K                   80u                        // 80% pwm
#define POTI_RAW_DATA_TO_80_PERCENT_LIMIT_K     800u                       // 80% ADC limit
#define POTI_90_PERCENT_PWM_K                   90u                        // 90% pwm
#define POTI_RAW_DATA_TO_90_PERCENT_LIMIT_K     900u                       // 90% ADC limit
#define POTI_100_PERCENT_PWM_K                  100u                       // 100% pwm
#define POTI_RAW_DATA_TO_100_PERCENT_LIMIT_K    1000u                      // 100% ADC limit

class RE_Poti_cls
{
public:

	/*!
        @method
        @abstract RE_Potentiometer abstract constructor
        @discussion RE_Potentiometer class abstract constructor needed to create the abstract base class.
	*/
	RE_Poti_cls(); 

	/*!
        @function
        @abstract Module initialization
        @discussion Initialize local data and internal state into default

        @param  none
        @return none
	*/
	 void potiF_Init(void);	
	
    /*!
        @function
        @abstract Module cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
	*/
	 void potiF_Cyclic(void);

protected:

    uint8_t poti_raw_pwm_data_u8[POTI_TOTAL_NUMBER_K];  // raw pwm data
	uint8_t poti_pwm_data_u8[POTI_TOTAL_NUMBER_K];      // stabilized pwm data
	uint8_t poti_debounce_time_u8[POTI_TOTAL_NUMBER_K]; // debounce time to stabilize the raw data

private:

	/*!
	    @function
		@abstract Check equivalent pwm
		@discussion The poti raw ADC value will be compared to the ADC limits to get the equivalent pwm.

		@param  adc_u16 {[0..ADC resolution] poti raw ADC value}
		@return none
	*/
	uint8_t potiLF_checkEquivalentPwm(uint16_t adc_u16); 
	
	/*!
	    @function
		@abstract Get and check poti status
		@discussion Read the poti raw ADC value and check if the pwm is changed.

		@param  idx {[0..POTI_TOTAL_NUMBER_K] poti index}
		@return none
	*/
	void potiLF_getAndCheckPotiPwm(uint8_t idx);
	
	/*!
	    @function
		@abstract Stabilize poti pwm
		@discussion The raw poti pwm will be stabilized before being sent to Rte interface.
		Makes sure the poti data is stable before being used by other modules.

		@param  idx {[0..POTI_TOTAL_NUMBER_K] poti index}
		@return none 
	*/
	void potiLF_stabilizePotiPwm(uint8_t idx);
	
};

#endif // RE_POTENTIOMETER_H_