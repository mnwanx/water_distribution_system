#include <iostream>
#include <vector>

// Superclass for all water system components
class WaterSystemComponent {
public:
    std::string name;
    double pressure;
    double flowRate;

    WaterSystemComponent(std::string n, double p, double f) 
        : name(n), pressure(p), flowRate(f) {}

    virtual void displayInfo() {
        std::cout << "Component: " << name << "\nPressure: " << pressure 
                  << " kPa\nFlow Rate: " << flowRate << " L/s\n";
    }

    virtual void simulate() {
        std::cout << name << " simulation running...\n";
    }
};

// Pipe class inheriting from WaterSystemComponent
class Pipe : public WaterSystemComponent {
public:
    double diameter;

    Pipe(std::string n, double d, double f, double p) 
        : WaterSystemComponent(n, p, f), diameter(d) {}

    void simulate() override {
        std::cout << "Pipe '" << name << "' - Diameter: " << diameter 
                  << " cm - Flow: " << flowRate << " L/s\n";
    }
};

// Pump class inheriting from WaterSystemComponent
class Pump : public WaterSystemComponent {
public:
    double power;

    Pump(std::string n, double pow, double p, double f) 
        : WaterSystemComponent(n, p, f), power(pow) {}

    void adjustPressure(double increase) {
        pressure += increase;
        std::cout << "Pump '" << name << "' increased pressure by " << increase 
                  << " kPa. New Pressure: " << pressure << " kPa\n";
    }
};

// Reservoir class inheriting from WaterSystemComponent
class Reservoir : public WaterSystemComponent {
public:
    double capacity, currentLevel;

    Reservoir(std::string n, double cap, double cl, double p, double f) 
        : WaterSystemComponent(n, p, f), capacity(cap), currentLevel(cl) {}

    void supplyWater(double demand) {
        if (currentLevel >= demand) {
            currentLevel -= demand;
            std::cout << "Reservoir '" << name << "' supplied " << demand 
                      << " L. Remaining Level: " << currentLevel << " L\n";
        } else {
            std::cout << "Reservoir '" << name << "' is low on water!\n";
        }
    }
};

// Junction class inheriting from WaterSystemComponent
class Junction : public WaterSystemComponent {
public:
    std::vector<Pipe> connectedPipes;

    Junction(std::string n, double p, double f) : WaterSystemComponent(n, p, f) {}

    void addPipe(const Pipe& pipe) {
        connectedPipes.push_back(pipe);
    }

    void simulate() override {
        std::cout << "Junction '" << name << "' - Simulating connections...\n";
        for (auto& pipe : connectedPipes) {
            pipe.simulate();
        }
    }
};

// Main function
int main() {
    Pipe p1("Main Pipe", 10, 50, 100);
    Pump pump1("Pump A", 5, 120, 0);
    Reservoir res1("Reservoir X", 1000, 800, 90, 0);
    Junction j1("Junction 1", 100, 0);

    j1.addPipe(p1);

    // Run simulations
    p1.simulate();
    pump1.adjustPressure(20);
    res1.supplyWater(200);
    j1.simulate();

    return 0;
}
