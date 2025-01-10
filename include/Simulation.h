#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "Rocket.h"
#include "Planet.h"

class Simulation {
private:
    double final_time;   // e.g. 180.0 s
    double time_step;    // e.g. 0.001 s
    const Rocket& rocket;
    const Planet& planet;

    // Data arrays
    std::vector<double> time;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> velocity_x;
    std::vector<double> velocity_y;
    std::vector<double> acceleration_x;
    std::vector<double> acceleration_y;

public:
    // Constructor
    Simulation(double final_time, double time_step,
               const Rocket& rocket, const Planet& planet);

    // Run the Euler integration
    void runSimulation();

    // Print out apogee
    void apogee() const;

    void burnout() const;

    const std::vector<double>& getTime() const { return time; }
    const std::vector<double>& getX() const { return x; }
    const std::vector<double>& getY() const { return y; }
    const std::vector<double>& getVelocityX() const { return velocity_x; }
    const std::vector<double>& getVelocityY() const { return velocity_y; }
    const std::vector<double>& getAccelerationX() const { return acceleration_x; }
    const std::vector<double>& getAccelerationY() const { return acceleration_y; }
};

#endif
