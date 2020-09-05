/**
    @file RE_SwitchIn.cpp

    @brief
    This implements the switches(e.g. push button, toggle) control in the controller.
    Currently, the module only covered digital input switches. R-coded switches is not
    yet covered in the module. It depends on the HW design, R-coded switches can also
    be covered here.

    @author Alfonso, Rudy Manalo
    @version 
*/

#include "RE_SwitchIn.h"


// CLASS CONSTRUCTOR
// ---------------------------------------------------------------------------
SwitchIn::SwitchIn()
{
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void SwitchIn::switchInF_Init(void)
{
    uint8_t idx;

    // initialize into default value/state
    for(idx=0u; idx < SWITCHIN_NUM_K; idx++)
    {
        rte_read_switchState_b_[idx]   = false;
        switch_state_b_[idx]           = false;
        switch_state_raw_b_[idx]       = false;
        switch_debounce_time_[idx] = 0u;   
    }
}

// ---------------------------------------------------------------------------
// Cyclic function
void SwitchIn::switchInF_Cyclic(void)
{
    uint8_t idx=0u;

    // Get Rte data
    switchInLF_getRteData();

    for(idx=0u; idx < SWITCHIN_NUM_K; idx++)
    {
        // first, get the switch state
        switchInLF_getSwitchStatus(idx);

        // and then apply the debounce time to statiblize the switch state
        switchInLF_stabilizeSwitchStatus(idx);
    }

    // Update Rte data
    switchInLF_updateRteData();
}

// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Read hardware switch state from Rte
void SwitchIn::switchInLF_getRteData(void)
{
    #if (SWITCHIN_NUM_K > 0u)
    rte_read_switchState_b_[0] = rte_ivar.Rte_Read_Hal_DI_Switch1();
    #endif

    #if (SWITCHIN_NUM_K > 1u)
    rte_read_switchState_b_[1] = rte_ivar.Rte_Read_Hal_DI_Switch2();
    #endif

    #if (SWITCHIN_NUM_K > 2u)
    rte_read_switchState_b_[2] = rte_ivar.Rte_Read_Hal_DI_Switch3();
    #endif

    #if (SWITCHIN_NUM_K > 3u)
    rte_read_switchState_b_[3] = rte_ivar.Rte_Read_Hal_DI_Switch4();
    #endif

    #if (SWITCHIN_NUM_K > 4u)
    rte_read_switchState_b_[4] = rte_ivar.Rte_Read_Hal_DI_MenuSwitch();
    #endif        
}

// ---------------------------------------------------------------------------
// Check if switch state is changed
void SwitchIn::switchInLF_getSwitchStatus(uint8_t idx)
{
    bool tmp_b;

    tmp_b = rte_read_switchState_b_[idx]; 
    if(tmp_b != switch_state_raw_b_[idx])
    {
        switch_state_raw_b_[idx] = tmp_b;    // switch state is changed.
        switch_debounce_time_[idx] = 0u; // reset debounce time to stabilize the new state
    }
    else
    {
        // no action
    }
    
}

// ---------------------------------------------------------------------------
// Stabilize the switch state
void SwitchIn::switchInLF_stabilizeSwitchStatus(uint8_t idx)
{
    switch(idx)
    {
        case SWITCHIN_SWS1_E:
        case SWITCHIN_SWS2_E:
        case SWITCHIN_SWS3_E:
        case SWITCHIN_SWS4_E:
        {
            if(switch_debounce_time_[idx] >= SWITCHIN_TOGGLE_PUSH_BUTTON_SWS_DEBOUNCE_TIME_K)
            {
                // Debounce time is finished. It is safe to assign the new switch state.
                switch_state_b_[idx] = switch_state_raw_b_[idx];
            }
            else
            { 
                switch_debounce_time_[idx]++;
            }
            break;
        }
        case SWITCHIN_MENU_SWS_E:
        {
            if(switch_debounce_time_[idx] >= SWITCHIN_MENU_SWS_DEBOUNCE_TIME_K)
            {
                // Debounce time is finished. It is safe to assign the new switch state.
                switch_state_b_[idx] = switch_state_raw_b_[idx];
            }
            else
            { 
                switch_debounce_time_[idx]++;
            }
            break;
        }
        default:
        {
            // no action
            break;
        }
    }
}

// ---------------------------------------------------------------------------
// Update the Rte information with the latest and stable switch state
void SwitchIn::switchInLF_updateRteData(void)
{
    #if (SWITCHIN_NUM_K > 0u)
    rte_ivar.Rte_Write_SwitchIn_Switch1(switch_state_b_[0]);
    #endif

    #if (SWITCHIN_NUM_K > 1u)
    rte_ivar.Rte_Write_SwitchIn_Switch2(switch_state_b_[1]);
    #endif

    #if (SWITCHIN_NUM_K > 2u)
    rte_ivar.Rte_Write_SwitchIn_Switch3(switch_state_b_[2]);
    #endif

    #if (SWITCHIN_NUM_K > 3u)
    rte_ivar.Rte_Write_SwitchIn_Switch4(switch_state_b_[3]);
    #endif

    #if (SWITCHIN_NUM_K > 4u)
    rte_ivar.Rte_Write_SwitchIn_MenuSwitch(switch_state_b_[4]);
    #endif                   
}