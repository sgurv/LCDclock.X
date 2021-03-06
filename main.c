/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F1938
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "APDS9960.h"
/*
                         Main application
 */

enum e_ir_flag{
    IR_NONE,
    IR_BUSY,
    IR_DONE,
    IR_REPEAT
};

volatile uint8_t ir_address, ir_address_complement, ir_command, ir_command_complement;
volatile uint8_t ir_flag;

volatile uint8_t flag_gesture;

static void CCP4_CallBack(uint16_t capturedValue);
static void IOC_RB1_N_Handler(void);

void LCD_Digit1Num (unsigned char num); // this supports hex char
void LCD_Digit2Num (unsigned char num);
void LCD_Digit3Num (unsigned char num);
void LCD_Digit4Num (unsigned char num);

uint16_t intToBCD(uint16_t binaryInput);
uint8_t reverseBits(uint8_t b);

void main(void)
{
    uint16_t temp_num = 0,bcd_num;
    uint8_t temp8;
    // initialize the device
    SYSTEM_Initialize();
    
    ir_flag = IR_NONE;
    ir_address = ir_address_complement = ir_command = ir_command_complement = 0;
    
    flag_gesture = 0;
    
    CCP4_SetCallBack(CCP4_CallBack);
    IOCBF1_SetInterruptHandler(IOC_RB1_N_Handler);
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    if(APDS9960Init()){
        bcd_num = 1;
    } else {
        bcd_num = 0;
    }
    
    LCD_Digit4Num(bcd_num & 0x000F);
    //enableLightSensor(false); // without interrupt
    
    setProximityGain(PGAIN_2X); // Adjust the Proximity sensor gain
    
    //enableProximitySensor(false); // without interrupt
    
    enableGestureSensor(true); // with interrupt

    while (1)
    {
        // Add your application code
        CLRWDT();
      
//        D1_SYM04ON;
//        D2_SYM05ON;
//        D3_SYM06ON;
//        P_SYM07ON;
        
        
     
        //temp_num = readAmbientLight(); // works
        //temp_num = readProximity(); // works
        
        if(flag_gesture != 0){ // works with LED_BOOST_100
            
            D1_SYM04OFF;
            D2_SYM05OFF;
            D3_SYM06OFF;
            P_SYM07OFF;
            
            switch ( readGesture() ) {
                case DIR_UP:
                    LCD_Digit1Num('U');
                    LCD_Digit2Num('P');
                    LCD_Digit3Num(' ');
                    LCD_Digit4Num(' ');
                    break;
                case DIR_DOWN:
                    LCD_Digit1Num('D');
                    LCD_Digit2Num('N');
                    LCD_Digit3Num(' ');
                    LCD_Digit4Num(' ');
                    break;
                case DIR_LEFT:
                    LCD_Digit1Num('L');
                    LCD_Digit2Num('E');
                    LCD_Digit3Num('F');
                    LCD_Digit4Num('T');
                    break;
                case DIR_RIGHT:
                    LCD_Digit1Num('R');
                    LCD_Digit2Num('I');
                    LCD_Digit3Num('T');
                    LCD_Digit4Num(' ');
                    break;
                case DIR_NEAR:
                    LCD_Digit1Num('N');
                    LCD_Digit2Num('E');
                    LCD_Digit3Num('A');
                    LCD_Digit4Num('R');
                    break;
                case DIR_FAR:
                    LCD_Digit1Num('F');
                    LCD_Digit2Num('A');
                    LCD_Digit3Num('R');
                    LCD_Digit4Num(' ');
                    break;
                default:
                    LCD_Digit1Num('N');
                    LCD_Digit2Num('O');
                    LCD_Digit3Num('N');
                    LCD_Digit4Num('E');
            }
            
            flag_gesture = 0;
            
        } else {
            //temp_num = getStatusRegister();
            
//            bcd_num = intToBCD(temp_num);
//
//            LCD_Digit1Num((bcd_num >> 12) & 0x000F);
//            LCD_Digit2Num((bcd_num >> 8) & 0x000F);
//            LCD_Digit3Num((bcd_num >> 4) & 0x000F);
//            LCD_Digit4Num(bcd_num & 0x000F);
            //LCD_Digit4Num('P');
        }
        

        
        //__delay_ms(20);
        
        if(ir_flag == IR_DONE || ir_flag == IR_REPEAT){
            
            temp8 = reverseBits(ir_address); // because while decoding we used MSB first approach
            
            LCD_Digit1Num((temp8 >> 4) & 0x000F);
            LCD_Digit2Num(temp8 & 0x000F);
            
            P_SYM07ON; // colon
            
            temp8 = reverseBits(ir_command);
            
            LCD_Digit3Num((temp8 >> 4) & 0x000F);
            LCD_Digit4Num(temp8 & 0x000F);
            
            ir_flag = IR_NONE;
        }
        
    }
}

