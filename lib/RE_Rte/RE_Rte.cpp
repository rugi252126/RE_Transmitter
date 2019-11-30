/**
    @file RE_Rte.cpp

    @brief
    Handles the interfaces between modules.
    Main purpose, it serves as medium between upper layer and lower layer.
    With this approach, portability, maintainability and adaptability of different modules is easy.

    @author Alfonso, Rudy Manalo
    @version
*/

#include "RE_Rte.h"
#include "RE_Hal.h"
#include "RE_Transceiver.h"
#include "RE_Lcd.h"
#include "RE_Buzzer.h"
#include "RE_VoltageMonitoring.h"
#include "RE_JoyStick.h"
#include "RE_Led.h"
#include "RE_Potentiometer.h"
#include "RE_SwitchIn.h"
#include "RE_Menu.h"


//! Create object instances
RE_Hal                   rte_hal_cls;          // from "RE_Hal" module
RE_Transceiver_cls       rte_transceiver_cls;  // from "RE_Transceiver" module
RE_Lcd_cls               rte_lcd_cls;          // from "RE_Lcd" module    
RE_Buzzer_cls            rte_buzzer_cls;       // from "RE_Buzzer" module              
RE_VoltageMonitoring_cls rte_voltage_cls;      // from "RE_VoltageMonitoring" module   
RE_JoyStick_cls          rte_joystick_cls;     // from "RE_JoyStick" module            
RE_Led_cls               rte_led_cls;          // from "RE_Led" module                 
RE_Poti_cls              rte_poti_cls;         // from "RE_Potentiometer" module       
RE_SwitchIn_cls          rte_switchIn_cls;     // from "RE_SwitchIn" module            
RE_Menu_cls              rte_menu_cls;         // from "RE_Menu" module               

  
// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------
RE_Rte_cls::RE_Rte_cls()
{
}

// ---------------------------------Rte Read----------------------------------

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// System initialization
void RE_Rte_cls::rteF_System_Init(enum system_init_et init_e)
{
    switch(init_e)
    {
        case HW_INIT_E:
        {
            rte_hal_cls.halF_init();
            break;
        }
        case HW_SW_INIT_E:
        {
            rte_transceiver_cls.transceiverF_Init();
            rte_lcd_cls.lcdF_Init();
            break;
        }
        case SW_INIT_E:
        {
            rte_buzzer_cls.buzzerF_Init();
            rte_voltage_cls.voltageMonitoringF_Init();
            rte_joystick_cls.joyStickF_init();
            rte_led_cls.ledF_Init();
            rte_poti_cls.potiF_Init();
            rte_switchIn_cls.switchInF_Init();
            rte_menu_cls.menuF_Init();
            break;
        }
        default:
        {
            // no action
            break;
        }
    }
}

// ---------------------------------------------------------------------------
// RE_HAL cyclic
void RE_Rte_cls::rteF_RE_Hal_Cyclic(void)
{
    rte_hal_cls.halF_cyclic();    
}

