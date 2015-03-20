/*--------------------------------------------------------------------
  FaireBot control firmware rev. 110714

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--------------------------------------------------------------------*/


#include <Servo.h>
#include <EEPROM.h>

int addr = 0;
int upperAddr = 0;

int loopVal = 10; //change for servo turn tuning

int lowLED = 13;
int midLED = 12;
int highLED = 11;
int bckLED = 10;
int rhtLED = 9;
int fwdLED = 8;
int lftLED = 7;

int fwd = 3;
int bck = 5;
int lft = 6;
int rht = 2;
int ent = 4;

int usbLev = 512;
int battLowLev = 717;
int battMidLev = 800;
int battHighLev = 875;
boolean changeBatt = false;
boolean battToggle = false;
int battFlashDelay = 100;
unsigned long battFlashTime;

Servo leftServo; //180
Servo rightServo;

void setup() {
  pinMode(lowLED, OUTPUT);
  pinMode(midLED, OUTPUT);
  pinMode(highLED, OUTPUT);
  pinMode(fwdLED, OUTPUT);
  pinMode(bckLED, OUTPUT);
  pinMode(lftLED, OUTPUT);
  pinMode(rhtLED, OUTPUT);
  
  pinMode(fwd, INPUT);
  pinMode(bck, INPUT);
  pinMode(lft, INPUT);
  pinMode(rht, INPUT);
  pinMode(ent, INPUT);
  
  leftServo.attach(A1);
  rightServo.attach(A2);

  leftServo.write(90);
  delay(15);
  rightServo.write(90);
  delay(15);
  
  Serial.begin(9600);
  startup();
}

void loop() {
  if (changeBatt) {
    if (millis() >= battFlashTime) {
      battFlashTime += battFlashDelay;
      battToggle = !battToggle;
      light(1, battToggle);
    }
  }
  battCheck();
  buttonCheck();
  
  //default sit idle
  leftServo.write(90);
  delay(15);
  rightServo.write(90);
  delay(15);
}

void startup() {
  for (int i = 1; i < 8; i++) {
    if (i == 5) {
      light(i, true);
      i++;
      light(i, true);
    }
    else {
      light(i, true);
    }
    delay(100);
  }
  for (int i = 1; i < 8; i++) {
    if (i == 5) {
      light(i, false);
      i++;
      light(i, false);
    }
    else {
      light(i, false);
    }
    delay(100);
  }
}

void buttonCheck(){
  int maxAddr = 255;
  if (digitalRead(fwd) == 1) {
    if (addr >= maxAddr) {
      error();
    }
    else {
      EEPROM.write(addr,1);
      EEPROM.write(addr+256,1);//for backup
      addr++;
      while(digitalRead(fwd) == 1) {
        light(7, true);
      }
      light(7, false);
    }
  }
  else if(digitalRead(bck) == 1) {
    if (addr >= maxAddr) {
      error();
    }
    else {
      EEPROM.write(addr,2);
      EEPROM.write(addr+256,2);//for backup
      addr++;
      while(digitalRead(bck) == 1) {
        light(4, true);
      }
      light(4, false);
    }
  }
  else if(digitalRead(lft) == 1) {
    if (addr >= maxAddr) {
      error();
    }
    else {
      EEPROM.write(addr,3);
      EEPROM.write(addr+256,3);//for backup
      addr++;
      while(digitalRead(lft) == 1) {
        light(5, true);
      }
      light(5, false);
    }
  }
  else if(digitalRead(rht) == 1) {
    if (addr >= maxAddr) {
      error();
    }
    else {
      EEPROM.write(addr,4);
      EEPROM.write(addr+256,4);//for backup
      addr++;
      while(digitalRead(rht) == 1) {
        light(6, true);
      }
      light(6, false);
    }
  }
  else if(digitalRead(ent) == 1) {
    wait();
    run();
  }
}
 
void wait() {
  //7645
  int countDownDelay = 500;
  light(7, false);
  light(6, false);
  light(4, false);
  light(5, false);
  delay(countDownDelay);
  light(7, true);
  light(6, false);
  light(4, false);
  light(5, false);
  delay(countDownDelay);
  light(7, true);
  light(6, true);
  light(4, false);
  light(5, false);
  delay(countDownDelay);
  light(7, true);
  light(6, true);
  light(4, true);
  light(5, false);
  delay(countDownDelay);
  light(7, true);
  light(6, true);
  light(4, true);
  light(5, true);
  delay(countDownDelay);
  light(7, false);
  light(6, false);
  light(4, false);
  light(5, false);
}

void error() {
  for (int i = 0; i < 4; i++){
    light(4, true);
    light(5, true);
    light(6, true);
    light(7, true);
    delay(50);
    light(4, false);
    light(5, false);
    light(6, false);
    light(7, false);
    delay(50);
  }
}

void battCheck(){
  int battLevel = analogRead(0);
  if (battLevel < battLowLev && battLevel > usbLev) {
    changeBatt = true;
    light(2, false);
    light(3, false);
  }
  else {
    changeBatt = false;
  }
  if (battLevel <= usbLev) {
    light(1, false);
    light(2, false);
    light(3, false);
  }
  else if (battLevel >= battLowLev && battLevel < battMidLev) {
    light(1, true);
    light(2, false);
    light(3, false);
  }
  else if (battLevel >= battMidLev && battLevel < battHighLev) {
    light(1, true);
    light(2, true);
    light(3, false);
  }
  else if (battLevel >= battHighLev) {
    light(1, true);
    light(2, true);
    light(3, true);
  }
}     

void light(int led, boolean state) {
  switch (led) {
    case 1:
      if (state) {
        digitalWrite(lowLED, HIGH);
      }
      else {
        digitalWrite(lowLED, LOW);
      }
      break;
    case 2:
      if (state) {
        digitalWrite(midLED, HIGH);
      }
      else {
        digitalWrite(midLED, LOW);
      }
      break;
    case 3:
      if (state) {
        digitalWrite(highLED, HIGH);
      }
      else {
        digitalWrite(highLED, LOW);
      }
      break;
    case 4:
      if (state) {
        digitalWrite(bckLED, HIGH);
      }
      else {
        digitalWrite(bckLED, LOW);
      }
      break;
    case 5:
      if (state) {
        digitalWrite(lftLED, HIGH);
      }
      else {
        digitalWrite(lftLED, LOW);
      }
      break;
    case 6:
      if (state) {
        digitalWrite(rhtLED, HIGH);
      }
      else {
        digitalWrite(rhtLED, LOW);
      }
      break;
    case 7:
      if (state) {
        digitalWrite(fwdLED, HIGH);
      }
      else {
        digitalWrite(fwdLED, LOW);
      }
      break;
  }
}
