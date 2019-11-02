
/**
    @file main.c

    @brief
    DIY transmitter using NRF24L01 aka "RE_Transmitter".
    The transmitter is designed in a way that can be used in different application like controlling
    robot, drone, rc car, rc boat, planes etc..
    The LCD display is used to select the modes(e.g. robot, drone, etc..) and to test and calibrate the joyStick.
    IMU is also available to make it possible to control thru the movement of the controller itself.
    It has up to 10 channels. There is LED indicator to show the connection status between transmitter and receiver.
    It reads the voltage as well. The information is also visible in the LCD display.
    There is a built-in buzzer. The buzzer will be activated when in low voltage. Different sounds will
    produce depend on the voltage level.
    Default controlled mode is Mode2 but it is possible to select the mode during operation( Mode1 and Mode2).

    @author Alfonso, Rudy Manalo
    @version version/revision history ussually comes from the version control tool
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


//! Create object instances
RE_Hal                   main_hal_cls;         // from "RE_Hal" module
RE_Buzzer_cls            main_buzzer_cls;      // from "RE_Buzzer" module              
RE_VoltageMonitoring_cls main_voltage_cls;     // from "RE_VoltageMonitoring" module   
RE_JoyStick_cls          main_joystick_cls;    // from "RE_JoyStick" module            
RE_Led_cls               main_led_cls;         // from "RE_Led" module                 
RE_Transceiver_cls       main_transceiver_cls; // from "RE_Transceiver" module         
RE_Poti_cls              main_poti_cls;        // from "RE_Potentiometer" module       
RE_SwitchIn_cls          main_switchIn_cls;    // from "RE_SwitchIn" module            
RE_Menu_cls              main_menu_cls;        // from "RE_Menu" module               
RE_Lcd_cls               main_lcd_cls;         // from "RE_Lcd" module    
RE_Rte_cls               Rte_cls;              // from :RE_Rte" module          

//! global variable declarations
static unsigned long main_previous_task_time_ul = 0u;


//! Local funtion prototypes
static void mainLF_prio_TASK(void);
static void main_sub_TASK(void   );


/**
    Setting-up the system
    This function will be called once every POR/start-up.

    @param  none
    @return none
*/
void setup() {
#ifdef MAIN_DEBUG_USED_
    Serial.begin(9600);
#endif // #ifdef MAIN_DEBUG_USED_

    // Initialize the IO ports.
    main_hal_cls.halF_init(); 

    // Initialize buzzer module
    main_buzzer_cls.buzzerF_Init();

    // Initialize JoyStick module
    main_joystick_cls.joyStickF_init();

    // Set the controller default mode
    main_joystick_cls.joyStickF_setMode(MODE2_E);

    // Initialize the NRFL401 transceiver
    main_transceiver_cls.transceiverF_Init();

    // Initialize the LCD display
    main_lcd_cls.lcdF_Init();
}

/**
    Main loop
    This function will be called cyclically.

    @param  none
    @return none
*/
void loop() {

    if ((millis() - main_previous_task_time_ul) >= MAIN_200MS_TASK_K)
    {
        main_sub_TASK();
        main_previous_task_time_ul = millis();
    }
} // loop


/**
    Functions that cyclically calls HAL related tasks.
    Must be called before other application.

    @param  none
    @return none
*/
static void mainLF_prio_TASK(void)
{//! Read and execute HAL related stuffs
    main_hal_cls.halF_cyclic();

    main_switchIn_cls.switchInF_Cyclic();
}


/**
    Functions handles the rest of the application that need to be called cyclically.

    @param  none
    @return none
*/
static void main_sub_TASK(void)
{
    mainLF_prio_TASK();

    // Voltage monitoring cylic function
    main_voltage_cls.voltageMonitoringF_Cyclic();

    // Poti cylic function
    main_poti_cls.potiF_Cyclic();

    // JoyStick cylic function
    main_joystick_cls.joyStickF_Cyclic();

    // Transceiver cylic function
    main_transceiver_cls.transceiverF_Cyclic();

    // Menu cylic function
    main_menu_cls.menuF_Cyclic();

    // LED cylic function
    main_led_cls.ledF_Cyclic();

    // Buzzer cylic function
    main_buzzer_cls.buzzerF_Cyclic();

    // LCD cylic function
    main_lcd_cls.lcdF_Cyclic();
}