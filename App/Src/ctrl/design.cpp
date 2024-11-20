#include "design.hpp"

namespace ctrl{
    Design::Design(std::unique_ptr<ctrl::AccelDesigner>& accel_designer):
    accel_designer_(accel_designer){}

    void Design::TrapeAccel(float dist , float spd_in , float spd_out){
        //加速度を設定
        accel_ = (spd_out * spd_out - spd_in * spd_in) / (2 * dist);
    // std::cout << "accel_ : " << accel_ << std::endl;
    }
    void Design::CurveAccel(float dist , float spd_in , float spd_out){
        //パラメータを設定
        accel_designer_->reset(consts::software::JERK_MAX,consts::software::ACCEL_MAX,consts::software::SPD_MAX,spd_in,spd_out,dist);
    }

    float Design::get_accel(){
        return accel_;
    }
}