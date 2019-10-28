/**
 * TODO: Add description
 * 
*/

#include "RE_Rte.h"


/*
 */
RE_Rte_cls::RE_Rte_cls()
{

}

/*************** start -> RTE READ ***************/
/*
 */
uint16_t RE_Rte_cls::Rte_Read_VoltageMonitoring_VoltageInDigit(void)
{
    return(Rte_VoltageInDigit_u16);
}

/*
 */
float RE_Rte_cls::Rte_Read_VoltageMonitoring_ActualVoltage(void)
{
    return(Rte_ActualVoltage_f);
}

/*
 */
enum voltage_status_et RE_Rte_cls::Rte_Read_VoltageMonitoring_VoltageStatus(void)
{
    return(Rte_VoltageStatus_e);
}    

/*
 */
enum digitalPortState_et RE_Rte_cls::Rte_Read_Buzzer_PortState(void) 
{
    return(Rte_BuzzerDO_PortState_e);
}

/*
  */
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd(void)
{
    return(Rte_ADC_LeftJoyStick_FwdBckwrd_u16);
}
    
/*
 */
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_LeftJoyStick_LeftRight(void)
{
    return(Rte_ADC_LeftJoyStick_LeftRight_u16);
}

/*
 */
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd(void)
{
    return(Rte_ADC_RightJoyStick_FwdBckwrd_u16);
}
    
/*
 */
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_RightJoyStick_LeftRight(void)
{
    return(Rte_ADC_RightJoyStick_LeftRight_u16);
}

/*
 */
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_VoltageReading(void)
{
    return(Rte_ADC_VoltageReading_u16);
}
    
/*
 */
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_Potentiometer1(void)
{
    return(Rte_ADC_Potentiometer1_u16);
}

/*
 */
bool RE_Rte_cls::Rte_Read_Hal_DI_Switch1(void)   
{
    return(Rte_DI_Switch1_b);
}

/*
 */
bool RE_Rte_cls::Rte_Read_Hal_DI_Switch2(void) 
{
    return(Rte_DI_Switch2_b);
}

/*
 */
bool RE_Rte_cls::Rte_Read_Hal_DI_Switch3(void)
{
    return(Rte_DI_Switch3_b);
}

/*
 */
bool RE_Rte_cls::Rte_Read_Hal_DI_Switch4(void) 
{
    return(Rte_DI_Switch4_b);
} 

/*
 */
bool RE_Rte_cls::Rte_Read_Hal_DI_MenuSwitch(void)
{
    return(Rte_DI_MenuSwitch_b);
}

/*
 */
bool RE_Rte_cls::Rte_Read_Hal_DO_LedIndicator(void)
{
    return(Rte_DO_LedIndicator_b);
}

/*
 */
bool RE_Rte_cls::Rte_Read_Hal_DO_Buzzer(void)
{
    return(Rte_DO_Buzzer_b);
}

/*
 */   
uint8_t RE_Rte_cls::Rte_Read_JoyStick_ThrottleFwdBckwrd(void)
{
    return(Rte_JoyStick_ThrottleFwdBckwrd_u8);
}       

/*
 */   
uint8_t RE_Rte_cls::Rte_Read_JoyStick_ThrottleLeftRight(void)
{
    return(Rte_JoyStick_ThrottleLeftRight_u8);
}

/*
 */
enum direction_et RE_Rte_cls::Rte_Read_JoyStick_ControlFwdBckwrd(void)  
{
    return(Rte_JoyStick_ControlFwdBckwrd_e);
}

/*
 */
enum direction_et RE_Rte_cls::Rte_Read_JoyStick_ControlLeftRight(void)
{
    return(Rte_JoyStick_ControlLeftRight_e);
}

/*
 */
enum mode_et RE_Rte_cls::Rte_Read_JoyStick_ControllerMode(void)
{
    return(Rte_ControllerMode_e);
}

/*
 */
