/**
    @file RE_JoyStick.cpp

	@brief
	This implements the joystick control behavior.
	It supports two modes, Mode1(right-hand throttle) and Mode2(default: left-hand throttle).
	The read ADC value will be processed and converted into specific movements(forward, backward, left-turn, right-turn, etc..)
	and also the equivalent pwm(in percentage form)
    All read ADC will be stabilized first before being published to have more better and accurate control.

	@author Alfonso, Rudy Manalo
	@version
*/

#include "RE_JoyStick.h"


static const uint8_t joyStick_throttle_pwm[JS_TOTAL_NUMBER_OF_PWM_ELEMENTS_K] =
{
	 JS_10_PERCENT_PWM_K
	,JS_20_PERCENT_PWM_K
	,JS_30_PERCENT_PWM_K
	,JS_40_PERCENT_PWM_K
	,JS_50_PERCENT_PWM_K
	,JS_60_PERCENT_PWM_K
	,JS_70_PERCENT_PWM_K
	,JS_80_PERCENT_PWM_K
	,JS_90_PERCENT_PWM_K
	,JS_100_PERCENT_PWM_K
};

static const uint16_t joyStick_throttle_raw_data[JS_TOTAL_NUMBER_OF_PWM_ELEMENTS_K] =
{
	 JS_RAW_DATA_TO_10_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_20_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_30_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_40_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_50_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_60_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_70_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_80_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_90_PERCENT_LIMIT_K
	,JS_RAW_DATA_TO_100_PERCENT_LIMIT_K
};

// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------
JoyStick::JoyStick()
{
}

