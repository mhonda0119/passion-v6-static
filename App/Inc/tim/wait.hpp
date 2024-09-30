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
    public:
        TIM_HandleTypeDef name_;
        Wait(TIM_HandleTypeDef name);
        void Us(uint32_t us);
        void Ms(uint32_t ms);
        ~Wait() = default;
    };
}

#endif // _WAIT_HPP_

