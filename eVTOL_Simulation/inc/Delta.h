/**
 * @file Delta.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DELTA_H
#define DELTA_H

#include "Vehicle.h"
#include <string>

// Vehicle specific parameters
constexpr int DELTA_CRUISE_SPEED = 90;
constexpr int DELTA_BATTERY_CAPACITY = 120;
constexpr double DELTA_TIME_TO_CHARGE = 0.62;
constexpr double DELTA_ENERGY_USE_PER_MI = 0.8;
constexpr int DELTA_PASSENGER_COUNT = 2;
constexpr double DELTA_FAULT_PROBABILITY = 0.22;

class Delta : public Vehicle {
    private:
        static std::string _name;
        static int _vehicleCount;
        static double _timeInFlightHr;
        static double _timeChargingHr;
        static double _timeAwaitingChargeHr;
        static int _faultCount;
        static double _distanceAllPassengersMi;
    public:
        Delta();
        ~Delta() override = default;
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

#endif /* DELTA_H */