static void CCP4_CallBack(uint16_t capturedValue)
{
    static uint8_t bit_count;
    
    TMR1_WriteTimer(0x0000); // clear timer
    
    //NEC decoder
    if((capturedValue > 13350) && (capturedValue < 13650)){ //13.5ms Start
        bit_count = 0;
        ir_address = ir_address_complement = ir_command = ir_command_complement = 0;
        ir_flag = IR_BUSY;
    } else if((capturedValue > 11200) && (capturedValue < 11400)){ //11.25ms Repeat
        ir_flag = IR_REPEAT;
    } else if((capturedValue > 2100) && (capturedValue < 2400)){ //2.25ms 1
        if(bit_count < 8){
            //address
            ir_address <<= 1; // its actually LSB first, but who cares!
            ir_address++;
        } else if(bit_count < 16){
            // address complement
            ir_address_complement <<= 1;
            ir_address_complement++;
        } else if(bit_count < 24){
            // command
            ir_command <<= 1;
            ir_command++;
        } else if(bit_count < 32){
            // command complement
            ir_command_complement <<= 1;
            ir_command_complement++;
        }
        
        bit_count++;
        
        if(bit_count == 32){
            // done
            if(ir_command == (~ir_command_complement)){
                ir_flag = IR_DONE;
            }
        }
        
    } else if((capturedValue > 970) && (capturedValue < 1270)){ //1.12ms 0
        if(bit_count < 8){
            // address
            ir_address <<= 1; // its actually LSB first, but who cares!
        } else if(bit_count < 16){
            // address complement
            ir_address_complement <<= 1;
        } else if(bit_count < 24){
            // command
            ir_command <<= 1;
        } else if(bit_count < 32){
            // command complement
            ir_command_complement <<= 1;
        }
        
        bit_count++;
        
        if(bit_count == 32){
            //done
            if(ir_command == (~ir_command_complement)){
                ir_flag = IR_DONE;
            }
        }
    }
}

static void IOC_RB1_N_Handler(void){
    flag_gesture = 1;
}

