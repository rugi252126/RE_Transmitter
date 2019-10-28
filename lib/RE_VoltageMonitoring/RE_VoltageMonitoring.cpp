/*
 Add description
 */
 
 
//#include "RE_Rte.h"
#include "RE_VoltageMonitoring.h"
 
/*
 */ 
RE_VoltageMonitoring_cls::RE_VoltageMonitoring_cls()
{
	
}

/*
 Return the calculated voltage. It will return the actual one(e.g. 7.5V)
 */
float RE_VoltageMonitoring_cls::voltageMonitoringF_getActualVoltage(void)
{
    return(ad_voltage_f);
}	

/*
 Return the calculated voltage. It will return in digit(e.g. 7.5V -> 750 in digit)
 */
uint16_t RE_VoltageMonitoring_cls::voltageMonitoringF_getVoltageInDigit(void)
{
    return(ad_voltage_u16);
}	

/*
 */
//void RE_VoltageMonitoring_cls::voltageMonitoringF_RTE_Read_10bit_ADC(uint16_t adc_u16)
//{
//    RTE_Read_ad_voltage_f = adc_u16;
//}

/*
 */
void RE_VoltageMonitoring_cls::voltageMonitoringF_Cyclic(void) 
{
	// get voltage raw AD
	//voltageMonitoringLF_getVoltageRawAD();
	
	// calculate voltage
	voltageMonitoringLF_calculateVoltage();

	// check voltage status
	voltageMonitoringLF_checkVoltageStatus();

	// apply voltage error filtering
	voltageMonitoringLF_applyVoltageErrorFiltering();

	// update RTE data
	voltageMonitoringLF_updateRteData();
}


/*
 */
////void RE_VoltageMonitoring_cls::voltageMonitoringLF_getVoltageRawAD(void)
//{
//}

/*
 */
void RE_VoltageMonitoring_cls::voltageMonitoringLF_calculateVoltage(void)
{
	float tmp_f;

	tmp_f = Rte_cls.Rte_Read_Hal_ADC_VoltageReading();
	tmp_f = tmp_f/VOLT_MONITOR_DIVISOR_K;

	ad_voltage_u16 = (uint16_t)(tmp_f * VOLT_MONITOR_RESOLUTION_K); // This will give a value in digit form with 2 decimal places(e.g. 7.5V -> 750)

	ad_voltage_f = tmp_f / VOLT_MONITOR_RESOLUTION_K;
}

/*
 */
void RE_VoltageMonitoring_cls::voltageMonitoringLF_checkVoltageStatus(void)
{
	uint16_t tmp_u16;
    
	tmp_u16 = ad_voltage_u16;
	if(tmp_u16 <= VOLT_BUZZER_THRESHOLD1_K)
	{ 
		if(voltage_status_buf_e != VOLT_LOW_E)
		{
		    filter_time_u8 = 0u;
		    voltage_status_buf_e = VOLT_LOW_E;
		}
	}
	else if(tmp_u16 <= VOLT_BUZZER_THRESHOLD1_K)
	{
		if(voltage_status_buf_e != VOLT_LOW_CRITICAL_E)
		{
		    filter_time_u8 = 0u;
		    voltage_status_buf_e = VOLT_LOW_CRITICAL_E;
		}		
	}
	else
	{
		voltage_status_buf_e = VOLT_NORMAL_E;
	}
}

/*
 */
void RE_VoltageMonitoring_cls::voltageMonitoringLF_applyVoltageErrorFiltering(void)
{
    switch(voltage_status_buf_e)
	{
		case VOLT_NORMAL_E:
	    {
		    if(filter_time_u8 != 0u)
		    {
		        filter_time_u8--;
		    }
            else
		    {
		    	voltage_status_e = VOLT_NORMAL_E;
		    }		
			break;
		}

		case VOLT_LOW_E:
		{
		    if(filter_time_u8 >= VOLT_FILTER_TIME_IN_MS_K)
		    {
		        voltage_status_e = VOLT_LOW_E;
		    }
		    else
		    {
			    filter_time_u8++;
		    }
			break;
		}

		case VOLT_LOW_CRITICAL_E:
		{
		    if(filter_time_u8 >= VOLT_FILTER_TIME_IN_MS_K)
		    {
		        voltage_status_e = VOLT_LOW_CRITICAL_E;
		    }
		    else
		    {
			    filter_time_u8++;
		    }			
			break;
		}

		default:
		{
			/* no action */
			break;
		}
	}
}

/*
 */
void RE_VoltageMonitoring_cls::voltageMonitoringLF_updateRteData(void)
{
	// update the voltage in digit
    Rte_cls.Rte_Write_VoltageMonitoring_VoltageInDigit(ad_voltage_u16);

	// update the actual voltage
	Rte_cls.Rte_Write_VoltageMonitoring_ActualVoltage(ad_voltage_f);

	// update voltage status
	Rte_cls.Rte_Write_VoltageMonitoring_VoltageStatus(voltage_status_e);
}

