#ifndef _WAIT_HPP_
#define _WAIT_HPP_

#include <stdio.h>
#include <stdint.h>
#include "peripheral.h"
#include "stdout.h"
#include "stm32f4xx_hal.h"

namespace tim{
    class Wait{
    private:
        TIM_HandleTypeDef tim;
    public:
        Wait(TIM_HandleTypeDef* timnum);
        void Us(uint32_t us);
        ~Wait() = default;
    };
}

#endif // _WAIT_HPP_

