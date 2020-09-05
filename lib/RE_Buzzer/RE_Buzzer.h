/**
     @file RE_Buzzer.h

	 @brief
	 This file implements the buzzer control.
	 It reads the battery voltage status and do the evaluation.
	 There are two low voltage thresholds(low and critical).
	 At low voltage, the buzzer will produce beep beep sound.
	 And at critical voltage level, the buzzer will beep continously.

	 @author Alfonso, Rudy Manalo
	 @version
 */

#ifndef RE_BUZZER_H_
#define RE_BUZZER_H_

#include "RE_Rte.h"

/*!
    @defined 
    @abstract Defines the module cyclic time
    @discussion This constant defines the time at which the module is called cyclically.
    The time is in milli-second form.
*/
#define BUZZER_CYCLIC_TIME_K           200u                        // 200ms

/*!
    @defined 
    @abstract Defines the time for low voltage buzzer control
    @discussion This constant defines the time to control the buzzer sound and produce
    beep-beep sound when battery voltage status is low.
*/
#define BUZZER_DELAY_TIME_K            (600u/BUZZER_CYCLIC_TIME_K) // 600ms


class Buzzer
{
public:

    /*!
        @method
        @abstract Buzzer abstract constructor.
        @discussion Buzzer class abstract constructor needed to create the abstract base class.
	*/
	Buzzer();

    /*!
        @function
        @abstract Module initialization
        @discussion It sets the initial state of the buzzer.

        @param  none
        @return none
	*/
    void buzzerF_Init(void);	

    /*!
        @function
        @abstract Module cylic task
        @discussion This will be called cyclically at a given time.

        @param  none
        @return none
	*/
    void buzzerF_Cyclic(void);	 

protected:
    // Internal buzzer variables to control the buzzer behavior
    enum    digitalPortState_et buzzer_digitalPortState_e_; // digital output port status(HIGH/LOW) of the buzzer
    bool    buzzer_status_b_;                               // status when battery voltage is in low condition
    uint8_t buzzer_delay_;                                  // time to toggle the buzzer output between HIGH to LOW and vice versa

private:
	/*!
        @function
        @abstract Controls buzzer behavior
        @discussion Buzzer will be either set to OFF, beep-beep sound or continously ON.

        @param  none
        @return none
	*/
	void buzzerLF_checkBuzzerBehavior(void);	

	/*!
        @function
        @abstract Update RTE information
        @discussion The information will be sent to RTE module and become available to other module(s).

        @param  none
        @return none
	*/
	void buzzerLF_updateRteData(void);    
}; // class Buzzer

#endif // RE_BUZZER_H_