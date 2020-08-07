/**
 * @author: Anurag Kumar
 * @date: July 27th, 2020
 * @description: This program is the code for quiz 2 of the EE3420 course in summer 2020
 *               at Texas State university. It's meant to model a solar panel array control
 *               system that has two 180 degree axes of control
*/

#include <Wire.h>
#define XSERVOADDRESS 0x51
#define ZSERVOADDRESS 0x52
#define SHUNTRESISTANCE 1
#define ASC712PRESENT 0
//These two pins would be attached across a shunt resistor
//or pin A0 would be reading from the ACS712
int currentSensorPin1 = A0;
int currentSensorPin2 = A1;
double mVperAmp = 100; //The ASC712-20A model has 100mV/A  use 185 for 5A Module and 66 for 30A Module
unsigned long mostRecentCheck;
int currentPos[2] = {0, 0};
int optimalPos[2] = {0, 0};


// reads a byte of data from xServo
// Based on https://www.arduino.cc/en/Reference/WireRead
byte readXServo()
{
  byte result;
  Wire.requestFrom(XSERVOADDRESS, 1);    // request 1 byte from XSERVOADDRESS
  while (Wire.available())   // slave may send less than requested
  {
    byte result = Wire.read();    // receive a byte as character
  }
  return result;
  delay(1);
}

// reads a byte of data from zServo
// Based on https://www.arduino.cc/en/Reference/WireRead
byte readZServo()
{
  byte result;
  Wire.requestFrom(ZSERVOADDRESS, 1);    // request 1 byte from ZSERVOADDRESS
  while (Wire.available())   // slave may send less than requested
  {
    byte result = Wire.read();    // receive a byte as character
  }
  return result;
  delay(1);
}


//writes a byte to xServo
// Code based on https://www.arduino.cc/en/Reference/WireWrite
void writeXServo(byte value) {
  Wire.beginTransmission(XSERVOADDRESS);
  Wire.write(value);
  Wire.endTransmission();
  delay(20);
}
// writes a byte to zServo
// Code based on https://www.arduino.cc/en/Reference/WireWrite
void writeZServo(byte value) {
  Wire.beginTransmission(ZSERVOADDRESS);
  Wire.write(value);
  Wire.endTransmission();
  delay(20);
}

#if ASC712PRESENT == 0
//This function reads the current from the solar panel array
//using a shunt resistor technique. However, this is not an ideal method
//as shunt resistor current measurement is often very imprecise, so an
//alternative, more accurate measurement method is also defined
double readCurrent() {
  unsigned int readVoltage1, readVoltage2;
  double pin1Voltage, pin2Voltage, outputCurrent;
  readVoltage1 = analogRead(currentSensorPin1);
  readVoltage2 = analogRead(currentSensorPin2);
  pin1Voltage = readVoltage1 * .00488;
  pin2Voltage = readVoltage2 * .00488;
  outputCurrent = (pin1Voltage - pin2Voltage) / SHUNTRESISTANCE;
  return outputCurrent;
}
#else
//This function reads the current from the solar panel array, but does so
//through a ASC712 hall effect current sensor
//Code based on https://circuits4you.com/2016/05/13/arduino-asc712-current/
double readCurrent() {
  double sensorValue = analogRead(currentSesnsorPin1);
  double voltage = (sensorValue / 1024.0) * 5000; // gets mv
  double amps = (Voltage - 2500) / mVperAmp;
  return amps;
}
#endif

//Writes the wattage to the console
void reportToConsole() {
  double watts = 12.0 * readCurrent();
  Serial.print("The array's output wattage is: ");
  Serial.println(watts, 2);
}

//A simple wrapper function for writing to individual servos
void writePos(byte x, byte z) {
  writeXServo(x);
  writeZServo(z);
  currentPos[1] = x;
  currentPos[2] = z;
}

//This function goes through all of the possible positions
//for the solar panel array and finds the one with the
//highest current
void findOptimalPosition() {
  double currentMax, currentVal;
  byte xMax, zMax;
  for (byte x = 0; x <= 180; x += 10) {
    for (byte z = 0; z <= 180; z += 10) {
      writePos(x, z);
      currentVal = readCurrent();
      if (currentVal > currentMax) {
        currentMax = currentVal;
        xMax = x;
        zMax = z;
      }
    }
  }
  optimalPos[1] = xMax;
  optimalPos[2] = zMax;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Quiz 2");
  //Initialize the solar panel array
  writePos(0, 0); //set the position to a known value
  findOptimalPosition(); //find the optimal position
  writePos(optimalPos[1], optimalPos[2]); //set the panel to the optimal position
  mostRecentCheck = millis();
}

void loop() {
  // put your main code here, to run repeatedly:

  //We don't have to worry about millis() rollover in this scenario,
  //since the unsigned subtraction will undeflow to the higher values

  if (millis() - 1800000 > mostRecentCheck) { // if half an hour has passed since the last check

    //do a check and calibration
    findOptimalPosition();
    writePos(optimalPos[1], optimalPos[2]);
    mostRecentCheck = millis();
  }
  else { // write the wattage of the system to the console
    reportToConsole();
    delay(100);
  }

}
