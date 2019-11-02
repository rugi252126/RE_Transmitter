/**
    @file RE_hal.h

    @brief
    The module contains the IO and ADC information.
    It defines here the ports used for digital IO and analog reading.

    @author Alfonso, Rudy Manalo
    @version
*/

#ifndef RE_HAL_H_
#define RE_HAL_H_

#include "RE_Rte.h"

//#define HAL_CYCLIC_TIME_K       10u // 10ms

//! Macro definition

/*!
    @defined 
    @abstract ADC-resolution definitions
    @discussion These constants can be used to shift the read analog data according to the needed resolution.
    Please keep in mind the base/maximum ADC-reolution supported by the microcontroller.
*/
#define HAL_TO_8BIT_ADC_K       2u // for arduino nano the maximum ADC resolution is 10-bit. Modify for other microcontroller that support ADC resolution more than 10-bit.
#define HAL_TO_10BIT_ADC_K      0u // for arduino nano the maximum ADC resolution is 10-bit. Modify for other microcontroller that support ADC resolution more than 10-bit.

/*!
    @defined 
    @abstract I/O pins definitions
    @discussion These constants define the digital I/O pins according to microcontroller pins.
*/
#define HAL_DI_SWITCH1_K        10 // D10
#define HAL_DI_SWITCH2_K        9  // D09
#define HAL_DI_SWITCH3_K        3  // D03
#define HAL_DI_SWITCH4_K        1  // D01/TX1
#define HAL_DI_MENU_SWITCH_K    2  // D02
#define HAL_DO_BUZZER_K         5  // D05
#define HAL_DO_LED_IND_K        6  // D06

/*!
    @defined 
    @abstract Defines all digital input switches
    @discussion This enum will be used when working with digital input switches.
*/
enum digitalIn_et
{
     HAL_DI_SWITCH1_E     = 0 // 0
    ,HAL_DI_SWITCH2_E     = 1 // 1
    ,HAL_DI_SWITCH3_E     = 2 // 2
    ,HAL_DI_SWITCH4_E     = 3 // 3
    ,HAL_DI_SWITCH_MAX_E  = 4 // 4
    ,HAL_DI_MENU_SWITCH_E = HAL_DI_SWITCH_MAX_E // 4
    ,HAL_DI_MAX_E
};

/*!
    @defined 
    @abstract Defines all digital output controls
    @discussion This enum will be used when controlling stuffs via digital output pins.
*/
enum digitalOut_et
{
     HAL_DO_LED_IND_E      // 0
    ,HAL_DO_BUZZER_E       // 1
    ,HAL_DO_MAX_E
};

// Enumerations for ADC(Analog Digital Convertion) channels
/*!
    @defined 
    @abstract Defines all analog channels
    @discussion This enum will be used when reading analog information.
*/
enum adc_et
{
     HAL_ADC_LEFT_JOYSTICK_FWD_BCKWD_E    // 0 -> A0
    ,HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_E   // 1 -> A1
    ,HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWD_E   // 2 -> A2
    ,HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_E  // 3 -> A3
    ,HAL_ADC_JOYSTICK_MAX_E               // number of joysticks
    ,HAL_ADC_VOLTAGE_READING_E = HAL_ADC_JOYSTICK_MAX_E // 4 -> A6
    ,HAL_ADC_POTENTIOMETER1_E             // 5 -> A7
    ,HAL_ADC_MAX_INDEX_E                  // 6
};


class RE_Hal
{
public:
    
    /*!
        @method
        @abstract HAL(Hardware Abstraction Layer) contructor
        @discussion HAL class abstract constructor needed to create the base abstract class.
    */
    RE_Hal( );

    /*!
        @function
        @abstract Module initialization
        @discussion Initialize local data and internal state into default

        @param  none
        @return none
    */
    void halF_init(void);

    /*!
        @function
        @abstract Digital output ports interface
        @discussion Set digital output ports to either HIGH or LOW. 

        @param digitalOut_e {[see enum digitalOut_et] digital output ID}
               state_b      {[0..1] value 0 = LOW; 1 = HIGH}
         @return none
    */
    void halF_setDO_State(digitalOut_et digitalOut_e, bool state_b);

    /*!
        @function
        @abstract Digital input ports interface
        @discussion Get digital input ports status. Status either HIGH or LOW.
        HIGH means 1. Usually the port is connected to positive voltage(e.g. 3.3V, 5V). 
        LOW means 0. Usually the port is connected to GND.

        @param  digitalIn_e [see enum digitalIn_et] digital input ID
        @return bool [0..1] value either 1 or 0.    
    */
    bool halF_getDI_State(enum digitalIn_et digitalIn_e);

    /*!
        @function
        @abstract 8-bit ADC
        @discusiion Read 8-bit ADC equivalent value

        @param adc_e [see enum adc_et] ADC ID
        @return uint8_t [0..255] 8-bit ADC value
    */
    uint8_t halF_getADC_8bit(enum adc_et adc_e);

    /*!
        @function
        @abstract 8-bit ADC
        @discusiion Read 10-bit ADC equivalent value

        @param adc_e [see enum adc_et] ADC ID
        @return uint16_t will only handle masimum of 10-bit ADC value
    */
    uint16_t halF_getADC_10bit(enum adc_et adc_e);    

    /*!
        @function
        @abstract Cyclic function
        @discussion Cyclic function to be called in specific task/time slice

        @param none
        @return none
    */
    void halF_cyclic(void);

protected:
    // Internal variables to handle analog data.
    struct adc_data_st
    {
        uint8_t  adc_8bit_u8;    // for 8-bit resolution 
        uint16_t adc_10bit_u16;  // for 10-bt resolution
        uint16_t adc_raw_16;     // data before converion to different resolution is applied.
    };
    struct adc_data_st adc_data_s[HAL_ADC_MAX_INDEX_E];


private:
    /*!
        @function
        @abstract ADC reading
        @discussion Read all ADC values and assigned to specific variables

        @param none
        @return none
    */
    void halLF_readADC(void);

    /*!
    */
    void halLF_updateRteData(void);    
};


#endif // RE_HAL_H_