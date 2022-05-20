/**
 * @file Vehicle.cpp
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"
#include "Vehicle.h"
#include <chrono>
#include <random>
#include <cmath>

/**
 * @brief Construct a new Vehicle:: Vehicle object
 * 
 * @param capacityKwh Battery capacity parameter for Battery object
 * @param timeToChargeHr Battery time to charge parameter for Battery object
 * @param cruiseSpeedMph Cruise speed parameter for Vehicle object
 * @param energyUseKwh Energy usage parameter per millisecond of travel for Battery object
 * @param passengerCount Passenger count parameter for Vehicle object
 * @param faultProbability Fault probability parameter for Vehicle object
 */
Vehicle::Vehicle(int capacityKwh, double timeToChargeHr, int cruiseSpeedMph, double energyUseKwh, int passengerCount, double faultProbability)
    : _pBattery(std::make_shared<Battery>(capacityKwh, energyUseKwh, timeToChargeHr))
    , _cruiseSpeedMph{cruiseSpeedMph}
    , _passengerCount{passengerCount}
    , _faultProbability{faultProbability} {}

/**
 * @brief Get the Battery object
 * 
 * @return std::shared_ptr<Battery> 
 */
std::shared_ptr<Battery> Vehicle::getBattery() const {
    return _pBattery;
}

/**
 * @brief Get the Cruise Speed object
 * 
 * @return int Cruise speed in mph
 */
int Vehicle::getCruiseSpeed() const {
    return _cruiseSpeedMph;
}

/**
 * @brief Get the Passenger Count object
 * 
 * @return int Max number of passengers per vehicle
 */
int Vehicle::getPassengerCount() const {
    return _passengerCount;
}

/**
 * @brief Get the Fault Probability object
 * 
 * @return double Probability of fault between 0.0 and 1.0 per hour of use
 */
double Vehicle::getFaultProbability() const {
    return _faultProbability;
}

/**
 * @brief Check the vehicle for a fault based on fault probability
 * 
 */
void Vehicle::faultCheck() const {
    
    // Set random seed for current time and get max random value
    std::mt19937 mt((unsigned int) std::chrono::steady_clock::now().time_since_epoch().count());

    // Set max
    constexpr auto rand_max = (unsigned long)std::mt19937::max();

    // Randomize number for fault check between 0 and max
    auto random = (unsigned long)mt();


    // Number of checks per hour in real time (1 min in simulation)
    int numChecks = HR_TO_MS(1) / SIM_DELAY;

    // Gets probability per loop iteration based on an hour
    double probPerIteration = 1.0 - pow(getFaultProbability(), 1.0/numChecks);


    // Set threshold per specific vehicle fault probability rate
    auto threshold = (unsigned long)(rand_max * probPerIteration);
    
    // Check if random number falls below threshold for specific vehicle
    if(random < threshold) {
        triggerFault();
    }
}
