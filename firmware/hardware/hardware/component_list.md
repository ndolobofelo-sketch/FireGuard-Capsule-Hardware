# FIREGUARD CAPSULE
## BILL OF MATERIALS (BOM)

### 1. Introduction and Purpose

This Bill of Materials (BOM) identifies the principal electronic, electrical and mechanical components required to develop and assemble one FireGuard Capsule prototype.

It provides an overview of the main components, their intended specifications, quantities and preliminary estimated costs. It also identifies additional materials and supporting equipment required to complete the hardware integration.

The document supports procurement planning, prototype development, cost estimation and future improvements to the system.

### 2. Main Components and Estimated Costs

The following table presents the ten principal components identified for the FireGuard Capsule prototype.

| No. | Component | Specifications and Technical Requirements | Quantity | Unit Price (BWP) | Total (BWP) |
|---:|---|---|---:|---:|---:|
| 1 | ESP32 Development Board | ESP32-WROOM-32 with Wi-Fi and Bluetooth connectivity | 1 | 188.00 | 188.00 |
| 2 | Flame Sensor | Infrared flame detection module | 1 | 50.00 | 50.00 |
| 3 | DHT11 Sensor | Temperature and relative humidity measurement | 1 | 45.00 | 45.00 |
| 4 | MQ-2 Sensor | Gas and smoke-related detection module | 1 | 55.00 | 55.00 |
| 5 | MQ-7 Sensor | Carbon monoxide detection module | 1 | 55.00 | 55.00 |
| 6 | GPS Module | NEO-6M GPS module with antenna | 1 | 133.50 | 133.50 |
| 7 | GSM Module | SIM900 GSM/GPRS communication module | 1 | 373.00 | 373.00 |
| 8 | Water Pump | 12V DC diaphragm pump; target flow rate of approximately 5–6 L/min and target pressure of 70–100 PSI, subject to model verification | 1 | 427.00 | 427.00 |
| 9 | High-Torque Servo Motor | Metal-gear servo; exact model, operating voltage and torque rating to be confirmed | 1 | 604.00 | 604.00 |
| 10 | Rechargeable Battery | 12.8V, 20Ah LiFePO4 battery, with compatible battery protection and charging equipment | 1 | 1,800.00 | 1,800.00 |
| | **TOTAL ESTIMATED COST – MAIN COMPONENTS** | | **10** | | **3,730.50** |

### 3. Additional Components and Supporting Materials

In addition to the ten principal components, the complete prototype requires supporting electrical, mechanical and installation materials. These components are necessary for safe power distribution, hardware integration, water delivery and physical protection.

The following items will be specified and costed as the final design and procurement requirements are confirmed.

| No. | Additional Component | Purpose and Technical Requirements | Quantity | Estimated Cost (BWP) |
|---:|---|---|---:|---:|
| 1 | Pump Driver or Relay Module | Controls the water pump and must support its operating and starting current | To be confirmed | Pending quotation |
| 2 | DC-DC Voltage Regulators | Provide suitable regulated voltages for electronic components | To be confirmed | Pending quotation |
| 3 | Fuses and Electrical Protection | Protect power circuits against excessive current and electrical faults | To be confirmed | Pending quotation |
| 4 | Electrical Wiring and Connectors | Provide reliable power and signal connections | To be confirmed | Pending quotation |
| 5 | Protective Enclosure | Protects electronic components against dust, moisture and environmental exposure | 1 | Pending quotation |
| 6 | Water Tank | Stores water for the suppression system; capacity to be determined by the design | 1 | Pending quotation |
| 7 | Reinforced Water Hose | Transfers water from the tank and pump to the spray assembly; pressure-rated for the selected pump | To be confirmed | Pending quotation |
| 8 | Adjustable Spray Nozzle | Directs water towards the intended suppression area and must be compatible with the selected fittings and pressure | 1 | Pending quotation |
| 9 | Solenoid Valve | Controls water flow where required by the final hydraulic design | To be confirmed | Pending quotation |
| 10 | Servo Mounting Bracket and Mechanical Supports | Secure the servo and support the directional spray mechanism | To be confirmed | Pending quotation |
| 11 | LED Resistors and Electronic Accessories | Support safe operation of the RGB indicator and associated circuits | To be confirmed | Pending quotation |
| 12 | LiFePO4 Battery Protection and Charger | Provides compatible battery protection and charging according to the battery manufacturer's specifications | To be confirmed | Pending quotation |

