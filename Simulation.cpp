#include "Simulation.h"
#include <cmath>
#include <algorithm>  // for std::max_element
#include <iostream>   // for std::cout

Simulation::Simulation(double final_time_val, double time_step_val,
                       const Rocket& rocket_val, const Planet& planet_val)
    : final_time(final_time_val),
      time_step(time_step_val),
      rocket(rocket_val),
      planet(planet_val)
{
    // Pre-allocate arrays to hold data up to final_time / time_step
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
    // Initialize the time array
    for (int i = 0; i < (int)time.size(); i++) {
        time[i] = i * time_step;
    }

    // Initial conditions
    x[0] = 0.0;
    y[0] = 0.0;
    velocity_x[0] = 0.0;
    velocity_y[0] = 0.0;
    acceleration_x[0] = 0.0;
    acceleration_y[0] = 0.0;

    int n = 0;
    int n_max = (int)time.size() - 1;

    // Planet gravity
    double g = planet.getGravity();

    // Thrust components
    std::vector<double> thrust = rocket.rocket_thrust_x_y();
    double thrust_x = thrust[0];
    double thrust_y = thrust[1];

    // Burn time
    double burnTime = rocket.get_burn_time();

    // ------------------- Thrusting phase -------------------
    while (time[n] < burnTime && n < n_max) {
        // Current speed
        double v = std::sqrt(velocity_x[n]*velocity_x[n] + velocity_y[n]*velocity_y[n]);

        // Drag in x & y
        double drag_x = rocket.rocket_drag_i_direction(planet, y[n], v, velocity_x[n]);
        double drag_y = rocket.rocket_drag_i_direction(planet, y[n], v, velocity_y[n]);

        // Current rocket mass
        double current_mass = rocket.rocket_mass(time[n]);

        // Acceleration
        acceleration_x[n] = (thrust_x + drag_x) / current_mass;
        acceleration_y[n] = (thrust_y + drag_y) / current_mass - g;

        // Euler step for position
        x[n + 1] = x[n] + velocity_x[n] * time_step;
        y[n + 1] = y[n] + velocity_y[n] * time_step;

        // Euler step for velocity
        velocity_x[n + 1] = velocity_x[n] + acceleration_x[n] * time_step;
        velocity_y[n + 1] = velocity_y[n] + acceleration_y[n] * time_step;

        n++;
    }

    // ------------------- Coasting phase -------------------
    while (y[n] >= 0.0 && n < n_max) {
        // Current speed
        double v = std::sqrt(velocity_x[n]*velocity_x[n] + velocity_y[n]*velocity_y[n]);

        // Drag in x & y
        double drag_x = rocket.rocket_drag_i_direction(planet, y[n], v, velocity_x[n]);
        double drag_y = rocket.rocket_drag_i_direction(planet, y[n], v, velocity_y[n]);

        // After burn-out, mass = dry mass
        double current_mass = rocket.get_dry_mass();

        // Acceleration
        acceleration_x[n] = drag_x / current_mass;
        acceleration_y[n] = drag_y / current_mass - g;

        // Euler step for position
        x[n + 1] = x[n] + velocity_x[n] * time_step;
        y[n + 1] = y[n] + velocity_y[n] * time_step;

        // Euler step for velocity
        velocity_x[n + 1] = velocity_x[n] + acceleration_x[n] * time_step;
        velocity_y[n + 1] = velocity_y[n] + acceleration_y[n] * time_step;

        n++;
    }

    // Trim arrays down to the actual size used
    time.resize(n);
    x.resize(n);
    y.resize(n);
    velocity_x.resize(n);
    velocity_y.resize(n);
    acceleration_x.resize(n);
    acceleration_y.resize(n);
}

void Simulation::apogee() const {
    // Find the index where y is maximum
    auto it = std::max_element(y.begin(), y.end());
    if (it != y.end()) {
        int idx = static_cast<int>(std::distance(y.begin(), it));
        double vx = velocity_x[idx];
        double vy = velocity_y[idx];
        double speed = std::sqrt(vx*vx + vy*vy);

        std::cout << "Apogee time: " << time[idx] << " s\n";
        std::cout << "Altitude: " << y[idx] << " m\n";
        std::cout << "Speed: " << speed << " m/s\n";
    } else {
        std::cout << "No apogee found.\n";
    }
}
