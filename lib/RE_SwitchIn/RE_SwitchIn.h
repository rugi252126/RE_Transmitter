#ifndef RE_SWITCHIN_H_
#define RE_SWITCHIN_H_

#include "Arduino.h"
#include "RE_Hal.h"

#define SWITCHIN_TASK_IN_MS_K                             200u//10u                           // 200ms
#define SWITCHIN_TOGGLE_PUSH_BUTTON_SWS_DEBOUNCE_TIME_K   (200u/SWITCHIN_TASK_IN_MS_K) //(400u/SWITCHIN_TASK_IN_MS_K)  // 400ms
#define SWITCHIN_MENU_SWS_DEBOUNCE_TIME_K                 (200u/SWITCHIN_TASK_IN_MS_K) //(400u/SWITCHIN_TASK_IN_MS_K)  // 400ms
#define SWITCHIN_NUM_K                                     5u

class RE_SwitchIn_cls
{
    boolean  switch_state_b[HAL_DI_MAX_E];
    boolean  switch_state_raw_b[HAL_DI_MAX_E];
    uint16_t switch_debounce_time_u16[HAL_DI_MAX_E];

public:
    
    /*!

     */
    RE_SwitchIn_cls( );

    /*!
    
    */
    //void switchInF_init(void);

    /*
     */
    //void switchInF_RTE_Read_State(enum digitalIn_et digitalIn_ID_e, bool state_b);

    /*!
     
     */
    //bool switchInF_getSwitchState(enum digitalIn_et digitalIn_e);

    /*!

     */
    void switchInF_Cyclic(void);

protected:
    
    bool read_switchState_b[HAL_DI_MAX_E];
 

private:

    /*!

     */
    void switchInLF_stabilizeSwitchStatus(uint8_t idx);

    /*!

     */
    void switchInLF_getSwitchStatus(uint8_t idx);

    /*
     */
    void switchInLF_getRteData(void);

    /*
     */
    void switchInLF_updateRteData(void);    
}; // end of class RE_SwitchIn_cls

#endif // RE_SWITCHIN_H_