The quantities, specifications and costs of these additional items will be updated following final design verification and supplier quotations.

### 4. Electrical Power and Battery Requirements

The prototype uses a proposed 12.8V, 20Ah LiFePO4 rechargeable battery as its main power source.

The final power system will require:

- A compatible battery management and protection system.
- A charger specifically designed for the selected LiFePO4 battery.
- Suitable fuses and electrical protection.
- Regulated power supplies for components requiring different operating voltages.
- Adequate current capacity for the water pump, servo motor and communication modules.
- Proper power distribution, wiring and grounding.

The battery capacity and expected operating duration will be assessed against the total system power consumption and verified through practical testing.

### 5. Pricing and Procurement Information

All prices listed in Section 2 are expressed in Botswana Pula (BWP) and represent preliminary budget estimates.

The following procurement conditions apply:

- The listed prices are estimates and have not yet been confirmed through final supplier quotations.
- Supplier names, product references and quotation dates will be added once verified.
- Shipping, customs duties and other procurement charges are excluded.
- Component specifications, compatibility and availability will be checked before purchasing.
- Additional integration materials will be costed separately and included in the revised budget.

**Price Verification Record**

| Item | Information |
|---|---|
| Currency | Botswana Pula (BWP) |
| Pricing basis | Preliminary estimates |
| Supplier quotations | Pending verification |
| Price verification date | To be recorded |
| Shipping and customs | Excluded |

### 6. Estimated Prototype Cost Summary

| Cost Category | Estimated Cost (BWP) |
|---|---:|
| Ten principal components | **3,730.50** |
| Additional electrical and mechanical components | Pending quotations |
| Installation and assembly materials | Pending assessment |
| Shipping and customs | Excluded |
| **Final prototype cost** | **To be determined** |

The current estimated amount of **BWP 3,730.50** covers only the ten principal components listed in Section 2. It does not represent the complete cost of assembling and commissioning the prototype.

The final project cost will be established after the remaining components have been specified, sourced and priced.

### 7. Technical Verification and Quality Considerations

Before procurement and final hardware integration, the following technical requirements will be verified:

1. **Water pump:** Confirm the actual operating voltage, current, flow rate and pressure against the selected pump's datasheet.
2. **Servo motor:** Confirm the exact model, operating voltage, torque rating and mechanical compatibility with the directional mechanism.
3. **Battery system:** Verify battery protection, charger compatibility, power capacity and electrical safety.
4. **Power distribution:** Confirm that voltage regulators, drivers, fuses and wiring are suitable for the connected components.
5. **Sensor compatibility:** Verify sensor output voltages and protect the ESP32 inputs from excessive voltage.
6. **Water delivery system:** Confirm that the tank, hose, valve, fittings and spray nozzle are compatible with the pump.
7. **Environmental protection:** Assess the enclosure and mounting arrangements for the intended field operating conditions.

These checks will support reliable hardware integration and reduce the risk of electrical, mechanical and operational failures.

### 8. Development Status and Future Updates

FireGuard Capsule is under active prototype development. The main component requirements and preliminary cost estimates have been documented, while further procurement, integration and performance verification remain ongoing.

As development progresses, this BOM will be updated to include confirmed component models, supplier information, final quantities, verified prices and additional materials.

The final version will provide a more complete and accurate record of the resources required to assemble, test and improve the FireGuard Capsule system.

### 9. Project Information

**Project Name:** FireGuard Capsule  
**Project Category:** Wildfire Detection and Automatic Suppression Technology  
**Development Location:** Botswana  
**Main Hardware Platform:** ESP32  
**Document:** Bill of Materials (BOM)  
**Purpose:** Prototype development, procurement planning and cost estimation
