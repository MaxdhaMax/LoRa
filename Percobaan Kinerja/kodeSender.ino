#include <LoRa.h>
#include <WEMOS_SHT3X.h>

SHT3X sht30(0x45);

void setup() {
  LoRa.setPins(D8, D4, D3);
//  LoRa.setSpreadingFactor(10);   // dicomment karena saat percobaan dapat dipakai ataupun tidak
  LoRa.begin(920E6);
}

void loop() {
  for (int i = 0; i < 60; i++) {
    sht30.get();
    LoRa.beginPacket();
    LoRa.print(i);              LoRa.print(", ");
    LoRa.print(sht30.cTemp);    LoRa.print(", ");
    LoRa.print(sht30.humidity); LoRa.print(", ");
    LoRa.endPacket();
    delay(5000);
  }
  ESP.deepSleep(0); 
}