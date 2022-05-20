/**
 * @file VehicleFactory.cpp
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "VehicleFactory.h"
#include "Alpha.h"
#include "Beta.h"
#include "Charlie.h"
#include "Delta.h"
#include "Echo.h"

/**
 * @brief Creates a smart pointer for Vehicle object
 * 
 * @param vehicle
 * @return std::shared_ptr<Vehicle>
 */
std::shared_ptr<Vehicle> VehicleFactory::createVehicle(VehicleType vehicleType) const {

    std::shared_ptr<Vehicle> newVehicle;

    switch (vehicleType) {
        case VehicleType::ALPHA_TYPE:
            newVehicle = std::make_shared<Alpha>();
            break;
        case VehicleType::BETA_TYPE:
            newVehicle = std::make_shared<Beta>();
            break;
        case VehicleType::CHARLIE_TYPE:
            newVehicle = std::make_shared<Charlie>();
            break;
        case VehicleType::DELTA_TYPE:
            newVehicle = std::make_shared<Delta>();
            break;
        case VehicleType::ECHO_TYPE:
            newVehicle = std::make_shared<Echo>();
            break;
        default:
        break;
    }

    return newVehicle;
}