# FireGuard Capsule — ESP32 Detection and Actuation Simulation

## 1. Purpose

This project provides an interactive virtual test bench for examining the FireGuard Capsule ESP32 detection and actuation logic.

The simulation allows users to change virtual sensor inputs and observe the controller's responses through status LEDs, a buzzer, a servo and a pump-command indicator.

## 2. Simulation Platform

- Simulator: Wokwi
- Controller: ESP32 DevKitC V4
- Programming language: Arduino C++
- Firmware: Simulation-specific ESP32 firmware

## 3. Virtual Components

| Component | Simulation role |
|---|---|
| ESP32 DevKitC V4 | Main controller |
| Pushbutton | Simulated flame-detection event |
| DHT22 | Adjustable temperature and humidity input; virtual substitute for the physical DHT11 |
| Potentiometer 1 | Simulated MQ-2 analogue input |
| Potentiometer 2 | Simulated MQ-7 analogue input |
| Servo | Simulated actuator movement |
| Red LED | Alarm status |
| Green LED | Normal status |
| Pump LED | Pump-control command indicator |
| Buzzer | Audible warning |

## 4. Pin Connections

| ESP32 GPIO | Virtual component |
|---:|---|
| GPIO 18 | Flame-event pushbutton |
| GPIO 19 | DHT22 data |
| GPIO 34 | MQ-2 analogue input |
| GPIO 35 | MQ-7 analogue input |
| GPIO 13 | Servo signal |
| GPIO 27 | Pump-command LED |
| GPIO 22 | Buzzer |
| GPIO 25 | Green status LED |
| GPIO 26 | Red alarm LED |

## 5. How to Run

1. Open the Wokwi simulation project.
2. Start the simulation.
3. Open the Serial Monitor.
4. Adjust the DHT22 temperature and humidity values.
5. Adjust both potentiometers to change the simulated analogue readings.
6. Press the flame-event pushbutton.
7. Observe the LEDs, buzzer, servo and Serial Monitor.
8. Record the actual response for each test scenario.

## 6. Test Scenarios

| Scenario | Input condition | Expected response |
|---|---|---|
| Normal conditions | All readings below configured thresholds; no flame event | Green status; pump command OFF |
| Flame event | Press the flame button | Alarm response; pump command ON |
| High temperature | Temperature above 35 °C | Alarm response |
| Low humidity | Humidity below 30% | Alarm response |
| High MQ-2 input | Analogue reading above 1800 | Alarm response |
| High MQ-7 input | Analogue reading above 1800 | Alarm response |
| Combined warning | More than one warning condition | Alarm response |

These are planned test scenarios. Results must only be marked as passed after the simulation has actually been run and observed.

## 7. Configured Thresholds

- High temperature: 35 °C
- Low humidity: 30%
- MQ-2 analogue threshold: 1800
- MQ-7 analogue threshold: 1800

These values are software test thresholds, not calibrated gas-concentration measurements.

## 8. Simulation Limitations

This virtual test bench does not establish:

- Actual MQ-2 or MQ-7 gas concentration or calibration.
- Physical flame-sensor detection range.
- Real pump pressure, water flow or spray distance.
- Battery runtime or actual electrical load performance.
- Physical servo torque or mechanical performance.
- GPS satellite reception or SIM900 cellular communication.
- Real-world wildfire detection or suppression performance.

The pump LED represents a control command only. Physical hardware requires separate testing.

## 9. Project Files

- `README.md` — project description and test procedure.
- `sketch.ino` — ESP32 simulation firmware.
- `diagram.json` — virtual circuit configuration.
- `libraries.txt` — required simulation libraries.

## 10. Verification and Evidence

Test evidence will include the simulation configuration, test inputs, observed outputs and relevant screenshots.

No test will be reported as successful until its result has been observed and documented.

---

**FireGuard Capsule — ESP32 Detection and Actuation Test Bench**
