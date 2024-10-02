#ifndef _WAIT_HPP_
#define _WAIT_HPP_

#include <stdio.h>
#include "wall_parameter.hpp"
#include "peripheral.h"
#include "stdout.h"
#include "stm32f4xx_hal.h"

namespace tim{
    class Wait{
    private:
        TIM_HandleTypeDef* htim_;
    public:
        
        Wait(TIM_HandleTypeDef* htim);
        void Us(uint32_t us);
        void Ms(uint32_t ms);
        ~Wait() = default;
    };
}

#endif // _WAIT_HPP_

