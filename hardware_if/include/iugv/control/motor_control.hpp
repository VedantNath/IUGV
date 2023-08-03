#ifndef __MOTOR_CONTROL_HPP__
#define __MOTOR_CONTROL_HPP__

#include "iugv/hardware_setup.hpp"

namespace iugv::hardwareInterface::control{

    class StepperMotorControl : public rclcpp::Node{
        public:
            
            StepperMotorControl() : Node("StepperMotorControl"), m_stepper_current_angle(0){

                StepperSetupPins();

                m_server = create_service<iugv_interfaces::srv::Stepper>(
                    "/iugv/set_stepper_angle", 
                    std::bind(&StepperMotorControl::ServiceHandler, this, 
                        std::placeholders::_1, std::placeholders::_2)
                );

            }

            ~StepperMotorControl(){
                gpioWrite(STEPPER_STEP, 0);
            }

            void ServiceHandler(
                const std::shared_ptr<iugv_interfaces::srv::Stepper::Request>& request,
                const std::shared_ptr<iugv_interfaces::srv::Stepper::Response>& response
            ){
                m_stepper_angle = (double)request->angle;
                SetStepperMode(request->mode);
                SetStepperSpeed(request->speed);
                m_stepper_direction = request->dir;
                response->result = RunStepper();
            }

            bool RunStepper(){

                gpioWrite(STEPPER_DIR, m_stepper_direction);

                uint32_t delay = (uint32_t)(1/m_stepper_speed)*1000000;

                double error = abs(m_stepper_angle) - abs(m_stepper_current_angle);
                
                int steps = (int)floor(error/m_stepper_step_angle);

                for(int i=0; i < steps; i++)
                {
                    gpioWrite(STEPPER_STEP, 1);
                    gpioDelay(delay);
                    gpioWrite(STEPPER_STEP, 0);
                    gpioDelay(delay);

                    m_stepper_current_angle += m_stepper_step_angle;
                }
                
                return true;
            }

            void SetStepperMode(int mode){
                StepperMode(mode, m_stepper_step_angle);
            }

            void SetStepperSpeed(int speed){
                m_stepper_speed = speed*(speed>0);
                if(m_stepper_speed > STEPPER_SPM_UPPER){
                    m_stepper_speed = STEPPER_SPM_UPPER;
                }
            }

        protected:
            // stepper_speed = speed at which stepper_current_angle becomes stepper_angle
            // Units: stepper_speed = steps per second
            double m_stepper_current_angle, m_stepper_angle;
            double m_stepper_step_angle;
            int m_stepper_mode, m_stepper_speed;
            bool m_stepper_direction;

        private:
            rclcpp::Service<iugv_interfaces::srv::Stepper>::SharedPtr m_server;
    };

} // hardwareInterface::control

#endif