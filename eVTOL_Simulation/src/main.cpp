/**
 * @file main.cpp
 * @brief The following program runs the eVTOL simulation
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <thread>
#include "Vehicle.h"
#include "VehicleFactory.h"
#include "Simulation.h"
#include "Charger.h"
#include "Alpha.h"
#include "Beta.h"
#include "Charlie.h"
#include "Delta.h"
#include "Echo.h"

int main(void) {

    // Create a simulation instance
    Simulation sim;
    
    // Create vehicle factory instance
    VehicleFactory factory;

    // Create vector that holds all vehicles instance addresses
    std::vector<std::shared_ptr<Vehicle>> vehiclesFlying;

    // Cast strongly typed enum for readability
    auto numOfVehicleTypes = (size_t)VehicleType::NUM_OF_VEHICLE_TYPES;

    // Push at least one of every vehicle type to the vector
    for (size_t i = 0; i < numOfVehicleTypes; i++) {
        vehiclesFlying.push_back(factory.createVehicle((VehicleType)i));
    }

    // Randomly choose vehicles to create and push to vector up to max vehicles
    // number of vehicles for the test
    std::mt19937 mt((unsigned) time(nullptr));
    for (size_t i = numOfVehicleTypes; i < NUM_OF_TEST_VEHICLES; i++) {
        // Get a random number between 0(inc) and number(exc) of enum types
        int random = mt() % numOfVehicleTypes;
        vehiclesFlying.push_back(factory.createVehicle((VehicleType)random));
    }

    // Create vector that holds all charger instance addresses
    std::vector<std::unique_ptr<Charger>> chargers;

    // Create chargers and push to vector
    for (size_t i = 0; i < NUM_OF_CHARGERS; i++) {
        chargers.push_back(std::make_unique<Charger>());
    }

    // Start the simulation
    sim.startSimulation(vehiclesFlying, chargers, TEST_LENGTH_MS);

    // Print all data from each vehicle company to the terminal
    std::cout << "Test Results for " << TEST_LENGTH_MIN <<
    " MIN\n(" << TEST_LENGTH_MIN << " HR of Real Time)" << 
    std::endl;

    std::cout << "\n";
    Alpha::printData();
    std::cout << "\n";
    Beta::printData();
    std::cout << "\n";
    Charlie::printData();
    std::cout << "\n";
    Delta::printData();
    std::cout << "\n";
    Echo::printData();

    return 0;
}
