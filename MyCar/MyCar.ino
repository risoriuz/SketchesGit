// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor motorM1(1);  //Задний мост
AF_DCMotor motorM3(1);  //Руль
SoftwareSerial BTSerial(A0, A1); // RX, TX

char btCmd = 'S';           // Переменнвя для комманд BT
char prevbtCmd = 'A';
int vpsdM1 = 0;           //Память скорости M1

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
    char prevbtCmd = btCmd;
    btCmd = BTSerial.read();
    Serial.println(btCmd);

    if (btCmd != prevbtCmd)
    {
      switch (btCmd)
      {
        case 'F':                    //Вперед
          motorM1.setSpeed(vpsdM1);
          motorM1.run(FORWARD);
          break;
        case 'B':                    //Вперед
          motorM1.setSpeed(vpsdM1);
          motorM1.run(BACKWARD);
          break;
        case 'L':
          motorM3.run(BACKWARD);
          break;
        case 'R':
          motorM3.run(FORWARD);
          break;
        case 'G':
          fLeft(vpsdM1);
          break;
        case 'К':
          fRight(vpsdM1);
          break;
        case 'I':
          fRight(vpsdM1);
          break;
        case 'H':
          bLeft(vpsdM1);
          break;
        case 'J':
          bRight(vpsdM1);
          break;
        default:  //Get velocity
          if (btCmd == 'q') {
            vpsdM1 = 255;  //Full velocity
            motorM1.setSpeed(vpsdM1);
          } else {
            if (( btCmd >= 48) && (btCmd <= 57))
            {
              //Subtracting 48 changes the range from 48-57 to 0-9.
              //Multiplying by 25 changes the range from 0-9 to 0-225.
              vpsdM1 = (btCmd - 48) * 25;
              motorM1.setSpeed(vpsdM1);
            }
          }
      }
    }
  }
}


// Прямо влево
void fLeft(int vpsdM1) {
  motorM1.setSpeed(vpsdM1);
  motorM1.run(FORWARD);
  motorM3.run(FORWARD);
}

// Прямо вправо
void fRight(int vpsdM1) {
  motorM1.setSpeed(vpsdM1);
  motorM1.run(FORWARD);
  motorM3.run(BACKWARD);
}

// Назад влево
void bLeft(int vpsdM1) {
  motorM1.setSpeed(vpsdM1);
  motorM1.run(BACKWARD);
  motorM3.run(FORWARD);
}

// Назад направо
void bRight(int vpsdM1) {
  motorM1.setSpeed(vpsdM1);
  motorM1.run(BACKWARD);
  motorM3.run(BACKWARD);
}

//Остановка моторов
void MotorsStop() {
  motorM1.run(RELEASE);
  motorM3.run(RELEASE);
}

