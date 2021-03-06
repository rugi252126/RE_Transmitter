/**
    @file RE_Transceiver.cpp

    @brief
    The implementation handles the transmission of data before being processed by nRF24L01 library.
    The data being transmitted is a set of collected data from different modules.
    It will take care of the received data as well.
    This module has direct interface to the nRF24L01 library. Setting-up of nRF24L01 will be done here. 

    @author Alfonso, Rudy Manalo
    @version
*/

#include "RE_Transceiver.h"
#include <SPI.h>
#include "RF24.h"

/* Formula: Freq(selected) = 2400 + CH(selected)
   Channel is from 0 to 125. Recommended is from channel 25 and above as lower channel is used for wifi.
*/
// #define TRANSCEIVER_CHANNEL_FREQUENCY_K   108 // just set the number(e.g. 25) since the library only need this information

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8
   Create an instance from class RF24
*/
RF24 RE_radio(TRANSCEIVER_CE_K,TRANSCEIVER_CSN_K);

const uint8_t TXRX_ADDRESS[6] = "2RE5t";


// CLASS CONSTRUCTOR
// ---------------------------------------------------------------------------
Transceiver::Transceiver()
{
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void Transceiver::transceiverF_Init(void)
{
    // start radio
    RE_radio.begin();

    // Set PA(Power Amplifier)
    RE_radio.setPALevel(RF24_PA_MAX); // RF24_PA_MAX = 0dBm

    // Set channel frequency
    // RE_radio.setChannel(TRANSCEIVER_CHANNEL_FREQUENCY_K);

    // while( (RE_radio.setDataRate(RF24_1MBPS)) != true ){/* wait until it sets successfully. */} // sentivity of -94dBm. lowest sensitivity is better.
    

    // Open a writing and reading pipe on each radio, with opposite addresses
    RE_radio.openWritingPipe(TXRX_ADDRESS);

    // Stop receiving anything
    RE_radio.stopListening();

    // set the connection status to NOK by default
    txrx_status_b_ = false;
}

// ---------------------------------------------------------------------------
// Cyclic function
void Transceiver::transceiverF_Cyclic(void)
{
    // First, collect the data to be transmitted.
    transceiverLF_collectData();

    // Send the data
    transceiverLF_Send();

    // Check any received data
    // transceiverLF_Receive();
}

// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Collection of data from other modules via Rte
void Transceiver::transceiverLF_collectData(void)
{
    tx_data_s.joystick_throttle_fwd_bckwd_ = rte_ivar.Rte_Read_JoyStick_ThrottleFwdBckwrd();

    tx_data_s.joystick_throttle_left_right_ = rte_ivar.Rte_Read_JoyStick_ThrottleLeftRight();

    tx_data_s.joystick_ctrl_fwd_bckwd_ = (uint8_t)rte_ivar.Rte_Read_JoyStick_ControlFwdBckwrd();

    tx_data_s.joystick_ctrl_left_right_ = (uint8_t)rte_ivar.Rte_Read_JoyStick_ControlLeftRight();

    tx_data_s.potentiometer1_ = rte_ivar.Rte_Read_Potentiometer_Poti1Data();

    tx_data_s.switch1_ = rte_ivar.Rte_Read_Hal_DI_Switch1();

    tx_data_s.switch2_ = rte_ivar.Rte_Read_Hal_DI_Switch2();

    tx_data_s.switch3_ = rte_ivar.Rte_Read_Hal_DI_Switch3();

    tx_data_s.switch4_ = rte_ivar.Rte_Read_Hal_DI_Switch4();
}

// ---------------------------------------------------------------------------
// Increments radio timeout counter
void Transceiver::transceiverLF_incrementTimeoutCounter(void)
{
    if(timeout_ctr_ >= TRANSCEIVER_TIMEOUT_K)
    {
        // radio connection is not okay.
        txrx_status_b_ = false;
        rte_ivar.Rte_Write_Transceiver_Status(txrx_status_b_);
    }
    else
    {
        timeout_ctr_++;
    }
}

// ---------------------------------------------------------------------------
// Decrements radio timeout counter
void Transceiver::transceiverLF_decrementTimeoutCounter(void)
{
    if(0u == timeout_ctr_)
    {
        // radio connection is okay.
        txrx_status_b_ = true;
        rte_ivar.Rte_Write_Transceiver_Status(txrx_status_b_);
    }
    else
    {
        timeout_ctr_--;
    }
}

// ---------------------------------------------------------------------------
// Sending of collected data to nRF24L01 library
void Transceiver::transceiverLF_Send(void)
{
    // First, stop listening so we can talk.
    RE_radio.stopListening();   

    // Send the data
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

// ---------------------------------------------------------------------------
// Reading of data from nRF24L01 library
//void RE_Transceiver_cls::transceiverLF_Receive(void)
//{
//}