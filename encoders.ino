void doEncoderB()
{
  if(digitalRead(2) == digitalRead(8)) posB++;
  else posB--;
}

void doEncoderC()
{
  if(digitalRead(3) == digitalRead(9)) posC++;
  else posC--;
}