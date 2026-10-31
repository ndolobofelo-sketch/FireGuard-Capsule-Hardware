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

// Flame sensor output logic
const bool FLAME_ACTIVE_HIGH = true;

// Pump driver or relay logic
const int PUMP_ON_LEVEL = HIGH;
const int PUMP_OFF_LEVEL = LOW;

// RGB LED configuration
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

  digitalWrite(
      PUMP_PIN,
      requestedState ? PUMP_ON_LEVEL : PUMP_OFF_LEVEL
  );

  pumpIsOn = requestedState;
}
// ================ GPS ================
String gpsText() {
  if (!gpsFix) {
    return "GPS fix not available";
  }

  return "Latitude: " + String(latitude, 6) +
         ", Longitude: " + String(longitude, 6);
}

void updateGPS() {
  while (GPSSerial.available()) {
    gps.encode(GPSSerial.read());
  }

  if (gps.location.isValid() &&
      gps.location.age() < 10000) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    gpsFix = true;
  } else {
    gpsFix = false;
  }
}

// ================ SMS ================
void sendSMS(const String& message) {
  Serial.println("Preparing FireGuard SMS...");

  SIM900.println("AT");
  delay(300);

  SIM900.println("AT+CMGF=1");
  delay(300);

  SIM900.print("AT+CMGS=\"");
  SIM900.print(emergencyNumber);
  SIM900.println("\"");

  delay(1000);

  SIM900.print(message);
  SIM900.write(26);

  delay(3000);

  while (SIM900.available()) {
    Serial.write(SIM900.read());
  }

  Serial.println();
  Serial.println(
      "SMS submission attempted. Verify modem response.");
}

// ================ SENSOR READING ================
void readSensors() {
  int flameValue = digitalRead(FLAME_PIN);

  flameDetected = FLAME_ACTIVE_HIGH
                      ? (flameValue == HIGH)
                      : (flameValue == LOW);

  float newTemperature = dht.readTemperature();
  float newHumidity = dht.readHumidity();

  if (isnan(newTemperature) ||
      isnan(newHumidity) ||
      newTemperature < 0.0 ||
      newTemperature > 80.0 ||
      newHumidity < 0.0 ||
      newHumidity > 100.0) {
    temperature = NAN;
    humidity = NAN;
    Serial.println("WARNING: DHT11 reading unavailable.");
  } else {
    temperature = newTemperature;
    humidity = newHumidity;
  }

  mq2Value = analogRead(MQ2_PIN);
  mq7Value = analogRead(MQ7_PIN);

  gasAlert =
      (mq2Value >= MQ2_THRESHOLD) ||
      (mq7Value >= MQ7_THRESHOLD);

  temperatureAlert =
      !isnan(temperature) &&
      temperature >= HIGH_TEMPERATURE;

  humidityAlert =
      !isnan(humidity) &&
      humidity < LOW_HUMIDITY;

  alertActive =
      flameDetected ||
      gasAlert ||
      temperatureAlert ||
      humidityAlert;

  // Pump remains disabled until enabled from the local dashboard.
  setPump(flameDetected);

  updateIndicators();

  if (alertActive && !smsSentForCurrentAlert) {
    String message = "FIREGUARD ALERT! ";

    if (flameDetected) {
      message += "Flame detected. ";
    }

    if (gasAlert) {
      message += "Gas threshold exceeded. ";
    }

    if (temperatureAlert) {
      message += "High temperature. ";
    }

    if (humidityAlert) {
      message += "Low humidity. ";
    }

    message += gpsText();

    smsSentForCurrentAlert = true;
    sendSMS(message);
  }

  if (!alertActive) {
    smsSentForCurrentAlert = false;
  }

  Serial.println();
  Serial.println("====== FIREGUARD STATUS ======");

  Serial.print("Flame: ");
  Serial.println(flameDetected ? "DETECTED" : "No flame");

  Serial.print("Temperature: ");
  if (isnan(temperature)) {
    Serial.println("Unavailable");
  } else {
    Serial.print(temperature, 1);
    Serial.println(" C");
  }

  Serial.print("Humidity: ");
  if (isnan(humidity)) {
    Serial.println("Unavailable");
  } else {
    Serial.print(humidity, 1);
    Serial.println(" %");
  }

  Serial.print("MQ2: ");
  Serial.println(mq2Value);

  Serial.print("MQ7: ");
  Serial.println(mq7Value);

  Serial.print("Alert: ");
  Serial.println(alertActive ? "YES" : "NO");

  Serial.print("Pump enabled: ");
  Serial.println(pumpEnabled ? "YES" : "NO");

  Serial.print("Pump: ");
  Serial.println(pumpIsOn ? "ON" : "OFF");

  Serial.print("Servo angle: ");
  Serial.println(servoAngle);

  Serial.print("GPS: ");
  Serial.println(gpsText());

  Serial.println("==============================");
}

