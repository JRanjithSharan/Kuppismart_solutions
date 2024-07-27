#include <Arduino.h>
#include <HardwareSerial.h>
#include <EEPROM.h> // Include EEPROM library

// Define UART object for SIM module (using HardwareSerial)
HardwareSerial SIMSerial(1);

// Define relay control pin (connected to GP17)
const int relayPin = 17;

// Define EEPROM address for storing relay state
int eepromAddress = 0;
bool lastRelayState = LOW; // Initial state

void setup() {
  Serial.begin(9600); // Initialize serial communication with Arduino IDE Serial Monitor
  SIMSerial.begin(9600, SERIAL_8N1, 4, 5); // Initialize UART1 (GP4=TX, GP5=RX) for SIM module
  
  pinMode(relayPin, OUTPUT); // Set relay pin as output

  // Read last relay state from EEPROM
  lastRelayState = EEPROM.read(eepromAddress);
  digitalWrite(relayPin, lastRelayState); // Set initial relay state
}

void loop() {
  if (SIMSerial.available()) {
    String message = SIMSerial.readString();
    message.trim();
    
    Serial.print("Message received: ");
    Serial.println(message);
    
    if (message.equalsIgnoreCase("ON")) {
      digitalWrite(relayPin, HIGH); // Turn on the relay (activating the DOL starter)
      Serial.println("DOL Starter turned ON.");
      lastRelayState = HIGH; // Update last relay state
    } else if (message.equalsIgnoreCase("OFF")) {
      digitalWrite(relayPin, LOW); // Turn off the relay (deactivating the DOL starter)
      Serial.println("DOL Starter turned OFF.");
      lastRelayState = LOW; // Update last relay state
    }
    
    // Write current relay state to EEPROM
    EEPROM.write(eepromAddress, lastRelayState);
    EEPROM.commit(); // Save changes to EEPROM
    
    SIMSerial.flush(); // Clear the received message buffer
  }
}
