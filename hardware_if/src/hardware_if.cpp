#include "iugv/control/motor_control.hpp"

using namespace iugv::hardwareInterface::control;

int main(int argc, char * argv[]){
    
	rclcpp::init(argc, argv);
    
	gpioInitialise();    

	rclcpp::executors::MultiThreadedExecutor exe;

	std::shared_ptr<StepperMotorControl> smc = std::make_shared<StepperMotorControl>();
	exe.add_node(smc->get_node_base_interface());

	exe.spin();
	rclcpp::shutdown();
        
    return 0;
}