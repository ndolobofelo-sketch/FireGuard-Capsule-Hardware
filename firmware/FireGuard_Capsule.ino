#include <WiFi.h>
#include <WebServer.h>
#include <TinyGPSPlus.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <math.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Preferences.h>

// ================ PRIVATE SETTINGS ================
// Enter settings in Serial Monitor on first startup.
// They are stored locally in ESP32 Preferences.
Preferences settingsStore;

String wifiSSID;
String wifiPassword;
String emergencyNumber;
String capsuleCode;
String deviceToken;

String readSerialSetting(const char* prompt) {
  Serial.println();
  Serial.println(prompt);

  while (!Serial.available()) {
    delay(20);
  }

  String value = Serial.readStringUntil('\n');
  value.trim();
  return value;
}

void loadPrivateSettings() {
  settingsStore.begin("fireguard", false);

  wifiSSID = settingsStore.getString("wifi_ssid", "");
  wifiPassword = settingsStore.getString("wifi_pass", "");
  emergencyNumber = settingsStore.getString("emergency", "");
  capsuleCode = settingsStore.getString("capsule", "");
  deviceToken = settingsStore.getString("device_token", "");

  if (wifiSSID.length() &&
      wifiPassword.length() &&
      emergencyNumber.length() &&
      capsuleCode.length() &&
      deviceToken.length()) {
    Serial.println("Private FireGuard settings loaded.");
    return;
  }

  Serial.println();
  Serial.println("===== FIRST-TIME FIREGUARD SETUP =====");
  Serial.println("Serial Monitor: 115200 baud, Newline.");
  Serial.println("Keep all entered credentials private.");

  wifiSSID = readSerialSetting(
      "Enter your Wi-Fi network name (SSID):");

  wifiPassword = readSerialSetting(
      "Enter your Wi-Fi password:");

  emergencyNumber = readSerialSetting(
      "Enter emergency phone number with country code:");

  capsuleCode = readSerialSetting(
      "Enter your registered FireGuard capsule code:");

  deviceToken = readSerialSetting(
      "Enter your private device token:");

  if (!wifiSSID.length() ||
      !wifiPassword.length() ||
      !emergencyNumber.length() ||
      !capsuleCode.length() ||
      !deviceToken.length()) {
    Serial.println(
        "ERROR: A setting is empty. Restart and enter every value.");
    while (true) {
      delay(1000);
    }
  }

  settingsStore.putString("wifi_ssid", wifiSSID);
  settingsStore.putString("wifi_pass", wifiPassword);
  settingsStore.putString("emergency", emergencyNumber);
  settingsStore.putString("capsule", capsuleCode);
  settingsStore.putString("device_token", deviceToken);

  Serial.println("Private settings saved on this ESP32.");
}

// ================ FIREGUARD BACKEND ================
const char* FIREGUARD_API =
    "https://fireguard-backend-pxyf.onrender.com";

unsigned long lastTelemetryUpload = 0;
const unsigned long TELEMETRY_INTERVAL = 15000;

// ================ ESP32 PINS ================
#define FLAME_PIN 18
#define DHT_PIN 19
#define MQ2_PIN 34
#define MQ7_PIN 35

#define GPS_RX_PIN 32
#define GPS_TX_PIN 33

#define SIM900_RX_PIN 16
#define SIM900_TX_PIN 17

#define RED_PIN 25
#define GREEN_PIN 26
#define BLUE_PIN 14

#define BUZZER_PIN 22
#define PUMP_PIN 27
#define SERVO_PIN 13

// ================ SENSOR SETTINGS ================
#define DHT_TYPE DHT11

const int MQ2_THRESHOLD = 1800;
const int MQ7_THRESHOLD = 1800;

const float HIGH_TEMPERATURE = 35.0;
const float LOW_HUMIDITY = 30.0;

// Confirm the flame sensor's output logic for your module.
const bool FLAME_ACTIVE_HIGH = true;

// Verify these levels against your pump driver or relay.
const int PUMP_ON_LEVEL = HIGH;
const int PUMP_OFF_LEVEL = LOW;

// false is normally used for common-cathode RGB LEDs.
const bool RGB_COMMON_ANODE = false;

// ================ SERVO SETTINGS ================
const int SERVO_CENTER = 90;
const int SERVO_MIN_ANGLE = 60;
const int SERVO_MAX_ANGLE = 120;
const int SERVO_STEP = 3;

const unsigned long SERVO_MOVE_INTERVAL = 100;

// ================ TIMING ================
const unsigned long SENSOR_INTERVAL = 2500;
const unsigned long WIFI_RETRY_INTERVAL = 10000;

// ================ OBJECTS ================
WebServer server(80);
TinyGPSPlus gps;
DHT dht(DHT_PIN, DHT_TYPE);
Servo servoMotor;

HardwareSerial GPSSerial(1);
HardwareSerial SIM900(2);

// ================ VARIABLES ================
float temperature = NAN;
float humidity = NAN;

int mq2Value = 0;
int mq7Value = 0;

bool flameDetected = false;
bool gasAlert = false;
bool temperatureAlert = false;
bool humidityAlert = false;
bool alertActive = false;

// Pump is disabled initially for safer testing.
bool pumpEnabled = false;
bool pumpIsOn = false;

bool smsSentForCurrentAlert = false;
bool servoAttached = false;

double latitude = 0.0;
double longitude = 0.0;
bool gpsFix = false;

int servoAngle = SERVO_CENTER;
int servoDirection = 1;

unsigned long lastSensorRead = 0;
unsigned long lastServoMove = 0;
unsigned long lastWiFiRetry = 0;

// ================ RGB LED ================
void setRGB(bool red, bool green, bool blue) {
  if (RGB_COMMON_ANODE) {
    digitalWrite(RED_PIN, red ? LOW : HIGH);
    digitalWrite(GREEN_PIN, green ? LOW : HIGH);
    digitalWrite(BLUE_PIN, blue ? LOW : HIGH);
  } else {
    digitalWrite(RED_PIN, red ? HIGH : LOW);
    digitalWrite(GREEN_PIN, green ? HIGH : LOW);
    digitalWrite(BLUE_PIN, blue ? HIGH : LOW);
  }
}

void updateIndicators() {
  if (flameDetected) {
    setRGB(true, false, false);
  } else if (gasAlert || temperatureAlert || humidityAlert) {
    setRGB(true, true, false);
  } else {
    setRGB(false, true, false);
  }

  digitalWrite(BUZZER_PIN, alertActive ? HIGH : LOW);
}

// ================ PUMP CONTROL ================
void setPump(bool turnOn) {
  bool requestedState = turnOn && pumpEnabled;
