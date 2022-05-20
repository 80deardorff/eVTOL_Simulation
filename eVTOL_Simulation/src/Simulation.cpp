/**
 * @file Simulation.cpp
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "main.h"
#include "Simulation.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <thread>
#include <memory>
#include <chrono>

// Helper function prototypes
static void manageVehiclesFlying(std::vector<std::shared_ptr<Vehicle>> &vehiclesFlying);
static void manageChargers(std::vector<std::shared_ptr<Vehicle>> &vehiclesFlying, const std::vector<std::unique_ptr<Charger>> &chargers);

/**
 * @brief Starts the simulation engine
 * 
 * @param vehicles Vector of simulation vehicles
 * @param chargers Vector of simulation chargers
 * @param ms Length of the test in milliseconds @
 */
void Simulation::startSimulation(std::vector<std::shared_ptr<Vehicle>> &vehiclesFlying, const std::vector<std::unique_ptr<Charger>> &chargers, long ms) {
   
    _endTime = getCurrentTime() + ms;
    _currTime = getCurrentTime();

    // This sets an awake point for the next iteration of while loop. If the
    // simulation starts to lag behind, it will catch up and keep timing
    // calculations accurate.
    auto awakeTime = std::chrono::steady_clock::now();

    while(getTimeRemaining() > 0) {

        // Set awake time of next loop
        awakeTime += std::chrono::milliseconds(SIM_DELAY);
        
        // Print remaining time to terminal
        printRemainingTime();

        // Manage the vehicles flying
        manageVehiclesFlying(vehiclesFlying);

        // Manage the chargers
        manageChargers(vehiclesFlying, chargers);

        // Increase waiting time for vehicles in the charge queue
        Charger::increaseTimeWaiting(SIM_DELAY);

        // Check for vehicle faults in charge queue
        Charger::faultCheckQueue();

        // Not a busy sleep, will yield to other threads
        std::this_thread::sleep_until(awakeTime);
    }
    std::cout << "\n" << std::endl;
}

/*******************Private Member Methods***********************/
/**
 * @brief Get the current system time in milliseconds
 * 
 * @return long long 
 */
inline long long Simulation::getCurrentTime() {
    using namespace std::chrono;
    _currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return _currTime;
}

/**
 * @brief Get the time remaining for the simulation in milliseconds
 * 
 * @return long long 
 */
long long Simulation::getTimeRemaining() {
    return (_endTime - getCurrentTime() < 0) ? 0 : _endTime - getCurrentTime();
}

/**
 * @brief Prints the remaining time in the simulation to the console
 * 
 */
void Simulation::printRemainingTime() {
    long long ms = getTimeRemaining();
    int min = (int)MS_TO_SEC(ms) / 60;
    int sec = (int)MS_TO_SEC(ms) % 60;
    std::cout << '\r' << "Time remaining: "
        << std::setw(2) << std::setfill('0') << min << ':'
        << std::setw(2) << sec << std::flush;
}

/*******************Private Helper Functions***********************/
static void manageVehiclesFlying(std::vector<std::shared_ptr<Vehicle>> &vehiclesFlying) {

    // Run through vehicles flying and do the following:
    //  - Check battery soc
    //  - If 0% soc, send to charger queue
    //  - If battery still has charge, we will drain it by the rate spec of
    //    the vehicle and increase the total flight miles traveled
    for(auto it = vehiclesFlying.begin(); it != vehiclesFlying.end(); /*For loop update within the loop*/ ) {

        // Fault check vehicle
        (*it)->faultCheck();

        //Check battery SOC and push to charge queue if necessary
        if((*it)->getBattery()->getStateOfCharge() <= 0.0) {
            Charger::enqueueVehicleWaiting(*it);
#if DEBUG_MODE
                std::cout << (*it)->getName() << " queueing..." << std::endl;
#endif /* DEBUG_MODE*/

            // This deletes the current iterator as it will be a nullptr at
            // by now due to the use of unique_ptr being moved to the charger
            // queue
            it = vehiclesFlying.erase(it);
        }

        // Battery SOC is fine so drain battery and add flight distance and time
        else {
            // Add to total flight time and miles traveled
            (*it)->addTimeInFlight(SIM_DELAY);
            
            // Drain battery at rate for specific vehicle type
            (*it)->getBattery()->drainBattery(SIM_DELAY);
            it++;
        }   
    }
}

static void manageChargers(std::vector<std::shared_ptr<Vehicle>> &vehiclesFlying, const std::vector<std::unique_ptr<Charger>> &chargers) {

    // Run through the chargers and do the following
    //  - Get the vehicle on the charger
    //  - If no vehicle exists on the charger, check the queue and add
    //  - Check current vehicle on charger and see if it has full charge
    //   -- If so, remove it and put back in flying vehicle vector and grab the next vehicle from the charge queue
    //   -- If not, continue to charge it
    for(auto &charger : chargers) {

        // Get the vehicle on the charger
        auto vehicle = charger->getVehicleCharging();

        // If no vehicle on charger
        if(!vehicle) {
            if(Charger::isChargeQueueEmpty()) continue;
            else {
                vehicle = Charger::dequeueVehicleWaiting();
                charger->setVehicleCharging(vehicle);
#if DEBUG_MODE
                std::cout << vehicle->getName() << " charging..." << std::endl;
#endif /* DEBUG_MODE*/
            }
        }

        // Fault check vehicle
        vehicle->faultCheck();

        // Charger has vehicle and it is still charging
        if(vehicle->getBattery()->isCharging()) {
            vehicle->addTimeCharging(SIM_DELAY);
            continue;
        }

        // Charger has vehicle and it is charged
        else if(vehicle->getBattery()->getStateOfCharge() >= 100.0) {

            // Move vehicle off the charger and back into flying vehicles
            vehiclesFlying.push_back(std::move(vehicle));
            
            // Get next vehicle from charge queue
            if(Charger::isChargeQueueEmpty()) {
                charger->setVehicleCharging(nullptr);
                continue;
            }
            else {
                vehicle = Charger::dequeueVehicleWaiting();
                charger->setVehicleCharging(vehicle);
                vehicle->addTimeCharging(SIM_DELAY);
#if DEBUG_MODE
                std::cout << vehicle->getName() << " charging..." << std::endl;
#endif /* DEBUG_MODE*/
            }
        }

        // Charge the current vehicle on the charger
        vehicle->getBattery()->chargeBattery();
    }
}
