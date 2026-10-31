# FireGuard Capsule – Hardware Pin Connections

## 1. Purpose

This document describes the ESP32 GPIO assignments used by the FireGuard Capsule firmware. It identifies the signal connections between the ESP32 and the system's sensors, communication modules and control components.

## 2. ESP32 GPIO Pin Assignment Table

| Component | Module Pin | ESP32 Connection | Function |
|---|---|---|---|
| Flame Sensor | DO | GPIO 18 | Flame detection signal |
| DHT11 | DATA | GPIO 19 | Temperature and humidity data |
| MQ-2 | AO | GPIO 34 | Analogue gas/smoke-related reading |
| MQ-7 | AO | GPIO 35 | Analogue carbon monoxide-related reading |
| GPS Module | TX | GPIO 32 | GPS data received by ESP32 |
| GPS Module | RX | GPIO 33 | Data transmitted by ESP32 |
| SIM900 GSM | TX | GPIO 16 | GSM data received by ESP32 |
| SIM900 GSM | RX | GPIO 17 | Data transmitted by ESP32 |
| RGB LED | Red | GPIO 25 | Red status indicator |
| RGB LED | Green | GPIO 26 | Green status indicator |
| RGB LED | Blue | GPIO 14 | Blue status indicator |
| Buzzer Module | Signal | GPIO 22 | Audible warning control |
| Pump Driver/Relay | IN | GPIO 27 | Water pump control |
| Servo Motor | Signal | GPIO 13 | Servo position control |

## 3. Power and Ground Connections

Power and ground connections must follow the voltage and current requirements of each component.

- Connect module GND pins to a suitable common ground where required.
- Supply each module using its specified operating voltage.
- Use an appropriate external driver or relay circuit for the water pump.
- Provide a suitable external power supply for the servo motor and SIM900 module.
- Do not power high-current components directly from ESP32 GPIO pins.

**Important:** The exact power connections must be confirmed against the specifications of the actual modules being used.

## 4. Electrical Protection and Safety

- ESP32 GPIO pins operate at 3.3V logic levels and must not receive excessive voltage.
- Check the MQ-2 and MQ-7 analogue output voltage before connecting their AO pins to GPIO 34 and GPIO 35. Use suitable voltage protection where necessary.
- Never connect the water pump directly to an ESP32 GPIO pin.
- Ensure that the servo and SIM900 power supplies can provide sufficient current.
- Use appropriate current-limiting resistors for the RGB LED.
- Verify all connections before powering the prototype.

## 5. Firmware and Hardware Verification

The GPIO assignments in this document are based on the current FireGuard Capsule firmware configuration.

They describe the intended signal connections and do not independently confirm that all physical wiring has been assembled or tested.

Before deployment, verify the connections against the actual hardware modules and complete functional and electrical safety testing.

## 6. Project Status

FireGuard Capsule is a developing prototype. Hardware integration, testing and improvements are ongoing.
