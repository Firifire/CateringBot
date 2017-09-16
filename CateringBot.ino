/**********************************************************************/
/*                            CONFIG                                  */
/**********************************************************************/

#define MOTOR 1  //0 = DC Motors, 1 = Servo Motors
#define MODE 2  //0 = Auto solve maze,1 = defined map mode,2 = Fixed defined map mode with objective,3 = Manual path mode, 4 = Manual path mode with objective
//add path mode with ultrasonic
//map mode deined not done
//find solution to in accurate ultrasonic. ?add mean, mode reading in functions?
/***********************************************************************/
/*                        END OF CONFIG                                */
/***********************************************************************/

//#include "Ultrasonic.h"
#if MOTOR == 1
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

int melody[] = {
   NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
 4, 4, 4, 4
};
LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo frontRight, frontLeft;
#endif

/* Define key objects */
//Define pins ultrasonic(trig,echo)
//Ultrasonic ultrasonic[3] = { Ultrasonic( A0, A1 ), Ultrasonic( A2, A3 ), Ultrasonic( 7, 6 )}; //left, front and right //may prefer left and right sensors at the back


/*Define variable*/
const unsigned short int Time = 770, FTime = 1350; //Time for turning 90 degree, Ftime for forward (half a block in a maze) //may need to be reworked for inaccurate mazes
//const int armUp = 100; old objective related

const byte Size = 7, Gap = 17; //Gap is in CM

#if MODE == 2
const short int Map[Size][Size] = {
  {1, 1, 1, 1, 1, 1, 1 }, //do the map manually
  {1, 7, 1, 1, 1, 1, 1 }, //0=Wall, 1=Open , 2 = Changeable, 3= Null , 4=unconfirmed wall? , >4 objectives
  {1, 7, 1, 1, 8, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1 }, //5 = C 6=L  7=  S  8=B
  {6, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 5, 5 }
};
#endif
int x = 2, y = 6, Tx, Ty; //x and y are initial point
short int dir = 0; // N=0, E=1, S=2, W=3


void setup() {
  Serial.begin(115200);
  //buttons
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
#if MOTOR == 1
  frontRight.attach(13);
  frontLeft.attach(12);
#endif
 pinMode (11,OUTPUT); //PIR Sensor
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Calibrating Sensors");
  accelSetup();  //initialize gyro
    for (long int i = 0; i < 2000; i++) {
      gyro();
      delay(1);
    }
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print(" Calibration Done");
 
  
  


}

void loop() {
  //add operation compelte function
  //gyro calibration too long
  //enter desired method
  // add menu code then folowed by findCord(Target) and then rest of the stuff
  if (digitalRead(7)) {
    newCustomer();
  }
  delay(15);
}

void play(){
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(9, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}

