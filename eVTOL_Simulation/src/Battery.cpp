/**
 * @file Battery.cpp
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"
#include "Battery.h"
#include <thread>
#include <chrono>
#include <iostream>

/**
 * @brief Construct a new Battery:: Battery object
 * 
 * @param capacityKwh Battery capacity parameter for Battery object
 * @param energyUseKwh Energy usage parameter per millisecond of travel for Battery object
 * @param timeToChargeHr Battery time to charge parameter for Battery object
 */
Battery::Battery(int capacityKwh, double energyUse, double timeToChargeHr)
    : _capacityKwh{capacityKwh}
    , _currChargeKwh{(double)capacityKwh}
    , _energyUseKwh{energyUse}
    , _timeToChargeHr{timeToChargeHr} {}

/**
 * @brief Get the capacity of the battery object
 * 
 * @return int Max capacity of the battery in kWh
 */
int Battery::getCapacity() const {
    return _capacityKwh;
}

/**
 * @brief Gets the current state of charge of the battery object
 * 
 * @return double State of charge from 0.0 to 100.0
 */
double Battery::getStateOfCharge() const {
    return _stateOfCharge;
}

/**
 * @brief Get the energy use of the vehicle
 * 
 * @return double Energy use in kWh per millisecond of travel at cruise speed
 */
double Battery::getEnergyUse() const {
 return _energyUseKwh;
}

/**
 * @brief Gets the charge time of the battery object
 * 
 * @return double Charge time from 0% to 100% capacity in hours
 */
double Battery::getTimeToChargeHr() const {
    return _timeToChargeHr;
}

/**
 * @brief Starts the draining of the battery until empty
 * 
 */
void Battery::drainBattery(long ms) {
    double amount = _energyUseKwh * ms * TIME_SCALE_FACTOR;

    // Checks for negative; otherwise subtracts amount calculated for time given
    _currChargeKwh = (_currChargeKwh - amount < 0.0) ? 
        0.0 :
        _currChargeKwh - amount;
    this->setStateOfCharge();
}

/**
 * @brief Starts the charging of the battery until full
 * 
 */
void Battery::chargeBattery() {
    // Check if vehicle is already charging or it is 100% soc
    if(isCharging() || _stateOfCharge == 100.0) return;
    
    // Set the charging state
    setCharging(ENABLE);

    // Create and run thread for charging
    std::thread t([this]() {

        // Get rate of charger for current battery pack
        double rate = (double)getCapacity() / HR_TO_MS(getTimeToChargeHr()) * TIME_SCALE_FACTOR * SIM_DELAY;

        // This sets an awake point for the next iteration of while loop. If the
        // simulation starts to lag behind, it will catch up and keep timing
        // calculations accurate.
        auto awakeTime = std::chrono::steady_clock::now();

        // Run loop and charge the battery based on rate until full
        while(getStateOfCharge() < 100.0) {
            
            // Set awake time of next loop
            awakeTime += std::chrono::milliseconds(SIM_DELAY);

            // Increase charge per rate (taking into account the loop wait period)
            _currChargeKwh += rate;

            // Update state of charge
            setStateOfCharge();

            // Not a busy sleep, will yield to other threads
            std::this_thread::sleep_until(awakeTime);
        }

        // Set charge state as not charging
        setCharging(DISABLE);
    });

    // Detach the thread to run in the background on its own
    // TODO as improvement later would be to use jthread in C++20 instead of
    // detaching. This way, we can ensure the thread operates correctly in the
    // background. 
    t.detach();
}

/**
 * @brief Check for if vehicle is charging
 * 
 * @return true 
 * @return false 
 */
bool Battery::isCharging() const {
    return _charging;
}

/**
 * @brief Sets the state of charging for the battery
 * 
 * @param EnOrDi @main.h for macro ENABLE or DISABLE
 */
void Battery::setCharging(int EnOrDi) {
    if(EnOrDi && _stateOfCharge < 100.0) _charging = true;
    else _charging = false;
}

/*******************Private Member Methods***********************/
/**
 * @brief Set the state of charge for the battery object
 * 
 */
void Battery::setStateOfCharge() {
    double currentState = _currChargeKwh / _capacityKwh * 100.0;
    if(currentState > 100.0) _stateOfCharge = 100.0;
    else if(currentState < 0) _stateOfCharge = 0.0;
    else _stateOfCharge = currentState;
}
