#include <LoRa.h>

void setup() {
  Serial.begin(115200);
  LoRa.setPins(D8, D4, D3);
//  LoRa.setSpreadingFactor(10);       // dicomment karena saat percobaan dapat dipakai ataupun tidak
  LoRa.begin(920E6);
},

void loop() {
  if (LoRa.parsePacket()) {
    while (LoRa.available())
      Serial.print((char)LoRa.read());
    Serial.println(LoRa.packetRssi());
  }}

