/**
    @file RE_Transceiver.h

    @brief
    The implementation handles the transmission of data before being processed by nRF24L01 library.
    The data being transmitted is a set of collected data from different modules.
    It will take care of the received data as well.
    This module has direct interface to the nRF24L01 library. Setting-up of nRF24L01 will be done here. 

    @author Alfonso, Rudy Manalo
    @version
*/


#ifndef RE_TRANSCEIVER_H_
#define RE_TRANSCEIVER_H_

#include "RE_Rte.h"


/*!
    @defined 
    @abstract Defines module time configuration
    @discussion This constant defines the module cyclic time and transceiver timeout.
    The time is in milli-second form.
*/
#define TRANSCEIVER_CYCLIC_TIME_K       200u                              // 200ms
#define TRANSCEIVER_TIMEOUT_K           (1000u/TRANSCEIVER_CYCLIC_TIME_K) // 1sec.

//! For nRF24L01
/*!
    @defined 
    @abstract Defines the pins for the SPI communication
    @discussion CSN and CE pins definition that will be used in SPI communication.
    Communication between nRF24L01 and microcontroller is done via SPI. 
*/
#define TRANSCEIVER_CSN_K               8 // D08
#define TRANSCEIVER_CE_K                7 // D07


class Transceiver
{
public:

    /*!
        @method
        @abstract Transceiver abstract constructor
        @discussion Transceiver class abstract constructor needed to create the abstract base class.
    */
    Transceiver();

    /*!
        @function
        @abstract Module initialization
        @discussion It sets the initial state of the transceiver.

        @param  none
        @return none
    */
    void transceiverF_Init(void);

    /*!
        @function
        @abstract Module cyclic function
        @discussion Tasks within the module that need to be called cyclically will be done here.

        @param  none
        @return none
    */
    void transceiverF_Cyclic(void);

protected:
    
    bool    txrx_status_b_;   // radio status
    uint8_t timeout_ctr_;     // radio timeout counter

    // data to be transmitted
    struct tx_data_st
    {
        byte joystick_throttle_fwd_bckwd_;   // contains the pwm for throttle forward/backward
        byte joystick_throttle_left_right_;  // contains the pwm for throttle left/right
        byte joystick_ctrl_fwd_bckwd_;       // contains the direction(e.g. forward, backward, neutral)
        byte joystick_ctrl_left_right_;      // contains the direction(e.g. left-turn, right-turn, neutral)
        byte potentiometer1_;                // poti pwm value
        byte switch1_;                       // contains ON/OFF switch information
        byte switch2_;                       // contains ON/OFF switch information
        byte switch3_;                       // contains ON/OFF switch information
        byte switch4_;                       // contains ON/OFF switch information
    };
    struct tx_data_st tx_data_s;

private:
   
    /*!
        @function
        @abstract Data collection
        @discussion Collects the data to be sent. The data will be collected from other modules.

        @param  none
        @return none
    */
    void transceiverLF_collectData(void);

    /*!
        @function
        @abstract Timeout counter increments.
        @discussion The timeout counter will be incremented continously as long as the radio is giving not available status.
        Rte interface will be updated to inform other module regarding the radio status.
    */
    void transceiverLF_incrementTimeoutCounter(void);

    /*!
        @function
        @abstract Timeout counter decrements.
        @discussion The timeout counter will be decremented until it reaches 0 as long as radio connection is okay.
        Rte interface will be updated to inform other module regarding the radio status.
    */
    void transceiverLF_decrementTimeoutCounter(void);    

    /*!
        @function
        @abstract Sending the data
        @discussion Sending the collected data. The data will be transferred first to nRF24L01 library.
        nRF24L01 will handle the actual sending of data.
    */
    void transceiverLF_Send(void);

    /*!
        @function
        @abstract Receiving the data
        @discussion The data will be read from nRF24L01 buffer.
        nRF24L01 will handle the actual reading of data.
    */
    //void transceiverLF_Receive(void);

}; // class Transceiver

#endif // RE_TRANSCEIVER_H_