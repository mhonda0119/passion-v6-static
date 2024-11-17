#ifndef _CORRECTION_HPP_
#define _CORRECTION_HPP_

#include <iostream>
#include <memory>
#include <cstdint>

#include "peripheral.h"
#include "states.hpp"
#include "consts.hpp"

namespace correction{
    class WallGap
    {
        private:
        float pre_ad_;
        float e_;
        float wall_gap_th_;
        public:
        WallGap(float wall_gap_th);
        void Correct(float wall_th , float wall_e_th , float ad);
        void Update(float& wall_th_r,float& wall_th_l , float wall_gap_c ,float ad_r,float ad_l);
        float get_wall_th();
        ~WallGap() = default;

    };
}

#endif