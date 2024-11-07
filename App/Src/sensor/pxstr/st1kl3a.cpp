#include "st1kl3a.hpp"

namespace sensor::pxstr{

	ST1KL3A::ST1KL3A(ADC_HandleTypeDef* hadc)
	 : val_(std::make_unique<state::Wall>()),
	 adc_(std::make_unique<peripheral::ADC>(hadc)) {}

	void ST1KL3A::Init(){

	}

	void ST1KL3A::ReadVal(){
		adc_->ReadVal();
		uint16_t* buff = adc_->get_val_ptr();
		val_->dir[static_cast<int>(state::Wall::DIR::R)] = buff[0];
		val_->dir[static_cast<int>(state::Wall::DIR::L)] = buff[1];
		val_->dir[static_cast<int>(state::Wall::DIR::FR)] = buff[2];
		val_->dir[static_cast<int>(state::Wall::DIR::FL)] = buff[3];
	}

	std::unique_ptr<state::Wall>& ST1KL3A::get_val_ref(){
		return val_;
	}

}
