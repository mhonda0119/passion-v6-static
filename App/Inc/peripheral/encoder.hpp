#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include "peripheral.h"
#include <cstdint>

namespace peripheral{
	class Encoder{
    private:
	TIM_HandleTypeDef* htim_;
	uint32_t channel_;
	uint32_t count_ = 0;
	public:
		Encoder(TIM_HandleTypeDef* htim, uint32_t channel);
		void Start();
		void ReadVal();
        void Stop();
        uint32_t get_val();
        ~Encoder() = default;
	};
}

#endif /* _ENCODER_HPP_ */