#ifndef _ADC_HPP_
#define _ADC_HPP_

#include <iostream>
#include <stdint.h>
#include "peripheral.h"
#include "stdout.h"

namespace peripheral{
	class ADC {
	private:
		ADC_HandleTypeDef* hadc_;
		uint16_t buff_[10] ={0};
		uint32_t channels_ = 5;
	public:
		ADC(ADC_HandleTypeDef* hadc);
		void ReadVal();
		uint16_t * get_val_ptr();
		~ADC() = default;
	};
}

#endif /* _ADC_HPP_ */
