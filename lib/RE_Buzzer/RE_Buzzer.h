#ifndef RE_BUZZER_H_
#define RE_BUZZER_H_

#include "RE_Hal.h"

#define BUZZER_CYCLIC_TIME_K           200u                        // 200ms
#define BUZZER_DELAY_TIME_K            (600u/BUZZER_CYCLIC_TIME_K) // 600ms
//#define BUZZER_VOLTAGE_THRESHOLD1_K    750                         // equivalent to 7.5V
//#define BUZZER_VOLTAGE_THRESHOLD2_K    720                         // equivalent to 7.2V


class RE_Buzzer_cls
{
public:

    /*!
	 */
	RE_Buzzer_cls();

    /*
     */
    //void buzzerF_RTE_Read_Voltage(uint16_t volt_u16);

    /*
     */
    //enum digitalPortState_et buzzerF_RTE_Write_State(void);    

    /*
     */
    //enum voltage_status_et buzzerF_getVoltageStatus(void);

    /*!
	 */
    void buzzerF_Init(void);	

    /*!
	 */
    void buzzerF_Cyclic(void);	 

protected:
    bool    buzzer_status_b;
    //enum    voltage_status_et   buzzer_voltage_status_e;
    enum    digitalPortState_et buzzer_digitalPortState_e;
    uint8_t buzzer_delay_u8;
    //uint16_t RTE_Read_Voltage_u16;

private:
    /*!
	 */
	//void buzzerLF_getVoltage(void);
	
	/*!
	 */
	void buzzerLF_checkAction(void);	

	/*!
	 */
	void buzzerLF_updateRteData(void);    
}; // class RE_Buzzer_cls

#endif // RE_BUZZER_H_