
#include <Arduino.h>
#include <DHTesp.h>
#include <ESP32Servo.h>

// FireGuard Capsule
// ESP32 Detection and Actuation — Wokwi simulation
// This firmware is for simulation only.

constexpr int PIN_FLAME  = 18;
constexpr int PIN_DHT    = 19;
constexpr int PIN_MQ2    = 34;
constexpr int PIN_MQ7    = 35;

constexpr int PIN_SERVO  = 13;
constexpr int PIN_PUMP   = 27;
constexpr int PIN_BUZZER = 22;
constexpr int PIN_GREEN  = 25;
constexpr int PIN_RED    = 26;

constexpr float HIGH_TEMPERATURE_C = 35.0;
constexpr float LOW_HUMIDITY_PCT = 30.0;

constexpr int MQ2_THRESHOLD = 1800;
constexpr int MQ7_THRESHOLD = 1800;

DHTesp dht;
Servo actuator;

float temperatureC = NAN;
float humidityPct = NAN;

int mq2Value = 0;
int mq7Value = 0;

bool flameDetected = false;
bool alarmActive = false;

unsigned long lastReportTime = 0;
constexpr unsigned long REPORT_INTERVAL_MS = 2000;

void setup() {
  Serial.begin(115200);

  pinMode(PIN_FLAME, INPUT_PULLUP);
  pinMode(PIN_MQ2, INPUT);
  pinMode(PIN_MQ7, INPUT);

  pinMode(PIN_PUMP, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);

  analogReadResolution(12);

  dht.setup(PIN_DHT, DHTesp::DHT22);

  actuator.setPeriodHertz(50);
  actuator.attach(PIN_SERVO, 500, 2400);
  actuator.write(90);

  digitalWrite(PIN_PUMP, LOW);
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, HIGH);

  Serial.println();
  Serial.println("==================================");
  Serial.println("       FIREGUARD CAPSULE");
  Serial.println(" ESP32 DETECTION AND ACTUATION");
  Serial.println("==================================");
  Serial.println("Simulation initialised.");
}

void readInputs() {
  flameDetected = (digitalRead(PIN_FLAME) == LOW);

  mq2Value = analogRead(PIN_MQ2);
  mq7Value = analogRead(PIN_MQ7);

  TempAndHumidity data = dht.getTempAndHumidity();

  temperatureC = data.temperature;
  humidityPct = data.humidity;
}

void evaluateConditions() {
  bool temperatureWarning =
      !isnan(temperatureC) &&
      temperatureC > HIGH_TEMPERATURE_C;

  bool humidityWarning =
      !isnan(humidityPct) &&
      humidityPct < LOW_HUMIDITY_PCT;

  bool mq2Warning = mq2Value > MQ2_THRESHOLD;
  bool mq7Warning = mq7Value > MQ7_THRESHOLD;

  alarmActive =
      flameDetected ||
      temperatureWarning ||
      humidityWarning ||
      mq2Warning ||
      mq7Warning;
}

void updateOutputs() {
  if (alarmActive) {
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_RED, HIGH);
    digitalWrite(PIN_PUMP, HIGH);

    tone(PIN_BUZZER, 2000);
    actuator.write(120);
  } else {
    digitalWrite(PIN_GREEN, HIGH);
    digitalWrite(PIN_RED, LOW);
    digitalWrite(PIN_PUMP, LOW);

    noTone(PIN_BUZZER);
    actuator.write(90);
  }
}

void printReport() {
  Serial.println("----------------------------------");

  Serial.print("Flame event: ");
  Serial.println(flameDetected ? "DETECTED" : "NOT DETECTED");

  Serial.print("Temperature: ");
  if (isnan(temperatureC)) {
    Serial.println("Unavailable");
  } else {
    Serial.print(temperatureC, 1);
    Serial.println(" C");
  }

  Serial.print("Humidity: ");
  if (isnan(humidityPct)) {
    Serial.println("Unavailable");
  } else {
    Serial.print(humidityPct, 1);
    Serial.println(" %");
  }

  Serial.print("MQ-2 analogue input: ");
  Serial.println(mq2Value);

  Serial.print("MQ-7 analogue input: ");
  Serial.println(mq7Value);

  Serial.print("System status: ");
  Serial.println(alarmActive ? "ALARM" : "NORMAL");

  Serial.print("Pump command: ");
  Serial.println(alarmActive ? "ON" : "OFF");

  Serial.print("Servo position: ");
  Serial.println(alarmActive ? 120 : 90);
}

void loop() {
  readInputs();
  evaluateConditions();
  updateOutputs();

  if (millis() - lastReportTime >= REPORT_INTERVAL_MS) {
    lastReportTime = millis();
    printReport();
  }

  delay(100);
}
