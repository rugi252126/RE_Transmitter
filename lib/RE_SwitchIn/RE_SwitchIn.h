/**
    @file RE_SwitchIn.h

    @brief
    This implements the switches(e.g. push button, toggle) control in the controller.
    Currently, the module only covered digital input switches. R-coded switches is not
    yet covered in the module. It depends on the HW design, R-coded switches can also
    be covered here.

    @author Alfonso, Rudy Manalo
    @version 
*/

#ifndef RE_SWITCHIN_H_
#define RE_SWITCHIN_H_

#include "RE_Rte.h"


/*!
    @defined 
    @abstract Module macro definitions
    @discussion Defines the cyclic time, debounce time to stabilize the switches data and 
    maximum number of supported switches.
*/
#define SWITCHIN_TASK_IN_MS_K                             200u                         // 200ms -> module cyclic time
#define SWITCHIN_TOGGLE_PUSH_BUTTON_SWS_DEBOUNCE_TIME_K   (200u/SWITCHIN_TASK_IN_MS_K) // 200ms -> debounce time for other switches
#define SWITCHIN_MENU_SWS_DEBOUNCE_TIME_K                 (200u/SWITCHIN_TASK_IN_MS_K) // 200ms -> debounce time for menu switch
#define SWITCHIN_NUM_K                                    5u                           // maximum number of supported switches

/*!
    @defined 
    @abstract Digital input switches
    @discussion Defines all digital input switches
*/
enum switchIn_et
{
     SWITCHIN_SWS1_E     = 0 // 0
    ,SWITCHIN_SWS2_E     = 1 // 1
    ,SWITCHIN_SWS3_E     = 2 // 2
    ,SWITCHIN_SWS4_E     = 3 // 3
    ,SWITCHIN_SWS_MAX_E  = 4 // 4
    ,SWITCHIN_MENU_SWS_E = SWITCHIN_SWS_MAX_E // 4
    ,SWITCHIN_MAX_K          // maximum number of supported switches
};


class RE_SwitchIn_cls
{
public:
    
	/*!
        @method
        @abstract RE_SwitchIn abstract constructor
        @discussion RE_SwitchIn class abstract constructor needed to create the abstract base class.
	*/
    RE_SwitchIn_cls( );

	/*!
        @function
        @abstract Module initialization
        @discussion Initialize local data and internal state into default

        @param  none
        @return none
	*/
    void switchInF_Init(void);

    /*!
        @function
        @abstract Module cyclic function
        @discussion Called in fixed time interval cyclically

        @param  none
        @return none
	*/
    void switchInF_Cyclic(void);

protected:
    
    bool rte_read_switchState_b[SWITCHIN_NUM_K];        // data read from Rte
    bool switch_state_b[SWITCHIN_NUM_K];                // stabilized switch state
    bool switch_state_raw_b[SWITCHIN_NUM_K];            // raw switch state
    uint16_t switch_debounce_time_u16[SWITCHIN_NUM_K];  // debounce time to stabilize the switches   
 

private:

    /*!
        @function
        @abstract Get the data from Rte
        @discussion Get the switch state data from Rte interface and assign to local variable
        This is the hardware switch state. The infromation is coming from HAL layer.

        @param  none
        @return none
    */
    void switchInLF_getRteData(void);
 

    /*!
        @function
        @abstract Get switch status
        @discussion Get the switch state and check if state is changed or not.
        
        @param  idx {[0..SWITCHIN_NUM_K] switch index}
        @return none
    */
    void switchInLF_getSwitchStatus(uint8_t idx);

    /*!
        @function
        @abstract Stabilize the switches data
		@discussion The raw switch state will be stabilized before being sent to Rte interface.
		Makes sure the switch state data is stable before being used by other modules.

        @param  idx {[0..SWITCHIN_NUM_K] switch index}
        @return none        
    */
    void switchInLF_stabilizeSwitchStatus(uint8_t idx);

    /*!
        @function
        @abstract Update Rte Interface
        @discussion Update the Rte interface information to keep other modules up-to-date

        @param  none
        @return none
    */
    void switchInLF_updateRteData(void);    
}; // end of class RE_SwitchIn_cls

#endif // RE_SWITCHIN_H_