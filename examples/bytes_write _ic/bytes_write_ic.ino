//https://github.com/NickChungVietNam/ALL_EEPROM_24Cxx_ATMEL_ARDUINO_AT_MASTER
#include <Wire.h>
#include <Eeprom24Cxx.h>
#define type_ic 4
static Eeprom24C eeprom(type_ic,0x50);// mình chọn 24c04
void setup()
{     // viết và ghi dữ liệu lên eeprom của ic
	Serial.begin(9600);
byte a=255;
unsigned int b=62770;
unsigned long c=4000000000; //4 tỷ
        eeprom.write_1_byte(0, a);
        eeprom.write_2_byte(10, b);
        eeprom.write_4_byte(40, c);

Serial.println(eeprom.read_1_byte(0));
Serial.println(eeprom.read_2_byte(10));
Serial.println(eeprom.read_4_byte(40));
}
void loop()
{
  }
/*
•	        void write_1_byte( unsigned int address, byte data);
•	        byte read_1_byte(  unsigned int address);
•	        uint16_t read_2_byte(  unsigned int address);
•	        void write_2_byte( unsigned int address, uint16_t data);
•	         void  write_4_byte( unsigned int address, uint32_t data);
•	         uint32_t read_4_byte(  unsigned int address);
•	         void write_8_byte( unsigned int address, uint64_t data);
•	         uint64_t read_8_byte(  unsigned int address);
*/