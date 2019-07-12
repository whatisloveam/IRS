void first_init()
{
  //motors
  pinMode(4, OUTPUT); //m1 dir
  pinMode(5, OUTPUT); //m1 speed
  pinMode(6, OUTPUT); //m2 speed
  pinMode(7, OUTPUT); //m2 dir
  
  //encoders motorB channels
  pinMode(2, INPUT);
  pinMode(8, INPUT);
  // motorC channels
  pinMode(3, INPUT);
  pinMode(9, INPUT);
  //start communication with computer
  Serial.begin(57600);
  attachInterrupt(0, doEncoderB, CHANGE);// pin2
  attachInterrupt(1, doEncoderC, CHANGE);// pin3
}