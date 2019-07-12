int s[5], maxi[5] = {600, 600, 600, 600, 600 }, 
		  mini[5] = {300, 300, 300, 300, 300 };

volatile int posB = 0; //encoderB
volatile int posC = 0; //encoderC

void setup()
{
  first_init();
  
}

void loop()
{
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.print(analogRead(A2));
  Serial.print(" ");
  Serial.print(analogRead(A3));
  Serial.print(" ");
  Serial.println(analogRead(A4));
  delay(30);
}