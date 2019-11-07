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

 
// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------
RE_Led_cls::RE_Led_cls()
{	
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void RE_Led_cls::ledF_Init(void)
{
    led_status_b = false;
    transceiver_status_b = false;
    led_blink_delay_u8 = 0u;	
}

// ---------------------------------------------------------------------------
// Cyclic function
void RE_Led_cls::ledF_Cyclic(void)
{
	// Read transceiver status
	ledLF_getTransceiverStatus();
	
	// Take necessary action based on transceiver status
	ledLF_applyLedBehavior();
}

// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Read the transceiver status
void RE_Led_cls::ledLF_getTransceiverStatus(void)
{
	bool tmp_stat_b;

	tmp_stat_b = Rte_cls.Rte_Read_Transceiver_Status();
	if(tmp_stat_b != false)
	{ //! Connection is established.
		transceiver_status_b = true;
	}
	else
	{ //! Connection is not established.
		transceiver_status_b = false;
	}
}

// ---------------------------------------------------------------------------
 // Either LED is permanently ON(connection is established) or LED is blinking(connection is not established).
void RE_Led_cls::ledLF_applyLedBehavior(void)
{
	if (transceiver_status_b != true)
	{ //! Connection is not established. Blink the LED indicator.
		if (led_status_b != false)
		{
            if (led_blink_delay_u8 >= LED_BLINK_DELAY_TIME_K)
			{
				led_status_b = false;    // transition from LED OFF to LED ON.
				led_blink_delay_u8 = 0u; // reset the delay time
			}
			else
			{
				led_blink_delay_u8++;
				Rte_cls.Rte_Write_Hal_DO_LedIndicator(HAL_IO_LOW_E);
			}
		}			
        else
        {
            if (led_blink_delay_u8 >= LED_BLINK_DELAY_TIME_K)
			{
				led_status_b = true;     // transition from LED ON to LED OFF.
				led_blink_delay_u8 = 0u; // reset the delay time
			}
			else
			{
				led_blink_delay_u8++;
				Rte_cls.Rte_Write_Hal_DO_LedIndicator(HAL_IO_HIGH_E);
			}
        }	
	}
	else
	{ //! Connection is established. Keep the LED indicator always ON.
        led_status_b = true; // LED is ON.
		Rte_cls.Rte_Write_Hal_DO_LedIndicator(HAL_IO_HIGH_E);
		//RTE_Write_LedState_e = HAL_IO_HIGH_E; // hal_led_cls.halF_setDO_State(HAL_DO_LED_IND_E,HAL_IO_HIGH_E);
	}
}