#include "st1kl3a.hpp"

namespace pxstr{

	void ST1KL3A::Init(){
		adc_ = std::make_unique<adc::Driver>();
	}

	void ST1KL3A::ReadVal(){
		adc_->ReadVal(&hadc1);
		uint16_t* buff = adc_->get_val_ptr();
		for (int i = 0; i < 4; i++) {
			pxstr_.dir[i] = buff[i];
		}
	}
	WallParameter* ST1KL3A::get_val_ptr(){
		return &pxstr_; // 修正: アドレスを返すように変更
	};

}
