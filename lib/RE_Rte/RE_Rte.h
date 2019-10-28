#ifndef RE_RTE_H_
#define RE_RTE_H_

#include "Arduino.h"
//#include "RE_Hal.h"
//#include "RE_VoltageMonitoring.h"
//#include "RE_JoyStick.h"
//#include "RE_Menu.h"

enum voltage_status_et
{
     VOLT_NORMAL_E       = 0
    ,VOLT_LOW_E          = 1
    ,VOLT_LOW_CRITICAL_E = 2	
};

enum digitalPortState_et
{
	 HAL_IO_LOW_E  = 0
	,HAL_IO_HIGH_E = 1
};

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

enum main_menu_et
{
     MENU_MAIN_OPTIONS_E
    ,MENU_MAIN_MODE_E
};

enum browse_menu_et
{
     MENU_DISPLAY_GENERAL_INFO_E   = 0 // connection, controller mode
    ,MENU_DISPLAY_VOLTAGE_INFO_E   = 1 // voltage and its status(normal, low voltage, critical low voltage)
    ,MENU_DISPLAY_JOYSTICK_INFO_E  = 2 // throttle and control info
    ,MENU_DISPLAY_SWITCH_INFO_E    = 3 // switch 1 to 4 info
    ,MENU_DISPLAY_POTI_INFO_E      = 4 // potentiometer info
    ,MENU_SW_HW_VERSION_E          = 5 // SW and HW Version. Format(YY/CW/PL) YY -> Year, CW -> Calendar Week, PL -> Path Level (e.g. 19/38/00)
    ,MENU_DISPLAY_CONTROLLER_TYPE_E= 6 // robot, drone, plane, boat, car, etc..(default: robot)
    ,MENU_DISPLAY_MAX_E
};

class RE_Rte_cls
{
public:

    /*
     */
    RE_Rte_cls();

    /*************** start -> RTE READ ***************/
    /*
     */
    uint16_t Rte_Read_VoltageMonitoring_VoltageInDigit(void);

    /*
     */
    float Rte_Read_VoltageMonitoring_ActualVoltage(void);

    /*
     */
    enum voltage_status_et Rte_Read_VoltageMonitoring_VoltageStatus(void);       

    /*
     */
    enum digitalPortState_et Rte_Read_Buzzer_PortState(void);   

    /*
     */
    uint16_t Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd(void);
    
    /*
     */
    uint16_t Rte_Read_Hal_ADC_LeftJoyStick_LeftRight(void);    

     /*
     */
    uint16_t Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd(void);
    
    /*
     */
    uint16_t Rte_Read_Hal_ADC_RightJoyStick_LeftRight(void);       

     /*
     */
    uint16_t Rte_Read_Hal_ADC_VoltageReading(void);
    
    /*
     */
    uint16_t Rte_Read_Hal_ADC_Potentiometer1(void);

     /*
     */
    bool Rte_Read_Hal_DI_Switch1(void);    

     /*
     */
    bool Rte_Read_Hal_DI_Switch2(void);  

     /*
     */
    bool Rte_Read_Hal_DI_Switch3(void);  

    /*
     */
    bool Rte_Read_Hal_DI_Switch4(void);  

     /*
     */
    bool Rte_Read_Hal_DI_MenuSwitch(void); 

     /*
     */
    bool Rte_Read_Hal_DO_LedIndicator(void); 

     /*
     */
    bool Rte_Read_Hal_DO_Buzzer(void);     

    /*
     */   
    uint8_t Rte_Read_JoyStick_ThrottleFwdBckwrd(void);         

    /*
     */   
    uint8_t Rte_Read_JoyStick_ThrottleLeftRight(void);  

    /*
     */
    enum direction_et Rte_Read_JoyStick_ControlFwdBckwrd(void);  

    /*
     */
    enum direction_et Rte_Read_JoyStick_ControlLeftRight(void);

    /*
     */
    enum mode_et Rte_Read_JoyStick_ControllerMode(void);   

    /*
     */
    uint8_t Rte_Read_Potentiometer_Poti1Data(void);   

    /*
     */
    bool Rte_Read_Transceiver_Status(void); 

    /*
     */
    bool Rte_Read_SwitchIn_Switch1(void);  

    /*
     */
    bool Rte_Read_SwitchIn_Switch2(void);  

    /*
     */
    bool Rte_Read_SwitchIn_Switch3(void);  

    /*
     */
    bool Rte_Read_SwitchIn_Switch4(void);  

    /*
     */
    bool Rte_Read_SwitchIn_MenuSwitch(void);   

    /*
     */
    enum browse_menu_et Rte_Read_Menu_BrowseMenu(void);    

    /*
     */
    enum main_menu_et Rte_Read_Menu_MainMenu(void);                               
    /*************** end   -> RTE READ ***************/

    /**************************************************/
    /*************** start -> RTE WRITE ***************/
    void Rte_Write_VoltageMonitoring_VoltageInDigit(uint16_t param_u16);   

    /*
     */
    void Rte_Write_VoltageMonitoring_ActualVoltage(float param_f);

    /*
     */
    void Rte_Write_VoltageMonitoring_VoltageStatus(enum voltage_status_et  param_e);   
    
    /*
     */
    void Rte_Write_Buzzer_PortState(enum digitalPortState_et  param_e);     

