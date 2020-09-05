/**
    @file RE_Rte.h

    @brief
    Handles the interfaces between modules.
    Main purpose, it serves as medium between upper layer and lower layer.
    With this approach, portability, maintainability and adaptability of different modules is easy.

    @author Alfonso, Rudy Manalo
    @version
*/

#ifndef RE_RTE_H_
#define RE_RTE_H_

#include "Arduino.h"


/*!
    @defined 
    @abstract Voltage status
    @discussion Defines different voltage status
*/
enum voltage_status_et
{
     VOLT_NORMAL_E       = 0
    ,VOLT_LOW_E          = 1
    ,VOLT_LOW_CRITICAL_E = 2	
};

/*!
    @defined 
    @abstract Digital IO port states
    @discussion Defines different digital IO port states
*/
enum digitalPortState_et
{
     HAL_IO_LOW_E  = 0
    ,HAL_IO_HIGH_E = 1
};

/*!
    @defined 
    @abstract Controller modes
    @discussion Defines different controller modes
*/
enum mode_et
{
     MODE2_E = 0 // default mode. left hand throttle
    ,MODE1_E = 1
};

/*!
    @defined 
    @abstract Joystick directions
    @discussion Defines different joystick directions
*/
enum direction_et
{
     JS_OFF_E        = 0
    ,JS_FORWARD_E    = 1
    ,JS_BACKWARD_E   = 2
    ,JS_LEFT_TURN_E  = 3
    ,JS_RIGHT_TURN_E = 4
};

/*!
    @defined 
    @abstract Main menu settings
    @discussion Defines main menu configurations
*/
enum main_menu_et
{
     MENU_MAIN_OPTIONS_E
    ,MENU_MAIN_MODE_E
};

/*!
    @defined 
    @abstract Browse menu
    @discussion Defines browse menu information
*/
enum browse_menu_et
{
     MENU_DISPLAY_GENERAL_INFO_E        = 0 // connection, controller mode
    ,MENU_DISPLAY_VOLTAGE_INFO_E        = 1 // voltage and its status(normal, low voltage, critical low voltage)
    ,MENU_DISPLAY_JOYSTICK_INFO_E       = 2 // throttle and control info
    ,MENU_DISPLAY_SWITCH_INFO_E         = 3 // switch 1 to 4 info
    ,MENU_DISPLAY_POTI_INFO_E           = 4 // potentiometer info
    ,MENU_DISPLAY_LOGISTIC_DATA_INFO_E  = 5 // SW and HW Version. Format(YY/CW/PL) YY -> Year, CW -> Calendar Week, PL -> Path Level (e.g. 19/38/00)
    ,MENU_DISPLAY_CONTROLLED_OBJ_INFO_E = 6 // robot, drone, plane, rc boat, rc car, etc..(default: robot)
    ,MENU_DISPLAY_MAX_E
};

/*!
    @defined 
    @abstract System initialization
    @discussion Defines system initialization category
*/
enum system_init_et
{
     HW_INIT_E     = 0  // hardware related initialization
    ,HW_SW_INIT_E       // hardware and software related initialization
    ,SW_INIT_E          // software related initialization
};

class Rte
{
public:

    /*!
        @method
        @abstract RE_Rte abstract constructor
        @discussion RE_Rte class abstract constructor needed to create the abstract base class.
    */
    Rte();

    /*!
        @function
        @abstract System initialization
        @discussion System initialization

        @param  init_e {[see enum system_init_et] init category}
        @return none
    */
    void rteF_System_Init(enum system_init_et init_e);

    /*!
        @function
        @abstract RE_Hal cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_Hal_Cyclic(void);    

    /*!
        @function
        @abstract RE_Transceiver cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_Transceiver_Cyclic(void); 

    /*!
        @function
        @abstract RE_Lcd cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_Lcd_Cyclic(void);  

    /*!
        @function
        @abstract RE_Buzzer cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_Buzzer_Cyclic(void);             

    /*!
        @function
        @abstract RE_VoltageMonitoring cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_VoltageMonitoring_Cyclic(void); 

    /*!
        @function
        @abstract RE_JotStick cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_JoyStick_Cyclic(void);  

    /*!
        @function
        @abstract RE_Led cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_Led_Cyclic(void);      

    /*!
        @function
        @abstract RE_Potentiometer cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_Potentiometer_Cyclic(void);    

    /*!
        @function
        @abstract RE_SwitchIn cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_SwitchIn_Cyclic(void);       

    /*!
        @function
        @abstract RE_Menu cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
    */
    void rteF_RE_Menu_Cyclic(void);          

