#include "buzzer.hpp"

namespace indicator::buzzer{
    Driver::Driver(){
        pwm_ = std::make_unique<pwm::Driver>(&htim3, TIM_CHANNEL_2);
    }

    void Driver::Start(uint32_t freq,float duty){
        pwm_->Start();
        pwm_->set_freq(freq);
        pwm_ ->set_duty(duty);
    }

    void Driver::Play(uint32_t freq,uint32_t duration,float duty){
        pwm_->Start();
        pwm_->set_freq(freq);
        pwm_->set_duty(duty);
        HAL_Delay(duration);
        pwm_->Stop();
    }

    void Driver::Stop(){
        pwm_->Stop();
    }
}
