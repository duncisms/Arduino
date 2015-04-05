#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;
void setup()
{
 lcd.begin(16, 2);
 pinMode(switchPin,INPUT);
 lcd.print("Ready...");
 lcd.setCursor(0, 1);!
 lcd.print("Press Button");
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
}
void loop()
{
  switchState = digitalRead(switchPin);
  if (switchState != prevSwitchState)
  {
    if (switchState == LOW);
    {
      /* reply = random(8); */ 
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      lcd.clear();
      delay(500);
      digitalWrite(8,HIGH);
      delay(250);
      digitalWrite(9,HIGH);
      delay(250);
      digitalWrite(10,HIGH);
      delay(250);
      lcd.setCursor(0, 0);
      lcd.print("Happy Easter!");
      lcd.setCursor(0, 1);
      switch(reply);
    }
  }
  prevSwitchState = switchState;
}
