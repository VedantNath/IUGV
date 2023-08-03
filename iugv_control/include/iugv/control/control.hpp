#ifndef __CONTROL_HPP__
#define __CONTROL_HPP__

#include <memory>
#include <cmath>

namespace iugv::control {

    // PID Based Controller
    template<typename T>
    class Controller{

        public:

            Controller(
                const T& kp, const T& kd, const T& ki,
                const T* output, const T* state, const T* reference,
                const T& smoothness, const T& windup, const T& upper,
                const T& lower
            ) : m_kp(kp), m_kd(kd), m_ki(ki), 
            m_output(output), 
            m_state(state), 
            m_reference(reference), 
            m_smoothness(smoothness),
            m_windup(windup),
            m_upper(upper),
            m_lower(lower),
            m_previous_error(0),
            m_sum(0){}

            void Step(){
                // Calculate error
                T error = *(m_reference) - *(m_state);
                // Proportional error
                *(m_output) = kp*error;
                // Differential error with high frequiencies smoothened out
                DifferentialFilter(error);    
                // Integral error with tanh windup scheme
                WindupScheme(error);
                // Output Clamped under limits
                *(m_output) = *(m_output)(*(m_output) > m_lower && *(m_output) < m_upper) +
                    m_upper(*(m_output) > m_upper) + m_lower(*(m_output) < m_lower);
            }

            void DifferentialFilter(const T& error){
                *(m_output) += m_kd*((1-m_smoothness)*m_previous_error \
                    + m_smoothness*error);
            }

            void WindupScheme(const T& error){
                m_sum = (m_windup*tanh(m_sum/m_windup));
                *(m_output) += m_ki*m_sum;
            }

        protected:

            T* m_output, m_state, m_reference;
            T m_kp, m_kd, m_ki;
            T m_smoothness, m_windup;
            T m_upper, m_lower;

        private:

            T m_previous_error, m_sum;

    };

    Controller<double> controller_double;
    Controller<float> controller_float;

    // Class is modelled around A4988 stepper motor driver
    template<typename T>
    class StepperControl{
        
        public:
            
            StepperControl(const T* reference) : m_state(0), m_step(0), m_speed(0) 
            {}

            void SetStepPrecision(int PrecisionState){
                
                /*
                * There are 5 states this can exist in,
                * 1) Full Step => PrecisionState = 0
                * 2) Half Step => PrecisionState = 1
                * 3) Quarter Step => PrecisionState = 2
                * 4) Eighth Step => PrecisionState = 3
                * 5) Sixteenth Step => PrecisionState = 4
                */

                m_step = PrecisionState*(0<=PrecisionState<5);
            }

        protected:

            int m_step;
            T m_state, m_speed;
            T* m_reference;

    };

    StepperControl<double> stepper_double;
    StepperControl<float> stepper_float;

} // iugv::control

#endif