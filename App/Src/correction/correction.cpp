#include "correction.hpp"

namespace correction{
    WallGap::WallGap(float wall_gap_th) : pre_ad_(0),e_(0),wall_gap_th_(wall_gap_th){}

    float WallGap::Update(float wall_th , float wall_gap_th , float ad){    
        e_ = pre_ad_ - ad;
        if(abs(e_) > wall_gap_th){
            wall_th = wall_th + wall_gap_th_;
        }
        pre_ad_ = ad;
        return wall_th;
    }
}