#include "correction.hpp"//なんでこれだけファイル指定しなきゃならんの

namespace correction{
    WallGap::WallGap(float wall_gap_th) : pre_ad_(0),e_(0),wall_gap_th_(wall_gap_th),wall_th_(){}

    float WallGap::Update(float wall_th , float wall_e_th , float ad){    
        e_ = pre_ad_ - ad;
        if(abs(e_) > wall_gap_th_){
            wall_th = wall_th + wall_e_th;
        }
        pre_ad_ = ad;
        wall_th_ = wall_th;
        return wall_th_;
    }

    float WallGap::get_wall_th(){
        return wall_th_;
    }
}