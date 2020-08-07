//EE3420 Quiz 1 problem 2
//Anurag Kumar
unsigned int var1 = 10;
int var2 = 20;
void setup() {
  // put your setup code here, to run once:
  //need to configure the serial port for 9600 baud
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(var1);
  Serial.println(var2);

}
