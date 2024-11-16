#include "correction.hpp"//なんでこれだけファイル指定しなきゃならんの

namespace correction{
    WallGap::WallGap(float wall_gap_th) : pre_ad_(0),e_(0),wall_gap_th_(wall_gap_th){}

    void WallGap::Correct(float wall_th , float ad, float wall_gap_c){
        e_ = pre_ad_ - ad;
        if(abs(e_) > wall_gap_th_){
            wall_th = wall_th + wall_gap_c;
        }
        pre_ad_ = ad;
    }

    void WallGap::Update(float& wall_th_l, float& wall_th_r , float ad_l, float ad_r ,float wall_gap_c){
        this->Correct(wall_th_l,wall_gap_c,ad_l);
        this->Correct(wall_th_r,wall_gap_c,ad_r);
    }

}