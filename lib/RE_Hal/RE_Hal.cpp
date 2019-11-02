/**
    @file RE_hal.cpp

    @brief
    The module contains the IO and ADC information.
    It defines here the ports used for digital IO and analog reading.

    @author Alfonso, Rudy Manalo
    @version
*/

#include "RE_Hal.h"


// Macros definition for Analog AD pins
#define HAL_ADC_LEFT_JOYSTICK_FWD_BCKWRD_K    A0
#define HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_K    A1
#define HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWRD_K   A2 
#define HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_K   A3
#define HAL_ADC_VOLTAGE_K                     A6
#define HAL_ADC_POTENTIOMETER1_K              A7

// Equivalent constant definition for digital input pins
static const uint8_t halDI_ports[] = 
{
     HAL_DI_SWITCH1_K
    ,HAL_DI_SWITCH2_K 
    ,HAL_DI_SWITCH3_K
    ,HAL_DI_SWITCH4_K
    ,HAL_DI_MENU_SWITCH_K
};

// Equivalent constant definition for digital output pins
static const uint8_t halDO_ports[] =
{
     HAL_DO_LED_IND_K 
    ,HAL_DO_BUZZER_K
};

// Equivalent constant definition for analog pins
static const uint8_t halADC_ports[] =
{
     HAL_ADC_LEFT_JOYSTICK_FWD_BCKWRD_K
    ,HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_K
    ,HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWRD_K
    ,HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_K
    ,HAL_ADC_VOLTAGE_K
    ,HAL_ADC_POTENTIOMETER1_K
};


// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------
RE_Hal::RE_Hal()
{
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void RE_Hal::halF_init(void)
{
    uint8_t idx=0u;

    /* Digital input ports initialization */
    for(idx=0u; idx < HAL_DI_MAX_E; idx++)
    {
        pinMode(halDI_ports[idx], INPUT);
    }

    /* Digital output ports initialization */
    for(idx=0u; idx < HAL_DO_MAX_E; idx++)
    {
        pinMode(halDO_ports[idx], OUTPUT);
    }
}

// ---------------------------------------------------------------------------
// Set digital output port state(HIGH or LOW)
void RE_Hal::halF_setDO_State(digitalOut_et digitalOut_e, bool state_b)
{
    // add assert?
    digitalWrite(halDO_ports[digitalOut_e],state_b);
}

// ---------------------------------------------------------------------------
// Get digital input port state(HIGH or LOW)
bool RE_Hal::halF_getDI_State(enum digitalIn_et digitalIn_e)
{
    // add aasert?
    return(digitalRead(halDI_ports[digitalIn_e]));
}

// ---------------------------------------------------------------------------
// Get 8-bit ADC data
uint8_t RE_Hal::halF_getADC_8bit(enum adc_et adc_e)
{
    // Shift the original ADC data to get the equivalent 8-bit resolution data
    adc_data_s[adc_e].adc_8bit_u8 = (uint8_t)(adc_data_s[adc_e].adc_raw_16 >> HAL_TO_8BIT_ADC_K);

    return(adc_data_s[adc_e].adc_8bit_u8);
}

// ---------------------------------------------------------------------------
// Get 10-bit ADC data
uint16_t RE_Hal::halF_getADC_10bit(enum adc_et adc_e)
{
    // Shift the original ADC data(if needed) to get the equivalent 10-bit resolution data
    adc_data_s[adc_e].adc_10bit_u16 = (adc_data_s[adc_e].adc_raw_16 >> HAL_TO_10BIT_ADC_K);

    return(adc_data_s[adc_e].adc_10bit_u16);
}

// ---------------------------------------------------------------------------
// Module cyclic function
void RE_Hal::halF_cyclic(void)
{
    // Read all ADC data
    halLF_readADC();

    // Update the RTE data
    halLF_updateRteData();
}


// PRIVATE METHODS
// ---------------------------------------------------------------------------
// cyclically read all ADC data
void RE_Hal::halLF_readADC(void)
{
    uint8_t idx=0u;

    for(idx=0u; idx < HAL_ADC_MAX_INDEX_E; idx++)
    {
        adc_data_s[idx].adc_raw_16 = analogRead(halADC_ports[idx]);
    }
}

// ---------------------------------------------------------------------------
// Cyclically update the RTE interfaces to make the information available on other modules
void RE_Hal::halLF_updateRteData(void)
{
    bool tmp_b;

    // Update ADC information
    Rte_cls.Rte_Write_Hal_ADC_LeftJoyStick_FwdBckwrd(adc_data_s[HAL_ADC_LEFT_JOYSTICK_FWD_BCKWD_E].adc_raw_16);

    Rte_cls.Rte_Write_Hal_ADC_LeftJoyStick_LeftRight(adc_data_s[HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_E].adc_raw_16);

    Rte_cls.Rte_Write_Hal_ADC_RightJoyStick_FwdBckwrd(adc_data_s[HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWD_E].adc_raw_16);

    Rte_cls.Rte_Write_Hal_ADC_RightJoyStick_LeftRight(adc_data_s[HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_E].adc_raw_16);

    Rte_cls.Rte_Write_Hal_ADC_VoltageReading(adc_data_s[HAL_ADC_VOLTAGE_READING_E].adc_raw_16);

    Rte_cls.Rte_Write_Hal_ADC_Potentiometer1(adc_data_s[HAL_ADC_POTENTIOMETER1_E].adc_raw_16);

    // Update digital input information
    tmp_b = digitalRead(halDI_ports[HAL_DI_SWITCH1_E]);
    Rte_cls.Rte_Write_Hal_DI_Switch1(tmp_b);

    tmp_b = digitalRead(halDI_ports[HAL_DI_SWITCH2_E]);
    Rte_cls.Rte_Write_Hal_DI_Switch2(tmp_b);

    tmp_b = digitalRead(halDI_ports[HAL_DI_SWITCH3_E]);
    Rte_cls.Rte_Write_Hal_DI_Switch3(tmp_b);

    tmp_b = digitalRead(halDI_ports[HAL_DI_SWITCH4_E]);
    Rte_cls.Rte_Write_Hal_DI_Switch4(tmp_b);

    tmp_b = digitalRead(halDI_ports[HAL_DI_MENU_SWITCH_E]);
    Rte_cls.Rte_Write_Hal_DI_MenuSwitch(tmp_b);        

    // Update digital output information
    tmp_b = Rte_cls.Rte_Read_Hal_DO_LedIndicator();
    digitalWrite(halDO_ports[HAL_DO_LED_IND_E],tmp_b);

    tmp_b = Rte_cls.Rte_Read_Hal_DO_Buzzer();
    digitalWrite(halDO_ports[HAL_DO_BUZZER_E],tmp_b);    
}