// ================ JSON HELPERS ================
String jsonNumberOrNull(float value, int decimals = 1) {
  if (isnan(value) || isinf(value)) {
    return "null";
  }

  return String(value, decimals);
}

String jsonEscape(const String& input) {
  String out;
  out.reserve(input.length() + 8);

  for (size_t i = 0; i < input.length(); i++) {
    char c = input[i];

    if (c == '\\' || c == '"') {
      out += '\\';
    }

    if (c == '\n' || c == '\r') {
      continue;
    }

    out += c;
  }

  return out;
}
// ================ ONLINE TELEMETRY ================
void uploadTelemetry() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(
        "Telemetry skipped: Wi-Fi is not connected.");
    return;
  }

  if (!capsuleCode.length() || !deviceToken.length()) {
    Serial.println(
        "Telemetry skipped: capsule credentials are missing.");
    return;
  }

  WiFiClientSecure secureClient;

  // Prototype only: this disables certificate verification.
  // Validate the HTTPS server certificate before production use.
  secureClient.setInsecure();

  HTTPClient http;

  String url =
      String(FIREGUARD_API) + "/api/device/telemetry";

  if (!http.begin(secureClient, url)) {
    Serial.println(
        "Telemetry error: could not start HTTPS request.");
    return;
  }

  http.setTimeout(12000);
  http.addHeader("Content-Type", "application/json");

  String payload = "{";

  payload += "\"capsule_code\":\"";
  payload += jsonEscape(capsuleCode);
  payload += "\",";

  payload += "\"device_token\":\"";
  payload += jsonEscape(deviceToken);
  payload += "\",";

  payload += "\"temperature\":";
  payload += jsonNumberOrNull(temperature);
  payload += ",";

  payload += "\"smoke_level\":";
  payload += String(mq2Value);
  payload += ",";

  payload += "\"humidity\":";
  payload += jsonNumberOrNull(humidity);
  payload += ",";

  payload += "\"mq2\":";
  payload += String(mq2Value);
  payload += ",";

  payload += "\"mq7\":";
  payload += String(mq7Value);
  payload += ",";

  payload += "\"flame_detected\":";
  payload += flameDetected ? "true" : "false";
  payload += ",";

  payload += "\"latitude\":";
  payload += gpsFix ? String(latitude, 6) : "null";
  payload += ",";

  payload += "\"longitude\":";
  payload += gpsFix ? String(longitude, 6) : "null";
  payload += ",";

  payload += "\"communication_status\":\"online\",";
  payload += "\"sensor_status\":\"";

  payload +=
      (isnan(temperature) || isnan(humidity))
          ? "partial"
          : "online";

  payload += "\"}";

  Serial.println("Sending telemetry to FireGuard backend...");

  int httpCode = http.POST(payload);

  if (httpCode > 0) {
    Serial.print("Telemetry HTTP status: ");
    Serial.println(httpCode);

    Serial.print("Backend response: ");
    Serial.println(http.getString());
  } else {
    Serial.print("Telemetry request failed: ");
    Serial.println(http.errorToString(httpCode));
  }

  http.end();
}

