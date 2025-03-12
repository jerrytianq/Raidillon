#include <Arduino.h>
#include "config.h"

// Buffer to store incoming UART data
char receivedData[32];
int dataIndex = 0;

void setup() {
  // Initialize GPIO2 as output
  pinMode(GPIO2, OUTPUT);
  digitalWrite(GPIO2, LOW); // Start with GPIO2 LOW
  
  // Initialize Serial for debugging (USB)
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for serial to connect
  
  // Initialize UART2 for communication
  Serial1.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  Serial.println("XIAO ESP32-C3 UART Reader Started");
}

void loop() {
  // Check if data is available on UART2
  while (Serial1.available()) {
    char incomingChar = Serial1.read();
    
    // Check for message end or buffer limit
    if (incomingChar == '\n' || incomingChar == '\r' || dataIndex >= 31) {
      receivedData[dataIndex] = '\0'; // Null terminate the string
      
      // Check if message contains "ON"
      if (strstr(receivedData, "ON") != NULL) {
        digitalWrite(GPIO2, HIGH);
        Serial.println("GPIO2 set HIGH - 'ON' detected");
      } else {
        digitalWrite(GPIO2, LOW);
        Serial.println("GPIO2 set LOW");
      }
      
      // Reset buffer and index
      dataIndex = 0;
      memset(receivedData, 0, sizeof(receivedData));
    } 
    else {
      // Store character in buffer
      receivedData[dataIndex] = incomingChar;
      dataIndex++;
    }
  }
}
