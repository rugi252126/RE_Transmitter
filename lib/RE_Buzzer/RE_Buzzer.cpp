/**
     @file RE_Buzzer.cpp

     @brief
     This file implements the buzzer control.
     It reads the battery voltage status and do the evaluation.
     There are two low voltage thresholds(low and critical).
     At low voltage, the buzzer will produce beep beep sound.
     And at critical voltage level, the buzzer will beep continously.

     @author Alfonso, Rudy Manalo
     @version
 */
 
#include "RE_Buzzer.h"

// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------
RE_Buzzer_cls::RE_Buzzer_cls()
{	
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void RE_Buzzer_cls::buzzerF_Init(void)
{
    buzzer_digitalPortState_e = HAL_IO_LOW_E;
    buzzer_delay_u8 = 0u;
    buzzer_status_b = false;
}

// Cyclic function
void RE_Buzzer_cls::buzzerF_Cyclic(void)
{
    // Set buzzer according to the status of the battery voltage
    buzzerLF_checkBuzzerBehavior();

    // Update the Rte data
    buzzerLF_updateRteData();
}


// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Controls the behavior of buzzer based on battery voltage status
void RE_Buzzer_cls::buzzerLF_checkBuzzerBehavior(void)
{
    enum voltage_status_et   volt_stat_e;
    volt_stat_e = Rte_cls.Rte_Read_VoltageMonitoring_VoltageStatus();

    switch(volt_stat_e)
    {
        case VOLT_NORMAL_E:
        {
            // Voltage is in normal state. Buzzer is OFF.
            buzzer_digitalPortState_e = HAL_IO_LOW_E;
            break;
        }
        case VOLT_LOW_E:
        {
            // Voltage is in semi-critical state. Buzzer will switch-ON and OFF.
            if (buzzer_status_b != false)
            {
                if (buzzer_delay_u8 >= BUZZER_DELAY_TIME_K)
                {
                    buzzer_status_b = false; // transition from Buzzer OFF to Buzzer ON.
                    buzzer_delay_u8 = 0u; // reset the delay time
                }
                else
                {
                    buzzer_delay_u8++;
                    buzzer_digitalPortState_e = HAL_IO_LOW_E;
                }
            }			
            else
            {
                if (buzzer_delay_u8 >= BUZZER_DELAY_TIME_K)
                {
                    buzzer_status_b = true; // transition from Buzzer ON to Buzzer OFF.
                    buzzer_delay_u8 = 0u; // reset the delay time
                }
                else
                {
                    buzzer_delay_u8++;
                    buzzer_digitalPortState_e = HAL_IO_HIGH_E;
                }
            }			
            break;
        }
        case VOLT_LOW_CRITICAL_E:
        {
            // Voltage is in critical state. Buzzer will beep continously.
            buzzer_digitalPortState_e = HAL_IO_HIGH_E;
            break;
        }
        default:
        {
            break;
        }
    }
}

// ---------------------------------------------------------------------------
// Update the RTE interface
void RE_Buzzer_cls::buzzerLF_updateRteData(void)
{
    // Buzzer digital output port state(HIGH or LOW)
    Rte_cls.Rte_Write_Buzzer_PortState(buzzer_digitalPortState_e);
}