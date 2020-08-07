#include <dht11.h>
#include <ShiftedLCD.h>
#include <Wire.h>
#include <SPI.h>

#define LUXRSVAL 10000.0 // lux sensor resistance val
#define LUXPIN A0
#define TEMP_PIN A1 // thermistor sensor pin
#define DHT11PIN 7
#define V_IN 5.0
#define eeprom_address 0x50
#define E1 5 // Enable Pin for motor
#define I1 3 // Control pin 1 for motor 
#define I2 4 // Control pin 2 for motor 
#define INTERRUPTPIN 2 // Button-triggered interrupt pin
#define SSPIN 10
#define LEDPIN 6
#define LUX_CALC_SCALAR           12518931
#define LUX_CALC_EXPONENT         -1.405

dht11 DHT11;
bool dcMotorDir = 0; //0=CW, 1=CCW
LiquidCrystal lcd(SSPIN);
byte LEDlevel;
volatile int temperature;
volatile int luxlevel;
volatile int fancycle;
int MemAddress=0;

// Based on the work by David Williams
// https://www.allaboutcircuits.com/projects/design-a-luxmeter-using-a-light-dependent-resistor/
// The physical constants are not calibrated to this particular photoresistor
// but that is ignored for this calculation
int getLux() {
  int   ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;

  // Perform the analog to digital conversion
  ldrRawData = analogRead(LUXPIN);

  // RESISTOR VOLTAGE_CONVERSION
  // Convert the raw digital data back to the voltage that was measured on the analog pin
  resistorVoltage = (float)ldrRawData / 1023 * 5.0;

  // voltage across the LDR is the 5V supply minus the 5k resistor voltage
  ldrVoltage = 5 - resistorVoltage;

  // LDR_RESISTANCE_CONVERSION
  // resistance that the LDR would have for that voltage
  ldrResistance = ldrVoltage / resistorVoltage * LUXRSVAL;

  // LDR_LUX
  // Change the code below to the proper conversion from ldrResistance to
  // ldrLux
  ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
  return (int) ldrLux;
}

int getTemp() {

  //  int chk = DHT11.read(DHT11PIN);
  //  double fahren = DHT11.temperature;
  //  switch (chk)
  //  {
  //    case DHTLIB_OK:
  //      Serial.println("OK");
  //      break;
  //    case DHTLIB_ERROR_CHECKSUM:
  //      Serial.println("Checksum error");
  //      break;
  //    case DHTLIB_ERROR_TIMEOUT:
  //      Serial.println("Time out error");
  //      break;
  //    default:
  //      Serial.println("Unknown error");
  //      break;
  //  }
  //  return fahren;

  // The DHT11 unit is non-functional, so temperature will be done through a thermistor

  // this is copied over from the getLux method, as everything but the final
  // calculation will be different
  int   ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;

  // Perform the analog to digital conversion
  ldrRawData = analogRead(TEMP_PIN);

  // RESISTOR VOLTAGE_CONVERSION
  // Convert the raw digital data back to the voltage that was measured on the analog pin
  resistorVoltage = (float)ldrRawData / 1023 * 5.0;

  // voltage across the LDR is the 5V supply minus the 5k resistor voltage
  ldrVoltage = 5 - resistorVoltage;

  // LDR_RESISTANCE_CONVERSION
  // resistance that the LDR would have for that voltage
  ldrResistance = ldrVoltage / resistorVoltage * LUXRSVAL;

  // This part was taken/based on
  // https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/
  // since he went through the trouble of calculating the constants for 10k @ 25C NTC thermistors
  float logR2, R2, T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  logR2 = log(ldrResistance);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;
  T = (T * 9.0) / 5.0 + 32.0;
  return (int) T;
}


