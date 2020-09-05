/**
    @file RE_VoltageMonitoring.h

	@brief
	This implements the battery voltage monitoring.
	The battery voltage ADC value will be read and converted into voltage form.
	The status will be cyclically checked to determine whether the battery is
	still in normal voltage range, low voltage or critically low voltage.

	@author Alfonso, Rudy Manalo
	@version
*/

#ifndef RE_VOLTAGEMONITORING_H_
#define RE_VOLTAGEMONITORING_H_

#include "RE_Rte.h"

/*!
    @defined 
    @abstract Module macro definitions
    @discussion Defines the cyclic time, filter time before moving from one voltage state to another,
    voltage conversion constants and low voltage thresholds.
*/
#define VOLT_MONITOR_CYCLIC_TIME_K    200u                               // 200ms -> module cyclic time 
#define VOLT_LOW_FILTER_TIME_IN_MS_K  (1000u/VOLT_MONITOR_CYCLIC_TIME_K) // time needed to change the state from normal -> low -> critical
#define VOLT_MONITOR_DIVISOR_K        4.092                              // Voltage divisor applied to the read voltage
#define VOLT_MONITOR_RESOLUTION_K     10                                 // Voltage resolution to have more accurate comparison and checking
#define VOLT_MONITOR_THRESHOLD1_K     750                                // equivalent to 7.5V
#define VOLT_MONITOR_THRESHOLD2_K     720                                // equivalent to 7.2V


class VoltageMonitoring
{
public:

	/*!
        @method
        @abstract RE_VoltageMonitoring abstract constructor
        @discussion RE_VoltageMonitoring class abstract constructor needed to create the abstract base class.
	*/
	VoltageMonitoring();
	
	/*!
        @function
        @abstract Module initialization
        @discussion Initialize local data and internal state into default

        @param  none
        @return none
	*/
    void voltageMonitoringF_Init(void);	

    /*!
        @function
        @abstract Module cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
	*/
    void voltageMonitoringF_Cyclic(void);	

protected:

    uint8_t  filter_time_;                          // filter time to make sure the voltage state is stable
    float    ad_voltage_f_;                         // actual voltage value. mainly used for voltage display
	uint16_t ad_voltage_;                           // voltage in decimal form. mainly used when comparing to low voltage thresholds
	enum voltage_status_et  voltage_status_e_;      // stable voltage state
	enum voltage_status_et  voltage_status_buf_e_;  // unstable voltage state

private:

    /*!
        @function
        @abstract Calculate voltage
        @discussion Based on the raw voltage ADC value, the actual voltage will be calculated.
        formula: actual_voltage = (raw battery voltage ADC value / VOLT_MONITOR_DIVISOR_K) / VOLT_MONITOR_RESOLUTION_K

        @param  none
        @return none
	*/
    void voltageMonitoringLF_calculateVoltage(void);

	/*!
        @function
        @abstract Check voltage status
        @discussion Check the raw voltage status(normal, low, critical)
        This function will be called before voltage state filteting.

        @param  none
        @return none

	*/
	void voltageMonitoringLF_checkVoltageStatus(void);

	/*!
        @function
        @abstract Voltage state filtering
        @discussion Filter time will be applied when changing from one state to another.
        This will make sure that the state is in stable condition.

        @param  none
        @return none
	*/
	void voltageMonitoringLF_applyVoltageStateFiltering(void);

    /*!
        @function
        @abstract Update Rte Interface
        @discussion Update the Rte interface information to keep other modules up-to-date

        @param  none
        @return none
    */
    void voltageMonitoringLF_updateRteData(void);
}; // class VoltageMonitoring

#endif // RE_VOLTAGEMONITORING_H_