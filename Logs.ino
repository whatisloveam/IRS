void LogGetCoord()
{
    Serial.print("StartCoord: ");
    Serial.print(" ");
    Serial.print(stPos.x);
    Serial.print(" ");
    Serial.println(stPos.y);
}

void PrintSensorValues()
{
  UpdSen();
  Serial.print("L ");
  for(int i = 0; i < 4; i++)
  {
    Serial.print(s[i]);
    Serial.print(' ');
  }
  Serial.print(s[4]);
  Serial.print(' ');
  Serial.print(posB);
  Serial.print(' ');
  Serial.println(posC);
  delay(50);
}

void PrintSensorsRanges()
{
  UpdSen();
  for(int jo=0;jo<5;jo++)
  {
   Serial.print(s[jo]);
   Serial.print('\t');
  }
  Serial.println();
  for(int jo=0;jo<5;jo++)
  {
   Serial.print(mini[jo]);
   Serial.print('\t');
  }
  Serial.println();
  for(int jo=0;jo<5;jo++)
  {
   Serial.print(maxi[jo]);
   Serial.print('\t');
  }
  Serial.println();
  delay(300);
}
