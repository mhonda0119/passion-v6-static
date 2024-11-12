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
	uint32_t count_ = 0;
	
	public:
		uint32_t cnt_;
		uint32_t period_;
		uint32_t edge_ ;
		TimEncoder(TIM_HandleTypeDef* htim, uint32_t channel);
		void Start();
		void ReadVal();
        void Stop();
        uint32_t get_val();
		void set_val(uint32_t count);
        ~TimEncoder() = default;
	};
}

#endif /* _TIMENCODER_HPP_ */