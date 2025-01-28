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
    std::cout   << "Rocket: " << name <<"\n"
                << " Wet Mass:               " << wet_mass << " kg\n"
                << " Dry Mass:               " << dry_mass << " kg\n"
                << " Thrust (avg):           " << average_rocket_thrust << " N\n"
                << " Burn Time:              " << burn_time << " s\n"
                << " Cross-sectional Area:   " << rocket_area << " m^2\n"
                << " Drag Coefficient:       " << rocket_drag_coeff << "\n";
}

static std::vector<Rocket> predefinedRockets() {
    return {
        Rocket("Saturn V (lumped)", 2'800'000.0, 130'000.0, 3.5e7, 700.0, 80.0, 0.2),
        Rocket("Space Shuttle (lumped)", 2'000'000.0, 120'000.0, 3.0e7, 510.0, 55.0, 0.3),
        Rocket("Falcon Heavy (lumped)", 1'420'000.0, 80'000.0, 2.3e7, 600.0, 30.0, 0.3),
        Rocket("SLS Block 1 (lumped)", 2'600'000.0, 130'000.0, 3.5e7, 700.0, 55.0, 0.25),
        Rocket("ESA Rocket", 19.765, 11.269, 2501.8, 6.09, 1.081e-2, 0.51)
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

string Rocket::getName() const {
    return name;
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

Rocket Rocket::selectRocket() {
    // Present the predefined rocket choices
    std::cout << "Choose a Rocket:\n";

    // Retrieve the predefined rocket list
    std::vector<Rocket> rockets = predefinedRockets();

    // Display them with indices
    for (size_t i = 0; i < rockets.size(); ++i) {
        std::cout << i + 1 << ") " << rockets[i].getName() << "\n";
    }
    std::cout << rockets.size() + 1 << ") Create your own Rocket\n";

    // Get the user's choice
    int choice;
    std::cin >> choice;

    if (choice >= 1 && choice <= (int)rockets.size()) {
        // Return the selected predefined rocket
        return rockets[choice - 1];
    } 
    else if (choice == (int)rockets.size() + 1) {
        // Create a custom rocket
        std::string name;
        double wet_mass, dry_mass, thrust, burn_time, area, drag_coeff;

        std::cout << "Enter rocket name: ";
        std::cin >> name;

        std::cout << "Enter wet mass (kg): ";
        std::cin >> wet_mass;

        std::cout << "Enter dry mass (kg): ";
        std::cin >> dry_mass;

        std::cout << "Enter average thrust (N): ";
        std::cin >> thrust;

        std::cout << "Enter burn time (s): ";
        std::cin >> burn_time;

        std::cout << "Enter cross-sectional area (m^2): ";
        std::cin >> area;

        std::cout << "Enter drag coefficient (dimensionless): ";
        std::cin >> drag_coeff;

        // Build and return a new Rocket with the user inputs
        return Rocket(name, wet_mass, dry_mass, thrust, burn_time, area, drag_coeff);
    } 
    else {
        // Invalid choice: default to the first rocket or handle error
        std::cerr << "Invalid choice. Defaulting to \"" 
                  << rockets[0].getName() << "\".\n";
        return rockets[0];
    }
}