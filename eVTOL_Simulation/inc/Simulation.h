/**
 * @file Simulation.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vehicle.h"
#include "Charger.h"
#include <memory>
#include <vector>

class Simulation {
    private:
        long long _currTime;
        long long _endTime;
        long long getCurrentTime();
        long long getTimeRemaining();
        void printRemainingTime();
    public:
        void startSimulation(
            std::vector<std::shared_ptr<Vehicle>> &vehiclesFlying,
            const std::vector<std::unique_ptr<Charger>> &chargers, 
            long ms);
};

#endif /* SIMULATION_H */
