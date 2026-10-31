# FIREGUARD CAPSULE

# Electrical Load and Power System Engineering Report

**Project:** FireGuard Capsule – Wildfire Detection and Automatic Suppression System
**Engineering Area:** Electrical and Power System Design
**Controller:** ESP32 Development Board
**Main Energy Source:** 12.8 V, 20 Ah LiFePO4 Battery
**Document Status:** Engineering Design and Calculation Report
**Currency:** SI units

---

## 1. Executive Summary

This report presents the electrical power design basis for the FireGuard Capsule prototype. It evaluates the electrical requirements of the detection, communication, control and suppression subsystems and establishes the calculations required for reliable battery-powered operation.

The system uses an ESP32 controller to process information from environmental and fire-detection sensors, communicate through Wi-Fi and GSM, receive GPS information, and control the water-suppression mechanism.

The selected energy source is a 12.8 V, 20 Ah lithium iron phosphate (LiFePO4) battery. Its nominal stored energy is:

[
E=V\times C
]

[
E=12.8\times20=\boxed{256\text{ Wh}}
]

The design uses separate regulated power supplies for components that require different operating voltages. High-current equipment, including the pump, servo and GSM module, must have appropriately rated power circuits rather than being supplied directly from the ESP32.

The calculations in this report distinguish manufacturer reference specifications from confirmed prototype measurements. This ensures that the engineering decisions remain traceable and technically defensible.

## 2. System Description and Electrical Architecture

The FireGuard Capsule electrical system consists of four functional groups:

1. **Detection subsystem:** Flame sensor, DHT11, MQ-2 and MQ-7.
2. **Processing subsystem:** ESP32 development board.
3. **Communication subsystem:** GPS module and SIM900 GSM/GPRS module, with Wi-Fi provided by the ESP32.
4. **Suppression and indication subsystem:** DC water pump, servo motor, buzzer and RGB indicator.

The battery supplies the main electrical energy. DC-DC converters provide the required regulated voltage levels, while suitable motor drivers and switching circuits control the pump and servo.

### 2.1 Electrical design arrangement

| Power system           | Main equipment                   | Design requirement                                      |
| ---------------------- | -------------------------------- | ------------------------------------------------------- |
| Main battery supply    | 12.8 V, 20 Ah LiFePO4            | Main energy source                                      |
| Regulated logic supply | ESP32 and compatible electronics | Stable regulated voltage                                |
| Sensor supply          | Flame, DHT11, MQ-2 and MQ-7      | Voltage matched to each module                          |
| GSM supply             | SIM900                           | Dedicated supply capable of handling transmission peaks |
| Motor supply           | Pump and servo                   | Appropriately rated motor power circuits                |

The final voltage and current ratings of the regulators and switching devices are determined by the actual component specifications and their combined operating conditions.

## 3. Component Electrical Specifications

The following reference values are taken from manufacturer documentation or technical specifications for the identified component families.

| Component                |               Reference operating voltage |                                                           Reference current or power | Engineering consideration                           |
| ------------------------ | ----------------------------------------: | -----------------------------------------------------------------------------------: | --------------------------------------------------- |
| ESP32-WROOM-32           |                                     3.3 V | Wi-Fi transmission typically approximately 240 mA in the ESP32 series reference data | Radio activity affects current demand               |
| Flame sensor module      |                         Depends on module |                                                                      Module-specific | Confirm actual board specification                  |
| DHT11                    | 3.5–5.5 V in the referenced documentation |                                             0.3 mA during measurement; 60 µA standby | Confirm the exact sensor revision and module        |
| MQ-2 sensing element     |                              5.0 V heater |                                                      Up to 950 mW heater consumption | Heater is a continuous power load while operating   |
| MQ-7 sensing element     |                    5.0 V heater reference |                                                      Up to 900 mW heater consumption | Heater voltage-cycle requirements must be respected |
| NEO-6M GPS family        |        Module-specific supply arrangement |                                               Depends on receiver and breakout board | Confirm exact GPS board                             |
| SIM900                   |       3.4–4.5 V at the module VBAT supply |                                                 Up to 2 A during transmission bursts | Requires a stable, high-current supply              |
| Water pump               |                        12 V system target |                                                  Exact current depends on pump model | Use pump datasheet and startup measurements         |
| Servo motor              |                           Model-dependent |                                              Depends on movement and mechanical load | Stall current and torque must be considered         |
| Buzzer and RGB indicator |                          Module-dependent |                                                         Depends on actual components | Include operating current and LED resistors         |

