// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor motorM1(1);  //Задний мост
AF_DCMotor motorM3(1);  //Руль
SoftwareSerial BTSerial(A0, A1); // RX, TX

int maxSpeed = 127;   //Ограничение максимальной скорости
char btcmd;           // Переменнвя для комманд BT
int vpsdM1;           //Память скорости M1

void setup() {
  Serial.begin(9600);              // set up Serial library at 9600 bps
  BTSerial.begin(9600);

  motorM1.setSpeed(100);   //speed- Valid values for 'speed' are between 0 and 255 with 0 being off and 255 as full throttle.
  motorM1.run(RELEASE);

  motorM3.setSpeed(100);
  motorM3.run(RELEASE);
}

void loop() {
  uint8_t i;
  if (BTSerial.available())
  {
    btcmd = (char)BTSerial.read();
    Serial.println(btcmd);

    // Вперед
    if (btcmd == 'F') {
      motorM1.run(FORWARD);
      for (i = 0; i < vpsdM1; i++) {
        motorM1.setSpeed(i);
        delay(10);
      }
    }
    
    // Назад
    if (btcmd == 'B') {
      for (i = 0; i < vpsdM1; i++) {
        motorM1.setSpeed(i);
        delay(10);
      }
    }
  }



}
// Прямо влево
void fLeft() {
  Speed(vpsdM1,maxSpeed);
  motorM1.run(FORWARD);
  motorM3.run(FORWARD);
}

// Прямо вправо
void fRight() {
  Speed(vpsdM1,maxSpeed);
  motorM1.run(FORWARD);
  motorM3.run(BACKWARD);
}

// Назад влево
void bLeft() {
  Speed(vpsdM1,maxSpeed);
  motorM1.run(BACKWARD);
  motorM3.run(FORWARD);
}

// Назад направо
void bRight() {
  Speed(vpsdM1,maxSpeed);
  motorM1.run(BACKWARD);
  motorM3.run(BACKWARD);
}
// Изменение скорости
void Speed(int spd, int max) {
  if (spd > max) {
    spd = max;
  }
  motorM1.setSpeed(spd);
}

//Остановка моторов
void MotorsStop() {
    motorM1.run(RELEASE);
    motorM3.run(RELEASE);
}

