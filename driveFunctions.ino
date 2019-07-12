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
