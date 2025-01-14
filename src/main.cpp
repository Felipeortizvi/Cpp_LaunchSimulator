#include <iostream>
#include "Planet.h"
#include "Rocket.h"
#include "Simulation.h"

int main() {

    Planet selected_planet = Planet::selectPlanet();
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

    // Create the simulation (This is going to be standard, I may make this a constant actually)
    //    - final_time=180 s, time_step=0.001 s
    Simulation sim(180.0, 0.001, myRocket, selected_planet);

    sim.runSimulation();

    std::cout<<"===ENVIRONMENT VARIABLES==="<<std::endl;

    std::cout<<myRocket<<std::endl;
    std::cout<<std::endl;
    selected_planet.printDetails();
    std::cout<<std::endl;

    std::cout<< "====LAUNCH STATISTICS===="<<std::endl;
    sim.burnout();
    std::cout<<std::endl;
    sim.apogee();

    std::cout<<std::endl;
    sim.didEscapeOrbit();

    return 0;
}
