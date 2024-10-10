#include "encoder_creater.hpp"

namespace sensor::encoder{
	Creater::Creater(NAME name)
	:name_(name){}
	std::unique_ptr<Product> Creater::Create(TIM_HandleTypeDef* htim, uint32_t channel){
		switch(name_){
			case NAME::IEH24096:
				encoder_ = std::make_unique<IEH24096>();
				return std::move(encoder_);
			default:
				return nullptr;
		}
	}
}