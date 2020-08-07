//EE3420 Quiz 1 problem 6
//Anurag Kumar

#include <SPI.h>

long speedMaximum = 500000;
int dataOrder = MSBFIRST;
int dataMode = SPI_MODE1;
int latchPin = 10;
byte setMotorSpeed(0);
byte motorSpeed(0);
SPISettings mySetting(speedMaximum, dataOrder, dataMode);

byte writeSPI(byte data) {
  SPI.beginTransaction(mySetting);
  digitalWrite(latchPin, LOW);
  byte receivedVal = SPI.transfer(data);
  digitalWrite(latchPin, HIGH);
  SPI.endTransaction();
  return receivedVal;
}

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  pinMode(latchPin, OUTPUT);
  digitalWrite(latchPin, HIGH);
  motorSpeed = writeSPI(setMotorSpeed);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (motorSpeed < 100 && setMotorSpeed < 255) {
    motorSpeed = writeSPI(++setMotorSpeed);
  }
  else if (motorSpeed > 100 && setMotorSpeed > 0) {
    motorSpeed = writeSPI(--setMotorSpeed);
  }
  else{
    motorSpeed = writeSPI(setMotorSpeed);
  }

}