    /*!
        @function
        @abstract Module cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
	*/
    //void rteF_Cyclic(void);    

    // ---------------------------------Rte Read----------------------------------

    /*!
        @function
        @abstract Voltage in digit form
        @discussion Returns back the battery voltage in digit form(e.g. 7.5V = 750 in digit)

        @param  none
        @return {[0..depends on ADC-resolution] battery voltage in digit form}
    */
    uint16_t Rte_Read_VoltageMonitoring_VoltageInDigit(void);

    /*!
        @function
        @abstract Actual battery voltage
        @discussion Returns back the actual battery voltage(e.g. 7.5V)

        @param  none
        @return {[0..25V(also depends on the voltage divided used in the design)] actual battery voltage}
    */
    float Rte_Read_VoltageMonitoring_ActualVoltage(void);

    /*!
        @function
        @abstract Voltage status
        @discussion Returns back the voltage status

        @param  none
        @return {[see enum voltage_status_et] voltage status}
    */
    enum voltage_status_et Rte_Read_VoltageMonitoring_VoltageStatus(void);       

    /*!
        @function
        @abstract Buzzer port control state
        @discussion Returns back the port state of the buzzer control

        @param  none
        @return {[see enum digitalPortState_et] buzzer port control state}
    */
    //enum digitalPortState_et Rte_Read_Buzzer_PortState(void);   

    /*!
        @function
        @abstract Left Joystick Forward/Backward ADC value
        @discussion Returns back the left joystick Forward/Backward ADC value

        @param  none
        @return {[0..ADC-resolution] ADC value}
    */
    uint16_t Rte_Read_Hal_ADC_LeftJoyStick_FwdBckwrd(void);
    
    /*!
        @function
        @abstract Left Joystick Left/Right ADC value
        @discussion Returns back the left joystick Left/Right ADC value

        @param  none
        @return {[0..ADC-resolution] ADC value}
    */
    uint16_t Rte_Read_Hal_ADC_LeftJoyStick_LeftRight(void);    

    /*!
        @function
        @abstract Right Joystick Forward/Backward ADC value
        @discussion Returns back the right joystick Forward/Backward ADC value

        @param  none
        @return {[0..ADC-resolution] ADC value}
    */
    uint16_t Rte_Read_Hal_ADC_RightJoyStick_FwdBckwrd(void);
    
    /*!
        @function
        @abstract Right Joystick Left/Right ADC value
        @discussion Returns back the right joystick Left/Right ADC value

        @param  none
        @return {[0..ADC-resolution] ADC value}
    */
    uint16_t Rte_Read_Hal_ADC_RightJoyStick_LeftRight(void);       

    /*!
        @function
        @abstract Battery voltage ADC value
        @discussion Returns back the battery voltage ADC value

        @param  none
        @return {[0..ADC-resolution] ADC value}
    */
    uint16_t Rte_Read_Hal_ADC_VoltageReading(void);
    
    /*!
        @function
        @abstract Potentiometer ADC value
        @discussion Returns back the potentiometer ADC value

        @param  none
        @return {[0..ADC-resolution] ADC value}
    */
    uint16_t Rte_Read_Hal_ADC_Potentiometer1(void);

    /*!
        @function
        @abstract Switch1 state
        @discussion Returns back the switch1 state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_Hal_DI_Switch1(void);    

    /*!
        @function
        @abstract Switch2 state
        @discussion Returns back the switch2 state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_Hal_DI_Switch2(void);  

    /*!
        @function
        @abstract Switch3 state
        @discussion Returns back the switch3 state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_Hal_DI_Switch3(void);  

    /*!
        @function
        @abstract Switch4 state
        @discussion Returns back the switch4 state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_Hal_DI_Switch4(void);  

    /*!
        @function
        @abstract Menu switch state
        @discussion Returns back the menu switch state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_Hal_DI_MenuSwitch(void); 

    /*!
        @function
        @abstract LED port state
        @discussion Returns back the LED port state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_Hal_DO_LedIndicator(void); 

    /*!
        @function
        @abstract Buzzer port state
        @discussion Returns back the Buzzer port state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_Hal_DO_Buzzer(void);     

    /*!
        @function
        @abstract Joystick throttle forward/backward
        @discussion Returns back the joystick throttle forward/backward

        @param  none
        @return {[0..255] pwm}
    */ 
    uint8_t Rte_Read_JoyStick_ThrottleFwdBckwrd(void);         

