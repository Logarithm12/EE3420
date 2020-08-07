//EE3420 Quiz 1 problem 2
//Anurag Kumar
long inputvar (0);
String inputString = "";
String isPrimeResult = "";

//checks if the value passed to it is prime
bool isPrime(long val) {
  long testval = sqrt(val)+1;
  if (val == 1)
    return false;
  for (int i = 2; i <= testval; ++i) {
    if (val % i == 0) {
      return false;
    }
  }
  return true;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Please enter a 32 bit integer");
  while (!Serial.available()) {}

  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');
    inputvar = inputString.toInt(); //Apparently this function actually returns a long, go figure
    Serial.println(inputvar);
    isPrime(inputvar) ? isPrimeResult = "prime" : isPrimeResult = "not prime";
    Serial.print("The 32 bit integer is ");
    Serial.println(isPrimeResult);
  }

}
