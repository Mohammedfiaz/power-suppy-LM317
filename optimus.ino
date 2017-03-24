/*
 * Using a 16x2 LCD with an I2C backpack (TLPCF8574T)
 * 
 * 12C LCD Connections to the Arduino Uno
 * SDA : A4
 * SCL : A5
 * GND
 * VCC
 * 
 * Note voltage divider should be connected to the Arduino's
 * GND 
 * A2 
 * also the VOUT & GND of the LM317 
 * See schematic attached on github
 */

//Libraries for the LCD to function 

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity



//Measuring the Voltage
// The Arduino will take 43 measurements of the voltage  then averaged out
#define NUM_SAMPLES 43
int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;



void setup()
{
   //Initialize the LCD screen plus backlight
    lcd.begin(16,2);
    lcd.backlight();

   //Note LCD has 2 rows: 0 (top) & 1 (bottom) 
   //Space count for character placement begins with 0 all the way up to 15
   //Hence the name 16x2 LCD ! 
 
   
   
}
void loop()

{
  // take a number of analog samples and add them up
    while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        delay(10);
    }
    // Calculating  the voltage
    
    // 5.015V is the voltage I measured on my Arduino from the 5V & GND pin using my multimeter when it is powered from a 5V 2.1A power supply
    //replace 5.06 with the Voltage on your Arduino note it will change slighty based on what power source you use! play with this 
    voltage = ((float)sum / (float)NUM_SAMPLES * 5.06) / 1024.0; //5.08 chunky 5V 2A OR 5.04 5V 1A (metropcs) AVERAGE 5.06

      
   
    //Begin Text on First Line
    lcd.setCursor(0, 0); //(space, line #)
    lcd.print(voltage * 11.00); //voltage multiplied by 11 bc voltage divider divides by 11 
    
    //Print the letter V 5 spaces from the voltage number
    lcd.setCursor (5, 0); //(space, line #)
    lcd.print(" V");
    
    sample_count = 0;
    sum = 0;
  

}
