/**
 * @file Echo.cpp
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"
#include "Echo.h"
#include <iostream>

// Initialize static class members
std::string Echo::_name = "Echo";
int Echo::_vehicleCount = 0;
double Echo::_timeInFlightHr = 0.0;
double Echo::_timeChargingHr = 0.0;
double Echo::_timeAwaitingChargeHr = 0.0;
int Echo::_faultCount = 0;
double Echo::_distanceAllPassengersMi = 0.0;

/**
 * @brief Constructs a new Echo Vehicle object with parameters from header
 * 
 */
Echo::Echo()
    : Vehicle(
        ECHO_BATTERY_CAPACITY,
        ECHO_TIME_TO_CHARGE,
        ECHO_CRUISE_SPEED,
        // The following line converts to energy used per millisecond of cruise
        (ECHO_ENERGY_USE_PER_MI * ECHO_CRUISE_SPEED / HR_TO_MS(1)),
        ECHO_PASSENGER_COUNT,
        ECHO_FAULT_PROBABILITY
    ) {
        _vehicleCount++;
}

/**
 * @brief Get the name of company vehicle 
 * 
 * @return string
 */
std::string Echo::getName() const {
    return _name;
}

/**
 * @brief Get the total number of company vehicle instances 
 * 
 * @return int 
 */
int Echo::getVehicleCount() const {
    return _vehicleCount;
}

/**
 * @brief Get the total time in flight of the company vehicles
 * @return hours as double
 */
double Echo::getTimeInFlight() const {
    return _timeInFlightHr;
}

/**
 * @brief Get the total time charging of the company vehicles
 * @return hours as double 
 */
double Echo::getTimeCharging() const {
    return _timeChargingHr;
}

/**
 * @brief Get the total time awaiting charge of the company vehicles
 * @return hours as double 
 */
double Echo::getTimeAwaitingCharge() const {
    return _timeAwaitingChargeHr;
}

/**
 * @brief Get the total fault of the company vehicles
 * @return faults as int 
 */
int Echo::getFaultCount() const {
    return _faultCount;
}

/**
 * @brief Get the total distance traveled of the company vehicles considering number of passengers and total miles traveled
 * @return miles as double 
 */
double Echo::getDistanceAllPassengers() const {
    return _distanceAllPassengersMi;
}

/**
 * @brief Adds time to total flight time for company vehicles and increases total distance traveled
 * @param ms Time in milliseconds to add
 */
void Echo::addTimeInFlight(long ms) const {
    if(ms > 0) {
        // Add flight time to company vehicle class
        _timeInFlightHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));

        // Increase distance traveled for company vehicle class
        _distanceAllPassengersMi += ((double)ECHO_PASSENGER_COUNT * ECHO_CRUISE_SPEED * TIME_SCALE_FACTOR * ms / HR_TO_MS(1));
    }
}

/**
 * @brief Adds time to the charging time for company vehicles
 * @param ms Time in milliseconds to add
 */
void Echo::addTimeCharging(long ms) const {
    if(ms > 0) {
        _timeChargingHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));
    }
}

/**
 * @brief Adds time to the awaiting charge time for company vehicles
 * @param ms Time in milliseconds to add
 */
void Echo::addTimeAwaitingCharge(long ms) const {
    if(ms > 0) {
       _timeAwaitingChargeHr += (MS_TO_HR(ms * TIME_SCALE_FACTOR));
    }
}

/**
 * @brief Triggers a fault
 */
void Echo::triggerFault() const {
    _faultCount++;
}

/**
 * @brief Prints the data of company vehicles
 */
void Echo::printData() {
    std::cout << "***Echo Vehicle Stats***\n" <<
        "Vehicle Count:  " << _vehicleCount << "\n" <<
        "Time Flying:    " << _timeInFlightHr << "\n" <<
        "Time Charging:  " << _timeChargingHr << "\n" <<
        "Time Waiting:   " << _timeAwaitingChargeHr << "\n" <<
        "Faults:         " << _faultCount << "\n" <<
        "Total Distance: " << _distanceAllPassengersMi << "\n";
}
