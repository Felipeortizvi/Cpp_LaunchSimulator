#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rocket{

    private:
        // Member variables and attributes
        string name;
        double mass;
        double fuelCapacity;
        double currentFuel;

    public:
        // Constructor
        Rocket(string rocketName, double rocketMass, double fuelCapacity) 
        : name(rocketName), mass(rocketMass), fuelCapacity(fuelCapacity), currentFuel(currentFuel) {}

        void burnFuel(double amount) {
            if (amount <= currentFuel) {
                currentFuel -= amount;
                cout << "Burned: " << amount << " units of fuel.\n";
                cout << "Remaining fuel: "<<currentFuel;

            }
            else{
                cout << "Not enough fuel";
            }
        }

        double calculateThrustToWeightRatio(double thrust) const {
            double weight = mass * 9.81; // Assuming Earth's Gravity
            return thrust / weight;
            
        }
        
        void displayStats() const {
            cout << "Rocket Name: " << name << endl;
            cout << "Mass: " << mass << " kg" << endl;
            cout << "Fuel Capacity: " << fuelCapacity << " units" << endl;
            cout << "Current Fuel: " << currentFuel << " units" << endl;
        }
};



int main() {
    
    Rocket rocket1("Ares", 549054, 150000); // Name, mass, and fuel capacity

    rocket1.displayStats();

    return 0;


}