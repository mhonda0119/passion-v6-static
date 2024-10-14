#include "buzzer.hpp"

namespace indicator{
    Buzzer::Buzzer(TIM_HandleTypeDef* htim,uint32_t channel)
     : pwm_(std::make_unique<peripheral::PWM>(htim, channel)) {}

    void Buzzer::Start(uint32_t freq, float duty){
        pwm_->Start();
        pwm_->set_freq(freq);
        pwm_->set_duty(duty);
    }

    void Buzzer::Play(uint32_t freq, uint32_t duration, float duty){
        Start(freq, duty);
        HAL_Delay(duration);
        Stop();
    }

    void Buzzer::Stop(){
        pwm_->Stop();
    }
}
