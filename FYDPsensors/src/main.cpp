#include <Arduino.h>

#define PIN_D3 5 // GPIO5 is mapped to D3 on XIAO ESP32C3

void setup() {
  pinMode(PIN_D3, OUTPUT); // Set D3 (GPIO5) as an output
  digitalWrite(PIN_D3, HIGH); // Set D3 (GPIO5) to HIGH
}

void loop() {
  // Nothing to do here; pin stays HIGH
}