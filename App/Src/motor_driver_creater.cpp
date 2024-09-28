#include "motor_driver_creater.hpp"

namespace motor_driver{
	Creater::Creater(){
		name_ = MOTORDRIVER_NAME::TB6612FNG;
	}
	std::unique_ptr<Product> Creater::Create(){
		std::unique_ptr<Product> motor_driver;
		switch(name_){
			case MOTORDRIVER_NAME::TB6612FNG:
				motor_driver = std::make_unique<TB6612FNG>();
				return motor_driver;
			default:
				return nullptr;
		}
	}
}
