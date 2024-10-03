#include "encoder.hpp"

namespace encoder{
    Driver::Driver(TIM_HandleTypeDef* htim,uint32_t channel){
        htim_ = htim;
        channel_ = channel;
    }

    void Driver::Start(){
        HAL_TIM_Encoder_Start(htim_, channel_);
    }

    void Driver::ReadVal(){
        count_ = __HAL_TIM_GET_COUNTER(htim_);
    }

    void Driver::Stop(){
        HAL_TIM_Encoder_Stop(htim_, channel_);
    }

    uint32_t Driver::get_val(){
        return count_;
    }
}




