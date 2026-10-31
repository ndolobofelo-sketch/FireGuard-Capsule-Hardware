# FireGuard Capsule — Engineering Simulations

## 1. Overview

This directory contains the engineering simulation programme for FireGuard Capsule, a wildfire early-detection and automatic suppression prototype developed in Botswana.

The simulations are intended to examine the behaviour of the control system, sensor inputs, electrical interfaces and suppression-control logic before and alongside physical testing.

The programme combines microcontroller simulation, electrical analysis, engineering calculations and documented validation. Each simulation must identify its assumptions, inputs, outputs, limitations and evidence.

## 2. Simulation Objectives

The simulation programme aims to:

- Examine ESP32 firmware behaviour under different simulated sensor conditions.
- Demonstrate how fire-related inputs affect system alerts and output signals.
- Examine the control logic for the pump and servo.
- Review electrical supply requirements and expected load behaviour.
- Support repeatable testing using documented input values and expected responses.
- Identify design issues that require further investigation through physical testing.

## 3. Simulation Programme

| Simulation                    | Main scope                                                | Primary evidence                               |
| ----------------------------- | --------------------------------------------------------- | ---------------------------------------------- |
| ESP32 Detection and Actuation | Sensor inputs, decision logic, alerts and output control  | Interactive circuit, firmware and test results |
| Electrical Power              | Supply voltage, load demand and power distribution        | Circuit analysis and calculations              |
| Sensor Response               | Input ranges, thresholds and detection behaviour          | Input/output test records                      |
| Pump Control                  | Pump command, switching logic and shutdown behaviour      | Control tests and documented assumptions       |
| System Response               | Integrated sequence from detection to suppression command | System-level test scenarios                    |

## 4. First Simulation: ESP32 Detection and Actuation

The first simulation is an interactive ESP32 test bench developed using Wokwi.

It includes:

- ESP32 DevKitC V4 virtual development board.
- DHT22 virtual temperature and humidity sensor used as a test substitute for the physical DHT11.
- Adjustable analog input controls representing the MQ-2 and MQ-7 sensor readings.
- A pushbutton representing a digital flame-detection event.
- Servo motor representing the directional actuator.
- LEDs representing system status and pump-control output.
- Buzzer representing the audible warning output.
- Serial Monitor for live readings, system decisions and test observations.

The simulation firmware uses the FireGuard control pin assignments where applicable. It is separate from the production firmware so that simulation-only inputs and test behaviour do not interfere with the physical device firmware.

## 5. Simulation Methodology

Each test follows this sequence:

1. Start the virtual ESP32.
2. Set or change one or more sensor inputs.
3. Observe the sensor readings in the Serial Monitor.
4. Observe the system status and output indicators.
5. Record whether the observed behaviour matches the expected response.
6. Repeat the test with different input conditions.

Test results must be recorded with the input values, expected behaviour, observed behaviour and pass/fail status. A test must not be marked as passed until it has actually been run and observed.

## 6. Engineering Limitations

A virtual simulation is not equivalent to physical validation.

The first Wokwi test bench demonstrates firmware logic and virtual input/output behaviour. It does not establish:

- Actual MQ-2 or MQ-7 gas concentration or calibration accuracy.
- Physical flame-sensor performance or detection range.
- Actual pump pressure, water flow rate or spray distance.
- Battery runtime under measured field loads.
- Physical servo torque or mechanical performance.
- GPS satellite reception or SIM900 cellular-network operation.
- Field performance under real wildfire conditions.

These areas require appropriate component datasheets, electrical measurements, controlled physical tests and field validation.

## 7. Evidence and Reproducibility

Each simulation should include:

- Source files and circuit configuration.
- Component and pin connection information.
- Test procedure and input conditions.
- Expected and observed results.
- Screenshots or other supporting evidence.
- Known limitations and any required follow-up work.

Simulation files should be kept under version control so that changes can be reviewed and repeated.

## 8. Development Status

The simulation programme is organised into the following engineering workstreams:

- ESP32 detection and actuation test bench.
- Electrical power analysis.
- Sensor response analysis.
- Pump-control analysis.
- Integrated system-response analysis.

The results and completion status of each workstream will be documented as the corresponding simulations and tests are executed.

## 9. External Simulation Platform

The first interactive test bench uses Wokwi.

- Wokwi ESP32 simulator:&#x20;

  [https://wokwi.com/esp32](https://wokwi.com/esp32)
- ESP32 simulation documentation:&#x20;

  [https://docs.wokwi.com/guides/esp32](https://docs.wokwi.com/guides/esp32)
- Diagram format documentation:&#x20;

  [https://docs.wokwi.com/diagram-format](https://docs.wokwi.com/diagram-format)

---

**FireGuard Capsule — Engineering Simulation Programme**

*Simulation supports engineering development; physical testing is required to validate real-world performance.*