uint8_t RE_Rte_cls::Rte_Read_Potentiometer_Poti1Data(void)
{
    return(Rte_Potentiometer_Poti1Data_u8);
}

/*
 */
bool RE_Rte_cls::Rte_Read_Transceiver_Status(void)
{
    return(Rte_Transceiver_Status_b);
}

/*
 */
bool RE_Rte_cls::Rte_Read_SwitchIn_Switch1(void)
{
    return(Rte_SwitchIn_Switch1_b);
} 

/*
 */
bool RE_Rte_cls::Rte_Read_SwitchIn_Switch2(void)
{
    return(Rte_SwitchIn_Switch2_b);
}

/*
 */
bool RE_Rte_cls::Rte_Read_SwitchIn_Switch3(void)
{
    return(Rte_SwitchIn_Switch3_b);
} 

/*
 */
bool RE_Rte_cls::Rte_Read_SwitchIn_Switch4(void)
{
    return(Rte_SwitchIn_Switch4_b);
}

/*
 */
bool RE_Rte_cls::Rte_Read_SwitchIn_MenuSwitch(void)
{
    return(Rte_SwitchIn_MenuSwitch_b);
} 

/*
 */
enum browse_menu_et RE_Rte_cls::Rte_Read_Menu_BrowseMenu(void)   
{
    return(Rte_BrowseMenu_e);
} 

/*
 */
enum main_menu_et RE_Rte_cls::Rte_Read_Menu_MainMenu(void)
{
    return(Rte_MainMenu_e);
}
/*************** end   -> RTE READ ***************/

/**************************************************/
/*************** start -> RTE WRITE ***************/
/*
 */
void RE_Rte_cls::Rte_Write_VoltageMonitoring_VoltageInDigit(uint16_t param_u16)
{
    Rte_VoltageInDigit_u16 = param_u16;
}

/*
 */
void RE_Rte_cls::Rte_Write_VoltageMonitoring_ActualVoltage(float param_f)
{
    Rte_ActualVoltage_f = param_f;
}

/*
 */
void RE_Rte_cls::Rte_Write_VoltageMonitoring_VoltageStatus(enum voltage_status_et  param_e)
{
    Rte_VoltageStatus_e = param_e;
}  
    
/*
 */
void RE_Rte_cls::Rte_Write_Buzzer_PortState(enum digitalPortState_et  param_e)
{
    Rte_BuzzerDO_PortState_e = param_e;
}

/*
 */
void RE_Rte_cls::Rte_Write_Hal_ADC_LeftJoyStick_FwdBckwrd(uint16_t param_u16)
{
    Rte_ADC_LeftJoyStick_FwdBckwrd_u16 = param_u16;
}
    
/*
 */
void RE_Rte_cls::Rte_Write_Hal_ADC_LeftJoyStick_LeftRight(uint16_t param_u16)
{
    Rte_ADC_LeftJoyStick_LeftRight_u16 = param_u16;
}   

/*
 */
void RE_Rte_cls::Rte_Write_Hal_ADC_RightJoyStick_FwdBckwrd(uint16_t param_u16)
{
    Rte_ADC_RightJoyStick_FwdBckwrd_u16 = param_u16;
}
    
/*
 */
void RE_Rte_cls::Rte_Write_Hal_ADC_RightJoyStick_LeftRight(uint16_t param_u16)
{
    Rte_ADC_RightJoyStick_LeftRight_u16 = param_u16;
} 

/*
 */
void RE_Rte_cls::Rte_Write_Hal_ADC_VoltageReading(uint16_t param_u16)
{
    Rte_ADC_VoltageReading_u16 = param_u16;
}
    
/*
 */
void RE_Rte_cls::Rte_Write_Hal_ADC_Potentiometer1(uint16_t param_u16)
{
    Rte_ADC_Potentiometer1_u16 = param_u16;
}

/*
 */
