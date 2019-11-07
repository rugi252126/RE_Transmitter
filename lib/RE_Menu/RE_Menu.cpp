/**
    @file RE_Menu.cpp

    @brief
    This handles the different menu and browse menu in the system.
    In main menu, user can choose what to control(e.g. robot, drone, etc..) and can set the controller mode.
    Basically, it can set the controller configuration.
    And in browse menu, user can see the actual settings of the controller and the status like
    connection, battery, throttle, direction, etc..

    @author Alfonso, Rudy Manalo
    @version
*/

#include "RE_Menu.h"


// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------
RE_Menu_cls::RE_Menu_cls()
{
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void RE_Menu_cls::menuF_Init(void)
{
    // Every POR, initialize into default and desirable states
    main_menu_e                            = MENU_MAIN_OPTIONS_E;
    browse_menu_e                          = MENU_DISPLAY_GENERAL_INFO_E;
    menu_switch_browse_state_e             = MENU_SWITCH_NOT_PRESSED_E;
    main_menu_status_b                     = false;
    main_menu_entry_exit_b                 = false;
    browse_menu_status_b                   = false;
    browse_menu_ctr_u8                     = 0u;
    main_menu_ctr_u8                       = 0u;
    main_menu_entry_exit_debounce_time_u16 = 0u;
}

// ---------------------------------------------------------------------------
// Returns main menu status
//bool RE_Menu_cls::menuF_getMainmenuStatus(void)
//{
//    return(main_menu_status_b);
//}

// ---------------------------------------------------------------------------
// Cyclic function
void RE_Menu_cls::menuF_Cyclic(void)
{
    // first, get the menu switch status
    menuLF_checkMenuSwitchStatus();  

    // execute main menu or browse menu
    menuLF_browseMenu();

    //menuLF_mainMenu();

    // Update Rte data
    menuLF_updateRteData();
}

// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Main menu entry/exit debounce time
void RE_Menu_cls::menuLF_checkMainMenuDebounceTime(void)
{
    if(main_menu_entry_exit_debounce_time_u16 >= MENU_MAIN_DEBOUNCE_TIME_K)
    {
        if(main_menu_entry_exit_b != true)
        { 
            // main menu entry/exit is triggered.
            main_menu_entry_exit_b = true;

            if(main_menu_status_b != false)
            {
                // main menu is de-activated. Can process the browse menu in this state.
                main_menu_status_b = false;
            }
            else
            {
                // main menu is activated. Can't process the browse menu in this state.
                main_menu_status_b = true;
            }
        }
        else
        {
            // no action
        }    
    }
    else
    {
        main_menu_entry_exit_debounce_time_u16++;
    }
}

// ---------------------------------------------------------------------------
// Reading and checking main menu switch state
void RE_Menu_cls::menuLF_checkMenuSwitchStatus(void)
{
    bool tmp_b;


    tmp_b = Rte_cls.Rte_Read_Hal_DI_MenuSwitch(); 

    if((bool)MENU_SWITCH_PRESSED_E == tmp_b)
    {
        menuLF_checkMainMenuDebounceTime();

        if(main_menu_status_b != true)
        { 
            // main menu is not activated. Possible to do menu browsing.
            menu_switch_browse_state_e = MENU_SWITCH_PRESSED_E;
        }
    }
    else
    {
        menu_switch_browse_state_e = MENU_SWITCH_NOT_PRESSED_E;

        if(main_menu_entry_exit_b != false)
        {
            // reset main menu entry/exit status
            main_menu_entry_exit_b = false;

            // reset the counter
            main_menu_entry_exit_debounce_time_u16 = 0u;
        }
        else
        {
            // no action
        }
    }
}

// ---------------------------------------------------------------------------
// Browse menu options checking and assignment
void RE_Menu_cls::menuLF_browseMenu(void)
{
    switch(menu_switch_browse_state_e)
    {
        case MENU_SWITCH_PRESSED_E:
        {
            browse_menu_status_b = true;
            break;
        }
        case MENU_SWITCH_NOT_PRESSED_E:
        {
            if(browse_menu_status_b != false)
            {
                // reset the browse_menu_status_b and wait for new pressed
                browse_menu_status_b = false;

                // menu switch is pressed and un-pressed. increment browse counter
                browse_menu_ctr_u8++;
                if(browse_menu_ctr_u8 >= MENU_DISPLAY_MAX_E)
                {
                    // reset the browse counter
                    browse_menu_ctr_u8 = 0u;
                }
                else
                {
                    // no action
                }
                 
                browse_menu_e = (enum browse_menu_et)browse_menu_ctr_u8;
            }
            else
            {
                // no action
            }
            
            break;
        }
        default:
        {
            break;
        }
    }
}

// ---------------------------------------------------------------------------
// Main menu checking and controller settings configuration
//void RE_Menu_cls::menuLF_mainMenu(void)
//{
//}

// ---------------------------------------------------------------------------
// Update Rte data
void RE_Menu_cls::menuLF_updateRteData(void)
{
    // Update Rte data for browse menu
    Rte_cls.Rte_Write_Menu_BrowseMenu(browse_menu_e);

    // Update Rte data for main menu
    Rte_cls.Rte_Write_Menu_MainMenu(main_menu_e);
}