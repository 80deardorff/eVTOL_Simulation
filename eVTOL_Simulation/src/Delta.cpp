/**
 * @file Delta.cpp
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"
#include "Delta.h"
#include <iostream>

// Initialize static class members
std::string Delta::_name = "Delta";
int Delta::_vehicleCount = 0;
double Delta::_timeInFlightHr = 0.0;
double Delta::_timeChargingHr = 0.0;
double Delta::_timeAwaitingChargeHr = 0.0;
int Delta::_faultCount = 0;
double Delta::_distanceAllPassengersMi = 0.0;

/**
 * @brief Constructs a new Delta Vehicle object with parameters from header
 * 
 */
Delta::Delta()
    : Vehicle(
        DELTA_BATTERY_CAPACITY,
        DELTA_TIME_TO_CHARGE,
        DELTA_CRUISE_SPEED,
        // The following line converts to energy used per millisecond of cruise
        (DELTA_ENERGY_USE_PER_MI * DELTA_CRUISE_SPEED / HR_TO_MS(1)),
        DELTA_PASSENGER_COUNT,
        DELTA_FAULT_PROBABILITY
    ) {
        _vehicleCount++;
}

/**
 * @brief Get the name of company vehicle 
 * 
 * @return string
 */
std::string Delta::getName() const {
    return _name;
}

/**
 * @brief Get the total number of company vehicle instances 
 * 
 * @return int 
 */
int Delta::getVehicleCount() const {
    return _vehicleCount;
}

/**
 * @brief Get the total time in flight of the company vehicles
 * @return hours as double
 */
double Delta::getTimeInFlight() const {
    return _timeInFlightHr;
}

/**
 * @brief Get the total time charging of the company vehicles
 * @return hours as double 
 */
double Delta::getTimeCharging() const {
    return _timeChargingHr;
}

/**
 * @brief Get the total time awaiting charge of the company vehicles
 * @return hours as double 
 */
double Delta::getTimeAwaitingCharge() const {
    return _timeAwaitingChargeHr;
}

/**
 * @brief Get the total fault of the company vehicles
 * @return faults as int 
 */
int Delta::getFaultCount() const {
    return _faultCount;
}

/**
 * @brief Get the total distance traveled of the company vehicles considering number of passengers and total miles traveled
 * @return miles as double 
 */
double Delta::getDistanceAllPassengers() const {
    return _distanceAllPassengersMi;
}

/**
 * @brief Adds time to total flight time for company vehicles and increases total distance traveled
 * @param ms Time in milliseconds to add
 */
void Delta::addTimeInFlight(long ms) const {
    if(ms > 0) {
        // Add flight time to company vehicle class
        _timeInFlightHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));

        // Increase distance traveled for company vehicle class
        _distanceAllPassengersMi += ((double)DELTA_PASSENGER_COUNT * DELTA_CRUISE_SPEED * TIME_SCALE_FACTOR * ms / HR_TO_MS(1));
    }
}

/**
 * @brief Adds time to the charging time for company vehicles
 * @param ms Time in milliseconds to add
 */
void Delta::addTimeCharging(long ms) const {
    if(ms > 0) {
        _timeChargingHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));
    }
}

/**
 * @brief Adds time to the awaiting charge time for company vehicles
 * @param ms Time in milliseconds to add
 */
void Delta::addTimeAwaitingCharge(long ms) const {
    if(ms > 0) {
       _timeAwaitingChargeHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));
    }
}

/**
 * @brief Triggers a fault
 */
void Delta::triggerFault() const{
    _faultCount++;
}

/**
 * @brief Prints the data of company vehicles
 */
void Delta::printData() {
    std::cout << "***Delta Vehicle Stats***\n" <<
        "Vehicle Count:  " << _vehicleCount << "\n" <<
        "Time Flying:    " << _timeInFlightHr << "\n" <<
        "Time Charging:  " << _timeChargingHr << "\n" <<
        "Time Waiting:   " << _timeAwaitingChargeHr << "\n" <<
        "Faults:         " << _faultCount << "\n" <<
        "Total Distance: " << _distanceAllPassengersMi << "\n";
}
