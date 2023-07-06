#include <LoRa.h>
#include <WEMOS_SHT3X.h>
#include <LiquidCrystal_I2C.h>

SHT3X sht30(0x45);

//LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  Serial.begin(115200);
  LoRa.setPins(D8, D4, D3);
  LoRa.begin(920E6);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  
  float temp;
  float humid;
  int counter;

  while (counter <= 60) {
    Serial.print("Sending packet: ");
    Serial.println(counter);

    if(sht30.get()==0){
    temp = sht30.cTemp;
    humid = sht30.humidity; 
    }
  
    lcd.setCursor(0, 0);       
    lcd.print(temp);    
    lcd.print((char)223);      
    lcd.print("C");
    lcd.setCursor(0, 1);       
    lcd.print(humid); 
    lcd.print((char)223);      
    lcd.print("%");
    
    LoRa.beginPacket();
    LoRa.print(counter);
    LoRa.print("|");
    LoRa.print(temp);
    LoRa.print("|");
    LoRa.print(humid);
    LoRa.print("|");
    LoRa.endPacket();

    counter++;
    delay(30000);
  }

  exit(0);
}