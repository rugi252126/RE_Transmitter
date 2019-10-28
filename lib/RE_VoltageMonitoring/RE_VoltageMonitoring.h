#ifndef RE_VOLTAGEMONITORING_H_
#define RE_VOLTAGEMONITORING_H_

//#include "Arduino.h"
#include "RE_Rte.h"

#define VOLT_MONITOR_CYCLIC_TIME_K    200u//20u // 200ms
#define VOLT_FILTER_TIME_IN_MS_K      (1000u/VOLT_MONITOR_CYCLIC_TIME_K)
//! Voltage divisor applied to the read voltage
#define VOLT_MONITOR_DIVISOR_K        4.092
#define VOLT_MONITOR_RESOLUTION_K     10
#define VOLT_BUZZER_THRESHOLD1_K      750                         // equivalent to 7.5V
#define VOLT_BUZZER_THRESHOLD2_K      720                         // equivalent to 7.2V

#if 0
enum voltage_status_et
{
     VOLT_NORMAL_E       = 0
    ,VOLT_LOW_E          = 1
    ,VOLT_LOW_CRITICAL_E = 2	
};
#endif


class RE_VoltageMonitoring_cls
{
public:

    /*!
	 */
	RE_VoltageMonitoring_cls();
	
	/*!
	 */
	float voltageMonitoringF_getActualVoltage(void); 
	
	/*!
	 */
	uint16_t voltageMonitoringF_getVoltageInDigit(void); 	

	/*
	 */
	//void voltageMonitoringF_RTE_Read_10bit_ADC(uint16_t adc_u16);

    /*!
	 */
    void voltageMonitoringF_Cyclic(void);	

protected:
    uint8_t  filter_time_u8;
    //float    RTE_Read_ad_voltage_f;
    float    ad_voltage_f;
	uint16_t ad_voltage_u16;
	enum voltage_status_et  voltage_status_e;
	enum voltage_status_et  voltage_status_buf_e;

private:

    /*!
	 */
    void voltageMonitoringLF_getVoltageRawAD(void);	

    /*!
	 */
    void voltageMonitoringLF_calculateVoltage(void);

	/*
	 */
	void voltageMonitoringLF_checkVoltageStatus(void);

	/*
	 */
	void voltageMonitoringLF_applyVoltageErrorFiltering(void);

    /*!
	 */
    void voltageMonitoringLF_updateRteData(void);
}; // class RE_VoltageMonitoring_cls

#endif // RE_VOLTAGEMONITORING_H_