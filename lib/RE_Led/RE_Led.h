/**
    @file RE_Led.h

	@brief
	This implements the LED indicator.
	The LED represents the radio transceiver status.
	If the connection between radio and target is not okay, the LED will blink continously.
	And if the connection is okay, the LED will switch-ON continously.

	@author Alfonso, Rudy Manalo
    @version
*/

#ifndef RE_LED_H_
#define RE_LED_H_

#include "RE_Rte.h"

/*!
    @defined 
    @abstract Defines module time configuration
    @discussion This constant defines the module cyclic time and LED blink time.
    The time is in milli-second form.
*/
#define LED_CYCLIC_TIME_K         200u                      // 200ms

/*!
    @defined 
    @abstract Defines the time for LED control
    @discussion This constant defines the time to control the LED when connection is not okay.
    ON->OFF and vice versa of LED
*/
#define LED_BLINK_DELAY_TIME_K    (600u/LED_CYCLIC_TIME_K)  // 600ms

class RE_Led_cls
{
public:

    /*!
        @method
        @abstract RE_Led abstract constructor
        @discussion RE_Led class abstract constructor needed to create the abstract base class.
    */
	RE_Led_cls();

    /*!
        @function
        @abstract Module initialization
        @discussion It sets the initial state of the LED.

        @param  none
        @return none
    */
    void ledF_Init(void);

    /*!
        @function
        @abstract Module cyclic function
        @discussion Tasks within the module that need to be called cyclically will be done here.

        @param  none
        @return none
    */
    void ledF_Cyclic(void);

protected:

    bool    led_status_b;          // either LED is ON/OFF
    bool    transceiver_status_b;  // either connection is okay or not.
    uint8_t led_blink_delay_u8;    // delay time between LED ON->OFF and vice versa

private:
    
    /*!
	    @function
		@abstract Read transceiver status
		@discussion Read status of transceiver and decide the action for the LED.

		@param  none
		@return none
	*/
	void ledLF_getTransceiverStatus(void);
	
	/*!
	    @function
		@abstract Apply LED behavior
		@discussion Controls the behavior of the LED based on the status of the transceiver.
		LED is always ON if connection is okay otherwise the LED will blink continously.

		@param  none
		@return none
	*/
	void ledLF_applyLedBehavior(void);
};

#endif // RE_LED_H_