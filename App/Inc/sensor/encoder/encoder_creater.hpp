#ifndef _ENCODER_CREATER_HPP_
#define _ENCODER_CREATER_HPP_

#include "ie24096.hpp"

namespace sensor::encoder{
	enum struct NAME{
		IEH2-4096 = 0,
	};
	class Creater{
	private:
		std::unique_ptr<sensor::encoder::Product> encoder_;
		NAME name_;
	public:
		Creater(NAME name);
		std::unique_ptr<Product> Create(TIM_HandleTypeDef* htim, uint32_t channel);
		~Creater() = default;
	};
}

#endif /* _ENCODER_CREATER_HPP_ */