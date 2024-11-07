#include "ctrl.hpp"

namespace ctrl{
    PID::PID(float kp, float ki = 0, float kd = 0)
    :kp_(kp),ki_(ki),kd_(kd),u_(0),pre_e_(0){}

    float PID::Update(float e){
        p_ = kp_ * e;
        i_ += ki_ * e;
        d_ = kd_ * (e - pre_e_);
        pre_e_ = e;
        u_ = p_ + i_ + d_;
        return u_;
    }

    void PID::Reset(){
        pre_e_ = 0;
        u_ = 0;
        p_ = 0;
        i_ = 0;
        d_ = 0;
    }
}