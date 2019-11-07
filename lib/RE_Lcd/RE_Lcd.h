/**
    @file RE_Lcd.h

    @brief
    This implements the information need to be displayed on the LCD like the 
    radio transceiver status, controller mode, battery voltage and status, throttle speed,
    direction, etc..
    This module has direct interface to the LCD library. Setting-up of LCD will be done here. 

    @author Alfonso, Rudy Manalo
    @version
*/

#ifndef RE_LCD_H_
#define RE_LCD_H_

#include "RE_Rte.h"


/*!
    @defined 
    @abstract Module macro definitions
    @discussion Defines the module cyclic time, LCD address and size of rows and columns.
*/
#define LCD_CYCLIC_TIME_K         200u    // 200ms
#define LCD_I2C_ADDRESS_K         0x27    // LDC I2C address
#define LCD_NUM_OF_ROWS_K         4       // LCD number of rows
#define LCD_NUM_OF_COLUMNS_K      20      // LCD number of columns


class RE_Lcd_cls
{
public:

    /*!
        @method
        @abstract RE_Lcd abstract constructor
        @discussion RE_Lcd class abstract constructor needed to create the abstract base class.
    */
    RE_Lcd_cls();

    /*!
        @function
        @abstract Module initialization
        @discussion It sets the initial state of the LCD display.

        @param  none
        @return none
    */
    void lcdF_Init();


    /*!
        @function
        @abstract Module cyclic function
        @discussion Tasks within the module that need to be called cyclically will be done here.

        @param  none
        @return none
    */
    void lcdF_Cyclic(void);

protected:

    enum browse_menu_et   copy_browse_menu_e; // holds the browse menu current state

private:

    /*!
        @function
        @abstract Browse menu
        @discussion Displays information under browse menu

        @param  none
        @return none
    */
    void lcdLF_browseMenuDisplay(void);

    /*!
        @function
        @abstract Main menu
        @discussion Displays information under main menu

        @param  none
        @return none
    */
    void lcdLF_mainMenuDisplay(void);

}; // class RE_Lcd_cls


#endif // RE_LCD_H_