#ifndef _CTRL_HPP_
#define _CTRL_HPP_

#include <iostream>
#include <memory>

#include "consts.hpp"

namespace ctrl{
    class PID{
    private:
        float kp_;
        float ki_;
        float kd_;
        float p_;
        float i_;
        float d_;
        float freq_;//制御周期
        float pre_e_;//前回の偏差
        float u_;//制御量
    public:
        PID(float kp, float ki = 0, float kd = 0 ,float freq = consts::software::CTRL_FREQ);//defaultの値を設定しとくといいかも
        void Update(float r, float y);//r:目標値 y:制御量
        void set_kp(float kp);
        void set_ki(float ki);
        void set_kd(float kd);
        float get_u();
        float get_p();
        float get_i();
        float get_d();
        void Reset();
        ~PID() = default;
    };

    class I_PD{
    private:
        float kp_;
        float ki_;
        float kd_;
        float p_;
        float i_;
        float d_;
        float freq_;//制御周期
        float pre_e_;//前回の偏差
        float pre_y_;//前回の制御量
        float u_;//制御量
    public:
        //比例微分先行型PID
        I_PD(float kp, float ki, float kd,float freq = consts::software::CTRL_FREQ);//defaultの値を設定しとくといいかも
        void Update(float r, float y);//r:目標値 y:制御量
        float get_u();
        void Reset();
        ~I_PD() = default;
    };
}

#endif // _CTRL_HPP_