void RE_Rte_cls::Rte_Write_Hal_DI_Switch1(bool param_b)  
{
    Rte_DI_Switch1_b = param_b;
}

/*
 */
void RE_Rte_cls::Rte_Write_Hal_DI_Switch2(bool param_b)
{
    Rte_DI_Switch2_b = param_b;
}

/*
 */
void RE_Rte_cls::Rte_Write_Hal_DI_Switch3(bool param_b) 
{
    Rte_DI_Switch3_b = param_b;
}

/*
 */
void RE_Rte_cls::Rte_Write_Hal_DI_Switch4(bool param_b) 
{
    Rte_DI_Switch4_b = param_b;
}

/*
 */
void RE_Rte_cls::Rte_Write_Hal_DI_MenuSwitch(bool param_b)
{
    Rte_DI_MenuSwitch_b = param_b;
}

/*
 */
void RE_Rte_cls::Rte_Write_Hal_DO_LedIndicator(bool param_b)
{
    Rte_DO_LedIndicator_b = param_b;
}

/*
 */
void RE_Rte_cls::Rte_Write_Hal_DO_Buzzer(bool param_b)
{
    Rte_DO_Buzzer_b = param_b;
}

/*
 */   
void RE_Rte_cls::Rte_Write_JoyStick_ThrottleFwdBckwrd(uint8_t param_u8)      
{
    Rte_JoyStick_ThrottleFwdBckwrd_u8 = param_u8;
}   

/*
 */   
void RE_Rte_cls::Rte_Write_JoyStick_ThrottleLeftRight(uint8_t param_u8) 
{
    Rte_JoyStick_ThrottleLeftRight_u8 = param_u8;
}

/*
 */
void RE_Rte_cls::Rte_Write_JoyStick_ControlFwdBckwrd(enum direction_et param_e)  
{
    Rte_JoyStick_ControlFwdBckwrd_e = param_e;
}

/*
 */
void RE_Rte_cls::Rte_Write_JoyStick_ControlLeftRight(enum direction_et param_e)
{
    Rte_JoyStick_ControlLeftRight_e = param_e;
}

/*
 */
void RE_Rte_cls::Rte_Write_JoyStick_ControllerMode(enum mode_et param_e)
{
    Rte_ControllerMode_e = param_e;
}

/*
 */
void RE_Rte_cls::Rte_Write_Potentiometer_Poti1Data(uint8_t param_u8)
{
    Rte_Potentiometer_Poti1Data_u8 = param_u8;
}

/*
 */
void RE_Rte_cls::Rte_Write_Transceiver_Status(bool param_b)
{
    Rte_Transceiver_Status_b = param_b;
}

/*
 */
void RE_Rte_cls::Rte_Write_SwitchIn_Switch1(bool param_b)
{
    Rte_SwitchIn_Switch1_b = param_b;
}

/*
 */
void RE_Rte_cls::Rte_Write_SwitchIn_Switch2(bool param_b)
{
    Rte_SwitchIn_Switch2_b = param_b;
} 

/*
 */
void RE_Rte_cls::Rte_Write_SwitchIn_Switch3(bool param_b)
{
    Rte_SwitchIn_Switch3_b = param_b;
} 

/*
 */
void RE_Rte_cls::Rte_Write_SwitchIn_Switch4(bool param_b)
{
    Rte_SwitchIn_Switch4_b = param_b;
} 

/*
 */
void RE_Rte_cls::Rte_Write_SwitchIn_MenuSwitch(bool param_b)
{
    Rte_SwitchIn_MenuSwitch_b = param_b;
} 

/*
 */
void RE_Rte_cls::Rte_Write_Menu_BrowseMenu(enum browse_menu_et param_e)
{
    Rte_BrowseMenu_e = param_e;
}   

/*
 */
void RE_Rte_cls::Rte_Write_Menu_MainMenu(enum main_menu_et param_e)
{
    Rte_MainMenu_e = param_e;
}
/*************** end   -> RTE WRITE ***************/