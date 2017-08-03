
#include <Wire.h>
#include <Eeprom24Cxx.h>
static Eeprom24C ic_64(64,0x50);
static Eeprom24C ic_128(128,0x52);
void setup()
{//sử dụng nhiều ic dùng chung 1 bus i2c
    // chú ý đặt đúng địa chỉ cho ic
    // hãy tìm đọc bài 2 nói về cách dùng nhiều ic eeprom trên 1 bus của Thái Sơn trên arduino.vn 
    Serial.begin(9600);
    const int address = 100;
    ic_64.write_1_byte(address, 64); 
    delay(5); 
    ic_128.write_1_byte(address, 128); 
    delay(5);
    
    Serial.println("Read byte from EEPROM memory...");
    byte data = ic_64.read_1_byte(address);
    
   
    Serial.print("Read byte ic64 = ");
    Serial.print(data);
    Serial.println("");
     byte data2 = ic_128.read_1_byte(address);
    
   
    Serial.print("Read byte ic128 = ");
    Serial.print(data2);
    Serial.println("");
}

void loop()
{

}