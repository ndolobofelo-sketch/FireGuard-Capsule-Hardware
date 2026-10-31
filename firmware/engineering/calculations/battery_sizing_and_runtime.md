# FIREGUARD CAPSULE

# Battery Sizing and Runtime Engineering Report

**Project:** FireGuard Capsule – Wildfire Detection and Automatic Suppression System
**Engineering Area:** Battery Selection, Energy Storage and Runtime Analysis
**Battery Chemistry:** Lithium Iron Phosphate (LiFePO4)
**Nominal Battery Voltage:** 12.8 V
**Rated Battery Capacity:** 20 Ah
**Nominal Stored Energy:** 256 Wh
**Document Status:** Engineering Design and Sizing Report

---

## 1. Executive Summary

This report evaluates the battery capacity and energy requirements of the FireGuard Capsule wildfire detection and automatic suppression system.

The system integrates environmental sensors, an ESP32 controller, GPS positioning, GSM communication, a water pump, a servo motor and warning indicators. These components have different electrical requirements and operating patterns. The battery must therefore supply sufficient energy for continuous monitoring while also supporting short-duration high-current activities such as GSM transmission, servo movement and water-pump operation.

The selected prototype energy source is a 12.8 V, 20 Ah LiFePO4 battery with a nominal energy capacity of 256 Wh.

The battery capacity is calculated as:

[
E=V\times C
]

[
E=12.8\times20
]

[
\boxed{E=256\text{ Wh}}
]

This provides the baseline energy capacity for the system's electrical design.

The report also evaluates usable energy under a stated 80% depth-of-discharge planning scenario and a 90% DC-DC conversion-efficiency assumption. These assumptions are used for engineering estimates and are not presented as measured characteristics of the installed battery or converters.

The final battery runtime depends on the complete system's average power demand, the pump's operating duty cycle, the battery's discharge limits and the efficiency of the power-distribution system.

## 2. Battery Selection and Technical Characteristics

The FireGuard Capsule prototype uses a 12.8 V, 20 Ah LiFePO4 battery.

| Parameter         |                                         Selected design specification |
| ----------------- | --------------------------------------------------------------------: |
| Battery chemistry |                                      Lithium Iron Phosphate (LiFePO4) |
| Nominal voltage   |                                                                12.8 V |
| Rated capacity    |                                                                 20 Ah |
| Nominal energy    |                                                                256 Wh |
| Main application  |                                              Portable DC power supply |
| System function   | Supplies detection, communication, control and suppression subsystems |

LiFePO4 chemistry is used in energy-storage applications because it provides a rechargeable battery platform with a relatively stable nominal voltage and a long-cycle-life potential when operated within manufacturer limits.

Battery safety and service life depend on the quality of the cells, battery management system (BMS), charging equipment, temperature and discharge conditions.

The battery's exact manufacturer and model determine its maximum continuous discharge current, short-duration peak current, permitted charging current, discharge cut-off voltage and operating-temperature limits. These ratings must be taken from the actual battery datasheet rather than inferred from its voltage and capacity alone.

## 3. Nominal Energy Capacity Calculation

The nominal energy capacity is calculated using:

[
E=V\times C
]

Where:

- (E) = nominal energy in watt-hours (Wh)
- (V) = nominal battery voltage in volts (V)
- (C) = rated battery capacity in ampere-hours (Ah)

Substituting the selected battery specifications:

[
E=12.8\times20
]

[
\boxed{E=256\text{ Wh}}
]

The battery therefore has a nominal stored energy capacity of **256 Wh**.

This value represents the rated nominal energy. It does not mean that all 256 Wh should be consumed during normal operation. The actual energy available to the system depends on the permitted depth of discharge, battery condition, temperature, discharge rate and conversion losses.

## 4. Usable Energy Calculation

Depth of discharge (DoD) describes the proportion of a battery's rated capacity that has been used.

For this engineering estimate, an 80% depth-of-discharge planning scenario is applied.

[
E\_{usable}=E\_{nominal}\times DoD
]

[
E\_{usable}=256\times0.80
]

[
\boxed{E\_{usable}=204.8\text{ Wh}}
]

Under this planning scenario, 204.8 Wh is available before accounting for DC-DC conversion losses.

