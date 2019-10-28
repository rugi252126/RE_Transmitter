/*
 TODO: Add module description
 */

//#include "RE_Rte.h"
#include "RE_Hal.h"


// Macros definition for Analog AD pins
#define HAL_ADC_LEFT_JOYSTICK_FWD_BCKWRD_K    A0
#define HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_K    A1
#define HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWRD_K   A2 
#define HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_K   A3
#define HAL_ADC_VOLTAGE_K                     A6
#define HAL_ADC_POTENTIOMETER1_K              A7


static const uint8_t halDI_ports[] = 
{
     HAL_DI_SWITCH1_K
    ,HAL_DI_SWITCH2_K 
    ,HAL_DI_SWITCH3_K
    ,HAL_DI_SWITCH4_K
    ,HAL_DI_MENU_SWITCH_K
};

static const uint8_t halDO_ports[] =
{
     HAL_DO_LED_IND_K 
    ,HAL_DO_BUZZER_K
};

static const uint8_t halADC_ports[] =
{
     HAL_ADC_LEFT_JOYSTICK_FWD_BCKWRD_K
    ,HAL_ADC_LEFT_JOYSTICK_LEFT_RIGHT_K
    ,HAL_ADC_RIGHT_JOYSTICK_FWD_BCKWRD_K
    ,HAL_ADC_RIGHT_JOYSTICK_LEFT_RIGHT_K
    ,HAL_ADC_VOLTAGE_K
    ,HAL_ADC_POTENTIOMETER1_K
};


/*

 */
RE_Hal::RE_Hal()
{

}

/*
 
 */
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

/*
 
 */
void RE_Hal::halF_setDO_State(digitalOut_et digitalOut_e, bool state_b)
{
    // add assert?
    digitalWrite(halDO_ports[digitalOut_e],state_b);
}

/*
 
 */
bool RE_Hal::halF_getDI_State(enum digitalIn_et digitalIn_e)
{
    // add aasert?
    return(digitalRead(halDI_ports[digitalIn_e]));
}

/*

*/
uint8_t RE_Hal::halF_getADC_8bit(enum adc_et adc_e)
{
    // adc_raw_16 contains 10-bit of ADC data. Shift to right twice to get the 8-bit form.
    adc_data_s[adc_e].adc_8bit_u8 = (uint8_t)(adc_data_s[adc_e].adc_raw_16 >> HAL_TO_8BIT_ADC_K);

    return(adc_data_s[adc_e].adc_8bit_u8);
}

/*

 */
uint16_t RE_Hal::halF_getADC_10bit(enum adc_et adc_e)
{
    adc_data_s[adc_e].adc_10bit_u16 = (adc_data_s[adc_e].adc_raw_16 >> HAL_TO_10BIT_ADC_K);

    return(adc_data_s[adc_e].adc_10bit_u16);
}

/*
 TODO: Define the cyclic time
 */
void RE_Hal::halF_cyclic(void)
{
    halLF_readADC();

    halLF_updateRteData();
}


/*

 */
void RE_Hal::halLF_readADC(void)
{
    uint8_t idx=0u;

    for(idx=0u; idx < HAL_ADC_MAX_INDEX_E; idx++)
    {
        adc_data_s[idx].adc_raw_16 = analogRead(halADC_ports[idx]);
    }
}

/*
 */
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
