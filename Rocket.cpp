
#define _USE_MATH_DEFINES
#include "Rocket.h"
#include "Planet.h"
#include <iostream>
#include <cmath>  // For mathematical operations like exp

Rocket::Rocket(string rocket_name, double rocket_wet_mass, double rocket_dry_mass, 
               double rocket_thrust, double rocket_burn_time, 
               double rocket_area_value, double rocket_drag_coefficient)
                : name(rocket_name), wet_mass(rocket_wet_mass), dry_mass(rocket_dry_mass), 
                average_rocket_thrust(rocket_thrust), burn_time(rocket_burn_time), 
                rocket_area(rocket_area_value), rocket_drag_coeff(rocket_drag_coefficient),
                launch_angle(0.0) {};      

double Rocket::rocket_mass(double time) const {
    if (time > burn_time) return dry_mass;
    return wet_mass - (wet_mass - dry_mass) * time / burn_time;
}

double Rocket::rocket_wet_mass() const {
    return wet_mass;
}

double Rocket::rocket_drag_i_direction(const Planet& planet, double altitude, double velocity, double velcity_i) const {
    return -0.5 * rocket_drag_coeff * rocket_area * planet.planet_air_density(altitude) * velocity * velcity_i;
}

void Rocket::rocket_launch_angle(double angle){
    launch_angle = angle * M_PI / 180.0;  // Convert degrees to radians and store
}

double Rocket::get_launch_angle() const {
    return launch_angle;  // Return the stored launch angle
}

vector<double> Rocket::rocket_thrust_x_y() const {
    double thrust_x = average_rocket_thrust * cos(launch_angle);
    double thrust_y = average_rocket_thrust * sin(launch_angle);
    std::cout << launch_angle << std::endl;
    std::cout << thrust_x << std::endl;
    std::cout << thrust_y << std::endl;

    return {thrust_x, thrust_y};

}

double Rocket::get_burn_time() const{
    return burn_time;
}

double Rocket::get_dry_mass() const {
    return dry_mass;
}

double Rocket::get_wet_mass() const {
    return wet_mass;
}
