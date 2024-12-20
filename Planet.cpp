#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


#include "planet.h"

Planet::Planet(string planet_name, double gravity, double air_density_sea_level)
    : name(planet_name), gravity(gravity), air_density_sea_level(air_density_sea_level) {}

double Planet::planet_air_density(double altitude) const{
    // Air density of planet [kg/m^3]
    int scale_height = 7700;  // Scale height of Earth's atmosphere
    return air_density_sea_level * exp(-altitude / scale_height);
}
