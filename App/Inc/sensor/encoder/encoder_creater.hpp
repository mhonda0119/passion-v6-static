#ifndef _ENCODER_CREATER_HPP_
#define _ENCODER_CREATER_HPP_

#include "ieh24096.hpp"

namespace sensor::encoder{
	enum struct NAME{
		IEH24096 = 0,
	};
	class Creater{
	private:
		std::unique_ptr<Product> encoder_;
		NAME name_;
	public:
		Creater(NAME name);
		std::unique_ptr<Product> Create(TIM_HandleTypeDef* htim, uint32_t channel);
		~Creater() = default;
	};
}

#endif /* _ENCODER_CREATER_HPP_ */