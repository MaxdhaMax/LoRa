#include <LoRa.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(115200);
  LoRa.setPins(D8, D4, D3);
  LoRa.begin(920E6);
  lcd.begin();
  lcd.backlight();
  WiFi.begin("Galaxy A315AB0", "tich3524");
  while (!WiFi.isConnected()) delay(500);
}


void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String message = "";
    String temp;
    String humid;
    String counter;
    int erssi;

    while (LoRa.available()) {
       counter = LoRa.readStringUntil('|');
       temp = LoRa.readStringUntil('|');
       humid = LoRa.readStringUntil('|');
       erssi = LoRa.packetRssi();
    }

    lcd.clear();
    lcd.setCursor(0, 0);       // start to print at the first row
    lcd.print(temp);    // print the temperature in Celsius
    lcd.print((char)223);      // print ° character
    lcd.print("C");
    lcd.setCursor(0, 1);       // start to print at the second row
    lcd.print(humid); // print the temperature in Fahrenheit
    lcd.print((char)223);      // print ° character
    lcd.print("%");

    WiFiClient wifi;
    HTTPClient http;

    http.begin(wifi, "http://api.thingspeak.com/update");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.POST("api_key=ZZQC8MDSC93P0EW4&field1=" + temp + "&field2=" + humid + "&field3=" + erssi + "&field4=" + counter);
    http.end();

  }
}