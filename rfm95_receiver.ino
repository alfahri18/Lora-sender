#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 15
#define rst 16
#define dio0 4

int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  // LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

      // register the receive callback
  LoRa.onReceive(onReceive);
 
  // put the radio into receive mode
  LoRa.receive();
}

void loop() {
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");
 
  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }
 
  // print RSSI of packet
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
}
