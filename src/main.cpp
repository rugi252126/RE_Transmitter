
/*
* DIY transmitter using NRF24L01 aka "RE_Transmitter".
* The transmitter is designed in a way that can be used in different application like controlling
* robot, drone, rc car, rc boat, planes etc..
* The LCD display is used to select the modes(e.g. robot, drone, etc..) and to test and calibrate the joyStick.
* IMU is also available to make it possible to control thru the movement of the controller itself.
* It has up to 10 channels. There is LED indicator to show the connection status between transmitter and receiver.
* It reads the voltage as well. The information is also visible in the LCD display.
* There is a built-in buzzer. The buzzer will be activated when in low voltage. Different sounds will
* produce depend on the voltage level.
* Default controlled mode is Mode2 but it is possible to select the mode during operation( Mode1 and Mode2).
* Author: Alfonso, Rudy Manalo
*/

#include "Arduino.h"
#include "RE_Hal.h"
#include "RE_Buzzer.h"
#include "RE_VoltageMonitoring.h"
#include "RE_JoyStick.h"
#include "RE_Led.h"
#include "RE_Transceiver.h"
#include "RE_Potentiometer.h"
#include "RE_SwitchIn.h"
#include "RE_Menu.h"
#include "RE_Lcd.h"

//! Macros
//#define MAIN_DEBUG_USED_   // define to debug using Serial monitor      
#define MAIN_CYCLIC_TIME_FREQUENCY_K    5u // 5Hz
#define MAIN_200MS_TASK_K               (1000u/MAIN_CYCLIC_TIME_FREQUENCY_K)
#define MAIN_50MS_TASK_K                50u

//! Create object instances
RE_Hal                   main_hal_cls;         //! from "RE_Hal" module
RE_Buzzer_cls            main_buzzer_cls;      //! from "RE_Buzzer" module              
RE_VoltageMonitoring_cls main_voltage_cls;     //! from "RE_VoltageMonitoring" module   
RE_JoyStick_cls          main_joystick_cls;    //! from "RE_JoyStick" module            
RE_Led_cls               main_led_cls;         //! from "RE_Led" module                 
RE_Transceiver_cls       main_transceiver_cls; //! from "RE_Transceiver" module         
RE_Poti_cls              main_poti_cls;        //! from "RE_Potentiometer" module       
RE_SwitchIn_cls          main_switchIn_cls;    //! from "RE_SwitchIn" module            
RE_Menu_cls              main_menu_cls;        //! from "RE_Menu" module               
RE_Lcd_cls               main_lcd_cls;         //! from "RE_Lcd" module    
RE_Rte_cls               Rte_cls;              //! from :RE_Rte" module          

//! global variable declarations
#if 0
enum digitalPortState_et RTE_Write_buzzerPortState_e;
enum digitalPortState_et RTE_Write_transceiverPortState_e;
bool RTE_Read_transceiverState_b;
bool RTE_Read_menuSwitchState_b;
bool RTE_Read_DI_state_b[HAL_DI_MAX_E];
uint16_t RTE_Read_buzzerVoltageInDigit_u16;
uint16_t RTE_Read_Voltage_10bit_ADC_u16;
uint16_t RTE_Read_JoyStick_10bit_ADC_u16[HAL_ADC_JOYSTICK_MAX_E];
uint16_t RTE_Read_Poti_10bit_ADC_u16[POTI_TOTAL_NUMBER_K];
uint8_t  RTE_Read_JoyStickThrottleFwdBckwd_u8;
uint8_t  RTE_Read_JoyStickThrottleLeftRight_u8;   
enum direction_et  RTE_Read_JoyStickControlFwdBckwd_e;  
enum direction_et  RTE_Read_JoyStickControlLeftRight_e;  
enum voltage_status_et RTE_Read_voltageStatus_e;
uint8_t  RTE_Read_Poti_u8;
float RTE_Read_actualVoltage_f;
enum main_menu_et RTE_Read_MainMenu_e;
enum browse_menu_et RTE_Read_BrowseMenu_e;
// bool RTE_Read_DI_state_b[HAL_DI_MAX_E];
#endif // #if 0

