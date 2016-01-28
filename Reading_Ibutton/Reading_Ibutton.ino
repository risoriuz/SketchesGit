#include <OneWire.h>
#define pin 10

OneWire ibutton (pin); // I button connected on PIN 2.

byte addr[8]; //array to store the Ibutton ID.

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (!ibutton.search (addr)) { //Чтение подключенного ibutton
    ibutton.reset_search();
    delay(500);
    return;
  }

  Serial.print(millis() / 1000);
  Serial.print("> ");
  for (byte x = 0; x < 8; x++) {
    Serial.print(addr[x], HEX); //print the buffer content in LSB. For MSB: for (int x = 8; x>0; x--)
    if (x != 7) Serial.print(":");
  }
  Serial.print("\n");

  Serial.print("  Put commnad \'33h\':");
  ibutton.skip(); ibutton.reset(); ibutton.write(0x33);
  Serial.print("       Answer:");
  for (byte x = 0; x < 8; x++) {
    Serial.print(' ');
    Serial.print(ibutton.read(), BIN);
    //Serial.print('\' ');
  }
  Serial.print("\n");

  //RW1990(1115) 1:C2:EA:B7:1:0:0:17
  // Отвечает НА:
  // 0xF0    Ответ: F5:FF:FF:FF:FF:FF:FF:FF
  // 0x0F    Ответ: 1:C2:EA:B7:1:0:0:17
  //
  // RW 2004
  // c 0xF0   Ответ: 6D:DB:B6:6D:DB:B6:6D:DB
  // по 0хFB  Ответ: 6D:DB:B6:6D:DB:B6:6D:DB
  // 0х35            F8:FF:FF:FF:FF:FF:FF:FF
  //------------------------------------

  //  for (byte i = 0; i < 255; i++) {
  //    Serial.print("  Put commanad ");
  //    Serial.print(i, HEX);
  //
  //    ibutton.skip(); ibutton.reset(); ibutton.write(i);
  //    Serial.print("       Answer:");
  //    for (byte x = 0; x < 8; x++) {
  //      Serial.print(':');
  //      Serial.print(ibutton.read(), HEX);
  //    }
  ibutton.skip(); ibutton.reset(); ibutton.write(0xF0);
  Serial.print("  Put commanad 0xF0");
  Serial.print("      Answer:");
  for (byte x = 0; x < 8; x++) {
    Serial.print(':');
    Serial.print(ibutton.read(), HEX);
  }

  Serial.print("\n");
  delay(500);
}



