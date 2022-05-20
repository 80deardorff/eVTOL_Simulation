/**
 * @file Beta.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BETA_H
#define BETA_H

#include "Vehicle.h"
#include <string>

// Vehicle specific parameters
constexpr int BETA_CRUISE_SPEED = 100;
constexpr int BETA_BATTERY_CAPACITY = 100;
constexpr double BETA_TIME_TO_CHARGE = 0.2;
constexpr double BETA_ENERGY_USE_PER_MI = 1.5;
constexpr int BETA_PASSENGER_COUNT = 5;
constexpr double BETA_FAULT_PROBABILITY = 0.10;

class Beta : public Vehicle {
    private:
        static std::string _name;
        static int _vehicleCount;
        static double _timeInFlightHr;
        static double _timeChargingHr;
        static double _timeAwaitingChargeHr;
        static int _faultCount;
        static double _distanceAllPassengersMi;
    public:
        Beta();
        ~Beta() override = default;
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

#endif /* BETA_H */
