#ifndef ROCKET_H
#define ROCKET_H

#include <string>
#include "planet.h"  // Include the Planet class header file

class Rocket {
    private:
        std::string name;                    // Name for rocket
        double wet_mass;                     // Wet mass of the rocket [kg]
        double dry_mass;                     // Dry mass of the rocket [kg]
        double average_rocket_thrust;        // Average rocket engine thrust [N]
        double burn_time;                    // Burn time [s]
        double rocket_area;                  // Rocket body frontal area [m^2]
        double rocket_drag_coeff;            // Drag coefficient of the rocket [-]

    public:
        Rocket(std::string rocket_name, double rocket_wet_mass, double rocket_dry_mass, 
               double rocket_thrust, double rocket_burn_time, 
               double rocket_area_value, double rocket_drag_coefficient);

        double rocket_mass(double time) const;
        double rocket_wet_mass() const;

        double drag_i_direction(double time, double altitude, double velocity, 
                                 double velocity_i, const Planet& planet); // Method to compute drag force
};

#endif
