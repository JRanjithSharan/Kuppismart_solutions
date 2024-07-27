#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <HardwareSerial.h>

#define BME280_I2C_ADDRESS 0x76  
#define MG811_PIN 34
#define TDS_PIN 35
#define SIM800_TX_PIN 17
#define SIM800_RX_PIN 16

Adafruit_BME280 bme; 
HardwareSerial sim800(2); 

void setup() {
  Serial.begin(115200);
  sim800.begin(9600, SERIAL_8N1, SIM800_RX_PIN, SIM800_TX_PIN);

  if (!bme.begin(BME280_I2C_ADDRESS)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  pinMode(MG811_PIN, INPUT);
  pinMode(TDS_PIN, INPUT);
}

void loop() {

  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();

  int co2Value = analogRead(MG811_PIN);
  int tdsValue = analogRead(TDS_PIN);


  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, CO2: ");
  Serial.print(co2Value);
  Serial.print("TDS: ");
  Serial.println(tdsValue);

  sendToSIM800L(temperature, humidity, co2Value, tdsValue);
  delay(10000);
}

void sendToSIM800L(float temp, float hum, int co2, int tds) {
  sim800.print("AT+CMGF=1\r"); 
  delay(1000);
  sim800.print("AT+CMGS=\"+919789078720\"\r"); 
  delay(1000);
  sim800.print("Temperature: ");
  sim800.print(temp);
  sim800.print(" C, Humidity: ");
  sim800.print(hum);
  sim800.print(" %, CO2: ");
  sim800.print(co2);
  sim800.print("TDS: ");
  sim800.print(tds);
  sim800.print("\r");
  delay(1000);
  sim800.write(26);
  delay(1000);
}
