void motorB(int power)
{
  power = constrain(power, -255, 255);
  if(power > 0)
  {
    digitalWrite(4, 0);
    analogWrite(5, power);
  }
  else
  {
    digitalWrite(4, 1);
    analogWrite(5, 255+power);
  }
}

void motorC(int power)
{
  power = constrain(power, -255, 255);
  if(power > 0)
  {
    digitalWrite(7, 0);
    analogWrite(6, power);
  }
  else
  {
    digitalWrite(7, 1);
    analogWrite(6, 255+power);
  }
}