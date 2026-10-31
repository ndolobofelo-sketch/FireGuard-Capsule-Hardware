# Pump and Hydraulic Sizing Engineering Report

## 1. Purpose

This report defines the hydraulic design requirements for the FireGuard Capsule water-suppression system. It explains the pump selection requirements, operating pressure, water flow, hose and nozzle considerations, estimated water delivery duration, and the tests required to verify system performance.

The objective is to deliver water reliably when the system activates its suppression mechanism.

## 2. Hydraulic System Description

The proposed hydraulic system consists of:

- A water storage tank.
- A 12V DC diaphragm water pump.
- Reinforced water-delivery hose.
- An adjustable spray nozzle.
- Suitable fittings and connectors.
- A pump driver or relay circuit controlled by the ESP32.
- Appropriate pressure protection and water-resistant connections.

The pump draws water from the storage tank and delivers it through the hose to the spray nozzle. The ESP32 controls the pump through a suitable switching device. The pump must not be connected directly to an ESP32 GPIO pin.

## 3. Pump Design Requirements

The current component plan identifies the following pump design targets:

| Parameter | Design target |
|---|---:|
| Pump type | 12V DC diaphragm pump |
| Nominal supply voltage | 12V DC |
| Target flow rate | 5–6 L/min |
| Target pressure range | 70–100 PSI |
| Intended fluid | Water |
| Application | Automatic water spraying |

**Important:** These values are design targets, not verified specifications of the pump currently installed in the prototype. The exact pump manufacturer, model, pressure-flow curve, maximum current and duty-cycle rating must be confirmed from its datasheet.

The pump must be selected using its flow rate at the required operating pressure, not its maximum free-flow rating alone.

## 4. Pressure and Flow Relationship

Pump flow rate normally changes as the discharge pressure increases. The actual relationship depends on the pump design and its performance curve.

For hydraulic design, the selected pump must provide sufficient flow at the pressure required by the nozzle and the delivery system.

The following conversions apply to the design targets:

| Pressure | Equivalent pressure |
|---|---:|
| 70 PSI | Approximately 4.83 bar |
| 100 PSI | Approximately 6.89 bar |

The system must not be assumed to deliver 5–6 L/min at 70–100 PSI until the manufacturer's performance curve or a controlled test confirms the operating point.

## 5. Hydraulic Power Calculation

Hydraulic power is the power transferred to the water by the pump.

The calculation is:

\[
P_h = \Delta p \times Q
\]

Where:

- \(P_h\) = hydraulic power in watts.
- \(\Delta p\) = pressure difference in pascals.
- \(Q\) = flow rate in cubic metres per second.

### 5.1 Flow-rate conversion

\[
5\ L/min = \frac{5}{60,000}
= 0.0000833\ m^3/s
\]

\[
6\ L/min = \frac{6}{60,000}
= 0.0001000\ m^3/s
\]

### 5.2 Illustrative hydraulic power calculations

At 70 PSI and 5 L/min:

\[
P_h = 482,633 \times 0.0000833
\]

\[
P_h \approx 40.2\ W
\]

At 100 PSI and 6 L/min:

\[
P_h = 689,476 \times 0.0001000
\]

\[
P_h \approx 68.9\ W
\]

These are illustrative calculations using the design-target values. They do not establish that the selected pump can deliver those pressure and flow combinations simultaneously.

The electrical input power will be higher than hydraulic output power because of pump and motor losses. Actual electrical consumption must be obtained from the pump datasheet or measured during testing.

## 6. Water Tank Capacity and Spray Duration

The prototype design uses a compact water storage arrangement with a target capacity of approximately 5 litres.

The theoretical continuous delivery duration is calculated using:

\[
t = \frac{V}{Q}
\]

Where:

- \(t\) = delivery duration in minutes.
- \(V\) = available water volume in litres.
- \(Q\) = actual water flow rate in litres per minute.

For a 5-litre tank at 5 L/min:

\[
t = \frac{5}{5} = 1\ minute
\]

For a 5-litre tank at 6 L/min:

\[
t = \frac{5}{6} = 0.833\ minutes
\]

This is approximately 50 seconds.

Therefore, the theoretical continuous delivery duration is approximately 50–60 seconds at the target flow rates.

Actual spray duration may be shorter because of unusable tank volume, pump priming, leakage, pressure variation and other hydraulic losses. The system's real operating duration must be measured during testing.

## 7. Hose and Pipe Considerations

The proposed delivery hose is a reinforced hose with a target internal diameter of approximately 1/2 inch.

The final hose selection must consider:

- Compatibility with the pump outlet and nozzle connections.
- Maximum working pressure.
- Internal diameter and total hose length.
- Resistance to kinking and leakage.
- Compatibility with water and the expected operating environment.
- Secure fittings and clamps.

A smaller internal diameter, long hose, sharp bends and restrictive fittings can increase hydraulic losses and reduce the flow available at the nozzle.

The hose pressure rating must be suitable for the maximum possible system pressure. It must not be selected using the normal operating pressure alone.

## 8. Spray Nozzle Requirements

The proposed nozzle is an adjustable stainless-steel spray nozzle with a target 1/2-inch BSP female connection.

The final nozzle must be compatible with the hose fittings and the pump's available operating pressure.

The following characteristics must be evaluated:

- Spray pattern and coverage.
- Nozzle orifice size.
- Water flow at operating pressure.
- Spray distance under controlled conditions.
- Resistance to blockage.
- Leakage and connection security.

