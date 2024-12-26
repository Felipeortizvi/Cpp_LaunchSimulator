#define _USE_MATH_DEFINES
#include "Simulation.h"
#include "Rocket.h"
#include "Planet.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

Simulation::Simulation(double final_time, double time_step, const Rocket& rocket, const Planet& planet) 
    : final_time(final_time), time_step(time_step), rocket(rocket), planet(planet) {

    // Resize the vectors based on the number of time steps
    int N = static_cast<int>(std::ceil(final_time / time_step));
    time.resize(N);
    x.resize(N);
    y.resize(N);
    velocity_x.resize(N);
    velocity_y.resize(N);
    acceleration_x.resize(N);
    acceleration_y.resize(N);
}

void Simulation::runSimulation() {
    // Initialize time vector
    for (int i = 0; i < time.size(); i++) {
        time[i] = i * time_step;
    }

    // Initial values for position and velocity
    x[0] = 0.0;
    y[0] = 0.0;
    velocity_x[0] = 0.0;
    velocity_y[0] = 0.0;
    acceleration_x[0] = 0.0;
    acceleration_y[0] = 0.0;

    // Simulation variables
    int n = 0;
    int n_max = time.size() - 1;
    double g = 9.81; // Gravitational constant (assuming Earth's gravity)


    // Thrusting phase

    vector<double> thrust = rocket.rocket_thrust_x_y();
    double thrust_x = thrust[0];
    double thrust_y = thrust[1];


    while (time[n] < rocket.get_burn_time() && n < n_max) {
        double v = std::sqrt(velocity_x[n] * velocity_x[n] + velocity_y[n] * velocity_y[n]);

        // Assuming `D_i` is some drag force function
        double drag_x = rocket.rocket_drag_i_direction(planet, y[n], v, velocity_x[n]);
        double drag_y = rocket.rocket_drag_i_direction(planet, y[n], v, velocity_y[n]);

        acceleration_x[n] = (thrust_x + drag_x) / rocket.rocket_mass(time[n]);
        acceleration_y[n] = (thrust_y + drag_y) / rocket.rocket_mass(time[n]) - g;

        // Euler's method for updating position and velocity
        x[n + 1] = x[n] + velocity_x[n] * time_step;
        y[n + 1] = y[n] + velocity_y[n] * time_step;

        velocity_x[n + 1] = velocity_x[n] + acceleration_x[n] * time_step;
        velocity_y[n + 1] = velocity_y[n] + acceleration_y[n] * time_step;

        n++;
    }

    // Coasting phase
    while (y[n] >= 0 && n < n_max) {
        double v = std::sqrt(velocity_x[n] * velocity_x[n] + velocity_y[n] * velocity_y[n]);

        // Assuming `D_i` is some drag force function
        double drag_x = rocket.rocket_drag_i_direction(planet, y[n], v, velocity_x[n]);
        double drag_y = rocket.rocket_drag_i_direction(planet, y[n], v, velocity_y[n]);

        acceleration_x[n] = drag_x / rocket.get_dry_mass();
        acceleration_y[n] = drag_y / rocket.get_dry_mass() - g;

        // Euler's method for updating position and velocity
        x[n + 1] = x[n] + velocity_x[n] * time_step;
        y[n + 1] = y[n] + velocity_y[n] * time_step;

        velocity_x[n + 1] = velocity_x[n] + acceleration_x[n] * time_step;
        velocity_y[n + 1] = velocity_y[n] + acceleration_y[n] * time_step;

        n++;
    }

    // Resize the vectors to the number of points calculated
    time.resize(n);
    x.resize(n);
    y.resize(n);
    velocity_x.resize(n);
    velocity_y.resize(n);
    acceleration_x.resize(n);
    acceleration_y.resize(n);
}


double Simulation::velocity() const{
    double v_x = velocity_x[0];
    double v_y = velocity_y[0];
    return sqrt(pow(v_x, 2) + pow(v_y,2));
}


void Simulation::apogee() const {
    auto max_it = std::max_element(y.begin(), y.end());
    if (max_it != y.end()) {
        int n_a = std::distance(y.begin(), max_it);
        cout << "Apogee time: " << time[n_a] << " seconds" << endl;
        cout << "Altitude: " << y[n_a] << " meters" << endl;
        cout << "Speed: " << sqrt(pow(velocity_x[n_a], 2) + pow(velocity_y[n_a], 2)) << " m/s" << endl;
    } else {
        cout << "Apogee could not be determined." << endl;
    }
}
