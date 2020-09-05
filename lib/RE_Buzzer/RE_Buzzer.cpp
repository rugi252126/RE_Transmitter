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

// CLASS CONSTRUCTOR
// ---------------------------------------------------------------------------
Buzzer::Buzzer()
{	
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void Buzzer::buzzerF_Init(void)
{
    buzzer_digitalPortState_e_ = HAL_IO_LOW_E;
    buzzer_delay_ = 0u;
    buzzer_status_b_ = false;
}

// Cyclic function
void Buzzer::buzzerF_Cyclic(void)
{
    // Set buzzer according to the status of the battery voltage
    buzzerLF_checkBuzzerBehavior();

    // Update the Rte data
    buzzerLF_updateRteData();
}


// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Controls the behavior of buzzer based on battery voltage status
void Buzzer::buzzerLF_checkBuzzerBehavior(void)
{
    enum voltage_status_et   volt_stat_e;
    volt_stat_e = rte_ivar.Rte_Read_VoltageMonitoring_VoltageStatus();

    switch(volt_stat_e)
    {
        case VOLT_NORMAL_E:
        {
            // Voltage is in normal state. Buzzer is OFF.
            buzzer_digitalPortState_e_ = HAL_IO_LOW_E;
            break;
        }
        case VOLT_LOW_E:
        {
            // Voltage is in semi-critical state. Buzzer will switch-ON and OFF.
            if (buzzer_status_b_ != false)
            {
                if (buzzer_delay_ >= BUZZER_DELAY_TIME_K)
                {
                    buzzer_status_b_ = false; // transition from Buzzer OFF to Buzzer ON.
                    buzzer_delay_ = 0u; // reset the delay time
                }
                else
                {
                    buzzer_delay_++;
                    buzzer_digitalPortState_e_ = HAL_IO_LOW_E;
                }
            }			
            else
            {
                if (buzzer_delay_ >= BUZZER_DELAY_TIME_K)
                {
                    buzzer_status_b_ = true; // transition from Buzzer ON to Buzzer OFF.
                    buzzer_delay_ = 0u; // reset the delay time
                }
                else
                {
                    buzzer_delay_++;
                    buzzer_digitalPortState_e_ = HAL_IO_HIGH_E;
                }
            }			
            break;
        }
        case VOLT_LOW_CRITICAL_E:
        {
            // Voltage is in critical state. Buzzer will beep continously.
            buzzer_digitalPortState_e_ = HAL_IO_HIGH_E;
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
void Buzzer::buzzerLF_updateRteData(void)
{
    // Buzzer digital output port state(HIGH or LOW)
    rte_ivar.Rte_Write_Hal_DO_Buzzer((bool)buzzer_digitalPortState_e_);
}