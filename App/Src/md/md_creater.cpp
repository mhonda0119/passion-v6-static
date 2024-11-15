#include "md_creater.hpp"

namespace md{
	Creater::Creater(NAME name)
	:name_(name){}
	std::unique_ptr<Product> Creater::Create(TIM_HandleTypeDef* htim,uint32_t channel_r,uint32_t channel_l
	,GPIO_TypeDef* stby_port,uint16_t stby_pin,
	GPIO_TypeDef* l_cw_port,uint16_t l_cw_pin,
	GPIO_TypeDef* l_ccw_port,uint16_t l_ccw_pin,
	GPIO_TypeDef* r_cw_port,uint16_t r_cw_pin,
	GPIO_TypeDef* r_ccw_port,uint16_t r_ccw_pin){
		switch(name_){
			case NAME::TB6612FNG:
				md_ = std::make_unique<TB6612FNG>(htim,channel_r,channel_l,
				stby_port,stby_pin,
				l_cw_port,l_cw_pin,
				l_ccw_port,l_ccw_pin,
				r_cw_port,r_cw_pin,
				r_ccw_port,r_ccw_pin);
				return std::move(md_);
			default:
				return nullptr;
		}
	}
}
