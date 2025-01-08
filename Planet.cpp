#include "Planet.h"
#include <cmath>  // for std::exp

Planet::Planet(std::string planet_name, double gravity_val, double air_density_sea_level_val)
    : name(planet_name),
      gravity(gravity_val),
      air_density_sea_level(air_density_sea_level_val)
{
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
