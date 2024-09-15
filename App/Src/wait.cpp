#include "wait.hpp"

namespace tim{
    Wait::Wait(TIM_HandleTypeDef* timnum){
        tim = htim1; // 'this->' to refer to the class member
    }

    void Wait::Us(uint32_t us){
        __HAL_TIM_SET_COUNTER(&tim, 0);
        HAL_TIM_Base_Start(&tim);
        while(tim.Instance->CNT < us);
        HAL_TIM_Base_Stop(&tim);
    }
}
