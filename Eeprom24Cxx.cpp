


#include <Arduino.h>

#include <Eeprom24Cxx.h>
#include <Wire.h>
#include <EEPROM.h>
/*
Thư viện eeprom iv 24cxx , viết bởi Phùng Thái Sơn, VIET NAM.
https://github.com/NickChungVietNam/ALL_EEPROM_24Cxx_ATMEL_ARDUINO_AT_MASTER
*/


Eeprom24C::Eeprom24C(  unsigned int size_m, byte deviceAddress){
    m_deviceAddress = deviceAddress;
    size_memory=size_m;
    size_bytes=size_m*128; //  size_bytes=(size_m*1024)/8; 
    // tìm số byte mà ic có thể lưu trữ
    // ví dụ ic 24c04 có (4*1024)/8=512 bytes
    //byte đầu tiên là 0. byte cuối là 511
     select_eeprom=eeprom_on_ic;// chọn phương thức lưu trên ic
     Wire.begin();
}
Eeprom24C::Eeprom24C(){
   
     select_eeprom=eeprom_on_arduino;// chọn phương thức lưu trên arduino
}

void Eeprom24C::write_byte_eeprom_ic(unsigned int   address,byte  data){


if((address>=size_bytes)|(read_1_byte(address)==data)){
    // nếu quá địa chỉ thì không ghi -> thoát
    // nếu dữ liệu đưa vào bằng dữ liệu cũ thì không cần ghi ->thoát
    //( tiết kiệm số lần ghi)
    return;// thoát ngay
}

    // ví dụ ic 24c04 có (4*1024)/8=512 bytes
    //byte đầu tiên là 0. byte cuối là 511
    if( size_memory<=2){
        //24c01 và 24c02
        Wire.beginTransmission(m_deviceAddress);
    Wire.write((byte)address);//địa chỉ 8 bit 
    
    }else if(size_memory<=16){ 
     //24c04, 24c08 và 24c16
        // vì kích thước của adress lớn hơn 8bit : ví dụ số 300.
        //khi đó ic được cấu tạo từ các đơn vị ic nhỏ hơn
        //ví dụ 24c04 thực chất được cấu tạo từ 2 ic 24c02 dùng chung 1 đường bus i2c
        //mỗi ic được gọi là 1 page
        //khi đó pin A0 sẽ được dùng giống như pin chọn chip (chọn page)
        // lúc này địa chỉ của ic là : 1.0.1.0.A2.A1.0 (page 1) và 1.0.1.0.A2.A1.1 (page 2)
        // page 1 có thể lưu được ô nhớ từ 0->255, page 2 lưu ô nhớ từ 256->511
      
        // XEM LẠI BÀI VIẾT CỦA MÌNH TRÊN TRANG ARDUINO.VN-THÁI SƠN
    Wire.beginTransmission((byte)(m_deviceAddress | ((address >> 8) & 0x07)));
    Wire.write(address & 0xFF);
    } else if(size_memory<=256){
        //24c32, 24c64, 24c128, 24c256

    Wire.beginTransmission(m_deviceAddress);
    Wire.write(address >> 8);
    Wire.write(address & 0xFF);
    }

    Wire.write(data);
    Wire.endTransmission();
    delay(10);
}

byte Eeprom24C::read_byte_eeprom_ic( unsigned int address){

if(address>=size_bytes){
    return 0;// thoát ngay
}

 byte data = 0;
     if( size_memory<=2){
Wire.beginTransmission(m_deviceAddress);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(m_deviceAddress, (byte)1);
    
   

     }else if(size_memory<=16){
        //24c04, 24c08 và 24c16


    Wire.beginTransmission((byte)(m_deviceAddress | ((address >> 8) & 0x07)));
    Wire.write(address & 0xFF);
    Wire.endTransmission();
    Wire.requestFrom((byte)(m_deviceAddress | ((address >> 8) & 0x07)), (byte)1);
   
   

 } else if(size_memory<=256){
        //24c32, 24c64, 24c128, 24c256


Wire.beginTransmission(m_deviceAddress);
    Wire.write(address >> 8);
    Wire.write(address & 0xFF);
    Wire.endTransmission();
    Wire.requestFrom(m_deviceAddress, (byte)1);
    
    
}
 if (Wire.available())
    { 
        data = Wire.read();
        delay(5);
        return data;
    }
    

}

void Eeprom24C::write_byte_eeprom_arduino(unsigned int   address,byte  data){

if(read_1_byte(address)==data){
    // nếu quá địa chỉ thì không ghi -> thoát
    // nếu dữ liệu đưa vào bằng dữ liệu cũ thì không cần ghi ->thoát
    //( tiết kiệm số lần ghi)
    return;// thoát ngay
}
EEPROM.write( address,data);
delay(5);
}
byte Eeprom24C::read_byte_eeprom_arduino( unsigned int address){
 byte data = EEPROM.read( address);
        delay(5);
        return data;

    }





