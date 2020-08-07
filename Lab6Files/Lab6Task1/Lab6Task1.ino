/**
 *  \author Anurag Kumar
 *  \file Lab6Task1.ino
 *  \brief The code to accomplish task 1 of Lab 6 in EE 3420
 *  	   of summer 2020
 */

#define E1 5 // Enable Pin for motor
#define I1 3 // Control pin 1 for motor 
#define I2 4 // Control pin 2 for motor 

//quick end the program function
void endProgram() {
  while (1) {};
}
void setDCspeed(byte value);
void changeDir();
bool dcMotorDir = 0; //0=CW, 1=CCW
char userOpt;
String inputString = "";
typedef enum {S0 = 0, S25 = 64, S50 = 128, S75 = 192, S100 = 255} dcSpeed;
dcSpeed curMotorState(S0);

/**
 *  \brief This function acts as a state machine to control the state of 
 *         the DC motor to iterate through the phases outlined in the 
 *  	   lab manual
 *  
 *  \param [in] dir The dir argument is the character the user entered
 *  				to determine which way the motor will change behavior
 *  
 *  \details this function is organized into 4 blocks, based on two conditions,
 *  		 the first condition is what character the user entered, and the second
 *  		 condition is what is the current state of the motor. Based on that, each
 *  		 switch statement will change the behaviour of the motor to what is appropriate
 *  		 for the situation
 */
void incrementDir(char dir) {
  if (dir == 'A') { // going more clockwise
    //This is an increase the speed block
    if (dcMotorDir == 0) { // the motor is currently going clockwise
      switch (curMotorState) {
        case S0: curMotorState = S25; setDCspeed(curMotorState); break;
        case S25: curMotorState = S50; setDCspeed(curMotorState); break;
        case S50: curMotorState = S75; setDCspeed(curMotorState); break;
        case S75: curMotorState = S100; setDCspeed(curMotorState); break;
        case S100: break;
        default: Serial.println("Something has gone wrong!");

      }
    }
    //This is a decrease the speed block
    else { // the motor is currently going counter-clockwise
      switch (curMotorState) {
        case S0: changeDir(); curMotorState = S25; setDCspeed(curMotorState); break;
        case S25: curMotorState = S0; setDCspeed(curMotorState); break;
        case S50: curMotorState = S25; setDCspeed(curMotorState); break;
        case S75: curMotorState = S50; setDCspeed(curMotorState); break;
        case S100: curMotorState = S75; setDCspeed(curMotorState); break;
        default: Serial.println("Something has gone wrong!");

      }

    }

  }
  else if (dir == 'B') {// going more counter-clockwise
    //This is a decrease the speed bloack
    if (dcMotorDir == 0) {// the motor is currently going clockwise
      switch (curMotorState) {
        case S0: changeDir(); curMotorState = S25; setDCspeed(curMotorState); break;
        case S25: curMotorState = S0; setDCspeed(curMotorState); break;
        case S50: curMotorState = S25; setDCspeed(curMotorState); break;
        case S75: curMotorState = S50; setDCspeed(curMotorState); break;
        case S100: curMotorState = S75; setDCspeed(curMotorState); break;
        default: Serial.println("Something has gone wrong!");

      }

    }
    //This is an increase the speed block
    else {// the motor is currently going counter-clockwise
      switch (curMotorState) {
        case S0: curMotorState = S25; setDCspeed(curMotorState); break;
        case S25: curMotorState = S50; setDCspeed(curMotorState); break;
        case S50: curMotorState = S75; setDCspeed(curMotorState); break;
        case S75: curMotorState = S100; setDCspeed(curMotorState); break;
        case S100: break;
        default: Serial.println("Something has gone wrong!");

      }

    }
  }

}

/**
 *  \brief This function will control the speed of the 
 *         DC motor
 *  
 *  \param [in] value The value to send to the DC motor controller
 *  
 *  \details This function writes the byte through a PWM signal to
 *  		 the DC motor controller
 */
void setDCspeed(byte value) {
  Serial.print("The direction: ");
  Serial.println(dcMotorDir);
  Serial.print("The speed: ");
  Serial.println(value);

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

// just a quick way to change the dcMotorDir variable
void changeDir() {
  dcMotorDir = !dcMotorDir;
}

/**
 *  \brief The setup function
 *  
 *  \details This initializes the pins and Serial port
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(E1, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  Serial.println("Lab 6 Task 1");
}

/**
 *  \brief the main loop of the function
 *  
 *  \details This controls getting the user input, and sending it to the correct functions
 */
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Please enter the option that you want (enter the character): ");
  Serial.println("A: Move to 100% CW speed");
  Serial.println("B: Move to 100 CCW speed");
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
    case 'A': incrementDir('A'); break;
    case 'B': incrementDir('B'); break;
    case 'Q': setDCspeed(0); Serial.println("The program has ended"); endProgram(); break;
    case 'q': setDCspeed(0); Serial.println("The program has ended"); endProgram(); break;
    case 'F': setDCspeed(0); Serial.println("The program has ended"); endProgram(); break;
    case 'f': setDCspeed(0); Serial.println("The program has ended"); endProgram(); break;
    case '#': setDCspeed(0); Serial.println("The program has ended"); endProgram(); break;
    default: Serial.println("You didn't choose a valid option!");
  }

}
