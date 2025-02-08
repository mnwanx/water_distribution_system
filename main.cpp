#include <iostream>
#include <vector>

using namespace std;

void print(string parameter) { cout << parameter << endl; } 

class WaterSystemComponent{
    protected:
        double pressure, flowrate;
        bool status;
        string location, name;
    public:
        WaterSystemComponent(string n = "", double p = 0, double f = 0) : name(n), pressure(p), flowrate(f) {}
        virtual void show_info()   {
            cout << "Component: " << name << "\nPressure: " << pressure << " kPa\nFlow Rate: " << flowrate << " L/s\n";
        }
};

class Pipe : public WaterSystemComponent {
    protected:
        double diameter;
    public:
        Pipe(string n = "", double d = 0, double f = 0, double p = 0)  {
            name = n;
            flowrate = f;
            pressure = p;
            diameter = d;
        }

        void show_info() override  {
            cout << "Pipe: " << name << "\nDiameter: " << diameter << "cm^2\nPressure: " << pressure << " kPa\nFlow Rate: " << flowrate << " L/s\n";
        }
};

class Pump  : public WaterSystemComponent{
    private:
        double power;
    public:
        Pump(string n = "", double pow = 0, double p = 0, double f = 0) : WaterSystemComponent(n, p, f), power(pow) {}

        void show_info() override {
            cout << "Pump: " << name << "\nPower: " << power << "W\nPressure: " << pressure << " kPa\nFlow Rate: " << flowrate << " L/s\n";
        }
};
class Reservoir  : public WaterSystemComponent{
    private:
        double capacity, current_level;
    public:
        Reservoir(string name = "", double capacity = 0, double current_level = 0) : WaterSystemComponent(name = name), capacity(capacity), current_level(current_level) {}
        void show_info() override {
            cout << "Reservoir: " << name << "\nCapacity: " << capacity << "L\nCurrent Level: " << current_level << " L\n";
        }
        void waterSupply(double in_demand) {
            if (current_level >= in_demand)  {
                current_level -= in_demand;
                show_info();
            }   else    {
                cout << "Water level in resevoir is low" << endl;
            }
        }
};
class Junction  : public WaterSystemComponent{
    private:
        vector<Pipe> connected_pipes;
    public:
        Junction(string name = "", double pressure = 0, double flowrate = 0) : WaterSystemComponent(name, pressure, flowrate) {}
        void add_pipe(const Pipe& pipe) {
            connected_pipes.push_back(pipe);
        }  
        
        void show_info() override   {
            cout << "Connected junction: " << endl;
            for (auto& pipe : connected_pipes)    {
                pipe.show_info();
            }
        }
};



void separator()    {
    for (int i = 0; i < 20; i ++)   {
        cout << "-";
    }
    cout << endl;
}

int main()  {
    Pipe pipe1("Main Pipe", 10, 50, 100);
    Pump pump1("Main Pump", 10, 10,10);
    Reservoir reservoir1("Main Reservoir", 20000, 20000);
    Junction junction1("Main Junction", 10, 10);
    WaterSystemComponent().show_info();
    separator();
    pipe1.show_info();
    separator();
    pump1.show_info();
    separator();
    reservoir1.show_info();
    separator();
    // reservoir1.waterSupply(10);
    junction1.add_pipe(pipe1);
    junction1.show_info();
    return 0;
}