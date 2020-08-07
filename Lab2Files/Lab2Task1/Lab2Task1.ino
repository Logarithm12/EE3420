/**
 *  \author Anurag Kumar
 *  \file Lab2Task2.ino
 *  \brief The code used to run task 2 of lab 2
 *  	   for the Texas State EE 3420 of Summer 2020
 *
 */

// provided by the lab manual
int digit_pattern[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                         0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
                        };

int led3 = A2;
int led2 = A3;
int led1 = A4;
int led0 = A5;

int led7segA = 13;
int led7segB = 12;
int led7segC = 11;
int led7segD = 10;
int led7segE = 9;
int led7segF = 8;
int led7segG = 7;

int i = 0;

/**
 *  \brief the setup function
 *  
 *  \details initializes the pins for use
 */
void setup() {
  //4 discrete LEDs
  pinMode(led3, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led0, OUTPUT);
  //7 segment LEDs
  pinMode(led7segA, OUTPUT);
  pinMode(led7segB, OUTPUT);
  pinMode(led7segC, OUTPUT);
  pinMode(led7segD, OUTPUT);
  pinMode(led7segE, OUTPUT);
  pinMode(led7segF, OUTPUT);
  pinMode(led7segG, OUTPUT);
  //2 button inputs
  pinMode(A0, INPUT_PULLUP); // increment
  pinMode(A1, INPUT_PULLUP); // decrement

}
/**
 *  \brief the main loop
 *  
 *  \details this controls the counter for the assignment
 *  		 as well as reads the button input
 */
void loop() {
  // put your main code here, to run repeatedly:
  led_4control(i);
  led_7segControl(i);
  //detect which button was input
  if (digitalRead(A0) == LOW) {
    ++i;
    //debounce the input
    while (digitalRead(A0) == LOW) {
      delay(100);
    }
    //control the display rollover
    if (i == 16) {
      i = 0;
    }
  }
  if (digitalRead(A1) == LOW) {
    //debounce the input
    while (digitalRead(A1) == LOW) {
      delay(100);
    }
    --i;
    //control the display rollover
    if (i == -1) {
      i = 15;
    }
  }


}

/**
 *  \brief a function to control to the 4 discrete LEDs
 *  
 *  \param [in] value the hex value to display on the device
 *  
 *  \details This works by selecting whether or not to turn a bit on
 *  		 through using the value that the LED is represents intersected
 *  		 with the value being displayed
 */
void led_4control(int value) {
  //control 4 leds to display 0-F in binary
  digitalWrite(led3, 0x8 & value);

  digitalWrite(led2, 0x4 & value);

  digitalWrite(led1, 0x2 & value);

  digitalWrite(led0, 0x1 & value);
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
}
