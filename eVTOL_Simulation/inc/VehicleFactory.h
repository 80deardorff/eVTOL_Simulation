/**
 * @file VehicleFactory.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H

#include <memory>
#include "Vehicle.h"

enum class VehicleType {
    ALPHA_TYPE,
    BETA_TYPE,
    CHARLIE_TYPE,
    DELTA_TYPE,
    ECHO_TYPE,
    NUM_OF_VEHICLE_TYPES
};

class VehicleFactory {
    public:
        std::shared_ptr<Vehicle> createVehicle(VehicleType vehicle) const;
};

#endif /* VEHICLE_FACTORY_H */
