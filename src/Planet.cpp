#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


class Planet{

    private:
        string name; // planet name
        double gravity; // gravitational acceleration [m/s^2]
        double air_density_sea_level; // air density at sea level

    public:

        Planet(
            string planet_name,
            double gravity,
            double air_density_sea_level)
            : name(planet_name),
            gravity(gravity),
            air_density_sea_level(air_density_sea_level) {}

        double planet_air_density(double altitude){
            // Air density of planet [kg/m^3]
            int scale_height = 7700;
            return air_density_sea_level * exp(-altitude / scale_height);
        }
};