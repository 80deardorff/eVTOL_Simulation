/**
 * @file Alpha.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ALPHA_H
#define ALPHA_H

#include "Vehicle.h"
#include <string>

// Vehicle specific parameters
constexpr int ALPHA_CRUISE_SPEED = 120;
constexpr int ALPHA_BATTERY_CAPACITY = 320;
constexpr double ALPHA_TIME_TO_CHARGE = 0.6;
constexpr double ALPHA_ENERGY_USE_PER_MI = 1.6;
constexpr int ALPHA_PASSENGER_COUNT = 4;
constexpr double ALPHA_FAULT_PROBABILITY = 0.25;

class Alpha : public Vehicle {
    private:
        static std::string _name;
        static int _vehicleCount;
        static double _timeInFlightHr;
        static double _timeChargingHr;
        static double _timeAwaitingChargeHr;
        static int _faultCount;
        static double _distanceAllPassengersMi;
    public:
        Alpha();
        ~Alpha() override = default;
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

#endif /* ALPHA_H */
