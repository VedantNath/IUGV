#ifndef __DIFFERENTIAL_DRIVE_HPP__
#define __DIFFERENTIAL_DRIVER_HPP__

#include <assert.h> 

namespace iugv::models{
    
    template<typename T>
    class DifferentialDrive
    {
        public:

            // Initialize with wheel radius and base length
            DifferentialDrive(const T& wheel_radius, const T& base_length){
                assert(wheel_radius > 0 && base_length > 0);

                m_wheel_radius = wheel_radius;
                m_base_length = base_length;
            }

            // Gets and sets of internal parameters. Not good practice to expose parameters, hence indirect API.

            void SetWheelRadius(const T& wheel_radius){m_wheel_radius = wheel_radius;}

            void SetBaseLength(const T& base_length){m_base_length = base_length;}

            T GetWheelRadius(){return m_wheel_radius;}

            T GetBaseLength(){return m_base_length;}

            // Given, V_{l,r} give v, w.

            T GetVehicleLinearVelocity(){return m_linear_velocity;}

            T GetVehicleAngularVelocity(){return m_angular_velocity;}

            void SetVehicleVelocities(const T& left_wheel_velocity, const T& right_wheel_velocity){

                m_left_wheel_velocity = left_wheel_velocity;

                m_right_wheel_velocity = right_wheel_velocity;

                m_linear_velocity = m_wheel_radius*0.5* \
                    (left_wheel_velocity + right_wheel_velocity);
                
                m_angular_velocity = (m_wheel_radius/m_base_length)* \
                    (left_wheel_velocity - right_wheel_velocity);
            }

            void SetWheelVelocities(const T& linear_velocity, const T& angular_velocity){

                m_linear_velocity = linear_velocity;

                m_angular_velocity = angular_velocity;

                T temp = (1/(2*m_wheel_radius));

                m_left_wheel_velocity = (2*linear_velocity + m_base_length*angular_velocity)*temp;

                m_right_wheel_velocity = (2*linear_velocity - m_base_length*angular_velocity)*temp;

            }

        protected:
            // Parameters
            T m_left_wheel_velocity, m_right_wheel_velocity;
            T m_wheel_radius, m_base_length;
            T m_linear_velocity, m_angular_velocity;
    };

    // Explicit Template Specialization, Acceptable Types:
    DifferentialDrive<double> diff_drive_model_double;
    DifferentialDrive<float> diff_drive_model_float;

} // models

#endif