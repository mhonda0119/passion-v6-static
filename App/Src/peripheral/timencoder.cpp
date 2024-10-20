#include "timencoder.hpp"


namespace peripheral{
    TimEncoder::TimEncoder(TIM_HandleTypeDef* htim, uint32_t channel)
     : htim_(htim), channel_(channel) ,period_(htim_->Init.Period + 1){

        std::unique_ptr<TIM_Encoder_InitTypeDef> sConfig = std::make_unique<TIM_Encoder_InitTypeDef>();
                std::cout << "1" << std::endl;
        if(sConfig->EncoderMode == TIM_ENCODERMODE_TI1){
            edge_ = 2;
        }else if(sConfig->EncoderMode == TIM_ENCODERMODE_TI2){
            edge_ = 2;
        }else if(sConfig->EncoderMode == TIM_ENCODERMODE_TI12){
            edge_ = 4;
        }else{
            edge_ = 5;
            }
                std::cout << "2" << std::endl;
     }
    void TimEncoder::Start(){
        HAL_TIM_Encoder_Start(htim_, channel_);
    }

    void TimEncoder::ReadVal(){
        count_ = __HAL_TIM_GET_COUNTER(htim_);
        //std::cout << "Encoder Value: " << count_ << std::endl;
    }

    void TimEncoder::Stop(){
        HAL_TIM_Encoder_Stop(htim_, channel_);
    }

    uint32_t TimEncoder::get_val(){
        return count_;
    }

    void TimEncoder::set_val(uint32_t count){
        __HAL_TIM_SET_COUNTER(htim_,count);
    }

}