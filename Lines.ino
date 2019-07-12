int err, prevErr;
int u;
float kp, kd;

void UpdSen()
{
  s[0] = map(analogRead(A0), maxi[0], mini[0], 0, 100); 
  s[1] = map(analogRead(A1), maxi[1], mini[1], 0, 100);
  s[2] = map(analogRead(A2), maxi[2], mini[2], 0, 100);
  s[3] = map(analogRead(A3), maxi[3], mini[3], 0, 100);  
  s[4] = map(analogRead(A4), maxi[4], mini[4], 0, 100);  
}


void PDAction(int power) // one iteration of PD regulator
{
    UpdSen();
    
    err = s[1] - s[2];
    u = err*kp + (err - prevErr)*kd;
    prevErr = err;
    
    motorB(power + u);
    motorC(power - u);
    delay(10);
}
void setArgs(float kpArg, float kdArg)
{
	kp = kpArg;
	kd = kdArg;
}

void LineForCross(int power) // really? I have nothing to explain in this case
{
  preset();
  setArgs(2, 4);
  while(1)
  {
    PDAction(power);
    if(s[0] < 30 && s[3] < 30) // this is cross condition
    {
      HoldBoth(posB, posC);
      break;
    }
  }
}
