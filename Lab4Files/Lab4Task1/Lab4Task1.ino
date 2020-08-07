/**
 *  \author Anurag KUmar
 *  \file Lab4Task1.ino
 *  \brief The code to accomplish task 1 of Lab 4 in EE 3420
 *  	   of summer 2020
 */

#include <SPI.h>
int latchPin = 10;
long speedMaximum = 500000;
int dataOrder = MSBFIRST;
int dataMode = SPI_MODE0;
unsigned char table[] =
{ 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c
  , 0x39, 0x5e, 0x79, 0x71
};
String userinput = "";

SPISettings mySetting(speedMaximum, dataOrder, dataMode);

/**
 *  \brief takes a hex character and returns the int value of it
 *  
 *  \param [in] in The character to get the hex value of
 *  \return The int value of the character input, or -1 if the input is invalid
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
    default: retVal = -1;
  }
  return retVal;
}


/**
 *  \brief loads a byte on the SPI bus, designed for displaying
 *  	   hex characters on a 7 segment LED
 *  
 *  \param [in] num The hex number to display, as a character
 *  
 *  \details uses the SPI library to send data
 */
void Display(unsigned char num)
{
  SPI.beginTransaction(mySetting);
  digitalWrite(latchPin, LOW);
  int receivedVal = SPI.transfer(table[num]);
  digitalWrite(latchPin, HIGH);
  SPI.endTransaction();
}


void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Please enter the hex character you want to display");
  while (!Serial.available()) {}

  if (Serial.available() > 0) {
    userinput = Serial.readStringUntil('\n');
    if (userinput.length() > 1) {
      Serial.println("The input you entered was invalid");
    }
    else {
      if (hexatoi(userinput.charAt(0)) == -1) {
      Serial.println("The input you entered was invalid");
      }
      else{
        Display(hexatoi(userinput.charAt(0)));
      }

    }
  }
}
