#include "wait.hpp"

namespace peripheral{
    Wait::Wait(TIM_HandleTypeDef* htim){
        htim_ = htim;
    }

    void Wait::Us(uint32_t us){
        __HAL_TIM_SET_COUNTER(htim_, 0);
        HAL_TIM_Base_Start(htim_);
        while(htim_->Instance->CNT < us);
        HAL_TIM_Base_Stop(htim_);
    }

    void Wait::Ms(uint32_t ms){
        HAL_Delay(ms);
    }
}
