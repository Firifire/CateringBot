//int moveforward = FTime / 1.9; objective related
//need to combine functions 

void turnLeft() {
  Serial.println("turnLeft");
#if MOTOR == 0
motor->goLeftStrong();
#elif MOTOR == 1
  frontRight.writeMicroseconds(1300);
  frontLeft.writeMicroseconds(1300);
#endif
  delay(Time);
  if (dir == 0)
    dir = 3;
  else
    dir--;
  angularCorrection();
}

void turnLeft(int offset) {
  Serial.print("lAngle: ");
  Serial.print(lAngle);
  Serial.print(" lAngle: ");
  Serial.print(uAngle);
  Serial.print(" Cur: ");
  Serial.print(cur);
  Serial.print(" Offset: : ");
  Serial.print(offset);
  Serial.println(" turnLeft offsset");
#if MOTOR == 0
motor->goLeftStrong();
#elif MOTOR == 1
  frontRight.writeMicroseconds(1300);
  frontLeft.writeMicroseconds(1300);
#endif
  delay(offset);
  angularCorrection();
}

void turnRight() {
  Serial.println("turnRight");
#if MOTOR == 0
motor->goRightStrong();
#elif MOTOR == 1
  frontRight.writeMicroseconds(1700);
  frontLeft.writeMicroseconds(1700);
#endif
  delay(Time);
  if (dir == 3)
    dir = 0;
  else
    dir++;
  angularCorrection();
}

void turnRight(int offset) {
  Serial.print("lAngle: ");
  Serial.print(lAngle);
  Serial.print(" lAngle: ");
  Serial.print(uAngle);
  Serial.print(" Cur: ");
  Serial.print(cur);
  Serial.print(" Offset: : ");
  Serial.print(offset);
  Serial.println(" turnRight offset");
#if MOTOR == 0
motor->goRightStrong();
#elif MOTOR == 1
  frontRight.writeMicroseconds(1700);
  frontLeft.writeMicroseconds(1700);
#endif
  delay(offset);
  angularCorrection();
}

void forward() {
  Serial.println("forward");
#if MOTOR == 0
motor->goFront();
#elif MOTOR == 1
  frontRight.writeMicroseconds(1300);
  frontLeft.writeMicroseconds(1700);
#endif
PosUpdate(x, y);
  delay(FTime);
  angularCorrection();
}

void backward() {
  Serial.println("backward");
#if MOTOR == 0
#elif MOTOR == 1
  frontRight.writeMicroseconds(1700);
  frontLeft.writeMicroseconds(1300);
#endif
  delay(FTime);
  angularCorrection();
}

void Stop() {
  Serial.println("Stop");
#if MOTOR == 0
motor->goStop();
#elif MOTOR == 1
  frontRight.writeMicroseconds(1500);
  frontLeft.writeMicroseconds(1500);

#endif
}

