#include "Planet.h"
#include <cmath>  // for std::exp
#include <iostream>

Planet::Planet(std::string planet_name, double gravity_val, double air_density_sea_level_val)
    : name(planet_name),
      gravity(gravity_val),
      air_density_sea_level(air_density_sea_level_val) {}

std::ostream& operator<<(std::ostream& os, const Planet& planet)
{
    os << "Planet: "                    << planet.name << std::endl
       << "Gravity = "                  << planet.gravity << " m/s" << std::endl
       << "Air Density Sea Level = "    << planet.air_density_sea_level << " kg/m^3" << std::endl;
    return os;
}


double Planet::planet_air_density(double altitude) const {
    // Same scale height as in your Python code
    const double scale_height = 7700.0;
    // ρ = ρ0 * exp(-altitude / H)
    return air_density_sea_level * std::exp(-altitude / scale_height);
}

double Planet::getGravity() const {
    return gravity;
}
