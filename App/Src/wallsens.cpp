#include "wallsens.hpp"
namespace sensor{
    static constexpr WallParameter* Wall::thresh_ -> dir(static_cast<int>(DIR::R)) = 100;
    static constexpr WallParameter* Wall::thresh_ -> dir(static_cast<int>(DIR::L)) = 100;
    static constexpr WallParameter* Wall::thresh_ -> dir(static_cast<int>(DIR::FR)) = 100;
    static constexpr WallParameter* Wall::thresh_ -> dir(static_cast<int>(DIR::FL)) = 100;
    Wall::Wall(){
        std::unique_ptr<pxstr::Creater> pxstr_c = std::make_unique<pxstr::Creater>();
        pxstr_ = pxstr_c->Create();
        ir_ = std::make_unique<ir::Driver>();
        tim1_ = std::make_unique<tim::Wait>(htim1);
    }
    Wall::ReadVal(){
        ir_ -> On();//ir光らせる
        tim1_ -> Us(20);//充電まつ
        pxstr_ -> ReadVal();//読む
        ir_ -> Off();//ir消す
        wp_ = pxstr_ -> get_val_ptr();//代入
        for (int i = 0; i < 4; i++) {
            if (wp_->dir[i] > thresh_->dir[i]) {
                wp_->dir[i] = 1;
            } else {
                wp_->dir[i] = 0;
            }
        }//wp_とthresh_比べてwp_のがデカければ1,小さければ0.
    }
    Wall::get_val_ptr(){
        return wp_;
    }
}