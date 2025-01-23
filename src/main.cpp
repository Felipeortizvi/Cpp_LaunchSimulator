#include <iostream>
#include "Planet.h"
#include "Rocket.h"
#include "Simulation.h"

int main() {

    std::cout<<"=====ROCKET LAUNCH SIMULATION====="<<"\n";

    Planet selected_planet = Planet::selectPlanet();
    std::cout<<std::endl;
    Rocket selected_rocket = Rocket::selectRocket();
 
    // Set the rocket's launch angle
    //    - In your Python: theta_0 = 75 deg
    selected_rocket.set_launch_angle();

    // Create the simulation (This is going to be standard, I may make this a constant actually)
    //    - final_time=180 s, time_step=0.001 s
    Simulation sim(selected_rocket, selected_planet);

    sim.runSimulation();

    std::cout<<"\n===ENVIRONMENT VARIABLES==="<<std::endl;

    std::cout<<std::endl;
    selected_planet.printDetails();
    std::cout<<std::endl;
    selected_rocket.printRocketDetails();

    std::cout<<std::endl;
    std::cout<< "====LAUNCH STATISTICS===="<<std::endl;
    sim.burnout();
    std::cout<<std::endl;
    sim.apogee();

    if (sim.didEscapeOrbit()) {std::cout << "\nCongratulations! The rocket escaped the planet's orbit.\n";}
    else {std::cout << "\nThe rocket failed to escape orbit. Try adjusting your design!\n";}

    return 0;
}