    /*!
        @function
        @abstract Joystick throttle left/right
        @discussion Returns back the joystick throttle left/right

        @param  none
        @return {[0..255] pwm}
    */   
    uint8_t Rte_Read_JoyStick_ThrottleLeftRight(void);  

    /*!
        @function
        @abstract Joystick direction forward/backward
        @discussion Returns back the joystick direction forward/backward

        @param  none
        @return {[see direction_et] direction}
    */ 
    enum direction_et Rte_Read_JoyStick_ControlFwdBckwrd(void);  

    /*!
        @function
        @abstract Joystick direction left/right
        @discussion Returns back the joystick direction left/right

        @param  none
        @return {[see direction_et] direction}
    */ 
    enum direction_et Rte_Read_JoyStick_ControlLeftRight(void);

    /*!
        @function
        @abstract Controller mode
        @discussion Returns back the joystick controller mode

        @param  none
        @return {[see mode_et] controller mode}
    */
    enum mode_et Rte_Read_JoyStick_ControllerMode(void);   

    /*!
        @function
        @abstract Potentiometer1 pwm 
        @discussion Returns back the potentiometer1 pwm

        @param  none
        @return {[0..255] pwm}
    */ 
    uint8_t Rte_Read_Potentiometer_Poti1Data(void);   

    /*!
        @function
        @abstract Transceiver status
        @discussion Returns back the transceiver status(0/false=not connected; 1/true=connected)

        @param  none
        @return {[0..1] status}
    */ 
    bool Rte_Read_Transceiver_Status(void); 

    /*!
        @function
        @abstract Switch1 state
        @discussion Returns back the switch1 state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_SwitchIn_Switch1(void);  

    /*!
        @function
        @abstract Switch2 state
        @discussion Returns back the switch2 state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_SwitchIn_Switch2(void);  

    /*!
        @function
        @abstract Switch3 state
        @discussion Returns back the switch3 state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_SwitchIn_Switch3(void);  

    /*!
        @function
        @abstract Switch4 state
        @discussion Returns back the switch4 state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_SwitchIn_Switch4(void);  

    /*!
        @function
        @abstract Menu switch state
        @discussion Returns back the menu switch state(0=OFF/LOW; 1=ON/HIGH)

        @param  none
        @return {[0..1] state}
    */
    bool Rte_Read_SwitchIn_MenuSwitch(void);   

    /*!
        @function
        @abstract Browse menu
        @discussion Returns back which information is being browsed

        @param  none
        @return {[see enumbrowse_menu_et] browse menu}
    */
    enum browse_menu_et Rte_Read_Menu_BrowseMenu(void);    

    /*!
        @function
        @abstract Main menu
        @discussion Returns back which settings/configuration is being selected

        @param  none
        @return {[see main_menu_et] main menu}
    */
    enum main_menu_et Rte_Read_Menu_MainMenu(void);                               

    // ---------------------------------Rte Write---------------------------------

    /*!
        @function
        @abstract Voltage in digit form
        @discussion Update the battery voltage in digit form(e.g. 7.5V = 750 in digit)

        @param  param_u16 {[0..depends on ADC-resolution] battery voltage in digit form}
        @return none
    */
    void Rte_Write_VoltageMonitoring_VoltageInDigit(uint16_t param_u16);   

    /*!
        @function
        @abstract Actual battery voltage
        @discussion Update the actual battery voltage(e.g. 7.5V)

        @param  param_f {[0..25V(also depends on the voltage divided used in the design)] actual battery voltage}
        @return none
    */
    void Rte_Write_VoltageMonitoring_ActualVoltage(float param_f);

    /*!
        @function
        @abstract Voltage status
        @discussion Update the voltage status

        @param  param_e {[see enum voltage_status_et] voltage status}
        @return none
    */
    void Rte_Write_VoltageMonitoring_VoltageStatus(enum voltage_status_et  param_e);   
    