// ---------------------------------------------------------------------------
// Set the controller mode during instance creation. 
JoyStick::JoyStick(enum mode_et setMode_e)
{
	mode_e_ = setMode_e;
	// Update Rte interface
	rte_ivar.Rte_Write_JoyStick_ControllerMode(mode_e_); 		
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization	
void JoyStick::joyStickF_init(void)
{
	mode_e_ = MODE2_E;
	ctrl_fwd_bckwd_e_ = JS_OFF_E;
	ctrl_left_right_e_ = JS_OFF_E;
	raw_ctrl_fwd_bckwd_e_ = JS_OFF_E;
	raw_ctrl_left_right_e_ = JS_OFF_E;
	throttle_fwd_bckwd_ = 0u;
	throttle_left_right_ = 0u;
	raw_throttle_fwd_bckwd_ = 0u;
	raw_throttle_left_right_ = 0u;
	throttle_fwd_bckwd_debounce_time_ = 0u;
	throttle_left_right_debounce_time_ = 0u;
	ctrl_fwd_bckwd_debounce_time_ = 0u;
	ctrl_left_right_debounce_time_ = 0u;
}

// ---------------------------------------------------------------------------
// Function to set the controller mode(mode1 or mode2).
void JoyStick::joyStickF_setMode(enum mode_et setMode_e)
{
    mode_e_ = setMode_e;
}

// ---------------------------------------------------------------------------
// Returns controller mode(mode1 or mode2).
enum mode_et JoyStick::joyStickF_getMode(void)
{
    return(mode_e_);
}

// ---------------------------------------------------------------------------
// Returns throttle forward/backward data
uint8_t JoyStick::joyStickF_getThrottleFwdBckwd(void)
{
	return(throttle_fwd_bckwd_);
}

// ---------------------------------------------------------------------------
// Returns throttle left/right data
uint8_t JoyStick::joyStickF_getThrottleLeftRight(void)
{
	return(throttle_left_right_);
}

// ---------------------------------------------------------------------------
// Returns forward, backward or no movement
enum direction_et JoyStick::joyStickF_getControlFwdBckwd(void)
{
	return(ctrl_fwd_bckwd_e_);
}

// ---------------------------------------------------------------------------
// Returns left turn, Right turn or no movement
enum direction_et JoyStick::joyStickF_getControlLeftRight(void)
{
	return(ctrl_left_right_e_);
}

// ---------------------------------------------------------------------------
// Cyclic function
void JoyStick::joyStickF_Cyclic(void)
{
    // Get, check and process all joysticks
	joyStickLF_getAllControlSticksStatus();
	
	// Apply debounce time to stablize the data
	joyStickLF_stabilizeAllControlSticksStatus();
}	

// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Convert raw data into equivalent pwm value
uint8_t JoyStick::joyStickLF_checkEquivalentPwm(uint16_t pwm_u16)
{
	uint8_t idx;
	uint8_t pwm_u8;
	
	pwm_u8 = JS_100_PERCENT_PWM_K;
	for(idx=0u; idx < JS_TOTAL_NUMBER_OF_PWM_ELEMENTS_K; idx++)
	{
        // The data will be checked against all the limits based on the defined number of elements.
		if(pwm_u16 < joyStick_throttle_raw_data[idx])
		{
			pwm_u8 = joyStick_throttle_pwm[idx];
			break;
		}
		else
		{
			/* no action */
		}
	}
	
	return(pwm_u8);
}

// ---------------------------------------------------------------------------
// Contains general information for forward/backward or left turn/right turn
uint8_t JoyStick::joyStickLF_checkControlDirection(uint16_t pwm_u16)
{
	uint8_t direction_u8 = 0u;
	
	if(pwm_u16 < JS_CTRL_STICK_BCKWD_OR_TURN_RIGHT_LIMIT_K)
	{
		direction_u8 = JS_BCKWRD_OR_RIGHT_TURN_K; // backward or right turn
	}
	else if(pwm_u16 > JS_CTRL_STICK_FWD_OR_TURN_LEFT_LIMIT_K)
	{
		direction_u8 = JS_FWRD_OR_LEFT_TURN_K;    // forward or left turn
	}
	else
	{
		direction_u8 = 0u;
	}

	return(direction_u8);
}

// ---------------------------------------------------------------------------
// Contains specific information for forward/backward or left turn/right turn
enum direction_et JoyStick::joyStickLF_checkControlStick(uint8_t index_u8, uint16_t pwm_u16)
{
	uint8_t dir_u8;
	enum direction_et direction_e;
	
	direction_e = JS_OFF_E;
	
	// arrangement would be: index_u8 = 0 -> forward/backwad; index_u8 = 1 -> turn left/turn right
    if(0u == index_u8)
	{ // forward/backwad
		dir_u8 = joyStickLF_checkControlDirection(pwm_u16);
		if(JS_FWRD_OR_LEFT_TURN_K == dir_u8)
		{
			direction_e = JS_FORWARD_E;
		}
		else if(JS_BCKWRD_OR_RIGHT_TURN_K == dir_u8)
		{
			direction_e = JS_BACKWARD_E;
		}
		else
		{
			/* no action */
		}
	}
	else if(1u == index_u8)
	{ // left/right turn
		dir_u8 = joyStickLF_checkControlDirection(pwm_u16);
		if(1u == dir_u8)
		{
			direction_e = JS_LEFT_TURN_E;
		}
		else if(2u == dir_u8)
		{
			direction_e = JS_RIGHT_TURN_E;
		}
		else
		{
			/* no action */
		}
	}
	else
	{
		/* no action */
	}

	return(direction_e);
}


// ---------------------------------------------------------------------------
// Get, check and process all joysticks
void JoyStick::joyStickLF_getAllControlSticksStatus(void)
{
	uint8_t tmp_raw_dir_u8;
	uint16_t tmp_raw_data_u16;
	enum direction_et  tmp_raw_dir_e;
	
	
	if(MODE2_E == mode_e_)
	{
		tmp_raw_data_u16 = rte_ivar.Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd();
		tmp_raw_dir_u8 = joyStickLF_checkEquivalentPwm(tmp_raw_data_u16);
		if(raw_throttle_fwd_bckwd_ != tmp_raw_dir_u8)
		{
			throttle_fwd_bckwd_debounce_time_ = 0u;
			raw_throttle_fwd_bckwd_ = tmp_raw_dir_u8;
		}else{/* no action */}
			
		tmp_raw_data_u16 = rte_ivar.Rte_Read_Hal_ADC_LeftJoyStick_LeftRight();
		tmp_raw_dir_u8 = joyStickLF_checkEquivalentPwm(tmp_raw_data_u16);
		if(raw_throttle_left_right_ != tmp_raw_dir_u8)
		{
			throttle_left_right_debounce_time_ = 0u;
			raw_throttle_left_right_ = tmp_raw_dir_u8;
		}else{/* no action */}
			
		tmp_raw_data_u16 = rte_ivar.Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd();
		tmp_raw_dir_e = joyStickLF_checkControlStick(0u, tmp_raw_data_u16);
		if(raw_ctrl_fwd_bckwd_e_ != tmp_raw_dir_e)
		{
			ctrl_fwd_bckwd_debounce_time_ = 0u;
			raw_ctrl_fwd_bckwd_e_ = tmp_raw_dir_e;
		}else{/* no action */}
			
		tmp_raw_data_u16 = rte_ivar.Rte_Read_Hal_ADC_RightJoyStick_LeftRight();
		tmp_raw_dir_e = joyStickLF_checkControlStick(1u, tmp_raw_data_u16);
		if(raw_ctrl_left_right_e_ != tmp_raw_dir_e)
		{
			ctrl_left_right_debounce_time_ = 0u;
			raw_ctrl_left_right_e_ = tmp_raw_dir_e;
		}else{/* no action */}
	}
	else
	{
		tmp_raw_data_u16 = rte_ivar.Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd();
		tmp_raw_dir_u8 = joyStickLF_checkEquivalentPwm(tmp_raw_data_u16);
		if(raw_throttle_fwd_bckwd_ != tmp_raw_dir_u8)
		{
			throttle_fwd_bckwd_debounce_time_ = 0u;
			raw_throttle_fwd_bckwd_ = tmp_raw_dir_u8;
		}else{/* no action */}
			
		tmp_raw_data_u16 = rte_ivar.Rte_Read_Hal_ADC_RightJoyStick_LeftRight();
		tmp_raw_dir_u8 = joyStickLF_checkEquivalentPwm(tmp_raw_data_u16);
		if(raw_throttle_left_right_ != tmp_raw_dir_u8)
		{
			throttle_left_right_debounce_time_ = 0u;
			raw_throttle_left_right_ = tmp_raw_dir_u8;
		}else{/* no action */}
			
		tmp_raw_data_u16 = rte_ivar.Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd();
		tmp_raw_dir_e = joyStickLF_checkControlStick(0u, tmp_raw_data_u16);
		if(raw_ctrl_fwd_bckwd_e_ != tmp_raw_dir_e)
		{
			ctrl_fwd_bckwd_debounce_time_ = 0u;
			raw_ctrl_fwd_bckwd_e_ = tmp_raw_dir_e;
		}else{/* no action */}
			
		tmp_raw_data_u16 = rte_ivar.Rte_Read_Hal_ADC_LeftJoyStick_LeftRight();
		tmp_raw_dir_e = joyStickLF_checkControlStick(1u, tmp_raw_data_u16);
		if(raw_ctrl_left_right_e_ != tmp_raw_dir_e)
		{
			ctrl_left_right_debounce_time_ = 0u;
			raw_ctrl_left_right_e_ = tmp_raw_dir_e;
		}else{/* no action */}		
	}
}

// ---------------------------------------------------------------------------
// Stabilize the data and update RTE interfaces
void JoyStick::joyStickLF_stabilizeAllControlSticksStatus(void)
{
	if(throttle_fwd_bckwd_debounce_time_ >= JS_THROTTLE_DEBOUNCE_TIME_K)
	{
		throttle_fwd_bckwd_ = raw_throttle_fwd_bckwd_;
		// Update Rte interface
		rte_ivar.Rte_Write_JoyStick_ThrottleFwdBckwrd(throttle_fwd_bckwd_); 
	}
	else
	{
		throttle_fwd_bckwd_debounce_time_++;
	}
	
	if(throttle_left_right_debounce_time_ >= JS_THROTTLE_DEBOUNCE_TIME_K)
	{
		throttle_left_right_ = raw_throttle_left_right_;
		// Update Rte interface
		rte_ivar.Rte_Write_JoyStick_ThrottleLeftRight(throttle_left_right_); 		
	}
	else
	{
		throttle_left_right_debounce_time_++;
	}	

	if(ctrl_fwd_bckwd_debounce_time_ >= JS_CONTROL_DEBOUNCE_TIME_K)
	{
		ctrl_fwd_bckwd_e_ = raw_ctrl_fwd_bckwd_e_;
		// Update Rte interface
		rte_ivar.Rte_Write_JoyStick_ControlFwdBckwrd(ctrl_fwd_bckwd_e_); 			
	}
	else
	{
		ctrl_fwd_bckwd_debounce_time_++;
	}
	
	if(ctrl_left_right_debounce_time_ >= JS_CONTROL_DEBOUNCE_TIME_K)
	{
		ctrl_left_right_e_ = raw_ctrl_left_right_e_;
		// Update Rte interface
		rte_ivar.Rte_Write_JoyStick_ControlLeftRight(ctrl_left_right_e_); 		
	}
	else
	{
		ctrl_left_right_debounce_time_++;
	}		
}