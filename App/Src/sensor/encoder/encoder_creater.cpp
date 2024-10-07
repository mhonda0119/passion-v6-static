#include "encoder_creater.hpp"

namespace encoder{
	Creater::Creater(NAME name){
		name_ = NAME::IEH24096;
	}
	std::unique_ptr<Product> Creater::Create(TIM_HandleTypeDef* htim, uint32_t channel){
		switch(name_){
			case NAME::IEH24096:
				encoder_ = std::make_unique<IEH2_4096>();
				return std::move(encoder_);
			default:
				return nullptr;
		}
	}
}