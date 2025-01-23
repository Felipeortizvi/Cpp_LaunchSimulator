#define _USE_MATH_DEFINES
#include "Rocket.h"
#include <vector>
#include <cmath>     // for std::cos, std::sin
#include <iostream>  // optional for debugging

Rocket::Rocket(std::string rocket_name,
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
      rocket_drag_coeff(rocket_drag_coefficient),
      launch_angle(0.0){}

void Rocket::printRocketDetails() const {
    std::cout << "Rocket: " << name <<"\n"
                << " Wet Mass: " << wet_mass << " kg"
                << " Dry Mass: " << dry_mass << " kg"
                << "Thrust (avg):           " << average_rocket_thrust << " N\n"
                << "Burn Time:              " << burn_time << " s\n"
                << "Cross-sectional Area:   " << rocket_area << " m^2\n"
                << "Drag Coefficient:       " << rocket_drag_coeff << "\n";
}

static std::vector<Rocket> selectPresetRocket() {
    // Build a list of lumps
    return {
        Rocket("Saturn V (lumped)", 2'800'000.0, 130'000.0, 3.5e7, 700.0, 80.0, 0.2),
        Rocket("Space Shuttle (lumped)", 2'000'000.0, 120'000.0, 3.0e7, 510.0, 55.0, 0.3),
        Rocket("Falcon Heavy (lumped)", 1'420'000.0, 80'000.0, 2.3e7, 600.0, 30.0, 0.3),
        Rocket("SLS Block 1 (lumped)", 2'600'000.0, 130'000.0, 3.5e7, 700.0, 55.0, 0.25)
    };
}

double Rocket::rocket_mass(double time) const {
    // If time is beyond burn time, rocket is at dry mass
    if (time > burn_time) {
        return dry_mass;
    }
    // Linear mass drop from wet_mass to dry_mass
    return wet_mass - (wet_mass - dry_mass) * (time / burn_time);
}

double Rocket::rocket_wet_mass() const {
    return wet_mass;
}

double Rocket::rocket_drag_i_direction(const Planet& planet,
                                       double altitude,
                                       double velocity,
                                       double velocity_i) const {
    // D_i = -0.5 * C_D * A * rho(y) * v * v_i
    return -0.5 * rocket_drag_coeff * rocket_area
                 * planet.planet_air_density(altitude)
                 * velocity * velocity_i;
}

void Rocket::set_launch_angle() {
    // convert degrees -> radians
    double angle_degrees;
    std::cout<<"Set your launch angle in Degrees (recommended value is 75-90): ";
    std::cin>>angle_degrees;
    launch_angle = angle_degrees * M_PI / 180.0;
}

double Rocket::get_launch_angle() const {
    return launch_angle; // in radians
}

std::vector<double> Rocket::rocket_thrust_x_y() const {
    // Thrust in x, y directions
    double thrust_x = average_rocket_thrust * std::cos(launch_angle);
    double thrust_y = average_rocket_thrust * std::sin(launch_angle);
    return {thrust_x, thrust_y};
}

double Rocket::get_burn_time() const {
    return burn_time;
}

double Rocket::get_dry_mass() const {
    return dry_mass;
}

double Rocket::get_wet_mass() const {
    return wet_mass; 
}
