/*
 Add description
 */

#include "RE_Led.h"
#include "RE_Rte.h"

 
/*
 */
RE_Led_cls::RE_Led_cls()
{
	
}

/*
 */
//void RE_Led_cls::ledF_RTE_Read_TransceiverStatus(bool RTE_Read_transceiver_state_b)
//{
//    RTE_Read_transceiver_status_b = RTE_Read_transceiver_state_b;
//}

/*
 */
//enum digitalPortState_et RE_Led_cls::ledF_RTE_Write_LedStatus(void)
//{
    //return(RTE_Write_LedState_e);
//}

/*
 */
void RE_Led_cls::ledF_Cyclic(void)
{
	ledLF_getTransceiverStatus();
	
	/* Take necessary action based on transceiver status */
	ledLF_checkAction();
}

/***************************************************************************/

/*
 */
void RE_Led_cls::ledLF_getTransceiverStatus(void)
{
	bool tmp_stat_b;

	tmp_stat_b = Rte_cls.Rte_Read_Transceiver_Status(); //RTE_Read_transceiver_status_b;
	if(tmp_stat_b != 0u)
	{ // Connection is established.
		transceiver_status_b = 1u;
	}
	else
	{ // Connection is not established.
		transceiver_status_b = 0u;
	}
}

/*
 Either LED is permanently ON(connection is established) or LED is blinking(connection is not established).
 */
void RE_Led_cls::ledLF_checkAction(void)
{
	//RE_Hal hal_led_cls; // create an object of class RE_Hal
	
	if (transceiver_status_b != 1u)
	{ // Connection is not established. Blink the LED indicator.
		if (led_status_b != 0u)
		{
            if (led_blink_delay_u8 >= LED_BLINK_DELAY_TIME_K)
			{
				led_status_b = 0u;       // transition from LED OFF to LED ON.
				led_blink_delay_u8 = 0u; // reset the delay time
			}
			else
			{
				led_blink_delay_u8++;
				Rte_cls.Rte_Write_Hal_DO_LedIndicator(HAL_IO_LOW_E);
				//RTE_Write_LedState_e = HAL_IO_LOW_E; // hal_led_cls.halF_setDO_State(HAL_DO_LED_IND_E,HAL_IO_LOW_E);
			}
		}			
        else
        {
            if (led_blink_delay_u8 >= LED_BLINK_DELAY_TIME_K)
			{
				led_status_b = 1u;       // transition from LED ON to LED OFF.
				led_blink_delay_u8 = 0u; // reset the delay time
			}
			else
			{
				led_blink_delay_u8++;
				Rte_cls.Rte_Write_Hal_DO_LedIndicator(HAL_IO_HIGH_E);
				//RTE_Write_LedState_e = HAL_IO_HIGH_E; // hal_led_cls.halF_setDO_State(HAL_DO_LED_IND_E,HAL_IO_HIGH_E);
			}
        }	
	}
	else
	{ // Connection is established. Keep the LED indicator always ON.
        led_status_b = 1u; // LED is ON.
		Rte_cls.Rte_Write_Hal_DO_LedIndicator(HAL_IO_HIGH_E);
		//RTE_Write_LedState_e = HAL_IO_HIGH_E; // hal_led_cls.halF_setDO_State(HAL_DO_LED_IND_E,HAL_IO_HIGH_E);
	}
}