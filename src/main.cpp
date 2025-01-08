#include <iostream>
#include "Planet.h"
#include "Rocket.h"
#include "Simulation.h"

int main() {
    // 1) Create the planet
    //    - For Earth: gravity=9.81, air_density_sea_level=1.225
    Planet earth("Earth", 9.81, 1.225);

    // 2) Create the rocket
    //    - Must match your Python constants for a direct comparison:
    //      wet_mass = 19.765 kg
    //      dry_mass = 11.269 kg
    //      average thrust = 2501.8 N
    //      burn_time = 6.09 s
    //      frontal area = 1.081e-2 m^2
    //      drag coefficient = 0.51
    Rocket myRocket("TestRocket", 19.765, 11.269,
                    2501.8, 6.09,
                    1.081e-2, 0.51);

    // 3) Set the rocket's launch angle
    //    - In your Python: theta_0 = 75 deg
    myRocket.rocket_launch_angle(75.0);

    // 4) Create the simulation
    //    - final_time=180 s, time_step=0.001 s
    Simulation sim(180.0, 0.001, myRocket, earth);

    sim.runSimulation();

    sim.apogee();

    return 0;
}
