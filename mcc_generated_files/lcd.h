/**
  LCD Generated Driver API Header File
  
  @Company
    Microchip Technology Inc.

  @File Name
    lcd.h
	
  @Summary
    This is the generated header file for the LCD driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for LCD.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.5
        Device            :  PIC16F1938
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB 	          :  MPLAB X 5.40
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef LCD_H
#define LCD_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
    
/**
    Section: Defines
*/ 
   
/**
    Defines: the segments pins
*/
#define SEG00      LCDSE0bits.SE0
#define SEG01      LCDSE0bits.SE1
#define SEG02      LCDSE0bits.SE2
#define SEG03      LCDSE0bits.SE3
#define SEG04      LCDSE0bits.SE4
#define SEG05      LCDSE0bits.SE5
#define SEG06      LCDSE0bits.SE6
#define SEG07      LCDSE0bits.SE7
#define SEG08      LCDSE1bits.SE8
#define SEG09      LCDSE1bits.SE9
#define SEG10      LCDSE1bits.SE10
#define SEG11      LCDSE1bits.SE11
#define SEG12      LCDSE1bits.SE12
#define SEG13      LCDSE1bits.SE13
#define SEG14      LCDSE1bits.SE14
#define SEG15      LCDSE1bits.SE15

#define DIG1_SYM00A      LCDDATA9bits.SEG4COM3
#define DIG1_SYM00B      LCDDATA9bits.SEG7COM3
#define DIG1_SYM00C      LCDDATA3bits.SEG7COM1
#define DIG1_SYM00D      LCDDATA0bits.SEG7COM0
#define DIG1_SYM00E      LCDDATA3bits.SEG4COM1
#define DIG1_SYM00F      LCDDATA6bits.SEG4COM2
#define DIG1_SYM00G      LCDDATA6bits.SEG7COM2
#define DIG2_SYM01A      LCDDATA9bits.SEG5COM3
#define DIG2_SYM01B      LCDDATA10bits.SEG12COM3
#define DIG2_SYM01C      LCDDATA4bits.SEG12COM1
#define DIG2_SYM01D      LCDDATA1bits.SEG12COM0
#define DIG2_SYM01E      LCDDATA3bits.SEG5COM1
#define DIG2_SYM01F      LCDDATA6bits.SEG5COM2
#define DIG2_SYM01G      LCDDATA7bits.SEG12COM2
#define DIG3_SYM02A      LCDDATA10bits.SEG13COM3
#define DIG3_SYM02B      LCDDATA9bits.SEG1COM3
#define DIG3_SYM02C      LCDDATA3bits.SEG1COM1
#define DIG3_SYM02D      LCDDATA0bits.SEG1COM0
#define DIG3_SYM02E      LCDDATA4bits.SEG13COM1
#define DIG3_SYM02F      LCDDATA7bits.SEG13COM2
#define DIG3_SYM02G      LCDDATA6bits.SEG1COM2
#define DIG4_SYM03A      LCDDATA10bits.SEG14COM3
#define DIG4_SYM03B      LCDDATA9bits.SEG2COM3
#define DIG4_SYM03C      LCDDATA3bits.SEG2COM1
#define DIG4_SYM03D      LCDDATA0bits.SEG2COM0
#define DIG4_SYM03E      LCDDATA4bits.SEG14COM1
#define DIG4_SYM03F      LCDDATA7bits.SEG14COM2
#define DIG4_SYM03G      LCDDATA6bits.SEG2COM2
#define D1_SYM04      LCDDATA0bits.SEG5COM0
#define D2_SYM05      LCDDATA1bits.SEG13COM0
#define D3_SYM06      LCDDATA1bits.SEG14COM0
#define P_SYM07      LCDDATA0bits.SEG4COM0


