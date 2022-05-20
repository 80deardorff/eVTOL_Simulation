/**
 * @file Vehicle.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef VEHICLE_H
#define VEHICLE_H

#include "Battery.h"
#include <memory>
#include <string>

class Vehicle {
    private:
        std::shared_ptr<Battery> _pBattery;
        int _cruiseSpeedMph;
        int _passengerCount;
        double _faultProbability;
    protected:
        virtual ~Vehicle() = default;
    public:
        Vehicle(int capacityKwh, double timeToChargeHr, int cruiseSpeedMph, double energyUseKwh, int passengerCount, double faultProbability);
        std::shared_ptr<Battery> getBattery() const;
        virtual std::string getName() const = 0;
        virtual int getVehicleCount() const = 0;
        virtual double getTimeInFlight() const = 0;
        virtual double getTimeCharging() const = 0;
        virtual double getTimeAwaitingCharge() const = 0;
        virtual int getFaultCount() const = 0;
        virtual double getDistanceAllPassengers() const = 0;
        virtual void addTimeInFlight(long ms) const = 0;
        virtual void addTimeCharging(long ms) const = 0;
        virtual void addTimeAwaitingCharge(long ms) const = 0;
        virtual void triggerFault() const = 0;
        int getCruiseSpeed() const;
        int getPassengerCount() const;
        double getFaultProbability() const;
        void faultCheck() const;
};

#endif /* VEHICLE_H */
