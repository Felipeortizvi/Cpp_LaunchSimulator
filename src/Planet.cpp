#include "Planet.h"
#include <cmath>  // for std::exp
#include <iostream>
#include <string>
#include <vector>

Planet::Planet(std::string planet_name, double gravity_val, double air_density_sea_level_val, 
                double radius, double mass, double scale_height)
    : name(planet_name),
      gravity(gravity_val),
      air_density_sea_level(air_density_sea_level_val),
      radius(radius),
      mass(mass),
      scale_height(scale_height) {}

static std::vector<Planet> predefinedPlanets() {
    return {
        Planet("Earth", 9.81, 1.225, 6371000, 5.972e24, 7700),
        Planet("Mars", 3.721, 0.020, 3389500, 6.417e23, 11100),
        Planet("Venus", 8.87, 65.0, 6051800, 4.867e24, 15900),
        Planet("Jupiter", 24.79, 0.0, 69911000, 1.898e27, 27000)  // Gas giant, no air density
    };
}

void Planet::printDetails() const {
    std::cout << "Planet: " << name << "\n"
                << "  Gravity:                  " << gravity << " m/s^2\n"
                << "  Air Density at Sea Level: " << air_density_sea_level << " kg/m^3\n"
                << "  Radius:                   " << radius << " m\n"
                << "  Mass:                     " << mass << " kg\n"
                << "  Scale height:             " << scale_height << " m\n";
}


double Planet::planet_air_density(double altitude) const {
    // ρ = ρ0 * exp(-altitude / H)
    return air_density_sea_level * std::exp(-altitude / scale_height);
}

double Planet::getScaleHeight() const {
    return scale_height;
}

string Planet::getName() const {
    return name;
}

double Planet::getGravity() const {
    return gravity;
}

double Planet::getRadius() const {
    return radius;
}

double Planet::getMass() const {
    return mass;
}


Planet Planet::selectPlanet(){
    std::cout << "Choose a planet:\n";

    // Retrieve the predefined planets
    std::vector<Planet> planets = predefinedPlanets();

    // Display the planets
    for (size_t i = 0; i < planets.size(); ++i) {
        std::cout << i + 1 << ") " << planets[i].getName() << "\n";
    }
    std::cout << planets.size() + 1 << ") Create your own planet\n";

    // Get the user's choice
    int choice;
    std::cin >> choice;

    if (choice >= 1 && choice <= planets.size()) {
        // Return the selected predefined planet
        return planets[choice - 1];
    } else if (choice == planets.size() + 1) {
        // Create a custom planet
        std::string name;
        double gravity, air_density, radius, mass, scale_height;

        std::cout << "Enter planet name: ";
        std::cin >> name;
        std::cout << "Enter gravity (m/s^2): ";
        std::cin >> gravity;
        std::cout << "Enter air density at sea level (kg/m^3): ";
        std::cin >> air_density;
        std::cout << "Enter radius (m): ";
        std::cin >> radius;
        std::cout << "Enter mass (kg): ";
        std::cin >> mass;
        std::cout <<"Enter Scale Height (m): ";
        std::cin >> scale_height;

        return Planet(name, gravity, air_density, radius, mass, scale_height);
    } else {
        std::cerr << "Invalid choice. Defaulting to Earth.\n";
        return planets[0];  // Default to Earth if the input is invalid
    }
}