// ================ SERVO CONTROL ================
void updateServo() {
  if (!servoAttached) {
    return;
  }

  if (!flameDetected) {
    if (servoAngle != SERVO_CENTER) {
      servoAngle = SERVO_CENTER;
      servoMotor.write(servoAngle);
    }

    servoDirection = 1;
    return;
  }

  if (millis() - lastServoMove < SERVO_MOVE_INTERVAL) {
    return;
  }

  lastServoMove = millis();
  servoAngle += SERVO_STEP * servoDirection;

  if (servoAngle >= SERVO_MAX_ANGLE) {
    servoAngle = SERVO_MAX_ANGLE;
    servoDirection = -1;
  } else if (servoAngle <= SERVO_MIN_ANGLE) {
    servoAngle = SERVO_MIN_ANGLE;
    servoDirection = 1;
  }

  servoMotor.write(servoAngle);
}
// ================ LOCAL DASHBOARD ================
void handleRoot() {
  String html = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>FireGuard Dashboard</title>
<style>
body {
  font-family: Arial, sans-serif;
  margin: 20px;
  background: #f2f4f7;
  color: #202530;
}
h1 { color: #b22222; }
.card {
  background: white;
  padding: 15px;
  margin: 10px 0;
  border-radius: 10px;
  box-shadow: 0 2px 6px #0001;
}
button {
  padding: 12px 16px;
  margin: 5px;
  border: 0;
  border-radius: 6px;
  cursor: pointer;
}
.stop { background: #b22222; color: white; }
.enable { background: #18864b; color: white; }
</style>
</head>
<body>
<h1>FireGuard Dashboard</h1>

<div class="card">System status: <b id="status">Loading...</b></div>
<div class="card">Flame: <span id="flame">--</span></div>
<div class="card">Temperature: <span id="temp">--</span> &deg;C</div>
<div class="card">Humidity: <span id="humidity">--</span> %</div>
<div class="card">MQ-2: <span id="mq2">--</span></div>
<div class="card">MQ-7: <span id="mq7">--</span></div>
<div class="card">Pump: <span id="pump">--</span></div>
<div class="card">Pump control: <span id="pumpControl">--</span></div>
<div class="card">Servo angle: <span id="servo">--</span>&deg;</div>
<div class="card">GPS: <span id="gps">--</span></div>

<button class="stop" onclick="controlPump('/stopPump')">
Disable pump
</button>

<button class="enable" onclick="controlPump('/enablePump')">
Enable pump
</button>

<script>
async function updateData() {
  try {
    const response = await fetch('/data');
    if (!response.ok) throw new Error('HTTP error');

    const d = await response.json();

    document.getElementById('status').textContent =
      d.alert ? 'ALERT' : 'NORMAL';

    document.getElementById('flame').textContent =
      d.flame ? 'DETECTED' : 'No flame';

    document.getElementById('temp').textContent = d.temperature;
    document.getElementById('humidity').textContent = d.humidity;
    document.getElementById('mq2').textContent = d.mq2;
    document.getElementById('mq7').textContent = d.mq7;

    document.getElementById('pump').textContent =
      d.pump ? 'ON' : 'OFF';

    document.getElementById('pumpControl').textContent =
      d.pumpEnabled ? 'Enabled' : 'Disabled';

    document.getElementById('servo').textContent = d.servo;
    document.getElementById('gps').textContent = d.gps;

  } catch (e) {
    document.getElementById('status').textContent =
      'Connection error';
  }
}

async function controlPump(path) {
  try {
    const response = await fetch(path);
    if (!response.ok) throw new Error('Control failed');
    await updateData();
  } catch (e) {
    document.getElementById('status').textContent =
      'Connection error';
  }
}

updateData();
setInterval(updateData, 2000);
</script>
</body>
</html>
)HTML";

  server.send(200, "text/html", html);
}

// ================ DASHBOARD DATA ================
void handleData() {
  String json = "{";

  json += "\"alert\":";
  json += alertActive ? "true" : "false";

  json += ",\"flame\":";
  json += flameDetected ? "true" : "false";

  json += ",\"temperature\":\"";
  json += isnan(temperature)
              ? "Unavailable"
              : String(temperature, 1);
  json += "\"";

  json += ",\"humidity\":\"";
  json += isnan(humidity)
              ? "Unavailable"
              : String(humidity, 1);
  json += "\"";

  json += ",\"mq2\":";
  json += String(mq2Value);

  json += ",\"mq7\":";
  json += String(mq7Value);

  json += ",\"pump\":";
  json += pumpIsOn ? "true" : "false";

  json += ",\"pumpEnabled\":";
  json += pumpEnabled ? "true" : "false";

  json += ",\"servo\":";
  json += String(servoAngle);

  json += ",\"gps\":\"";

  if (gpsFix) {
    json += String(latitude, 6);
    json += ", ";
    json += String(longitude, 6);
  } else {
    json += "No GPS fix";
  }

  json += "\"}";

  server.send(200, "application/json", json);
}

// ================ PUMP DASHBOARD CONTROLS ================
void handleStopPump() {
  pumpEnabled = false;
  setPump(false);

  server.send(200, "text/plain", "Pump disabled");
}

void handleEnablePump() {
  pumpEnabled = true;
  setPump(flameDetected);

  server.send(200, "text/plain", "Pump enabled");
}

// ================ WIFI MANAGEMENT ================
void maintainWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  if (millis() - lastWiFiRetry < WIFI_RETRY_INTERVAL) {
    return;
  }

  lastWiFiRetry = millis();

  Serial.println("Wi-Fi disconnected. Reconnecting...");

  WiFi.disconnect();
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
}
// ================ SETUP ================

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(120000);
  delay(800);

  // Load saved settings without clearing Preferences.
  loadPrivateSettings();

  pinMode(FLAME_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);

  analogReadResolution(12);

  setRGB(false, false, false);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(PUMP_PIN, PUMP_OFF_LEVEL);

  pumpIsOn = false;
  pumpEnabled = false;

  dht.begin();
  delay(2000);

  GPSSerial.begin(
      9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN
  );

  SIM900.begin(
      9600, SERIAL_8N1, SIM900_RX_PIN, SIM900_TX_PIN
  );

  servoMotor.setPeriodHertz(50);

  servoAttached = servoMotor.attach(
      SERVO_PIN, 500, 2400
  );

  if (servoAttached) {
    servoAngle = SERVO_CENTER;
    servoMotor.write(SERVO_CENTER);
    Serial.println("SG90 servo initialized.");
  } else {
    Serial.println("ERROR: Servo could not be attached.");
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());

  Serial.print("Connecting to Wi-Fi...");

  unsigned long startAttempt = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttempt < 20000) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi connected.");
    Serial.print("Local dashboard: http://");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Wi-Fi connection failed; will retry.");
  }

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.on("/stopPump", handleStopPump);
  server.on("/enablePump", handleEnablePump);

  server.begin();

  Serial.println("FireGuard started.");
  Serial.println("Pump is disabled for initial testing.");
}

// ================ MAIN LOOP ================
void loop() {
  updateGPS();
  server.handleClient();
  maintainWiFi();

  if (millis() - lastSensorRead >= SENSOR_INTERVAL) {
    lastSensorRead = millis();
    readSensors();
  }

  if (millis() - lastTelemetryUpload >= TELEMETRY_INTERVAL) {
    lastTelemetryUpload = millis();
    uploadTelemetry();
  }

  updateServo();
}
