//http://arduino.vn/tutorial/1370-huong-dan-su-dung-ic-eeprom-24cxx-cua-atmel-va-thu-vien
//http://arduino.vn/tutorial/1371-bai-2-su-dung-nhieu-ic-eeprom-24cxx-cung-luc
//Kĩ thuật lưu 1 số bất kì :

//Code này mình tìm được trên trang arduino.cc
// dùng để lưu một số bất kì ở tất các kiểu Int, long, float, số âm dương vv
// Đoạn code này rất nhỏ gọn và tổng quát.
// Tâm sự : sau khi tìm được đoạn code này, mình đã rất vui và có phần hụt hẫng
// vì thư viện mà mình viết để lưu các kiểu int, long, ... chỉ là thứ BỎ ĐI 
// nó quá dài và không linh hoạt, do bận rộn nên mình chưa cập nhật thư viện 
//
// mình đã áp dụng kĩ thuật này để truyền dẫn thành công các số kiểu int,long, float...
//tại http://arduino.vn/tutorial/1471-truyen-cac-so-kieu-long-int-float-trong-giao-tiep-serial-uart
#include <EEPROM.h>

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
   const byte* p = (const byte*)(const void*)&value;
   int i;
   for (i = 0; i < sizeof(value); i++)
       EEPROM.write(ee++, *p++);
   return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
   byte* p = (byte*)(void*)&value;
   int i;
   for (i = 0; i < sizeof(value); i++)
       *p++ = EEPROM.read(ee++);
   return i;
}

struct st_t { long lo; byte by; double db; };

void setup()
{
   Serial.begin(9600);

   int n = 0;

   byte by = 0x33;
   Serial.println(by, HEX);
   n = EEPROM_writeAnything(0, by);
   Serial.print("Wrote bytes: ");
   Serial.println(n);
   by = 0xFF;
   Serial.println(by, HEX);
   n = EEPROM_readAnything(0, by);
   Serial.print("Read bytes: ");
   Serial.println(n);
   Serial.println(by, HEX);

   Serial.println("-------");

   long lo = 0xDEADBEEF;
   Serial.println(lo);
   n = EEPROM_writeAnything(23, lo);
   Serial.print("Wrote bytes: ");
   Serial.println(n);
   lo = 0xFFFFFFFF;
   Serial.println(lo);
   n = EEPROM_readAnything(23, lo);
   Serial.print("Read bytes: ");
   Serial.println(n);
   Serial.println(lo);

   Serial.println("-------");

   double pi = 3.1415926538;

   struct st_t st;
   st.lo = 0xABADF00D;
   st.by = 0x22;
   st.db = pi;
   Serial.println(st.lo);
   Serial.println(st.by, HEX);
   Serial.println(st.db == pi);
   n = EEPROM_writeAnything(221, st);
   Serial.print("Wrote bytes: ");
   Serial.println(n);
   st.lo = 0xFFFFFFFF;
   st.by = 0x11;
   st.db = 0.0;
   Serial.println(st.lo);
   Serial.println(st.by, HEX);
   Serial.println(st.db == pi);
   n = EEPROM_readAnything(221, st);
   Serial.print("Read bytes: ");
   Serial.println(n);
   Serial.println(st.lo);
   Serial.println(st.by, HEX);
   Serial.println(st.db == pi);
}

void loop()
{
}
