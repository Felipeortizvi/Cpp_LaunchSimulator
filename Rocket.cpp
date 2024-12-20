#include "Rocket.h"
#include "Planet.h"
#include <cmath>  // For mathematical operations like exp

Rocket::Rocket(string rocket_name, double rocket_wet_mass, double rocket_dry_mass, 
               double rocket_thrust, double rocket_burn_time, 
               double rocket_area_value, double rocket_drag_coefficient)
                : name(rocket_name), wet_mass(rocket_wet_mass), dry_mass(rocket_dry_mass), 
                average_rocket_thrust(rocket_thrust), burn_time(rocket_burn_time), 
                rocket_area(rocket_area_value), rocket_drag_coeff(rocket_drag_coefficient) {}

double Rocket::rocket_mass(double time) const {
    return wet_mass - (wet_mass - dry_mass) * time / burn_time;
}

double Rocket::rocket_wet_mass() const {
    return wet_mass;
}

double Rocket::rocket_drag_i_Direction(double altitude, double velocity, double velcity_i) const {
    return -0.5 * rocket_drag_coeff * rocket_area * Planet::planet_air_density(altitude) * velocity * velcity_i;
}