/**
    Defines: To Turn on a pixel (a segment from a digit or a special character)
*/
#define DIG1_SYM00AON     DIG1_SYM00A = 1
#define DIG1_SYM00BON     DIG1_SYM00B = 1
#define DIG1_SYM00CON     DIG1_SYM00C = 1
#define DIG1_SYM00DON     DIG1_SYM00D = 1
#define DIG1_SYM00EON     DIG1_SYM00E = 1
#define DIG1_SYM00FON     DIG1_SYM00F = 1
#define DIG1_SYM00GON     DIG1_SYM00G = 1
#define DIG2_SYM01AON     DIG2_SYM01A = 1
#define DIG2_SYM01BON     DIG2_SYM01B = 1
#define DIG2_SYM01CON     DIG2_SYM01C = 1
#define DIG2_SYM01DON     DIG2_SYM01D = 1
#define DIG2_SYM01EON     DIG2_SYM01E = 1
#define DIG2_SYM01FON     DIG2_SYM01F = 1
#define DIG2_SYM01GON     DIG2_SYM01G = 1
#define DIG3_SYM02AON     DIG3_SYM02A = 1
#define DIG3_SYM02BON     DIG3_SYM02B = 1
#define DIG3_SYM02CON     DIG3_SYM02C = 1
#define DIG3_SYM02DON     DIG3_SYM02D = 1
#define DIG3_SYM02EON     DIG3_SYM02E = 1
#define DIG3_SYM02FON     DIG3_SYM02F = 1
#define DIG3_SYM02GON     DIG3_SYM02G = 1
#define DIG4_SYM03AON     DIG4_SYM03A = 1
#define DIG4_SYM03BON     DIG4_SYM03B = 1
#define DIG4_SYM03CON     DIG4_SYM03C = 1
#define DIG4_SYM03DON     DIG4_SYM03D = 1
#define DIG4_SYM03EON     DIG4_SYM03E = 1
#define DIG4_SYM03FON     DIG4_SYM03F = 1
#define DIG4_SYM03GON     DIG4_SYM03G = 1
#define D1_SYM04ON     D1_SYM04 = 1
#define D2_SYM05ON     D2_SYM05 = 1
#define D3_SYM06ON     D3_SYM06 = 1
#define P_SYM07ON     P_SYM07 = 1

/**
    Defines: To Turn off a pixel (a segment from a digit or a special character)
*/
#define DIG1_SYM00AOFF    DIG1_SYM00A = 0
#define DIG1_SYM00BOFF    DIG1_SYM00B = 0
#define DIG1_SYM00COFF    DIG1_SYM00C = 0
#define DIG1_SYM00DOFF    DIG1_SYM00D = 0
#define DIG1_SYM00EOFF    DIG1_SYM00E = 0
#define DIG1_SYM00FOFF    DIG1_SYM00F = 0
#define DIG1_SYM00GOFF    DIG1_SYM00G = 0
#define DIG2_SYM01AOFF    DIG2_SYM01A = 0
#define DIG2_SYM01BOFF    DIG2_SYM01B = 0
#define DIG2_SYM01COFF    DIG2_SYM01C = 0
#define DIG2_SYM01DOFF    DIG2_SYM01D = 0
#define DIG2_SYM01EOFF    DIG2_SYM01E = 0
#define DIG2_SYM01FOFF    DIG2_SYM01F = 0
#define DIG2_SYM01GOFF    DIG2_SYM01G = 0
#define DIG3_SYM02AOFF    DIG3_SYM02A = 0
#define DIG3_SYM02BOFF    DIG3_SYM02B = 0
#define DIG3_SYM02COFF    DIG3_SYM02C = 0
#define DIG3_SYM02DOFF    DIG3_SYM02D = 0
#define DIG3_SYM02EOFF    DIG3_SYM02E = 0
#define DIG3_SYM02FOFF    DIG3_SYM02F = 0
#define DIG3_SYM02GOFF    DIG3_SYM02G = 0
#define DIG4_SYM03AOFF    DIG4_SYM03A = 0
#define DIG4_SYM03BOFF    DIG4_SYM03B = 0
#define DIG4_SYM03COFF    DIG4_SYM03C = 0
#define DIG4_SYM03DOFF    DIG4_SYM03D = 0
#define DIG4_SYM03EOFF    DIG4_SYM03E = 0
#define DIG4_SYM03FOFF    DIG4_SYM03F = 0
#define DIG4_SYM03GOFF    DIG4_SYM03G = 0
#define D1_SYM04OFF    D1_SYM04 = 0
#define D2_SYM05OFF    D2_SYM05 = 0
#define D3_SYM06OFF    D3_SYM06 = 0
#define P_SYM07OFF    P_SYM07 = 0
/**
  Section: Interface Routines
*/

