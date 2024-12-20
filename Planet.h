#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <cmath>  // For exp function

using namespace std;  // Using the standard namespace

class Planet {
    private:
        string name;                    // Planet name
        double gravity;                 // Gravitational acceleration [m/s^2]
        double air_density_sea_level;   // Air density at sea level

    public:
        Planet(string planet_name, double gravity, double air_density_sea_level);

        double planet_air_density(double altitude) const;  // Method to calculate air density
};

#endif