static unsigned long main_previous_task_time_ul = 0u;
//static unsigned long main_50ms_task_ul = 0u;


//! Funtion prototypes
void mainLF_RTE(void);
void mainLF_prio_TASK(void);
void main_sub_TASK(void);


void setup() {
#ifdef MAIN_DEBUG_USED_
    Serial.begin(9600);
#endif

    //! Initialize the digital IO ports.
    main_hal_cls.halF_init(); 

    //! Set the controller default mode
    main_joystick_cls.joyStickF_setMode(MODE2_E);

    //! Initialize the NRFL401 transceiver
    main_transceiver_cls.transceiverF_Init();

    //! Initialize the LCD display
    main_lcd_cls.lcdF_Init();
}

void loop() {
    //if ((millis() - main_50ms_task_ul) >= MAIN_50MS_TASK_K)
    //{
        //mainLF_prio_TASK();
    //    main_50ms_task_ul = millis();
    //}

    if ((millis() - main_previous_task_time_ul) >= MAIN_200MS_TASK_K)
    {
        main_sub_TASK();
        main_previous_task_time_ul = millis();
    }
} // loop

/*
 */
void mainLF_RTE(void)
{
#if 0
    uint8_t    idx;

    /* start -> RE_Buzzer Read and Write */
    RTE_Read_buzzerVoltageInDigit_u16 = main_voltage_cls.voltageMonitoringF_getVoltageInDigit();
    main_buzzer_cls.buzzerF_RTE_Read_Voltage(RTE_Read_buzzerVoltageInDigit_u16);

    RTE_Write_buzzerPortState_e = main_buzzer_cls.buzzerF_RTE_Write_State();
    //main_hal_cls.halF_setDO_State(HAL_DO_BUZZER_E, RTE_Write_buzzerPortState_e); // set buzzer either OFF, ON and OFF repeatedly or contionusly ON.
    /* end   -> RE_Buzzer Read and Write */
#ifdef MAIN_DEBUG_USED_    
    Serial.print("Voltage: ");
    Serial.println(RTE_Read_buzzerVoltageInDigit_u16);
#endif    


    /* start -> RE_JoyStick Read and Write */
    for(idx=0u; idx < HAL_ADC_JOYSTICK_MAX_E; idx++)
    {
        RTE_Read_JoyStick_10bit_ADC_u16[idx] = main_hal_cls.halF_getADC_10bit((enum adc_et)idx); 
        main_joystick_cls.joyStickF_RTE_Read_10bit_ADC((enum adc_et)idx, RTE_Read_JoyStick_10bit_ADC_u16[idx]);
    }
#ifdef MAIN_DEBUG_USED_
    Serial.print("Joystick throttle fwd bckwd ");
    Serial.println(RTE_Read_JoyStick_10bit_ADC_u16[0]);
    Serial.print("Joystick throttle left right ");
    Serial.println(RTE_Read_JoyStick_10bit_ADC_u16[1]);
    Serial.print("Joystick control fwd bckwrd ");
    Serial.println(RTE_Read_JoyStick_10bit_ADC_u16[2]);
    Serial.print("Joystick control left right ");
    Serial.println(RTE_Read_JoyStick_10bit_ADC_u16[3]);            
#endif
    /* end   -> RE_JoyStick Read and Write */


    /* start -> RE_Led Read and Write */
    RTE_Read_transceiverState_b = main_transceiver_cls.transceiverF_getStatus();
    main_led_cls.ledF_RTE_Read_TransceiverStatus(RTE_Read_transceiverState_b);

    RTE_Write_transceiverPortState_e = main_led_cls.ledF_RTE_Write_LedStatus();
    main_hal_cls.halF_setDO_State(HAL_DO_LED_IND_E, RTE_Write_transceiverPortState_e); // set LED either continously ON or ON and OFF repeatedly.

    //! below info is for RE_Lcd module
    main_lcd_cls.lcdF_RTE_Read_TransceiverStatus(RTE_Read_transceiverState_b);
    /* end   -> RE_Led Read and Write */
#ifdef MAIN_DEBUG_USED_    
    Serial.println(RTE_Read_transceiverState_b);
#endif    


    /* start -> RE_Potentiometer Read and Write */
    for(idx=0u; idx < POTI_TOTAL_NUMBER_K; idx++)
    {
        RTE_Read_Poti_10bit_ADC_u16[idx] = main_hal_cls.halF_getADC_10bit(HAL_ADC_POTENTIOMETER1_E);
        main_poti_cls.potiF_RTE_Read_10bit_ADC(idx, RTE_Read_Poti_10bit_ADC_u16[idx]);
    }
    /* end   -> RE_Potentiometer Read and Write */
#ifdef MAIN_DEBUG_USED_    
    Serial.println(RTE_Read_Poti_10bit_ADC_u16[0]);
#endif    

    /* start -> RE_SwitchIn Read and Write */
    for(idx=0u; idx < HAL_DI_MAX_E; idx++)
    {
        RTE_Read_DI_state_b[idx] = main_hal_cls.halF_getDI_State((enum digitalIn_et)idx);
        main_switchIn_cls.switchInF_RTE_Read_State((enum digitalIn_et)idx, RTE_Read_DI_state_b[idx]);

        //! below info is for RE_Transceiver module
        main_transceiver_cls.transceiverF_RTE_Read_SwitchState((enum digitalIn_et)idx, RTE_Read_DI_state_b[idx]);

        //! below info is for RE_Lcd module
        main_lcd_cls.lcdF_RTE_Read_SwitchState((enum digitalIn_et)idx, RTE_Read_DI_state_b[idx]);
    }
    /* end   -> RE_SwitchIn Read and Write */
#ifdef MAIN_DEBUG_USED_    
        //Serial.println(RTE_Read_DI_state_b[4]);
#endif        


    /* start -> RE_Transceiver Read and Write */
    RTE_Read_JoyStickThrottleFwdBckwd_u8 = main_joystick_cls.joyStickF_getThrottleFwdBckwd();
    main_transceiver_cls.transceiverF_RTE_Read_JoyStickThrottleFwdBckwd(RTE_Read_JoyStickThrottleFwdBckwd_u8);
    
    RTE_Read_JoyStickThrottleLeftRight_u8 = main_joystick_cls.joyStickF_getThrottleLeftRight();
    main_transceiver_cls.transceiverF_RTE_Read_JoyStickThrottleLeftRight(RTE_Read_JoyStickThrottleLeftRight_u8); 

    RTE_Read_JoyStickControlFwdBckwd_e = main_joystick_cls.joyStickF_getControlFwdBckwd();
    main_transceiver_cls.transceiverF_RTE_Read_JoyStickControlFwdBckwd(RTE_Read_JoyStickControlFwdBckwd_e);  

    RTE_Read_JoyStickControlLeftRight_e = main_joystick_cls.joyStickF_getControlLeftRight();
    main_transceiver_cls.transceiverF_RTE_Read_JoyStickControlLeftRight(RTE_Read_JoyStickControlLeftRight_e);  

    RTE_Read_Poti_u8 = main_poti_cls.potiF_getValue(0u);
    main_transceiver_cls.tranceiverF_RTE_Read_Poti(RTE_Read_Poti_u8);

    //! below info is for RE_Lcd module
    main_lcd_cls.lcdF_RTE_Read_JoyStickThrottleFwdBckwd(RTE_Read_JoyStickThrottleFwdBckwd_u8);
    main_lcd_cls.lcdF_RTE_Read_JoyStickThrottleLeftRight(RTE_Read_JoyStickThrottleLeftRight_u8);
    main_lcd_cls.lcdF_RTE_Read_JoyStickControlFwdBckwd(RTE_Read_JoyStickControlFwdBckwd_e);
    main_lcd_cls.lcdF_RTE_Read_JoyStickControlLeftRight(RTE_Read_JoyStickControlLeftRight_e);
    main_lcd_cls.lcdF_RTE_Read_Poti(RTE_Read_Poti_u8);
    /* end   -> RE_Transceiver Read and Write */    


    /* start -> RE_VoltageMonitoring Read and Write */
    RTE_Read_Voltage_10bit_ADC_u16 = main_hal_cls.halF_getADC_10bit(HAL_ADC_VOLTAGE_READING_E); 
    main_voltage_cls.voltageMonitoringF_RTE_Read_10bit_ADC(RTE_Read_Voltage_10bit_ADC_u16);
    /* end   -> RE_VoltageMonitoring Read and Write */  


    /* start -> RE_Menu Read and Write */
    RTE_Read_menuSwitchState_b = main_hal_cls.halF_getDI_State(HAL_DI_MENU_SWITCH_E);
    main_menu_cls.menuF_RTE_Read_MenuSwitchState(RTE_Read_menuSwitchState_b);
#ifdef MAIN_DEBUG_USED_    
        //Serial.println(RTE_Read_menuSwitchState_b);
#endif        

     //! below info is for RE_Lcd module
    main_lcd_cls.lcdF_RTE_Read_MainMenuState(RTE_Read_menuSwitchState_b);
    /* end   -> RE_Menu Read and Write */ 


    /* start -> RE_Lcd Read and Write */
    RTE_Read_actualVoltage_f = main_voltage_cls.voltageMonitoringF_getActualVoltage();
	main_lcd_cls.voltageMonitoringF_RTE_Read_ActualVoltage(RTE_Read_actualVoltage_f); 
#ifdef MAIN_DEBUG_USED_    
    Serial.print("Actual Voltage: ");
    Serial.println(RTE_Read_actualVoltage_f);
#endif    

    RTE_Read_MainMenu_e = main_menu_cls.menuF_getMainMenu();
    main_lcd_cls.lcdF_RTE_Read_MainMenu(RTE_Read_MainMenu_e);  

    RTE_Read_BrowseMenu_e = main_menu_cls.menuF_getBrowseMenu();
    main_lcd_cls.lcdF_RTE_Read_BrowseMenu(RTE_Read_BrowseMenu_e);

    RTE_Read_voltageStatus_e = main_buzzer_cls.buzzerF_getVoltageStatus();
    main_lcd_cls.lcdF_RTE_Read_VoltageStatus(RTE_Read_voltageStatus_e);
    // Note: Other info needed for LCD are placed in other places as info is already used there.   
    /* end   -> RE_Lcd Read and Write */ 
#ifdef MAIN_DEBUG_USED_         
        //Serial.println(RTE_Read_BrowseMenu_e);
#endif     

#endif // #if 0
}

/*
 */
void mainLF_prio_TASK(void)
{//! Read HAL related stuffs
    main_hal_cls.halF_cyclic();

    //mainLF_RTE();

    main_switchIn_cls.switchInF_Cyclic();
}

void main_sub_TASK(void)
{
    mainLF_prio_TASK();

    //! Voltage monitoring cylic function
    main_voltage_cls.voltageMonitoringF_Cyclic();

    //! Poti cylic function
    main_poti_cls.potiF_Cyclic();

    //! JoyStick cylic function
    main_joystick_cls.joyStickF_Cyclic();

    //! Transceiver cylic function
    main_transceiver_cls.transceiverF_Cyclic();

    //! Menu cylic function
    main_menu_cls.menuF_Cyclic();

    //! LED cylic function
    main_led_cls.ledF_Cyclic();

    //! Buzzer cylic function
    main_buzzer_cls.buzzerF_Cyclic();

    //! LCD cylic function
    main_lcd_cls.lcdF_Cyclic();
}