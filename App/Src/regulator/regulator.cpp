#include "regulator.hpp"

namespace regulator{
    Motion::Motion()
    :r_(std::make_unique<state::Motion>()),y_(std::make_unique<state::Motion>()),u_(0.0f),
    pid_(std::make_unique<ctrl::PID>(consts::software::MOTION_KP,consts::software::MOTION_KI,consts::software::MOTION_KD)){}
    float Motion::Gen(std::unique_ptr<state::Motion> r){
        //指令値から目標値を生成
        r = C_ff->filter(r);
        //目標値rとセンサー値yを取得
        y_ = motion_->get_val_ref();
        pid->(r,y_); 
        //操作量を取得//偏差を計算して制御器に入れて操作量を取得．
        u_ = pid_->Update(r->accel[static_cast<int>(state::Motion::AXIS::X)],y_->accel[static_cast<int>(state::Motion::AXIS::X)]);

    }
}