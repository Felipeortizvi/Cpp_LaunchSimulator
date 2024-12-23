#include "Rocket.h"
#include "Planet.h"
#include "Simulation.h"
#include <iostream>

using namespace std;

int main() {
    // Create a Planet object for Earth
    Planet earth("Earth", 9.81, 1.225);  // Earth's gravity and air density at sea level
    Rocket myRocket("Aries", 19.765, 11.269, 2501.8, 6.09, 1.081e-2, 0.51);


    int time = 60;              // Elapsed time [s]
    double altitude = 10000;    // Altitude in meters
    double velocity = 250;      // Velocity [m/s]
    double velocity_i = 150;    // Velocity in the direction of motion [m/s]

    cout << myRocket.rocket_mass(time) << " kg after "<< time<< " seconds."<< endl;

    myRocket.rocket_launch_angle(75);  // Set the launch angle

    cout << "Launch angle in radians: " << myRocket.get_launch_angle() << endl;

    // Call rocket_thrust_x_y to print thrust_x and thrust_y
    myRocket.rocket_thrust_x_y();

    Simulation sim(180.0, 0.001, myRocket, earth);

    sim.apogee();


    return 0;
}