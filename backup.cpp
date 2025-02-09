/*
Student Name    : Muhammad Najwan bin Hassan
Student ID      : 2023680886
Project Title   : Water Distribution System
*/
#include <iostream>
#include <vector>
using namespace std;

// superclass: Water System Component
class WaterSystemComponent {
protected:
    string name;
    double pressure, flowRate;

public:
    WaterSystemComponent(string n, double p, double f) : name(n), pressure(p), flowRate(f) {}
    virtual void simulate() = 0; 
    virtual double calculateFlow() = 0; 

    virtual void displayInfo() {
        cout << "Component: " << name 
             << " | Pressure: " << pressure << " kPa"
             << " | Flow Rate: " << flowRate << " L/s" << endl;
    }
};

// Pipe Class
class Pipe : public WaterSystemComponent {
private:
    double diameter, length;
public:

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
private:
    double powerUsage;
    double costPerUnit;
public:
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
private:
    double capacity, currentLevel;
public:
    Reservoir(string n, double p, double f, double cap) 
        : WaterSystemComponent(n, p, f), capacity(cap), currentLevel(cap) {}

    double calculateFlow() override {
        return (flowRate > capacity) ? capacity : flowRate;
    }
    void waterAdd(double water_add) {
        cout << "Water added to reservoir: " << water_add << " liters" << endl;
        if (water_add <= capacity - currentLevel)  {
            currentLevel += water_add;
        }   else    {
            cout << "Not enough capacity! Extra limit: " << water_add - (capacity - currentLevel) << " liters" << endl;
            currentLevel = capacity;
        }
    }
    void waterDemand(double demand)  {
        cout << "Demanding: " << demand << " liters" << endl;
        if (currentLevel >= demand) {
            currentLevel -= demand;
        }   else    {
            cout << "Water Capacity not enough for demand" << endl;
        }
    }
    void simulate() override {
        cout << "Reservoir: " << name 
             << " | Capacity: " << capacity << " liters |  Current Level: " << currentLevel
             << "liters | Flow: " << calculateFlow() << " L/s" << endl;
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


void separator()    {
    for (int i = 0; i < 20; i ++)   {
        cout << "-";
    }
    cout << endl;
}
// Main Function
string info = "Student Name    : Muhammad Najwan bin Hassan\nStudent ID      : 2023680886\n\n";
int main() {
    cout << info << endl;

    // Object instance
    Pipe pipe1("Main Pipe", 10, 50, 100, 50);
    Pipe pipe2("Secondary Pipe", 10, 50, 100, 50);

    Pump pump1("Central Pump", 100, 50, 500, 0.05);
    Pump pump2("Secondary Pump", 100, 50, 500, 0.05);
    
    Reservoir reservoir1("Water Tank", 120, 60, 5000);
    Junction junction1("Distribution Hub", 110, 55);

    // Simulate system behavior
    junction1.addPipe(&pipe1);
    junction1.addPipe(&pipe2);

    pump1.adjustPressure(100);
    pump2.adjustPressure(100);

    vector<WaterSystemComponent*> components = {&pipe1, &pump1, &reservoir1, &junction1};
    
    cout << "\n==== Water Distribution System Simulation ====\n";
    for (auto comp : components) {
        comp->simulate();
    }
    separator();
    reservoir1.waterDemand(4000);
    reservoir1.simulate();
    reservoir1.waterAdd(30000);
    reservoir1.simulate();

    return 0;
}
