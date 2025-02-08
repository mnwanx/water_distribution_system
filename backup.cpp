#include <iostream>
#include <vector>

using namespace std;

class Pipe {
public:
    double diameter, flowRate, pressure;

    Pipe(double d, double f, double p) : diameter(d), flowRate(f), pressure(p) {}

    void calculateFlow() {
        cout << "Flow in pipe: " << flowRate << " L/s\n";
    }
};

class Pump {
public:
    double power, pressureIncrease;

    Pump(double p, double pi) : power(p), pressureIncrease(pi) {}

    void adjustPressure(double& systemPressure) {
        systemPressure += pressureIncrease;
        cout << "New system pressure: " << systemPressure << " kPa\n";
    }
};

class Reservoir {
public:
    double capacity, currentLevel;

    Reservoir(double c, double cl) : capacity(c), currentLevel(cl) {}

    void supplyWater(double demand) {
        if (currentLevel >= demand) {
            currentLevel -= demand;
            cout << "Water supplied: " << demand << " L\n";
        } else {
            cout << "Not enough water in reservoir!\n";
        }
    }
};

class Junction {
public:
    vector<Pipe> connectedPipes;

    void addPipe(const Pipe& pipe) {
        connectedPipes.push_back(pipe);
    }

    void simulateScenario() {
        cout << "Simulating water demand scenario...\n";
        for (double pipe : connectedPipes) {
            pipe.calculateFlow();

        }
    }
};

int main() {
    Pipe p1(10, 50, 100);
    Pump pump1(5, 20);
    Reservoir res1(1000, 800);
    Junction j1;

    j1.addPipe(p1);
    j1.simulateScenario();

    pump1.adjustPressure(p1.pressure);
    res1.supplyWater(200);

    return 0;
}
