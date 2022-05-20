/**
 * @file Battery.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BATTERY_H
#define BATTERY_H

class Battery {
    private:
        int _capacityKwh;
        double _currChargeKwh;
        double _energyUseKwh;
        double _stateOfCharge = 100.0;
        double _timeToChargeHr;
        bool _charging = false;

        void setStateOfCharge();
    public:
        Battery(int capacityKwh, double energyUse, double timeToChargeHr);
        int getCapacity() const;
        double getStateOfCharge() const;
        double getEnergyUse() const;
        double getTimeToChargeHr() const;
        void drainBattery(long ms);
        void chargeBattery();
        bool isCharging() const;
        void setCharging(int EnOrDi);
};

#endif /* BATTERY_H */