The remaining 20% represents the capacity reserved outside the assumed operating discharge window. It is a design allowance, not a measurement of the battery's actual remaining capacity.

**Important:** The 80% DoD value is an engineering planning assumption. The actual permitted discharge depth must follow the selected battery manufacturer's specifications and BMS settings.

## 5. DC-DC Conversion Efficiency

The FireGuard Capsule includes electronic components operating at different voltages. These components require suitable voltage-regulation circuits between the main battery and individual loads.

Power conversion produces losses. Therefore, the energy delivered to regulated loads is lower than the energy drawn from the battery.

For this runtime estimate, a 90% DC-DC conversion-efficiency assumption is used.

[
E\_{delivered}=E\_{usable}\times\eta
]

Where:

- (E\_{delivered}) = estimated energy delivered to the regulated loads
- (E\_{usable}) = usable battery energy
- (\eta) = assumed conversion efficiency

[
E\_{delivered}=204.8\times0.90
]

[
\boxed{E\_{delivered}=184.32\text{ Wh}}
]

The estimated energy available to regulated loads is therefore **184.32 Wh** under the stated 80% DoD and 90% conversion-efficiency assumptions.

The 90% efficiency is a planning assumption, not a verified rating of the converters installed in the prototype. The final calculation must use the selected converter specifications and actual operating conditions.

## 6. Battery Runtime Analysis

Battery runtime is determined by dividing the usable energy available to the loads by the average power consumption.

[
t=\frac{E}{P\_{average}}
]

Where:

- (t) = estimated operating time in hours
- (E) = estimated energy delivered to the loads in Wh
- (P\_{average}) = average load power in watts

Using the estimated delivered energy:

[
t=\frac{184.32}{P\_{average}}
]

### 6.1 Illustrative runtime comparison

The following table shows how the estimated operating time changes at different average system power levels.

| Average Load Power | Estimated Runtime |
| -----------------: | ----------------: |
|                5 W |       36.86 hours |
|               10 W |       18.43 hours |
|               15 W |       12.29 hours |
|               20 W |        9.22 hours |
|               25 W |        7.37 hours |
|               30 W |        6.14 hours |

These are calculated scenarios, not measured FireGuard operating times. They show the relationship between average electrical demand and battery runtime.

For example, at an average load of 10 W:

[
t=\frac{184.32}{10}
]

[
\boxed{t=18.43\text{ hours}}
]

This means that a system averaging 10 W would have an estimated runtime of approximately 18.43 hours under the stated planning assumptions.

The actual FireGuard runtime is determined by its measured average power consumption during monitoring, communication and suppression operation.

## 7. Electrical Load and Battery Discharge Relationship

The battery supplies both continuous electrical loads and short-duration peak loads.

Continuous loads include:

- ESP32 processing and wireless communication.
- MQ-2 and MQ-7 sensor heaters.
- GPS receiver operation.
- Environmental sensor electronics.
- Indicator and control circuits.

Short-duration or variable loads include:

- SIM900 GSM transmission.
- Water-pump startup and operation.
- Servo motor movement.
- Alarm activation.

The average power consumption determines energy usage and runtime. The maximum simultaneous current determines whether the battery and power-distribution system can safely supply the connected equipment.

These are separate design requirements. A battery may have sufficient energy capacity for long operation but still be unsuitable if its discharge-current rating is below the system's peak demand.

## 8. Battery Discharge Current Calculation

The battery-side current for a given electrical power demand is estimated using:

[
I=\frac{P}{V}
]

Where:

- (I) = battery current in amperes
- (P) = battery-side power in watts
- (V) = battery voltage in volts

For example, at a 12.8 V nominal battery voltage and a 20 W battery-side load:

[
I=\frac{20}{12.8}
]

[
\boxed{I=1.56\text{ A}}
]

At a 30 W battery-side load:

[
I=\frac{30}{12.8}
]

[
\boxed{I=2.34\text{ A}}
]

These examples illustrate the relationship between power demand and battery current. They do not represent measured FireGuard loads.

For loads supplied through converters, the battery-side current must account for conversion efficiency:

