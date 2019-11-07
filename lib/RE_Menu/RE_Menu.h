/**
    @file RE_Menu.h

    @brief
    This handles the different menu and browse menu in the system.
    In main menu, user can choose what to control(e.g. robot, drone, etc..) and can set the controller mode.
    Basically, it can set the controller configuration.
    And in browse menu, user can see the actual settings of the controller and the status like
    connection, battery, throttle, direction, etc..

    @author Alfonso, Rudy Manalo
    @version
*/

#ifndef RE_MENU_H_
#define RE_MENU_H_

#include "RE_Rte.h"


/*!
    @defined 
    @abstract Defines module cyclic time
    @discussion This constant defines the module cyclic time.
    The time is in milli-second form.
*/
#define MENU_CYCLIC_TIME_K            200u                      // 200ms

/*!
    @defined 
    @abstract Time to enter main menu
    @discussion When the menu switch is pressed continously within 3sec., the system will enter in main menu.
*/
#define MENU_MAIN_DEBOUNCE_TIME_K    (3000u/MENU_CYCLIC_TIME_K) // 3sec.

/*!
    @defined 
    @abstract Switch state
    @discussion The enumeration defines the different switch state for digital IO switch.
*/
enum menu_switch_state_et
{
     MENU_SWITCH_PRESSED_E     = 0
    ,MENU_SWITCH_NOT_PRESSED_E = 1
    ,MENU_SWITCH_MAX_E
};


class RE_Menu_cls
{
public:

    /*!
        @method
        @abstract RE_Menu abstract constructor
        @discussion RE_Menu class abstract constructor needed to create the abstract base class.
    */
    RE_Menu_cls();

    /*!
        @function
        @abstract Module initialization
        @discussion It sets the initial state of the module.

        @param  none
        @return none
    */
    void menuF_Init(void);       

    /*!
        @function
        @abstract Return main menu status
        @Discussion Returns whether its inside the main menu or not.

        @param  none
        @return {[true/false] true=inside main menu; false=otherwise}
    */
    // bool menuF_getMainmenuStatus(void);

    /*!
        @function
        @abstract Module cyclic function
        @discussion Tasks within the module that need to be called cyclically will be done here.

        @param  none
        @return none
    */
    void menuF_Cyclic(void);

protected:
    
    enum main_menu_et main_menu_e;                        // main menu options
    enum browse_menu_et browse_menu_e;                    // browse menu options
    enum menu_switch_state_et menu_switch_browse_state_e; // browse menu switch state(pressed/not pressed) 
    bool main_menu_status_b;                              // true = inside main menu; false = otherwise
    bool main_menu_entry_exit_b;                          // mani menu exit status
    bool browse_menu_status_b;                            // true = inside browse menu; false = otherwise
    uint8_t browse_menu_ctr_u8;                           // counter to go to the list of browse menu options
    uint8_t main_menu_ctr_u8;                             // counter to go to the list of main menu options
    uint16_t main_menu_entry_exit_debounce_time_u16;      // main menu debounce time

private:

    /*!
        @function
        @abstract Main menu debounce time check
        @discussion If main menu switch is pressed, the debounce time will start to increment.
        And if pressed for at least 3sec., it will enter in main menu.

        @param  none
        @return none
    */
    void menuLF_checkMainMenuDebounceTime(void);

    /*!
        @function
        @abstract Menu switch status check
        @discussion Checks whether menu switch is pressed or not.

        @param  none
        @return none
    */
    void menuLF_checkMenuSwitchStatus(void);

    /*!
        @function
        @abstract Browse menu
        @discussion Every pressed and not pressed of the switch, the browse menu will go from one
        option to another.

        @param  none
        @return none
    */
    void menuLF_browseMenu(void);

    /*!
        @function
        @abstract Main menu
        @discussion Every pressed and not pressed of the switch, the main menu will go from one
        option to another. Controller settings can be done here.

        @param  none
        @return none
    */
    //void menuLF_mainMenu(void);

    /*!
        @function
        @abstract Update Rte Information
        @discussion Rte data will be updated here to make the information available to other modules.

        @param  none
        @return none
    */
    void menuLF_updateRteData(void);
}; // class RE_Menu_cls

#endif // RE_MENU_H_