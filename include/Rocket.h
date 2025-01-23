
#ifndef ROCKET_H
#define ROCKET_H

#include <string>
#include <vector>
#include "planet.h"  // Include the Planet class header file

using namespace std;  // Using the standard namespace

class Rocket {
    private:
        string name;                    // Name for rocket
        double wet_mass;                // Wet mass of the rocket [kg]
        double dry_mass;                // Dry mass of the rocket [kg]
        double average_rocket_thrust;   // Average rocket engine thrust [N]
        double burn_time;               // Burn time [s]
        double rocket_area;             // Rocket body frontal area [m^2]
        double rocket_drag_coeff;       // Drag coefficient of the rocket [-]
        double launch_angle;            // Launch angle in radians

    public:
        Rocket(string rocket_name, double rocket_wet_mass, double rocket_dry_mass, 
               double rocket_thrust, double rocket_burn_time, 
               double rocket_area_value, double rocket_drag_coefficient);
        
        void printRocketDetails() const;

        //static Rocket selectPresetRocket;
        static Rocket selectRocket();

        double rocket_mass(double time) const;

        double rocket_wet_mass() const;

        string getName() const;

        double rocket_drag_i_direction(const Planet& planet, double altitude, double velocity, double velcity_i) const;

        void set_launch_angle() ;

        double get_launch_angle() const;

        vector<double> rocket_thrust_x_y() const;

        double get_burn_time() const;

        double get_wet_mass() const;

        double get_dry_mass() const;


};

#endif
