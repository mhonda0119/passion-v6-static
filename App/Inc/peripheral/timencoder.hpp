#ifndef _TIMENCODER_HPP_
#define _TIMENCODER_HPP_

#include "peripheral.h"
#include <cstdint>

#include <iostream>
namespace peripheral{
	class TimEncoder{
    private:
	TIM_HandleTypeDef* htim_;
	uint32_t channel_;
	uint32_t count_ = 0;
	public:
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