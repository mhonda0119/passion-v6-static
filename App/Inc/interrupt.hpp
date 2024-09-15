#ifndef _INTERRUPT_HPP_
#define _INTERRUPT_HPP_

#include <iostream>
#include <memory>
#include "pxstr_creater.hpp"
#include "peripheral.h"
#include "stdout.h"
#include "stdint.h"
#include "wall_parameter.hpp"
#include "stm32f4xx_hal.h"
#include "wait.hpp"
#include "pxstr_creater.hpp"

namespace tim{
	class It{
		private:
		static std::unique_ptr<pxstr::Product> pxstr;
		static WallParameter* wp;
		static std::unique_ptr<tim::Wait> tim1;

		public:
		It();
        static void PeriodElapsedCallback(TIM_HandleTypeDef *htim);
		~It() = default;
	};
}

#endif /* _INTERRUPT_HPP_ */