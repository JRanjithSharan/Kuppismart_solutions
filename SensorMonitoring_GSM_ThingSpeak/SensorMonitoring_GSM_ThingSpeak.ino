#define TINY_GSM_MODEM_SIM800

#include <SoftwareSerial.h>
#include <DHT.h>
#include <TinyGsmClient.h>
#include <ThingSpeak.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ2PIN A0
#define TEMP_THRESHOLD 30.0
#define GAS_THRESHOLD 300

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial SerialAT(2, 3); 
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

const char *apn = "airtelgprs.com"; 
const char *apiKey = "4VH0D5R904V5QR3A"; 
unsigned long channelID = 2567114;

void setup() {
  Serial.begin(9600);
  SerialAT.begin(9600);
  dht.begin();
  initializeGSM();
  ThingSpeak.begin(client);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int gasValue = analogRead(MQ2PIN);

  sendToThingSpeak(temperature, humidity, gasValue);

  if (temperature > TEMP_THRESHOLD) {
    sendSMS("Temperature exceeded threshold!");
  }

  if (gasValue > GAS_THRESHOLD) {
    sendSMS("Gas concentration exceeded threshold!");
  }

  delay(20000);
}

void initializeGSM() {
  modem.restart();
  if (!modem.waitForNetwork() || !modem.gprsConnect(apn)) {
    Serial.println("Failed to connect to network");
    while (true); 
  }
}

void sendToThingSpeak(float temperature, float humidity, int gasValue) {
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, gasValue);

  int responseCode = ThingSpeak.writeFields(channelID, apiKey);

  if (responseCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.print("Error sending data to ThingSpeak: ");
    Serial.println(responseCode);
  }
}

void sendSMS(String message) {
  modem.sendSMS("9789078720", message); 
  Serial.println("SMS sent: " + message);
}
