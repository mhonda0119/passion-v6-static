#ifndef _PWM_DRIVER_HPP_
#define _PWM_DRIVER_HPP_

#include "peripheral.h"
#include <memory>
#include <iostream>
#include <cstdint>

namespace peripheral::pwm{
    class Driver{
    private://duty比と周波数を決められるようなset関数をつくりたい．
        TIM_HandleTypeDef* htim_;  // タイマのハンドル
        uint32_t channel_;         // タイマのチャネル
        uint32_t arr_;          // タイマの周期
        uint32_t ccr_ = 0;  // capturecompareregister
        float duty_ = 0; //0から1
        uint32_t freq_ = 0;//周波数．
        uint32_t clock_;//timerのクロック
        uint32_t prescaler_; 
    public:
        Driver(TIM_HandleTypeDef* htim,uint32_t channel);
        void Start();
        void set_duty(float);
        void set_freq(uint32_t);
        void Stop();
        ~Driver() = default;
    };
}

#endif //_PWM_DRIVER_HPP_
