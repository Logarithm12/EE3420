/**
 *  \author Anurag Kumar
 *  \file Lab4Task2.ino
 *  \brief The code to accomplish task 2 of Lab 4 in EE 3420
 *  	   of summer 2020
 */


/* 
 * Copyright (C) 2006-2008 Hans-Christoph Steiner. All rights reserved.
 * Copyright (c) 2010 Arduino LLC. All right reserved.
 * This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * ShiftedLCD library provided by 
 * https://github.com/omersiar/ShiftedLCD
 * author: Ömer Şiar Baysal
 * 
 */
#include <ShiftedLCD.h>

#include <SPI.h>
int sspin = 10;
// initialize the library with the number of the sspin
// (or the latch pin of the 74HC595)
LiquidCrystal lcd(sspin);
String userinput("");
byte colcur = 0;
byte rowcur = 0;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Lab 4 Task 2");
  delay(1000);
  lcd.clear();
  lcd.setCursor(colcur, rowcur);
  lcd.blink();
}

/**
 *  \brief main loop of the function
 *  
 *  \details This handles the logic around sending data to the character LCD
 *  		 and clearing and changing the lines on the LCD display
 *  
 */
void loop() {
  if (Serial.available() > 0) {
    userinput = Serial.readStringUntil('\n');
    if (colcur > 15) {
      if (rowcur == 0) {
		//clear the second line
        for (int i = 0; i < 16; i++) {
          lcd.setCursor(i, 1);
          lcd.print(' ');
        }
        rowcur = 1;
        colcur = 0;
        lcd.setCursor(colcur, rowcur);
        lcd.blink();
      }
      else {
		//clear the first line
        for (int i = 0; i < 16; i++) {
          lcd.setCursor(i, 0);
          lcd.print(' ');
        }
        colcur = 0;
        rowcur = 0;
        lcd.setCursor(colcur, rowcur);
        lcd.blink();
      }
    }
    colcur += userinput.length();
    lcd.print(userinput);
  }
}
