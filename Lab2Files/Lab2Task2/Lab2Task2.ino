/**
 *  \author Anurag Kumar
 *  \file Lab2Task2.ino
 *  \brief The code used to run task 2 of lab 2
 *  	   for the Texas State EE 3420 of Summer 2020
 */


#include <Keypad.h>

int hexatoi(char in);

//provided by the lab manual
byte digit_pattern[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                          0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
                         };
byte led7segA = 13;
byte led7segB = 12;
byte led7segC = 11;
byte led7segD = 10;
byte led7segE = 9;
byte led7segF = 8;
byte led7segG = 7;

// start all of the initializing of the keypad
byte row0 = A0;
byte row1 = A1;
byte row2 = A2;
byte row3 = A3;

byte col0 = A4;
byte col1 = A5;
byte col2 = 4;
byte col3 = 3;
byte i = 0;

const byte rows = 4;
const byte cols = 4;

//The 2d character array representing the keypad being used
char keys[rows][cols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'E', '0', 'F', 'D'}
};
byte rowPins[rows] = {row0, row1, row2, row3};
byte colPins[cols] = {col0, col1, col2, col3};
Keypad custkeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols);
// end of the initializing of the keypad

void led_4control(int value);
void led_7segControl(int value);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //7 segment LED
  pinMode(led7segA, OUTPUT);
  pinMode(led7segB, OUTPUT);
  pinMode(led7segC, OUTPUT);
  pinMode(led7segD, OUTPUT);
  pinMode(led7segE, OUTPUT);
  pinMode(led7segF, OUTPUT);
  pinMode(led7segG, OUTPUT);

}
/**
 *  \brief the main loop
 *  
 *  \details Only used to capture the input from the keypad
 *  		 and send it to the control functions
 */
void loop() {
  // put your main code here, to run repeatedly:
  char inputkey = custkeypad.getKey();
  if (inputkey) {
    led_7segControl(hexatoi(inputkey));
  }
}

/**
 *  \brief a function to control to the 7 segment LED
 *  
 *  \param [in] value the hex value to display on the device
 *  
 *  \details This works by selecting whether or not to turn a bit on
 *  		 through a digit pattern array defined globally, alongside
 *  		 digital pin control
 */
void led_7segControl(int value) {
  digitalWrite(led7segA, 0x01 & digit_pattern[value]);
  digitalWrite(led7segB, 0x02 & digit_pattern[value]);
  digitalWrite(led7segC, 0x04 & digit_pattern[value]);
  digitalWrite(led7segD, 0x08 & digit_pattern[value]);
  digitalWrite(led7segE, 0x10 & digit_pattern[value]);
  digitalWrite(led7segF, 0x20 & digit_pattern[value]);
  digitalWrite(led7segG, 0x40 & digit_pattern[value]);
  //digitalWrite(led7egA, 0x80 & digit_pattern[value]);
}

/**
 *  \brief an atoi function for 1-digit hex characters
 *  
 *  \param [in] in the character to be converted
 *  \return the int value of the character parameter
 *  
 */
int hexatoi(char in) {
  int retVal = 0;
  switch (in) {
    case '0': retVal = 0; break;
    case '1': retVal = 1; break;
    case '2': retVal = 2; break;
    case '3': retVal = 3; break;
    case '4': retVal = 4; break;
    case '5': retVal = 5; break;
    case '6': retVal = 6; break;
    case '7': retVal = 7; break;
    case '8': retVal = 8; break;
    case '9': retVal = 9; break;
    case 'A': retVal = 0xA; break;
    case 'B': retVal = 0xB; break;
    case 'C': retVal = 0xC; break;
    case 'D': retVal = 0xD; break;
    case 'E': retVal = 0xE; break;
    case 'F': retVal = 0xF; break;
  }

  return retVal;
}
