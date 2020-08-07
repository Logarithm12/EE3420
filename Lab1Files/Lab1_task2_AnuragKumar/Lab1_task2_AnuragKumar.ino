/**
 * @author Anurag Kumar
 * @filename Lab1_task2_AnuragKumar
 * @description This program is designed to run on the
 * arduino and interface with a user through serial communication
 * and get two nonnegative integers with a max of one zero, and generate
 * a fibonacci sequence with it.
 *
 */




unsigned long fibonum = 0;
int i = 0;
int vals[2];
String ding;

/**
 * @author Anurag Kumar
 * @description The setup function is run once and intended
 * to setup any needed things prior to the loop function
 * 
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start Lab 1 Task 2");
  Serial.println("Please enter two non-negative integers, at least one of which is not zero");

}
/**
 * @author Anurag Kumar
 * @description The loop function is the main function that
 * runs the code that queries the user for inputs, and calls
 * the fibonacci number generator when all conditions are met.
 */
void loop() {
  Serial.println(" ");
  Serial.print("Please enter number: ");
  Serial.println(i);
  while (!Serial.available()) {}

  if (Serial.available() > 0) {
    ding = Serial.readStringUntil('\n');
    Serial.print("I got: ");
    Serial.print(ding + '\n');
    vals[i] = ding.toInt();
  }
  Serial.print("Vals[");
  Serial.print(i);
  Serial.print("]: ");
  Serial.println(vals[i]);
  Serial.print(" ");
  ++i;

//Checking if the inputs match the req, and if so,
//sending them to the fibonacci function
  if (i == 2) {
    if (vals[1] <= 0 && vals[0] <= 0) {
      Serial.println("Nonegative numbers and max of 1 zero");
      i-=2;
    } else {
      Serial.println("Fibonacci Sequence: ");
      genFibo((long) vals[0], (long) vals[1]);
      Serial.println("New run");
	  i-=2;
    }
  }
}

/**
 * @author Anurag Kumar
 * @description The genFibo function generates fibonacci numbers
 * based on two long initial seeds, which are the first two numbers
 * in the sequence.
 * @param seed1, seed2: the first two numbers of the fibo seq to be 
 * generated
 * 
 *
 */
void genFibo(long seed1, long seed2) {
  fibonum = seed1 + seed2;
  unsigned long prevnum = seed2;
  unsigned long nextnum;
  Serial.print(seed1);
  Serial.print(",");
  Serial.print(seed2);
  Serial.print(",");
  Serial.print(fibonum);
  Serial.print(",");
  
  //This loop generates the fibonacci numbers past the first
  //iteration
  while (fibonum >= prevnum) {
    nextnum = fibonum + prevnum;
    prevnum = fibonum;
    fibonum = nextnum;
    if (fibonum > prevnum) {
      Serial.print(fibonum);
      if (nextnum < fibonum + prevnum)
        Serial.print(", ");
    }

  }
}
