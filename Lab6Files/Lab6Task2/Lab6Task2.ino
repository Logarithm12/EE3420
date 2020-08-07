/**
 *  \author Anurag Kumar
 *  \file Lab6Task2.ino
 *  \brief The code to accomplish task 2 of Lab 6 in EE 3420
 *  	   of summer 2020
 */

#include <Servo.h>

Servo myservo;
char userOpt;
String inputString = "";
int servoPosMicro = 1000;

//quick end the program function
void endProgram() {
  while (1) {};
}

/**
 *  \brief This function acts as a simple state machine
 *         to control the servo motor
 *  
 *  \param [in] value the character the user input
 */
void increment(char value) {
  if (value == 'A') {
    if (servoPosMicro > 1000) {
      servoPosMicro -= 50;
      myservo.writeMicroseconds(servoPosMicro);
    }
  }
  else if (value == 'B') {
    if (servoPosMicro < 2000) {
      servoPosMicro += 50;
      myservo.writeMicroseconds(servoPosMicro);
    }
  }
Serial.print("Servo position: ");
Serial.println(servoPosMicro);
}

/**
 *  \brief The setup function
 *  
 *  \details This initializes the pins and Serial port
 */
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  Serial.begin(9600);
  Serial.println("Lab 6 Task 2");
  myservo.writeMicroseconds(1000);
}

/**
 *  \brief the main loop of the function
 *  
 *  \details This controls getting the user input, and sending it to the correct functions
 */
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Please enter the option that you want (enter the character): ");
  Serial.println("A: Move towards 1ms");
  Serial.println("B: Move towards 2ms");
  Serial.println("Q,q,F,f,#: End the program");

  while (!Serial.available()) {}
  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');
    if (inputString.length() > 1) {
      userOpt = 'G';
    }
    else {
      userOpt = inputString.charAt(0);
    }
  }
  switch (userOpt) {
    case 'A': increment('A'); break;
    case 'B': increment('B'); break;
    case 'Q': Serial.println("The program has ended"); endProgram(); break;
    case 'q': Serial.println("The program has ended"); endProgram(); break;
    case 'F': Serial.println("The program has ended"); endProgram(); break;
    case 'f': Serial.println("The program has ended"); endProgram(); break;
    case '#': Serial.println("The program has ended"); endProgram(); break;
    default: Serial.println("You didn't choose a valid option!");
  }

}
