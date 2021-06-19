// LCDKeypad.c
// Program to test LCD and keypad.
// For project using USB interface with Bootloader

#include <xc.h>
#include "keypad.h"
#include "delays.h"
#include "lcd.h"

unsigned char key, outchar;
unsigned char key1, key2, key3;
char Message1 [ ] = "Press buttons:      ";	  // Defining a 20 char string
char Message2 [ ] = "Opening Container 1 ";   // To open up first compartment
char Message3 [ ] = "Opening Container 2 ";
char Message4 [ ] = "Pressed 3           ";
char Message5 [ ] = "Invalid Button      ";   // Any other button that has no function
char Message6 [ ] = "Compartment 1 is ";   // To find moisture and display on LCD
char Message7 [ ] = "Compartment 2 is ";   // To find percentage of food 
char Message9 [ ] = "Compartment 1 is wet"; // Check whether compartment 1 is wet
char Message10 [ ] = "Compartment 1 is dry"; // Check whether compartment 1 is dry
char Message11 [ ] = "Compartment 2 is wet"; // Check whether compartment 2 is wet
char Message12 [ ] = "Compartment 2 is dry"; // Check whether compartment 2 is dry

// ---- Main Program ---------------------------------------------------------------
void main(void)
{
	int i;
    TRISAbits.TRISA3 = 0; // Servo motor 1st compartment left side
    TRISAbits.TRISA2 = 0; // Servo motor 1st compartment right side
    TRISAbits.TRISA4 = 1; // Moisture sensor 1st compartment
    TRISAbits.TRISA5 = 1; // Moisture sensor 2nd compartment
    TRISCbits.TRISC1 = 0; // Servo motor 2nd compartment right side
    TRISCbits.TRISC2 = 0; // Servo motor 2nd compartment left side
           
	lcd_init();						// Initialize LCD module
    

	while(1)
	{
		lcd_write_cmd(0x80);			// Move cursor to line 1 position 1
		for (i = 0; i < 20; i++)		//for 20 char LCD module
		{
			outchar = Message1[i];
			lcd_write_data(outchar); 	// write character data to LCD
		}
		
		lcd_write_cmd(0xC0);			// Move cursor to line 2 position 1
		//Note that buttons 1-3 are for opening the compartment doors  
        key = getkey();
        key1 = key;
        
        if(key == '1'){
            lcd_write_data(key);
            delay_ms(1000); //wait for 1 second delay
            lcd_write_cmd(0x01); // 00000001 Clear Display instruction
            lcd_write_cmd(0x80);
            for (i = 0; i < 20; i++) {
                outchar = Message2[i];
                lcd_write_data(outchar);
            }
            
            
             /* We'll be using RA2 for the first compartment, RIGHT servo motor for the right side of the door */
           for(i=0;i<33;i++) {
                PORTAbits.RA2 = 1;
                delay_us(100);
                PORTAbits.RA2 = 0; 
                delay_us(19900); 
                
                 PORTAbits.RA3 = 1;
                delay_us(1500);
                PORTAbits.RA3 = 0; 
                delay_us(18500);
            } //turn ANTIclockwise
            
            
            
          //   for(i=0;i<33;i++) {
               
           // } //turn clockwise
            
            delay_ms(3000);
            
        
            
          /* We'll be using RA3 for the first compartment, LEFT servo motor for the left side of the door */
                for(i=0;i<33;i++) {
                PORTAbits.RA2 = 1;
                delay_us(1500);
                PORTAbits.RA2 = 0;
                delay_us(18500);
                
                 PORTAbits.RA3 = 1;
                delay_us(100);
                PORTAbits.RA3 = 0;
                delay_us(19900);
            } //turn clockwise
            
            
            
            // for(i=0;i<33;i++) {
               
           // } //turn anti-clockwise
            
           
            
            
            
        }
        else if(key == '2'){
            lcd_write_data(key);
            delay_ms(1000); //wait for 1 second delay
            lcd_write_cmd(0x01); // 00000001 Clear Display instruction
            lcd_write_cmd(0x80);
            for (i = 0; i < 20; i++)
            {
                outchar = Message3[i];
                lcd_write_data(outchar);
            }
            
             /* We'll be using RC1 for the second compartment, RIGHT servo motor for the right side of the door */
           for(i=0;i<33;i++) {
                PORTCbits.RC1 = 1;  //turn ANTIclockwise
                delay_us(100);
                PORTCbits.RC1 = 0; 
                delay_us(19900);
                
                
                 PORTCbits.RC2 = 1;  //turn clockwise
                delay_us(1500);
                PORTCbits.RC2 = 0; 
                delay_us(18500);
            }                           
            
            delay_ms(3000);
            
        
           for(i=0;i<33;i++) {       
                 PORTCbits.RC2 = 1; //turn anti-clockwise
                delay_us(100);
                PORTCbits.RC2 = 0;
                delay_us(19900);
                
                
                PORTCbits.RC1 = 1; //turn clockwise
                delay_us(1500);
                PORTCbits.RC1 = 0;
                delay_us(18500);
            } 
        }
        else if(key == '3'){
            lcd_write_data(key);
            delay_ms(1000); //wait for 1 second delay
            lcd_write_cmd(0x01); // 00000001 Clear Display instruction
            lcd_write_cmd(0x80);
            for (i = 0; i < 20; i++)
            {
                outchar = Message4[i];
                lcd_write_data(outchar);
            }
        }
        else if(key == 'A'){ // Check moisture in compartment 1
            lcd_write_data(key);
            delay_ms(1000); //wait for 1 second delay
            lcd_write_cmd(0x01); // 00000001 Clear Display instruction
            lcd_write_cmd(0x80);
          /*  for (i = 0; i < 20; i++)
            {
                outchar = Message6[i];
                lcd_write_data(outchar);
            } */
          
            if(PORTAbits.RA4 == 1) {
              for (i = 0; i < 20; i++)
            {
                outchar = Message9[i];
                lcd_write_data(outchar);
            }  
            } else {
                for (i = 0; i < 20; i++)
            {
                outchar = Message10[i];
                lcd_write_data(outchar);
            }  
                
            }
            
            
        }
        else if(key == 'B'){ // Check moisture of Compartment 2
            lcd_write_data(key);
            delay_ms(1000); //wait for 1 second delay
            lcd_write_cmd(0x01); // 00000001 Clear Display instruction
            lcd_write_cmd(0x80);
          /*  for (i = 0; i < 20; i++)
            {
                outchar = Message7[i];
                lcd_write_data(outchar);
            } */
            
            if(PORTAbits.RA5 == 1) {
                 for (i = 0; i < 20; i++)
            {
                outchar = Message11[i];
                lcd_write_data(outchar);
            }
            } else {
                 for (i = 0; i < 20; i++)
            {
                outchar = Message12[i];
                lcd_write_data(outchar);
            }
            }
            
        }
       /* else if(key == 'C'){ // FInd Weight
            lcd_write_data(key);
            delay_ms(1000); //wait for 1 second delay
            lcd_write_cmd(0x01); // 00000001 Clear Display instruction
            lcd_write_cmd(0x80);
            for (i = 0; i < 20; i++)
            {
                outchar = Message8[i];
                lcd_write_data(outchar);
            }
        } */
        else if(key !='1' || key != '2' || key != '3' || key != 'A' || key != 'B' || key != 'C'){
                lcd_write_cmd(0x01); // 00000001 Clear Display instruction
            lcd_write_cmd(0x80);
            for (i = 0; i < 20; i++)
            {
                outchar = Message5[i];
                lcd_write_data(outchar);
            }
        }
            		
    }
}
