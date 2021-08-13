#include <DHT.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "Timer.h"
#include <BlynkSimpleStream.h>
LiquidCrystal lcd (12,11,5,4,3,2);
int motor = 13; //khai báo chân 13 của arduino là chân motor
Timer timer; //khai báo timer
BlynkTimer blynkTimer; //Khai báo timer cho blynk  
const int DHTPIN = 8; //khai báo chân 8 là chân cảm biến
const int DHTTYPE = DHT11; //khai báo loại cảm biến là DHT11
int enbTemp = 30; //nhiệt độ đạt ngưỡng tưới
int enbHumi = 75; //độ ẩm đạt ngưỡng tưới  
unsigned long prevTime = 0; //biến lưu trữ trước khi cập nhật
float h, t; //khai báo biến nhiệt độ, độ ẩm
char auth[] = "9JPF8RjS9UcqFr7QSt8bFr4P9H2Nz1a5"; //mã kết nối với server blynk qua cổng USB

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

void writetoBlynk() {
   Blynk.run(); 
   Blynk.virtualWrite(V5, h); //chọn độ ẩm trên blynk gắn vào chân V5 chế độ virtual 
   Blynk.virtualWrite(V6, t); //chọn nhiệt độ trên blynk gắn vào chân V6 chế độ     virtual
}
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(motor,OUTPUT); //chân motor là output
  Blynk.begin(Serial, auth); //khởi tạo blynk
  blynkTimer.setInterval(5000, writetoBlynk); //cứ 5s thì dữ liệu sẽ gửi đến blynk một lần
}

void loop() {
  blynkTimer.run();
  timer.update();
  h = dht.readHumidity();   
  t = dht.readTemperature();
  unsigned long currTime = millis();  // biến lưu trữ thời gian hiện tại
  if(currTime - prevTime >= 1000){   //nếu biến hiện tại trừ biến trước khi cập nhật               mà lớn hơn 1s
//hiện thị nhiệt độ, độ ẩm lên lcd
  if (isnan(t)||isnan(h)){
    Serial.println("False to read from DHT11");
    }
  else { 
    lcd.begin(16,2);
    lcd.print("nhiet do: ");
    lcd.print(t);
    lcd.setCursor(0,1);
    lcd.print("do am: ");
    lcd.print(h);
    lcd.setCursor (1,1);
    }
    prevTime = currTime;   //thì dữ liệu sẽ được cập nhật lại
}

//khi nhiệt độ lớn hơn 30 độ C và độ ẩm nhỏ hơn 75% thì máy bơm hoạt động
    if(t >= enbTemp && h <= enbHumi )  {
      digitalWrite (motor, HIGH);
      } 
      else
      {
        digitalWrite (motor, LOW);
      }   
}
