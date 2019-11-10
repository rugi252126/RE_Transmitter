/**
    @file RE_Lcd.cpp

    @brief
    This implements the information need to be displayed on the LCD like the 
    radio transceiver status, controller mode, battery voltage and status, throttle speed,
    direction, etc..
    This module has direct interface to the LCD library. Setting-up of LCD will be done here. 

    @author Alfonso, Rudy Manalo
    @version
*/

#include "RE_Lcd.h"
#include "logistic_data.h"
#include "dataset.h"
#include <Wire.h> // for I2C communication
#include <LiquidCrystal_I2C.h>


// LCD class object declaration and I2C pins declaration
LiquidCrystal_I2C lcd_display(LCD_I2C_ADDRESS_K, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// CLASS CONSTRUCTORS
// ---------------------------------------------------------------------------
RE_Lcd_cls::RE_Lcd_cls()
{
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------
// Module initialization
void RE_Lcd_cls::lcdF_Init(void)
{
    // Set LCD colum and row size
    lcd_display.begin(LCD_NUM_OF_COLUMNS_K,LCD_NUM_OF_ROWS_K),

    // Set backlight ON
    lcd_display.backlight();

    // Display the welcome screen during start-up
    lcd_display.setCursor(6,1);
    lcd_display.print("Welcome");
    lcd_display.setCursor(3,2);
    lcd_display.print("RE Transmitter");
    delay(3000);    

    // Initialize the current browse menu state to invalid
    copy_browse_menu_e = MENU_DISPLAY_MAX_E;
    diplay_refresh_time_u8 = 0u;
}

// ---------------------------------------------------------------------------
// Cyclic function
void RE_Lcd_cls::lcdF_Cyclic(void)
{
    //if(get Rte info to check menu status)
    //{ //! main menu is active.
        //lcdLF_mainMenuDisplay();
    //}
    //else
    //{ //! main menu is not active. browse menu is possible.
        lcdLF_browseMenuDisplay();
    //}
}

// PRIVATE METHODS
// ---------------------------------------------------------------------------
// Browse menu - General information display
void RE_Lcd_cls::lcdLF_generalInfoDisplay(void)
{
    bool                     tmp_b;
    enum mode_et             tmp_mode_e;

    // Connection status
    lcd_display.setCursor(0,0);
    lcd_display.print("CONNECTION: ");
    tmp_b = Rte_cls.Rte_Read_Transceiver_Status();
    if(tmp_b != false)
    {
        lcd_display.setCursor(12,0);
        lcd_display.print("OK ");
    }
    else
    {
        lcd_display.setCursor(12,0);
        lcd_display.print("NOK");                             
    }
            
    // Controller mode
    lcd_display.setCursor(0,2);
    lcd_display.print("MODE: "); 
    tmp_mode_e = Rte_cls.Rte_Read_JoyStick_ControllerMode();
    if(tmp_mode_e != MODE1_E)
    { //! Mode2
        lcd_display.setCursor(6,2);
        lcd_display.print("Mode2"); 
    }
    else
    { //! Mode1
        lcd_display.setCursor(6,2);
        lcd_display.print("Mode1");                
    } 
}

// ---------------------------------------------------------------------------
// Browse menu - Voltage information display
void RE_Lcd_cls::lcdLF_voltageInfoDisplay(void)
{
    enum voltage_status_et   tmp_volt_stat_e;
    float                    tmp_volt_disp_f;

    tmp_volt_disp_f = Rte_cls.Rte_Read_VoltageMonitoring_ActualVoltage();
    lcd_display.setCursor(0,0);
    lcd_display.print("VOLTAGE:     ");
    lcd_display.setCursor(9,0);
    lcd_display.print(tmp_volt_disp_f); 
    lcd_display.setCursor(13,0);
    lcd_display.print("V");             

    // voltage status(normal, low, critical)
    lcd_display.setCursor(0,2);  
    lcd_display.print("STATUS:            "); 

    tmp_volt_stat_e = Rte_cls.Rte_Read_VoltageMonitoring_VoltageStatus();
    if (VOLT_NORMAL_E == tmp_volt_stat_e)
    {
        lcd_display.setCursor(8,2);  
        lcd_display.print("Normal");
        lcd_display.setCursor(8,3);  
        lcd_display.print("           ");                                  
    }
    else if(VOLT_LOW_E == tmp_volt_stat_e)
    {
        lcd_display.setCursor(8,2);  
        lcd_display.print("Low Battery");  
        lcd_display.setCursor(8,3);  
        lcd_display.print("           ");                                
    }
    else
    {
        lcd_display.setCursor(8,2);  
        lcd_display.print("Critical");  
        lcd_display.setCursor(8,3);  
        lcd_display.print("Low Battery");                  
    }  
}

// ---------------------------------------------------------------------------
// Browse menu - JoyStick information display
void RE_Lcd_cls::lcdLF_joyStickInfoDisplay(void)
{
    uint8_t              tmp_u8;
    enum direction_et    tmp_dir_e;

    // Throttle forward and backward
    tmp_u8 = Rte_cls.Rte_Read_JoyStick_ThrottleFwdBckwrd();
    lcd_display.setCursor(0,0);
    lcd_display.print("THROTTLE-Y:         "); 
    lcd_display.setCursor(12,0);
    lcd_display.print(tmp_u8);                
    if(LCD_NUM_DIGIT_CHECK_K == (tmp_u8/LCD_NUM_DIGIT_CHECK_K))
    {
        
        lcd_display.setCursor(15,0);
        lcd_display.print("%");                 
    }
    else
    {                    
        lcd_display.setCursor(14,0);
        lcd_display.print("%");   
    }
    
    // Throttle left and right
    tmp_u8 = Rte_cls.Rte_Read_JoyStick_ThrottleLeftRight();
    lcd_display.setCursor(0,1);
    lcd_display.print("THROTTLE-X:         ");
    lcd_display.setCursor(12,1);
    lcd_display.print(tmp_u8); 
    if(LCD_NUM_DIGIT_CHECK_K == (tmp_u8/LCD_NUM_DIGIT_CHECK_K))
    {
        
        lcd_display.setCursor(15,1);
        lcd_display.print("%");                 
    }
    else
    {                    
        lcd_display.setCursor(14,1);
        lcd_display.print("%");   
    }       

    // Control forward and backward 
    tmp_dir_e = Rte_cls.Rte_Read_JoyStick_ControlFwdBckwrd();
    lcd_display.setCursor(0,2);
    lcd_display.print("CONTROL-Y:          ");
    if(JS_OFF_E == tmp_dir_e) 
    {
        lcd_display.setCursor(12,2);
        lcd_display.print("Neutral");
    }
    else if(JS_FORWARD_E == tmp_dir_e) 
    {
        lcd_display.setCursor(12,2);
        lcd_display.print("Forward");                
    }
    else if(JS_BACKWARD_E == tmp_dir_e) 
    {
        lcd_display.setCursor(12,2);
        lcd_display.print("Backward");                 
    }
    else
    {
        // no action
    }
    
    // Control left and right
    tmp_dir_e = Rte_cls.Rte_Read_JoyStick_ControlLeftRight();
    lcd_display.setCursor(0,3);
    lcd_display.print("CONTROL-X:          ");
    lcd_display.setCursor(12,3); 
    if(JS_OFF_E == tmp_dir_e) 
    {
        lcd_display.setCursor(12,3);
        lcd_display.print("Neutral");
    }
    else if(JS_LEFT_TURN_E == tmp_dir_e) 
    {
        lcd_display.setCursor(12,3);
        lcd_display.print("L-Turn");                
    }
    else if(JS_RIGHT_TURN_E == tmp_dir_e) 
    {
        lcd_display.setCursor(12,3);
        lcd_display.print("R-Turn");                 
    }
    else
    {
        // no action
    }   
}

// ---------------------------------------------------------------------------
// Browse menu - JoyStick information display
void RE_Lcd_cls::lcdLF_switchInfoDisplay(void)
{
    bool tmp_b;

    // Switch 1
    tmp_b = Rte_cls.Rte_Read_SwitchIn_Switch1();
    lcd_display.setCursor(0,0);
    lcd_display.print("SWITCH1:      ");
    if(tmp_b != false)
    {
        lcd_display.setCursor(9,0);
        lcd_display.print("OFF");                
    }
    else
    {
        lcd_display.setCursor(9,0);
        lcd_display.print("ON");     
    }
    
    // Switch 2
    tmp_b = Rte_cls.Rte_Read_SwitchIn_Switch2();
    lcd_display.setCursor(0,1);
    lcd_display.print("SWITCH2:      ");
    if(tmp_b != false)
    {
        lcd_display.setCursor(9,1);
        lcd_display.print("OFF");                
    }
    else
    {
        lcd_display.setCursor(9,1);
        lcd_display.print("ON");     
    }            
    
    // Switch 3
    tmp_b = Rte_cls.Rte_Read_SwitchIn_Switch3();
    lcd_display.setCursor(0,2);
    lcd_display.print("SWITCH3:       ");
    if(tmp_b != false)
    {
        lcd_display.setCursor(9,2);
        lcd_display.print("NPSD");                
    }
    else
    {
        lcd_display.setCursor(9,2);
        lcd_display.print("PSD");     
    }          

    // Switch 4
    tmp_b = Rte_cls.Rte_Read_SwitchIn_Switch4();
    lcd_display.setCursor(0,3);
    lcd_display.print("SWITCH4:      ");
    if(tmp_b != false)
    {
        lcd_display.setCursor(9,3);
        lcd_display.print("NPSD");                
    }
    else
    {
        lcd_display.setCursor(9,3);
        lcd_display.print("PSD");     
    }  
}

// ---------------------------------------------------------------------------
// Browse menu - Potentiometer information display
void RE_Lcd_cls::lcdLF_potiInfoDisplay(void)
{
    uint8_t tmp_u8;

    tmp_u8 = Rte_cls.Rte_Read_Potentiometer_Poti1Data();
    lcd_display.setCursor(0,0);
    lcd_display.print("RIGHT KNOB:     ");
    lcd_display.setCursor(12,0);
    lcd_display.print(tmp_u8);     
    if(LCD_NUM_DIGIT_CHECK_K == (tmp_u8/LCD_NUM_DIGIT_CHECK_K))
    {
        
        lcd_display.setCursor(15,0);
        lcd_display.print("%");                 
    }
    else
    {                    
        lcd_display.setCursor(14,0);
        lcd_display.print("%");   
    }   

    lcd_display.setCursor(0,2);
    lcd_display.print("LEFT KNOB: ");
    lcd_display.setCursor(11,2);
    lcd_display.print("Reserved");  
}

// ---------------------------------------------------------------------------
// Browse menu - Logistic data information display
void RE_Lcd_cls::lcdLF_logisticDataInfoDisplay(void)
{
    // SW version
    lcd_display.setCursor(0,0);
    lcd_display.print("SW Version: ");
    lcd_display.setCursor(12,0);
    lcd_display.print(SW_VERSION_C.version_u8[0]); // year
    lcd_display.setCursor(14,0);
    lcd_display.print("/");
    lcd_display.setCursor(15,0);
    lcd_display.print(SW_VERSION_C.version_u8[1]); // week
    lcd_display.setCursor(17,0);
    lcd_display.print("/");    
    lcd_display.setCursor(18,0);
    lcd_display.print(SW_VERSION_C.version_u8[2]); // path level

    // HW Version
    lcd_display.setCursor(0,2);         
    lcd_display.print("HW Version: ");
    lcd_display.setCursor(12,2);
    lcd_display.print(HW_VERSION_C.version_u8[0]); // year 
    lcd_display.setCursor(14,2);
    lcd_display.print("/");    
    lcd_display.setCursor(15,2);
    lcd_display.print(HW_VERSION_C.version_u8[1]); // week  
    lcd_display.setCursor(17,2);
    lcd_display.print("/");      
    lcd_display.setCursor(18,2);
    lcd_display.print(HW_VERSION_C.version_u8[2]); // path level   
}

// ---------------------------------------------------------------------------
// Browse menu - Controlled object type information display
void RE_Lcd_cls::lcdLF_controlledObjectInfoDisplay(void)
{
    uint8_t tmp_u8=0u;

    lcd_display.setCursor(0,0);
    lcd_display.print("Controlling...");

    // tmp_u8 = get the controlled type 
    if(DS_ROBOT_K == CONTROLLED_OBJECT_TYPE_C.type_u8[tmp_u8])
    {
        lcd_display.setCursor(7,2);
        lcd_display.print("ROBOT");   
    }
    else
    {
        // other types...
    }
}

// ---------------------------------------------------------------------------
// Set of browse menu displays
void RE_Lcd_cls::lcdLF_browseMenuDisplay(void)
{      
    enum browse_menu_et      tmp_browse_menu_e;


    tmp_browse_menu_e = Rte_cls.Rte_Read_Menu_BrowseMenu(); 
    if(tmp_browse_menu_e != copy_browse_menu_e)
    {
        // clear all displays if new browse state has changed.
        lcd_display.clear();
        diplay_refresh_time_u8 = LCD_DISPLAY_REFRESH_TIME_K; // there is new state. immediately display the info without refresh time
        copy_browse_menu_e = tmp_browse_menu_e;
    }
    else
    {
        // no action
    }

    if(diplay_refresh_time_u8 >= LCD_DISPLAY_REFRESH_TIME_K)
    {
        diplay_refresh_time_u8 = 0u; // clear refresh time

    // run to all supported display
    switch(tmp_browse_menu_e)
    {
        case MENU_DISPLAY_GENERAL_INFO_E:
        {
            lcdLF_generalInfoDisplay();
            break;
        }
        case MENU_DISPLAY_VOLTAGE_INFO_E:
        {
            // Voltage Display
            lcdLF_voltageInfoDisplay();          
            break;
        }
        case MENU_DISPLAY_JOYSTICK_INFO_E:
        {
            // JoyStick info
            lcdLF_joyStickInfoDisplay();           
            break;
        }
        case MENU_DISPLAY_SWITCH_INFO_E:
        {
            // Switch info
            lcdLF_switchInfoDisplay();                  
            break;
        }
        case MENU_DISPLAY_POTI_INFO_E:
        {
            // Potentiometer Display
            lcdLF_potiInfoDisplay();        
            break;
        }
        case MENU_DISPLAY_LOGISTIC_DATA_INFO_E:
        {
            // Logistic info
            lcdLF_logisticDataInfoDisplay();    
            break;
        }        
        case MENU_DISPLAY_CONTROLLED_OBJ_INFO_E:
        {
            // Controlled object(e.g. Robot, drone, rc car, rc plane, rc boat, etc..)
            lcdLF_controlledObjectInfoDisplay();         
            break;
        }
        default:
        {
            // no action
            break;
        }
    }
    }
    else
    {
        // increment refresh counter
        diplay_refresh_time_u8 += 1;
    }
}

// ---------------------------------------------------------------------------
// Set of main menu displays
//void RE_Lcd_cls::lcdLF_mainMenuDisplay(void)
//{
    //lcd_display.setCursor(0,0);
    //lcd_display.print("Welcome to Main Menu");
//}