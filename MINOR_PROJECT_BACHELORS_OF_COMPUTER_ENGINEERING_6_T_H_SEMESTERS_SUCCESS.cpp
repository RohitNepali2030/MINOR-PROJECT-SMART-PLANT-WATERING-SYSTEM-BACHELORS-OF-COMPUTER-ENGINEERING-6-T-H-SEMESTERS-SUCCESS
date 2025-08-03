#define BLYNK_TEMPLATE_ID "TMPL6R3sD_hHX"
#define BLYNK_TEMPLATE_NAME "SMART PLANT WATERING SYSTEM"
#define BLYNK_AUTH_TOKEN "14_S6EnI5sOjbUxS9ZFGALuTYyGe2izM"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// --- Pin Definitions ---
#define DHTPIN 14
#define DHTTYPE DHT11
#define SOIL_PIN 34
#define RELAY_PIN 25

// --- WiFi Credentials ---
char ssid[] = "SM-POKHARA1";
char pass[] = "6557165571";

// --- Sensor & Timer Setup ---
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// --- State Variables ---
int mode = 0;               // 0 = Auto, 1 = Manual
int manualPump = 0;         // 1 = ON, 0 = OFF
bool isSoilDry = false;
bool pumpOn = false;

// --- Virtual Pins ---
#define PUMP_LED_VPIN V5

// --- Mode Switch (Auto / Manual) ---
BLYNK_WRITE(V4) {
  mode = param.asInt();
}

// --- Manual Pump Button ---
BLYNK_WRITE(V3) {
  manualPump = param.asInt();
}

void sendSensorData() {
  // --- Read Sensors ---
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  int soilRaw = analogRead(SOIL_PIN);
  int soilPercent = map(soilRaw, 4095, 0, 0, 100);  // 4095 = dry, 0 = wet

  // --- Send to Blynk ---
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, soilPercent);

  // --- Debug Output ---
  Serial.print("Soil Raw: ");
  Serial.print(soilRaw);
  Serial.print(" | Soil %: ");
  Serial.print(soilPercent);
  Serial.print(" | Mode: ");
  Serial.print(mode == 0 ? "AUTO" : "MANUAL");
  Serial.print(" | Manual Pump: ");
  Serial.print(manualPump);
  Serial.print(" | Pump State: ");

  // --- Soil Moisture Notification ---
  if (soilPercent < 30 && !isSoilDry) {
    Blynk.logEvent("dry_soil", "Soil is too dry! Pump may turn on.");
    isSoilDry = true;
  } else if (soilPercent >= 30 && isSoilDry) {
    Blynk.logEvent("wet_soil", "Soil is wet again.");
    isSoilDry = false;
  }

  // --- Decide Pump State ---
  bool pumpShouldBeOn;
  if (mode == 0) {
    pumpShouldBeOn = (soilPercent < 30);
  } else {
    pumpShouldBeOn = (manualPump == 1);
  }

  Serial.println(pumpShouldBeOn ? "ON" : "OFF");

  // --- REVERSED RELAY LOGIC (Active HIGH) ---
  digitalWrite(RELAY_PIN, pumpShouldBeOn ? HIGH : LOW);

  // --- Pump LED Widget ---
  Blynk.virtualWrite(PUMP_LED_VPIN, pumpShouldBeOn ? 255 : 0);

  // --- Pump ON/OFF Notifications ---
  if (pumpShouldBeOn != pumpOn) {
    pumpOn = pumpShouldBeOn;
    if (pumpOn) {
      Blynk.logEvent("pump_on", "Water Pump is ON.");
    } else {
      Blynk.logEvent("pump_off", "Water Pump is OFF.");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Relay OFF at start (for Active HIGH relay)

  dht.begin();
  timer.setInterval(3000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}