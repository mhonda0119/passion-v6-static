#ifndef _TIMENCODER_HPP_
#define _TIMENCODER_HPP_

#include "peripheral.h"
#include "stm32f4xx_hal_tim.h"
#include <cstdint>
#include <memory>
#include <iostream>
namespace peripheral{
	class TimEncoder{
    private:
	TIM_HandleTypeDef* htim_;
	uint32_t channel_ = 0;
	float count_ = 0;
	public:
		float cnt_;
		uint32_t period_;
		uint32_t edge_ ;
		TimEncoder(TIM_HandleTypeDef* htim, uint32_t channel);
		void Start();
		void ReadVal();
		void Reset();
        void Stop();
        uint32_t get_val();
		void set_val(float count);
        ~TimEncoder() = default;
	};
}

#endif /* _TIMENCODER_HPP_ */