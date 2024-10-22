#ifndef _VOL_HPP_
#define _VOL_HPP_

#include <cstdint>
#include <memory>
#include <cstring>

#include "stdout.h"
#include "adc.hpp"

namespace sensor{
	class Vol : public Elec{
	private:
		std::unique_ptr<peripheral::Adc> adc_ = nullptr;
		std::unique_ptr<parameter::Motion> vol_;
		ADC_HandleTypeDef* hadc_;
		uint32_t channel_;
	public:
		Vol(ADC_HandleTypeDef* hadc, uint32_t channel);
		void Init() override;
		void ReadVal() override;
        virtual ~Vol() = default;
	};
}

#endif //_VOL_HPP_
