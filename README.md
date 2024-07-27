# Kuppismart Solutions

Welcome to the Kuppismart Solutions repository! This project features an integrated system for environmental monitoring and communication, leveraging various sensors and a SIM800 module to collect and transmit data.

## Project Overview

This project features an integrated system for environmental monitoring and communication, leveraging various sensors and a SIM800 module to collect and transmit data. It is designed to monitor environmental parameters and send the data via SMS. The system uses the BME280 sensor to measure temperature and humidity, while CO2 and TDS sensors provide additional environmental metrics. The data is transmitted through the SIM800 module.

## Hardware Components

- **Adafruit BME280**: Measures temperature, humidity, and pressure.
- **MG811**: Measures CO2 concentration.
- **TDS Sensor**: Measures Total Dissolved Solids (TDS) in liquids.
- **SIM800 Module**: For sending SMS messages.
- **Microcontroller**: Manages sensor readings and communication.

## Software Overview

The provided Arduino sketch initializes the sensors, reads their values, and sends the data via SMS. Key components of the code include:

- Initialization of sensors and serial communication.
- Data reading from BME280, CO2, and TDS sensors.
- SMS message composition and transmission using the SIM800 module.

## Installation and Usage

1. **Hardware Setup**:
   - Connect the BME280 sensor to the I2C bus.
   - Wire the CO2 sensor to the designated analog pin (MG811_PIN).
   - Connect the TDS sensor to the analog pin (TDS_PIN).
   - Connect the SIM800 module to the appropriate serial pins (SIM800_TX_PIN and SIM800_RX_PIN).

2. **Software Setup**:
   - Install the necessary libraries (`Wire.h`, `Adafruit_Sensor.h`, `Adafruit_BME280.h`).
   - Upload the provided Arduino sketch to your microcontroller.
   - Ensure the SIM800 module is properly configured to send SMS.

3. **Running the Code**:
   - After uploading the sketch, the system will start reading sensor data.
   - Data will be sent via SMS every 10 seconds to the predefined phone number.

## Customization

- **Phone Number**: Modify the phone number in the `sendToSIM800L` function to your desired recipient.
- **Sensor Calibration**: Adjust sensor readings and calibration as needed for your specific use case.

Feel free to modify or expand upon this template as needed!
