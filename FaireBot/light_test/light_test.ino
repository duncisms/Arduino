int low = 13;
int mid = 12;
int full = 11;
int fwd = 8;
int bck = 10;
int lft = 7;
int rht = 9;

//flash delay time delay(ms)
int flashDelay = 100;

void setup()
{
  //Configures pins as outputs 
  pinMode(low, OUTPUT);
  pinMode(mid, OUTPUT);
  pinMode(full, OUTPUT);
  pinMode(fwd, OUTPUT);
  pinMode(bck, OUTPUT);
  pinMode(lft, OUTPUT);
  pinMode(rht, OUTPUT);
}

void loop()
{
  //flash away!
  digitalWrite(low,HIGH);
  delay(flashDelay);
  digitalWrite(low,low);
  delay(flashDelay);
  
  digitalWrite(mid,HIGH);
  delay(flashDelay);
  digitalWrite(mid,LOW);
  delay(flashDelay);
  
  digitalWrite(full,HIGH);
  delay(flashDelay);
  digitalWrite(full, LOW);
  delay(flashDelay);
  
  digitalWrite(bck, HIGH);
  delay(flashDelay);
  digitalWrite(bck, LOW);
  delay(flashDelay);
  
  digitalWrite(lft, HIGH);
  delay(flashDelay);
  digitalWrite(lft, LOW);
  delay(flashDelay);
  
  digitalWrite(rht, HIGH);
  delay(flashDelay);
  digitalWrite(rht, LOW);
  delay(flashDelay);
  
  digitalWrite(fwd, HIGH);
  delay(flashDelay);
  digitalWrite(fwd, LOW);
  delay(flashDelay);
}
