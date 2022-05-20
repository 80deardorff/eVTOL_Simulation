/**
 * @file main.h
 * @author Adrian Deardorff (80deardorff@gmail.com)
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MAIN_H
#define MAIN_H

// Simulation configurations - modify as necessary
#define NUM_OF_TEST_VEHICLES    20UL    // Number of test vehicles
#define NUM_OF_CHARGERS         3UL     // Number of available chargers
#define TEST_LENGTH_MIN         3UL     // Length of simulation in minutes
#define TIME_SCALE_FACTOR       60UL    // Scales the sim to real time 1min=1hr

// Utility defines
#define MS_TO_HR(ms)            (((double)ms) / 1000UL / 60UL / 60UL)
#define MS_TO_SEC(ms)           (((double)ms) / 1000UL)
#define HR_TO_MS(hr)            ((long)((hr) * 1000UL * 60UL * 60UL))
#define TEST_LENGTH_MS          (TEST_LENGTH_MIN * (1000UL * 60UL))
#define SIM_DELAY               10  // In ms; modify if needed for tuning
#define ENABLE                  1
#define DISABLE                 0

// Debug mode allows debug code to be ran
#define DEBUG_MODE              0

#endif /* MAIN_H */
