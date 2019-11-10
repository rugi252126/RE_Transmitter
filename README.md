This is a DIY transmitter based on arduino and NRF24L01 transceiver.


The software in repository is using Arduino nano microcontroller.
The software can able to support any Arduino framework but please keep in mind not to forget
to update the HAL layer in case you are planning to use different microcontroller.
If you look at the Software architecture overview, the software components under RE_Rte need to be
adapted according to the microcontroller or hardware design.
Mostly, the adaptation will only be done on the microcontroller pins assignments.


Software Architecture Overview
     ________      ___________      _____________      ________      _________      __________________      _____________      ______________________
    |        |    |           |    |             |    |        |    |         |    |                  |    |             |    |                      |
    |  main  |    | RE_Buzzer |    | RE_JoyStick |    | RE_Led |    | RE_Menu |    | RE_Potentiometer |    | RE_SwitchIn |    | RE_VoltageMonitoring |
    |________|    |___________|    |_____________|    |________|    |_________|    |__________________|    |_____________|    |______________________|
         |              |                 |                |             |                  |                     |                       |
	     |              |                 |                |             |                  |                     |                       |
	 ____|______________|_________________|________________|_____________|__________________|_____________________|_______________________|__________
	|                                                                                                                                                |
	|                                                                   RE_Rte                                                                       |
	|________________________________________________________________________________________________________________________________________________|
	         |                                         |                                         |                                          |
	         |                                         |                                         |                                          |
     ________|_______                          ________|_______                          ________|_______                           ________|________
    |                |                        |                |                        |                |                         |                 | 
    |     RE_Hal     |                        |     RE_Lcd     |                        | RE_Transceiver |                         |     RE_Imu      |
    |________________|                        |________________|                        |________________|                         |_________________|
            |                                          |                                         |                                          |
            |                                          |                                         |                                          |
            |                                  ________|_______                          ________|_______                           ________|________
            |                                 |                |                        |                |                         |                 |
            |                                 |  LCD Library   |                        |  nRF24 Library |                         |   I2C Library   |   
            |                                 |________________|                        |________________|                         |_________________|
			|								           |                                         |                                          |
			|								           |                                         |                                          |
	 _______|__________________________________________|_________________________________________|__________________________________________|________
	|                                                                                                                                                |
	|                                                              Arduino Library                                                                   |
	|________________________________________________________________________________________________________________________________________________|	
                                                                           |
                                                                           |
	 ______________________________________________________________________|_________________________________________________________________________
	|                                                                                                                                                |
	|                                                                    MCAL                                                                        |
	|________________________________________________________________________________________________________________________________________________|	
											  