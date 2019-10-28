/*
Add description
*/


//#include "RE_Rte.h"
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

/*
 Default constructor
*/
RE_JoyStick_cls::RE_JoyStick_cls()
{
	// initialize the variables
	#if 0
	mode_e = MODE2_E;
	ctrl_fwd_bckwd_e = JS_OFF_E;
	ctrl_left_right_e = JS_OFF_E;
	raw_ctrl_fwd_bckwd_e = JS_OFF_E;
	raw_ctrl_left_right_e = JS_OFF_E;
	throttle_fwd_bckwd_u8 = 0u;
	throttle_left_right_u8 = 0u;
	raw_throttle_fwd_bckwd_u8 = 0u;
	raw_throttle_left_right_u8 = 0u;
	throttle_fwd_bckwd_debounce_time_u8 = 0u;
	throttle_left_right_debounce_time_u8 = 0u;
	ctrl_fwd_bckwd_debounce_time_u8 = 0u;
	ctrl_left_right_debounce_time_u8 = 0u;
	#endif
}

/*
 Set the controller mode during initialization.
 Default mode is Mode2
 */
RE_JoyStick_cls::RE_JoyStick_cls(enum mode_et setMode_e)
{
	mode_e = setMode_e;
	// Update Rte interface
	Rte_cls.Rte_Write_JoyStick_ControllerMode(mode_e); 		
}

/*
 Function to check the controller mode.
 Mode1 or Mode2.
 Mode1 => Right throttle; Left controller
 Mode2 => Left throttle; Right control
 */
void RE_JoyStick_cls::joyStickF_setMode(enum mode_et setMode_e)
{
    mode_e = setMode_e;
}

/*
 */
enum mode_et RE_JoyStick_cls::joyStickF_getMode(void)
{
    return(mode_e);
}

/*
 Throttle increase or decrease
 */
uint8_t RE_JoyStick_cls::joyStickF_getThrottleFwdBckwd(void)
{
	return(throttle_fwd_bckwd_u8);
}

/*
 not use in robot
 */
uint8_t RE_JoyStick_cls::joyStickF_getThrottleLeftRight(void)
{
	return(throttle_left_right_u8);
}

/*
 Forward, backward or no movement
 */
enum direction_et RE_JoyStick_cls::joyStickF_getControlFwdBckwd(void)
{
	return(ctrl_fwd_bckwd_e);
}

/*
 Left turn, Right turn or no movement
 */
enum direction_et RE_JoyStick_cls::joyStickF_getControlLeftRight(void)
{
	return(ctrl_left_right_e);
}

//void RE_JoyStick_cls::joyStickF_RTE_Read_10bit_ADC(enum adc_et adc_id_e, uint16_t adc_u16)
//{
//    RTE_Read_JoyStick_10bit_ADC_u16[adc_id_e] = adc_u16;
//}

/*
 */
void RE_JoyStick_cls::joyStickF_Cyclic(void)
{
	joyStickLF_getAllControlSticksStatus();
	
	// apply debounce time to stablize the data
	joyStickLF_stabilizeAllControlSticksStatus();
}	

/************************************************************************************/

/*
 Convert raw data into equivalent Pwm value.
 The info. gather here is for the throttle.
 */
