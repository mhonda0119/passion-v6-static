#include "pwm_driver.hpp"

namespace pwm{
    Driver::Driver(TIM_HandleTypeDef* htim,uint32_t channel){
        htim_ = htim;
        channel_ = channel;
        arr_ = htim_->Init.Period;
        clock_ = 2*HAL_RCC_GetPCLK1Freq();
        prescaler_ = htim_ -> Init.Prescaler;
    }
    void Driver::Start(){
        HAL_TIM_PWM_Start(htim_, channel_);
    }

    void Driver::set_duty(float duty){
        duty_ = duty;
        if(0 <= duty && duty <= 1){
            ccr_ = duty * (arr_ + 1);
        }else{}
        __HAL_TIM_SET_COMPARE(htim_,channel_,ccr_);
    }

    void Driver::set_freq(uint32_t freq){
        freq_ = freq;
        arr_ = (clock_/(freq_*(prescaler_+1)))-1;
        __HAL_TIM_SET_AUTORELOAD(htim_,arr_);
    }

    void Driver::Stop(){
        HAL_TIM_PWM_Stop(htim_,channel_);
    }
}