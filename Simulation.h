#ifndef SIMULATION_H
#define SIMULATION_H


#include <vector>
#include <cmath>
#include "Rocket.h"
#include "Planet.h"

using namespace std;

class Simulation{
    private:
        double final_time;
        double time_step;
        const Rocket& rocket;
        const Planet& planet;

        vector<double> time, x, y, velocity_x, velocity_y, acceleration_x, acceleration_y;

        
        
    public:

        Simulation(double final_time, double time_step, const Rocket& rocket, const Planet& planet);

        void runSimulation();

        const vector<double>& get_time() const { return time; }
        const vector<double>& get_x() const { return x; }
        const vector<double>& get_y() const { return y; }
        const vector<double>& get_velocity_x() const { return velocity_x; }
        const vector<double>& get_velocity_y() const { return velocity_y; }
        const vector<double>& get_acceleration_x() const { return acceleration_x; }
        const vector<double>& get_acceleration_y() const { return acceleration_y; }

        double velocity() const; 

        double burnout() const;

        double apogee() const; 


};

#endif