[
I\_{battery}=\frac{P\_{load}}{V\_{battery}\times\eta}
]

The calculation must use the actual battery voltage under load and the converter efficiency at the relevant operating point.

## 9. Battery Discharge Capability and Peak-Load Requirements

The battery must support the maximum simultaneous electrical demand of the system.

The following loads are particularly important:

| Equipment           | Battery design consideration                           |
| ------------------- | ------------------------------------------------------ |
| ESP32               | Stable supply during processing and Wi-Fi transmission |
| MQ-2 and MQ-7       | Continuous heater energy consumption                   |
| GPS module          | Continuous receiver power                              |
| SIM900              | Short-duration transmission-current peaks              |
| Water pump          | Startup current and continuous running current         |
| Servo motor         | Movement current and stall current                     |
| Control electronics | Stable operation during switching and motor activity   |

The SIM900 module's documented transmission-burst current can reach 2 A at its module supply. This demand must be supported by its dedicated regulated power circuit.

The water pump and servo also require suitable power supplies and switching circuits. Their current demand must be included when evaluating the maximum simultaneous battery load.

The battery's maximum continuous and peak discharge ratings must be greater than the corresponding calculated system requirements, with suitable engineering margin.

**Battery selection principle:** The 20 Ah capacity determines nominal energy storage, while the battery's BMS and discharge-current ratings determine how much current can safely be delivered. Capacity alone does not establish the battery's suitability for the complete system.

## 10. Pump Duty Cycle and Energy Consumption

The water pump is an event-driven suppression load. Its energy consumption depends on how long it operates during a fire event and how frequently suppression is activated.

Pump energy is calculated using:

[
E\_{pump}=P\_{pump}\times t\_{pump}
]

Where:

- (E\_{pump}) = pump energy consumption in Wh
- (P\_{pump}) = pump electrical power in W
- (t\_{pump}) = total pump operating time in hours

For repeated operation:

[
E\_{pump,total}=P\_{pump}\times t\_{total}
]

The pump's operating time must be based on the actual suppression cycle and the verified pump power rating.

The pump must not be treated as a continuous load if it operates only during a suppression event. Its starting current, running current and total operating duration must nevertheless be included in the battery and power-distribution design.

## 11. Battery Charging Requirements

The battery must be charged using a charger specifically compatible with the selected 12.8 V LiFePO4 battery.

Charging voltage, maximum charging current, temperature limits and charging termination conditions must follow the battery manufacturer's instructions.

A compatible charging arrangement must provide:

1. The correct LiFePO4 charging profile.
2. Voltage regulation within the manufacturer's permitted range.
3. Current limiting appropriate to the battery rating.
4. Protection against overcharging and reverse polarity.
5. Safe electrical connections and suitable cable ratings.
6. Operation within the manufacturer's permitted charging-temperature range.

A charger intended for a different battery chemistry must not be used unless the battery manufacturer explicitly confirms compatibility.

## 12. Battery Management and Protection

The battery management system is an important part of the energy-storage design.

The BMS protects the battery by monitoring electrical and operating conditions according to its design.

The battery installation must provide:

- Overcharge protection.
- Over-discharge protection.
- Overcurrent protection.
- Short-circuit protection.
- Appropriate cell balancing.
- Temperature protection where supported by the selected battery.
- A correctly rated external fuse and suitable battery wiring.

The BMS current limits must be compatible with the combined electrical demand of the detection, communication and suppression systems.

The battery must be installed securely in a suitable enclosure, protected from water ingress, excessive heat, mechanical damage and accidental short circuits.

## 13. Engineering Design Decisions

The battery-sizing analysis establishes the following design basis:

| Design parameter                              | Engineering value or decision                   |
| --------------------------------------------- | ----------------------------------------------- |
| Battery chemistry                             | LiFePO4                                         |
| Nominal battery voltage                       | 12.8 V                                          |
| Rated battery capacity                        | 20 Ah                                           |
| Nominal stored energy                         | 256 Wh                                          |
| Planning depth of discharge                   | 80%                                             |
| Estimated usable battery energy               | 204.8 Wh                                        |
| Assumed DC-DC conversion efficiency           | 90%                                             |
| Estimated energy delivered to regulated loads | 184.32 Wh                                       |
| Runtime calculation method                    | Available energy divided by average load power  |
| Battery protection                            | BMS and appropriately rated external protection |
| Charging arrangement                          | LiFePO4-compatible charger                      |

