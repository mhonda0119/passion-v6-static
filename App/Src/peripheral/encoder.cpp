#include "encoder.hpp"

namespace peripheral{
    Encoder::Encoder(TIM_HandleTypeDef* htim, uint32_t channel) : htim_(htim), channel_(channel) {}

    void Encoder::Start(){
        HAL_TIM_Encoder_Start(htim_, channel_);
    }

    void Encoder::ReadVal(){
        count_ = __HAL_TIM_GET_COUNTER(htim_);
    }

    void Encoder::Stop(){
        HAL_TIM_Encoder_Stop(htim_, channel_);
    }

    uint32_t Encoder::get_val(){
        return count_;
    }
}




