#ifndef _VOL_HPP_
#define _VOL_HPP_

#include <cstdint>
#include <memory>

#include "peripheral.h"
#include "stdout.h"
#include "adc.hpp"

namespace sensor::bat{
	class Vol{
	private:
		std::shared_ptr<peripheral::ADC> adc_ ;
		uint16_t vol_;
	public:
		Vol(std::shared_ptr<peripheral::ADC> adc);
		void ReadVal();
		uint16_t get_val();
        ~Vol() = default;
	};
}

#endif //_VOL_HPP_
