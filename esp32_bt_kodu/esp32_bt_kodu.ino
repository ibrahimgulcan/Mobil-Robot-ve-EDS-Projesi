#include "BluetoothSerial.h"

BluetoothSerial SerialBT;


#define RX_PIN 16 
#define TX_PIN 17 

void setup() {
  Serial.begin(9600); 
  
  SerialBT.begin("IBRAHIM_ARABA_ESP32"); 
  Serial.println("Bluetooth Hazir! Baglanabilirsin...");

  
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); 
}

void loop() {
  if (SerialBT.available()) {
    char veri = SerialBT.read();
    
    
    Serial.print("Gelen: ");
    Serial.println(veri);

    
    Serial2.write(veri); 
  }
}