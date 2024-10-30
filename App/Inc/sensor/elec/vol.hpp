#ifndef _VOL_HPP_
#define _VOL_HPP_

#include <cstdint>
#include <memory>
#include <cstring>

#include "stdout.h"
#include "adc.hpp"

namespace sensor::elec{
	class Vol{
	private:
		ADC_HandleTypeDef* hadc_ = nullptr;
		std::unique_ptr<peripheral::Adc> adc_ = nullptr;
		uint16_t vol_ = 0;
	public:
		Vol(ADC_HandleTypeDef* hadc);
		void Init() ;
		void ReadVal() ;
		uint16_t get_val();
        void  ~Vol() = default;
	};
}

#endif //_VOL_HPP_
