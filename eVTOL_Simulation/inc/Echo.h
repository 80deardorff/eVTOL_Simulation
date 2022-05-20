/**
 * @file Echo.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ECHO_H
#define ECHO_H

#include "Vehicle.h"
#include <string>

// Simulation configurations
constexpr int ECHO_CRUISE_SPEED = 30;
constexpr int ECHO_BATTERY_CAPACITY = 150;
constexpr double ECHO_TIME_TO_CHARGE = 0.3;
constexpr double ECHO_ENERGY_USE_PER_MI = 5.8;
constexpr int ECHO_PASSENGER_COUNT = 2;
constexpr double ECHO_FAULT_PROBABILITY = 0.61;

class Echo : public Vehicle {
    private:
        static std::string _name;
        static int _vehicleCount;
        static double _timeInFlightHr;
        static double _timeChargingHr;
        static double _timeAwaitingChargeHr;
        static int _faultCount;
        static double _distanceAllPassengersMi;
    public:
        Echo();
        ~Echo() override = default;
        std::string getName() const override;
        int getVehicleCount() const override;
        double getTimeInFlight() const override;
        double getTimeCharging() const override;
        double getTimeAwaitingCharge() const override;
        int getFaultCount() const override;
        double getDistanceAllPassengers() const override;
        void addTimeInFlight(long ms) const override;
        void addTimeCharging(long ms) const override;
        void addTimeAwaitingCharge(long ms) const override;
        void triggerFault() const override;
        static void printData();
};

#endif /* ECHO_H */
