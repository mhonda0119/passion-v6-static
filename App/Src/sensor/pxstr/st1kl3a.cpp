#include "st1kl3a.hpp"

namespace sensor::pxstr{

	ST1KL3A::ST1KL3A(ADC_HandleTypeDef* hadc)
	 : pxstr_(std::make_unique<parameter::Wall>()),
	 adc_(std::make_unique<peripheral::ADC>(hadc)) {}

	void ST1KL3A::Init(){

	}

	void ST1KL3A::ReadVal(){
		adc_->ReadVal();
		uint16_t* buff = adc_->get_val_ptr();
		for (int i = 0; i < 4; i++) {
			pxstr_->dir[i] = buff[i];
		}
	}

	parameter::Wall* ST1KL3A::get_val_ptr(){
		return pxstr_.get(); // 修正:unique_ptrの生ポインタを渡す．
	}

}
