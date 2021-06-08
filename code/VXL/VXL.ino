#include "DHT.h"
#include <Wire.h> 
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
BlynkTimer timer;

LiquidCrystal_I2C lcd(0x3F,16,2);
const int DHTPIN = 8;
const int DHTTYPE = DHT11;
#define BLYNK_PRINT Serial
char auth[] = "YourAuthToken";
char SSID[] = "YourNetworkName";
char PASSWORD[] = "YourPassword"
// khai báo chân pin kết nối của dht11:
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
  //ket noi blynk:
  Blynk.begin(auth, SSID, PASSWORD, "blynk.getblocky.com");
  timer.setInterval
  while (Blynk.connect() == false) {
    // Wait until connected
    delay(500);
  }
  Serial.println("Connected to Blynk server");
  //kết nối wifi :
  WiFi.begin(SSID,PASSWORD);
  Serial.print("\nConnecting to WiFi.");
  while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\Connected to the WiFi network");
}
lcd.init();
lcd.backlight();
lcd.createChar(0, degree);
lcd.setCursor(0,0);
lcd.print("  DHT11   with ");
lcd.setCursor(0,1);
delay(3000);
lcd.clear();
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
   }
  else{
  lcd.begin(16,2);
  lcd.print("nhiet do: ");
  lcd.print(t);
  lcd.setCursor(0,1);
  lcd.print("do am: ");
  lcd.print(h);
  lcd.setCursor(1,1);
  delay(2000);
  } 
delay(5000);
Blynk.run();
}
