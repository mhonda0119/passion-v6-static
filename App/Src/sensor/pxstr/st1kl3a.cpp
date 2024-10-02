#include "st1kl3a.hpp"

namespace sensor::pxstr{

	ST1KL3A::ST1KL3A(){
		adc_ = std::make_unique<peripheral::adc::Driver>(&hadc1);
	}

	void ST1KL3A::Init(){

	}

	void ST1KL3A::ReadVal(){
		adc_->ReadVal();
		uint16_t* buff = adc_->get_val_ptr();
		for (int i = 0; i < 4; i++) {
			pxstr_->dir[i] = buff[i];
		}
	}

	WallParameter* ST1KL3A::get_val_ptr(){
		return pxstr_; // 修正: アドレスを返すように変更
	};

}
