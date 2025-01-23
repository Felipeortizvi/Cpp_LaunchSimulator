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
    Rocket esa_rocket("TestRocket", 19.765, 11.269,
                    2501.8, 6.09,
                    1.081e-2, 0.51);

    //Rocket starship("Starship", 1200000.0, 120000.0, 16000000.0, 200.0, 22.0, 0.25); Realistic variables
    Rocket starship("Starship", 1000000.0, 100000.0, 30000000.0, 250.0, 18.0, 0.2); // Fake variables


    Rocket mediumEscapeRocket(
        "MediumEscapeRocket",
        /* wet_mass    */ 5000.0,     // 5 tonnes
        /* dry_mass    */ 500.0,      // 0.5 tonnes
        /* thrust      */ 500000.0,   // 500 kN
        /* burn_time   */ 180.0,      // 180 seconds
        /* frontalArea */ 1.0,        // 1 m^2
        /* Cd          */ 0.3         // drag coefficient
    );

    Rocket highThrustEscape(
    "HighThrustEscape",
    /* wet_mass    */ 100000.0,    // 100 tonnes
    /* dry_mass    */ 10000.0,     // 10 tonnes
    /* thrust      */ 1.0e7,       // 10,000,000 N (10 MN)
    /* burn_time   */ 180.0,       // 180 seconds
    /* frontalArea */ 3.0,         // 3 m^2
    /* Cd          */ 0.15         // drag coefficient
    );

    Rocket extremeEscape(
        "ExtremeEscape",
        /* wet_mass    */ 80000.0,     // 80 tonnes
        /* dry_mass    */ 5000.0,      // 5 tonnes (mass ratio = 16:1)
        /* thrust      */ 2.0e7,       // 20,000,000 N (20 MN)
        /* burn_time   */ 120.0,       // 120 seconds
        /* frontalArea */ 2.0,         // 2 m^2 cross-section
        /* Cd          */ 0.1          // very low drag coefficient
    );
    Rocket& selected_rocket = bigEscapeRocket; // We are creating a reference

    // 3) Set the rocket's launch angle
    //    - In your Python: theta_0 = 75 deg
    selected_rocket.set_launch_angle();

    // Create the simulation (This is going to be standard, I may make this a constant actually)
    //    - final_time=180 s, time_step=0.001 s
    Simulation sim(180.0, 0.001, selected_rocket, selected_planet);

    sim.runSimulation();

    std::cout<<"\n===ENVIRONMENT VARIABLES==="<<std::endl;

    std::cout<<selected_rocket<<std::endl;
    std::cout<<std::endl;
    selected_planet.printDetails();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<< "====LAUNCH STATISTICS===="<<std::endl;
    sim.burnout();
    std::cout<<std::endl;
    sim.apogee();

    if (sim.didEscapeOrbit()) {
        std::cout << "\nCongratulations! The rocket escaped the planet's orbit.\n";
    }
    else {
        std::cout << "\nThe rocket failed to escape orbit. Try adjusting your design!\n";
    }

    return 0;
}
