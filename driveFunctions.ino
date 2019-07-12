void stopMotors()
{
  motorB(0);
  motorC(0);
}
void preset()
{
  posB = 0;
  posC = 0;  
}

void MoveForEnc(int power, int enc)
{
	preset();
	
	while(abs((posB+posC)/2) < enc)
	{
		u = 3*(posC - posB);
		motorB(power + u);
		motorC(power - u);
	}
	if(power > 0) HoldBoth(enc, enc);
	else HoldBoth(-enc, -enc);
}


void HoldBoth(int setPointB, int setPointC) // Hold in pos
{
  unsigned long t = millis() + 1000; //FUTURE
  while(t > millis())
  {
    motorB((setPointB - posB)*3);
    motorC((setPointC - posC)*3);
    delay(10);
  }
  stopMotors();
}

void TurnB(int power, int enc)
{
	preset();
	motorB(power);
	while(abs(posB) < enc);
	
	if(power > 0) HoldBoth(enc, 0);
	else HoldBoth(-enc, 0);
}

void TurnC(int power, int enc)
{
	preset();
	motorC(power);
	while(abs(posC) < enc);
	
	if(power > 0) HoldBoth(0, enc);
	else HoldBoth(0, -enc);
}


void TurnAround(int power, int enc)
{
	preset();
	
	while((abs(posB)+abs(posC))/2 < enc)
	{
		u = 3*(posC + posB);
		motorB(power - u);
		motorC(-power - u);
	}
	if(power > 0) HoldBoth(enc, -enc);
	else HoldBoth(-enc, enc);
}


















void HoldBoth(int setPointB, int setPointC) // Hold in pos
{
  unsigned long t = millis() + 500; //FUTURE
  while(t > millis())
  {
    motorB((setPointB - posB)*3);
    motorC((setPointC - posC)*3);
    delay(10);
  }
  stopMotors();
}

void TurnB(int powerB, int enc) // ну тут даже даун поймет
{
  preset();
  while(abs(posB) < enc)
  {
    motorB(powerB);
    delay(10);
  }
  if(powerB > 0) HoldBoth(enc, posC);// TurnRight
  else HoldBoth(-enc, posC);
  motorB(0);
} 

void TurnC(int powerC, int enc) // oh shit here we go again
{
  preset();
  while(abs(posC) < enc)
  {
    motorC(powerC);
    delay(10);
  }
  if(powerC > 0) HoldBoth(posB, enc);// TurnRight
  else HoldBoth(posB, -enc);
  motorB(0);
} 

void TurnAround(int powerB, int enc) // кружимся на месте как олды
{
  preset();
  while(abs(posB) < enc)
  {
    motorB(powerB);
    motorC(-powerB);
    delay(10);
  }
  if(powerB > 0) HoldBoth(enc, -enc);// TurnRight
  else HoldBoth(-enc, enc);
  stopMotors();
} 

void MoveForEnc2(int power, int enc, bool brake)// Without power ctrl
{
  posB = 0;
  posC = 0;
  int u;
  while(abs(posB) < enc) 
  {
    u = 3*(posC - posB);
    motorB(power+u);
    motorC(power-u);
    delay(10);
  }
  if(brake)
  {
    if(power >= 0)HoldBoth(enc, enc);
    else HoldBoth(-enc, -enc);
  }
  stopMotors();
}