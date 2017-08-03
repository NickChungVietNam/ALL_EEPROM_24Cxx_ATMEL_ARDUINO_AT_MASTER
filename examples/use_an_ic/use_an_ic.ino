//https://github.com/NickChungVietNam/ALL_EEPROM_24Cxx_ATMEL_ARDUINO_AT_MASTER

#include <Wire.h>
#include <Eeprom24Cxx.h>
static Eeprom24C eeprom(4,0x50);// mình chọn 24c04

void setup()
{
    Serial.begin(9600);
    const int address = 500;
    eeprom.write_1_byte(address, 123); 
    delay(5);
    
    Serial.println("Read byte from EEPROM memory...");
    byte data = eeprom.read_1_byte(address);
    
   
    Serial.print("Read byte = ");
    Serial.print(data);
    Serial.println("");
}

void loop()
{

}