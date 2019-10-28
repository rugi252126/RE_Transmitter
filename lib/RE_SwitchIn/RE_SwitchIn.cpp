/*
 TODO: Add description
 */

#include "RE_SwitchIn.h"
#include "RE_Rte.h"


/*

 */
RE_SwitchIn_cls::RE_SwitchIn_cls()
{

}

/*
 */
///void RE_SwitchIn_cls::switchInF_RTE_Read_State(enum digitalIn_et digitalIn_ID_e, bool state_b)
//{
   // RTE_Read_DI_switchState_e[digitalIn_ID_e] = state_b;
//}

/*
 
 */
//bool RE_SwitchIn_cls::switchInF_getSwitchState(enum digitalIn_et digitalIn_e)
//{
    // add an assert?
//    return(switch_state_b[digitalIn_e]);
//}

/* 
 
 */
void RE_SwitchIn_cls::switchInF_Cyclic(void)
{
    uint8_t idx=0u;

    // Get Rte data
    switchInLF_getRteData();

    for(idx=0u; idx < HAL_DI_MAX_E; idx++)
    {
        // first, get the switch state
        switchInLF_getSwitchStatus(idx);

        // and then apply the debounce time to statiblize the switch state
        switchInLF_stabilizeSwitchStatus(idx);
    }

    // Update Rte data
    switchInLF_updateRteData();
}

/*******************************************************************************/

/*

 */
void RE_SwitchIn_cls::switchInLF_getRteData(void)
{
    #if (SWITCHIN_NUM_K > 0u)
    read_switchState_b[0] = Rte_cls.Rte_Read_Hal_DI_Switch1();
    #endif

    #if (SWITCHIN_NUM_K > 1u)
    read_switchState_b[1] = Rte_cls.Rte_Read_Hal_DI_Switch2();
    #endif

    #if (SWITCHIN_NUM_K > 2u)
    read_switchState_b[2] = Rte_cls.Rte_Read_Hal_DI_Switch3();
    #endif

    #if (SWITCHIN_NUM_K > 3u)
    read_switchState_b[3] = Rte_cls.Rte_Read_Hal_DI_Switch4();
    #endif

    #if (SWITCHIN_NUM_K > 4u)
    read_switchState_b[4] = Rte_cls.Rte_Read_Hal_DI_MenuSwitch();
    #endif        
}

/*

 */
void RE_SwitchIn_cls::switchInLF_stabilizeSwitchStatus(uint8_t idx)
{
    switch(idx)
    {
        case HAL_DI_SWITCH1_E:
        case HAL_DI_SWITCH2_E:
        case HAL_DI_SWITCH3_E:
        case HAL_DI_SWITCH4_E:
        {
            if(switch_debounce_time_u16[idx] >= SWITCHIN_TOGGLE_PUSH_BUTTON_SWS_DEBOUNCE_TIME_K)
            {
                // Debounce time is finished. It is safe to assign the new switch state.
                switch_state_b[idx] = switch_state_raw_b[idx];
            }
            else
            { 
                switch_debounce_time_u16[idx]++;
            }
            break;
        }
        case HAL_DI_MENU_SWITCH_E:
        {
            if(switch_debounce_time_u16[idx] >= SWITCHIN_MENU_SWS_DEBOUNCE_TIME_K)
            {
                // Debounce time is finished. It is safe to assign the new switch state.
                switch_state_b[idx] = switch_state_raw_b[idx];
            }
            else
            { 
                switch_debounce_time_u16[idx]++;
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
void RE_SwitchIn_cls::switchInLF_getSwitchStatus(uint8_t idx)
{
    boolean tmp_b;
    //RE_Hal hal_cls;

    tmp_b = read_switchState_b[idx]; // hal_cls.halF_getDI_State((enum digitalIn_et)idx);
    if(tmp_b != switch_state_raw_b[idx])
    {
        switch_state_raw_b[idx] = tmp_b;
        switch_debounce_time_u16[idx] = 0u; // new switch state. reset debounce time to stabilize the state
    }
    else
    {
        /* no action */
    }
    
}

/*
 */
void RE_SwitchIn_cls::switchInLF_updateRteData(void)
{
    #if (SWITCHIN_NUM_K > 0u)
    Rte_cls.Rte_Write_SwitchIn_Switch1(switch_state_b[0]);
    #endif

    #if (SWITCHIN_NUM_K > 1u)
    Rte_cls.Rte_Write_SwitchIn_Switch2(switch_state_b[1]);
    #endif

    #if (SWITCHIN_NUM_K > 2u)
    Rte_cls.Rte_Write_SwitchIn_Switch3(switch_state_b[2]);
    #endif

    #if (SWITCHIN_NUM_K > 3u)
    Rte_cls.Rte_Write_SwitchIn_Switch4(switch_state_b[3]);
    #endif

    #if (SWITCHIN_NUM_K > 4u)
    Rte_cls.Rte_Write_SwitchIn_MenuSwitch(switch_state_b[4]);
    #endif                   
}