/**
  @Summary
    Initializes the LCD module

  @Description
    This routine should only be called once during system initialization.    

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    LCD_Initialize();
    </code>     
*/
void LCD_Initialize(void);

/**
    @Summary
        Enable LCD module
        
    @Description
        This routine enables LCD module.   
        
    @Preconditions
        None.

    @Param
        None.

    @Returns
        None.
      
    @Example
        <code>
        LCD_Enable();
        </code>     
*/
void LCD_Enable (void);

/**
    @Summary
        Disable LCD module
        
    @Description
        This routine disables LCD module.   
        
    @Preconditions
        None.

    @Param
        None.

    @Returns
        None.
      
    @Example
        <code>
        LCD_Disable();
        </code>     
*/
void LCD_Disable (void);

/**
    @Summary
        Enable sleep mode for LCD module
        
    @Description
        This routine enables the sleep mode for LCD module.
        
    @Preconditions
        None.

    @Param
        None.

    @Returns
        None.
      
    @Example
        <code>
        LCD_EnableSleepMode();
        </code>     
*/
void LCD_EnableSleepMode (void);

/**
    @Summary
        Disable sleep mode for LCD module
        
    @Description
        This routine disables the sleep mode for LCD module.
        
    @Preconditions
        None.

    @Param
        None.

    @Returns
        None.
      
    @Example
        <code>
        LCD_DisableSleepMode();
        </code>     
*/
void LCD_DisableSleepMode (void);

/**
    @Summary
        Set contrast for LCD module
        
    @Description
        This routine set the contrast value for LCD module.
        
    @Preconditions
       If The internal reference source bit is 0, then the internal LCDcontrast control is unconnected.

    @Param
        Pass the contrast bits value.
        This range for this value is specific for each device.

    @Returns
        None.
      
    @Example
        <code>
        LCD_SetContrast (value);
        </code>     
*/
void LCD_SetContrast (unsigned int value);

/**
    @Summary
        Set LCD module power mode for A interval.
        
    @Description
        This routine set the LCD module reference ladder A time
        power control.
        
    @Preconditions
        None.

    @Param
        Pass the power bits value.

    @Returns
        None.
      
    @Example
        <code>
        LCD_SetIntervalAPowerMode (value);
        </code>     
*/
void LCD_SetIntervalAPowerMode (unsigned int value);

/**
    @Summary
        Set LCD module power mode for B interval.
        
    @Description
        This routine set the LCD module reference ladder B time
        power control.
        
    @Preconditions
        None.

    @Param
        Pass the power bits value.

    @Returns
        None.
      
    @Example
        <code>
        LCD_SetIntervalBPowerMode (value);
        </code>     
*/
void LCD_SetIntervalBPowerMode (unsigned int value);

/**
    @Summary
        Set LCD module power distribution.
        
    @Description
        This routine set the LCD module power distribution during
        waveform intervals.
        
    @Preconditions
        None.

    @Param
        Pass the power bits value.

    @Returns
        None.
      
    @Example
        <code>
        LCD_SetPowerDistribution (value);
        </code>     
*/
void LCD_SetPowerDistribution (unsigned int value);

/**
    @Summary
        Returns true if the LCD module is active, otherwise false.
        
    @Description
        This routine is used to determine if the LCD module is active.
        
    @Preconditions
        None.

    @Param
        Node.

    @Returns
        true  - If module is active.
        false - If module is not active.
      
    @Example
        <code>
         LCD_Initialize();
         while(!LCD_IsActive()); // wait until the module is available
        </code>     
*/
bool LCD_IsActive (void);



/**
  @Summary
    Displays on all the defined pixels for digit DIG1_SYM00

  @Description
    This routine displays on all the defined pixels for digit DIG1_SYM00

  @Returns
    None

  @Param
    None
  
  @Example
        <code>
        void LCD_DisplayOn_DIG1_SYM00Num();
        </code>
*/
void LCD_DisplayOn_DIG1_SYM00Num();

