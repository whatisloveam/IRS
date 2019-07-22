int s[5], maxi[5] = {800, 800, 700, 800, 530 }, 
		  mini[5] = {30, 30, 30, 30, 30 };

volatile int posB = 0; //encoderB
volatile int posC = 0; //encoderC

bool prevCurve = false;//

struct Cord // coord record
{
  int x , y; 
};

struct Location
{
  bool lw;//left wall
  bool uw;//up wall
};
Location ProgMaze[5][9];

int dx[4] = { 1, 0, -1, 0 }; // offset by х
int dy[4] = { 0, -1, 0, 1 }; // offset by y
int lastDir = 0;
int myDir = 0;// robotDirection 0 - right, 1 - top, 2 - left, 3- bottom
bool IsTurnRight = false;

Cord stPos;
Cord FinPos;


void setup()
{
  stPos.x = 0;
  stPos.y = 0;
  FinPos.x = 4;
  FinPos.y = 3;
  
  first_init();// helper reference
  init_maze();
  
  checkFirstWalls();

  while(1)
  {
    if(Compute(stPos.x, stPos.y, FinPos.x, FinPos.y, true))
    {
      stPos.x += dx[lastDir];
      stPos.y += dy[lastDir]; 
      Serial.print("Pos: ");
      Serial.print(stPos.x);
      Serial.print(" ");
      Serial.println(stPos.y);
    }
    else 
    {
      if(prevCurve)
      {
        MoveOneCell(150, 810);
               
        stPos.x += dx[myDir];
        stPos.y += dy[myDir]; 
      }
      break;
    }
  }
  HoldBoth(posB, posC);
  
  while(1)
  {
    PrintSensorValues();
  }
}

void loop()
{
  delay(30);
}
