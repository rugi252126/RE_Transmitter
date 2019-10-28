#ifndef RE_MENU_H_
#define RE_MENU_H_

//#include "Arduino.h"
#include "RE_Rte.h"

#define MENU_CYCLIC_TIME_K            200u                      // 200ms
#define MENU_MAIN_DEBOUNCE_TIME_K    (3000u/MENU_CYCLIC_TIME_K) // 3sec.

enum menu_switch_state_et
{
     MENU_SWITCH_PRESSED_E     = 0
    ,MENU_SWITCH_NOT_PRESSED_E = 1
    ,MENU_SWITCH_MAX_E
};

#if 0
enum main_menu_et
{
     MENU_MAIN_OPTIONS_E
    ,MENU_MAIN_MODE_E
};

enum browse_menu_et
{
     MENU_DISPLAY_GENERAL_INFO_E   = 0 // connection, controller mode
    ,MENU_DISPLAY_VOLTAGE_INFO_E   = 1 // voltage and its status(normal, low voltage, critical low voltage)
    ,MENU_DISPLAY_JOYSTICK_INFO_E  = 2 // throttle and control info
    ,MENU_DISPLAY_SWITCH_INFO_E    = 3 // switch 1 to 4 info
    ,MENU_DISPLAY_POTI_INFO_E      = 4 // potentiometer info
    ,MENU_DISPLAY_CONTROLLER_TYPE_E= 5 // robot, drone, plane, boat, car, etc..(default: robot)
    ,MENU_DISPLAY_MAX_E
};
#endif

class RE_Menu_cls
{
public:

    /*
     */
    RE_Menu_cls();

    /*
     */
    bool menuF_getMainmenuStatus(void);

    /*
     */
    //enum browse_menu_et menuF_getBrowseMenu(void);

    /*
     */
    //enum main_menu_et menuF_getMainMenu(void);   

    /*
     */
    //void menuF_RTE_Read_MenuSwitchState(bool state_b);

    /*
     */
    void menuF_Cyclic(void);

protected:
    
    enum main_menu_et main_menu_e;
    enum browse_menu_et browse_menu_e;
    enum menu_switch_state_et menu_switch_browse_state_e;
    bool main_menu_status_b; // 1 = inside main menu; 0 = otherwise
    bool main_menu_entry_exit_b;
    bool browse_menu_status_b;
    //bool RTE_Read_menu_switch_state_b;
    uint8_t browse_menu_ctr_u8;
    uint8_t main_menu_ctr_u8;
    uint16_t main_menu_entry_exit_debounce_time_u16;

private:

    /*
     */
    void menuLF_checkMainMenuDebounceTime(void);

    /*
     */
    void menuLF_checkMenuSwitchStatus(void);

    /*
     */
    void menuLF_browseMenu(void);

    /*
     */
    void menuLF_mainMenu(void);

    /*
     */
    void menuLF_updateRteData(void);
}; // class RE_Menu_cls

#endif // RE_MENU_H_