int s[5], maxi[5] = {750, 750, 750, 750, 750 }, 
		  mini[5] = {30, 30, 30, 30, 30 };

volatile int posB = 0; //encoderB
volatile int posC = 0; //encoderC

void setup()
{
  first_init();
  LineForAnyCross(150);
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