**Specification note:** The values above are reference values, not a claim that every installed breakout board has identical electrical characteristics. The actual module's regulator, indicator LEDs, driver circuits and other onboard components can change its total current consumption.

## 4. Electrical Load Calculations

### 4.1 Battery nominal energy

The selected battery has the following stated design specifications:

- Nominal voltage: 12.8 V
- Rated capacity: 20 Ah
- Battery chemistry: LiFePO4

The nominal energy is calculated as:

[
E=V\times C
]

[
E=12.8\times20
]

[
\boxed{E=256\text{ Wh}}
]

Therefore, the battery has a nominal stored energy rating of **256 Wh**, based on its stated voltage and capacity.

This is the rated nominal energy, not a guarantee that the entire amount is available to the connected equipment. Actual usable energy depends on the battery manufacturer's discharge limits, battery management system, temperature, age, load and conversion losses.

### 4.2 ESP32 reference power

The ESP32 series documentation gives a typical Wi-Fi transmission current of approximately 240 mA under a specified RF test condition.

Using the 3.3 V operating supply:

[
P=V\times I
]

[
P=3.3\times0.240
]

[
\boxed{P=0.792\text{ W}}
]

This is a reference calculation for the stated transmission condition. It is not a measured average power value for the complete FireGuard controller board.

### 4.3 MQ-2 heater power

The MQ-2 technical documentation specifies a maximum heater consumption of approximately 950 mW under its stated standard test conditions.

[
I=\frac{P}{V}
]

[
I=\frac{0.950}{5.0}
]

[
\boxed{I=0.190\text{ A}}
]

The corresponding heater current is approximately **190 mA at 5 V**.

This calculation covers the sensing element heater. The complete MQ-2 breakout board may consume additional current through its signal-conditioning circuit and indicator components.

### 4.4 MQ-7 heater power

The referenced MQ-7 technical specification gives a maximum heater consumption of approximately 900 mW.

Using the 5 V heater reference:

[
I=\frac{P}{V}
]

[
I=\frac{0.900}{5.0}
]

[
\boxed{I=0.180\text{ A}}
]

The corresponding reference heater current is approximately **180 mA at 5 V**.

The MQ-7 requires the specified heater operating cycle for correct sensing. The selected module's circuit must be checked to establish whether it implements the required heater control or whether an external heater-control circuit is necessary.

### 4.5 SIM900 communication power

The SIM900 hardware documentation specifies a supply voltage of approximately 3.4–4.5 V and a transmission-burst current that can reach 2 A.

Using the 4.0 V nominal reference supply:

[
P=V\times I
]

[
P=4.0\times2.0
]

[
\boxed{P=8.0\text{ W}}
]

The GSM supply must therefore support transmission peaks of approximately **8 W at the module supply under this reference condition**.

The SIM900 must not be connected directly to the 12.8 V battery. A suitable regulated supply must provide the correct module voltage, sufficient peak current and appropriate local energy storage.

### 4.6 DHT11 reference power

The referenced DHT11 technical documentation gives a measurement current of approximately 0.3 mA.

At a 5 V reference supply:

[
P=5.0\times0.0003
]

[
\boxed{P=0.0015\text{ W}}
]

The reference measurement power is approximately **1.5 mW**. The actual breakout-board consumption must be confirmed separately.

## 5. Battery-Side Power Calculations

Components operating at 3.3 V, 5 V or approximately 4 V cannot be added together using their current values alone. Their power must first be calculated and then converted to equivalent battery-side current.

The battery-side current for a regulated load is:

[
I\_{battery}=\frac{P\_{load}}{V\_{battery}\times\eta}
]

Where:

- (I\_{battery}) = battery-side current in amperes
- (P\_{load}) = output power required by the load in watts
- (V\_{battery}) = battery voltage in volts
- (\eta) = converter efficiency as a decimal

For illustration, using a 90% converter-efficiency assumption and a 12.8 V battery:

[
I\_{battery}=\frac{P\_{load}}{12.8\times0.90}
]

The 90% value is a calculation assumption, not a measured efficiency or a confirmed specification for the installed converters. Final calculations must use the selected converter's verified efficiency at the actual operating load.

## 6. Continuous and Peak Electrical Loads

Electrical equipment does not always draw the same current throughout operation. The design therefore distinguishes continuous demand from short-duration peak demand.

### 6.1 Continuous loads

The principal continuous or regularly operating loads include:

- ESP32 processing and wireless communication.
- MQ-2 and MQ-7 sensor heaters.
- GPS receiver operation.
- Environmental sensor electronics.
- Indicator and control electronics.

The MQ sensor heaters are particularly important because their power consumption continues while the sensors are operating, even when the system is not actively suppressing a fire.

### 6.2 Peak loads

The design must also account for:

- SIM900 transmission bursts.
- Water pump startup current.
- Servo motor movement and stall current.
- Simultaneous operation of communication and suppression equipment.

The power supply and distribution system must support the highest credible simultaneous load without causing excessive voltage drop, controller resets or interruption of fire-detection functions.

## 7. Battery Runtime Calculation Method

Battery runtime depends on the total average power drawn from the battery.

The basic calculation is:

[
t=\frac{E}{P}
]

Where:

- (t) = operating time in hours
- (E) = available battery energy in watt-hours
- (P) = average battery-side power in watts

For the selected battery:

[
t=\frac{256}{P\_{average}}
]

This equation provides the nominal runtime relationship. The final runtime depends on the actual average load, usable battery capacity, converter efficiency and battery operating conditions.

The pump and servo must be included according to their actual duty cycles. A pump that operates only during a suppression event does not consume the same energy as a continuously running pump.

A reliable runtime figure must therefore be based on the measured operating profile of the complete system rather than the sum of component maximum ratings alone.

## 8. Power Distribution and Electrical Protection

The electrical architecture must maintain stable operation of the controller and sensors while supplying the higher-current communication and suppression equipment.

The following design requirements apply:

1. The 12.8 V battery supplies the main power distribution system.
2. Regulated DC-DC converters supply the voltage required by each electronic subsystem.
3. The SIM900 receives a dedicated supply that meets its voltage and transmission-current requirements.
4. The pump is controlled through a suitably rated driver, relay or switching circuit.
5. The servo receives a suitable external supply rather than drawing motor current directly from an ESP32 GPIO.
6. The ESP32 and connected signal circuits receive correctly regulated logic power.
7. Fuses and appropriately rated conductors protect the battery and individual power branches.
8. All connected modules share a suitable common reference ground where required by their signal interfaces.
9. Inductive loads receive suitable suppression and transient protection.
10. The battery is charged and protected according to the selected manufacturer's specifications.

### 8.1 ESP32 input protection

The ESP32-WROOM-32 recommended supply voltage is 3.0–3.6 V. Its GPIO inputs must not be exposed to voltages beyond their permitted electrical limits.

The MQ sensor modules must therefore be checked carefully. Their analog outputs may exceed the ESP32 ADC input range depending on the module supply and output circuit. A suitable voltage-divider or signal-conditioning circuit must be used where required.

### 8.2 Battery protection

The battery system requires appropriate overcurrent protection, short-circuit protection and charging control. The selected battery's built-in battery management system and permitted discharge current must be checked against the combined pump, servo, communication and electronics loads.

## 9. Engineering Design Decisions

The electrical design establishes the following decisions:

| Design area           | Engineering decision                                                                                |
| --------------------- | --------------------------------------------------------------------------------------------------- |
| Main energy source    | 12.8 V, 20 Ah LiFePO4 battery                                                                       |
| Nominal stored energy | 256 Wh                                                                                              |
| Controller supply     | Regulated supply suitable for ESP32 operating requirements                                          |
| Sensor power          | Regulated supply matched to the individual sensor modules                                           |
| GSM power             | Dedicated regulated supply capable of supporting up to 2 A transmission bursts at the SIM900 module |
| Pump control          | External switching or motor-driver circuit                                                          |
| Servo control         | External motor supply and suitable control circuit                                                  |
| Electrical protection | Fuses, suitable conductors and voltage protection                                                   |
| Battery runtime       | Calculated from actual average system power and usable battery energy                               |

These decisions provide the electrical design basis for the integration of the detection, communication and automatic suppression subsystems.

## 10. Electrical Verification and Performance Evaluation

The electrical system is evaluated against the following engineering criteria:

| Verification area  | Evaluation criterion                                                              |
| ------------------ | --------------------------------------------------------------------------------- |
| Battery output     | Voltage remains within the battery and connected equipment limits                 |
| ESP32 supply       | Stable regulated voltage during normal operation and wireless transmission        |
| Sensor supply      | Each sensor receives its specified operating voltage                              |
| GSM supply         | No unacceptable voltage drop during transmission bursts                           |
| Pump supply        | Driver, wiring and battery support the pump's starting and running requirements   |
| Servo supply       | Adequate voltage and current under the actual mechanical load                     |
| System integration | Controller and sensor operation remain stable during simultaneous load conditions |
| Protection         | Fuses, wiring and switching components are correctly rated                        |

The calculations are supported by manufacturer specifications and engineering equations. The complete prototype's final load and runtime ratings are established from the exact installed component models and measurements taken during integrated operation.

## 11. Conclusion

The FireGuard Capsule power design is based on a 12.8 V, 20 Ah LiFePO4 battery with a nominal energy capacity of 256 Wh.

The electrical analysis demonstrates why the system requires separate regulated supplies for its electronic, communication and motor-driven subsystems. It also identifies the importance of sensor-heater consumption, GSM transmission peaks, pump startup current and servo motor loading.

The power architecture is designed to maintain stable detection and communication while supporting automatic water-suppression operation. The use of correctly rated converters, switching devices, conductors and protective components forms an essential part of the system's electrical reliability.

The final electrical performance and operating-time specifications are based on the complete assembled system's verified component ratings and measured operating conditions.

## 12. Technical References

1. **Espressif Systems.** *ESP32 Series Datasheet.* Electrical characteristics and RF current-consumption specifications.\

   [https://documentation.espressif.com/esp32_datasheet_en.html](https://documentation.espressif.com/esp32_datasheet_en.html)

2. **SIMCom.** *SIM900 Hardware Design.* Power-supply voltage, transmission-burst current and power-supply design requirements.\

   [https://datasheet.octopart.com/SIM900-Simcom-datasheet-17594122.pdf](https://datasheet.octopart.com/SIM900-Simcom-datasheet-17594122.pdf)

3. **SIMCom.** *SIM900 Reference Design Guide.* Power-supply design and peak-current considerations.\

   [https://simcom.ee/documents/SIM900/AN_SIM900%20Reference%20Design%20Guide_V1.02.pdf](https://simcom.ee/documents/SIM900/AN_SIM900%20Reference%20Design%20Guide_V1.02.pdf)

4. **Winsen Electronics.** *MQ-2 Semiconductor Sensor for Flammable Gas.* Heater voltage and power-consumption specifications.\

   [https://www.rlocman.ru/datasheet/pdf.html?di=181583&p=2](https://www.rlocman.ru/datasheet/pdf.html?di=181583\&p=2)

5. **Aosong Electronics.** *DHT11 Temperature and Humidity Module.* Electrical characteristics and supply-current information.\

   [https://osoyoo.com/wp-content/uploads/2017/03/DHT11.pdf](https://osoyoo.com/wp-content/uploads/2017/03/DHT11.pdf)

6. **MQ-7 Technical Specifications.** Heater voltage, resistance and power-consumption reference. The exact installed module must be checked against its manufacturer's documentation.

---

**Document classification:** FireGuard Capsule – Electrical Engineering Design Documentation.
