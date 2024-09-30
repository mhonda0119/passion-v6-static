#include "encoder_creater.hpp"

namespace encoder{
	Creater::Creater(){
		name_ = ENCODER_NAME::IEH2_4096;
	}
	std::unique_ptr<Product> Creater::Create(){
		std::unique_ptr<Product> encoder;
		switch(name_){
			case ENCODER_NAME::IEH2_4096:
				encoder = std::make_unique<IEH2_4096>();
				return encoder;
			default:
				return nullptr;
		}
	}
}//いまんとこなんも検証してない