void LCD_Digit1Num (unsigned char num) 
{
    switch (num)
    {
        case 0: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GOFF;  break;
        case 1: DIG1_SYM00AOFF;  DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DOFF;  DIG1_SYM00EOFF;  DIG1_SYM00FOFF;  DIG1_SYM00GOFF;  break;
        case 2: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00COFF;  DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FOFF;  DIG1_SYM00GON;   break;
        case 3: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EOFF;  DIG1_SYM00FOFF;  DIG1_SYM00GON;   break;
        case 4: DIG1_SYM00AOFF;  DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DOFF;  DIG1_SYM00EOFF;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 5: DIG1_SYM00AON;   DIG1_SYM00BOFF;  DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EOFF;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 6: DIG1_SYM00AON;   DIG1_SYM00BOFF;  DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 7: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DOFF;  DIG1_SYM00EOFF;  DIG1_SYM00FOFF;  DIG1_SYM00GOFF;  break;
        case 8: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 9: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EOFF;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 0x0A: case 'A': case 'a': DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DOFF;   DIG1_SYM00EON;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 0x0B: case 'B': case 'b': DIG1_SYM00AOFF;   DIG1_SYM00BOFF;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 0x0C: case 'C': case 'c': DIG1_SYM00AON;   DIG1_SYM00BOFF;   DIG1_SYM00COFF;   DIG1_SYM00DON;   DIG1_SYM00EON;  DIG1_SYM00FON;   DIG1_SYM00GOFF;   break;
        case 0x0D: case 'D': case 'd': DIG1_SYM00AOFF;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;  DIG1_SYM00FOFF;   DIG1_SYM00GON;   break;
        case 0x0E: case 'E': case 'e': DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00COFF;   DIG1_SYM00DOFF;   DIG1_SYM00EON;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 0x0F: case 'F': case 'f': DIG1_SYM00AON;   DIG1_SYM00BOFF;   DIG1_SYM00COFF;   DIG1_SYM00DOFF;   DIG1_SYM00EON;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 'G': case 'g': DIG1_SYM00AON;   DIG1_SYM00BOFF;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GOFF;   break;
        case 'H': case 'h': DIG1_SYM00AOFF;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DOFF;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 'I': case 'i': DIG1_SYM00AOFF;   DIG1_SYM00BOFF;   DIG1_SYM00COFF;   DIG1_SYM00DOFF;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GOFF;   break;
        case 'J': case 'j': DIG1_SYM00AOFF;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FOFF;   DIG1_SYM00GOFF;   break;
        case 'L': case 'l': DIG1_SYM00AOFF;   DIG1_SYM00BOFF;   DIG1_SYM00COFF;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GOFF;   break;
        case 'N': case 'n': DIG1_SYM00AOFF;   DIG1_SYM00BOFF;   DIG1_SYM00CON;   DIG1_SYM00DOFF;   DIG1_SYM00EON;   DIG1_SYM00FOFF;   DIG1_SYM00GON;   break;
        case 'O': case 'o': DIG1_SYM00AOFF;   DIG1_SYM00BOFF;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FOFF;   DIG1_SYM00GON;   break;
        case 'P': case 'p': DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00COFF;   DIG1_SYM00DOFF;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 'R': case 'r': DIG1_SYM00AOFF;   DIG1_SYM00BOFF;   DIG1_SYM00COFF;   DIG1_SYM00DOFF;   DIG1_SYM00EON;   DIG1_SYM00FOFF;   DIG1_SYM00GON;   break;
        case 'S': case 's': DIG1_SYM00AOFF;   DIG1_SYM00BOFF;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EOFF;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 'T': case 't': DIG1_SYM00AOFF;   DIG1_SYM00BOFF;   DIG1_SYM00COFF;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 'U': case 'u': DIG1_SYM00AOFF;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GOFF;   break;
        case 'Y': case 'y': DIG1_SYM00AOFF;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EOFF;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;

        default: DIG1_SYM00AOFF; DIG1_SYM00BOFF; DIG1_SYM00COFF; DIG1_SYM00DOFF; DIG1_SYM00EOFF; DIG1_SYM00FOFF; DIG1_SYM00GOFF;
    }    
}

