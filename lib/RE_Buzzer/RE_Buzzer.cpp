/*
 Add description
 */
 
#include "RE_Buzzer.h"
#include "RE_VoltageMonitoring.h"
#include "RE_Rte.h"

/*
 */
RE_Buzzer_cls::RE_Buzzer_cls()
{
	
}

/*
 */
void RE_Buzzer_cls::buzzerF_Init(void)
{
	buzzer_digitalPortState_e = HAL_IO_LOW_E;
	buzzer_delay_u8 = 0u;
	buzzer_status_b = false;
}

#if 0
/*
 */
void RE_Buzzer_cls::buzzerF_RTE_Read_Voltage(uint16_t volt_u16)
{
	RTE_Read_Voltage_u16 = volt_u16;
}

/*
 */
enum digitalPortState_et RE_Buzzer_cls::buzzerF_RTE_Write_State(void)
{
    return(buzzer_digitalPortState_e);
}
#endif

/*
 */
//enum voltage_status_et RE_Buzzer_cls::buzzerF_getVoltageStatus(void)
//{
//    return(buzzer_voltage_status_e);
//}

/*
 */
void RE_Buzzer_cls::buzzerF_Cyclic(void)
{
	// Get and check the status of the voltage
	//buzzerLF_getVoltage();
	
	// Set buzzer according to the status of the voltage
	buzzerLF_checkAction();

	// Update the Rte data
	buzzerLF_updateRteData();
}

#if 0
/*
 */
void RE_Buzzer_cls::buzzerLF_getVoltage(void)
{
	uint16_t tmp_u16;
    
	tmp_u16 = Rte_cls.rteF_Rte_Read_VoltageInDigit(); //RTE_Read_Voltage_u16;
	if(tmp_u16 <= BUZZER_VOLTAGE_THRESHOLD1_K)
	{ 
		buzzer_voltage_status_e = VOLT_LOW_E;
	}
	else if(tmp_u16 <= BUZZER_VOLTAGE_THRESHOLD2_K)
	{
		buzzer_voltage_status_e = VOLT_LOW_CRITICAL_E;
	}
	else
	{
		buzzer_voltage_status_e = VOLT_NORMAL_E;
	}
}
#endif

/*
 Either Buzzer is permanently ON(critical voltage state) or buzzer is ON and OFF(voltage is in semi-critical state).
 */
void RE_Buzzer_cls::buzzerLF_checkAction(void)
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
			// Voltage is in critical state. Buzzer will switch-ON continously.
			buzzer_digitalPortState_e = HAL_IO_HIGH_E;
			break;
		}
		default:
		{
			break;
		}
	}
}
 
/*
 */ 
void RE_Buzzer_cls::buzzerLF_updateRteData(void)
{
	Rte_cls.Rte_Write_Buzzer_PortState(buzzer_digitalPortState_e);
}