
/****************************************************************************
 * 

 brief EEPROM 24C01 -> 24C256 library for Arduino
Thư viện được viết lại bởi Phùng Thái Sơn -96 Hà Nam
8:58pm 21/11/2016.
Uploaded to ardunio.vn
Thư viện phát triển lại giờ đây đã có thể dùng chung cho mọi loại eeprom từ 
24c01 đến 24c256. Có thêm tính năng chống ghi đè (nguyên nhân gây giảm tuổi thọ) và 
chống ghi quá địa chỉ cho phép ( nguyên nhân gây sai số ) 
 Thư viện này được viết lại từ nguồn có địa chỉ trang web www.idreammicro.com 

 * uthor Copyright (C) 2012  Julien Le Sech - www.idreammicro.com
 * version 1.0
 * date 20120218
 *
 *
 * This library is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see http://www.gnu.org/licenses
 ******************************************************************************/
#include <Wire.h>


#include <Arduino.h>

#include <EEPROM.h>

#define eeprom_on_arduino 0
// chọn eeprom của arduino
#define eeprom_on_ic 1
// chọn eeprom của ic ngoại vi
class Eeprom24C 
{
    public:
        Eeprom24C( unsigned int size_m, byte deviceAddress);

        
        Eeprom24C();

        void write_1_byte( unsigned int address, byte data);
        byte read_1_byte(  unsigned int address);
        uint16_t read_2_byte(  unsigned int address);
        void write_2_byte( unsigned int address, uint16_t data);
         void  write_4_byte( unsigned int address, uint32_t data);
         uint32_t read_4_byte(  unsigned int address);
         void write_8_byte( unsigned int address, uint64_t data);
         uint64_t read_8_byte(  unsigned int address);

    private:
void write_byte_eeprom_ic(unsigned int address,byte  data);
byte read_byte_eeprom_ic( unsigned int address);
void write_byte_eeprom_arduino(unsigned int address,byte  data);
byte read_byte_eeprom_arduino( unsigned int address);
    	byte select_eeprom;
    	// select eeprom=0 // arduino
    	//select eeprom=1 // ic eeprom 
unsigned int size_memory;
unsigned long size_bytes;
byte m_deviceAddress;

};

static Eeprom24C AVR_EEPROM;
