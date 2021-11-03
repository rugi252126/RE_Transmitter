This is a DIY transmitter based on arduino and NRF24L01 transceiver.
=====================================================================

The software in repository is using Arduino nano microcontroller.
The software can able to support any Arduino framework but please keep in mind not to forget
to update the HAL layer in case you are planning to use different microcontroller.
If you look at the Software architecture overview(under \Descriptions\Designs), 
the software components under RE_Rte need to be adapted according to the microcontroller or hardware design.
Mostly, the adaptation will only be done on the microcontroller pins assignments.

How to build the software
=====================================================================
    1) Clone this project to your environment
    2) Install platformIO IDE or integrate it from Visual Studio Code(the most easiest way)
	3) From Visual Studio Code, you can compile the software. You can also upload the firmware to the microcontroller. Debugging using serial monitor is also possible.


![Actual Photo1](https://github.com/rugi252126/RE_Transmitter/blob/master/Descriptions/Prototype/RE_14.JPG?raw=true)

![Actual Photo2](https://github.com/rugi252126/RE_Transmitter/blob/master/Descriptions/Prototype/RE_15.JPG?raw=true)

![Actual Photo3](https://github.com/rugi252126/RE_Transmitter/blob/master/Descriptions/Prototype/RE_17.JPG?raw=true)

![Actual Photo4](https://github.com/rugi252126/RE_Transmitter/blob/master/Descriptions/Prototype/RE_18.JPG?raw=true)

![Actual Photo5](https://github.com/rugi252126/RE_Transmitter/blob/master/Descriptions/Prototype/RE_20.JPG?raw=true)
