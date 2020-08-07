/**
 *  \author Anurag Kumar
 *  \file Lab3Task1.ino
 *  \brief The code used to complete Lab 3 for EE 3420 
 *  	   in the summer session of 2020 at Texas State University
 */

#include <Keypad.h>
#include <LiquidCrystal.h>


String dong{""};
char ding("");

//start of The things used to initialize the keypad and LCD character display
byte row0 = A5;
byte row1 = A4;
byte row2 = A3;
byte row3 = A2;

byte col0 = 9;
byte col1 = 10;
byte col2 = 11;
byte col3 = 12;
byte i = 0;

//int hexatoi(char in);
const byte rows = 4;
const byte cols = 4;

//The code for initializing the Keypad library
char keys[rows][cols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'E', '0', 'F', 'D'}
};
byte line1cur = 0;
byte line2cur = 0;
byte rowPins[rows] = {row0, row1, row2, row3};
byte colPins[cols] = {col0, col1, col2, col3};
Keypad custkeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols);

//The code for initializing the LCD library
const int rs = 2, rw = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);
// end of the things used to initialize the keypad and LCD character display


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Lab 3 Task 1");
}

/**
 *  \brief The main loop
 *  
 *  \details This function contains the logic used to implement the lab
 *  		 It accomplishes it through two logical blocks, one for the	
 *  		 first line of the character LCD, and one for the second
 */
void loop() {
	
  //The control section for the first line of the
  //character lcd, controlled by the serial port
  if (Serial.available() > 0) {
    dong = Serial.readStringUntil('\n');

    if (line1cur > 15) {
      for (int i = 0; i < 16; i++) {
        lcd.setCursor(i, 0);
        lcd.print(' ');
      }
      line1cur = 0;
    }

    lcd.setCursor(line1cur, 0);
    line1cur += dong.length();
    lcd.print(dong);
  }
  //The control for the second line of the 
  //character lcd, controlled by the keypad
  else {
    ding = custkeypad.getKey();

    if (ding) {
      if (line2cur > 15) {
        for (int i = 0; i < 16; i++) {
          lcd.setCursor(i, 1);
          lcd.print(' ');
        }
        line2cur = 0;
      }

      lcd.setCursor(line2cur, 1);
      ++line2cur;
      lcd.print(ding);
    }

  }


}
