#ifndef __HARDWARE_SETUP_HPP__
#define __HARDWARE_SETUP_HPP__

#include "third_party.hpp"
#include "iugv/hardware_definitions.hpp"

namespace iugv::hardwareInterface{

    void StepperSetupPins(){

        gpioSetMode(STEPPER_STEP, PI_OUTPUT);
        gpioSetMode(STEPPER_DIR, PI_OUTPUT);
        gpioSetMode(STEPPER_MS1, PI_OUTPUT);
        gpioSetMode(STEPPER_MS2, PI_OUTPUT);
        gpioSetMode(STEPPER_MS3, PI_OUTPUT);

        // Default Mode = 0
        gpioWrite(STEPPER_MS1, 0);
        gpioWrite(STEPPER_MS2, 0);
        gpioWrite(STEPPER_MS3, 0);

    }

    void StepperMode(
        const int& mode,
        double& stepper_step_angle
    ){
        if(mode==1){
            // Half Step
            gpioWrite(STEPPER_MS1, 1);
            gpioWrite(STEPPER_MS2, 0);
            gpioWrite(STEPPER_MS3, 0);
            stepper_step_angle=0.9;
        }
        else if(mode == 2){
            // Quarter Step
            gpioWrite(STEPPER_MS1, 0);
            gpioWrite(STEPPER_MS2, 1);
            gpioWrite(STEPPER_MS3, 0);
            stepper_step_angle=0.45;
        }
        else if(mode == 3){
            // Eighth Step
            gpioWrite(STEPPER_MS1, 1);
            gpioWrite(STEPPER_MS2, 1);
            gpioWrite(STEPPER_MS3, 0);
            stepper_step_angle=0.225;
        }
        else if(mode == 4){
            // Sixteenth Step
            gpioWrite(STEPPER_MS1, 1);
            gpioWrite(STEPPER_MS2, 1);
            gpioWrite(STEPPER_MS3, 1);
            stepper_step_angle=0.1125;
        }
        else{
            // Full Step; Mode 0
            gpioWrite(STEPPER_MS1, 0);
            gpioWrite(STEPPER_MS2, 0);
            gpioWrite(STEPPER_MS3, 0);
            stepper_step_angle=1.8;
        }
    }

}

#endif