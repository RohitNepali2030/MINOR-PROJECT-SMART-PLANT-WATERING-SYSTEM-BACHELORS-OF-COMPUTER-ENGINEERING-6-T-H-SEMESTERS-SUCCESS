****Smart Plant Watering System****

An IoT-based smart irrigation system using ESP32, soil moisture sensor, and Blynk app to automate plant watering and send notifications.

📋 Table of Contents
About

Features

1. Components Used

2. Circuit Diagram

3. Installation

4. How It Works

5. Screenshots

6. Contributors

License

**🧠 About**

This project is a smart plant watering system designed for small-scale use. It automates watering based on soil moisture and allows users to monitor and control the system remotely using the Blynk mobile app.

✅ Features
-> Real-time soil moisture monitoring

-> Automatic water pump control

-> Manual pump control via Blynk app

-> Notifications when water level is low

-> DHT11 sensor integration for temperature and humidity tracking

**🧰 Components Used**
-> ESP32 Dev Board

-> Soil Moisture Sensor

-> DHT11 Temperature & Humidity Sensor

-> Relay Module

-> DC Water Pump

-> Water Tank

-> Power Supply (Battery/Adapter)

-> Blynk App (for mobile control)

**🔌 Circuit Diagram**
<img width="1536" height="860" alt="11111" src="https://github.com/user-attachments/assets/0dc29e9f-1346-46e0-8e03-030474aca198" /> 
**⚙️ Installation**
1. Clone the Repository:
https://github.com/RohitNepali2030/MINOR-PROJECT-SMART-PLANT-WATERING-SYSTEM-BACHELORS-OF-COMPUTER-ENGINEERING-6-T-H-SEMESTERS-SUCCESS

2. Open the .ino file in Arduino IDE.

3. Install Required Libraries:

   ->Blynk
   ->DHT sensor library

4. Configure Wi-Fi & Blynk Token in Code:
Replace placeholders with your actual Wi-Fi credentials and Blynk Auth Token.

5. Upload the Code to ESP32.

6. Open Serial Monitor to check system logs.

**🚀 How It Works**
-> The ESP32 continuously reads moisture level from the soil sensor.

-> If moisture is below a threshold, it turns on the pump using a relay.

-> You can also manually control the pump from the Blynk app.

-> DHT11 sensor sends temperature and humidity data to Blynk.

-> A notification is sent if the water tank level is low. 

**🖼️ Screenshots**
![521774775_764214285977452_4194011063315624517_n](https://github.com/user-attachments/assets/9d55de2c-24d4-4890-ba6d-e1775ad2b28c)