uint8_t RE_JoyStick_cls::joyStickLF_checkEquivalentPwm(uint16_t pwm_u16)
{
	uint8_t idx;
	uint8_t pwm_u8;
	
	pwm_u8 = JS_100_PERCENT_PWM_K;
	for(idx=0u; idx < JS_TOTAL_NUMBER_OF_PWM_ELEMENTS_K; idx++)
	{
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

/*
 Contains info. for -> forward/backward or left turn/right turn
 */
uint8_t RE_JoyStick_cls::joyStickLF_checkControlDirection(uint16_t pwm_u16)
{
	uint8_t direction_u8 = 0u;
	
	if(pwm_u16 < JS_CTRL_STICK_BCKWD_OR_TURN_RIGHT_LIMIT_K)
	{
		direction_u8 = 2u;
	}
	else if(pwm_u16 > JS_CTRL_STICK_FWD_OR_TURN_LEFT_LIMIT_K)
	{
		direction_u8 = 1u; // forward or turn left
	}
	else
	{
		direction_u8 = 0u;
	}

	return(direction_u8);
}

/*
 Contains info. for -> forward/backward or left turn/right turn
 */
enum direction_et RE_JoyStick_cls::joyStickLF_checkControlStick(uint8_t index_u8, uint16_t pwm_u16)
{
	uint8_t dir_u8;
	enum direction_et direction_e;
	
	direction_e = JS_OFF_E;
	
	// arrangement would be -> 1.] forward/backwad; 2.] turn left/turn right
    if(0u == index_u8)
	{ // forward/backwad
		dir_u8 = joyStickLF_checkControlDirection(pwm_u16);
		if(1u == dir_u8)
		{
			direction_e = JS_FORWARD_E;
		}
		else if(2u == dir_u8)
		{
			direction_e = JS_BACKWARD_E;
		}
		else
		{
			/* no action */
		}
	}
	else if(1u == index_u8)
	{ // left/turn right
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


/*
 */
void RE_JoyStick_cls::joyStickLF_getAllControlSticksStatus(void)
{
	uint8_t tmp_raw_dir_u8;
	uint16_t tmp_raw_data_u16;
	enum direction_et  tmp_raw_dir_e;
	
	
	if(MODE2_E == mode_e)
	{
		tmp_raw_data_u16 = Rte_cls.Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd(); //RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_LEFT_JOYSTICK_FWD_BCKWD_E]; // re_hal_cls.halF_getADC_10bit(HAL_ADC_LEFT_JOYSTICK_FWD_BCKWD_E);
		tmp_raw_dir_u8 = joyStickLF_checkEquivalentPwm(tmp_raw_data_u16);
		if(raw_throttle_fwd_bckwd_u8 != tmp_raw_dir_u8)
		{
			throttle_fwd_bckwd_debounce_time_u8 = 0u;
			raw_throttle_fwd_bckwd_u8 = tmp_raw_dir_u8;
		}else{/* no action */}
			
		tmp_raw_data_u16 = Rte_cls.Rte_Read_Hal_ADC_LeftJoyStick_LeftRight(); //RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_E]; // re_hal_cls.halF_getADC_10bit(HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_E);
		tmp_raw_dir_u8 = joyStickLF_checkEquivalentPwm(tmp_raw_data_u16);
		if(raw_throttle_left_right_u8 != tmp_raw_dir_u8)
		{
			throttle_left_right_debounce_time_u8 = 0u;
			raw_throttle_left_right_u8 = tmp_raw_dir_u8;
		}else{/* no action */}
			
		tmp_raw_data_u16 = Rte_cls.Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd(); //RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWD_E]; // re_hal_cls.halF_getADC_10bit(HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWD_E);
		tmp_raw_dir_e = joyStickLF_checkControlStick(0u, tmp_raw_data_u16);
		if(raw_ctrl_fwd_bckwd_e != tmp_raw_dir_e)
		{
			ctrl_fwd_bckwd_debounce_time_u8 = 0u;
			raw_ctrl_fwd_bckwd_e = tmp_raw_dir_e;
		}else{/* no action */}
			
		tmp_raw_data_u16 = Rte_cls.Rte_Read_Hal_ADC_RightJoyStick_LeftRight(); //RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_E]; // re_hal_cls.halF_getADC_10bit(HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_E);
		tmp_raw_dir_e = joyStickLF_checkControlStick(1u, tmp_raw_data_u16);
		if(raw_ctrl_left_right_e != tmp_raw_dir_e)
		{
			ctrl_left_right_debounce_time_u8 = 0u;
			raw_ctrl_left_right_e = tmp_raw_dir_e;
		}else{/* no action */}
	}
	else
	{
		tmp_raw_data_u16 = Rte_cls.Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd(); //RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWD_E]; // re_hal_cls.halF_getADC_10bit(HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWD_E);
		tmp_raw_dir_u8 = joyStickLF_checkEquivalentPwm(tmp_raw_data_u16);
		if(raw_throttle_fwd_bckwd_u8 != tmp_raw_dir_u8)
		{
			throttle_fwd_bckwd_debounce_time_u8 = 0u;
			raw_throttle_fwd_bckwd_u8 = tmp_raw_dir_u8;
		}else{/* no action */}
			
		tmp_raw_data_u16 = Rte_cls.Rte_Read_Hal_ADC_RightJoyStick_LeftRight(); //RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_E]; // re_hal_cls.halF_getADC_10bit(HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_E);
		tmp_raw_dir_u8 = joyStickLF_checkEquivalentPwm(tmp_raw_data_u16);
		if(raw_throttle_left_right_u8 != tmp_raw_dir_u8)
		{
			throttle_left_right_debounce_time_u8 = 0u;
			raw_throttle_left_right_u8 = tmp_raw_dir_u8;
		}else{/* no action */}
			
		tmp_raw_data_u16 = Rte_cls.Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd(); //RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_LEFT_JOYSTICK_FWD_BCKWD_E]; // re_hal_cls.halF_getADC_10bit(HAL_ADC_LEFT_JOYSTICK_FWD_BCKWD_E);
		tmp_raw_dir_e = joyStickLF_checkControlStick(0u, tmp_raw_data_u16);
		if(raw_ctrl_fwd_bckwd_e != tmp_raw_dir_e)
		{
			ctrl_fwd_bckwd_debounce_time_u8 = 0u;
			raw_ctrl_fwd_bckwd_e = tmp_raw_dir_e;
		}else{/* no action */}
			
		tmp_raw_data_u16 = Rte_cls.Rte_Read_Hal_ADC_LeftJoyStick_LeftRight(); //RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_E]; // re_hal_cls.halF_getADC_10bit(HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_E);
		tmp_raw_dir_e = joyStickLF_checkControlStick(1u, tmp_raw_data_u16);
		if(raw_ctrl_left_right_e != tmp_raw_dir_e)
		{
			ctrl_left_right_debounce_time_u8 = 0u;
			raw_ctrl_left_right_e = tmp_raw_dir_e;
		}else{/* no action */}		
	}
}

/*
 */
void RE_JoyStick_cls::joyStickLF_stabilizeAllControlSticksStatus(void)
{
	if(throttle_fwd_bckwd_debounce_time_u8 >= JS_THROTTLE_DEBOUNCE_TIME_K)
	{
		throttle_fwd_bckwd_u8 = raw_throttle_fwd_bckwd_u8;
		// Update Rte interface
		Rte_cls.Rte_Write_JoyStick_ThrottleFwdBckwrd(throttle_fwd_bckwd_u8); 
	}
	else
	{
		throttle_fwd_bckwd_debounce_time_u8++;
	}
	
	if(throttle_left_right_debounce_time_u8 >= JS_THROTTLE_DEBOUNCE_TIME_K)
	{
		throttle_left_right_u8 = raw_throttle_left_right_u8;
		// Update Rte interface
		Rte_cls.Rte_Write_JoyStick_ThrottleLeftRight(throttle_left_right_u8); 		
	}
	else
	{
		throttle_left_right_debounce_time_u8++;
	}	

	if(ctrl_fwd_bckwd_debounce_time_u8 >= JS_CONTROL_DEBOUNCE_TIME_K)
	{
		ctrl_fwd_bckwd_e = raw_ctrl_fwd_bckwd_e;
		// Update Rte interface
		Rte_cls.Rte_Write_JoyStick_ControlFwdBckwrd(ctrl_fwd_bckwd_e); 			
	}
	else
	{
		ctrl_fwd_bckwd_debounce_time_u8++;
	}
	
	if(ctrl_left_right_debounce_time_u8 >= JS_CONTROL_DEBOUNCE_TIME_K)
	{
		ctrl_left_right_e = raw_ctrl_left_right_e;
		// Update Rte interface
		Rte_cls.Rte_Write_JoyStick_ControlLeftRight(ctrl_left_right_e); 		
	}
	else
	{
		ctrl_left_right_debounce_time_u8++;
	}		
}