# FireGuard Capsule — Mechanical and Hydraulic Design

## 1. Design Overview

The FireGuard Capsule is a compact wildfire detection and automatic water-suppression prototype developed in Botswana.

Its mechanical design integrates a water-storage container, pumping system, reinforced water hose, spray nozzle and servo-controlled spray-direction mechanism.

The design aims to provide a compact assembly that can detect a fire threat and initiate a programmed water-suppression response.

## 2. Main Mechanical and Hydraulic Components

| Component | Function |
|---|---|
| Water tank | Stores water for suppression |
| 12 V DC diaphragm pump | Supplies pressurised water |
| Reinforced water hose | Transfers water from the tank to the nozzle |
| Adjustable spray nozzle | Directs water towards the target area |
| High-torque servo | Adjusts the nozzle direction |
| Mounting structure | Supports and positions the assembly |
| Battery system | Supplies electrical power to the system |

## 3. Design Requirements and Targets

The following are component-selection targets for the prototype. They are not confirmed performance results.

| Parameter | Design target |
|---|---|
| Water tank capacity | Approximately 5 litres |
| Pump operating voltage | 12 V DC |
| Pump flow rate | 5–6 L/min |
| Pump pressure | 70–100 PSI |
| Hose internal diameter | 1/2 inch |
| Nozzle connection | 1/2 BSP female |
| Battery type | 12.8 V LiFePO4 |
| Battery capacity | 20 Ah |
| Servo | 12 V high-torque servo; final compatibility to be verified |

## 4. Water Delivery Arrangement

The intended hydraulic arrangement is:

**Water tank → Pump → Reinforced hose → Adjustable nozzle**

The pump supplies water through the hose to the adjustable nozzle. The nozzle directs the water towards the selected target area.

The actual operating pressure, flow rate and spray distance must be established through physical testing.

## 5. Mechanical Actuation

The servo mechanism is intended to adjust the spray direction.

The ESP32 provides the control signal to the servo based on the programmed system response.

The final mechanical assembly must be evaluated for:

- Servo torque and load capacity.
- Nozzle movement range.
- Mounting strength.
- Vibration resistance.
- Water-hose flexibility.
- Mechanical stability during operation.

## 6. Electrical and Hydraulic Integration

The pump and servo must operate using suitable power supplies and correctly rated control circuits.

The pump must be controlled through an appropriate driver or switching circuit. The ESP32 must not supply pump current directly through its GPIO pins.

Electrical connections, current requirements, pressure ratings and hose compatibility must be verified before integrated operation.

## 7. Testing and Validation Requirements

The mechanical and hydraulic assembly will require testing to establish:

1. Water leakage and connection integrity.
2. Pump startup and shutdown.
3. Actual water flow rate.
4. Operating pressure.
5. Spray direction and coverage.
6. Servo movement under mechanical load.
7. Stability during repeated operation.
8. Battery performance under operating load.

Test results must be documented before performance claims are made.

## 8. Further Development

Future development will focus on improving the compactness of the assembly, protecting electrical components from water exposure, improving nozzle positioning and validating the system under controlled test conditions.

---

**FireGuard Capsule — Mechanical and Hydraulic Engineering**
