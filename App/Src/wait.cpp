#include "wait.hpp"

namespace tim{
    Wait::Wait(TIM_HandleTypeDef name){
        name_ = name;
    }

    void Wait::Us(uint32_t us){
        __HAL_TIM_SET_COUNTER(&name_, 0);
        HAL_TIM_Base_Start(&name_);
        while(name_.Instance->CNT < us);
        HAL_TIM_Base_Stop(&name_);
    }

    void WaitMs(uint32_t ms){
        HAL_Delay(ms);
    }
}
