/**
 * @file Charger.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CHARGER_H
#define CHARGER_H

#include <deque>
#include <memory>
#include "Vehicle.h"

class Charger {
    private:
        static std::deque<std::shared_ptr<Vehicle>> _chargeQueue;
        std::shared_ptr<Vehicle> _vehicleCharging = nullptr;
    public:
        static void enqueueVehicleWaiting(const std::shared_ptr<Vehicle> &vehicle);
        static std::shared_ptr<Vehicle> dequeueVehicleWaiting();
        static bool isChargeQueueEmpty();
        static void increaseTimeWaiting(long ms);
        static void faultCheckQueue();
        std::shared_ptr<Vehicle> getVehicleCharging() const;
        void setVehicleCharging(const std::shared_ptr<Vehicle> &vehicle);
};

#endif /* CHARGER_H */
