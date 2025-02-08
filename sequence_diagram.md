@startuml
actor Authorities
participant "Water Distribution System" as System
participant "Pump" as Pump
participant "Reservoir" as Reservoir
participant "Pipe" as Pipe
participant "Junction" as Junction

Authorities -> System: Start Simulation
System -> Pump: Adjust Pressure()
Pump -> System: Return Adjusted Pressure

System -> Reservoir: Supply Water()
Reservoir -> System: Return Available Water

System -> Pipe: Calculate Flow()
Pipe -> System: Return Flow Rate

System -> Junction: Distribute Water()
Junction -> System: Return Distributed Flow

System -> Authorities: Display Simulation Results

@enduml