    /*!
        @function
        @abstract Buzzer port control state
        @discussion Update the port state of the buzzer control

        @param  param_e {[see enum digitalPortState_et] buzzer port control state}
        @return none
    */
    //void Rte_Write_Buzzer_PortState(enum digitalPortState_et  param_e);     

    /*!
        @function
        @abstract Left Joystick Forward/Backward ADC value
        @discussion Update the left joystick Forward/Backward ADC value

        @param  param_u16 {[0..ADC-resolution] ADC value}
        @return none
    */
    void Rte_Write_Hal_ADC_LeftJoyStick_FwdBckwrd(uint16_t param_u16);
    
    /*!
        @function
        @abstract Left Joystick Left/Right ADC value
        @discussion Update the left joystick Left/Right ADC value

        @param  param_u16 {[0..ADC-resolution] ADC value}
        @return none
    */
    void Rte_Write_Hal_ADC_LeftJoyStick_LeftRight(uint16_t param_u16);    

    /*!
        @function
        @abstract Right Joystick Forward/Backward ADC value
        @discussion Update the right joystick Forward/Backward ADC value

        @param  param_u16 {[0..ADC-resolution] ADC value}
        @return none
    */
    void Rte_Write_Hal_ADC_RightJoyStick_FwdBckwrd(uint16_t param_u16);
    
    /*!
        @function
        @abstract Right Joystick Left/Right ADC value
        @discussion Update the right joystick Left/Right ADC value

        @param  param_u16 {[0..ADC-resolution] ADC value}
        @return none
    */
    void Rte_Write_Hal_ADC_RightJoyStick_LeftRight(uint16_t param_u16);  

    /*!
        @function
        @abstract Battery voltage ADC value
        @discussion Update the battery voltage ADC value

        @param  param_u16 {[0..ADC-resolution] ADC value}
        @return none
    */
    void Rte_Write_Hal_ADC_VoltageReading(uint16_t param_u16);
    
    /*!
        @function
        @abstract Potentiometer ADC value
        @discussion Update the potentiometer ADC value

        @param  param_u16 {[0..ADC-resolution] ADC value}
        @return none
    */
    void Rte_Write_Hal_ADC_Potentiometer1(uint16_t param_u16); 

    /*!
        @function
        @abstract Switch1 state
        @discussion Update the switch1 state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_Hal_DI_Switch1(bool param_b);    

    /*!
        @function
        @abstract Switch2 state
        @discussion Update the switch2 state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_Hal_DI_Switch2(bool param_b);  

    /*!
        @function
        @abstract Switch3 state
        @discussion Update the switch3 state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_Hal_DI_Switch3(bool param_b);  

    /*!
        @function
        @abstract Switch4 state
        @discussion Update the switch4 state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_Hal_DI_Switch4(bool param_b);  

    /*!
        @function
        @abstract Menu switch state
        @discussion Update the menu switch state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_Hal_DI_MenuSwitch(bool param_b); 

    /*!
        @function
        @abstract LED port state
        @discussion Update the LED port state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_Hal_DO_LedIndicator(bool param_b); 

    /*!
        @function
        @abstract Buzzer port state
        @discussion update the Buzzer port state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_Hal_DO_Buzzer(bool param_b); 

    /*!
        @function
        @abstract Joystick throttle forward/backward
        @discussion Update the joystick throttle forward/backward

        @param  param_u8 {[0..255] pwm}
        @return none
    */   
    void Rte_Write_JoyStick_ThrottleFwdBckwrd(uint8_t param_u8);         

    /*!
        @function
        @abstract Joystick throttle left/right
        @discussion Update the joystick throttle left/right

        @param  param_u8 {[0..255] pwm}
        @return none
    */  
    void Rte_Write_JoyStick_ThrottleLeftRight(uint8_t param_u8);  

    /*!
        @function
        @abstract Joystick direction forward/backward
        @discussion Update the joystick direction forward/backward

        @param  param_e {[see direction_et] direction}
        @return none
    */ 
    void Rte_Write_JoyStick_ControlFwdBckwrd(enum direction_et param_e);  

    /*!
        @function
        @abstract Joystick direction left/right
        @discussion Update the joystick direction left/right

        @param  param_e {[see direction_et] direction}
        @return none
    */ 
    void Rte_Write_JoyStick_ControlLeftRight(enum direction_et param_e);

