//defines variables as pin numbers
int fwd = 3;
int bck =5;
int lft = 6;
int rht = 2;
int exe = 4;

void setup () 
{
  //opens and configures the serial port to 9600 baud
  Serial.begin(9600);
  
  //configure the button pins as inputs
  pinMode(fwd, INPUT);
  pinMode(bck, INPUT);
  pinMode(lft, INPUT);
  pinMode(rht, INPUT);
  pinMode(exe, INPUT);
}

void loop()
{
  //checks the state of each input pin & if pressed, shouts out the button name
  if (digitalRead(fwd) == 1)
  {
    Serial.println("FORWARD!");
  }
  else if (digitalRead(bck) == 1)
  {
    Serial.println("BACK!");
  }
  else if (digitalRead(lft) == 1)
  {
    Serial.println("LEFT!");
  }
  else if (digitalRead(rht) == 1)
  {
    Serial.println("RIGHT!");
  } 
  else if (digitalRead(exe) == 1)
  {
    Serial.println("EXECUTE!");
  }
  delay(100);
}
