#ifndef _MD_CREATER_HPP_
#define _MD_CREATER_HPP_

#include "tb6612fng.hpp"

namespace md{
	enum struct NAME{
		TB6612FNG = 0,
	};
	class Creater{
	private:
	std::unique_ptr<Product> md_;
	NAME name_;
	public:
		Creater(NAME name);
		std::unique_ptr<Product> Create(TIM_HandleTypeDef* htim,uint32_t channel_l,uint32_t channel_r);
		~Creater() = default;
	};
}

#endif /* _MD_CREATER_HPP_ */