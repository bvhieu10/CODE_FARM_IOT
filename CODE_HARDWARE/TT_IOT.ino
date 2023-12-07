#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "Adafruit_SHT31.h"
#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); 
#define SHT31_ADDRESS   0x44
Adafruit_SHT31 sht31 = Adafruit_SHT31();

const char *ssid     = "Giangnam Coffee VN";
const char *password = "";


// Thông tin Firebase
#define FIREBASE_HOST "https://lab3-86899-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "y7fcZDGvh9y7KF4hTNiVWpqjAj9NGWDEGpAYnpm3"

// Thông tin mạng Wi-Fi


//#include "Adafruit_SHT31.h"
 
// Khởi tạo màn hình LCD I2C

// Khai báo đối tượng Firebase
FirebaseData fbdo;
FirebaseData fbdo1;
// Định nghĩa các chân điều khiển

#define RED_LED 27
#define SUONG_LED 26
//#define MQ2_SENSOR 34
#define GIAMSAT_LED 25

//#define DHT_PIN 13
//#define DHT_TYPE DHT11
//DHT dht(DHT_PIN, DHT_TYPE);

// Biến thời gian
unsigned long dataMillis = 0;

// Các biến trạng thái của thiết bị
int giamsat_state = 0;
int led_state=0;
int suong_state=0;

void setup() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  tft.init();
  Wire.begin(21,22);
  Serial.begin(115200);

  // Khởi tạo Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  sht31.begin(SHT31_ADDRESS);
  if (! sht31.begin(0x44))
  {
  Serial.println("Couldn't find SHT31");
  while (1) delay(1);
  }

  pinMode(RED_LED, OUTPUT);
  pinMode(SUONG_LED, OUTPUT);
  pinMode(GIAMSAT_LED, OUTPUT);

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 3, 4);
  tft.setTextColor(TFT_GREEN);
  tft.println(" FARM IOT");

  tft.setCursor(10, 40, 4);
  tft.setTextColor(TFT_PINK);
  tft.print("Nhiet Do:");

  tft.setCursor(10, 100, 4);
  tft.setTextColor(TFT_PINK);
  tft.print("Do am:");

  tft.setCursor(10, 170, 2);
  tft.setTextColor(TFT_PINK); 
  tft.print("TT_LED:");

  tft.setCursor(10, 200, 2);
  tft.setTextColor(TFT_PINK); 
  tft.print("TT_DHOA:");

  tft.setCursor(10, 230, 2);
  tft.setTextColor(TFT_PINK); 
  tft.print("TT_CBAO:");

  tft.setCursor(10, 270, 2);
  tft.setTextColor(TFT_WHITE); 
  tft.print("NguyenVanTruong");
  tft.setCursor(10, 290, 2);
  tft.setTextColor(TFT_WHITE); 
  tft.print("BuiVanHieu");
}

void notification() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();


  tft.setCursor(60, 70, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.print(t,1); 
  tft.print("C");
  Serial.print(t);

  

  tft.setCursor(60, 130, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.print(h,1); 
  tft.print("%");
  Serial.print(h);
  
  Firebase.RTDB.getBool(&fbdo,"/thietbi1/den");
  led_state = fbdo.boolData();
  Serial.print("Led2 state: ");
  Serial.print(led_state);
  Serial.println();
  if(led_state==1){
    digitalWrite(RED_LED, HIGH);
    tft.setCursor(80, 170, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); 
    tft.print("ON  ");
  }
  else
  {
    digitalWrite(RED_LED, LOW);
    tft.setCursor(80, 170, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); 
    tft.print("OFF");
  }

  Firebase.RTDB.getBool(&fbdo,"/thietbi2/dieuhoa");
  suong_state = fbdo.boolData();
  Serial.print("suong state: ");
  Serial.print(suong_state);
  Serial.println();
  if(suong_state==1){
    digitalWrite(SUONG_LED, HIGH);
    tft.setCursor(80, 200, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); 
    tft.print("ON  ");
  }
  else
  {
    digitalWrite(SUONG_LED, LOW);
    tft.setCursor(80, 200, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); 
    tft.print("OFF");
  }

  Firebase.RTDB.getBool(&fbdo,"/thietbi3/giamsat");
  giamsat_state = fbdo.boolData();
  Serial.print("giamsat: ");
  Serial.print(giamsat_state);
  Serial.println();
  if(giamsat_state==1){
    digitalWrite(GIAMSAT_LED, HIGH);
    tft.setCursor(80, 230, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); 
    tft.print("ON  ");
  }
  else
  {
    digitalWrite(GIAMSAT_LED, LOW);
    tft.setCursor(80, 230, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); 
    tft.print("OFF");
  }

  // Cập nhật dữ liệu lên Firebase
  //if (millis() - dataMillis > 5000) {
    Serial.printf("Update ... %s\n", Firebase.setFloat(fbdo, "Do am", h) ? "Ok" : fbdo.errorReason().c_str());
    //Serial.printf("Update ... %s\n", Firebase.setInt(fbdo, "/Living room/Khi gas", mq2Value) ? "Ok" : fbdo.errorReason().c_str());
    Serial.printf("Update ... %s\n", Firebase.setFloat(fbdo, "Nhiet do", t) ? "Ok" : fbdo.errorReason().c_str());
    //dataMillis = millis();

    delay(1000);
 // }
}

void loop() {
  notification();
}