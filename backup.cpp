#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base Class: Water System Component
class WaterSystemComponent {
protected:
    string name;
    double pressure, flowRate;

public:
    WaterSystemComponent(string n, double p, double f) : name(n), pressure(p), flowRate(f) {}
    virtual void simulate() = 0; // Abstract method
    virtual double calculateFlow() = 0; // Abstract flow calculation

    virtual void displayInfo() {
        cout << "Component: " << name 
             << " | Pressure: " << pressure << " kPa"
             << " | Flow Rate: " << flowRate << " L/s" << endl;
    }
};

// Pipe Class
class Pipe : public WaterSystemComponent {
public:
    double diameter, length;

    Pipe(string n, double d, double l, double p, double f) 
        : WaterSystemComponent(n, p, f), diameter(d), length(l) {}

    double calculateFlow() override {
        // Simplified formula: Flow = Area * Pressure Factor
        return (3.14 * (diameter / 2) * (diameter / 2)) * (pressure / 10);
    }

    void simulate() override {
        cout << "Simulating Pipe: " << name 
             << " | Diameter: " << diameter << " cm"
             << " | Flow: " << calculateFlow() << " L/s" << endl;
    }
};

// Pump Class with Cost Control
class Pump : public WaterSystemComponent {
public:
    double powerUsage;
    double costPerUnit;

    Pump(string n, double p, double f, double power, double cost) 
        : WaterSystemComponent(n, p, f), powerUsage(power), costPerUnit(cost) {}

    void adjustPressure(double demand) {
        pressure = (demand > flowRate) ? pressure + 5 : pressure - 5;
        powerUsage += 0.1 * demand; // Simulating increased power usage
    }

    double calculateFlow() override {
        return flowRate + (pressure / 20); // Pumps increase flow based on pressure
    }

    double calculateCost() {
        return powerUsage * costPerUnit;
    }

    void simulate() override {
        cout << "Pump: " << name 
             << " | Adjusted Pressure: " << pressure << " kPa"
             << " | Power Cost: RM" << calculateCost() << endl;
    }
};

// Reservoir Class
class Reservoir : public WaterSystemComponent {
public:
    double capacity;

    Reservoir(string n, double p, double f, double cap) 
        : WaterSystemComponent(n, p, f), capacity(cap) {}

    double calculateFlow() override {
        return (flowRate > capacity) ? capacity : flowRate;
    }

    void simulate() override {
        cout << "Reservoir: " << name 
             << " | Capacity: " << capacity << " liters"
             << " | Flow: " << calculateFlow() << " L/s" << endl;
    }
};

// Junction Class for Flexibility
class Junction : public WaterSystemComponent {
public:
    vector<Pipe*> connectedPipes;

    Junction(string n, double p, double f) : WaterSystemComponent(n, p, f) {}

    void addPipe(Pipe* pipe) {
        connectedPipes.push_back(pipe);
        cout << "New pipe added to " << name 
             << ". Total pipes: " << connectedPipes.size() << endl;
    }

    double calculateFlow() override {
        double totalFlow = 0;
        for (Pipe* p : connectedPipes) {
            totalFlow += p->calculateFlow();
        }
        return totalFlow;
    }

    void simulate() override {
        cout << "Junction: " << name 
             << " | Connected Pipes: " << connectedPipes.size()
             << " | Total Flow: " << calculateFlow() << " L/s" << endl;
    }
};

// Main Function
int main() {
    // Create system components
    Pipe pipe1("Main Pipe", 10, 50, 100, 50);
    Pipe pipe2("Secondary Pipe", 10, 50, 100, 50);
    Pump pump1("Central Pump", 100, 50, 500, 0.05);
    Pump pump2("Secondary Pump", 100, 50, 500, 0.05);
    pump2.adjustPressure(100);
    Reservoir reservoir1("Water Tank", 120, 60, 5000);
    Junction junction1("Distribution Hub", 110, 55);

    // Simulate system behavior
    junction1.addPipe(&pipe1);
    junction1.addPipe(&pipe2);
    pump1.adjustPressure(100);

    vector<WaterSystemComponent*> components = {&pipe1, &pump1, &reservoir1, &junction1};
    
    cout << "\n==== Water Distribution System Simulation ====\n";
    for (auto comp : components) {
        comp->simulate();
    }

    return 0;
}