/**
  @Summary
    Displays off all the defined pixels for digit DIG1_SYM00

  @Description
    This routine displays off all the defined pixels for digit DIG1_SYM00

  @Returns
    None

  @Param
    None
  
  @Example
        <code>
        void LCD_DisplayOff_DIG1_SYM00Num();
        </code>
*/
void LCD_DisplayOff_DIG1_SYM00Num();    
/**
  @Summary
    Display a char for digit DIG1_SYM00

  @Description
    This routine displays a specific char for lcd's digit DIG1_SYM00

  @Returns
    None

  @Param
    The needed char
  
  @Example
        <code>
        void LCD_DIG1_SYM00Num ('5');
        </code>      
*/
void LCD_DIG1_SYM00Num (unsigned char num);
/**
  @Summary
    Displays on all the defined pixels for digit DIG2_SYM01

  @Description
    This routine displays on all the defined pixels for digit DIG2_SYM01

  @Returns
    None

  @Param
    None
  
  @Example
        <code>
        void LCD_DisplayOn_DIG2_SYM01Num();
        </code>
*/
void LCD_DisplayOn_DIG2_SYM01Num();

/**
  @Summary
    Displays off all the defined pixels for digit DIG2_SYM01

  @Description
    This routine displays off all the defined pixels for digit DIG2_SYM01

  @Returns
    None

  @Param
    None
  
  @Example
        <code>
        void LCD_DisplayOff_DIG2_SYM01Num();
        </code>
*/
void LCD_DisplayOff_DIG2_SYM01Num();    
/**
  @Summary
    Display a char for digit DIG2_SYM01

  @Description
    This routine displays a specific char for lcd's digit DIG2_SYM01

  @Returns
    None

  @Param
    The needed char
  
  @Example
        <code>
        void LCD_DIG2_SYM01Num ('5');
        </code>      
*/
void LCD_DIG2_SYM01Num (unsigned char num);
/**
  @Summary
    Displays on all the defined pixels for digit DIG3_SYM02

  @Description
    This routine displays on all the defined pixels for digit DIG3_SYM02

  @Returns
    None

  @Param
    None
  
  @Example
        <code>
        void LCD_DisplayOn_DIG3_SYM02Num();
        </code>
*/
void LCD_DisplayOn_DIG3_SYM02Num();

/**
  @Summary
    Displays off all the defined pixels for digit DIG3_SYM02

  @Description
    This routine displays off all the defined pixels for digit DIG3_SYM02

  @Returns
    None

  @Param
    None
  
  @Example
        <code>
        void LCD_DisplayOff_DIG3_SYM02Num();
        </code>
*/
void LCD_DisplayOff_DIG3_SYM02Num();    
/**
  @Summary
    Display a char for digit DIG3_SYM02

  @Description
    This routine displays a specific char for lcd's digit DIG3_SYM02

  @Returns
    None

  @Param
    The needed char
  
  @Example
        <code>
        void LCD_DIG3_SYM02Num ('5');
        </code>      
*/
void LCD_DIG3_SYM02Num (unsigned char num);
/**
  @Summary
    Displays on all the defined pixels for digit DIG4_SYM03

  @Description
    This routine displays on all the defined pixels for digit DIG4_SYM03

  @Returns
    None

  @Param
    None
  
  @Example
        <code>
        void LCD_DisplayOn_DIG4_SYM03Num();
        </code>
*/
void LCD_DisplayOn_DIG4_SYM03Num();

/**
  @Summary
    Displays off all the defined pixels for digit DIG4_SYM03

  @Description
    This routine displays off all the defined pixels for digit DIG4_SYM03

  @Returns
    None

  @Param
    None
  
  @Example
        <code>
        void LCD_DisplayOff_DIG4_SYM03Num();
        </code>
*/
void LCD_DisplayOff_DIG4_SYM03Num();    
/**
  @Summary
    Display a char for digit DIG4_SYM03

  @Description
    This routine displays a specific char for lcd's digit DIG4_SYM03

  @Returns
    None

  @Param
    The needed char
  
  @Example
        <code>
        void LCD_DIG4_SYM03Num ('5');
        </code>      
*/
void LCD_DIG4_SYM03Num (unsigned char num);
#endif /*_LCD_H*/