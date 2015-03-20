void run() {
  //check for repeat run
  if (EEPROM.read(0) == 0) { //indicates repeat run
    for (int i = 256; i < 512; i++) {
      byte inByte = EEPROM.read(i);
      if (inByte == 0) { //leaves routine if there are no more commands
        break;
      }
      if (inByte == 1) {
        forward();
      }
      else if (inByte == 2) {
        reverse();
      }
      else if (inByte == 3) {
        left();
      }
      else if (inByte == 4) {
        right();
      }
    }
  }
  else {
    upperAddr = addr;
    for (int i = 0; i < addr; i++) {
      byte inByte = EEPROM.read(i);
      if (inByte == 1) {
        forward();
      }
      else if (inByte == 2) {
        reverse();
      }
      else if (inByte == 3) {
        left();
      }
      else if (inByte == 4) {
        right();
      }
    }
  }
  delay(10);
  erase();
}

void erase() {
  //default sit idle
  leftServo.write(90);
  delay(15);
  rightServo.write(90);
  delay(15);

  int countDownDelay = 0;
  
  light(7, true);
  light(6, true);
  light(4, true);
  light(5, true);
  delay(countDownDelay);
  
  for (int i = 511; i >= upperAddr + 256; i--) {   //erase banks above current code
    EEPROM.write(i, 0);
  }
  
  for (int i = 0; i < 64; i++) {
    EEPROM.write(i, 0);
    light(5, false);
    light(4, true);
    light(6, true);
    light(7, true);
  }
  delay(countDownDelay);
  for (int i = 64; i < 128; i++) {
    EEPROM.write(i, 0);
    light(5, false);
    light(4, false);
    light(6, true);
    light(7, true);
  }
  delay(countDownDelay);
  for (int i = 128; i < 192; i++) {
    EEPROM.write(i, 0);
    light(5, false);
    light(4, false);
    light(6, true);
    light(7, true);    
  }
  delay(countDownDelay);  
  for (int i = 192; i < 256; i++) {
    EEPROM.write(i, 0);
    light(5, false);
    light(4, false);
    light(6, false);
    light(7, true);    
  }
  delay(countDownDelay);  
  light(5, false);
  light(4, false);
  light(6, false);
  light(7, false);
  
  addr = 0;
}
