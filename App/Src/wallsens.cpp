#include "wallsens.hpp"
namespace sensor{
    WallParameter* Wall::thresh_ = nullptr; // 修正: 配列として初期化
    Wall::Wall(){
        thresh_->dir[0] = 100;
        thresh_->dir[1] = 100;
        thresh_->dir[2] = 100;
        thresh_->dir[3] = 100;
        std::unique_ptr<pxstr::Creater> pxstr_c = std::make_unique<pxstr::Creater>();
        pxstr_ = pxstr_c->Create();
        ir_ = std::make_unique<ir::Driver>();
        tim1_ = std::make_unique<tim::Wait>(htim1);
    }
    void Wall::ReadVal(){
        ir_ -> On();//ir光らせる
        tim1_ -> Us(20);//充電まつ
        pxstr_ -> ReadVal();//読む
        ir_ -> Off();//ir消す
        wp_ = pxstr_ -> get_val_ptr();//代入
        std::cout << "WallParameterの中身:" << std::endl;
        for (int i = 0; i < 4; i++) {
            std::cout << "dir[" << i << "] = " << wp_->dir[i] << std::endl;
        }
        for (int i = 0; i < 4; i++) {
            if (wp_->dir[i] > thresh_->dir[i]) {
                wp_->dir[i] = 1;
            } else {
                wp_->dir[i] = 0;
            }
        }//wp_とthresh_比べてwp_のがデカければ1,小さければ0.
    }
    WallParameter* Wall::get_val_ptr(){
        return wp_;
    }
}