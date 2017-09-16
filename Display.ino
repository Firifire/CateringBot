int table = 0;
void newCustomer() {

  lcd.clear();
  play();
  lcd.setCursor(7, 0);
  lcd.print("WELCOME");
  lcd.setCursor(9, 1);
  lcd.print("TO");
  lcd.setCursor(6, 2);
  lcd.print("AUTODINER");
  delay(5000);
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("NUMBER OF PEOPLE??");
  lcd.setCursor(9, 2);
  lcd.print("--");
  lcd.setCursor(4, 3);
  lcd.print("TIME LEFT:--");
  short int p = 0;
  for (int i = 8000; i >= 0; i--) {
    if (i % 1000 == 0) {
      lcd.setCursor(14, 3);
      lcd.print(i / 10000);
      lcd.print((i / 1000 ) % 10);
    }

    if (digitalRead(4)) {
      lcd.setCursor(9, 2);
      p++;
      lcd.print(p / 10);
      lcd.print(p % 10);
      while (digitalRead(4))
        delay(2);
    }
    else if (digitalRead(6)) {
      Serial.print("7: ");
      Serial.println(digitalRead(6));
      if (p > 1) {
        lcd.setCursor(9, 2);
        p--;
        lcd.print(p / 10);
        lcd.print(p % 10);
        while (digitalRead(6))
          delay(2);
      }
    }
    else if (digitalRead(5)) {
      break;
    }
    delay(1);
  }

  //add code to detect button
  if (p == 0){
    lcd.clear();
    return;
    }
     digitalWrite(11,HIGH);
  lcd.clear();
  lcd.setCursor(5, 2);
  //if person 0 < reset restaurant // or special sequence
  lcd.print("Follow Me :)");
  if (p >= 8) {
    table = 7; findCord(7);
  }
  else if (p >= 4) {
    table = 6; findCord(6);
  }
  else {
    table = 8; findCord(8);
  }
  //

  while ((abs(x - Tx) + abs(y - Ty )) > 1) {
    dirCorrector();
  }
  Stop();
  menu();
}

void menu() {
  String food[7] = {"<Pizza>", "<Fries>", "<Roti>", "<Chappati>", "<Curry>", "<Beef>", "<Chicken>"};
  String drink[7] = {"<Fanta>", "<Milo Ice>", "<Lassi>", "<Teh Tarik>", "<Cola>", "<Milk>"};
  int fItem[8];
  int dItem[9];
  int p = 0, old = 1, o = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pls Place your Order");
  lcd.setCursor(4, 3);
  lcd.print("TIME LEFT:--");
  for (int i = 8000; i >= 0; i--) {
    if (i % 1000 == 0) {
      lcd.setCursor(14, 3);
      lcd.print(i / 10000);
      lcd.print((i / 1000 ) % 10);
    }
    if (p != old) {
      lcd.setCursor(0, 2);
      lcd.print("          ");
      lcd.setCursor(0, 2);
      lcd.print(food[p]);
      old = p;
    }
    if (digitalRead(4)) {
      p++;
      if (p >= 7)
        p = 0;
      i = 8000;
      while (digitalRead(4))
        delay(2);
    }
    else if (digitalRead(6)) {
      p--;
      if (p < 0)
        p = 6;

      i = 8000;
      while (digitalRead(6))
        delay(2);

    }
    else if (digitalRead(5)) {
      fItem[o] = p;
      Serial.println(food[p]);
      o++;
      play();
      if (o >= 7)
        break;
      i = 8000;
      while (digitalRead(5))
        delay(2);
    }
    delay(1);
  }
  p = 0, old = 1;
  int od = 0;
  for (int i = 8000; i >= 0; i--) {
    if (i % 1000 == 0) {
      lcd.setCursor(14, 3);
      lcd.print(i / 10000);
      lcd.print((i / 1000 ) % 10);
    }
    if (p != old) {
      lcd.setCursor(0, 2);
      lcd.print("          ");
      lcd.setCursor(0, 2);
      lcd.print(drink[p]);
      old = p;
    }
    if (digitalRead(4)) {
      p++;
      if (p >= 7)
        p = 0;
      i = 8000;
      while (digitalRead(4))
        delay(2);
    }
    else if (digitalRead(6)) {
      p--;
      if (p < 0)
        p = 6;

      i = 8000;
      while (digitalRead(6))
        delay(2);

    }
    else if (digitalRead(5)) {
      dItem[od] = p;
      Serial.println(drink[p]);
      od++;
      play();
      if (od >= 7)
        break;
      i = 8000;
      while (digitalRead(5))
        delay(2);
    }
    delay(1);
  }
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(" Please Wait");
  findCord(5);
  while ((abs(x - Tx) + abs(y - Ty )) > 1) {
    dirCorrector();
  }
  Stop();
  
  play();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Order No.");
  for (int i = 0; i < o; i++) {
    lcd.setCursor(10, 1);
    lcd.print(i + 1);
    lcd.setCursor(0, 2);
    lcd.print("          ");
    lcd.setCursor(0, 2);
    lcd.print(food[fItem[i]]);
    delay(1000);
  }
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Drink Order No.");
  for (int i = 0; i < od; i++) {
    lcd.setCursor(16, 1);
    lcd.print(i + 1);
    lcd.setCursor(0, 2);
    lcd.print("          ");
    lcd.setCursor(0, 2);
    lcd.print(drink[dItem[i]]);
    delay(1000);
  }
  lcd.clear();
  findCord(table);
  while ((abs(x - Tx) + abs(y - Ty )) > 1) {
    dirCorrector();
  }
  Stop();
  lcd.setCursor(0, 1);
  play();
  lcd.print("Here's your order");
  delay(3000);
  Tx = 2;
  Ty = 6;
  lcd.clear();
  while ((abs(x - Tx) + abs(y - Ty )) > 0) {
    dirCorrector();
  }
  Stop();
  if (dir == 1 )
    turnLeft();
  else if (dir == 2) {
    turnLeft(); turnLeft();
  }
  else if (dir == 3)
    turnRight();
 digitalWrite(11,LOW);

}

