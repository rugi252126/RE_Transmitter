#ifndef RE_TRANSCEIVER_H_
#define RE_TRANSCEIVER_H_

#include "RE_Hal.h"
#include "RE_JoyStick.h"

#define TRANSCEIVER_CYCLIC_TIME_K       200u//50u // 200ms
#define TRANSCEIVER_TIMEOUT_K           (1000u/TRANSCEIVER_CYCLIC_TIME_K) // 1sec.

//! For nRF24L01
#define TRANSCEIVER_CSN_K               8 // D08
#define TRANSCEIVER_CE_K                7 // D07

class RE_Transceiver_cls
{
public:

    /*
     */
    RE_Transceiver_cls();

    /*
     */
    void transceiverF_Init(void);

    /*
     */
    void transceiverF_setAddress(uint8_t address_u8);

#if 0
    /*
     */
    bool transceiverF_getStatus(void);

    /*
     */
    void transceiverF_RTE_Read_JoyStickThrottleFwdBckwd(uint8_t throttle_u8);

     /*
     */
    void transceiverF_RTE_Read_JoyStickThrottleLeftRight(uint8_t throttle_u8);   

    /*
     */
    void transceiverF_RTE_Read_JoyStickControlFwdBckwd(enum direction_et control_e);  

    /*
     */
    void transceiverF_RTE_Read_JoyStickControlLeftRight(enum direction_et control_e);  

    /*
     */
    void tranceiverF_RTE_Read_Poti(uint8_t poti_u8);

    /*
     */
    void transceiverF_RTE_Read_SwitchState(enum digitalIn_et id_e, bool state_b);        
#endif

    /*
     */
    void transceiverF_Cyclic(void);

protected:

    bool    txrx_status_b;
    uint8_t timeout_ctr_u8;

    struct tx_data_st
    {
        byte joystick_throttle_fwd_bckwd_u8;
        byte joystick_throttle_left_right_u8;
        byte joystick_ctrl_fwd_bckwd_u8;
        byte joystick_ctrl_left_right_u8;
        byte potentiometer1_u8;
        byte switch1_u8;
        byte switch2_u8;
        byte switch3_u8;
        byte switch4_u8;
    };
    struct tx_data_st tx_data_s;

private:
   
    /*
     */
    void transceiverLF_collectData(void);

    /*
     */
    void transceiverLF_incrementTimeoutCounter(void);

    /*
     */
    void transceiverLF_decrementTimeoutCounter(void);    

    /*
     */
    void transceiverLF_Send(void);

    /*
     */
    void transceiverLF_Receive(void);

}; // class RE_Transceiver_cls

#endif // RE_TRANSCEIVER_H_