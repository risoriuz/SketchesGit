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

  for (byte i = 0; i < 255; i++) {
    Serial.print("  Put commanad ");
    Serial.print(i, HEX);

    ibutton.skip(); ibutton.reset(); ibutton.write(i);
    Serial.print("       Answer:");
    for (byte x = 0; x < 8; x++) {
      Serial.print(':');
      Serial.print(ibutton.read(), HEX);
    }
    Serial.print("\n");
    delay(500);
  }
}



