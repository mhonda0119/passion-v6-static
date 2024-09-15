
#include "waitus.h"
void Tim1WaitUs(uint32_t us){
    __HAL_TIM_SET_COUNTER(&htim1,0);
    HAL_TIM_Base_Start(&htim1);
    while(htim1.Instance -> CNT < us);
    HAL_TIM_Base_Stop(&htim1);
}