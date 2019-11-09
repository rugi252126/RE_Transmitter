/**
    @file RE_VoltageMonitoring.cpp

	@brief
	This implements the battery voltage monitoring.
	The battery voltage ADC value will be read and converted into voltage form.
	The status will be cyclically checked to determine whether the battery is
	still in normal voltage range, low voltage or critically low voltage.

	@author Alfonso, Rudy Manalo
	@version
*/

#include "RE_VoltageMonitoring.h"

 
// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------
RE_VoltageMonitoring_cls::RE_VoltageMonitoring_cls()
{
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void RE_VoltageMonitoring_cls::voltageMonitoringF_Init(void)
{
    // initialize into default value/state
    filter_time_u8       = 0u;
    ad_voltage_f         = 0;
	ad_voltage_u16       = 0u;
	voltage_status_e     = VOLT_NORMAL_E; 
	voltage_status_buf_e = VOLT_NORMAL_E;
}

// ---------------------------------------------------------------------------
// Cyclic function
void RE_VoltageMonitoring_cls::voltageMonitoringF_Cyclic(void) 
{
	// calculate voltage
	voltageMonitoringLF_calculateVoltage();

	// check voltage status
	voltageMonitoringLF_checkVoltageStatus();

	// apply voltage error filtering
	voltageMonitoringLF_applyVoltageStateFiltering();

	// update RTE data
	voltageMonitoringLF_updateRteData();
}

// ---------------------------------------------------------------------------
// Calculate the actual battery voltage
void RE_VoltageMonitoring_cls::voltageMonitoringLF_calculateVoltage(void)
{
	float tmp_f;

    // get battery voltage raw ADC value
	tmp_f = Rte_cls.Rte_Read_Hal_ADC_VoltageReading();
    
	tmp_f = tmp_f/VOLT_MONITOR_DIVISOR_K;

    // This will give a value in digit form with 2 decimal places(e.g. 7.5V -> 750)
	ad_voltage_u16 = (uint16_t)(tmp_f * VOLT_MONITOR_RESOLUTION_K);

    // actual voltage
	ad_voltage_f = tmp_f / VOLT_MONITOR_RESOLUTION_K;
}

// ---------------------------------------------------------------------------
// Check voltage status
void RE_VoltageMonitoring_cls::voltageMonitoringLF_checkVoltageStatus(void)
{
	uint16_t tmp_u16;
    
	tmp_u16 = ad_voltage_u16;
	if(tmp_u16 <= VOLT_MONITOR_THRESHOLD2_K)
	{ 
		if(voltage_status_buf_e != VOLT_LOW_CRITICAL_E)
		{
            // state is changed. reset the filter time.
		    filter_time_u8 = 0u;
            // voltage state is critically low.
		    voltage_status_buf_e = VOLT_LOW_CRITICAL_E;
		}	        
	}
	else if(tmp_u16 <= VOLT_MONITOR_THRESHOLD1_K)
	{
		if(voltage_status_buf_e != VOLT_LOW_E)
		{
            // state is changed. reset the filter time.
		    filter_time_u8 = 0u;
            // voltage state is low.
		    voltage_status_buf_e = VOLT_LOW_E;
		}	
	}
	else
	{
        // voltage is normal.
		voltage_status_buf_e = VOLT_NORMAL_E;
	}
}

// ---------------------------------------------------------------------------
// Stabilize the voltage state
void RE_VoltageMonitoring_cls::voltageMonitoringLF_applyVoltageStateFiltering(void)
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
                // voltage is in normal range.
		    	voltage_status_e = VOLT_NORMAL_E;
		    }		
			break;
		}

		case VOLT_LOW_E:
		{
		    if(filter_time_u8 >= VOLT_LOW_FILTER_TIME_IN_MS_K)
		    {
                // low voltage
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
		    if(filter_time_u8 >= VOLT_LOW_FILTER_TIME_IN_MS_K)
		    {
                // critically low voltage
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
			// no action
			break;
		}
	}
}

// ---------------------------------------------------------------------------
// Update the Rte information with the latest and stable voltage status
void RE_VoltageMonitoring_cls::voltageMonitoringLF_updateRteData(void)
{
	// update the voltage in digit
    Rte_cls.Rte_Write_VoltageMonitoring_VoltageInDigit(ad_voltage_u16);

	// update the actual voltage
	Rte_cls.Rte_Write_VoltageMonitoring_ActualVoltage(ad_voltage_f);

	// update voltage status
	Rte_cls.Rte_Write_VoltageMonitoring_VoltageStatus(voltage_status_e);
}

