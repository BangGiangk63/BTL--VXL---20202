#include <DHT.h>
#include <BlynkSimpleStream.h>
#include <Wire.h> 
#include <LiquidCrystal.h>
//#define BLYNK_PRINT SwSerial
LiquidCrystal lcd (12,11,5,4,3,2);
int motor = 13; ;//khai báo chân 13 của arduino là chân motor
unsigned long prevTime = 0; //biến lưu trữ trước khi cập nhật
const int DHTPIN = 8;
const int DHTTYPE = DHT11;
char auth[] = "9JPF8RjS9UcqFr7QSt8bFr4P9H2Nz1a5";

DHT dht(DHTPIN, DHTTYPE); //khai báo thư viện chân cảm biến và kiểu cảm biến
byte degree[8]={
   0B01110,
   0B01010,
   0B01110,
   0B00000,
   0B00000,
   0B00000,
   0B00000
};
void setup() { 
  Serial.begin(9600); 
  dht.begin();
  pinMode(motor,OUTPUT); //chân motor là output
  Blynk.begin(Serial, auth); /khởi tạo blynk
}

void loop() {
    Blynk.run();
   // timer.run();
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    Blynk.virtualWrite(V5, h); //chọn độ ẩm trên blynk gắn vào chân V5 chế độ virtual 
    Blynk.virtualWrite(V6, t); //chọn nhiệt độ trên blynk gắn vào chân V6 chế độ virtual
    unsigned long currTime = millis(); // biến lưu trữ thời gian hiện tại
    //Ngắt
    if(currTime - prevTime >= 1000){   //nếu biến hiện tại trừ biến trước khi cập nhật mà lớn hơn 1s
    prevTime = currTime;               //thì dữ liệu sẽ được cập nhật lại
     if (isnan(t)||isnan(h)){
      Serial.println("False to read from DHT11");
     }
     else{
       lcd.begin(16,2);
       lcd.print("nhiet do: ");
       lcd.print(t);
       lcd.setCursor(0,1);
       lcd.print("do am: ");
       lcd.print(h);
       lcd.setCursor(1,1);
         }
         //khi nhiệt độ lớn hơn 30 độ C và độ ẩm nhỏ hơn 75% thì máy bơm hoạt động
        if(t >= 30 && h <= 75 )
          {
           digitalWrite(motor,LOW);
          } 
         else
          {
           digitalWrite(motor,HIGH);
          }   
       }
     
}
