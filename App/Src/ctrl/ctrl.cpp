#include "ctrl.hpp"

namespace ctrl{
    PID::PID(float kp, float ki, float kd,const float freq)
    :kp_(kp),ki_(ki),kd_(kd),freq_(freq),pre_e_(0),u_(0){}

    void PID::Update(float r, float y){
        // r:目標値 y:制御量
        //偏差eを計算
        float e = r - y;
        p_ = kp_ * e;
        i_ = i_ +  ki_*(pre_e_ + e)*(1/freq_)/2;
        d_ = kd_ * (e - pre_e_)/freq_;
        pre_e_ = e;
        u_ = p_ + i_ + d_;
    }

    float PID::get_u(){
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

namespace ctrl{
    I_PD::I_PD(float kp, float ki, float kd,const float freq)
    :kp_(kp),ki_(ki),kd_(kd),freq_(freq),pre_e_(0),pre_y_(0),u_(0){}

    void I_PD::Update(float r, float y){
        // r:目標値 y:制御量
        //偏差eを計算
        float e = r - y;
        i_ = i_ +  ki_*(pre_e_ + e)*(1/freq_)/2;
        p_ = kp_ * y;
        d_ = kd_ * (y - pre_y_)/freq_;
        pre_e_ = e;
        pre_y_ = y;
        u_ = i_ - i_ - d_;
    }

    float I_PD::get_u(){
        return u_;
    }

    void I_PD::Reset(){
        pre_e_ = 0;
        pre_y_ = 0;
        u_ = 0;
        p_ = 0;
        i_ = 0;
        d_ = 0;
    }
}