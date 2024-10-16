#include "timencoder.hpp"

namespace peripheral{
    TimEncoder::TimEncoder(TIM_HandleTypeDef* htim, uint32_t channel)
     : htim_(htim), channel_(channel) {}

    void TimEncoder::Start(){
        HAL_TIM_Encoder_Start(htim_, channel_);
    }

    void TimEncoder::ReadVal(){
        count_ = __HAL_TIM_GET_COUNTER(htim_);
    }

    void TimEncoder::Stop(){
        HAL_TIM_Encoder_Stop(htim_, channel_);
    }

    uint32_t TimEncoder::get_val(){
        //std::cout << count_ << std::endl;
        return count_;
    }

    void TimEncoder::set_val(uint32_t count){
        count_ = count;
    }

}