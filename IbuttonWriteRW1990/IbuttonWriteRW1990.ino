// Based on https://danman.eu/blog/cloning-ibutton-using-rw1990-and-avr/
// and: http://elimelecsarduinoprojects.blogspot.com/2013/06/read-dallas-ibutton-arduino.html
// By Swift Geek 28-08-2015
// TODO: danger to atmega328! Use OpenCollector logic!
// Used 4.8kΩ Pull-up and 3.1 Vcc for arduino/pull-up

#include <OneWire.h>
#define pin 10

OneWire ibutton (pin); // I button connected on PIN 2.

byte addr[8]; //array to store the Ibutton ID.
// Hardcode here your desired ID //
    // 01 01 01 00 00 00 
//ded KEY 1:59:87:F8:C:0:0:C9
//my 1:F1:77:56:1:0:0:3E
//my 1:E3:A6:6F:1:0:0:43
//byte newID[8] = {0x01, 0xF1,0x77, 0x56, 0x01, 0x00, 0x00, 0x3E};
//byte newID[8] = {0x01, 0x59,0x87, 0xF8, 0x0C, 0x00, 0x00, 0xC9}; //Ded
//byte newID[8] = {0x01, 0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00};
byte newID[8] = {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x9B};

void setup(){
 Serial.begin(115200); 
}

void loop(){
  if (!ibutton.search (addr)){//read attached ibutton and asign value to buffer
    ibutton.reset_search();
    delay(200);
    return;
 }
 
  Serial.print(millis()/1000);
  Serial.print("> ");
  for (byte x = 0; x<8; x++){  
    Serial.print(addr[x],HEX); //print the buffer content in LSB. For MSB: for (int x = 8; x>0; x--) 
     Serial.print(" ");
  }
 
  //compute crc//
  byte crc;
  crc = ibutton.crc8(addr, 8);
  Serial.print("CRC: ");
  Serial.println(crc,HEX);
  if ( Serial.read() == 'w' ){
    ibutton.skip();ibutton.reset();ibutton.write(0x33);
    Serial.print("  ID before write:");
    for (byte x=0; x<8; x++){
      Serial.print(' ');
      Serial.print(ibutton.read(), HEX);
    }
    // send reset
    ibutton.skip();
    ibutton.reset();
    // send 0xD1
    ibutton.write(0xD1);
    // send logical 0
    digitalWrite(10, LOW); pinMode(10, OUTPUT); delayMicroseconds(60);
    pinMode(10, INPUT); digitalWrite(10, HIGH); delay(10);
    
    Serial.print('\n');
    Serial.print("  Writing iButton ID:\n    ");
    // Hardcode here your desired ID //
    // 01 01 01 00 00 00 
    //byte newID[8] = {0x9B, 0x00,0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01};
                     
    ibutton.skip();
    ibutton.reset();
    ibutton.write(0xD5);
   // ibutton.write(0x3C);
    for (byte x = 0; x<8; x++){
      writeByte(newID[x]);
      Serial.print('*');
    }
    Serial.print('\n');
    ibutton.reset();
    // send 0xD1
    ibutton.write(0xD1);
    //send logical 1
    digitalWrite(10, LOW); pinMode(10, OUTPUT); delayMicroseconds(10);
    pinMode(10, INPUT); digitalWrite(10, HIGH); delay(10);

  }
} 

int writeByte(byte data){
  int data_bit;
  for(data_bit=0; data_bit<8; data_bit++){
    if (data & 1){
      digitalWrite(pin, LOW); pinMode(pin, OUTPUT);
      delayMicroseconds(60);
      pinMode(pin, INPUT); digitalWrite(pin, HIGH);
      delay(10);
    } else {
      digitalWrite(pin, LOW); pinMode(pin, OUTPUT);
      pinMode(pin, INPUT); digitalWrite(pin, HIGH);
      delay(10);
    }
    data = data >> 1;
  }
  return 0;
}

