#ifndef _INTERRUPT_HPP_
#define _INTERRUPT_HPP_

#include <iostream>
#include <memory>
#include "pxstr_creater.hpp"
#include "peripheral.h"
#include "stdout.h"
#include "stdint.h"
#include "wall_parameter.hpp"

namespace tim{
	class It{
	private:
        std::unique_ptr<pxstr::Product> pxstr;
        WallParameter* wp;
	public:
		It();
        void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
		~It() = default;
	};
}

#endif /* _INTERRUPT_HPP_ */