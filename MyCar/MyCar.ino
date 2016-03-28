// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
const int TopSpeed = 127;

AF_DCMotor motorM1(1);  //Задний мост
AF_DCMotor motorM3(1);  //Руль

void setup() {
  Serial.begin(9600);              // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motorM1.setSpeed(100);   //speed- Valid values for 'speed' are between 0 and 255 with 0 being off and 255 as full throttle.
  motorM1.run(RELEASE);
  
  motorM3.setSpeed(100);
  motorM3.run(RELEASE);
  
}

void loop() {
  uint8_t i;
  
  Serial.print("Задний мост вперед: ");
  
  motorM1.run(FORWARD);
  for (i=0; i<TopSpeed; i++) {
    motorM1.setSpeed(i);  
    delay(10);
 }
  Serial.print(" Полная скорость =");
  Serial.println(TopSpeed);
  for (i=TopSpeed; i!=0; i--) {
    motorM1.setSpeed(i);  
    delay(100);
 }
  
  Serial.println("Задний мост вперед: СТОП");
  delay (1000);
  Serial.println("Ждем 1000 ms");

  Serial.print("Задний мост назад: ");
  motorM1.run(BACKWARD);
  for (i=0; i<TopSpeed; i++) {
    motorM1.setSpeed(i);  
    delay(100);
 }
 
  for (i=TopSpeed; i!=0; i--) {
    motorM1.setSpeed(i);  
    delay(100);
 }
  Serial.println("Задний мост назад: СТОП");

  Serial.println("Вылючение");
  motorM1.run(RELEASE);
  delay(1000);
}