// hàm chuyên biệt






void Eeprom24C::write_1_byte(unsigned int   address,byte  data){
if(select_eeprom==eeprom_on_arduino){
    write_byte_eeprom_arduino(address, data);
}else if( select_eeprom==eeprom_on_ic){
    write_byte_eeprom_ic(address, data);
}


}
byte Eeprom24C::read_1_byte(   unsigned int address){
if(select_eeprom==eeprom_on_arduino){
  return  read_byte_eeprom_arduino(address);
}else if( select_eeprom==eeprom_on_ic){
   return read_byte_eeprom_ic(address);
}
}

///////////// ghi/ và đọc số có cỡ 2 byte
  
void Eeprom24C::write_2_byte( unsigned int address, uint16_t data){
   //ghi
    
    byte cao_8=((data>>8) & 0xFF);
    write_1_byte(address, cao_8);  
    byte thap_8=(data & 0xFF);   
  write_1_byte(address+1, thap_8); 
}
  uint16_t Eeprom24C::read_2_byte(  unsigned int address){
   
// đọc
 uint16_t doc_cao_8, doc_thap_8;
doc_cao_8=read_1_byte(address);
doc_thap_8=read_1_byte(address+1);
uint16_t doc_data;
doc_data=(doc_cao_8<<8);
  return (doc_data|doc_thap_8);
  }

///////////// ghi/ và đọc số có cỡ 4 byte
  
void Eeprom24C::write_4_byte( unsigned int address, uint32_t data){
   //ghi
    // ghi 4 byte liên tiếp vào 4 ô kề nhau
    /*
   byte tam_bit_thu_0=(data & 0xFF);// 8 bit thấp đầu tiên
    write(address+3, tam_bit_thu_0);  
    byte tam_bit_thu_1=((data>>8)& 0xFF);// 8 bit cao hơn thứ 2
    write(address+2, tam_bit_thu_1);   
    byte tam_bit_thu_2=((data>>16)& 0xFF);
    write(address+1, tam_bit_thu_2); 
    byte tam_bit_thu_3=((data>>24)& 0xFF);
write(address, tam_bit_thu_3);
*/
for( byte i=0; i<4; i++){
    write_1_byte(address+3-i, ((data>>(8*i) )& 0xFF));  
    //delay
}
}
  uint32_t Eeprom24C::read_4_byte(  unsigned int address){
   
// đọc
 uint32_t tam_bit_thu[4];   
uint32_t doc_bit_thu[4];
    for( byte i=0; i<4; i++){
        tam_bit_thu[(3-i)]=read_1_byte( address+i);
    }
    
for(byte i=0; i<4; i++){
     doc_bit_thu[i]=(tam_bit_thu[i]<<(i*8));
}

/*
doc_bit_thu[3]=(tam_bit_thu[3]<<24);
doc_bit_thu[2]=(tam_bit_thu[2]<<16);
doc_bit_thu[1]=(tam_bit_thu[1]<<8);
doc_bit_thu[0]=(tam_bit_thu[0]<<0);*/
/*
uint32_t doc_data=(doc_bit_thu[3]|( doc_bit_thu[2]|(doc_bit_thu[1]|doc_bit_thu[0])));
*/
uint32_t doc_data;
for( byte i=0; i<4; i++){
    doc_data=doc_data|doc_bit_thu[i];
}
  return doc_data;
  }


///////////// ghi/ và đọc số có cỡ 8 byte
  
void Eeprom24C::write_8_byte( unsigned int address, uint64_t data){
   //ghi
    // ghi 4 byte liên tiếp vào 4 ô kề nhau
   
for( byte i=0; i<8; i++){
    write_1_byte(address+7-i, ((data>>(8*i) )& 0xFF));  
    //delay
}
}
  uint64_t Eeprom24C::read_8_byte(  unsigned int address){
   
// đọc
 uint64_t tam_bit_thu[8];   
uint64_t doc_bit_thu[8];
    for( byte i=0; i<8; i++){
        tam_bit_thu[(7-i)]=read_1_byte( address+i);
    }
    
for(byte i=0; i<8; i++){
     doc_bit_thu[i]=(tam_bit_thu[i]<<(i*8));
}
/*
doc_bit_thu[3]=(tam_bit_thu[3]<<24);
doc_bit_thu[2]=(tam_bit_thu[2]<<16);
doc_bit_thu[1]=(tam_bit_thu[1]<<8);
doc_bit_thu[0]=(tam_bit_thu[0]<<0);*/

uint64_t doc_data;
/*(..........doc_bit_thu[3]|( doc_bit_thu[2]|(doc_bit_thu[1]|doc_bit_thu[0])));*/
for( byte i=0; i<8; i++){
    doc_data=doc_data|doc_bit_thu[i];
}
  return doc_data;
  }