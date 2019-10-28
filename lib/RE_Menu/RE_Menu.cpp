/*
 Add description
 */

//#include "RE_Rte.h"
#include "RE_Menu.h"
//#include "RE_Hal.h"


/*
 */
RE_Menu_cls::RE_Menu_cls()
{

}

/*
 */
bool RE_Menu_cls::menuF_getMainmenuStatus(void)
{
    return(main_menu_status_b);
}

/*
 */
//enum browse_menu_et RE_Menu_cls::menuF_getBrowseMenu(void)
//{
//    return(browse_menu_e);
//}

/*
 */
//enum main_menu_et RE_Menu_cls::menuF_getMainMenu(void)
//{
 //   return(main_menu_e);
//}

/*
 */
//void RE_Menu_cls::menuF_RTE_Read_MenuSwitchState(bool state_b)
//{
 //   RTE_Read_menu_switch_state_b = state_b;
//}

/*
 */
void RE_Menu_cls::menuF_Cyclic(void)
{
    //! first, get the menu switch status
    menuLF_checkMenuSwitchStatus();  

    //! execute main menu or browse menu
    menuLF_browseMenu();

    //menuLF_mainMenu();

    // Update Rte data
    menuLF_updateRteData();

}

/***********************************************************************/

/*
 */
void RE_Menu_cls::menuLF_checkMainMenuDebounceTime(void)
{
    if(main_menu_entry_exit_debounce_time_u16 >= MENU_MAIN_DEBOUNCE_TIME_K)
    {
        if(main_menu_entry_exit_b != 1)
        { // main menu entry/exit is triggered.
            main_menu_entry_exit_b = 1u;

            if(main_menu_status_b != 0)
            {
                // main menu is de-activated. Can process the browse menu in this state.
                main_menu_status_b = 0u;
            }
            else
            {
                // main menu is activated. Can't process the browse menu in this state.
                main_menu_status_b = 1u;
            }
        }
        else
        {
            /* no action */
        }    
    }
    else
    {
        main_menu_entry_exit_debounce_time_u16++;
    }
}

/*
 */
void RE_Menu_cls::menuLF_checkMenuSwitchStatus(void)
{
    bool tmp_b;


    tmp_b = Rte_cls.Rte_Read_Hal_DI_MenuSwitch(); //Rte_cls.Rte_Read_SwitchIn_MenuSwitch(); //RTE_Read_menu_switch_state_b; // switchIn_cls.switchInF_getSwitchState(HAL_DI_MENU_SWITCH_E);

    if(MENU_SWITCH_PRESSED_E == tmp_b)
    {
        menuLF_checkMainMenuDebounceTime();

        if(main_menu_status_b != 1)
        { // main menu is not activated. Possible to do menu browsing.
            menu_switch_browse_state_e = MENU_SWITCH_PRESSED_E;
        }
    }
    else
    {
        menu_switch_browse_state_e = MENU_SWITCH_NOT_PRESSED_E;

        if(main_menu_entry_exit_b != 0u)
        {
            // reset main menu entry/exit status
            main_menu_entry_exit_b = 0u;

            // reset the counter
            main_menu_entry_exit_debounce_time_u16 = 0u;
        }
        else
        {
            /* no action */
        }
        
    }
    
}

/*
 */
void RE_Menu_cls::menuLF_browseMenu(void)
{
    switch(menu_switch_browse_state_e)
    {
        case MENU_SWITCH_PRESSED_E:
        {
            browse_menu_status_b = 1u;
            break;
        }
        case MENU_SWITCH_NOT_PRESSED_E:
        {
            if(browse_menu_status_b != 0u)
            {
                // reset the browse_menu_status_b and wait for new pressed
                browse_menu_status_b = 0u;

                // menu switch is pressed and un-pressed. increment browse counter
                browse_menu_ctr_u8++;
                if(browse_menu_ctr_u8 >= MENU_DISPLAY_MAX_E)
                {
                    // reset the browse counter
                    browse_menu_ctr_u8 = 0u;
                }
                else
                {
                    /* no action */
                }
                 
                browse_menu_e = (enum browse_menu_et)browse_menu_ctr_u8;
            }
            else
            {
                /* no action */
            }
            
            break;
        }
        default:
        {
            break;
        }
    }
}

/*
 */
void RE_Menu_cls::menuLF_mainMenu(void)
{

}

/*
 */
void RE_Menu_cls::menuLF_updateRteData(void)
{
    Rte_cls.Rte_Write_Menu_BrowseMenu(browse_menu_e);

    Rte_cls.Rte_Write_Menu_MainMenu(main_menu_e);
}