    /*!
        @function
        @abstract Controller mode
        @discussion Update the joystick controller mode

        @param  param_e {[see mode_et] controller mode}
        @return none
    */
    void Rte_Write_JoyStick_ControllerMode(enum mode_et param_e);    

    /*!
        @function
        @abstract Potentiometer1 pwm 
        @discussion Update the potentiometer1 pwm

        @param  param_u8 {[0..255] pwm}
        @return none
    */ 
    void Rte_Write_Potentiometer_Poti1Data(uint8_t param_u8);   

    /*!
        @function
        @abstract Transceiver status
        @discussion Update the transceiver status(0/false=not connected; 1/true=connected)

        @param  param_b {[0..1] status}
        @return none
    */
    void Rte_Write_Transceiver_Status(bool param_b);   

    /*!
        @function
        @abstract Switch1 state
        @discussion update the switch1 state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_SwitchIn_Switch1(bool param_b);  

    /*!
        @function
        @abstract Switch2 state
        @discussion update the switch2 state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_SwitchIn_Switch2(bool param_b);  

    /*!
        @function
        @abstract Switch3 state
        @discussion update the switch3 state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_SwitchIn_Switch3(bool param_b);  

    /*!
        @function
        @abstract Switch4 state
        @discussion update the switch4 state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_SwitchIn_Switch4(bool param_b);  

    /*!
        @function
        @abstract Menu switch state
        @discussion update the menu switch state(0=OFF/LOW; 1=ON/HIGH)

        @param  param_b {[0..1] state}
        @return none
    */
    void Rte_Write_SwitchIn_MenuSwitch(bool param_b);  

    /*!
        @function
        @abstract Browse menu
        @discussion Update which information is being browsed

        @param  param_e {[see enumbrowse_menu_et] browse menu}
        @return none
    */
    void Rte_Write_Menu_BrowseMenu(enum browse_menu_et param_e);    

    /*!
        @function
        @abstract Main menu
        @discussion Update which settings/configuration is being selected

        @param  param_e {[see main_menu_et] main menu}
        @return none
    */
    void Rte_Write_Menu_MainMenu(enum main_menu_et param_e);                                   

protected:

    bool                        Rte_DI_Switch1_b_;
    bool                        Rte_DI_Switch2_b_;
    bool                        Rte_DI_Switch3_b_;
    bool                        Rte_DI_Switch4_b_;
    bool                        Rte_DI_MenuSwitch_b_;
    bool                        Rte_DO_LedIndicator_b_;
    bool                        Rte_DO_Buzzer_b_; 
    bool                        Rte_Transceiver_Status_b_;
    bool                        Rte_SwitchIn_Switch1_b_;   
    bool                        Rte_SwitchIn_Switch2_b_; 
    bool                        Rte_SwitchIn_Switch3_b_; 
    bool                        Rte_SwitchIn_Switch4_b_; 
    bool                        Rte_SwitchIn_MenuSwitch_b_;                   
    uint8_t                     Rte_Potentiometer_Poti1Data_;
    uint8_t                     Rte_JoyStick_ThrottleFwdBckwrd_;
    uint8_t                     Rte_JoyStick_ThrottleLeftRight_;
    uint16_t                    Rte_VoltageInDigit_;
    uint16_t                    Rte_ADC_LeftJoyStick_FwdBckwrd_;
    uint16_t                    Rte_ADC_LeftJoyStick_LeftRight_;
    uint16_t                    Rte_ADC_RightJoyStick_FwdBckwrd_;
    uint16_t                    Rte_ADC_RightJoyStick_LeftRight_;    
    uint16_t                    Rte_ADC_VoltageReading_;
    uint16_t                    Rte_ADC_Potentiometer1_;      
    float                       Rte_ActualVoltage_f_;
    enum voltage_status_et      Rte_VoltageStatus_e_;
    enum direction_et           Rte_JoyStick_ControlFwdBckwrd_e_;
    enum direction_et           Rte_JoyStick_ControlLeftRight_e_;
    enum mode_et                Rte_ControllerMode_e_;
    enum browse_menu_et         Rte_BrowseMenu_e_;
    enum main_menu_et           Rte_MainMenu_e_;
    

// private:

};

extern Rte    rte_ivar;

#endif // RE_RTE_H_