    /*
     */
    void Rte_Write_Hal_ADC_LeftJoyStick_FwdBckwrd(uint16_t param_u16);
    
    /*
     */
    void Rte_Write_Hal_ADC_LeftJoyStick_LeftRight(uint16_t param_u16);    

     /*
     */
    void Rte_Write_Hal_ADC_RightJoyStick_FwdBckwrd(uint16_t param_u16);
    
    /*
     */
    void Rte_Write_Hal_ADC_RightJoyStick_LeftRight(uint16_t param_u16);  

     /*
     */
    void Rte_Write_Hal_ADC_VoltageReading(uint16_t param_u16);
    
    /*
     */
    void Rte_Write_Hal_ADC_Potentiometer1(uint16_t param_u16); 

     /*
     */
    void Rte_Write_Hal_DI_Switch1(bool param_b);    

     /*
     */
    void Rte_Write_Hal_DI_Switch2(bool param_b);  

     /*
     */
    void Rte_Write_Hal_DI_Switch3(bool param_b);  

    /*
     */
    void Rte_Write_Hal_DI_Switch4(bool param_b);  

     /*
     */
    void Rte_Write_Hal_DI_MenuSwitch(bool param_b); 

     /*
     */
    void Rte_Write_Hal_DO_LedIndicator(bool param_b); 

     /*
     */
    void Rte_Write_Hal_DO_Buzzer(bool param_b); 

    /*
     */   
    void Rte_Write_JoyStick_ThrottleFwdBckwrd(uint8_t param_u8);         

    /*
     */   
    void Rte_Write_JoyStick_ThrottleLeftRight(uint8_t param_u8);  

    /*
     */
    void Rte_Write_JoyStick_ControlFwdBckwrd(enum direction_et param_e);  

    /*
     */
    void Rte_Write_JoyStick_ControlLeftRight(enum direction_et param_e);

    /*
     */
    void Rte_Write_JoyStick_ControllerMode(enum mode_et param_e);    

    /*
     */
    void Rte_Write_Potentiometer_Poti1Data(uint8_t param_u8);   

    /*
     */
    void Rte_Write_Transceiver_Status(bool param_b);   

    /*
     */
    void Rte_Write_SwitchIn_Switch1(bool param_b);  

    /*
     */
    void Rte_Write_SwitchIn_Switch2(bool param_b);  

    /*
     */
    void Rte_Write_SwitchIn_Switch3(bool param_b);  

    /*
     */
    void Rte_Write_SwitchIn_Switch4(bool param_b);  

    /*
     */
    void Rte_Write_SwitchIn_MenuSwitch(bool param_b);  

    /*
     */
    void Rte_Write_Menu_BrowseMenu(enum browse_menu_et param_e);    

    /*
     */
    void Rte_Write_Menu_MainMenu(enum main_menu_et param_e);                                   
    /*************** end   -> RTE WRITE ***************/ 

    /*
     */
    void rteF_Init(void);

    /*
     */
    void rteF_Cyclic(void);

protected:
    bool                        Rte_DI_Switch1_b;
    bool                        Rte_DI_Switch2_b;
    bool                        Rte_DI_Switch3_b;
    bool                        Rte_DI_Switch4_b;
    bool                        Rte_DI_MenuSwitch_b;
    bool                        Rte_DO_LedIndicator_b;
    bool                        Rte_DO_Buzzer_b; 
    bool                        Rte_Transceiver_Status_b;
    bool                        Rte_SwitchIn_Switch1_b;   
    bool                        Rte_SwitchIn_Switch2_b; 
    bool                        Rte_SwitchIn_Switch3_b; 
    bool                        Rte_SwitchIn_Switch4_b; 
    bool                        Rte_SwitchIn_MenuSwitch_b;                   
    uint8_t                     Rte_Potentiometer_Poti1Data_u8;
    uint8_t                     Rte_JoyStick_ThrottleFwdBckwrd_u8;
    uint8_t                     Rte_JoyStick_ThrottleLeftRight_u8;
    uint16_t                    Rte_VoltageInDigit_u16;
    uint16_t                    Rte_ADC_LeftJoyStick_FwdBckwrd_u16;
    uint16_t                    Rte_ADC_LeftJoyStick_LeftRight_u16;
    uint16_t                    Rte_ADC_RightJoyStick_FwdBckwrd_u16;
    uint16_t                    Rte_ADC_RightJoyStick_LeftRight_u16;    
    uint16_t                    Rte_ADC_VoltageReading_u16;
    uint16_t                    Rte_ADC_Potentiometer1_u16;      
    float                       Rte_ActualVoltage_f;
    enum voltage_status_et      Rte_VoltageStatus_e;
    enum digitalPortState_et    Rte_BuzzerDO_PortState_e;
    enum direction_et           Rte_JoyStick_ControlFwdBckwrd_e;
    enum direction_et           Rte_JoyStick_ControlLeftRight_e;
    enum mode_et                Rte_ControllerMode_e;
    enum browse_menu_et         Rte_BrowseMenu_e;
    enum main_menu_et           Rte_MainMenu_e;
    

private:
   
    /*
     */

};

extern RE_Rte_cls    Rte_cls;

#endif // RE_RTE_H_