#ifndef RE_JOYSTICK_H_
#define RE_JOYSTICK_H_

//#include "Arduino.h"
//#include "RE_Hal.h"
#include "RE_Rte.h"

#define JS_CYCLIC_TIME_K                      200u//20u                      // 200ms
#define JS_THROTTLE_DEBOUNCE_TIME_K           (400u/JS_CYCLIC_TIME_K)//(1000u/JS_CYCLIC_TIME_K) // 1sec.
#define JS_CONTROL_DEBOUNCE_TIME_K            (200u/JS_CYCLIC_TIME_K)//(1000u/JS_CYCLIC_TIME_K) // 1sec.

#define JS_NUM_OF_AXIS_PER_CONTROL_STICK_K    2u
#define JS_TOTAL_NUM_OF_AXIS_K                4u
#define JS_TOTAL_NUMBER_OF_PWM_ELEMENTS_K     10u

#define JS_10_PERCENT_PWM_K                   10u
#define JS_RAW_DATA_TO_10_PERCENT_LIMIT_K     100u
#define JS_20_PERCENT_PWM_K                   20u
#define JS_RAW_DATA_TO_20_PERCENT_LIMIT_K     200u
#define JS_30_PERCENT_PWM_K                   30u
#define JS_RAW_DATA_TO_30_PERCENT_LIMIT_K     300u
#define JS_40_PERCENT_PWM_K                   40u
#define JS_RAW_DATA_TO_40_PERCENT_LIMIT_K     400u
#define JS_50_PERCENT_PWM_K                   50u
#define JS_RAW_DATA_TO_50_PERCENT_LIMIT_K     500u
#define JS_60_PERCENT_PWM_K                   60u
#define JS_RAW_DATA_TO_60_PERCENT_LIMIT_K     600u
#define JS_70_PERCENT_PWM_K                   70u
#define JS_RAW_DATA_TO_70_PERCENT_LIMIT_K     700u
#define JS_80_PERCENT_PWM_K                   80u
#define JS_RAW_DATA_TO_80_PERCENT_LIMIT_K     800u
#define JS_90_PERCENT_PWM_K                   90u
#define JS_RAW_DATA_TO_90_PERCENT_LIMIT_K     900u
#define JS_100_PERCENT_PWM_K                  100u
#define JS_RAW_DATA_TO_100_PERCENT_LIMIT_K    1000u
#define JS_CTRL_STICK_BCKWD_OR_TURN_RIGHT_LIMIT_K  250u
#define JS_CTRL_STICK_FWD_OR_TURN_LEFT_LIMIT_K     750u

#if 0
enum mode_et
{
	 MODE2_E = 0 // default mode
	,MODE1_E = 1
};

enum direction_et
{
	 JS_OFF_E        = 0
	,JS_FORWARD_E    = 1
	,JS_BACKWARD_E   = 2
	,JS_LEFT_TURN_E  = 3
	,JS_RIGHT_TURN_E = 4
};
#endif

class RE_JoyStick_cls
{
public:
    
	/*!
	 */
	RE_JoyStick_cls();
	
	/*!
	 */
	RE_JoyStick_cls(enum mode_et setMode_e); 
	
	/*!
	 */
	void joyStickF_setMode(enum mode_et setMode_e);

	/*!
	 */
	enum mode_et joyStickF_getMode(void);	
	/*!
	 */
	uint8_t joyStickF_getThrottleFwdBckwd(void); 
	
	/*!
	 */
	uint8_t joyStickF_getThrottleLeftRight(void); 

	/*!
	 */
	enum direction_et joyStickF_getControlFwdBckwd(void); 

	/*!
	 */
	enum direction_et joyStickF_getControlLeftRight(void); 	

	/*!
	 */
	//void joyStickF_RTE_Read_10bit_ADC(enum adc_et adc_id_e, uint16_t adc_u16); 		

    /*!
	 */
    void joyStickF_Cyclic(void); 

protected:

    /*!
	 */
	enum mode_et mode_e;
	enum direction_et ctrl_fwd_bckwd_e;
	enum direction_et ctrl_left_right_e;
	enum direction_et raw_ctrl_fwd_bckwd_e;
	enum direction_et raw_ctrl_left_right_e;
	uint8_t throttle_fwd_bckwd_u8;
	uint8_t throttle_left_right_u8;
	uint8_t raw_throttle_fwd_bckwd_u8;
	uint8_t raw_throttle_left_right_u8;
	uint8_t throttle_fwd_bckwd_debounce_time_u8;
	uint8_t throttle_left_right_debounce_time_u8;
	uint8_t ctrl_fwd_bckwd_debounce_time_u8;
	uint8_t ctrl_left_right_debounce_time_u8;
	//uint16_t RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_JOYSTICK_MAX_E];

private:

    /*!
	 */
	uint8_t joyStickLF_checkControlDirection(uint16_t pwm_u16);
	
	/*!
	 */
	enum direction_et joyStickLF_checkControlStick(uint8_t index_u8, uint16_t pwm_u16); 

    /*!
	 */
	uint8_t joyStickLF_checkEquivalentPwm(uint16_t pwm_u16);

    /*!
     */
    void joyStickLF_getAllControlSticksStatus(void);	
	
	/*!
	 */
	void joyStickLF_stabilizeAllControlSticksStatus(void); 
};

#endif // RE_JOYSTICK_H_