void LCD_Digit2Num (unsigned char num) 
{
    switch (num)
    {
        case 0: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GOFF;  break;
        case 1: DIG2_SYM01AOFF;  DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DOFF;  DIG2_SYM01EOFF;  DIG2_SYM01FOFF;  DIG2_SYM01GOFF;  break;
        case 2: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01COFF;  DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FOFF;  DIG2_SYM01GON;   break;
        case 3: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EOFF;  DIG2_SYM01FOFF;  DIG2_SYM01GON;   break;
        case 4: DIG2_SYM01AOFF;  DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DOFF;  DIG2_SYM01EOFF;  DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 5: DIG2_SYM01AON;   DIG2_SYM01BOFF;  DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EOFF;  DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 6: DIG2_SYM01AON;   DIG2_SYM01BOFF;  DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 7: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DOFF;  DIG2_SYM01EOFF;  DIG2_SYM01FOFF;  DIG2_SYM01GOFF;  break;
        case 8: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 9: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EOFF;  DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 0x0A: case 'A': case 'a': DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DOFF;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 0x0B: case 'B': case 'b': DIG2_SYM01AOFF;   DIG2_SYM01BOFF;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 0x0C: case 'C': case 'c': DIG2_SYM01AON;   DIG2_SYM01BOFF;   DIG2_SYM01COFF;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GOFF;   break;
        case 0x0D: case 'D': case 'd': DIG2_SYM01AOFF;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FOFF;   DIG2_SYM01GON;   break;
        case 0x0E: case 'E': case 'e': DIG2_SYM01AON;   DIG2_SYM01BOFF;   DIG2_SYM01COFF;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 0x0F: case 'F': case 'f': DIG2_SYM01AON;   DIG2_SYM01BOFF;   DIG2_SYM01COFF;   DIG2_SYM01DOFF;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 'G': case 'g': DIG2_SYM01AON;   DIG2_SYM01BOFF;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GOFF;   break;
        case 'H': case 'h': DIG2_SYM01AOFF;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DOFF;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 'I': case 'i': DIG2_SYM01AOFF;   DIG2_SYM01BOFF;   DIG2_SYM01COFF;   DIG2_SYM01DOFF;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GOFF;   break;
        case 'J': case 'j': DIG2_SYM01AOFF;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FOFF;   DIG2_SYM01GOFF;   break;
        case 'L': case 'l': DIG2_SYM01AOFF;   DIG2_SYM01BOFF;   DIG2_SYM01COFF;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GOFF;   break;
        case 'N': case 'n': DIG2_SYM01AOFF;   DIG2_SYM01BOFF;   DIG2_SYM01CON;   DIG2_SYM01DOFF;   DIG2_SYM01EON;   DIG2_SYM01FOFF;   DIG2_SYM01GON;   break;
        case 'O': case 'o': DIG2_SYM01AOFF;   DIG2_SYM01BOFF;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FOFF;   DIG2_SYM01GON;   break;
        case 'P': case 'p': DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01COFF;   DIG2_SYM01DOFF;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 'R': case 'r': DIG2_SYM01AOFF;   DIG2_SYM01BOFF;   DIG2_SYM01COFF;   DIG2_SYM01DOFF;   DIG2_SYM01EON;   DIG2_SYM01FOFF;   DIG2_SYM01GON;   break;
        case 'S': case 's': DIG2_SYM01AOFF;   DIG2_SYM01BOFF;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EOFF;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 'T': case 't': DIG2_SYM01AOFF;   DIG2_SYM01BOFF;   DIG2_SYM01COFF;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 'U': case 'u': DIG2_SYM01AOFF;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GOFF;   break;
        case 'Y': case 'y': DIG2_SYM01AOFF;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EOFF;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;

        default: DIG2_SYM01AOFF; DIG2_SYM01BOFF; DIG2_SYM01COFF; DIG2_SYM01DOFF; DIG2_SYM01EOFF; DIG2_SYM01FOFF; DIG2_SYM01GOFF;
    }    
}