The nozzle opening strongly influences the operating pressure and flow rate. A nozzle that is too restrictive can increase back-pressure and reduce water delivery. A nozzle that is too large may produce a high flow rate but insufficient spray pressure.

The nozzle must therefore be selected together with the pump, rather than as an independent component.

## 9. Hydraulic Losses and System Performance

Pressure losses can occur throughout the hydraulic system due to friction and restrictions.

Important sources include:

- Hose-wall friction.
- Bends and elbows.
- Connectors and fittings.
- Valves and filters.
- The nozzle opening.
- Differences in elevation between the tank, pump and nozzle.

The Darcy–Weisbach equation can be used to estimate friction-related pressure losses in a pipe or hose:

\[
\Delta p = f \frac{L}{D}
\left(\frac{\rho v^2}{2}\right)
\]

Where:

- \(\Delta p\) = pressure loss in pascals.
- \(f\) = Darcy friction factor.
- \(L\) = hose length in metres.
- \(D\) = internal hose diameter in metres.
- \(\rho\) = water density in kg/m³.
- \(v\) = average water velocity in m/s.

A numerical hose-loss calculation requires the actual hose length, internal diameter, flow rate and relevant friction factor. These details must be measured or confirmed before a reliable pressure-loss result can be reported.

## 10. Pump Control and Electrical Integration

The ESP32 controls the pump through an appropriately rated relay or motor-driver circuit.

The electrical integration must provide:

- A suitable 12V power supply.
- A switching device rated for the pump's actual operating and starting current.
- Correctly sized wiring and connectors.
- Appropriate fuse protection.
- Protection against electrical interference and motor switching transients.
- A common reference ground where required by the control circuit.

The pump must be switched off when suppression is not required. The control system should also include a safe shutdown method and a means of stopping water delivery if a fault occurs.

The final fuse, wiring and driver ratings must be based on the selected pump's verified current requirements.

## 11. Hydraulic Safety Requirements

The hydraulic system must be designed and tested with the following safety considerations:

1. Use hoses, fittings and nozzles rated for the maximum possible system pressure.
2. Provide suitable pressure protection in accordance with the pump manufacturer's instructions.
3. Avoid operating the pump against a closed outlet unless the pump is specifically designed for that operating condition.
4. Secure the water tank and hose connections.
5. Inspect the system for leaks before operation.
6. Keep water away from exposed electronic circuits and electrical connections.
7. Switch off and isolate electrical power before hydraulic maintenance.
8. Never exceed the manufacturer's pressure, voltage or duty-cycle limits.

## 12. Testing and Performance Verification

The following tests are required to establish the actual hydraulic performance of the FireGuard Capsule prototype.

| Test | Measurement | Verification purpose |
|---|---|---|
| Pump identification | Manufacturer and model | Confirm pump specifications |
| Free-flow test | Water delivered per minute | Establish measured flow without nozzle restriction |
| Operating-flow test | Flow at the installed nozzle | Determine actual water delivery |
| Pressure test | Operating discharge pressure | Verify operating pressure |
| Spray test | Spray pattern and distance | Evaluate water coverage |
| Tank-duration test | Time until usable water is exhausted | Determine actual continuous delivery duration |
| Leakage test | Visible leakage and pressure loss | Check hydraulic connections |
| Automatic activation test | Pump response to a valid control command | Verify suppression control |
| Shutdown test | Pump stopping response | Verify safe water-delivery shutdown |

All tests should record the date, test conditions, equipment used and measured results. Photographs and videos should be retained as supporting evidence.

No measured hydraulic test results are claimed in this report until the tests have been completed and documented.

## 13. Engineering Evaluation

The hydraulic design depends on matching the pump, hose, fittings and nozzle to the required water-delivery performance.

The main engineering factors are:

- Sufficient water flow at the actual operating pressure.
- Acceptable pressure losses through the delivery hose and fittings.
- A nozzle that produces the required spray pattern.
- Safe pump operation within manufacturer limits.
- Reliable automatic activation and shutdown.
- Sufficient stored water for the intended suppression event.

The final hydraulic design must be validated using the actual pump performance curve and measurements from the assembled prototype.

## 14. Conclusion

The FireGuard Capsule hydraulic system is designed around a 12V diaphragm pump, compact water storage, reinforced delivery hose and adjustable spray nozzle.

The current pump design targets are 5–6 L/min and 70–100 PSI. These targets provide a basis for component selection, but actual performance must be confirmed using the selected pump's datasheet and prototype testing.

Final hydraulic sizing will be completed after confirming the pump model, nozzle specification, hose dimensions, operating pressure and measured water flow rate.

## 15. Technical References

1. ASHRAE Handbook – Fundamentals, Chapter 22: Pipe Design. Darcy–Weisbach equation and pressure losses in piping systems.
2. KNF – FP 1.70 Liquid Pump Datasheet. Manufacturer example showing the relationship between flow rate and discharge pressure.
3. TOPSFLO – TF Series Miniature Diaphragm Pump Datasheet. Manufacturer example providing pump specifications and flow-pressure performance curves.

These references explain general hydraulic principles and illustrate manufacturer pump-performance data. They do not identify or verify the pump installed in the FireGuard Capsule prototype.

---

**Document status:** Engineering design report – preliminary sizing and verification requirements.

**Project:** FireGuard Capsule

**Discipline:** Mechanical and Hydraulic Engineering
