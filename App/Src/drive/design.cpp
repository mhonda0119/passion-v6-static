#include "design.hpp"

namespace drive{
    Design::Design(){
    }
    void Design::TrapeAccel(float dist , float spd_in , float spd_out){
        //加速度を設定
        accel_ = (spd_out * spd_out - spd_in * spd_in) / (2 * dist);
    std::cout << "accel_ : " << accel_ << std::endl;
    }
    float Design::get_accel(){
        return accel_;
    }
}