# FireGuard Capsule Hardware

**An ESP32-Based Wildfire Detection, Monitoring and Water-Suppression System**

## 1. Project Overview

FireGuard Capsule is a wildfire detection and response hardware system developed in Botswana. It uses an ESP32 microcontroller and multiple sensors to monitor environmental conditions, identify potential fire threats and support a faster response through monitoring, alerts and water-suppression equipment.

The project addresses the risks associated with delayed wildfire detection, particularly in remote areas where fires can spread before they are noticed and reported.

FireGuard Capsule is being developed to support the protection of communities, agricultural land, wildlife and critical infrastructure.

## 2. Key System Capabilities

The hardware and firmware are designed to support:

- **Fire detection:** Flame sensor monitoring to identify potential fire threats.
- **Environmental monitoring:** Temperature and humidity readings.
- **Gas and smoke monitoring:** MQ-2 and MQ-7 sensor readings.
- **Location tracking:** GPS information for identifying the capsule's location.
- **Communication:** GSM notifications and communication with the FireGuard backend.
- **Warning system:** Buzzer and RGB LED status indicators.
- **Water-suppression control:** Pump control through the connected control circuit.
- **Directional control:** Servo motor operation for the connected mechanism.

Actual operation depends on correct hardware connections, configuration and testing. The pump is disabled by default in the current firmware and requires the appropriate enable command.

## 3. Hardware Components

| Component | Purpose |
|---|---|
| ESP32 | Main microcontroller |
| Flame sensor | Detects flame signals |
| DHT11 | Measures temperature and humidity |
| MQ-2 | Monitors gas and smoke-related levels |
| MQ-7 | Monitors carbon monoxide-related levels |
| GPS module | Provides location information |
| SIM900 GSM module | Supports mobile network communication |
| DC water pump | Provides water-suppression flow |
| Servo motor | Controls the connected directional mechanism |
| Buzzer | Provides audible warnings |
| RGB LED | Displays system status |

## 4. Repository Structure

```text
FireGuard-Capsule-Hardware/
├── firmware/
│   └── FireGuard_Capsule.ino
├── hardware/
│   ├── component_list.md
│   ├── pin_connections.md
│   └── wiring_diagram.md
└── README.md
```

## 5. Firmware

The firmware is developed using the Arduino IDE for the ESP32 platform.

It manages sensor readings, fire detection logic, warning indicators, GPS data, GSM communication, water-pump control, servo operation and communication with the FireGuard backend.

**Main firmware file:**

`firmware/FireGuard_Capsule.ino`

## 6. Installation and Configuration

### Requirements

- Arduino IDE
- ESP32 board support package
- USB data cable
- ESP32 development board
- Required Arduino libraries used by the firmware
- Connected and correctly powered hardware components

### Setup Instructions

1. Install the Arduino IDE.
2. Install ESP32 board support in the Arduino IDE.
3. Install the libraries required by the firmware.
4. Open `firmware/FireGuard_Capsule.ino`.
5. Select the correct ESP32 board and COM port.
6. Connect the ESP32 to your computer.
7. Upload the firmware.
8. Open the Serial Monitor and follow the prompts to configure the private device settings.

The firmware uses ESP32 Preferences to store configured private settings on the device.

## 7. Hardware Documentation

The hardware documentation provides information about:

- Component specifications and quantities.
- ESP32 pin assignments.
- Hardware connection details.
- Wiring diagram.

Refer to the hardware documentation before assembling or modifying the system.

## 8. Safety and Security

- Never connect a water pump directly to an ESP32 GPIO pin. Use a suitable external driver or relay circuit.
- Ensure that the power supply is suitable for each component.
- Protect ESP32 inputs from voltages above their permitted limits.
- Verify wiring and power connections before powering the system.
- Keep Wi-Fi passwords, emergency contact numbers, device tokens and other private credentials out of public files.
- The current firmware uses an insecure HTTPS certificate configuration for prototype communication. This must be replaced with proper certificate verification before production deployment.

FireGuard Capsule is a developing prototype and should not be treated as a certified fire-protection system.

## 9. Development and Testing Status

FireGuard Capsule has a working hardware prototype that has undergone practical testing. Development and improvement are ongoing, with further integration, reliability testing and validation required before wider deployment.

## 10. Future Development

Planned development areas include:

- Improving detection reliability.
- Improving water-suppression performance.
- Strengthening hardware durability and power management.
- Expanding field testing.
- Improving communication and remote monitoring.

## 11. Project Information

**Project:** FireGuard Capsule  
**Category:** Wildfire Detection and Suppression Technology  
**Development Location:** Botswana  
**Platform:** ESP32  
**Firmware Environment:** Arduino IDE

## 12. License

A project license will be added once the appropriate open-source license has been selected.
