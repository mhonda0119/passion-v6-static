#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include "encoder_driver.hpp"
#include "peripheral.h"
#include <motion_parameter.hpp>
#include <cstdint>

namespace encoder{
	class Product{
    private:
	public:
		Product(TIM_HandleTypeDef* htim, uint32_t channel);
		virtual void Init() = 0;
		virtual void Start() = 0;
		virtual void ReadVal() = 0;
        virtual ~Encoder() = default;
		MotionParameter* get_encoder_ptr();
	};
}

#endif /* _ENCODER_HPP_ */