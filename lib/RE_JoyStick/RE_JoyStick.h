/**
    @file RE_JoyStick.h

	@brief
	This implements the joystick control behavior.
	It supports two modes, Mode1(right-hand throttle) and Mode2(default: left-hand throttle).
	The read ADC value will be processed and converted into specific movements(forward, backward, left-turn, right-turn, etc..)
	and also the equivalent pwm(in percentage form)
    All read ADC will be stabilized first before being published to have more better and accurate control.

	@author Alfonso, Rudy Manalo
	@version
*/

#ifndef RE_JOYSTICK_H_
#define RE_JOYSTICK_H_

#include "RE_Rte.h"


/*!
    @defined 
    @abstract Module macro definitions
    @discussion Defines the cyclic time, debounce time, number of axis per control stick, total number of elements
    equivalent pwm(in percentage form) and control stick ADC limits.
*/
#define JS_CYCLIC_TIME_K                      200u                    // 200ms
#define JS_THROTTLE_DEBOUNCE_TIME_K           (400u/JS_CYCLIC_TIME_K) // 400ms
#define JS_CONTROL_DEBOUNCE_TIME_K            (200u/JS_CYCLIC_TIME_K) // 200ms

#define JS_NUM_OF_AXIS_PER_CONTROL_STICK_K    2u                      // number of axis per control stick 
#define JS_TOTAL_NUM_OF_AXIS_K                4u                      // total number of axis in a controller
#define JS_TOTAL_NUMBER_OF_PWM_ELEMENTS_K     10u                     // total number of pwm elements

#define JS_10_PERCENT_PWM_K                   10u                     // 10% pwm
#define JS_RAW_DATA_TO_10_PERCENT_LIMIT_K     100u                    // 10% ADC limit
#define JS_20_PERCENT_PWM_K                   20u                     // 20% pwm
#define JS_RAW_DATA_TO_20_PERCENT_LIMIT_K     200u                    // 20% ADC limit
#define JS_30_PERCENT_PWM_K                   30u                     // 30% pwm
#define JS_RAW_DATA_TO_30_PERCENT_LIMIT_K     300u                    // 30% ADC limit
#define JS_40_PERCENT_PWM_K                   40u                     // 40% pwm
#define JS_RAW_DATA_TO_40_PERCENT_LIMIT_K     400u                    // 40% ADC limit
#define JS_50_PERCENT_PWM_K                   50u                     // 50% pwm
#define JS_RAW_DATA_TO_50_PERCENT_LIMIT_K     500u                    // 50% ADC limit
#define JS_60_PERCENT_PWM_K                   60u                     // 60% pwm
#define JS_RAW_DATA_TO_60_PERCENT_LIMIT_K     600u                    // 60% ADC limit
#define JS_70_PERCENT_PWM_K                   70u                     // 70% pwm
#define JS_RAW_DATA_TO_70_PERCENT_LIMIT_K     700u                    // 70% ADC limit
#define JS_80_PERCENT_PWM_K                   80u                     // 80% pwm
#define JS_RAW_DATA_TO_80_PERCENT_LIMIT_K     800u                    // 80% ADC limit
#define JS_90_PERCENT_PWM_K                   90u                     // 90% pwm
#define JS_RAW_DATA_TO_90_PERCENT_LIMIT_K     900u                    // 90% ADC limit
#define JS_100_PERCENT_PWM_K                  100u                    // 100% pwm
#define JS_RAW_DATA_TO_100_PERCENT_LIMIT_K    1000u                   // 100% ADC limit
#define JS_CTRL_STICK_BCKWD_OR_TURN_RIGHT_LIMIT_K  250u               // low limit
#define JS_CTRL_STICK_FWD_OR_TURN_LEFT_LIMIT_K     750u               // high limit
#define JS_FWRD_OR_LEFT_TURN_K                1u
#define JS_BCKWRD_OR_RIGHT_TURN_K             2u


class JoyStick
{
public:
    
	/*!
        @method
        @abstract JoyStick abstract constructor
        @discussion JoyStick class abstract constructor needed to create the abstract base class.
	 */
	JoyStick();
	
	/*!
        @method
        @abstract RE_JoyStick constructor
        @discussion RE_JoyStick class constructor with parameter that able to set the controller mode during instance creation.
	 */
	JoyStick(enum mode_et setMode_e); 

	/*!
        @function
        @abstract Module initialization
        @discussion Initialize local data and internal state into default

        @param  none
        @return none
	 */
	void joyStickF_init(void);		
	
	/*!
        @function
        @abstract Set the controller mode
        @discussion To be able to set the controller mode in either mode1 or mode2
         Mode1 -> Right throttle; Left control
         Mode2 -> Left throttle; Right control

        @param  setMode_e  {[see enum mode_et] controller mode}
        @return none
	 */
	void joyStickF_setMode(enum mode_et setMode_e);

