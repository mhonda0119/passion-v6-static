#ifndef _CTRL_HPP_
#define _CTRL_HPP_

#include <iostream>
#include <memory>

namespace ctrl{
    class PID{
    private:
        float kp_;
        float ki_;
        float kd_;
        float p_;
        float i_;
        float d_;
        float pre_e_;//前回の偏差
        float u_;//制御量
    public:
        PID(float kp, float ki = 0, float kd = 0);//defaultの値を設定しとくといいかも
        float Update(float e);
        void Reset();
        ~PID() = default;
    };
}

#endif // _CTRL_HPP_
