/*
 Add description
 */

#include "RE_Transceiver.h"
#include "RE_Rte.h"
#include <SPI.h>
#include "RF24.h"

/* formula: Freq(selected) = 2400 + CH(selected)
   Channel is from 0 to 125. Recommended is from channel 25 and above as lower channel is used for wifi.
*/
#define TRANSCEIVER_CHANNEL_FREQUENCY_K   25 // channel is 26. just set 25 since the SW library only need this info.

//! Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 RE_radio(TRANSCEIVER_CE_K,TRANSCEIVER_CSN_K);

const uint8_t address_u8[6] = "2RE5t";

/*
 */
RE_Transceiver_cls::RE_Transceiver_cls()
{
}

/* 
 */
void RE_Transceiver_cls::transceiverF_Init(void)
{
    //! start radio
    RE_radio.begin();

    //! Set PA(Power Amplifier)
    RE_radio.setPALevel(RF24_PA_MAX/*RF24_PA_LOW*/); // RF24_PA_MAX = 0dBm

    //! Set channel frequency
    //RE_radio.setChannel(108/*TRANSCEIVER_CHANNEL_FREQUENCY_K*/);

    //while( (RE_radio.setDataRate(RF24_1MBPS)) != true ){/* wait until it sets successfully. */} // sentivity of -94dBm. lowest sensitivity is better.
    

    //! Open a writing and reading pipe on each radio, with opposite addresses
    RE_radio.openWritingPipe(address_u8);

    //! Stop receiving anything
    RE_radio.stopListening();

    txrx_status_b = 0u;
}

#if 0
/*
 */
bool RE_Transceiver_cls::transceiverF_getStatus(void)
{
    return(txrx_status_b);
}

/*
 */
void RE_Transceiver_cls::transceiverF_RTE_Read_JoyStickThrottleFwdBckwd(uint8_t throttle_u8)
{
    tx_data_s.joystick_throttle_fwd_bckwd_u8 = throttle_u8;
}

/*
 */
void RE_Transceiver_cls::transceiverF_RTE_Read_JoyStickThrottleLeftRight(uint8_t throttle_u8)
{
    tx_data_s.joystick_throttle_left_right_u8 = throttle_u8;
}

/*
 */
void RE_Transceiver_cls::transceiverF_RTE_Read_JoyStickControlFwdBckwd(enum direction_et control_e)
{
    tx_data_s.joystick_ctrl_fwd_bckwd_u8 = (uint8_t)control_e;
} 

/*
 */
void RE_Transceiver_cls::transceiverF_RTE_Read_JoyStickControlLeftRight(enum direction_et control_e)
{
    tx_data_s.joystick_throttle_left_right_u8 = (uint8_t)control_e;
}  

/*
 */
void RE_Transceiver_cls::tranceiverF_RTE_Read_Poti(uint8_t poti_u8)
{
    tx_data_s.potentiometer1_u8 = poti_u8;
}

/*
 */
void RE_Transceiver_cls::transceiverF_RTE_Read_SwitchState(enum digitalIn_et id_e, bool state_b)
{
    switch(id_e)
    {
        case HAL_DI_SWITCH1_E:
        {
            tx_data_s.switch1_u8 = state_b;
            break;
        }
        case HAL_DI_SWITCH2_E:
        {
            tx_data_s.switch2_u8 = state_b;
            break;
        }
        case HAL_DI_SWITCH3_E:
        {
            tx_data_s.switch3_u8 = state_b;
            break;
        }
        case HAL_DI_SWITCH4_E:
        {
            tx_data_s.switch4_u8 = state_b;
            break;
        }
        default:
        {
            break;
        }                        
    }
} 
#endif

/*
 */
void RE_Transceiver_cls::transceiverF_Cyclic(void)
{
    //! First, collect the data to be transmitted.
    transceiverLF_collectData();

    //! Send the data
    transceiverLF_Send();

    //! Check any received data
    //transceiverLF_Receive();
}

/**********************************************************************************/

/*
 */
void RE_Transceiver_cls::transceiverLF_collectData(void)
{
    tx_data_s.joystick_throttle_fwd_bckwd_u8 = Rte_cls.Rte_Read_JoyStick_ThrottleFwdBckwrd();

    tx_data_s.joystick_throttle_left_right_u8 = Rte_cls.Rte_Read_JoyStick_ThrottleLeftRight();

    tx_data_s.joystick_ctrl_fwd_bckwd_u8 = (uint8_t)Rte_cls.Rte_Read_JoyStick_ControlFwdBckwrd();

    tx_data_s.joystick_ctrl_left_right_u8 = (uint8_t)Rte_cls.Rte_Read_JoyStick_ControlLeftRight();

    tx_data_s.potentiometer1_u8 = Rte_cls.Rte_Read_Potentiometer_Poti1Data();

    tx_data_s.switch1_u8 = Rte_cls.Rte_Read_Hal_DI_Switch1();

    tx_data_s.switch2_u8 = Rte_cls.Rte_Read_Hal_DI_Switch2();

    tx_data_s.switch3_u8 = Rte_cls.Rte_Read_Hal_DI_Switch3();

    tx_data_s.switch4_u8 = Rte_cls.Rte_Read_Hal_DI_Switch4();
}

/*
 */
void RE_Transceiver_cls::transceiverLF_incrementTimeoutCounter(void)
{
    if(timeout_ctr_u8 >= TRANSCEIVER_TIMEOUT_K)
    {
        // radio timeout
        txrx_status_b = 0u;
        Rte_cls.Rte_Write_Transceiver_Status(txrx_status_b);
    }
    else
    {
        timeout_ctr_u8++;
    }
}

/*
 */
void RE_Transceiver_cls::transceiverLF_decrementTimeoutCounter(void)
{
    if(0u == timeout_ctr_u8)
    {
        // transmission is okay.
        txrx_status_b = 1u;
        Rte_cls.Rte_Write_Transceiver_Status(txrx_status_b);
    }
    else
    {
        timeout_ctr_u8--;
    }
}

/*
 */
void RE_Transceiver_cls::transceiverLF_Send(void)
{
    //! First, stop listening so we can talk.
    RE_radio.stopListening();   

    //! Send the data
    if (RE_radio.write( &tx_data_s, sizeof(tx_data_s)) )
    { //! Data is transmitted successfully.
        // start decrementing the timeout counter
        transceiverLF_decrementTimeoutCounter();
    }   
    else
    { //! Data is not transmitted successfully.
        // start incrementing the timeout counter
        transceiverLF_incrementTimeoutCounter();
    }
                                  
}

/*
 */
void RE_Transceiver_cls::transceiverLF_Receive(void)
{

}