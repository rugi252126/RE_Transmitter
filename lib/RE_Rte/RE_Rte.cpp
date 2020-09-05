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
Hal                      rte_hal_ivar;          // from "RE_Hal" module
Transceiver              rte_transceiver_ivar;  // from "RE_Transceiver" module
LcdDisplay               rte_lcd_ivar;          // from "RE_Lcd" module    
Buzzer                   rte_buzzer_ivar;       // from "RE_Buzzer" module              
VoltageMonitoring        rte_voltage_ivar;      // from "RE_VoltageMonitoring" module   
JoyStick                 rte_joystick_ivar;     // from "RE_JoyStick" module            
LedIndicator             rte_led_ivar;          // from "RE_Led" module                 
Poti                     rte_poti_ivar;         // from "RE_Potentiometer" module       
SwitchIn                 rte_switchIn_ivar;     // from "RE_SwitchIn" module            
Menu                     rte_menu_ivar;         // from "RE_Menu" module   
  
// CLASS CONSTRUCTOR
// ---------------------------------------------------------------------------
Rte::Rte()
{
}

// ---------------------------------Rte Read----------------------------------

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// System initialization
void Rte::rteF_System_Init(enum system_init_et init_e)
{
    switch(init_e)
    {
        case HW_INIT_E:
        {
            rte_hal_ivar.halF_init();
            break;
        }
        case HW_SW_INIT_E:
        {
            rte_transceiver_ivar.transceiverF_Init();
            rte_lcd_ivar.lcdF_Init();
            break;
        }
        case SW_INIT_E:
        {
            rte_buzzer_ivar.buzzerF_Init();
            rte_voltage_ivar.voltageMonitoringF_Init();
            rte_joystick_ivar.joyStickF_init();
            rte_led_ivar.ledF_Init();
            rte_poti_ivar.potiF_Init();
            rte_switchIn_ivar.switchInF_Init();
            rte_menu_ivar.menuF_Init();
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
void Rte::rteF_RE_Hal_Cyclic(void)
{
    rte_hal_ivar.halF_cyclic();    
}

// ---------------------------------------------------------------------------
// RE_Transceiver cyclic
void Rte::rteF_RE_Transceiver_Cyclic(void)
{
    rte_transceiver_ivar.transceiverF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Lcd cyclic
void Rte::rteF_RE_Lcd_Cyclic(void)
{
    rte_lcd_ivar.lcdF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Buzzer cyclic
void Rte::rteF_RE_Buzzer_Cyclic(void)
{
    rte_buzzer_ivar.buzzerF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_VoltageMonitoring cyclic
void Rte::rteF_RE_VoltageMonitoring_Cyclic(void)
{
    rte_voltage_ivar.voltageMonitoringF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_JoyStick cyclic
void Rte::rteF_RE_JoyStick_Cyclic(void)
{
    rte_joystick_ivar.joyStickF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Led cyclic
void Rte::rteF_RE_Led_Cyclic(void)
{
    rte_led_ivar.ledF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Potentiometer cyclic
void Rte::rteF_RE_Potentiometer_Cyclic(void)
{
    rte_poti_ivar.potiF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_SwitchIn cyclic
void Rte::rteF_RE_SwitchIn_Cyclic(void)
{
    rte_switchIn_ivar.switchInF_Cyclic();
}

// ---------------------------------------------------------------------------
// RE_Menu cyclic
void Rte::rteF_RE_Menu_Cyclic(void)
{
    rte_menu_ivar.menuF_Cyclic();
}

// ---------------------------------------------------------------------------
uint16_t Rte::Rte_Read_VoltageMonitoring_VoltageInDigit(void)
{
    return(Rte_VoltageInDigit_);
}

// ---------------------------------------------------------------------------
float Rte::Rte_Read_VoltageMonitoring_ActualVoltage(void)
{
    return(Rte_ActualVoltage_f_);
}

// ---------------------------------------------------------------------------
enum voltage_status_et Rte::Rte_Read_VoltageMonitoring_VoltageStatus(void)
{
    return(Rte_VoltageStatus_e_);
}    

// ---------------------------------------------------------------------------
uint16_t Rte::Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd(void)
{
    return(Rte_ADC_LeftJoyStick_FwdBckwrd_);
}
    
// ---------------------------------------------------------------------------
uint16_t Rte::Rte_Read_Hal_ADC_LeftJoyStick_LeftRight(void)
{
    return(Rte_ADC_LeftJoyStick_LeftRight_);
}

// ---------------------------------------------------------------------------
uint16_t Rte::Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd(void)
{
    return(Rte_ADC_RightJoyStick_FwdBckwrd_);
}
    
// ---------------------------------------------------------------------------
uint16_t Rte::Rte_Read_Hal_ADC_RightJoyStick_LeftRight(void)
{
    return(Rte_ADC_RightJoyStick_LeftRight_);
}

// ---------------------------------------------------------------------------
uint16_t Rte::Rte_Read_Hal_ADC_VoltageReading(void)
{
    return(Rte_ADC_VoltageReading_);
}
    
// ---------------------------------------------------------------------------
uint16_t Rte::Rte_Read_Hal_ADC_Potentiometer1(void)
{
    return(Rte_ADC_Potentiometer1_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_Hal_DI_Switch1(void)   
{
    return(Rte_DI_Switch1_b_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_Hal_DI_Switch2(void) 
{
    return(Rte_DI_Switch2_b_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_Hal_DI_Switch3(void)
{
    return(Rte_DI_Switch3_b_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_Hal_DI_Switch4(void) 
{
    return(Rte_DI_Switch4_b_);
} 

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_Hal_DI_MenuSwitch(void)
{
    return(Rte_DI_MenuSwitch_b_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_Hal_DO_LedIndicator(void)
{
    return(Rte_DO_LedIndicator_b_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_Hal_DO_Buzzer(void)
{
    return(Rte_DO_Buzzer_b_);
}

// ---------------------------------------------------------------------------   
uint8_t Rte::Rte_Read_JoyStick_ThrottleFwdBckwrd(void)
{
    return(Rte_JoyStick_ThrottleFwdBckwrd_);
}       

// ---------------------------------------------------------------------------  
uint8_t Rte::Rte_Read_JoyStick_ThrottleLeftRight(void)
{
    return(Rte_JoyStick_ThrottleLeftRight_);
}

// ---------------------------------------------------------------------------
enum direction_et Rte::Rte_Read_JoyStick_ControlFwdBckwrd(void)  
{
    return(Rte_JoyStick_ControlFwdBckwrd_e_);
}

// ---------------------------------------------------------------------------
enum direction_et Rte::Rte_Read_JoyStick_ControlLeftRight(void)
{
    return(Rte_JoyStick_ControlLeftRight_e_);
}

// ---------------------------------------------------------------------------
enum mode_et Rte::Rte_Read_JoyStick_ControllerMode(void)
{
    return(Rte_ControllerMode_e_);
}

// ---------------------------------------------------------------------------
uint8_t Rte::Rte_Read_Potentiometer_Poti1Data(void)
{
    return(Rte_Potentiometer_Poti1Data_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_Transceiver_Status(void)
{
    return(Rte_Transceiver_Status_b_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_SwitchIn_Switch1(void)
{
    return(Rte_SwitchIn_Switch1_b_);
} 

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_SwitchIn_Switch2(void)
{
    return(Rte_SwitchIn_Switch2_b_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_SwitchIn_Switch3(void)
{
    return(Rte_SwitchIn_Switch3_b_);
} 

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_SwitchIn_Switch4(void)
{
    return(Rte_SwitchIn_Switch4_b_);
}

// ---------------------------------------------------------------------------
bool Rte::Rte_Read_SwitchIn_MenuSwitch(void)
{
    return(Rte_SwitchIn_MenuSwitch_b_);
} 

// ---------------------------------------------------------------------------
enum browse_menu_et Rte::Rte_Read_Menu_BrowseMenu(void)   
{
    return(Rte_BrowseMenu_e_);
} 

// ---------------------------------------------------------------------------
enum main_menu_et Rte::Rte_Read_Menu_MainMenu(void)
{
    return(Rte_MainMenu_e_);
}

// ---------------------------------Rte Write---------------------------------

// ---------------------------------------------------------------------------
void Rte::Rte_Write_VoltageMonitoring_VoltageInDigit(uint16_t param_u16)
{
    Rte_VoltageInDigit_ = param_u16;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_VoltageMonitoring_ActualVoltage(float param_f)
{
    Rte_ActualVoltage_f_ = param_f;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_VoltageMonitoring_VoltageStatus(enum voltage_status_et  param_e)
{
    Rte_VoltageStatus_e_ = param_e;
}  

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_ADC_LeftJoyStick_FwdBckwrd(uint16_t param_u16)
{
    Rte_ADC_LeftJoyStick_FwdBckwrd_ = param_u16;
}
    
// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_ADC_LeftJoyStick_LeftRight(uint16_t param_u16)
{
    Rte_ADC_LeftJoyStick_LeftRight_ = param_u16;
}   

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_ADC_RightJoyStick_FwdBckwrd(uint16_t param_u16)
{
    Rte_ADC_RightJoyStick_FwdBckwrd_= param_u16;
}
    
// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_ADC_RightJoyStick_LeftRight(uint16_t param_u16)
{
    Rte_ADC_RightJoyStick_LeftRight_ = param_u16;
} 

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_ADC_VoltageReading(uint16_t param_u16)
{
    Rte_ADC_VoltageReading_ = param_u16;
}
    
// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_ADC_Potentiometer1(uint16_t param_u16)
{
    Rte_ADC_Potentiometer1_ = param_u16;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_DI_Switch1(bool param_b)  
{
    Rte_DI_Switch1_b_ = param_b;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_DI_Switch2(bool param_b)
{
    Rte_DI_Switch2_b_ = param_b;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_DI_Switch3(bool param_b) 
{
    Rte_DI_Switch3_b_ = param_b;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_DI_Switch4(bool param_b) 
{
    Rte_DI_Switch4_b_ = param_b;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_DI_MenuSwitch(bool param_b)
{
    Rte_DI_MenuSwitch_b_ = param_b;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_DO_LedIndicator(bool param_b)
{
    Rte_DO_LedIndicator_b_ = param_b;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Hal_DO_Buzzer(bool param_b)
{
    Rte_DO_Buzzer_b_ = param_b;
}

// --------------------------------------------------------------------------- 
void Rte::Rte_Write_JoyStick_ThrottleFwdBckwrd(uint8_t param_u8)      
{
    Rte_JoyStick_ThrottleFwdBckwrd_ = param_u8;
}   

// ---------------------------------------------------------------------------  
void Rte::Rte_Write_JoyStick_ThrottleLeftRight(uint8_t param_u8) 
{
    Rte_JoyStick_ThrottleLeftRight_ = param_u8;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_JoyStick_ControlFwdBckwrd(enum direction_et param_e)  
{
    Rte_JoyStick_ControlFwdBckwrd_e_ = param_e;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_JoyStick_ControlLeftRight(enum direction_et param_e)
{
    Rte_JoyStick_ControlLeftRight_e_ = param_e;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_JoyStick_ControllerMode(enum mode_et param_e)
{
    Rte_ControllerMode_e_ = param_e;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Potentiometer_Poti1Data(uint8_t param_u8)
{
    Rte_Potentiometer_Poti1Data_ = param_u8;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Transceiver_Status(bool param_b)
{
    Rte_Transceiver_Status_b_ = param_b;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_SwitchIn_Switch1(bool param_b)
{
    Rte_SwitchIn_Switch1_b_ = param_b;
}

// ---------------------------------------------------------------------------
void Rte::Rte_Write_SwitchIn_Switch2(bool param_b)
{
    Rte_SwitchIn_Switch2_b_ = param_b;
} 

// ---------------------------------------------------------------------------
void Rte::Rte_Write_SwitchIn_Switch3(bool param_b)
{
    Rte_SwitchIn_Switch3_b_ = param_b;
} 

// ---------------------------------------------------------------------------
void Rte::Rte_Write_SwitchIn_Switch4(bool param_b)
{
    Rte_SwitchIn_Switch4_b_ = param_b;
} 

// ---------------------------------------------------------------------------
void Rte::Rte_Write_SwitchIn_MenuSwitch(bool param_b)
{
    Rte_SwitchIn_MenuSwitch_b_ = param_b;
} 

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Menu_BrowseMenu(enum browse_menu_et param_e)
{
    Rte_BrowseMenu_e_ = param_e;
}   

// ---------------------------------------------------------------------------
void Rte::Rte_Write_Menu_MainMenu(enum main_menu_et param_e)
{
    Rte_MainMenu_e_ = param_e;
}
