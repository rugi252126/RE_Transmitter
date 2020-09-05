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


// CLASS CONSTRUCTOR
// ---------------------------------------------------------------------------
Menu::Menu()
{
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void Menu::menuF_Init(void)
{
    // Every POR, initialize into default and desirable states
    main_menu_e_                        = MENU_MAIN_OPTIONS_E;
    browse_menu_e_                      = MENU_DISPLAY_GENERAL_INFO_E;
    menu_switch_browse_state_e_         = MENU_SWITCH_NOT_PRESSED_E;
    main_menu_status_b_                 = false;
    main_menu_entry_exit_b_             = false;
    browse_menu_status_b_               = false;
    browse_menu_ctr_                    = 0u;
    main_menu_ctr_                      = 0u;
    main_menu_entry_exit_debounce_time_ = 0u;
}

// ---------------------------------------------------------------------------
// Returns main menu status
//bool RE_Menu_cls::menuF_getMainmenuStatus(void)
//{
//    return(main_menu_status_b);
//}

// ---------------------------------------------------------------------------
// Cyclic function
void Menu::menuF_Cyclic(void)
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
void Menu::menuLF_checkMainMenuDebounceTime(void)
{
    if(main_menu_entry_exit_debounce_time_ >= MENU_MAIN_DEBOUNCE_TIME_K)
    {
        if(main_menu_entry_exit_b_ != true)
        { 
            // main menu entry/exit is triggered.
            main_menu_entry_exit_b_ = true;

            if(main_menu_status_b_ != false)
            {
                // main menu is de-activated. Can process the browse menu in this state.
                main_menu_status_b_ = false;
            }
            else
            {
                // main menu is activated. Can't process the browse menu in this state.
                main_menu_status_b_ = true;
            }
        }
        else
        {
            // no action
        }    
    }
    else
    {
        main_menu_entry_exit_debounce_time_++;
    }
}

// ---------------------------------------------------------------------------
// Reading and checking main menu switch state
void Menu::menuLF_checkMenuSwitchStatus(void)
{
    bool tmp_b;


    tmp_b = rte_ivar.Rte_Read_Hal_DI_MenuSwitch(); 

    if((bool)MENU_SWITCH_PRESSED_E == tmp_b)
    {
        menuLF_checkMainMenuDebounceTime();

        if(main_menu_status_b_ != true)
        { 
            // main menu is not activated. Possible to do menu browsing.
            menu_switch_browse_state_e_ = MENU_SWITCH_PRESSED_E;
        }
    }
    else
    {
        menu_switch_browse_state_e_ = MENU_SWITCH_NOT_PRESSED_E;

        if(main_menu_entry_exit_b_ != false)
        {
            // reset main menu entry/exit status
            main_menu_entry_exit_b_ = false;

            // reset the counter
            main_menu_entry_exit_debounce_time_ = 0u;
        }
        else
        {
            // no action
        }
    }
}

// ---------------------------------------------------------------------------
// Browse menu options checking and assignment
void Menu::menuLF_browseMenu(void)
{
    switch(menu_switch_browse_state_e_)
    {
        case MENU_SWITCH_PRESSED_E:
        {
            browse_menu_status_b_ = true;
            break;
        }
        case MENU_SWITCH_NOT_PRESSED_E:
        {
            if(browse_menu_status_b_ != false)
            {
                // reset the browse_menu_status_b and wait for new pressed
                browse_menu_status_b_ = false;

                // menu switch is pressed and un-pressed. increment browse counter
                browse_menu_ctr_++;
                if(browse_menu_ctr_ >= MENU_DISPLAY_MAX_E)
                {
                    // reset the browse counter
                    browse_menu_ctr_ = 0u;
                }
                else
                {
                    // no action
                }
                 
                browse_menu_e_ = (enum browse_menu_et)browse_menu_ctr_;
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
//void Menu::menuLF_mainMenu(void)
//{
//}

// ---------------------------------------------------------------------------
// Update Rte data
void Menu::menuLF_updateRteData(void)
{
    // Update Rte data for browse menu
    rte_ivar.Rte_Write_Menu_BrowseMenu(browse_menu_e_);

    // Update Rte data for main menu
    rte_ivar.Rte_Write_Menu_MainMenu(main_menu_e_);
}