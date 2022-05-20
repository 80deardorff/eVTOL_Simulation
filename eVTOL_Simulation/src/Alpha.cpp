/**
 * @file Alpha.cpp
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"
#include "Alpha.h"
#include <iostream>

// Initialize static class members
std::string Alpha::_name = "Alpha";
int Alpha::_vehicleCount = 0;
double Alpha::_timeInFlightHr = 0.0;
double Alpha::_timeChargingHr = 0.0;
double Alpha::_timeAwaitingChargeHr = 0.0;
int Alpha::_faultCount = 0;
double Alpha::_distanceAllPassengersMi = 0.0;

/**
 * @brief Constructs a new Alpha Vehicle object with parameters from header
 * 
 */
Alpha::Alpha()
    : Vehicle(
        ALPHA_BATTERY_CAPACITY,
        ALPHA_TIME_TO_CHARGE,
        ALPHA_CRUISE_SPEED,
        // The following line converts to energy used per millisecond of cruise
        (ALPHA_ENERGY_USE_PER_MI * ALPHA_CRUISE_SPEED / HR_TO_MS(1)),
        ALPHA_PASSENGER_COUNT,
        ALPHA_FAULT_PROBABILITY
    ) {
        _vehicleCount++;
}

/**
 * @brief Get the name of company vehicle 
 * 
 * @return string
 */
std::string Alpha::getName() const {
    return _name;
}

/**
 * @brief Get the total number of company vehicle instances 
 * 
 * @return int 
 */
int Alpha::getVehicleCount() const {
    return _vehicleCount;
}

/**
 * @brief Get the total time in flight of the company vehicles
 * @return hours as double
 */
double Alpha::getTimeInFlight() const {
    return _timeInFlightHr;
}

/**
 * @brief Get the total time charging of the company vehicles
 * @return hours as double 
 */
double Alpha::getTimeCharging() const {
    return _timeChargingHr;
}

/**
 * @brief Get the total time awaiting charge of the company vehicles
 * @return hours as double 
 */
double Alpha::getTimeAwaitingCharge() const {
    return _timeAwaitingChargeHr;
}

/**
 * @brief Get the total fault of the company vehicles
 * @return faults as int 
 */
int Alpha::getFaultCount() const {
    return _faultCount;
}

/**
 * @brief Get the total distance traveled of the company vehicles considering number of passengers and total miles traveled
 * @return miles as double 
 */
double Alpha::getDistanceAllPassengers() const {
    return _distanceAllPassengersMi;
}

/**
 * @brief Adds time to total flight time for company vehicles and increases total distance traveled
 * @param ms Time in milliseconds to add
 */
void Alpha::addTimeInFlight(long ms) const {
    if(ms > 0) {
        // Add flight time to company vehicle class
        _timeInFlightHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));

        // Increase distance traveled for company vehicle class
        _distanceAllPassengersMi += ((double)ALPHA_PASSENGER_COUNT * ALPHA_CRUISE_SPEED * TIME_SCALE_FACTOR * ms / HR_TO_MS(1));
    }
}

/**
 * @brief Adds time to the charging time for company vehicles
 * @param ms Time in milliseconds to add
 */
void Alpha::addTimeCharging(long ms) const {
    if(ms > 0) {
        _timeChargingHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));
    }
}

/**
 * @brief Adds time to the awaiting charge time for company vehicles
 * @param ms Time in milliseconds to add
 */
void Alpha::addTimeAwaitingCharge(long ms) const {
    if(ms > 0) {
       _timeAwaitingChargeHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));
    }
}

/**
 * @brief Triggers a fault
 */
void Alpha::triggerFault() const {
    _faultCount++;
}

/**
 * @brief Prints the data of company vehicles
 */
void Alpha::printData() {
    std::cout << "***Alpha Vehicle Stats***\n" <<
        "Vehicle Count:  " << _vehicleCount << "\n" <<
        "Time Flying:    " << _timeInFlightHr << "\n" <<
        "Time Charging:  " << _timeChargingHr << "\n" <<
        "Time Waiting:   " << _timeAwaitingChargeHr << "\n" <<
        "Faults:         " << _faultCount << "\n" <<
        "Total Distance: " << _distanceAllPassengersMi << "\n";
}