void LCD_Digit3Num (unsigned char num) 
{
    switch (num)
    {
        case 0: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GOFF;  break;
        case 1: DIG3_SYM02AOFF;  DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DOFF;  DIG3_SYM02EOFF;  DIG3_SYM02FOFF;  DIG3_SYM02GOFF;  break;
        case 2: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02COFF;  DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FOFF;  DIG3_SYM02GON;   break;
        case 3: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EOFF;  DIG3_SYM02FOFF;  DIG3_SYM02GON;   break;
        case 4: DIG3_SYM02AOFF;  DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DOFF;  DIG3_SYM02EOFF;  DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 5: DIG3_SYM02AON;   DIG3_SYM02BOFF;  DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EOFF;  DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 6: DIG3_SYM02AON;   DIG3_SYM02BOFF;  DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 7: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DOFF;  DIG3_SYM02EOFF;  DIG3_SYM02FOFF;  DIG3_SYM02GOFF;  break;
        case 8: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 9: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EOFF;  DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 0x0A: case 'A': case 'a': DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DOFF;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 0x0B: case 'B': case 'b': DIG3_SYM02AOFF;   DIG3_SYM02BOFF;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 0x0C: case 'C': case 'c': DIG3_SYM02AON;   DIG3_SYM02BOFF;   DIG3_SYM02COFF;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GOFF;   break;
        case 0x0D: case 'D': case 'd': DIG3_SYM02AOFF;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FOFF;   DIG3_SYM02GON;   break;
        case 0x0E: case 'E': case 'e': DIG3_SYM02AON;   DIG3_SYM02BOFF;   DIG3_SYM02COFF;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 0x0F: case 'F': case 'f': DIG3_SYM02AON;   DIG3_SYM02BOFF;   DIG3_SYM02COFF;   DIG3_SYM02DOFF;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 'G': case 'g': DIG3_SYM02AON;   DIG3_SYM02BOFF;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GOFF;   break;
        case 'H': case 'h': DIG3_SYM02AOFF;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DOFF;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 'I': case 'i': DIG3_SYM02AOFF;   DIG3_SYM02BOFF;   DIG3_SYM02COFF;   DIG3_SYM02DOFF;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GOFF;   break;
        case 'J': case 'j': DIG3_SYM02AOFF;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FOFF;   DIG3_SYM02GOFF;   break;
        case 'L': case 'l': DIG3_SYM02AOFF;   DIG3_SYM02BOFF;   DIG3_SYM02COFF;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GOFF;   break;
        case 'N': case 'n': DIG3_SYM02AOFF;   DIG3_SYM02BOFF;   DIG3_SYM02CON;   DIG3_SYM02DOFF;   DIG3_SYM02EON;   DIG3_SYM02FOFF;   DIG3_SYM02GON;   break;
        case 'O': case 'o': DIG3_SYM02AOFF;   DIG3_SYM02BOFF;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FOFF;   DIG3_SYM02GON;   break;
        case 'P': case 'p': DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02COFF;   DIG3_SYM02DOFF;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 'R': case 'r': DIG3_SYM02AOFF;   DIG3_SYM02BOFF;   DIG3_SYM02COFF;   DIG3_SYM02DOFF;   DIG3_SYM02EON;   DIG3_SYM02FOFF;   DIG3_SYM02GON;   break;
        case 'S': case 's': DIG3_SYM02AOFF;   DIG3_SYM02BOFF;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EOFF;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 'T': case 't': DIG3_SYM02AOFF;   DIG3_SYM02BOFF;   DIG3_SYM02COFF;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 'U': case 'u': DIG3_SYM02AOFF;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GOFF;   break;
        case 'Y': case 'y': DIG3_SYM02AOFF;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EOFF;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;

        default: DIG3_SYM02AOFF; DIG3_SYM02BOFF; DIG3_SYM02COFF; DIG3_SYM02DOFF; DIG3_SYM02EOFF; DIG3_SYM02FOFF; DIG3_SYM02GOFF;
    }
}