// ---------------------------------------------------------------------------
// RE_Transceiver cyclic
void RE_Rte_cls::rteF_RE_Transceiver_Cyclic(void)
{
    rte_transceiver_cls.transceiverF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Lcd cyclic
void RE_Rte_cls::rteF_RE_Lcd_Cyclic(void)
{
    rte_lcd_cls.lcdF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Buzzer cyclic
void RE_Rte_cls::rteF_RE_Buzzer_Cyclic(void)
{
    rte_buzzer_cls.buzzerF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_VoltageMonitoring cyclic
void RE_Rte_cls::rteF_RE_VoltageMonitoring_Cyclic(void)
{
    rte_voltage_cls.voltageMonitoringF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_JoyStick cyclic
void RE_Rte_cls::rteF_RE_JoyStick_Cyclic(void)
{
    rte_joystick_cls.joyStickF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Led cyclic
void RE_Rte_cls::rteF_RE_Led_Cyclic(void)
{
    rte_led_cls.ledF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Potentiometer cyclic
void RE_Rte_cls::rteF_RE_Potentiometer_Cyclic(void)
{
    rte_poti_cls.potiF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_SwitchIn cyclic
void RE_Rte_cls::rteF_RE_SwitchIn_Cyclic(void)
{
    rte_switchIn_cls.switchInF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Menu cyclic
void RE_Rte_cls::rteF_RE_Menu_Cyclic(void)
{
    rte_menu_cls.menuF_Cyclic();
}

// ---------------------------------------------------------------------------
uint16_t RE_Rte_cls::Rte_Read_VoltageMonitoring_VoltageInDigit(void)
{
    return(Rte_VoltageInDigit_u16);
}

// ---------------------------------------------------------------------------
float RE_Rte_cls::Rte_Read_VoltageMonitoring_ActualVoltage(void)
{
    return(Rte_ActualVoltage_f);
}

// ---------------------------------------------------------------------------
enum voltage_status_et RE_Rte_cls::Rte_Read_VoltageMonitoring_VoltageStatus(void)
{
    return(Rte_VoltageStatus_e);
}    

// ---------------------------------------------------------------------------
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd(void)
{
    return(Rte_ADC_LeftJoyStick_FwdBckwrd_u16);
}
    
// ---------------------------------------------------------------------------
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_LeftJoyStick_LeftRight(void)
{
    return(Rte_ADC_LeftJoyStick_LeftRight_u16);
}

// ---------------------------------------------------------------------------
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd(void)
{
    return(Rte_ADC_RightJoyStick_FwdBckwrd_u16);
}
    
// ---------------------------------------------------------------------------
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_RightJoyStick_LeftRight(void)
{
    return(Rte_ADC_RightJoyStick_LeftRight_u16);
}

// ---------------------------------------------------------------------------
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_VoltageReading(void)
{
    return(Rte_ADC_VoltageReading_u16);
}
    
// ---------------------------------------------------------------------------
uint16_t RE_Rte_cls::Rte_Read_Hal_ADC_Potentiometer1(void)
{
    return(Rte_ADC_Potentiometer1_u16);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_Hal_DI_Switch1(void)   
{
    return(Rte_DI_Switch1_b);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_Hal_DI_Switch2(void) 
{
    return(Rte_DI_Switch2_b);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_Hal_DI_Switch3(void)
{
    return(Rte_DI_Switch3_b);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_Hal_DI_Switch4(void) 
{
    return(Rte_DI_Switch4_b);
} 

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_Hal_DI_MenuSwitch(void)
{
    return(Rte_DI_MenuSwitch_b);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_Hal_DO_LedIndicator(void)
{
    return(Rte_DO_LedIndicator_b);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_Hal_DO_Buzzer(void)
{
    return(Rte_DO_Buzzer_b);
}

// ---------------------------------------------------------------------------   
uint8_t RE_Rte_cls::Rte_Read_JoyStick_ThrottleFwdBckwrd(void)
{
    return(Rte_JoyStick_ThrottleFwdBckwrd_u8);
}       

// ---------------------------------------------------------------------------  
uint8_t RE_Rte_cls::Rte_Read_JoyStick_ThrottleLeftRight(void)
{
    return(Rte_JoyStick_ThrottleLeftRight_u8);
}

// ---------------------------------------------------------------------------
enum direction_et RE_Rte_cls::Rte_Read_JoyStick_ControlFwdBckwrd(void)  
{
    return(Rte_JoyStick_ControlFwdBckwrd_e);
}

// ---------------------------------------------------------------------------
enum direction_et RE_Rte_cls::Rte_Read_JoyStick_ControlLeftRight(void)
{
    return(Rte_JoyStick_ControlLeftRight_e);
}

// ---------------------------------------------------------------------------
enum mode_et RE_Rte_cls::Rte_Read_JoyStick_ControllerMode(void)
{
    return(Rte_ControllerMode_e);
}

// ---------------------------------------------------------------------------
uint8_t RE_Rte_cls::Rte_Read_Potentiometer_Poti1Data(void)
{
    return(Rte_Potentiometer_Poti1Data_u8);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_Transceiver_Status(void)
{
    return(Rte_Transceiver_Status_b);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_SwitchIn_Switch1(void)
{
    return(Rte_SwitchIn_Switch1_b);
} 

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_SwitchIn_Switch2(void)
{
    return(Rte_SwitchIn_Switch2_b);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_SwitchIn_Switch3(void)
{
    return(Rte_SwitchIn_Switch3_b);
} 

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_SwitchIn_Switch4(void)
{
    return(Rte_SwitchIn_Switch4_b);
}

// ---------------------------------------------------------------------------
bool RE_Rte_cls::Rte_Read_SwitchIn_MenuSwitch(void)
{
    return(Rte_SwitchIn_MenuSwitch_b);
} 

// ---------------------------------------------------------------------------
enum browse_menu_et RE_Rte_cls::Rte_Read_Menu_BrowseMenu(void)   
{
    return(Rte_BrowseMenu_e);
} 

// ---------------------------------------------------------------------------
enum main_menu_et RE_Rte_cls::Rte_Read_Menu_MainMenu(void)
{
    return(Rte_MainMenu_e);
}

// ---------------------------------Rte Write---------------------------------

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_VoltageMonitoring_VoltageInDigit(uint16_t param_u16)
{
    Rte_VoltageInDigit_u16 = param_u16;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_VoltageMonitoring_ActualVoltage(float param_f)
{
    Rte_ActualVoltage_f = param_f;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_VoltageMonitoring_VoltageStatus(enum voltage_status_et  param_e)
{
    Rte_VoltageStatus_e = param_e;
}  

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_ADC_LeftJoyStick_FwdBckwrd(uint16_t param_u16)
{
    Rte_ADC_LeftJoyStick_FwdBckwrd_u16 = param_u16;
}
    
// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_ADC_LeftJoyStick_LeftRight(uint16_t param_u16)
{
    Rte_ADC_LeftJoyStick_LeftRight_u16 = param_u16;
}   

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_ADC_RightJoyStick_FwdBckwrd(uint16_t param_u16)
{
    Rte_ADC_RightJoyStick_FwdBckwrd_u16 = param_u16;
}
    
// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_ADC_RightJoyStick_LeftRight(uint16_t param_u16)
{
    Rte_ADC_RightJoyStick_LeftRight_u16 = param_u16;
} 

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_ADC_VoltageReading(uint16_t param_u16)
{
    Rte_ADC_VoltageReading_u16 = param_u16;
}
    
// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_ADC_Potentiometer1(uint16_t param_u16)
{
    Rte_ADC_Potentiometer1_u16 = param_u16;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_DI_Switch1(bool param_b)  
{
    Rte_DI_Switch1_b = param_b;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_DI_Switch2(bool param_b)
{
    Rte_DI_Switch2_b = param_b;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_DI_Switch3(bool param_b) 
{
    Rte_DI_Switch3_b = param_b;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_DI_Switch4(bool param_b) 
{
    Rte_DI_Switch4_b = param_b;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_DI_MenuSwitch(bool param_b)
{
    Rte_DI_MenuSwitch_b = param_b;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_DO_LedIndicator(bool param_b)
{
    Rte_DO_LedIndicator_b = param_b;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Hal_DO_Buzzer(bool param_b)
{
    Rte_DO_Buzzer_b = param_b;
}

// --------------------------------------------------------------------------- 
void RE_Rte_cls::Rte_Write_JoyStick_ThrottleFwdBckwrd(uint8_t param_u8)      
{
    Rte_JoyStick_ThrottleFwdBckwrd_u8 = param_u8;
}   

// ---------------------------------------------------------------------------  
void RE_Rte_cls::Rte_Write_JoyStick_ThrottleLeftRight(uint8_t param_u8) 
{
    Rte_JoyStick_ThrottleLeftRight_u8 = param_u8;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_JoyStick_ControlFwdBckwrd(enum direction_et param_e)  
{
    Rte_JoyStick_ControlFwdBckwrd_e = param_e;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_JoyStick_ControlLeftRight(enum direction_et param_e)
{
    Rte_JoyStick_ControlLeftRight_e = param_e;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_JoyStick_ControllerMode(enum mode_et param_e)
{
    Rte_ControllerMode_e = param_e;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Potentiometer_Poti1Data(uint8_t param_u8)
{
    Rte_Potentiometer_Poti1Data_u8 = param_u8;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Transceiver_Status(bool param_b)
{
    Rte_Transceiver_Status_b = param_b;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_SwitchIn_Switch1(bool param_b)
{
    Rte_SwitchIn_Switch1_b = param_b;
}

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_SwitchIn_Switch2(bool param_b)
{
    Rte_SwitchIn_Switch2_b = param_b;
} 

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_SwitchIn_Switch3(bool param_b)
{
    Rte_SwitchIn_Switch3_b = param_b;
} 

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_SwitchIn_Switch4(bool param_b)
{
    Rte_SwitchIn_Switch4_b = param_b;
} 

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_SwitchIn_MenuSwitch(bool param_b)
{
    Rte_SwitchIn_MenuSwitch_b = param_b;
} 

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Menu_BrowseMenu(enum browse_menu_et param_e)
{
    Rte_BrowseMenu_e = param_e;
}   

// ---------------------------------------------------------------------------
void RE_Rte_cls::Rte_Write_Menu_MainMenu(enum main_menu_et param_e)
{
    Rte_MainMenu_e = param_e;
}
