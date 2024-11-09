#ifndef _CORRECTION_HPP_
#define _CORRECTION_HPP_

#include <iostream>
#include <memory>
#include <cstdint>

#include "peripheral.h"
#include "objects.hpp"
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
        float Update(float wall_th , float wall_e_th , float ad);
        float get_wall_th();
        ~WallGap() = default;

    };
}


#endif