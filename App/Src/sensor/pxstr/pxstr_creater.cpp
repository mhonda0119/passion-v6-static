#include "pxstr_creater.hpp"

namespace sensor::pxstr{
	Creater::Creater(NAME name)
	:name_(name){}
	std::unique_ptr<Product> Creater::Create(std::shared_ptr<peripheral::ADC> adc){
		switch(name_){
			case NAME::ST1KL3A:
				pxstr_ = std::make_unique<ST1KL3A>(adc);
				return std::move(pxstr_);
			default:
				return nullptr;
		}
	}
}