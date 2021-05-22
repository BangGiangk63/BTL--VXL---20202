#include "DHT.h"
#include<Wifi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
// khai báo ssid và mật khẩu để kết nối wifi:
const char* SSID = "Minh Dien No7";
const char*PASSWORD = "00001111";
// khai báo chân pin kết nối của dht11:
#define DHTPIN2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};
void setup() {
  // put your setup code here, to run once:
  // khai báo baudrate:
  Serial.begin(115200);
  //kết nối wifi :
  WiFi.begin(SSID,PASSWORD);
  Serial.print("\nConnecting to WiFi.");
  while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\Connected to the WiFi network");
}
// cho dht11 hoat dong:
dht.begin();

  }

void loop() {
  // put your main code here, to run repeatedly:
  // quy định cứ mỗi 5s esp sẽ đọc giá trị cảm biến và gửi về cho server:
  delay(5000);
  // đọc giá trị đo được từ dht11:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // kiểm tra xem giá trị đo được có đúng không:
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Temperature:"));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("\tHumidity: "));
  Serial.print(h);
  Serial.print(F("% ");
delay(5000);
}
