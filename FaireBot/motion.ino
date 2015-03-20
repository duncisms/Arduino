void forward() {
  light(7, true);
  for (int i = 0; i < loopVal; i++) {
    leftServo.write(180);
    delay(15);
    rightServo.write(0);
    delay(15);
  }
  light(7, false);
}

void reverse() {
  light(4, true);
  for (int i = 0; i < loopVal; i++) {
    leftServo.write(0);
    delay(15);
    rightServo.write(180);
    delay(15);
  }
  light(4, false);
}

void left() {
  light(5, true);
  for (int i = 0; i < loopVal; i++) {
    leftServo.write(0);
    delay(15);
    rightServo.write(0);
    delay(15);
  }
  light(5, false);
}

void right() {
  light(6, true);
  for (int i = 0; i < loopVal; i++) {
    leftServo.write(180);
    delay(15);
    rightServo.write(180);
    delay(15);
  }
  light(6, false);
}
