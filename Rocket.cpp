#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rocket{

    private:
        // Member variables and attributes
        string name;                    // name for rocket
        double wet_mass;                // wet mass of the rocket [kg]
        double dry_mass;                // dry mass of the rocket [kg]
        double average_rocket_thrust;   // average rocket engine thrust [N]
        double burn_time;               // burn time [s]
        double rocket_area;             // rocket body frontal area [m^2]. 1.081 dm^2 = 1.081e-2 m^2
        double rocket_drag_coeff;       // drag coefficient of the rocket [-]

    public:
    // Constructor
    Rocket(
        string rocket_name,
        double rocket_wet_mass,
        double rocket_dry_mass,
        double rocket_thrust,
        double rocket_burn_time,
        double rocket_area_value,
        double rocket_drag_coefficient) 
        : name(rocket_name),
        wet_mass(rocket_wet_mass),
        dry_mass(rocket_dry_mass),
        average_rocket_thrust(rocket_thrust),
        burn_time(rocket_burn_time),
        rocket_area(rocket_area_value),
        rocket_drag_coeff(rocket_drag_coefficient) {}


    double rocket_mass(double time) const {
        // Compute the rocket mass based on elapsed time
        return wet_mass - (wet_mass - dry_mass) * time / burn_time;
    }

    double rocket_wet_mass() const {
        return wet_mass;
    }

};



int main() {

    Rocket myRocket("Aries", 500000.0, 200000.0, 7600000.0, 180.0, 1.081e-2, 0.5);

    int time = 90;
    double mass = myRocket.rocket_mass(time);
    cout << "\n";
    cout << "Original mass: " << myRocket.rocket_wet_mass() << " kg\n";
    cout << "Rocket mass at time " << time << " seconds: " << mass << " kg" << endl;
    return 0;


}