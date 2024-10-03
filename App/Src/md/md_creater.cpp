#include "md_creater.hpp"

namespace md{
	Creater::Creater(NAME name){
		name_ = NAME::TB6612FNG;
	}
	std::unique_ptr<Product> Creater::Create(TIM_HandleTypeDef* htim,uint32_t channel_r,uint32_t channel_l){
		switch(name_){
			case NAME::TB6612FNG:
				md_ = std::make_unique<TB6612FNG>(htim,channel_r,channel_l);
				return std::move(md_);
			default:
				return nullptr;
		}
	}
}