The selected 20 Ah battery provides a defined energy-storage basis for the prototype. Its suitability for the complete system also depends on its discharge-current rating, BMS specification and the measured peak demand of the connected equipment.

## 14. Performance Evaluation Criteria

The battery and power system are evaluated against the following engineering criteria:

| Evaluation area      | Engineering acceptance criterion                                                           |
| -------------------- | ------------------------------------------------------------------------------------------ |
| Battery capacity     | Rated capacity and nominal voltage agree with the manufacturer's specification             |
| Usable energy        | Calculated within the permitted battery discharge limits                                   |
| Voltage stability    | Supply remains within the operating limits of connected components                         |
| Continuous discharge | Battery supports the normal operating current                                              |
| Peak discharge       | Battery and BMS support the maximum simultaneous current demand                            |
| Runtime              | Measured operating time is compared with calculated runtime                                |
| Charging             | Compatible charger operates within battery manufacturer limits                             |
| Protection           | Battery and electrical distribution have suitable overcurrent and short-circuit protection |
| Integrated operation | Detection and communication remain stable during suppression operation                     |

Runtime performance is evaluated using the complete prototype under representative monitoring, communication and suppression conditions. The recorded battery voltage, current, operating duration and pump activation periods provide the basis for comparing measured performance with the engineering estimates.

## 15. Conclusion

The FireGuard Capsule prototype uses a 12.8 V, 20 Ah LiFePO4 battery with a nominal stored energy capacity of 256 Wh.

Under an 80% depth-of-discharge planning scenario, the estimated usable energy is 204.8 Wh. Applying an assumed 90% DC-DC conversion efficiency gives an estimated 184.32 Wh available to regulated loads.

The runtime analysis demonstrates that operating time is directly affected by the average electrical power demand. The system's energy consumption is influenced by continuous sensor heating, controller operation, GPS reception and wireless communication, as well as the operating duration of the pump and servo.

The battery design therefore considers both energy capacity and discharge-current capability. Correct battery protection, charging control, voltage regulation and peak-load handling are essential to maintaining reliable operation of the FireGuard Capsule detection and automatic suppression system.

The calculated values provide a transparent engineering basis for battery sizing and runtime evaluation. Final operating-time and discharge-performance ratings are established from the manufacturer's specifications for the installed battery and measured performance of the integrated prototype.

## 16. Technical References

1. **LIONTRON.** *LiFePO4 LX 12.8 V 20 Ah Battery Datasheet.* Provides an example of manufacturer-specific ratings for a battery with the same nominal voltage and capacity, including discharge-current and charging specifications. This is a reference example and is not identified as the FireGuard installed battery.\

   [https://liontron.com/download/english/LI1220LX_EN.pdf](https://liontron.com/download/english/LI1220LX_EN.pdf)

2. **Victron Energy.** *Lithium Battery Smart – Technical Data.* Provides manufacturer information on LiFePO4 depth of discharge, cycle life, charging and discharge ratings. Its battery models have different capacities and ratings from the FireGuard prototype battery.\

   [https://www.victronenergy.com/media/pg/Lithium_Battery_Smart/en/technical-data.html](https://www.victronenergy.com/media/pg/Lithium_Battery_Smart/en/technical-data.html)

3. **Howell Energy.** *12.8 V 20 Ah LiFePO4 Battery Datasheet.* Provides another manufacturer example of a 12.8 V, 20 Ah battery and demonstrates why discharge-current limits must be obtained from the actual battery model.\

   [https://cdn.enfsolar.com/z/pp/2023/6/7cmzx2n03r1v6y/datasheet-of-12.8v-20ah-lifepo4-battery-HWE-4F20.pdf](https://cdn.enfsolar.com/z/pp/2023/6/7cmzx2n03r1v6y/datasheet-of-12.8v-20ah-lifepo4-battery-HWE-4F20.pdf)

---

**Document classification:** FireGuard Capsule – Battery Sizing and Energy Storage Engineering Documentation.