	/*!
        @function
        @abstract Returns the controller mode
        @discussion To be able to get the controller mode

        @param  none
        @return {[see enum mode_et] controller mode}
	 */
	enum mode_et joyStickF_getMode(void);	

	/*!
        @function
        @abstract Returns throttle pwm
        @discussion Returns the throttle forward/backward equivalent pwm

        @param  none
        @return {[0..255] pwm} 
	 */
	uint8_t joyStickF_getThrottleFwdBckwd(void); 
	
	/*!
        @function
        @abstract Returns throttle pwm
        @discussion Returns the throttle left/right equivalent pwm
        Note: For now, not use when controlling robot

        @param  none
        @return {[0..255] pwm} 
	 */
	uint8_t joyStickF_getThrottleLeftRight(void); 

	/*!
        @function
        @abstract Returns direction
        @discussion Returns control direction either forward or backward

        @param  none
        @return {[see enum direction_et] direction} 
	 */
	enum direction_et joyStickF_getControlFwdBckwd(void); 

	/*!
        @function
        @abstract Returns direction
        @discussion Returns control direction either left-turn or right-turn

        @param  none
        @return {[see enum direction_et] direction} 
	 */
	enum direction_et joyStickF_getControlLeftRight(void); 	

    /*!
        @function
        @abstract Module cyclic function
        @discussion Called in fixed time interval

        @param  none
        @return none
	 */
    void joyStickF_Cyclic(void); 

protected:

	enum mode_et mode_e_;                           // controller mode
	enum direction_et ctrl_fwd_bckwd_e_;            // control forward/backward data after being stabilized  
	enum direction_et ctrl_left_right_e_;           // control left/right data after being stabilized    
	enum direction_et raw_ctrl_fwd_bckwd_e_;        // control forward/backward data before being stabilized
	enum direction_et raw_ctrl_left_right_e_;       // control left/right data before being stabilized     
	uint8_t throttle_fwd_bckwd_;                    // throttle forward/backward data after being stabilized
	uint8_t throttle_left_right_;                   // throttle left/right data after being stabilized
	uint8_t raw_throttle_fwd_bckwd_;                // throttle forward/backward data before being stabilized
	uint8_t raw_throttle_left_right_;               // throttle left/right data before being stabilized       
	uint8_t throttle_fwd_bckwd_debounce_time_;      // throttle forward/backward debounce time
	uint8_t throttle_left_right_debounce_time_;     // throttle left/right debounce time
	uint8_t ctrl_fwd_bckwd_debounce_time_;          // control forward/backward debounce time
	uint8_t ctrl_left_right_debounce_time_;         // control left/right debounce time

private:

    /*!
        @function
        @abstract Check control direction
        @discussion Returns the general control direction based on the ADC limits and with respect to the xy-axis directions

        @param  pwm_u16 {[0..microcontroller ADC-resolution] ADC limits}
        @return {[0..2] direction with respect to xy-axis}
	 */
	uint8_t joyStickLF_checkControlDirection(uint16_t pwm_u16);
	
	/*!
        @function
        @abstract Check the control stick
        @discussion Returns the actual direction with respect to the actual stick movement(e.g. moving the stick upward means forward direction)

        @param  index_u8 {[0..1] 0 = forward/backwad; 1 = turn left/turn right}
                pwm_u16  {[0..microcontroller ADC-resolution] ADC data}
        @return {[see enum direction_et] direction according to the actual movement of the stick}
	 */
	enum direction_et joyStickLF_checkControlStick(uint8_t index_u8, uint16_t pwm_u16); 

    /*!
        @function
        @abstract Check equivalent pwm
        @discussion Returns the equvalent pwm based on the raw joystick ADC data
        The ADC data will be compared against the defined limit to determine the equivalent pwm.
        The information gather here is for the throttle.

        @param  pwm_u16 {[0..microcontroller ADC-resolution] ADC data}
        @return {[0..255] pwm} 
	 */
	uint8_t joyStickLF_checkEquivalentPwm(uint16_t pwm_u16);

    /*!
        @funtion
        @abstract Read all control stick status
        @discussion Read all raw ADC data and call specific functions(e.g. joyStickLF_checkControlStick, joyStickLF_checkEquivalentPwm) 
        to process and get the direction and pwm. Stablization of direction and pwm is not yet applied here.

        @param  none
        @return none
     */
    void joyStickLF_getAllControlSticksStatus(void);	
	
	/*!
        @function  Stabilize the control stick data
        @discussion Direction and pwm will be stabilized and data will be published via RTE.
	 */
	void joyStickLF_stabilizeAllControlSticksStatus(void); 
};

#endif // RE_JOYSTICK_H_