#ifndef RE_LCD_H_
#define RE_LCD_H_

#include "RE_Menu.h"
//#include "RE_JoyStick.h"
//#include "RE_Buzzer.h"

#define LCD_CYCLIC_TIME_K         200u    // 200ms
#define LCD_I2C_ADDRESS_K         0x27
#define LCD_NUM_OF_ROWS_K         4
#define LCD_NUM_OF_COLUMNS_K      20


class RE_Lcd_cls
{
public:

    /*
     */
    RE_Lcd_cls();

    /*
     */
    void lcdF_Init();

#if 0
    /*
     */
    void lcdF_RTE_Read_JoyStickThrottleFwdBckwd(uint8_t throttle_u8);

     /*
     */
    void lcdF_RTE_Read_JoyStickThrottleLeftRight(uint8_t throttle_u8);   

    /*
     */
    void lcdF_RTE_Read_JoyStickControlFwdBckwd(enum direction_et control_e);  

    /*
     */
    void lcdF_RTE_Read_JoyStickControlLeftRight(enum direction_et control_e);  

    /*
     */
    void lcdF_RTE_Read_JoyStickControllerMode(enum mode_et mode_e); 

    /*
     */
    void lcdF_RTE_Read_Poti(uint8_t poti_u8);

	/*
	 */
	void voltageMonitoringF_RTE_Read_ActualVoltage(float volt_f);    

	/*!
	 */
    void lcdF_RTE_Read_TransceiverStatus(bool state_b);    

    /*
     */
    void lcdF_RTE_Read_VoltageStatus(enum voltage_status_et state_e);

    /*
     */
    void lcdF_RTE_Read_SwitchState(enum digitalIn_et id_e, bool state_b);  

    /*
     */
    void lcdF_RTE_Read_MainMenuState(bool state_b); 

    /*
     */
    void lcdF_RTE_Read_MainMenu(enum main_menu_et main_menu_e);   

    /*
     */
    void lcdF_RTE_Read_BrowseMenu(enum browse_menu_et browse_menu_e);                
#endif

    /*
     */
    void lcdF_Cyclic(void);

protected:

    // variables to hold the info from other modules
    #if 0
    enum direction_et     RTE_Read_joystick_ctrl_fwd_bckwrd_display_info_e;
    enum direction_et     RTE_Read_joystick_ctrl_left_right_display_info_e;
    enum mode_et          RTE_Read_ControllerMode_e;
    uint8_t               RTE_Read_throttle_fwd_bckwrd_display_info_u8;
    uint8_t               RTE_Read_throttle_left_right_display_info_u8;
    uint8_t               RTE_Read_poti_display_info_u8;
    float                 RTE_Read_actual_voltage_display_info_f;
    bool                  RTE_Read_transceiver_status_display_info_b;
    bool                  RTE_Read_switch_DI_display_info_b[HAL_DI_SWITCH_MAX_E];
    bool                  RTE_Read_main_menu_state_b;
    enum main_menu_et     RTE_Read_main_menu_e;
    enum browse_menu_et   RTE_Read_browse_menu_e;
    enum voltage_status_et RTE_Read_VoltageStatus_e;
    #endif
    enum browse_menu_et   copy_browse_menu_e;

private:

    /*
     */
    void lcdLF_browseMenuDisplay(void);

    /*
     */
    void lcdLF_mainMenuDisplay(void);

}; // class RE_Lcd_cls


#endif // RE_LCD_H_