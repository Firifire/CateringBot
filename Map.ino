float lAngle, uAngle;

float AError = 1.5;
//add dynamic speed
//consider inertia when turning

void angularCorrection() {  //rename angular correction?
  Stop();
  delay(20);
  gyroUpdate();
  if (dir == 0) {
    lAngle = N - AError;
    uAngle = N + AError;
  }
  else if (dir == 1) {
    lAngle = N - AError + 90;
    uAngle = N + AError + 90;
  }
  else if (dir == 2) {
    lAngle = N - AError + 180;
    uAngle = N + AError + 180;
  }
  else {
    lAngle = N - AError - 90;
    uAngle = N + AError - 90;
  }

  if (lAngle <= -180)
    lAngle += 360;
  else if (lAngle >= 180)
    lAngle += -360;
  if (uAngle >= 180)
    uAngle += -360;
  else if (uAngle <= -180)
    uAngle += 360;

  if (lAngle - uAngle == -AError * 2) {
    if (cur >= lAngle && cur <= uAngle)
      return;
    else {
      if ((lAngle > 0 && cur < 0) || (lAngle < 0 && cur > 0) && fabs(cur - lAngle) > 100) { //new
        if (cur > 0)
          turnRight(floor((Time / 90) * ( lAngle + AError + 360 - cur)));
        else
          turnLeft(floor((Time / 90) * (cur - (lAngle + AError - 360))));
      }
      else if (cur < lAngle)
        turnRight(floor((Time / 90) * ( lAngle + AError - cur)));
      else
        turnLeft(floor((Time / 90) * (cur - (lAngle + AError))));
    }
  }
  else {
    if (cur > 0) {
      if (cur >= lAngle)
        return;
      else
        turnRight(floor((Time / 90) * ( lAngle + AError - cur )));
    }
    else {
      if (cur <= uAngle)
        return;
      else
        turnLeft(floor((Time / 90) * (cur - (uAngle - AError))));
    }
  }
}

#if MODE == 2

void PosUpdate(int &p, int &q, int Dir = dir)
{
  switch (Dir)
  {
    case 0:
    case 4: p--;
      break;
    case 1: q++;
      break;
    case 2: p++;
      break;
    case -1:
    case 3: q--;
      break;
  }
}

bool deadend(int Dir = dir) //add move forward in Mapupdate instead?
{
  if ((Dir == 0 || Dir == 4) && Map[x - 1][y] == 1)
    return false;
  else if ((Dir == 1 || Dir == 5) && Map[x][y + 1] == 1)
    return false;
  else if ((Dir == 2 || Dir == -2) && Map[x + 1][y] == 1)
    return false;
  else if ((Dir == 3 || Dir == -1) && Map[x][y - 1] == 1)
    return false;
  else
    return true;
}
void decide(int l = x, int m = y, int K = 0) //update code for when path splits again
{
  int p, q, temp;
  for (int k = -1 + K; k <= 1 + K; k++) {
    p = l;
    q = m;
    PosUpdate(p, q, dir + k);
    if (Map[p][q] == 1) {
      while (true) {
        temp = 0;
        for (int i = -1; i <= 1; i += 2)
        {
          if (p == Tx && q == Ty) //changed q+1 to q+i
          {
            if (k == -1 + K)
              turnLeft();
            else if (k == 1 + K)
              turnRight();
            return;
          }
          else if (Map[i + p][q] == 1 && abs(p + q - l - m) < abs(p + i + q - l - m))
          {
            p += i;
            //temp++;
            break;
          }
          else if (Map[p][i + q] == 1 && abs(p + q - l - m) < abs(p + i + q - l - m))
          {
            q += i;
            //temp++;
            break;
          }
        }
        // if(temp>3); //need to add code incase more than 2 paths
      }
    }
  }
}

bool dirCorrector() {
  int vx = 0, vy = 0;
  PosUpdate(vx, vy);
  if ((abs(x + vx - Tx) + abs(y +vy - Ty )) < (abs(x - Tx) + abs(y - Ty )) && !deadend()) {
    forward();
    return true;
  }
  else if ((abs(x -vx - Tx) + abs(y -vy- Ty )) < (abs(x - Tx) + abs(y - Ty )) && !deadend(dir + 2)) {
    turnRight();
    turnRight();
    forward();
    return true;
  }
  vx = 0;
  vy = 0;
  PosUpdate(vx, vy, dir + 1);
  if ((abs(x + vx - Tx) + abs(y +vy - Ty )) <(abs(x - Tx) + abs(y - Ty )) && !deadend(dir + 1)) {
    turnRight();
    forward();
    return true;
  }
  else if ((abs(x -vx - Tx) + abs(y -vy- Ty )) < (abs(x - Tx) + abs(y - Ty )) && !deadend(dir - 1)) {
    turnLeft();
    forward();
    return true;
  }
  else {
    Serial.println("vxv   ");
    Serial.print(vx);
    Serial.print("   ");
    Serial.print(vy);
    Serial.print("   ");
    Serial.print(dir + 1);
    delay(500);
    //decide();
    return false;
  }
}


void findCord(int T)  //make it circular search
{
  for (int i = 0; i < Size; i++)
    for (int j = 0; j < Size; j++)
      if (Map[i][j] == T) {
        Tx = i;
        Ty = j;
        Serial.print("Tx:");
        Serial.print(Tx);
        Serial.print("    Ty:");
        Serial.println(Ty);
        return;
      }
}



#endif
