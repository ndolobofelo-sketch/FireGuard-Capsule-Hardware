# FireGuard Capsule — Testing and Validation Report

## 1. Introduction

This report documents the testing and validation approach for the FireGuard Capsule wildfire detection and automatic suppression system.

The purpose is to evaluate the operation of the electronic hardware, embedded firmware, detection inputs, control outputs and software communication interfaces.

Testing evidence will be recorded to support technical review, identify faults and guide further development.

## 2. System Components Under Evaluation

| System area | Components or functions |
|---|---|
| Main controller | ESP32 development board |
| Environmental monitoring | DHT11 temperature and humidity sensor |
| Fire detection | Flame sensor |
| Gas and smoke monitoring | MQ-2 and MQ-7 sensors |
| Communication | Wi-Fi and SIM900 GSM module |
| Location monitoring | GPS module |
| Suppression control | Water pump and driver circuit |
| Mechanical actuation | Servo motor and spray mechanism |
| Software | Mobile application and backend |
| Virtual testing | Wokwi ESP32 simulation |

## 3. Testing Objectives

The testing programme aims to:

1. Verify that sensor inputs are received by the ESP32.
2. Examine the firmware response to configured detection thresholds.
3. Check alarm indicators and warning outputs.
4. Verify the pump-control and servo-control commands.
5. Examine communication between the device, backend and mobile application.
6. Identify electrical, mechanical and software limitations.
7. Record evidence before declaring a test successful.

## 4. Hardware Testing

Hardware testing will examine the physical components and their connections.

| Test area | Verification activity | Evidence required |
|---|---|---|
| ESP32 controller | Check power, startup and GPIO operation | Startup and test records |
| DHT11 | Check temperature and humidity readings | Sensor readings |
| Flame sensor | Check digital detection response | Detection observations |
| MQ-2 | Examine analogue sensor readings | Recorded ADC values |
| MQ-7 | Examine analogue sensor readings | Recorded ADC values |
| GPS | Check location data reception | Valid GPS records |
| SIM900 | Check GSM communication and SMS operation | Communication records |
| Pump | Check switching and water delivery | Operating observations |
| Servo | Check movement and spray-direction control | Movement observations |

## 5. Firmware Testing

Firmware testing will examine the ESP32 control logic, sensor processing and output responses.

Configured detection thresholds include:

- High temperature: 35 °C.
- Low humidity: 30%.
- MQ-2 analogue threshold: 1800.
- MQ-7 analogue threshold: 1800.

The tests will examine whether the controller processes sensor inputs and activates the programmed warning and control responses.

## 6. Automatic Suppression Testing

The suppression system will be evaluated through the following activities:

1. Verify the pump-driver control signal.
2. Check pump activation following the programmed detection conditions.
3. Observe servo movement and spray-direction adjustment.
4. Inspect water delivery and nozzle operation.
5. Check system shutdown when the programmed conditions return to normal.

Actual water pressure, flow rate and spray distance must be measured during physical testing.

## 7. Software and Communication Testing

The software testing programme will examine:

- ESP32 communication with the backend.
- Transmission of device telemetry.
- Mobile application connection to the backend.
- Display of available sensor readings and system status.
- Delivery and presentation of warning notifications.

Evidence will include relevant application screenshots, backend records and communication test observations.

## 8. Simulation Testing

The ESP32 detection and actuation simulation is maintained under:

`engineering/simulations/esp32_detection_and_actuation/`

The virtual test bench is intended to examine sensor-input processing, alarm logic, servo commands and pump-control indicators.

Simulation results will be recorded separately from physical hardware results because virtual components do not establish real-world sensor accuracy or suppression performance.

## 9. Test Results and Evidence Register

The following register will be updated as testing is performed.

| Test ID | Test description | Status | Evidence |
|---|---|---|---|
| FG-001 | ESP32 startup and controller operation | Pending documentation | To be recorded |
| FG-002 | Temperature and humidity sensor testing | Pending documentation | To be recorded |
| FG-003 | Flame detection testing | Pending documentation | To be recorded |
| FG-004 | MQ-2 and MQ-7 input testing | Pending documentation | To be recorded |
| FG-005 | Alarm and warning output testing | Pending documentation | To be recorded |
| FG-006 | Pump-driver and water-delivery testing | Pending documentation | To be recorded |
| FG-007 | Servo actuation testing | Pending documentation | To be recorded |
| FG-008 | GPS and GSM communication testing | Pending documentation | To be recorded |
| FG-009 | Backend and mobile application testing | Pending documentation | To be recorded |
| FG-010 | Integrated system testing | Pending documentation | To be recorded |

**Status definitions:**

- Pending documentation: Evidence has not yet been entered into this report.
- In progress: Testing is currently being conducted.
- Passed: The test has been performed and the acceptance criteria have been met.
- Failed: The test has been performed and the acceptance criteria have not been met.
- Blocked: Testing cannot proceed because of an identified issue.

A test must not be marked as passed without supporting evidence.

## 10. Limitations and Further Validation

Further testing is required to establish:

- Sensor accuracy and detection reliability under different environmental conditions.
- Actual pump pressure and water flow performance.
- Spray coverage and suppression effectiveness.
- Battery runtime under operating conditions.
- Mechanical durability and actuator performance.
- Communication reliability in remote locations.
- Integrated system performance during controlled field trials.

The prototype must undergo appropriate controlled testing before any claims of operational wildfire suppression effectiveness are made.

## 11. Conclusion

This report establishes a structured approach for evaluating the FireGuard Capsule prototype.

Testing evidence will be added as hardware, firmware, simulation and software verification activities are completed. The resulting records will support engineering improvements and provide a traceable basis for further prototype validation.

---

**FireGuard Capsule — Engineering Testing and Validation**
