#ifndef RE_LED_H_
#define RE_LED_H_

//#include "RE_Hal.h"
#include "Arduino.h"

#define LED_CYCLIC_TIME_K         200u // 200ms
#define LED_BLINK_DELAY_TIME_K    (600u/LED_CYCLIC_TIME_K)

class RE_Led_cls
{
public:

    /*!
	 */
	RE_Led_cls();

	/*!
	 */
    //void ledF_RTE_Read_TransceiverStatus(bool RTE_Read_transceiver_state_b);

	/*!
	 */
    //enum digitalPortState_et ledF_RTE_Write_LedStatus(void);	
	
	/*!
	 */
    void ledF_Cyclic(void);

protected:
    //enum digitalPortState_et  RTE_Write_LedState_e;
    bool    led_status_b;
    bool    transceiver_status_b;
	//bool    RTE_Read_transceiver_status_b;
    uint8_t led_blink_delay_u8;

private:
    
    /*!
	 */
	void ledLF_getTransceiverStatus(void);
	
	/*!
	 */
	void ledLF_checkAction(void);
};

#endif // RE_LED_H_