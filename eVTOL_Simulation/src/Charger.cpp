/**
 * @file Charger.cpp
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Charger.h"

// Initialize static class members
std::deque<std::shared_ptr<Vehicle>> Charger::_chargeQueue;

/**
 * @brief Queues the vehicle into the line of vehicles waiting to charge
 * 
 * @param vehicle 
 */
void Charger::enqueueVehicleWaiting(const std::shared_ptr<Vehicle> &vehicle) {
    if(vehicle) {
        Charger::_chargeQueue.push_back(vehicle);
    }
}

/**
 * @brief Removes the vehicle next in line of vehicles waiting to charge
 * 
 * @return std::shared_ptr<Vehicle> 
 */
std::shared_ptr<Vehicle> Charger::dequeueVehicleWaiting() {
    auto vehicle = Charger::_chargeQueue.front();
    Charger::_chargeQueue.pop_front();
    return vehicle;
}

/**
 * @brief Checks if the charge queue is empty
 * 
 * @return true 
 * @return false 
 */
bool Charger::isChargeQueueEmpty() {
    return _chargeQueue.empty();
}

void Charger::increaseTimeWaiting(long ms) {
    for(const auto &vehicle : _chargeQueue) {
        vehicle->addTimeAwaitingCharge(ms);
    }
}

/**
 * @brief Checks all vehicles in charging queue for faults
 * 
 */
void Charger::faultCheckQueue() {
    for(const auto &vehicle : _chargeQueue) {
        vehicle->faultCheck();
    }
}

/**
 * @brief Gets the current vehicle on the charger.
 * 
 * @return std::shared_ptr<Vehicle> 
 */
std::shared_ptr<Vehicle> Charger::getVehicleCharging() const {
    return _vehicleCharging;
}

/**
 * @brief Sets the current vehicle on the charger.
 * 
 * @param vehicle 
 */
void Charger::setVehicleCharging(const std::shared_ptr<Vehicle> &vehicle) {
    _vehicleCharging = vehicle;
}