void LCD_Digit4Num (unsigned char num) 
{
    switch (num)
    {
        case 0: case '0': DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GOFF;  break;
        case 1: case '1': DIG4_SYM03AOFF;  DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DOFF;  DIG4_SYM03EOFF;  DIG4_SYM03FOFF;  DIG4_SYM03GOFF;  break;
        case 2: case '2': DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03COFF;  DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FOFF;  DIG4_SYM03GON;   break;
        case 3: case '3': DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EOFF;  DIG4_SYM03FOFF;  DIG4_SYM03GON;   break;
        case 4: case '4': DIG4_SYM03AOFF;  DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DOFF;  DIG4_SYM03EOFF;  DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 5: case '5': DIG4_SYM03AON;   DIG4_SYM03BOFF;  DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EOFF;  DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 6: case '6': DIG4_SYM03AON;   DIG4_SYM03BOFF;  DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 7: case '7': DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DOFF;  DIG4_SYM03EOFF;  DIG4_SYM03FOFF;  DIG4_SYM03GOFF;  break;
        case 8: case '8': DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 9: case '9': DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EOFF;  DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 0x0A: case 'A': case 'a': DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DOFF;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 0x0B: case 'B': case 'b': DIG4_SYM03AOFF;   DIG4_SYM03BOFF;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 0x0C: case 'C': case 'c': DIG4_SYM03AON;   DIG4_SYM03BOFF;   DIG4_SYM03COFF;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GOFF;   break;
        case 0x0D: case 'D': case 'd': DIG4_SYM03AOFF;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FOFF;   DIG4_SYM03GON;   break;
        case 0x0E: case 'E': case 'e':  DIG4_SYM03AON;   DIG4_SYM03BOFF;   DIG4_SYM03COFF;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 0x0F: case 'F': case 'f': DIG4_SYM03AON;   DIG4_SYM03BOFF;   DIG4_SYM03COFF;   DIG4_SYM03DOFF;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 'G': case 'g': DIG4_SYM03AON;   DIG4_SYM03BOFF;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 'H': case 'h': DIG4_SYM03AOFF;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DOFF;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 'I': case 'i': DIG4_SYM03AOFF;   DIG4_SYM03BOFF;   DIG4_SYM03COFF;   DIG4_SYM03DOFF;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GOFF;   break;
        case 'J': case 'j': DIG4_SYM03AOFF;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FOFF;   DIG4_SYM03GOFF;   break;
        case 'L': case 'l': DIG4_SYM03AOFF;   DIG4_SYM03BOFF;   DIG4_SYM03COFF;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GOFF;   break;
        case 'N': case 'n': DIG4_SYM03AOFF;   DIG4_SYM03BOFF;   DIG4_SYM03CON;   DIG4_SYM03DOFF;   DIG4_SYM03EON;   DIG4_SYM03FOFF;   DIG4_SYM03GON;   break;
        case 'O': case 'o': DIG4_SYM03AOFF;   DIG4_SYM03BOFF;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FOFF;   DIG4_SYM03GON;   break;
        case 'P': case 'p': DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03COFF;   DIG4_SYM03DOFF;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 'R': case 'r': DIG4_SYM03AOFF;   DIG4_SYM03BOFF;   DIG4_SYM03COFF;   DIG4_SYM03DOFF;   DIG4_SYM03EON;   DIG4_SYM03FOFF;   DIG4_SYM03GON;   break;
        case 'S': case 's': DIG4_SYM03AOFF;   DIG4_SYM03BOFF;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EOFF;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 'T': case 't': DIG4_SYM03AOFF;   DIG4_SYM03BOFF;   DIG4_SYM03COFF;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 'U': case 'u': DIG4_SYM03AOFF;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GOFF;   break;
        case 'Y': case 'y': DIG4_SYM03AOFF;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EOFF;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;

        default: DIG4_SYM03AOFF; DIG4_SYM03BOFF; DIG4_SYM03COFF; DIG4_SYM03DOFF; DIG4_SYM03EOFF; DIG4_SYM03FOFF; DIG4_SYM03GOFF;
    }    
}

uint16_t intToBCD(uint16_t binaryInput){
    uint16_t bcdResult = 0;
    uint16_t shift = 0;
    
    while (binaryInput > 0) {
      bcdResult |= (binaryInput % 10) << (shift++ << 2);
      binaryInput /= 10;
    }
    
    return bcdResult;
}

uint8_t reverseBits(uint8_t b) {
   b = (b & 0b11110000) >> 4 | (b & 0b00001111) << 4;
   b = (b & 0b11001100) >> 2 | (b & 0b00110011) << 2;
   b = (b & 0b10101010) >> 1 | (b & 0b01010101) << 1;
   return b;
}
/**
 End of File
*/