int getHumid() {
  //unfortunately, the DHT11 unit is non-functional, so this
  //function is not valid to use any longer.
  //  int chk = DHT11.read(DHT11PIN);
  //  switch (chk)
  //  {
  //    case DHTLIB_OK:
  //      Serial.println("OK");
  //      break;
  //    case DHTLIB_ERROR_CHECKSUM:
  //      Serial.println("Checksum error");
  //      break;
  //    case DHTLIB_ERROR_TIMEOUT:
  //      Serial.println("Time out error");
  //      break;
  //    default:
  //      Serial.println("Unknown error");
  //      break;
  //  }
  //  double humid = DHT11.humidity;
  //  return humid;

  //instead this will just be a 0 value
  return 0;
}

void isrfunc() {
  //to be completed
  Serial.println("Interrupt Called");
  Serial.print("Lux: ");
  Serial.println(luxlevel);
  Serial.print("Temperature: ");
  Serial.println(getTemp());
  Serial.print("Fan Duty Cycle: ");
  Serial.print(((fancycle / 255.0) * 100.0));
  Serial.println("%");
}

//Celsius to Fahrenheit conversion
double fTemp(double celsius)
{
  return 1.8 * celsius + 32;
}


void setDCspeed(byte value) {
  if (dcMotorDir == 0) {
    //clockwise
    analogWrite(E1, value); //writing the speed value
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    delay(500);
  }
  else {
    //counter-clockwise
    analogWrite(E1, value); //writing the speed value
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    delay(500);

  }
}

void writeData(unsigned int eaddress, byte data)
{
  Wire.beginTransmission(eeprom_address);
  // set the pointer position
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.write(data);
  Wire.endTransmission();
  delay(10); // should be enough to complete the write cycle spec says 5 mS
}

// reads a byte of data from memory location eaddress
byte readData(unsigned int eaddress)
{
  byte result;
  Wire.beginTransmission(eeprom_address);
  // set the pointer position
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(eeprom_address, 1); // get the byte of data
  result = Wire.read();
  return result;
}

void doTempWork() {
  temperature = getTemp();
  if (temperature < 70) {
    fancycle = 77; //30%
  } else if (temperature >= 70 && temperature < 80) {
    fancycle = 179; //70%
  } else if (temperature >= 80) {
    fancycle = 255; //100%
  }
  //setDCspeed(fancycle);
}

void doLuxWork() {
  luxlevel = getLux();
  if (luxlevel < 45) {
    LEDlevel += 12; //analogwrite has a 0-255 range, and 255/20 is 12.75, so 12 is approx 5%
  } else if (luxlevel > 55) {
    LEDlevel -= 12;
  }
  analogWrite(LEDPIN, LEDlevel);
}

void doLCDWork() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp(F): ");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("Lux: ");
  lcd.print(luxlevel);
}

void doLogWork() {
  //These need to be cast to bytes in order to be written into the IIC memory easily
  //This should be fine, since the operating values of these would likely
  //not exceed the byte range
  byte tlog = (byte) temperature;
  byte llog = (byte) luxlevel;
  writeData(MemAddress, tlog);
  writeData(MemAddress+1,llog);
  writeData(MemAddress+2,fancycle);
  MemAddress+=3;

}

void readFromMem(){
  if(MemAddress !=0){
    Serial.println("Read from Memory");
    Serial.print("Temp: ");
    Serial.println(readData(MemAddress-3));
    Serial.print("Lux: ");
    Serial.println(readData(MemAddress-2));
    Serial.print("Fancycle: ");
    Serial.println(readData(MemAddress-1));
    
  }
}

//byte PWMValue = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  pinMode(INTERRUPTPIN, INPUT_PULLUP);
  pinMode(E1, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPTPIN), isrfunc, LOW);
  Serial.println("Lab 8 Task 1");
  lcd.print("Lab 8 Task 1");
  delay(500);
  lcd.clear();
}

void loop() {
  doLuxWork();
  doTempWork();
  doLCDWork();
  doLogWork();
  delay(500);
  readFromMem();

}
