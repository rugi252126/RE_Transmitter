
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

#include "RE_Rte.h"


//! Macros
//#define MAIN_DEBUG_USED_   // define to debug using Serial monitor      
#define MAIN_CYCLIC_TIME_FREQUENCY_K    5u // 5Hz
#define MAIN_200MS_TASK_K               (1000u/MAIN_CYCLIC_TIME_FREQUENCY_K)


//! Create object instance 
Rte               rte_ivar;              // from "RE_Rte" module          

//! global variable declarations
static unsigned long main_previous_task_time_ul = 0u;


//! Local funtion prototypes
static void mainLF_prio_TASK();
static void main_sub_TASK();


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

    // HW Initialization(e.g. IO ports)
    rte_ivar.rteF_System_Init(HW_INIT_E);    

    // SW initialization
    rte_ivar.rteF_System_Init(SW_INIT_E);

    // HW and SW initialization
    rte_ivar.rteF_System_Init(HW_SW_INIT_E);      
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
static void mainLF_prio_TASK()
{//! Read and execute HAL related stuffs

    // HAL cyclic function
    rte_ivar.rteF_RE_Hal_Cyclic();

    // SwitchIn cyclic function
    rte_ivar.rteF_RE_SwitchIn_Cyclic();
}


/**
    Functions handles the rest of the application that need to be called cyclically.

    @param  none
    @return none
*/
static void main_sub_TASK()
{
    mainLF_prio_TASK();

    // Voltage monitoring cylic function
    rte_ivar.rteF_RE_VoltageMonitoring_Cyclic();

    // Poti cylic function
    rte_ivar.rteF_RE_Potentiometer_Cyclic();

    // JoyStick cylic function
    rte_ivar.rteF_RE_JoyStick_Cyclic();

    // Transceiver cylic function
    rte_ivar.rteF_RE_Transceiver_Cyclic();

    // Menu cylic function
    rte_ivar.rteF_RE_Menu_Cyclic();

    // LED cylic function
    rte_ivar.rteF_RE_Led_Cyclic();

    // Buzzer cylic function
    rte_ivar.rteF_RE_Buzzer_Cyclic();

    // LCD cylic function
    rte_ivar.rteF_RE_Lcd_Cyclic();
}