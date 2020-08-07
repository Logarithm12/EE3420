/**
 *  \author Anurag Kumar
 *  \file Lab5Task1.ino
 *  \brief The code to accomplish task 1 of Lab 5 in EE 3420
 *  	   of summer 2020
 */
 
#include <Stepper.h>
//#define STEPS 2048
//Stepper small_stepper(STEPS, 8, 10, 9, 11);
String inputString("");
int inputSteps(0);
int inputSpeed(0);
bool inputDirection(0);
int inputvar(0);
Stepper* small_stepper; // a stepper object pointer

/**
 *  \brief the setup function
 *  
 *  \details this function controls the initialization of the
 *  		 first stepper motor control object, based on the
 *  		 user input
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Please enter the number of steps for 1 full revolution");
  while (!Serial.available()) {}
  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');
    Serial.print("I got: ");
    Serial.println(inputString);
    inputSteps = inputString.toInt();
  }
  Serial.println("Please enter the rpm of the motor");
  while (!Serial.available()) {}
  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');
    Serial.print("I got: ");
    Serial.println(inputString);
    inputSpeed = inputString.toInt();
  }

  Serial.println("Please enter the initial direction of rotation 0 = CCW, 1 = CW");
  while (!Serial.available()) {}
  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');
    Serial.print("I got: ");
    Serial.println(inputString);
    inputDirection = inputString.toInt();
  }
  small_stepper = new Stepper(inputSteps, 8, 10, 9, 11);
  small_stepper->setSpeed(inputSpeed);

}

/**
 *  \brief main loop of the function
 *  
 *  \details This loop handles getting the user input, and changing the
 *  		 the number of steps, rpm, and direction of the motor after
 *  		 initialization, as well as the actual operation of the motor
 */
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Please enter the option that you want (enter the number): ");
  Serial.println("1: Change number of steps for 1 full revolution");
  Serial.println("2: Change Stepper RPM");
  Serial.println("3: Change rotation of direction");
  Serial.println("4: Advance the motor a number of steps");

  while (!Serial.available()) {}
  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');
    inputvar = inputString.toInt();
  }
  Stepper* tmp;

  switch (inputvar) {
    case 1:
      Serial.println("Option 1 chosen");
      Serial.println("Please enter the number of steps for 1 full revolution");
      while (!Serial.available()) {}
      if (Serial.available() > 0) {
        inputString = Serial.readStringUntil('\n');
        Serial.print("I got: ");
        Serial.println(inputString);
        inputSteps = inputString.toInt();
      }
	  //need to do this to avoid memory leaks
      tmp = small_stepper;
      delete tmp; tmp = 0;
      small_stepper = new Stepper(inputSteps, 8, 9, 10, 11);
      small_stepper->setSpeed(inputSpeed);
      break;
    case 2:
      Serial.println("Option 2 chosen");
      Serial.println("Please enter the rpm of the motor");
      while (!Serial.available()) {}
      if (Serial.available() > 0) {
        inputString = Serial.readStringUntil('\n');
        Serial.print("I got: ");
        Serial.println(inputString);
        inputSpeed = inputString.toInt();
      }
      small_stepper->setSpeed(inputSpeed);
      break;
    case 3:
      Serial.println("Option 3 chosen");
      Serial.println("Please enter the direction of rotation 0 = CCW, 1 = CW");
      while (!Serial.available()) {}
      if (Serial.available() > 0) {
        inputString = Serial.readStringUntil('\n');
        Serial.print("I got: ");
        Serial.println(inputString);
        inputDirection = inputString.toInt();
      }
      break;
    case 4:
      Serial.println("Option 4 chosen");
      Serial.println("Please enter the number of steps to rotate the motor");
      while (!Serial.available()) {}
      if (Serial.available() > 0) {
        inputString = Serial.readStringUntil('\n');
        Serial.print("I got: ");
        Serial.println(inputString);
        inputSteps = inputString.toInt();
      }
      (inputDirection) ? small_stepper->step(-inputSteps) : small_stepper->step(inputSteps);
      break;
    default:
      Serial.println("You didn't choose one of the options!");
  }

}
