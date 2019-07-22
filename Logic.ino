int Mark[5][9];

bool IsLeftWall,IsUpWall,IsRightWall;

void init_maze()
{
  for (int y = 0; y < 5; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      ProgMaze[y][x].lw = 0;
      ProgMaze[y][x].uw = 0;

      if (x == 0 || x == 8) ProgMaze[y][x].lw = 1;
      if (y == 0 || y == 4) ProgMaze[y][x].uw = 1;
    }
  }
  ResetMarks();
}

void ResetMarks()
{
  for (int y = 0; y < 5; y++)
    for (int x = 0; x < 9; x++)
        Mark[y][x] = 0;
}

bool Compute(int xs, int ys, int xf, int yf, bool check)//main compute function
{
    ResetMarks();
    Mark[ys][xs] = 1;
    if(check) // check walls first if you want
    {
      if(prevCurve)
      {
        setWalls(xs,ys, false);
        if(IsTurnRight) myDir = (myDir + 3) % 4; //change position to right
        else myDir = (myDir + 1) % 4; // change position to left
      }
      else setWalls(xs,ys,true);
    }
    
    int x, y;
    if (Solve(xf, yf))
    {
        x = xf;
        y = yf;
        for (int N = Mark[yf][xf]; N > 1; N--)
        {
            for (int i = 0; i < 4; i++)
            {
                if (CanGo(x, y, dx[i], dy[i]) && 
                Mark[y + dy[i]][x + dx[i]] == N - 1)
                {
                    x += dx[i];
                    y += dy[i];
                    lastDir = i;
                    break;
                }
            }
        }
        lastDir = (lastDir + 2) % 4;// return direction
        
        if(myDir != lastDir) // some shitty turn logic
        {
          if(abs(lastDir - myDir) == 2) //turn 180
          {
            TurnAround(150, 400);
            TurnAroundSens(120);
            myDir = lastDir;
          }
          if(prevCurve) lastDir = myDir; // we can't change direction on curve
          else
          {
            if(lastDir - myDir == 1 || lastDir - myDir == -3)  //turn left
            {
              TurnAround(-130, 120); 
              TurnAroundSens(-120); 
            }
            if(lastDir - myDir == 3 || lastDir - myDir == -1) // turn right
            {
              TurnAround(130, 120);
              TurnAroundSens(120);
            }
            myDir = lastDir;
          }            
        }
        MoveOneCell(150, 800);
        return true;
    }
    else return false;
}

bool Solve(int xf, int yf)
{
  int N = 1;
  bool NoSolution;

  do
  {
    NoSolution = true;
    for (int x = 0; x < 8; x++)
      for (int y = 0; y < 4; y++)
        if(Mark[y][x] == N)
        {
          for (int i = 0; i < 4; i++)
            if (CanGo(x, y, dx[i], dy[i]) 
            && Mark[y + dy[i]][x + dx[i]] == 0)
            {
              NoSolution = false;
              Mark[y + dy[i]][x + dx[i]] = N + 1;
              if (x + dx[i] == xf && y + dy[i] == yf)
                  return true;
            }
        }                            
    N++;
  }
  while (NoSolution == false);
  return false;
}

bool CanGo(int x, int y, int dx, int dy)
{
    if (dx == -1) return !ProgMaze[y][x].lw;
    else if (dx == 1) return !ProgMaze[y][x + 1].lw;
    else if (dy == -1) return !ProgMaze[y][x].uw;
    else return !ProgMaze[y + 1][x].uw;
}

void setWalls(int xs, int ys, bool checkFront)
{
  bool sl, su, sr;
  UpdSen();
  if(checkFront) su = s[4] > 50;
  else su = IsUpWall;
  sl = IsLeftWall;
  sr = IsRightWall;

  if(myDir == 0) // dx = 1 right
  {
    ProgMaze[ys][xs].uw = sl;
    ProgMaze[ys][xs+1].lw = su;
    ProgMaze[ys+1][xs].uw = sr;
  }
  else if (myDir == 1) // dy = -1 up
  {
    ProgMaze[ys][xs].lw = sl;
    ProgMaze[ys][xs].uw = su;
    ProgMaze[ys][xs+1].lw = sr;
  }
  else if (myDir == 2) // dx = -1 left
  {
    ProgMaze[ys+1][xs].uw = sl;
    ProgMaze[ys][xs].lw = su;
    ProgMaze[ys][xs].uw = sr;
  }
  else // dy = 1 down
  {
    ProgMaze[ys][xs+1].lw = sl;
    ProgMaze[ys+1][xs].uw = su;
    ProgMaze[ys][xs].lw = sr;
  }
  Serial.print("C ");
  Serial.print(su);
  Serial.print(' ');
  Serial.print(sl);
  Serial.print(' ');
  Serial.print(sr);
  Serial.print(' ');
  Serial.println(myDir);
}

void checkFirstWalls()
{
  UpdSen();
  IsLeftWall = s[0] > 50;
  IsRightWall = s[3] > 50;
  MoveForEnc(100, 200);
}

void MoveOneCell(int power, int enc) //проехать одну ячейку вперед так же проезжает плавые повороты и меняет направления
{
  int exCode;
  preset();
  setArgs(2, 4);//0.7, 3 v = 70
  if(prevCurve)
  {
    prevCurve = false;
    enc = enc - 350;
  }
  while(true) 
  {
    PDAction(power);
    if((posB+posC)*0.5 >= enc) 
    {
      exCode = 0;
      break;
    }
    if(s[0] < 30 || s[3] < 30)
    {
      exCode = 1;
      break;
    }
  }
  if(exCode == 0)
  {
    if(abs(posB - posC) > 150) // this is curve condition
    {
      if(posB > posC)
      {
         IsTurnRight = true;
         IsRightWall = 0;
         IsUpWall = 1;
         IsLeftWall = 1;
      }
      else 
      {
        IsTurnRight = false;
        IsLeftWall = 0;
        IsUpWall = 1;
        IsRightWall = 1;
      }
      if(!prevCurve) LineForEnc(power, 160);
      prevCurve = true;      
    }
    else
    {
      IsLeftWall = 1;
      IsRightWall = 1;
    }
  }
  if(exCode == 1)
  {
    MoveForEnc(70, 10, false);
    UpdSen();
    IsLeftWall = s[0] > 50;
    IsRightWall = s[3] > 50;
    MoveForEnc(150, 200);
  }
  stopMotors();
}
