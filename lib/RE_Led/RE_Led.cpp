/**
    @file RE_Led.cpp

	@brief
	This implements the LED indicator.
	The LED represents the radio transceiver status.
	If the connection between radio and target is not okay, the LED will blink continously.
	And if the connection is okay, the LED will switch-ON continously.

	@author Alfonso, Rudy Manalo
    @version
*/

#include "RE_Led.h"

 
// CLASS CONSTRUCTOR
// ---------------------------------------------------------------------------
LedIndicator::LedIndicator()
{	
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void LedIndicator::ledF_Init(void)
{
    led_status_b_ = false;
    transceiver_status_b_ = false;
    led_blink_delay_ = 0u;	
}

// ---------------------------------------------------------------------------
// Cyclic function
void LedIndicator::ledF_Cyclic(void)
{
	// Read transceiver status
	ledLF_getTransceiverStatus();
	
	// Take necessary action based on transceiver status
	ledLF_applyLedBehavior();
}

// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Read the transceiver status
void LedIndicator::ledLF_getTransceiverStatus(void)
{
	bool tmp_stat_b;

	tmp_stat_b = rte_ivar.Rte_Read_Transceiver_Status();
	if(tmp_stat_b != false)
	{ //! Connection is established.
		transceiver_status_b_ = true;
	}
	else
	{ //! Connection is not established.
		transceiver_status_b_ = false;
	}
}

// ---------------------------------------------------------------------------
 // Either LED is permanently ON(connection is established) or LED is blinking(connection is not established).
void LedIndicator::ledLF_applyLedBehavior(void)
{
	if (transceiver_status_b_ != true)
	{ //! Connection is not established. Blink the LED indicator.
		if (led_status_b_ != false)
		{
            if (led_blink_delay_ >= LED_BLINK_DELAY_TIME_K)
			{
				led_status_b_ = false;    // transition from LED OFF to LED ON.
				led_blink_delay_ = 0u; // reset the delay time
			}
			else
			{
				led_blink_delay_++;
				rte_ivar.Rte_Write_Hal_DO_LedIndicator(HAL_IO_LOW_E);
			}
		}			
        else
        {
            if (led_blink_delay_ >= LED_BLINK_DELAY_TIME_K)
			{
				led_status_b_ = true;     // transition from LED ON to LED OFF.
				led_blink_delay_ = 0u; // reset the delay time
			}
			else
			{
				led_blink_delay_++;
				rte_ivar.Rte_Write_Hal_DO_LedIndicator(HAL_IO_HIGH_E);
			}
        }	
	}
	else
	{ //! Connection is established. Keep the LED indicator always ON.
        led_status_b_ = true; // LED is ON.
		rte_ivar.Rte_Write_Hal_DO_LedIndicator(HAL_IO_HIGH_E);
	}
}