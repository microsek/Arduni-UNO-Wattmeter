#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "EmonLib.h"                   // Include Emon Library

EnergyMonitor emon1;                   // Create an instance

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3f, 20, 4);

int voltageValue = 0; 
float unitValue=0;
float totalunitValue=0;
float power=0;

void setup()
{
  // initialize the LCD
  lcd.init();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  emon1.voltage(2, 260.26, 0);  // Voltage: input pin, calibration, phase_shift
  emon1.current(1, 6.5);       // Current: input pin, calibration.
  delay(2000);
}

void loop()
{
  
  emon1.calcVI(30,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  float voltage   = emon1.Vrms;             //extract Vrms into Variable
  float current   = emon1.Irms;             //extract Irms into Variable
  if (current>0.07)
  {
    power=(voltage*current)/1000;
    unitValue=power*0.000278;
    totalunitValue+=unitValue;
  }
  lcd.setCursor(0, 0);
  lcd.print("Voltage= ");
  lcd.print(voltage);
  lcd.print(" Vac  ");
  lcd.setCursor(0, 1);
  lcd.print("Current= ");
  lcd.print(current);
  lcd.print(" A(ac)  ");
  lcd.setCursor(0, 2);
  lcd.print("Unit = ");
  lcd.print(unitValue);
  lcd.print(" Unit    ");
  lcd.setCursor(0, 3);
  lcd.print("Total unit= ");
  lcd.print(totalunitValue);
  unitValue=0;
  
 delay(1000); // wait 10 milliseconds before the next loop 	// Do nothing here...
}
