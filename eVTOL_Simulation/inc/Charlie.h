/**
 * @file Charlie.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CHARLIE_H
#define CHARLIE_H

#include "Vehicle.h"
#include <string>

// Vehicle specific parameters
constexpr int CHARLIE_CRUISE_SPEED = 160;
constexpr int CHARLIE_BATTERY_CAPACITY = 220;
constexpr double CHARLIE_TIME_TO_CHARGE = 0.8;
constexpr double CHARLIE_ENERGY_USE_PER_MI = 2.2;
constexpr int CHARLIE_PASSENGER_COUNT = 3;
constexpr double CHARLIE_FAULT_PROBABILITY = 0.05;

class Charlie : public Vehicle {
    private:
        static std::string _name;
        static int _vehicleCount;
        static double _timeInFlightHr;
        static double _timeChargingHr;
        static double _timeAwaitingChargeHr;
        static int _faultCount;
        static double _distanceAllPassengersMi;
    public:
        Charlie();
        ~Charlie() override = default;
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

#endif /* CHARLIE_H */
