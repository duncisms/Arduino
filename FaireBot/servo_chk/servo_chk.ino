#include <Servo.h>

//setup servo names
Servo leftServo;
Servo rightServo;

//setup servo position value (90=stop)
int rp = 90;
int lp = 90;

void setup ()
{
  //attach the servo names to physical pins
  leftServo.attach(A1);
  rightServo.attach(A2);
}

void loop()
{
  leftServo.write(lp);
  rightServo.write(rp);
  
  //manditory delay
  delay(15);
}
